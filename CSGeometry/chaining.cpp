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
// chaining.cpp - curve chaining and connection functions

#pragma warning( disable : 4786 )
// #pragma warning( disable : 4800 )

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_chain.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)      
#else
#define CS_DEBUG(a)
#endif

//   DEBUGXXX(fprintf(fpDebugOut, "Line %d\n", __LINE__ )) ; 
// #define DEBUGXXX(a)     a

// Trigger which must be manually set and unset to trigger data output
int chainDebugSaveCurves = 0 ; 
char *szChainDebugFileName = 0 ; 
FILE *fpChainDebugFile = 0 ; 

// The curve chaining can operate in several modes, RIGHT, LEFT, TANGENT, and
// CUSTOM

int __cdecl CompChainSeg(const void *a, const void *b)
{
    if ( ((CS_ChainSegment *)a)->bndbox.l < ((CS_ChainSegment *)b)->bndbox.l)
        return -1 ; 
    else if (((CS_ChainSegment *)a)->bndbox.l > ((CS_ChainSegment *)b)->bndbox.l)
        return 1 ; 
    return 0 ; 
}


// Remove p
CS_ChainSegment *RemoveFromList(CS_ChainSegment* &pfirst, CS_ChainSegment* pdel)
{
    if (pfirst == pdel)
        pfirst = pdel->next ; 
    if (pdel->prev)
        pdel->prev->next = pdel->next ; 
    if (pdel->next)
        pdel->next->prev = pdel->prev ; 
    return pdel->next ; 
}

int CS_ChainUniqueSegments(CS_CurveSet &csin, CS_CurveSet &csout)
{
    CS_Curve *pcrv ; 
    int retval = 0 ; 

    csin.InitIterator() ;
    int segcount = 0 ; 
    while (pcrv = csin.NextCurve())
        segcount += pcrv->nodecnt ; 

    if (segcount == 0)
        return 0 ; // nothing to do

    CS_SegPtr *psegs = new CS_SegPtr[segcount + 2] ; 

    csin.InitIterator() ;
    int sc = 0 ; 
    while (pcrv = csin.NextCurve())
    {
        CS_SegPtr ps = pcrv->pStart ; 
        while (ps && (sc < segcount))
        {
            psegs[sc++] = ps ; 
            ps = ps->next ; 
        }

        if (sc >= segcount)
        {   // Then something is wrong, nodecount error in the 
            // input curveset.
            retval |= 0x00010000 ; // signal the error condition
            break ; 
        }
    }

    retval |= CS_ChainUniqueSegments(psegs, sc, csout) ; 

    delete psegs ; 
    
    return retval ; 
}


//! This is where the linker fails. 
/*
int CS_ChainUniqueSegments(CS_Segment **pIN, int nIN, CS_CurveSet &crvset, double *tol)
{
    int i ;

    // Intersect all the segments together. The first step is to sort all the 
    // segments based on their rectangles

    CS_ChainSegment *pfirst, *plast, *pnxt ; 
    CS_ChainSegment *pchnseg = new CS_ChainSegment[nIN+4] ;

    for (i=0; i < nIN; i++)
    {
        pchnseg[i].pseg = pIN[i] ;
        pchnseg[i].status = 0 ;
        pchnseg[i].bndbox = pIN[i]->BoundingRect() ; 
        pchnseg[i].bndbox.Expand(0.01) ; 
    }

    // Now sort the segments based on their left rect values.
    qsort(pchnseg, nIN, sizeof(CS_ChainSegment), CompChainSeg) ;


    // Connect up the list pointers
    for (i=0; i < nIN; i++)
    {
        pchnseg[i].next = &pchnseg[i+1] ;
        pchnseg[i+1].prev = &pchnseg[i] ;
    }

    // Only have to assign and clean up the first and last pointers
    pfirst = &pchnseg[0] ;
    plast = &pchnseg[nIN-1] ; 
    pfirst->prev = 0 ; 
    plast->next = 0 ; 

    // Chain simply connected segments together and filter out overlapping
    // segments.
    CS_SegPtr pseg ; 
    CS_IREC *pirec ; 
    int resmask ; 
    CS_Curve *pcrv ; 

    while (pfirst)
    {
        pcrv = new CS_Curve ; 
        pcrv->Append(pfirst->pseg->Copy()) ; 
        
        // Delete the first node from the list since it has been used
        pnxt = pfirst ; 
        pnxt = RemoveFromList(pfirst, pnxt) ; 
        
        bool bConnectedNewSegment = true ; 

        while (bConnectedNewSegment)
        {
            bConnectedNewSegment = false ;
            pnxt = pfirst ;
            while (pnxt)
            {
                if (0 != (resmask = SegmentsConnected(pcrv->pStart, pnxt->pseg, tol)))
                {   
                    bool overlapped = false ;

                    if (pnxt->pseg->SegmentType() == pcrv->pStart->SegmentType())
                    {   // Check if they overlap
                        CS_IRECList isset ;
                        CS_IRECListItr iri ;
                        pnxt->pseg->Intersect2D(pcrv->pStart, &isset) ;
                        for (iri = isset.begin(); iri != isset.end(); iri++)
                        {
                            pirec = iri->pir ; 
                            if (pirec->statinfo & CS_IREC::OVERLAP)
                            {   // Then don't want to append this record
                                overlapped = true ; 
                                break ;
                            }
                        }
                    }

                    //////////////////////////////////////////////////////////
                    // TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO 
                    // Have to check to see if the pnxt overlap record covers
                    // the [0,1] range. If it doesn't then we have to trim the 
                    // segment out that doesn't overlap and append it to the 
                    // end of the list of segments to test against
                    //////////////////////////////////////////////////////////


                    // Note: the logic below never reorients the segments in 
                    // the pcrv. 

                    int bProcessed = false ; 
                    if (!overlapped)
                    {   
                        if (resmask == CS_CONNECT_ALL)
                        {   // Then both end points are connected
                            // Should only get here if there are two segments which form
                            // a loop which means one of the segments 
                            assert(pcrv->nodecnt == 1) ; 

                            // THIS IS WRONG - the only way all end points can be connected
                            // is if the curve is a complete circle and the segment to be
                            // added is a complete circle, in which case we have two 
                            // overlapping circles and thus one of them should be discarded

                            // Test this by creating two overlapping circles and see if 
                            // this logic is entered. Note for this to work, complete 
                            // circles have to be normalized so that they start at 0 
                            // degrees, otherwise the start points won't overlap and 
                            // this condition will not be trapped. 


                            if (pcrv->pStart->StartPoint() == pnxt->pseg->StartPoint())
                            {   // Then reverse the second curve
                                pseg = pnxt->pseg->Copy() ; 
                                pseg->Reverse() ; 
                                pcrv->Insert(pcrv->pStart, pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            }
                            else
                            {   // Add it to the end
                                pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                            }
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_START) &&
                            (resmask & CS_CONNECT_B_START))
                        {   // reverse B and insert before A
                            pseg = pnxt->pseg->Copy() ; 
                            pseg->Reverse() ; 
                            pcrv->Insert(pcrv->pStart, pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_START) &&
                                 (resmask & CS_CONNECT_B_END))
                        {
                            pcrv->Insert(pcrv->pStart, pnxt->pseg->Copy(), 
                                                    CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if (pcrv->nodecnt == 1) 
                        {
                            if ((resmask & CS_CONNECT_A_END) &&
                                (resmask & CS_CONNECT_B_END))
                            {
                                pseg = pnxt->pseg->Copy() ; 
                                pseg->Reverse() ; 
                                pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                                bProcessed = true ; 
                                bConnectedNewSegment = true ; 
                            }
                            else if ((resmask & CS_CONNECT_A_END) &&
                                     (resmask & CS_CONNECT_B_START))
                            {
                                pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                                bProcessed = true ; 
                                bConnectedNewSegment = true ; 
                            }
                        }
                        // else (resmask & CS_CONNECT_A_END) must hold
                        // In this case simply want to skip the segment and 
                        // continue processing
                    }
                    
                    // delete pnxt since if it has been processed
                    if (bProcessed) 
                    {
                        pnxt = RemoveFromList(pfirst, pnxt) ; 
                        continue ; 
                    }
                    else 
                    {
                        int x = 0 ; 
                        x += 1 ; 
                    }
                }
                else if (0 != (resmask = SegmentsConnected(pcrv->pEnd, pnxt->pseg, tol)))
                {
                    bool overlapped = false ; 

                    if (pnxt->pseg->SegmentType() == pcrv->pStart->SegmentType())
                    {   // Check if they overlap
                        CS_IRECList isset ; 
                        CS_IRECListItr iri ;
                        pnxt->pseg->Intersect2D(pcrv->pEnd, &isset) ; 
                        for (iri = isset.begin(); iri != isset.end(); iri++)
                        {
                            pirec = iri->pir ; 
                            if (pirec->statinfo & CS_IREC::OVERLAP)
                            {   // Then don't want to append this record
                                overlapped = true ; 
                                break ;
                            }
                        }
                    }

                    //////////////////////////////////////////////////////////
                    // TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO 
                    // Have to check to see if the pnxt overlap record covers
                    // the [0,1] range. If it doesn't then we have to trim the 
                    // segment out that doesn't overlap and append it to the 
                    // end of the list of segments to test against
                    //////////////////////////////////////////////////////////


                    // Note: the logic below never reorients the segments in 
                    // the pcrv. 

                    int bProcessed = false ; 
                    if (!overlapped)
                    {   
                        if ((resmask & CS_CONNECT_A_END) &&
                            (resmask & CS_CONNECT_B_END))
                        {   // reverse B and append to curve
                            pseg = pnxt->pseg->Copy() ; 
                            pseg->Reverse() ; 
                            pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_END) &&
                                 (resmask & CS_CONNECT_B_START))
                        {
                            pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        // else (resmask & CS_CONNECT_A_START) must hold
                        // In this case simply want to skip the segment and 
                        // continue processing, since if the nodecnt==1 and this
                        // condition occured it would have been trapped in the
                        // first if statement above. 
                    }
                    
                    // delete pnxt since if it has been processed
                    if (bProcessed) 
                    {
                        pnxt = RemoveFromList(pfirst, pnxt) ; 
                        continue ; 
                    }
                    else 
                    {
                        int x = 0 ; 
                        x += 1 ; 
                    }
                }
                pnxt = pnxt->next ; 
            }
        } 
        crvset.AddCurve(pcrv) ; 
    }


    // Now see if any of the crvset curves can be connected together. 

    double cmptol = COMPARETOLERANCE ; 
    if (tol)
        cmptol = *tol ; 

    CS_CurveVecItr icset = crvset.crvlist.begin() ;  
    // TO DO - see if we can optimize this instead of looping through over and
    // over again. 
    bool connectedSomething ; 
    do {
        connectedSomething = false ; 

        while (icset != crvset.crvlist.end())
        {
            CS_Curve *pc = *icset ; 
            if (pc->Closed(tol))
            {
                icset++ ; 
                continue ; // skip the closed curves
            }

            CS_POINT sp = pc->StartPoint() ; 
            CS_POINT ep = pc->EndPoint() ; 

            CS_CurveVecItr ics2 = icset ;  
            ics2++ ; // move to next record
            
            bool nextRec = true ; 
            while (ics2 != crvset.crvlist.end())
            {
                CS_Curve *pc2 = *ics2 ; 
                CS_POINT sp2, ep2 ; 
                sp2 = pc2->StartPoint() ; 
                ep2 = pc2->EndPoint() ; 

                // note if any of these if conditions matches then we want to 
                // reprocess the current curve since it may conntect up to something else
                // which is why we set nextRec to false. 
                if (tcomp_PointsEQ(sp.p, sp2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc2->Reverse() ; 
                    pc->InsertCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(sp.p, ep2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc->InsertCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(ep.p, sp2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc->AddCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(ep.p, ep2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc2->Reverse() ; 
                    pc->AddCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }

                ics2++ ; 
            }

            if (nextRec)
                icset++ ; 
        }
    } while (connectedSomething) ; 

    return 0 ; 
}

*/


// Returns bit ORed value of:
// CS_CONNECT_A_START      0x0001
// CS_CONNECT_A_END        0x0002
// CS_CONNECT_B_START      0x0004
// CS_CONNECT_B_END        0x0008

int SegmentsConnected(CS_SegPtr psa, CS_SegPtr psb, double *tol)
{
    int mask ;
    CS_POINT spa, epa, spb, epb ; 

    mask = 0 ; 
    spa = psa->StartPoint() ;
    epa = psa->EndPoint() ; 
    spb = psb->StartPoint() ; 
    epb = psb->EndPoint() ; 

    double cmptol = COMPARETOLERANCE ; 
    if (tol)
        cmptol = *tol ; 

    if (tcomp_PointsEQ(spa.p, spb.p, cmptol)) 
        mask |= CS_CONNECT_A_START | CS_CONNECT_B_START ;
    
    if (tcomp_PointsEQ(spa.p, epb.p, cmptol)) 
        mask |= CS_CONNECT_A_START | CS_CONNECT_B_END ;
    
    if (tcomp_PointsEQ(epa.p, spb.p, cmptol)) 
        mask |= CS_CONNECT_A_END | CS_CONNECT_B_START ; 
    
    if (tcomp_PointsEQ(epa.p, epb.p, cmptol)) 
        mask |= CS_CONNECT_A_END | CS_CONNECT_B_END ;
    
    return mask ; 
}


/*****************************************************************
 *****************************************************************
 ******************  CS_ChainSTK class methods *******************
 *****************************************************************
 *****************************************************************/

CS_ChainSTK::~CS_ChainSTK()
{
    CS_ChainRECListItr icr ; 
    for (icr = creclist.begin(); icr != creclist.end(); icr++)
        delete *icr ; 
}


void CS_ChnCrvRec::Print(FILE *fp)
{
    fprintf(fp, "   stack point: ") ; 
    pcr->crvpnt.Point().Print(fp) ; 
    fprintf(fp, "\n") ; 
    fprintf(fp, "   Counts  fwd=%3d   rev=%3d\n", pcr->fwdwalkcount, pcr->revwalkcount) ; 
    fprintf(fp, "   Tan fwd:  ") ;  pcr->vtanfwd.Print(fp) ; fprintf(fp, "\n") ; 
    fprintf(fp, "   Tan rev:  ") ;  pcr->vtanrev.Print(fp) ; fprintf(fp, "\n") ; 
    fprintf(fp, "   fwd Ang=%6.2f   revAng=%6.2f\n", pcr->fwdang * RADIANStoDEGREES, 
                                                     pcr->revang * RADIANStoDEGREES) ; 
    fprintf(fp, "      status = %x\n", pcr->status) ; 
    fflush(fp) ; 
}


/*****************************************************************
 *****************************************************************
 ******************  CS_Chain class methods *******************
 *****************************************************************
 *****************************************************************/
CS_ChainREC::CS_ChainREC()
{
    crvpnt.s = 0 ;
    crvpnt.u = 0.0 ; 
    ucrv   = 0.0 ; 
    vtanfwd = CS_VECTOR(0,0,0) ; 
    vtanrev = CS_VECTOR(0,0,0) ; 
    fwdwalkcount = 0 ; 
    revwalkcount = 0 ; 
    status = 0 ; 
}


inline CS_ChainREC *CS_NextChainRECNode(CS_ChainREC *pcurnode, int direction)
{
    if (!pcurnode)
        return 0 ; 

    if (direction == CS_FORWARD)
    {
        if (!pcurnode->pcrfwd)
        {
            if (pcurnode->ParentCrv()->Closed())
            {   
                CS_ChnNodeMapItr icnm ; 
                icnm = pcurnode->ParentCrv()->pcnmap->begin() ; 
                pcurnode = icnm->second.pcr ; 
            }
            else
            {
                pcurnode = 0 ; 
            }
        }
        else
        {   // Simply step forward
            pcurnode = pcurnode->pcrfwd ; 
        }
    }
    else
    {   // The section a->b is in reverse
        if (!pcurnode->pcrrev)
        {
            if (pcurnode->ParentCrv()->Closed())
            {   
                CS_ChnNodeMapItr icnm ; 
                icnm = pcurnode->ParentCrv()->pcnmap->end() ; 
                icnm-- ; 
                pcurnode = icnm->second.pcr ; 
            }
            else
            {
                pcurnode = 0 ; // can't go any further
            }
        }
        else
        {   // Simply step backwards
            pcurnode = pcurnode->pcrrev ; 
        }
    }
    return pcurnode ; 
}


CS_ChainREC *CS_Chain::NextChainRECNode(CS_ChainREC *pcurnode)
{
    if (!pcurnode)
    {
        pcurnode = pcrFROM ; // set to the internal current node
    }
    return CS_NextChainRECNode(pcurnode, direction) ; 
}

CS_ChainREC *CS_Chain::AddChainRECToCurve(CS_Curve *pcrv, double ucrv, double epsilon)
{
    TolDbl utd(ucrv) ; 
   
    if (!pcrv->pcnmap)
        pcrv->pcnmap = new CS_ChnNodeMap ; 

    CS_ChnNodeMapItr icnm ; 
    icnm = pcrv->pcnmap->find(utd) ;
    if (icnm == pcrv->pcnmap->end())
    {   // Then add a stack entry to the map
        CS_ChainSTK cstk ;
        cstk.pChain = this ; 

        CS_ChainSTKListItr istk ; 
        cstk.stkpnt = pcrv->UPoint(ucrv) ; 
        
        // Add to stack list
        stklst.push_back(cstk) ; 
        istk = stklst.end() ; 
        istk-- ; // now points to the new stack record

        /////////////////////////////////////
        // Create chain record for curve A //
        /////////////////////////////////////
        CS_ChainREC *pcra = new CS_ChainREC ; 
        pcra->crvpnt = pcrv->UCrvPnt(ucrv) ; 
        pcra->ucrv   = utd.d ; 
        pcra->vtanfwd = pcrv->TanVectorForwards(pcra->crvpnt.s, pcra->crvpnt.u, epsilon) ; 
        pcra->vtanrev = pcrv->TanVectorBackwards(pcra->crvpnt.s, pcra->crvpnt.u, epsilon) ; 
        pcra->vtanrev.Reverse() ; 
        pcra->fwdwalkcount = 0 ; 
        pcra->revwalkcount = 0 ; 
        pcra->status = 0 ; 
        pcra->istk = istk ; 

        pcra->fwdang = 0 ; 
        pcra->revang = 0 ; 


        // Add the chain node to the sorted chain node map for the curve
        CS_ChnNode chnnodeA ;
        chnnodeA.pcr  = pcra ; 
        chnnodeA.ucrv = pcra->ucrv ; 
        chnnodeA.istk = istk ; 
        pair<CS_ChnNodeMapItr, bool> ires ; 
        ires = pcrv->pcnmap->insert(pair<TolDbl, CS_ChnNode>(utd, chnnodeA)) ; 

        CS_ChnNodeMapItr lastnode = pcrv->pcnmap->end() ; 
        if (pcrv->pcnmap->size() > 0)
            lastnode-- ; 

        if (!ires.second)
        {   // Then failed to craete the chaining node entry
            delete pcra ; 
            return 0 ; 
        }
        else
        {   // Hook up the forward and reverse pointers 
            CS_ChnNodeMapItr icnm, icnmnext, icnmprev ; 
            CS_ChainREC *plast = 0 ; 
    
            icnm = ires.first ; 
            
            // Do the previous record first
            icnmprev = icnm ; 
            if (icnm == pcrv->pcnmap->end())
            {   // Then this is the only record
                pcra->pcrfwd = 0 ; 
                pcra->pcrrev = 0 ; 
            }
            else if (icnm != pcrv->pcnmap->begin()) 
            {   // Then there is a previous node
                icnmprev-- ; 
                icnmprev->second.pcr->pcrfwd = pcra ; 
                pcra->pcrrev = icnmprev->second.pcr ;
            }
            else if (pcrv->Closed())
            {   // The previous node is the last node
                icnmprev = lastnode ; 
                icnmprev->second.pcr->pcrfwd = pcra ; 
                pcra->pcrrev = icnmprev->second.pcr ;
            }
            else
            {
                pcra->pcrrev = 0 ;
            }

            // Now hook up the next record
            icnmnext = icnm ; 
            if (icnm == pcrv->pcnmap->end())
            {   // Then this is the only record
                pcra->pcrfwd = 0 ; 
                pcra->pcrrev = 0 ; 
            }
            else if (icnm != lastnode) 
            {   // Then there is a next node
                icnmnext++ ; 
                icnmnext->second.pcr->pcrrev = pcra ; 
                pcra->pcrfwd = icnmnext->second.pcr ;
            }
            else if (pcrv->Closed())
            {   // The previous node is the last node
                icnmnext = pcrv->pcnmap->begin() ; 
                icnmnext->second.pcr->pcrrev = pcra ; 
                pcra->pcrfwd = icnmnext->second.pcr ;
            }
            else
            {
                pcra->pcrfwd = 0 ;
            }
        }

        // Add the CS_ChainREC to the stack
        istk->creclist.push_back(pcra) ; 
        return pcra ; 
    }
    // else already have a node simply return the record
    return icnm->second.pcr ; 
}

inline static
int UpdateStackNodes(CS_Chain *pchn, 
                     CS_ChainSTKList &stklst, // main chain set
                     CS_IRECListItr &iri,     // intersection record
                     TolDbl &tda,             // ucrv point on curve A  
                     TolDbl &tdb,             // ucrv point on curve B
                     int idx,                 // 0=start intersect, 1=end intersect  
                     CS_Curve *pcrvA,         // primary parent curve
                     CS_Curve *pcrvB,         // secondary parent curve
                     CS_ChnNodeMapItr &icna,  // primary CS_ChnNde pointer
                     CS_ChnNodeMapItr &icnb)  // secondary CS_ChnNde pointer
{ 
    if (icna == pcrvA->pcnmap->end() && icnb == pcrvB->pcnmap->end())
    {   // Then craete a whole new stack for this location
        // Later if duplicate stacks are detected, they are merged. 

        ///////////////////////
        // Create Stack Node //
        ///////////////////////
        CS_ChainSTK cstk ;
        cstk.pChain = pchn ;

        CS_ChainSTKListItr istk ; 
        cstk.stkpnt = iri->pir->ipnt[idx] ; 
        
        // Add to stack list
        stklst.push_back(cstk) ; 
        istk = stklst.end() ; 
        istk-- ; // now points to the new stack record

        /////////////////////////////////////
        // Create chain record for curve A //
        /////////////////////////////////////
        CS_ChainREC *pcra = new CS_ChainREC ; 
        pcra->crvpnt = iri->pir->cpp[idx] ; 
        pcra->ucrv   = tda.d ; 
        if (pchn->prcmode & CS_Chain::PRCMODE_EXACT)
        {
            pcra->vtanfwd = pcrvA->TanVectorForwardsExact(pcra->crvpnt.s, pcra->crvpnt.u) ; 
            pcra->vtanrev = pcrvA->TanVectorBackwardsExact(pcra->crvpnt.s, pcra->crvpnt.u) ; 
        }
        else
        {
            pcra->vtanfwd = pcrvA->TanVectorForwards(pcra->crvpnt.s, pcra->crvpnt.u, pchn->chntol) ; 
            pcra->vtanrev = pcrvA->TanVectorBackwards(pcra->crvpnt.s, pcra->crvpnt.u, pchn->chntol) ; 
        }
        pcra->vtanrev.Reverse() ; 
        pcra->fwdwalkcount = 0 ; 
        pcra->revwalkcount = 0 ; 

        pcra->fwdang = 0 ; 
        pcra->revang = 0 ; 

        if (idx == 0)
        {
            if (iri->Status() & CS_IREC::OVERLAP)
                pcra->origstatus = CS_ChainREC::OVRLAPSTART ; 
            else
                pcra->origstatus = 0 ; 
        }
        else
        {
            if (iri->Status() & CS_IREC::OVERLAP)
                pcra->origstatus = CS_ChainREC::OVRLAPEND ; 
            else
                pcra->origstatus = 0 ; 
        }
        pcra->status = 0 ; 
        pcra->istk = istk ; 

        // Add the chain node to the sorted chain node map for the curve
        CS_ChnNode chnnodeA ;
        chnnodeA.pcr  = pcra ; 
        chnnodeA.ucrv = pcra->ucrv ; 
        chnnodeA.istk = istk ; 

        pair<CS_ChnNodeMapItr, bool> ires ; 
        ires = pcrvA->pcnmap->insert(pair<TolDbl, CS_ChnNode>(tda, chnnodeA)) ; 
        if (!ires.second)
        {   // Then failed to create the chaining node entry
            delete pcra ; 
            return -1 ; 
        }
        icna = ires.first ; 

        // Add the CS_ChainREC to the stack
        istk->creclist.push_back(pcra) ; 

        /////////////////////////////////////
        // Create chain record for curve B //
        /////////////////////////////////////
        CS_ChainREC *pcrb = new CS_ChainREC ; 
        pcrb->crvpnt = iri->pir->cps[idx] ; 
        pcrb->ucrv   = tdb.d ; 

        if (pchn->prcmode & CS_Chain::PRCMODE_EXACT)
        {
            pcrb->vtanfwd = pcrvB->TanVectorForwardsExact(pcrb->crvpnt.s, pcrb->crvpnt.u) ; 
            pcrb->vtanrev = pcrvB->TanVectorBackwardsExact(pcrb->crvpnt.s, pcrb->crvpnt.u) ; 
        }
        else
        {
            pcrb->vtanfwd = pcrvB->TanVectorForwards(pcrb->crvpnt.s, pcrb->crvpnt.u, pchn->chntol) ; 
            pcrb->vtanrev = pcrvB->TanVectorBackwards(pcrb->crvpnt.s, pcrb->crvpnt.u, pchn->chntol) ; 
        }
        pcrb->vtanrev.Reverse() ; 
        pcrb->fwdwalkcount = 0 ; 
        pcrb->revwalkcount = 0 ; 


        if (idx == 0)
        {
            if (iri->Status() & CS_IREC::OVERLAP)
            {   // We are on the secondary section. 
                pcrb->origstatus = iri->pir->statinfo & CS_IREC::BREVERSED ? 
                            CS_ChainREC::OVRLAPEND : CS_ChainREC::OVRLAPSTART ; 
            }
            else
            {
                pcrb->origstatus = 0 ; 
            }
        }
        else
        {   // This is the [1] index of the secondary intersection. 
            if (iri->Status() & CS_IREC::OVERLAP)
            {   
                pcrb->origstatus = iri->pir->statinfo & CS_IREC::BREVERSED ? 
                            CS_ChainREC::OVRLAPSTART : CS_ChainREC::OVRLAPEND  ; 
            }
            else
            {
                pcrb->origstatus = 0 ; 
            }
        }

        pcrb->status = 0 ; 
        pcrb->istk = istk ; 

        pcrb->fwdang = 0 ; 
        pcrb->revang = 0 ; 

        // Add the chain node to the sorted chain node map for the curve
        CS_ChnNode chnnodeB ;
        chnnodeB.pcr  = pcrb ; 
        chnnodeB.ucrv = pcrb->ucrv ; 
        chnnodeB.istk = istk ; 
        ires = pcrvB->pcnmap->insert(pair<TolDbl, CS_ChnNode>(tdb, chnnodeB)) ; 
        if (!ires.second)
        {   // Then failed to craete the chaining node entry
            delete pcrb ; 
            return -1 ; 
        }
        icnb = ires.first ; 

        // Add the CS_ChainREC to the stack
        istk->creclist.push_back(pcrb) ; 
    }
    else if (icna == pcrvA->pcnmap->end())
    {   // Then the B record exists, so grab the stack from the 
        // B record and add the A info to the stack and the A curve

        ////////////////////
        // Get Stack Node //
        ////////////////////
        CS_ChainSTKListItr istk ; 
        istk = icnb->second.istk ; 
        
        /////////////////////////////////////
        // Create chain record for curve A //
        /////////////////////////////////////
        CS_ChainREC *pcra = new CS_ChainREC ; 
        pcra->crvpnt = iri->pir->cpp[idx] ;  
        pcra->ucrv   = tda.d ; 
        if (pchn->prcmode & CS_Chain::PRCMODE_EXACT)
        {
            pcra->vtanfwd = pcrvA->TanVectorForwardsExact(pcra->crvpnt.s, pcra->crvpnt.u) ; 
            pcra->vtanrev = pcrvA->TanVectorBackwardsExact(pcra->crvpnt.s, pcra->crvpnt.u) ; 
        }
        else
        {
            pcra->vtanfwd = pcrvA->TanVectorForwards(pcra->crvpnt.s, pcra->crvpnt.u, pchn->chntol) ; 
            pcra->vtanrev = pcrvA->TanVectorBackwards(pcra->crvpnt.s, pcra->crvpnt.u, pchn->chntol) ; 
        }
        pcra->vtanrev.Reverse() ; 
        pcra->fwdwalkcount = 0 ; 
        pcra->revwalkcount = 0 ; 

        if (idx == 0)
        {
            if (iri->Status() & CS_IREC::OVERLAP)
                pcra->origstatus = CS_ChainREC::OVRLAPSTART ; 
            else
                pcra->origstatus = 0 ; 
        }
        else
        {
            if (iri->Status() & CS_IREC::OVERLAP)
                pcra->origstatus = CS_ChainREC::OVRLAPEND ; 
            else
                pcra->origstatus = 0 ; 
        }

        pcra->status = 0 ; 
        pcra->istk = istk ; 

        pcra->fwdang = 0 ; 
        pcra->revang = 0 ; 

        // Add the chain node to the sorted chain node map for the curve
        CS_ChnNode chnnodeA ;
        chnnodeA.pcr  = pcra ; 
        chnnodeA.ucrv = pcra->ucrv ; 
        chnnodeA.istk = istk ; 
        pair<CS_ChnNodeMapItr, bool> ires ; 
        ires = pcrvA->pcnmap->insert(pair<TolDbl, CS_ChnNode>(tda, chnnodeA)) ; 
        if (!ires.second)
        {   // Then failed to craete the chaining node entry
            delete pcra ; 
            return -1 ; 
        }
        icna = ires .first ;

        // Add the CS_ChainREC to the stack
        istk->creclist.push_back(pcra) ; 
    }
    else if (icnb == pcrvB->pcnmap->end())
    {   // Then the A record exists, so grab the stack from the 
        // A record and add the B info to the stack and the B curve

        ////////////////////
        // Get Stack Node //
        ////////////////////
        CS_ChainSTKListItr istk ; 
        istk = icna->second.istk ; 
        
        /////////////////////////////////////
        // Create chain record for curve B //
        /////////////////////////////////////
        CS_ChainREC *pcrb = new CS_ChainREC ; 
        pcrb->crvpnt = iri->pir->cps[idx] ; 
        pcrb->ucrv   = tdb.d ; 
        if (pchn->prcmode & CS_Chain::PRCMODE_EXACT)
        {
            pcrb->vtanfwd = pcrvB->TanVectorForwardsExact(pcrb->crvpnt.s, pcrb->crvpnt.u) ; 
            pcrb->vtanrev = pcrvB->TanVectorBackwardsExact(pcrb->crvpnt.s, pcrb->crvpnt.u) ; 
        }
        else
        {
            pcrb->vtanfwd = pcrvB->TanVectorForwards(pcrb->crvpnt.s, pcrb->crvpnt.u, pchn->chntol) ; 
            pcrb->vtanrev = pcrvB->TanVectorBackwards(pcrb->crvpnt.s, pcrb->crvpnt.u, pchn->chntol) ; 
        }
        pcrb->vtanrev.Reverse() ; 
        pcrb->fwdwalkcount = 0 ; 
        pcrb->revwalkcount = 0 ; 

        if (idx == 0)
        {
            if (iri->Status() & CS_IREC::OVERLAP)
            {   // We are on the secondary section. 
                pcrb->origstatus = iri->pir->statinfo & CS_IREC::BREVERSED ? 
                            CS_ChainREC::OVRLAPEND : CS_ChainREC::OVRLAPSTART ; 
            }
            else
            {
                pcrb->origstatus = 0 ; 
            }
        }
        else
        {   // This is the [1] index of the secondary intersection. 
            if (iri->Status() & CS_IREC::OVERLAP)
            {   
                pcrb->origstatus = iri->pir->statinfo & CS_IREC::BREVERSED ? 
                            CS_ChainREC::OVRLAPSTART : CS_ChainREC::OVRLAPEND  ; 
            }
            else
            {
                pcrb->origstatus = 0 ; 
            }
        }

        pcrb->status = 0 ;
        pcrb->istk = istk ;

        pcrb->fwdang = 0 ;
        pcrb->revang = 0 ;

        // Add the chain node to the sorted chain node map for the curve
        CS_ChnNode chnnodeB ;
        chnnodeB.pcr  = pcrb ;
        chnnodeB.ucrv = pcrb->ucrv ;
        chnnodeB.istk = istk ;
        pair<CS_ChnNodeMapItr, bool> ires ;
        ires = pcrvB->pcnmap->insert(pair<TolDbl, CS_ChnNode>(tdb, chnnodeB)) ;
        if (!ires.second)
        {   // Then failed to craete the chaining node entry
            delete pcrb ;
            return -1 ;
        }
        icnb = ires.first ;

        // Add the CS_ChainREC to the stack
        istk->creclist.push_back(pcrb) ;
    }
    else if (icna->second.istk != icnb->second.istk)
    {   // Since both curves already have chain nodes defined for this 
        // intersection point, we have to merge the two stacks when 
        // the two curves reference different stacks.

        // Use the A stack
        CS_ChainSTKListItr istka = icna->second.istk ; 
        CS_ChainSTKListItr istkb = icnb->second.istk ; 
        
        // Set all the B stack info to refer to the A stack now
        CS_ChainRECListItr icrl ;
        for(icrl = istkb->creclist.begin(); icrl != istkb->creclist.end(); icrl++)
        {   // Only thing required is to repoint the istk pointer
            (*icrl)->istk = istka ; 
        }

        // Now update the chain node
        icnb->second.istk = istka ; 

        // Delete the duplicate stack that we don't need any more
        stklst.erase(istkb) ; 
    }
    else
    {   // We already have an intersection chaining record at this stack node. 
        // When these chain records are built, at nodes with overlap intersections
        // there will be multiple intersection records that occur at the same node
        // and if the non-overlap type intersection occurs first, then the OVERLAP
        // status will not be set correctly for the node. Thus we need to check if
        // this is an overlap intersection, and if it is, then update the 
        // origstatus variable. Note: if a node is an overlap start or end section
        // then once set it should never be unset. 

        CS_ChainREC *pcra = icna->second.pcr ; 
        CS_ChainREC *pcrb = icnb->second.pcr ; 

        if (idx == 0 && (iri->Status() & CS_IREC::OVERLAP))
        {
            pcra->origstatus |= CS_ChainREC::OVRLAPSTART ; 
            if (iri->Status() & CS_IREC::BREVERSED)
                pcrb->origstatus |= CS_ChainREC::OVRLAPEND ; 
            else
                pcrb->origstatus |= CS_ChainREC::OVRLAPSTART  ; 
        }
        else if (idx == 1 && (iri->Status() & CS_IREC::OVERLAP))
        {
            pcra->origstatus |= CS_ChainREC::OVRLAPEND ; 
            if (iri->Status() & CS_IREC::BREVERSED)
                pcrb->origstatus |= CS_ChainREC::OVRLAPSTART ; 
            else
                pcrb->origstatus |= CS_ChainREC::OVRLAPEND  ; 
        }
    }
    // else the two stacks are the same so there's nothing to do
    return 0 ; 
}

int CS_Chain::AddIntersectDataToCurves(CS_IRECList &isset)
{
    CS_Curve *pcrvA, *pcrvB ; 
    
    // pair<map<TolDbl, CS_ChnNode>::iterator, bool> res ;
    pair<CS_ChnNodeMapItr, bool> res ;
    CS_ChnNodeMapItr icnm ; 

    CS_IRECListItr iri ; 

    for (iri = isset.begin(); iri != isset.end(); iri++)
    {   // Create the A segment (primary) entry first

        CS_DEBUG( 
            fprintf(fpDebugOut, " Adding isect:\n") ; 
            iri->pir->Print(fpDebugOut) ; 
            fprintf(fpDebugOut, "    -----------\n") ; 
        ) ; 

        pcrvA = iri->pir->cpp[0].s->pParent ; 
        pcrvB = iri->pir->cps[0].s->pParent ; 

        CS_ChnNodeMapItr icna, icnb ; 
        TolDbl tda(iri->pir->UP0()) ; 
        TolDbl tdb(iri->pir->US0()) ; 

        if ((pcrvA->statflags & CS_CLOSEDCURVE) && tcomp_EQ(tda.d, 1.0))
        {   // Then map it back to the start
            tda.d = 0.0 ; 
        }

        if ((pcrvB->statflags & CS_CLOSEDCURVE) && tcomp_EQ(tdb.d, 1.0))
        {   // Then map it back to the start
            tdb.d = 0.0 ; 
        }

        if (!pcrvA->pcnmap)
            pcrvA->pcnmap = new CS_ChnNodeMap ; 

        if (!pcrvB->pcnmap)
            pcrvB->pcnmap = new CS_ChnNodeMap ; 

        icna = pcrvA->pcnmap->find(tda) ; 
        icnb = pcrvB->pcnmap->find(tdb) ; 
        
        UpdateStackNodes(this, stklst, iri, tda, tdb, 0, pcrvA, pcrvB, icna, icnb) ;  

        // Now deal with overlap records if requried
        if (iri->pir->statinfo & CS_IREC::OVERLAP)
        {
            // With overlap curves there are two intersections, one at the start of
            // the overlap and one at the end. The start and end are w.r.t. the primary
            // curve when the intersection is performed. 

            tda.d = iri->pir->UP1() ; 
            tdb.d = iri->pir->US1() ; 

            if ((pcrvA->statflags & CS_CLOSEDCURVE) && tcomp_EQ(tda.d, 1.0))
            {   // Then map it back to the start
                tda.d = 0.0 ; 
            }

            if ((pcrvB->statflags & CS_CLOSEDCURVE) && tcomp_EQ(tdb.d, 1.0))
            {   // Then map it back to the start
                tdb.d = 0.0 ; 
            }

            icna = pcrvA->pcnmap->find(tda) ; 
            icnb = pcrvB->pcnmap->find(tdb) ; 

            UpdateStackNodes(this, stklst, iri, tda, tdb, 1, pcrvA, pcrvB, icna, icnb) ;  
        }
    }
    return (int)stklst.size() ; 
}


int CS_Chain::SetFwdRevPointers(CS_Curve *pcrv)
{
    if (!pcrv->pcnmap)
        return -1 ; // no intersections with this curve most likely so nothing to do. 

    CS_ChnNodeMapItr icnm, icnmnext ; 
    CS_ChainREC *plast = 0 ; 
    
    icnm = pcrv->pcnmap->begin();
    while( icnm != pcrv->pcnmap->end())
    {
        icnm->second.pcr->status = 0 ; // initialize 

        icnmnext = icnm ; 
        icnmnext++ ;
        icnm->second.pcr->pcrrev = plast ; 
        if (icnmnext != pcrv->pcnmap->end())
        {
            icnm->second.pcr->pcrfwd = icnmnext->second.pcr ; 
            icnmnext->second.pcr->pcrrev = icnm->second.pcr ; 
            plast = icnm->second.pcr ;
        }
        else
        {
            icnm->second.pcr->pcrfwd = 0 ; // end of the list
        }
        icnm = icnmnext ; 
    }

    return 0 ; 
}

int CS_Chain::SetAllFwdMidPoints()
{
    CS_ChnNodeMapItr icnm, icnmnext ; 
    double ua, ub ; 
    
    CS_ChainSTKListItr ics ; 
    for (ics = stklst.begin(); ics != stklst.end(); ics++)
    {
        CS_ChainRECListItr icr ; 
        for (icr = ics->creclist.begin(); icr != ics->creclist.end(); icr++)
        {
            CS_ChainREC *pcr = *icr ; 
            ua = pcr->ucrv ; 
            CS_ChainREC *pcrnext = CS_NextChainRECNode(pcr, CS_FORWARD) ; 
            if (!pcrnext)
            {   // This is an error, show flag user, simply use ua as ub value
                ub = ua ; 
            }
            else
            {   // We have the next point in the chain. 
                ub = pcrnext->ucrv ; 
            
            }
            CS_Curve *pc = pcr->crvpnt.s->pParent ; 
            double umid = pc->UMid(ua, ub) ;
            pcr->pntFwdMid = pc->UPoint(umid) ; 
            pcr->bIsInside = false ; 
            pcr->statPntFwd = 0 ; 

            for (int i=0; i < (int)chncrvs.size(); i++)
            {
                if (chncrvs[i] == pc)
                    continue ; // skip self

                // Only set inside if not on the curve. 
                double u; 
                CS_CrvPnt cp ; 
                if (chncrvs[i]->PointOnCurve(pcr->pntFwdMid, cp, &u))
                {
                    CS_VECTOR va = pc->UTangent(umid) ; 
                    CS_VECTOR vb = cp.s->UTangent(cp.u) ; 
                    double dp = CS_DotProduct(va, vb) ;
                    if (tcomp_EQ(dp, -1))
                        pcr->statPntFwd |= CS_ChainREC::PNTFWD_ONREV ; 
                    else
                        pcr->statPntFwd |= CS_ChainREC::PNTFWD_ON ; 
                }
                else if (chncrvs[i]->Inside(pcr->pntFwdMid, 0, 1))
                {
                    pcr->bIsInside = true ; 
                    pcr->statPntFwd |= CS_ChainREC::PNTFWD_INSIDE ;
                }
            }
        }
    }

    return 0 ; 
}


CS_Curve *CS_Chain::ChainCurve(CS_Curve *pbc, double ustart, double uend, 
                                 int mode, CS_ChainCustomCallbackFunc fp) 
{
    // Start the chaining process from the given IntersectData node.
    cbfunc = fp ; 

    if (!mode)
        mode = CS_Chain::LEFT | CS_Chain::FORWARDONLY ; 

    CS_ChainREC *pstartrec = AddChainRECToCurve(pbc, ustart, chntol) ;
    
    if (tcomp_GEQ(uend, 0.0))
    {
        pendCrv = pbc ; 
        uend = uend ; 
    }

    if (ChainLoop(pstartrec, CS_FORWARD, mode))
        BuildChainCurve() ; 
    return pchncrv ; 
}



int CS_Chain::ChainLoop(CS_ChainREC *pcrstart, int dir, int chainmode)
{
    chnmode = chainmode ; 

    int chainCount = -1 ; 
    if (maxSegCount != 0)
        chainCount = maxSegCount ; 

    if (chainDebugSaveCurves)
    {
        fpChainDebugFile = fopen(szChainDebugFileName, "at") ;   
        fprintf(fpChainDebugFile, "#CHAIN SP=") ; 
        CS_ChainREC *pnxt = pcrstart->pcrfwd ; 
        if (!pnxt)
            pnxt = pcrstart->ParentCrv()->pcnmap->begin()->second.pcr ; 
        double u = pcrstart->ParentCrv()->UMid(pcrstart->ucrv, pnxt->ucrv) ; 
        CS_POINT pnt = pcrstart->ParentCrv()->UPoint(u) ; 
        pnt.Print(fpChainDebugFile) ; 
        fprintf(fpChainDebugFile,"\n") ; 
        fclose(fpChainDebugFile) ;                               
    }

    int bMoreSections = 0 ;
    pStartRec = pcrstart ;
    pcrFROM   = pcrstart ; 
    direction = dir ; 
    bool bAbortChain = false ;

    // Reset the chaining records list for new chain.
    chnreclist.clear() ; 


    CS_ChainSTK *pstk = &(*(pStartRec->istk)) ; 
    startchnpnt = pStartRec->istk->StackPnt() ; 

    do {
        CS_ChainREC *pnxtrec = AddChainSection() ; 
        bMoreSections = CalcNextSection(pnxtrec) ;

        CS_DEBUG(
            if (bMoreSections)
            {
                CS_DEBUG(fprintf(fpDebugOut, "more sections....\n")) ; 
            }
            else
            {
                CS_DEBUG(fprintf(fpDebugOut, "No more sections.\n")) ; 
            }
        )

        // TO DO - Add backup and retry capability here:
        //        To do this will require maintaining all chain sections
        //        as a list of CS_ISRInfo record pairs. The pair record
        //        would have to store the FROM-TO CS_ISRInfo record
        //        pointers, and the direction. If the TO pointer is 
        //        NULL then the end section is added (Note: this condition
        //        would only occur if all other possible paths are 
        //        exhausted and we end up at an end - which would also
        //        cause the loop to exit).
        if (bMoreSections
            && (chnmode & FORWARDONLY) && !(chnmode & OPENCURVES)
            && (direction & CS_REVERSE))
        {
            bAbortChain = true ; 
        }

        if (bMoreSections & 0x8000)
            bAbortChain = true ; 

    } while (bMoreSections && !bAbortChain && chainCount--) ; 

    CS_DEBUG(
        if (chainCount == 0)
        {   // This is an infinitie loop trap, since it means we never
            // exited the chain following process.
            fprintf(fpDebugOut, "ERROR: Reached max chain count!!!!!!\n") ; 
        }
    ) 

    if (chnreclist.size() > 0)
    {
        if (!bAbortChain)
            return 1 ; 

        if (chainDebugSaveCurves)
        {
            fpChainDebugFile = fopen(szChainDebugFileName, "at") ;   
            pchncrv = 0 ;
            BuildChainCurve() ; 
            fprintf(fpChainDebugFile, "#ABORTED PARTIAL CURVE\n") ; 
            pchncrv->WriteCurveToFile(fpChainDebugFile) ; 
            fflush(fpChainDebugFile) ; 
            delete pchncrv ; 
            pchncrv = 0 ; 
            fclose(fpChainDebugFile) ;                               
        }

        CS_DEBUG(fprintf(fpDebugOut,"Aborting the chain\n")) ; 
        chnreclist.clear() ; 
        return 2 ; 
    }

    return 0 ; 
}

//! Chain all full curve loops from the base curve 
/**
    This chaining function generates loops until all the segments
    within the base curve have been used at least once in a chained
    curve. All the chaining loops are returned within the curveset
    that is passed in. If the base curve is open, then the start
    of the curve is skipped and not used in generating any loops
    (as this section could not be part of a loop)
 */ 
int CS_Chain::ChainAllLoops(CS_ChnNodeMap *pcnmap, CS_CurveSet &chaincrvs, int chainmode) 
{
    if (pcnmap->size() == 0)
        return -1 ; // nothing to do, need starting point

    if (!chainmode)
        chainmode = CS_Chain::LEFT ; 

    // The loop exit condition is when all Intersection sets have
    // been used at least once in a curve loop, or when we reach 
    // the end of the intersection sets.
    CS_ChnNodeMapItr icnm ; 
    for (icnm = pcnmap->begin(); icnm != pcnmap->end(); icnm++)
    {
        if (icnm->second.pcr->WasWalked(CS_FORWARD) > 0)
            continue ; // then don't have to process this node
        if ((chainmode & STARTINSIDE) && (icnm->second.pcr->bIsInside == false))
            continue ; // then outside so don't start on this section
        if ((chainmode & STARTOUTSIDE) && (icnm->second.pcr->bIsInside == true))
            continue ; // then inside so don't start on this section
        
        // Start the chaining process from this next node
        if (ChainLoop(icnm->second.pcr, CS_FORWARD, chainmode) == 1)
            BuildChainCurve() ; 

        if (pchncrv && pchncrv->nodecnt > 0)
            chaincrvs.AddCurve(pchncrv) ; 
        else if (pchncrv)
            delete pchncrv ;

        pchncrv = 0 ;
    } 

    return 0 ; 
}

CS_Curve *CS_Chain::BuildChainCurve()
{
    CS_Curve *pcrv, *pccpy ;
    CS_ChainREC *prnext ;

    if (pchncrv)
        delete pchncrv ; 
    pchncrv = new CS_Curve ;
    if (!pchncrv)
        return 0 ; // memory error

    CS_ChnCrvRecListItr icrl ; 
    for (icrl = chnreclist.begin(); icrl != chnreclist.end(); icrl++)
    {
        // Get pointer to the curve that we're about to grab a section of
        pcrv = icrl->pcr->crvpnt.s->pParent ; 
        pccpy = 0 ;

        if (icrl->status & CS_ChnCrvRec::FORWARD)
        {   // Moving along the curve in the forward direction
            if (icrl->status & CS_ChnCrvRec::TOEND)
            {   // Then want to add the entire end section of the curve
                pccpy = pcrv->CopySection(icrl->pcr->crvpnt, CS_CrvPnt(pcrv->pEnd, 1.0)) ; 
            }
            else
            {   // Going to the next node
                direction = CS_FORWARD ; 
                prnext = NextChainRECNode(icrl->pcr) ; 
                pccpy = pcrv->CopySection(icrl->pcr->crvpnt, prnext->crvpnt) ; 
            }
        }
        else
        {
            if (icrl->status & CS_ChnCrvRec::TOSTART)
            {   // Then want to add the entire end section of the curve
                pccpy = pcrv->CopySection(icrl->pcr->crvpnt, 
                                          CS_CrvPnt(pcrv->pStart, 0.0), 
                                          CS_REVERSE) ; 
            }
            else
            {   // Going to the next node
                direction = CS_REVERSE ; 
                prnext = NextChainRECNode(icrl->pcr) ; 
                pccpy = pcrv->CopySection(icrl->pcr->crvpnt, prnext->crvpnt, CS_REVERSE) ; 
            }
        }
        if (pccpy)
            pchncrv->AddCurve(pccpy) ; 
    }

    return pchncrv ; 
}

// Based on the pisncur pointer and the direction, the next section
// of curve is added to the chain curve. AddChainSection() and 
// CalcNextSection() are intended to be used together.
// Returns error code if something goes wrong, otherwise returns 0
CS_ChainREC *CS_Chain::AddChainSection()
{
    CS_DEBUG(fprintf(fpDebugOut, "AddChainSection....\n")) ; 

    CS_ChainREC *pcrnxt = NextChainRECNode() ; 
    if (pcrnxt == 0)
    {   // Simply add the end section
        if (direction == CS_FORWARD)
        {
            if (tcomp_NEQ(pcrFROM->ucrv, 1.0))
            {   // Then add the end section of the curve
                pcrFROM->fwdwalkcount++ ; 
                CS_ChnCrvRec ccr ; 
                ccr.pcr = pcrFROM ; 
                ccr.status = CS_ChnCrvRec::FORWARD | CS_ChnCrvRec::TOEND ; 
            
                CS_DEBUG(fprintf(fpDebugOut,"   +++++++++++  Chaining Rec: +++++++++++\n" )) ; 
                CS_DEBUG(ccr.Print(fpDebugOut)) ; 
                CS_DEBUG(fflush(fpDebugOut)) ; 

                chnreclist.push_back(ccr) ; 

                CS_DEBUG(fprintf(fpDebugOut,"       ++++++ End Chaining Rec: ++++++\n" )) ; 
                CS_DEBUG(fflush(fpDebugOut)) ; 

                CS_Curve *parentcrv = pcrFROM->ParentCrv() ;
                lastchnpnt = parentcrv->EndPoint() ;
                lastchnvec = parentcrv->TanVectorBackwards(parentcrv->pEnd, 1.0, chntol) ; 
            }
        }
        else
        {   // The section a->b is in reverse
            if (tcomp_NEZ(pcrFROM->ucrv))
            {   // Then add the end section of the curve
                pcrFROM->revwalkcount++ ; 
                CS_ChnCrvRec ccr ; 
                ccr.pcr = pcrFROM ; 
                ccr.status = CS_ChnCrvRec::REVERSE | CS_ChnCrvRec::TOSTART ; 
                
                CS_DEBUG(fprintf(fpDebugOut,"   +++++++++++  Chaining Rec: +++++++++++\n" )) ; 
                CS_DEBUG(ccr.Print(fpDebugOut)) ; 
                CS_DEBUG(fflush(fpDebugOut)) ; 

                chnreclist.push_back(ccr) ; 

                CS_DEBUG(fprintf(fpDebugOut,"       ++++++ End Chaining Rec: ++++++\n" )) ; 
                CS_DEBUG(fflush(fpDebugOut)) ; 
                
                CS_Curve *parentcrv = pcrFROM->ParentCrv() ;
                lastchnpnt = parentcrv->StartPoint() ;
                lastchnvec = parentcrv->TanVectorBackwards(parentcrv->pStart, 0.0, chntol) ; 
                lastchnvec.Reverse() ; 
            }
        }
    }
    else
    {   // Add the section from {pcrFROM, direction} 
        if (direction == CS_FORWARD)
        {
            pcrFROM->fwdwalkcount++ ; 
            CS_ChnCrvRec ccr ; 
            ccr.pcr = pcrFROM ; 
            ccr.status = CS_ChnCrvRec::FORWARD ; 
            
            CS_DEBUG(fprintf(fpDebugOut,"   +++++++++++  Chaining Rec: +++++++++++\n" )) ; 
            CS_DEBUG(ccr.Print(fpDebugOut)) ; 

            chnreclist.push_back(ccr) ; 

            CS_DEBUG(fprintf(fpDebugOut,"       ++++++ End Chaining Rec: ++++++\n" )) ; 

            lastchnpnt = pcrnxt->istk->StackPnt() ; 
            lastchnvec = 
                pcrnxt->ParentCrv()->TanVectorBackwards(pcrnxt->crvpnt.s, pcrnxt->crvpnt.u, chntol) ; 
        }
        else
        {   // The section a->b is in reverse
            pcrFROM->revwalkcount++ ; 
            CS_ChnCrvRec ccr ; 
            ccr.pcr = pcrFROM ; 
            ccr.status = CS_ChnCrvRec::REVERSE  ; 

            CS_DEBUG(fprintf(fpDebugOut,"   +++++++++++  Chaining Rec: +++++++++++\n" )) ; 
            CS_DEBUG(ccr.Print(fpDebugOut)) ; 

            chnreclist.push_back(ccr) ; 

            CS_DEBUG(fprintf(fpDebugOut,"       ++++++ End Chaining Rec: ++++++\n" )) ; 

            lastchnpnt = pcrnxt->istk->StackPnt() ; 
            lastchnvec = 
                pcrnxt->ParentCrv()->TanVectorForwards(pcrnxt->crvpnt.s, pcrnxt->crvpnt.u, chntol) ; 
            lastchnvec.Reverse() ; 
        }
    }

    CS_DEBUG(fflush(fpDebugOut)) ; 

    return pcrnxt ; 
}


int CS_FindRightChain(CS_ChainSTKListItr &istk, int mode)
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;

    // In Chainright mode we want the smallest angle
    double angpick = RADIAN360 ; 
    CS_ChainRECListItr icrl ;
    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        if (!((mode & CS_Chain::WALKONCE) && (pcr->fwdwalkcount > 0)) && 
                !pcr->FWDAvoid() && tcomp_LT(pcr->fwdang, angpick, istk->pChain->angtol))
        {
            angpick = pcr->fwdang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }

        if (!((mode & CS_Chain::WALKONCE) && (pcr->revwalkcount > 0)) && 
                !pcr->REVAvoid() && tcomp_LT(pcr->revang, angpick, istk->pChain->angtol))
        {
            angpick = pcr->revang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_REVERSE ; 
        }
    }

    if (istk->pcrTO == 0)
    {   // Slack off the requirements

        for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
        {
            CS_ChainREC *pcr = *icrl ;         
            if (!((mode & CS_Chain::WALKONCE) && (pcr->fwdwalkcount > 0)) && 
                    !pcr->FWDBlocked() && tcomp_LT(pcr->fwdang, angpick, istk->pChain->angtol))
            {
                angpick = pcr->fwdang ;
                istk->pcrTO = pcr ; 
                istk->direction = CS_FORWARD ; 
            }

            if (!((mode & CS_Chain::WALKONCE) && (pcr->revwalkcount > 0)) && 
                    !pcr->REVBlocked() && tcomp_LT(pcr->revang, angpick, istk->pChain->angtol))
            {
                angpick = pcr->revang ;
                istk->pcrTO = pcr ; 
                istk->direction = CS_REVERSE ; 
            }
        }
    }
    return 0 ; 
}


int CS_FindTangentChain(CS_ChainSTKListItr &istk, int mode)
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;
    // Want angle closest to zero.
    CS_ChainRECListItr icrl ;
    double angdelta = RADIAN360 ; 
    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        double adtmp = fabs(pcr->fwdang - RADIAN180) ; 
        if (!((mode & CS_Chain::WALKONCE) && pcr->fwdwalkcount > 0) && 
            !pcr->FWDAvoid() && tcomp_LT(adtmp, angdelta, istk->pChain->angtol))
        {
            angdelta = adtmp ; 
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }

        // adtmp = fabs(angles[i*2 + 1] - RADIAN180) ;
        adtmp = fabs(pcr->revang - RADIAN180) ; 
        if (!((mode & CS_Chain::WALKONCE) && pcr->revwalkcount > 0) && 
            !pcr->REVAvoid() && tcomp_LT(adtmp, angdelta, istk->pChain->angtol))
        {
            angdelta = adtmp ; 
            istk->pcrTO = pcr ; 
            istk->direction = CS_REVERSE ; 
        }
    }

    if (istk->pcrTO == 0)
    {   // Slack off the requirements
        for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
        {
            CS_ChainREC *pcr = *icrl ;         
            double adtmp = fabs(pcr->fwdang - RADIAN180) ; 
            if (!((mode & CS_Chain::WALKONCE) && pcr->fwdwalkcount > 0) && 
                !pcr->FWDBlocked() && tcomp_LT(adtmp, angdelta, istk->pChain->angtol))
            {
                angdelta = adtmp ; 
                istk->pcrTO = pcr ; 
                istk->direction = CS_FORWARD ; 
            }

            // adtmp = fabs(angles[i*2 + 1] - RADIAN180) ;
            adtmp = fabs(pcr->revang - RADIAN180) ; 
            if (!((mode & CS_Chain::WALKONCE) && pcr->revwalkcount > 0) && 
                !pcr->REVBlocked() && tcomp_LT(adtmp, angdelta, istk->pChain->angtol))
            {
                angdelta = adtmp ; 
                istk->pcrTO = pcr ; 
                istk->direction = CS_REVERSE ; 
            }
        }
    }
    return 0 ; 
}


int CS_FindLeftChain(CS_ChainSTKListItr &istk, int mode)
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;
    // Looking for largest angle.
    double angpick = -RADIAN360 ; 
    CS_ChainRECListItr icrl ;
    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        if (!((mode & CS_Chain::WALKONCE) && (pcr->fwdwalkcount > 0)) && 
                !pcr->FWDAvoid() && tcomp_GT(pcr->fwdang, angpick, istk->pChain->angtol))
        {
            angpick = pcr->fwdang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }

        if (!((mode & CS_Chain::WALKONCE) && (pcr->revwalkcount > 0)) && 
                !pcr->REVAvoid() && tcomp_GT(pcr->revang, angpick, istk->pChain->angtol))
        {
            angpick = pcr->revang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_REVERSE ; 
        }
    }

    if (istk->pcrTO == 0)
    {   // Slack off the requirements
        for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
        {
            CS_ChainREC *pcr = *icrl ;         
            if (!((mode & CS_Chain::WALKONCE) && (pcr->fwdwalkcount > 0)) && 
                    !pcr->FWDBlocked() && tcomp_GT(pcr->fwdang, angpick, istk->pChain->angtol))
            {
                angpick = pcr->fwdang ;
                istk->pcrTO = pcr ; 
                istk->direction = CS_FORWARD ; 
            }

            if (!((mode & CS_Chain::WALKONCE) && (pcr->revwalkcount > 0)) && 
                    !pcr->REVBlocked() && tcomp_GT(pcr->revang, angpick, istk->pChain->angtol))
            {
                angpick = pcr->revang ;
                istk->pcrTO = pcr ; 
                istk->direction = CS_REVERSE ; 
            }
        }
    }
    return 0 ; 
}



// Works out the next direction to follow while adding sections to 
// the chain curve. The pisncur and the direction variables are set
// properly for the next call to AddChainSection()
// Returns false when there are no more sections to be added, this
// determination is made by checking to see if the chain curve
// has been closed, or if there is no other chain section that 
// can be followed.
// The AVOID/BLOCKED logic was added to allow for the possibility
// that a path that folds back on itself can be taken so long as 
// it is along a different curve than the one that was just walked
// along to for the last chain segment.

int CS_Chain::CalcNextSection(CS_ChainREC *plastrec) 
{

    if (!plastrec || startchnpnt == lastchnpnt)
        return 0 ; 

    lastDirection = direction ; 
    // Now work out where to go from here

    if ((plastrec->ParentCrv() == pendCrv) && tcomp_EQ(plastrec->ucrv, uend))
        return 0 ; 

    // Collect the tangent vectors of all the possible directions
    // that can be followed at the point we're at. To do this must 
    // scan through the list of current nodes for the one that defines
    // the direction to go in next.

    // Allocate a list of turn angles for each of the possible directions
    // that we can take from this point. 
    
    // Simply grab the working stack pointer
    CS_ChainSTKListItr istk = plastrec->istk ; 
    CS_ChainRECListItr icrl ;

    int retval = 0 ; 
    CS_ChainREC *pcr ;
    // Initialize various status bits to control the 'direction following' logic (block various possibilities etc...)
    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        pcr = *icrl ;         
        pcr->fwdang = lastchnvec.TurnAngle(pcr->vtanfwd) ;
        pcr->revang = lastchnvec.TurnAngle(pcr->vtanrev) ;
        pcr->status &= ~(CS_ChainREC::CLEARMASK) ; // reset for now

        // Adjust control status parameters for the current curve
        if (pcr == plastrec)
        {
            if (direction == CS_FORWARD)
            {   // Then block reverse direction on existing curve
                pcr->status |= CS_ChainREC::BLOCKREV ;
                if (!pcr->ParentCrv()->Closed() &&
                        (tcomp_EQ(pcr->ucrv, 1.0) || !NextChainRECNode(pcr)))
                {   // Then disallow the forward direction
                    pcr->status |= CS_ChainREC::BLOCKFWD ;
                }
            }
            else
            {   // Block the forward direction (going back on itself)
                pcr->status |= CS_ChainREC::BLOCKFWD ;
                if (!pcr->ParentCrv()->Closed() &&
                        (tcomp_EQ(pcr->ucrv, 0.0) || !NextChainRECNode(pcr)))
                {   // Then disallow the forward direction
                    pcr->status |= CS_ChainREC::BLOCKREV ;
                }
            }
        }
        else
        {
            if (!(chnmode & ALLOWREVERSALS))
            {
                pcr->SetAngleStats(&revangtol) ; // reset for now
            }

            // Now block any attempts to walk off the end of the
            // complementary curve if it is not closed
            if (!pcr->ParentCrv()->Closed())
            {
                if (tcomp_EQ(pcr->ucrv, 1.0) || !pcr->pcrfwd)
                {   // Then disallow the forward direction
                    pcr->status |= CS_ChainREC::BLOCKFWD ;
                }

                // Test if u=0 point on open curve
                if (tcomp_EQ(pcr->ucrv, 0.0) || !pcr->pcrrev)
                {   // disallow the reverse direction
                    pcr->status |= CS_ChainREC::BLOCKREV ;
                }
            }
        }

        // Finally test for blocked nodes and set the status bit accordingly
        CS_ChainREC *pcrf, *pcrr ;

        pcrf = CS_NextChainRECNode(pcr, CS_FORWARD) ;
        if (pcrf && (pcrf->status & CS_ChainREC::BLOCKED))
        {
            pcr->status |= CS_ChainREC::BLOCKFWD ;
        }

        pcrr = CS_NextChainRECNode(pcr, CS_REVERSE) ;
        if (pcrr && (pcrr->status & CS_ChainREC::BLOCKED))
        {
            pcr->status |= CS_ChainREC::BLOCKREV ;
        }
    }

    // Now based on the mode pick the proper angle
    // Custom call back (if CUSTOM mode is defined) will be passed
    // an array of angles, and the current test point for the prompted case.
    // This is why the array above is created even though it is redundant 
    // for all internally calculated situations (values required can be 
    // genreated on the fly)
    
    int cbretval = 0 ; 
    switch(chnmode & METHODMASK)
    {
    case RIGHT :
        CS_FindRightChain(istk, chnmode) ; 
        break ; 
    case TANGENT :
        CS_FindTangentChain(istk, chnmode) ; 
        break ; 
    case CUSTOM :
        // FROM->TO defines the last section that was added to the chain. 
        // The custom callback needs to modify the istk->pcrTO record as the
        // next node in the chain. 
        istk->pcrTO = plastrec ; 
        istk->pcrFROM = pcrFROM ; 
        istk->direction = lastDirection ; 
        cbretval = cbfunc(istk, chnmode) ; // do callback
        break ; 
    case LEFT :
    default :
        // In Chainleft mode we want the largest angle
        CS_FindLeftChain(istk, chnmode) ; 
        break ; 
    }

    if (istk->pcrTO != 0)
    {   // Then this is the record to follow
        retval = 1 ; 
    }
    else
    {   // No chain that could be followed
        retval = 0 ; 
    }

    pcrFROM = istk->pcrTO ; 
    direction = istk->direction ; 

    if (cbretval & CUSTOMABORT)
        return CUSTOMABORT ; 

    return retval ; 
}


