/***************************************************************************
    Copyright (C) 1986-2011 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/
// crvsynch.cpp

#pragma warning( disable : 4786 )

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_chain.h"
#include "cs_nmcurves.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)     a ; 
#else
#define CS_DEBUG(a)
#endif


// Note

static CS_CurveSyncData *csdptr(CS_CurveSyncData **pbase, int n, int idx)
{
    if (idx >= n)
        return *pbase ;
    return *(pbase + idx) ; 
}

static int CrvPntEQ(CS_CrvPnt &cp1, CS_CrvPnt &cp2)
{
    if (cp1.s != cp2.s)
        return 0 ; 
    if (tcomp_NEQ(cp1.u, cp2.u))
        return 0 ; 
    return 1 ; 
}


// Advance the curve point to the next segment or up to the end CrvPnt
// i=current j=next node. This uses cpi as the reference point of where
// the step is occuring from. The next step point is then saved in the 
// cpj variable. In the logic cpi = cpj is done before calling this
// function. Thus cpi is advanced first, and then cpi is advanced using
// it's current value. So upon entry, cpi==cpj will usually hold. Not 
// sure if a condition exists when they aren't equal. 
// Returns true if it hits the cpmax end point during the advance.
int AdvanceCP(CS_CrvPnt &cpi, CS_CrvPnt &cpj, CS_CrvPnt &cpmax) 
{
    int hitmax = 0 ; 

    if (cpi.s != cpmax.s)
    {   // For sure we are taking a step. Don't have to worry about wrapping on 
        // an open curve since that condition can't occur
        cpj.s = cpi.s->pParent->Next(cpi.s) ; 
        cpj.u = 0.0 ; 

        if (cpj.s == cpmax.s && tcomp_LEQ(cpmax.u, 0.0))
            hitmax = 1 ; 
    }
    else
    {   // We are on the max segment already. 
        cpj.s = cpmax.s ; 
        cpj.u = cpmax.u ; 
        hitmax = 1 ; 
    }

    return hitmax ; 
}

// This is required for the initial step. This was required to deal with the 
// condition where there is a single synchronization data point under the condition where there is
// 
int AdvanceCPInit(CS_CrvPnt &cpi, CS_CrvPnt &cpj, CS_CrvPnt &cpmax) 
{
    int hitmax = 0 ; 

    CS_Curve *ppc = cpi.s->pParent ; 

    if (cpi.s != cpmax.s)
    {   // For sure we are taking a step. Don't have to worry about wrapping on 
        // an open curve since that condition can't occur
        cpj.s = cpi.s->pParent->Next(cpi.s) ; 
        cpj.u = 0.0 ; 

        if (cpj.s == cpmax.s && tcomp_LEQ(cpmax.u, 0.0))
            hitmax = 1 ; 
    }
    else if (ppc->Closed() && ppc->nodecnt > 1 && tcomp_GEQ(cpi.u, cpmax.u))
    {   // Then we are going right around the shape and still need to 
        // set to next segment normally. 
        cpj.s = cpi.s->pParent->Next(cpi.s) ; 
        cpj.u = 0.0 ; 
    }
    else
    {   // We are on the max segment already. 
        cpj.s = cpmax.s ; 
        cpj.u = cpmax.u ; 
        hitmax = 1 ; 
    }

    return hitmax ; 
}


int _synccomp(const void *a, const void *b)
{
    const CS_CurveSyncData *pa = *((CS_CurveSyncData **)a) ; 
    const CS_CurveSyncData *pb = *((CS_CurveSyncData **)b) ; 
    if (tcomp_GT(pa->ua, pb->ua))
        return 1 ; 
    else if (tcomp_LT(pa->ua, pb->ua))
        return -1 ; 
    else if (tcomp_GT(pa->ub, pb->ub))
        return 1 ; 
    else if (tcomp_LT(pa->ub, pb->ub))
        return -1 ; 
    return 0 ; // else identical nodes. (this shouldn't happen)
}

// See RR-Geom Vol 4 pg 157 for notes. 
static void FixGroup(CS_CurveSyncData **pdata, int ip, int as, int ae, int in, int ndata)
{
    if (as == ae)
        return ; // only one node in group so nothing to do

    if (ip == in)
    {
        return ; // nothing to do since the way it is is OK
        // note that in this case there will only be a single set of 
        // values in the A list where all ua values match (one A group)
    }

    if (tcomp_LT(pdata[ip]->ub, pdata[in]->ub))
    {
        return ; // nothing to do since the group will have all the ub
        // values will be in a valid ascending order
    }

    // Otherwise bunxt < buprev which means the B group crosses the 0/1 boundary
    // of the B curve

    int isplit = as ; 
    while (isplit < ndata && tcomp_LT(pdata[isplit]->ub, pdata[in]->ub)) isplit++ ; 
    if (isplit == in)
        return ; // nothing to do. 

    // isplit now marks the split point in the a group. Need a temp array
    // to store the shifted data
    CS_CurveSyncData **ptmp = new CS_CurveSyncData*[ae - as + 1] ; 
    int j = 0 ; 
    int k = isplit ; 
    while (k <= ae)
    {
        ptmp[j] = pdata[k] ; 
        j++ ; 
        k++ ; 
    }

    k = as ; 
    while (k < isplit)
    {
        ptmp[j] = pdata[k] ; 
        j++ ; 
        k++ ; 
    }

    assert(j == (ae - as + 1)) ;

    // Now copy this back into the original array. 
    for (j=0, k=as; k <= ae; j++, k++)
        pdata[k] = ptmp[j] ; 

    // Should now be properly aligned. 
    delete[] ptmp ; 
}

void AdjustSyncCrvPnt(CS_CrvPnt &cp)
{
    if (tcomp_GEQ(cp.u, 1.0))
    {
        if (cp.s->next)
        {
            cp.s = cp.s->next ; 
            cp.u = 0.0 ; 
        }
        else if (cp.s->pParent->statflags & CS_CLOSEDCURVE)
        {
            cp.s = cp.s->pParent->Next(cp.s) ; 
            cp.u = 0.0 ; 
        }
    }
    // else do nothing
}

int CS_SortCurveSyncData(CS_CurveSyncData **pdata, int ndata, int closed)
{
    // First scan to make sure no ua=1 nodes exist for closed case
    int i ; 
    for (i=0; i < ndata; i++)
    {
        if (closed)
        { 
            if (tcomp_GEQ(pdata[i]->ua, 1.0))
                pdata[i]->ua = 0.0 ; 
            if (tcomp_GEQ(pdata[i]->ub, 1.0))
                pdata[i]->ub = 0.0 ; 
        }

        AdjustSyncCrvPnt(pdata[i]->cpa) ; // moves end point to start point of next
        AdjustSyncCrvPnt(pdata[i]->cpb) ; // segment so data always in range [0,1)
    }   

    qsort(pdata, ndata, sizeof(CS_CurveSyncData*), _synccomp) ; 
    
    // Final step is to reprocess groups 
    i = 0 ; 
    int as, ae ; 
    while (i < ndata)
    {
        int iprev, inext ;
        as = ae = inext = i ; 
        while (inext < ndata && tcomp_EQ(pdata[as]->ua, pdata[inext]->ua)) 
        {
            ae = inext ; 
            inext++ ; 
        }
        // as, ae define the start and end of the group to test. 
        iprev = as - 1 ; 
        if (iprev < 0)  
            iprev = ndata - 1 ; // then went backwards through start
        
        if (inext == ndata)
            inext = 0 ; // then went past the end

        FixGroup(pdata, iprev, as, ae, inext, ndata) ; 
        i = ae + 1 ; 
    }
    return 0 ; 
}

int CS_FreeCurveSyncData(CS_CurveSyncData **pdata, int ndata)
{
    for (int i=0; i < ndata; i++)
        free(pdata[i]) ; 
    free(pdata) ; 
    return 0 ; 
}


// See notes GEOM RR-Vol4 Pgs 154-159
int CS_CurveSynch(CS_Curve &crva, CS_Curve &crvb, 
                  CS_Curve &scrva, CS_Curve &scrvb, 
                  CS_CurveSyncData **pdata, int ndata)
{
    CS_CurveSyncData endnodes[2] ; 
    CS_CurveSyncData *pendptrs[2] ; 
    int closed = crva.Closed() ; 

    if (ndata == 0)
    {   // Then create a single node array
        endnodes[0].ua = 0.0 ; 
        endnodes[0].cpa.s = crva.pStart ; 
        endnodes[0].cpa.u = 0.0 ; 
        endnodes[0].ub = 0.0 ; 
        endnodes[0].cpb.s = crvb.pStart ; 
        endnodes[0].cpb.u = 0.0 ; 

        endnodes[1].ua = 1.0 ; 
        endnodes[1].cpa.s = crva.pEnd ; 
        endnodes[1].cpa.u = 1.0 ; 
        endnodes[1].ub = 1.0 ; 
        endnodes[1].cpb.s = crvb.pEnd ; 
        endnodes[1].cpb.u = 1.0 ; 

        pendptrs[0] = &endnodes[0] ;
        pendptrs[1] = &endnodes[1] ;
        pdata = pendptrs ; 
        
        if (closed)
            ndata = 1 ; 
        else
            ndata = 2 ; 
    }

    CS_CurveSyncData *psd1, *psd2 ; 
    CS_CrvPnt cpa1(0,0), cpa2(0,0) ; 
    CS_CrvPnt cpb1(0,0), cpb2(0,0) ; 
    CS_CrvPnt cpai(0,0), cpbi(0,0) ; // previous node added
    CS_CrvPnt cpaj(0,0), cpbj(0,0) ; // previous node added
    double ua1, ua2 ; // current from-to range on the A curve
    double ub1, ub2 ; // current from-to range on the B curve
    double uai, ubi ; // previous point processed
    double uaj, ubj ; // current point being processed

    // Establish the current node pair.
    psd1 = csdptr(pdata, ndata, 0) ;
    psd2 = csdptr(pdata, ndata, 1) ;

    cpa1 = psd1->cpa ; 
    cpa2 = psd2->cpa ; 
    ua1  = psd1->ua ; 
    ua2  = psd2->ua ; 

    cpb1 = psd1->cpb ; 
    cpb2 = psd2->cpb ; 
    ub1  = psd1->ub ; 
    ub2  = psd2->ub ; 

    CS_CrvPnt cpexit ; // when we hit this node we're done
    if (crva.Closed())
    {   // Set to the start node
        cpexit = cpa1 ;
    }
    else 
    {   // Take the last record in the array 
        cpexit = csdptr(pdata, ndata, ndata-1)->cpa ; 
    }

    // Now figure out the number of a and b groups
    int i ; 
    double lastua = -1.0 ; 
    double lastub = -1.0 ; 
    int grpacnt = 0 ; 
    int grpbcnt = 0 ; 

    // A group refers to a set of nodes that all have the same
    // u coordinate on the curve. Thus if a group has more than one 
    // node in it then there is a stationary point on that curve
    // there relative to the other curve. 
    for (i=0 ; ((grpacnt < 2) || (grpbcnt < 2)) && (i < ndata); i++)
    {
        if (tcomp_NEQ(lastua, pdata[i]->ua))
        {
            grpacnt += 1 ; 
            lastua = pdata[i]->ua ; 
        }

        if (tcomp_NEQ(lastub, pdata[i]->ub))
        {
            grpbcnt += 1 ; 
            lastub = pdata[i]->ub ; 
        }
    }

    double ualen, ublen ; 
    double uajdist, ubjdist ; 
    double ubrk ; 
    CS_SegPtr pseg, psegnxt ; 

    i = 1 ; // loop counter
    // Now process records between these nodes. 
    do {
        // Init the loop pointers
        ualen = crva.ULength(ua1, ua2) ;
        ublen = crvb.ULength(ub1, ub2) ;
        // Can't remember what this condition is testing for any more
        // Looks like it deals with the condition where there is a zero
        // length node right at the start/end of one of the curves and 
        // the overall processing begins right at that point. Then this
        // corrects the ulen value that results. 
        // See Geom Algo's RR-Vol4 pg 159 for some very sketchy notes.
        if (tcomp_GEQ(ualen, 1.0) && grpacnt > 1 && closed)
            ualen = 0.0 ; 
        if (tcomp_GEQ(ublen, 1.0) && grpbcnt > 1 && closed)
            ublen = 0.0 ;
        
        if (tcomp_EQZ(ualen))
        {   // Then A defines a stationary point with a zero length section
            // so we need to insert zero length lines here
            CS_POINT apnt = cpa1.Point() ; 

            CS_Curve *pcbsect = crvb.CopySection(cpb1, cpb2) ;
            pseg = pcbsect->pStart ; 
            while (pseg)
            {
                scrva.Append(new CS_LineSeg(apnt, apnt), CS_NOENDPOINTADJUSTMENT) ; 
                psegnxt = pcbsect->Remove(pseg) ;
                scrvb.Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                pseg = psegnxt ; 
            }
        }
        else if (tcomp_EQZ(ublen))
        {   // Then B defines a stationary point with a zero length section
            // so we need to insert zero length lines here
            CS_POINT bpnt = cpb1.Point() ; 

            CS_Curve *pcasect = crva.CopySection(cpa1, cpa2) ;
            pseg = pcasect->pStart ; 
            while (pseg)
            {
                scrva.Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                psegnxt = pcasect->Remove(pseg) ;
                scrvb.Append(new CS_LineSeg(bpnt, bpnt), CS_NOENDPOINTADJUSTMENT) ; 
                pseg = psegnxt ; 
            }
        }
        else
        {   // Process normally

            int hitmaxA = 0 ; 
            int hitmaxB = 0 ; 
            int didmaxA = 0 ; 
            int didmaxB = 0 ; 

            cpai = cpa1 ;
            cpbi = cpb1 ;
            hitmaxA |= AdvanceCPInit(cpai, cpaj, cpa2) ; 
            hitmaxB |= AdvanceCPInit(cpbi, cpbj, cpb2) ; 

            uai = cpai.UCrv() ; 
            uaj = cpaj.UCrv() ; 
            ubi = cpbi.UCrv() ; 
            ubj = cpbj.UCrv() ;  

            // Now work through the [ua1,ua2], [ub1,ub2] curve sections
            do {
                // uajdist and ubjdist are relative to the ualen and ublen sections

                // Make sure that the math has screwed up. If ua1 and ua2 are almost 
                // at the exact same point, then on a closed curve the ULength() will
                // come back as 1 instead of zero. We must reset this length back to 
                // zero in this case, but only if the section length that we are 
                // traversing over is less than 1.0 also. Must also test to make sure
                // that the a and b lengths are not both 0 since in that case we 
                // can never advance correctly. If not at the end of both segments
                // in that case then simply step to the end of the segment and 
                // continue processing. 

                double crvaUlen = crva.ULength(ua1, uaj) ; 
                double crvbUlen = crvb.ULength(ub1, ubj) ; 

                if (tcomp_GEQ(crvaUlen, 1.0) && tcomp_LT(ualen, 1.0))
                {
                    uajdist = 0.0 ; 
                }
                else
                {
                    uajdist = crva.ULength(ua1, uaj) / ualen ; 
                    if (uajdist > 1.0)
                        uajdist = 1.0 ; 
                }

                if (tcomp_GEQ(crvbUlen, 1.0) && tcomp_LT(ublen, 1.0))
                {
                    ubjdist = 0.0 ; 
                }
                else
                {
                    ubjdist = crvb.ULength(ub1, ubj) / ublen ; 
                    if (ubjdist > 1.0)
                        ubjdist = 1.0 ; 
                }

                // Trap the final possible error condition where both segments
                // work out to zero, in which case set them both to the same 
                // length of one. 
                if (uajdist == 0.0 && ubjdist == 0.0)
                {
                    uajdist = 1.0 ; 
                    ubjdist = 1.0 ; 
                }

                if (tcomp_LT(uajdist, ubjdist))
                {   // Then we hit the next node on the a curve first
                    // which means we have to break the b curve at the matching
                    // location
                    scrva.Append(cpai.s->Copy(cpai.u, 1.0)) ;
                    ubrk = crvb.UNorm(ub1 + uajdist * ublen) ; 
                    CS_CrvPnt cpbrk ; 
                    crvb.CrvU2SegU(ubrk, cpbi.s, cpbrk) ; 
                    if (closed && tcomp_GEQ(cpbrk.u, 1.0))
                    {
                        cpbrk.s = cpbrk.s->pParent->Next(cpbrk.s) ; 
                        cpbrk.u = 0.0 ; 
                    }
                    assert(cpbrk.s == cpbi.s) ; 
                    scrvb.Append(cpbi.s->Copy(cpbi.u, cpbrk.u)) ; 
                    // update the new B location
                    cpbi.u = cpbrk.u ; 

                    if (hitmaxA)
                        didmaxA = 1 ; 

                    // Advance the A node
                    cpai = cpaj ; 
                    hitmaxA |= AdvanceCP(cpai, cpaj, cpa2) ; 
                    uai = cpai.UCrv() ; 
                    uaj = cpaj.UCrv() ; 
                }
                else if (tcomp_LT(ubjdist, uajdist))
                {   // Then we hit the next node on the b curve first
                    // which means we have to break the a curve at the matching
                    // location
                    scrvb.Append(cpbi.s->Copy(cpbi.u, 1.0)) ;
                    ubrk = crva.UNorm(ua1 + ubjdist * ualen) ; 
                    CS_CrvPnt cpbrk ; 
                    crva.CrvU2SegU(ubrk, cpai.s, cpbrk) ;
                    if (closed && tcomp_GEQ(cpbrk.u, 1.0))
                    {
                        cpbrk.s = cpbrk.s->pParent->Next(cpbrk.s) ; 
                        cpbrk.u = 0.0 ; 
                    }
                    assert(cpbrk.s == cpai.s) ;
                    scrva.Append(cpai.s->Copy(cpai.u, cpbrk.u)) ;
                    // update the new A location
                    cpai.u = cpbrk.u ;

                    if (hitmaxB)
                        didmaxB = 1 ; 

                    // Advance the B node
                    cpbi = cpbj ;
                    hitmaxB |= AdvanceCP(cpbi, cpbj, cpb2) ;
                    ubi = cpbi.UCrv() ;
                    ubj = cpbj.UCrv() ;
                }
                else if (tcomp_NEQ(uai, ua2) && tcomp_NEQ(ubi, ub2))
                {   // Then advance both segments since they are both completely
                    // synched with one another
                    if (cpai.s == cpa2.s)
                    {
                        scrva.Append(cpai.s->Copy(cpai.u, cpa2.u)) ;
                    }
                    else
                    {
                        scrva.Append(cpai.s->Copy(cpai.u, 1.0)) ;
                    }
                    
                    if (cpbi.s == cpb2.s)
                    {
                        scrvb.Append(cpbi.s->Copy(cpbi.u, cpb2.u)) ;
                    }
                    else
                    {
                        scrvb.Append(cpbi.s->Copy(cpbi.u, 1.0)) ;
                    }

                    if (hitmaxA) 
                        didmaxA = 1 ; 
                    if (hitmaxB) 
                        didmaxB = 1 ; 

                    cpai = cpaj ;
                    cpbi = cpbj ;
                    hitmaxA |= AdvanceCP(cpai, cpaj, cpa2) ;
                    hitmaxB |= AdvanceCP(cpbi, cpbj, cpb2) ;
                    uai = cpai.UCrv() ;
                    uaj = cpaj.UCrv() ;
                    ubi = cpbi.UCrv() ;
                    ubj = cpbj.UCrv() ;
                }
                else
                {   // Then uai == ua2 && ubi == ub2)
                    // which likely means that we ended up with a double 
                    // zero length section so just exit the loop
                    break ; 
                }
            } while (!didmaxA && !didmaxB) ;
            

            // The old exit condition was the following. 
            // while (tcomp_NEQ(uai, ua2) && tcomp_NEQ(ubi, ub2)) ;
            // POSSIBLE BUG: in the while() condition above the exit condition
            // may not be reliable. As far as current thoughts go, the two sections
            // should end simultaneously.
            // Note: I think the exit condition is now reliable with the hitmax logic
        }

        // Increment all the loop variables
        i++ ;
        psd1 = psd2 ;
        psd2 = csdptr(pdata, ndata, i) ;

        cpa1 = psd1->cpa ;
        cpa2 = psd2->cpa ;
        ua1  = psd1->ua ;
        ua2  = psd2->ua ;

        cpb1 = psd1->cpb ;
        cpb2 = psd2->cpb ;
        ub1  = psd1->ub ;
        ub2  = psd2->ub ;
    } while (i <= ndata) ;

    return 0 ;
}
