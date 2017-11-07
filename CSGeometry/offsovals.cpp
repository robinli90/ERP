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
// offsovals.cpp 
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
#include "cs_shapes.h"
#include "cs_curves.h"

#include "cs_offset.h"
#include "cs_offsoval.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)     a ; 
#else
#define CS_DEBUG(a)
#endif



/** 
  Slow offset method, in that it's run time is significantly higher than
  the other method, but is much more reliable. The fast offset routine
  will fail over to this method if no result is generated. (Assuming I 
  can make it work of course)

 */

void QuickSort(void *base, unsigned int num, unsigned int width,
        int (*comp)(const void *, const void *),
        void (*swap)(const void *, const void *)) ;
///////////////////////////////////////////////////////////////
// UParameterPair - member functions
///////////////////////////////////////////////////////////////
// See notes RR-Vol3 pg 5 (Feb 28,2001)
// Return codes { UPARM_MERGE_NONE, UPARM_MERGED, UPARM_FULLRANGE }
// On entry (ua < ub) and (a < b) must both hold
int UParameterPair::MergeRange(UParameterPair *ppy)
{
    int extraStatus = 0 ; 
    status &= ~(CHANGED | MERGED) ; 
    
    if (ppy->ub < ua)
    {   // Case 1
        // note that we are not testing if [ua,ub]==[0,1] here 
        // since we assume that if that were the case then no attempt
        // would be made to merge this range
        if ((ppy->status & UB_ISECT_BASE) || (status & UA_ISECT_BASE))
        {   // Then we want to delete the section in between the two 
            // since it touches the base curve at one or both ends
            ua = ppy->ua ; 
            extraStatus = DELETE_B ;
        }
        // Also since the parameter pairs are sorted by UA values
        // this case should never occur. But the above code is how
        // to deal with it if it does
        return status | extraStatus ;
    }
    
    if (ppy->ua <= ua)
    {   // Case 2 thru 8
        extraStatus = DELETE_B ;
        if (ppy->status & UA_ISECT_BASE)
            status |= UA_ISECT_BASE ;
        if (ppy->ub < ub)
        {   // Case 2,3,6
            ua = ppy->ua ; // this is the only parm that changes
            status |= MERGED | CHANGED ; 
        }
        else if (ppy->ub == ub)
        {   // Case 4,7
            ua = ppy->ua ; // this is the only parm that changes
            status |= MERGED | CHANGED ; 
            if (ppy->status & UB_ISECT_BASE)
                status |= UB_ISECT_BASE ;
        }
        else
        {   // Case 5,8 (b > ub so we set both parameters)
            ua = ppy->ua ; 
            ub = ppy->ub ; 
            status |= MERGED | CHANGED ;
            status &= ~(UA_ISECT_BASE | UB_ISECT_BASE) ;
            status |= ppy->status & (UA_ISECT_BASE | UB_ISECT_BASE) ;
            extraStatus = DELETE_B ;
        }

        if (tcomp_EQZ(ua) && tcomp_EQ(ub, 1.0))
            status |= FULLRANGE ;
        return status | extraStatus ; 
    }

    if (ppy->ua <= ub)
    {   // Case 9 thru 12
        extraStatus = DELETE_B ;
        status |= MERGED ;
        if (ppy->ub > ub)
        {
            ub = ppy->ub ; 
            status &= ~UB_ISECT_BASE ;
            status |= ppy->status & UB_ISECT_BASE ;
            status |= CHANGED ;
            if (tcomp_EQZ(ua) && tcomp_EQ(ub, 1.0))
                status |= FULLRANGE ;
        }
        return status | extraStatus ;
    }
    
    // Finally do case 13
    if ((status & UB_ISECT_BASE) || (ppy->status & UA_ISECT_BASE))
    {   // Then join the two sections
        extraStatus = DELETE_B ;
        ub = ppy->ub ; 
        status &= ~UB_ISECT_BASE ;
        status |= (ppy->status & UB_ISECT_BASE) ; 
        status |= MERGED | CHANGED ;
        return status | extraStatus ; 
    }
        
    return MERGE_NONE ; 
}


static void InsertSortedUPPairList(UParmPairList &clipList, UParameterPair &up)
{
    UParmPairListItr ipp ; 
    for (ipp = clipList.begin() ; ipp != clipList.end(); ipp++)
    {
        if (up < *ipp)
        {
            clipList.insert(ipp, up) ; 
            return ; 
        }
    }

    if (ipp == clipList.end()) 
        clipList.push_back(up) ; 
}


///////////////////////////////////////////////////////////////
// CS_Oval - member functions
///////////////////////////////////////////////////////////////
CS_RECT &CS_Oval::SetBoundingRects() 
{
    // Must initialize the bounding rectangle with something. Since
    // we must always have an offset segment for an oval to be defined
    // start with the offset segments rectangle
    if (!poseg)
        return bndrect ; // nothing to do

    ofsrect = poseg->BoundingRect() ;
    bndrect = ofsrect ; 
    if (!(status & CS_OVAL_PIEWEDGE))
        bndrect.Union(pbseg->BoundingRect()) ; 
    bndrect.Union(arcA.BoundingRect()) ; 
    bndrect.Union(arcB.BoundingRect()) ; 

    ofsrect.Expand(0.02) ; // increase by 1%
    bndrect.Expand(0.02) ; 
    
    return bndrect ; 
}

// Returns true if the point p is inside the oval, should 
// call bounding box tests before the inside test to save time.
// TO DO - need to re-visit the logic here since it is hyper critical to get
// accurate results from this inside test in order for the final chaining to 
// work correctly. 
int CS_Oval::Inside(CS_POINT &p)
{
    if (poseg->SegmentType() == CS_Segment::LINE_TYPE)
    {   // See RR-Vol2 Pg 199 for notes
        CS_LINE lbase(*((CS_LineSeg *)pbseg)) ; 
        CS_LINE loffset(*((CS_LineSeg *)poseg)) ; 
        CS_LINE lQT(pbseg->StartPoint(), poseg->StartPoint()) ; 
        CS_LINE lRS(pbseg->EndPoint(), poseg->EndPoint()) ; 

        if (status & CS_OVAL_LEFTOFFSET)
        {
            if (   (PointSide(lbase,   p) == CS_LEFTSIDE) 
                && (PointSide(loffset, p) == CS_RIGHTSIDE) 
                && (PointSide(lQT,     p) == CS_RIGHTSIDE) 
                && (PointSide(lRS,     p) == CS_LEFTSIDE) )
            {   
                return 1 ; 
            }

            // Now do the arc end tests if required
            CS_VECTOR vap(arcA.ctr, p) ; 
            if (vap.Mag() < arcA.rad)
                return 1 ; 

            CS_VECTOR vbp(arcB.ctr, p) ; 
            if (vbp.Mag() < arcB.rad)
                return 1 ; 

            return 0 ; 
        }
        else
        {   // Test the other case
            if (   (PointSide(lbase,   p) == CS_RIGHTSIDE) 
                && (PointSide(loffset, p) == CS_LEFTSIDE) 
                && (PointSide(lQT,     p) == CS_LEFTSIDE) 
                && (PointSide(lRS,     p) == CS_RIGHTSIDE) )
            {   
                return 1 ; 
            }

            // Now do the arc end tests if required
            CS_VECTOR vap(arcA.ctr, p) ; 
            if (vap.Mag() < arcA.rad)
                return 1 ; 

            CS_VECTOR vbp(arcB.ctr, p) ; 
            if (vbp.Mag() < arcB.rad)
                return 1 ; 

            return 0 ; 
        }
    }
    else // ARC_TYPE
    {   // See RR-Vol3 Pg 1 for notes
        // Can change the order of operations around to optimize 
        // performance. For pie wedges, the rbase==0 condition
        // should cause the arcA and arcB circle tests to be
        // done first, since this will usually be sufficient in these
        // cases (higher probability of getting a hit right off the bat)

        // Dec 30, 2003, 00:38 hours
        // Found a problem with the inside testing for a case with a small segment
        // right next to a large radius flat arced oval
        //   _________________--------------------------___________________ _
        //  (_________________--------------------------___________________)    
        // Due to the tolerance that was used the midpoint of the small segment
        // (the dash on the upper right corner of the oval) actually intersected
        // the top arc (since the midpoint of this line tested as being on the 
        // sweep of the top arc. Thus it was discarded and this resulted in a 
        // small gap in the final output offset curve, which no longer made a 
        // continuous complete loop and thus the offset failed. Note that the 
        // gap was just longer than the minimal gap tolerance that would have 
        // allowed everything to work properly. 
        // So the following change was made. All the AngleOnSweep(...)'s were
        // changed to AngleInSweep(...). This caused other conditions to fail
        // since things that should have been deleted now weren't.
        //
        // Another fix would be to use exact floating point comparisons for the
        // AngleOnSweep(...) test. Could define another function called
        // AngleOnSweepX(...) where the X represents exact floating point 
        // comparisons without the tolerance factor. That's what is done 
        // below but this solution is not ideal since arc tolerance problems
        // can still result. 
        //                    

        // Update Feb 3, 2007. More of the same problem with almost tangent
        // arcs and lines this time. This could also happen (I think) with
        // two almost tangent line segments where an arc gets inserted into
        // the set of offset curves. The problem with endpoint testing of 
        // arcs is a serious problem. Need to convert to a spline type 
        // representation for the arcs which will give clearly defined end
        // points. For now the solution is to drastically back off on the 
        // tolerance requirements whenever comparing arc endpoints for 
        // connectivity. This was handled in the AddSegmentToChain(..)
        // function. This is not an ideal fix, but makes this much more 
        // robust for now. 

        double rbase, roffs, vcpm ; 
        CS_VECTOR vcp(((CS_ArcSeg *)poseg)->ctr, p) ; 

        if (status & CS_OVAL_PIEWEDGE)
            rbase = 0.0 ; 
        else
            rbase = ((CS_ArcSeg *)pbseg)->rad ; 
        roffs = ((CS_ArcSeg *)poseg)->rad ;
        vcpm = vcp.Mag() ;

        if (status & CS_OVAL_LEFTOFFSET)
        {   // Cases 1,2
            if (((CS_ArcSeg *)poseg)->swp > 0)
            {   // Arc CCW - left offset => move arc in
                // Case 2
                if ((roffs < vcpm) && (vcpm < rbase) &&
                    ((CS_ArcSeg *)poseg)->AngleOnSweepX(vcp.AngleXY()))
                {
                    return 1 ; 
                }
            }
            else
            {   // Arc CW - left offset => move arc out
                // Case 1  (possible pie wedge case)
                if ((rbase < vcpm) && (vcpm < roffs) &&
                    ((CS_ArcSeg *)poseg)->AngleOnSweepX(vcp.AngleXY()))
                {
                    return 1 ; 
                }
            }

            // Now do the arc end tests if required
            CS_VECTOR vap(arcA.ctr, p) ; 
            if (vap.Mag() < arcA.rad)
                return 1 ; 

            CS_VECTOR vbp(arcB.ctr, p) ; 
            if (vbp.Mag() < arcB.rad)
                return 1 ; 

            return 0 ; 
        }
        else
        {   // Cases 3,4 (Right offset)
            if (((CS_ArcSeg *)poseg)->swp < 0)
            {   // Arc CW - left offset => move arc in
                // Case 3
                if ((roffs < vcpm) && (vcpm < rbase) &&
                    ((CS_ArcSeg *)poseg)->AngleOnSweepX(vcp.AngleXY()))
                {
                    return 1 ; 
                }
            }
            else
            {   // Arc CCW - left offset => move arc out
                // Case 4  (possible pie wedge case)
                if ((rbase < vcpm) && (vcpm < roffs) &&
                    ((CS_ArcSeg *)poseg)->AngleOnSweepX(vcp.AngleXY()))
                {
                    return 1 ; 
                }
            }

            // Now do the arc end tests if required
            CS_VECTOR vap(arcA.ctr, p) ; 
            if (vap.Mag() < arcA.rad)
                return 1 ; 

            CS_VECTOR vbp(arcB.ctr, p) ; 
            if (vbp.Mag() < arcB.rad)
                return 1 ; 

            return 0 ; 
        }
    }
    return 0 ; 
}


int __cdecl doublecompare(const void *a, const void *b ) 
{
    if ( *(double *)a < *(double *)b)
        return -1 ; 
    else if (*(double *)a > *(double *)b)
        return 1 ; 
    return 0 ;
}


struct UIParmVals
{
    double u ; 
    int ib ; // set true if this u point intersects the base curve
    // of the oval that generated the intersection.
} ;

int CS_Oval::AddToClipList(CS_Oval *poval)
{
    CS_IRECList isset ;

    // Intersect the offset segment with all curves in the oval
    poseg->Intersect2D(poval->poseg, &isset) ; 
    if (!(poval->status & CS_OVAL_PIEWEDGE))
        poseg->Intersect2D(poval->pbseg, &isset) ; 
    poseg->Intersect2D(&poval->arcA, &isset) ; 
    poseg->Intersect2D(&poval->arcB, &isset) ; 

    // Work out all the u values on the this->poseg curve
    // and define overlaps as ranges that need to be deleted
    if (isset.size() > 0)
    {
        assert(isset.size() < 15) ;

        // Note: the maximum number of intersections we should 
        // ever get from an oval is 8 (and even this is highly 
        // unlikely. Thus simply allocate a fixed memory block
        // off the stack to speed things up.
        UIParmVals pui[20] ; 
        UIParmVals *ui ; // used to manipulate array contents
        bool bAppendUVal ; 

        CS_IRECListItr iri ; 
        int uilen = 0 ; 
        register int i, j ; 

        // Leave the first entry empty so that we can fill in 
        // the 0.0 entry if it isn't already in the list.
        // We'll also add the 1.0 entry to then end if it doesn't
        // exist
        ui = pui + 1 ;  

        for (iri = isset.begin() ; iri != isset.end(); iri++)
        {
            if (iri->pir->statinfo & CS_IREC::OVERLAP)
            {   // Automatically add overlap ranges to the clipping list
                UParameterPair upp(iri->pir->cpp[0].u, iri->pir->cpp[1].u) ; 
                upp.status |= UParameterPair::OVERLAP ; 
                InsertSortedUPPairList(clipList, upp) ;
            }
            else
            {   // Insert it into the event point list
                // and eliminate duplicate values at the same time
                bAppendUVal = true ; 
                for (i=0; i < uilen; i++)
                {
                    if (tcomp_LT(iri->pir->cpp[0].u, ui[i].u))
                    {   // Insert into the list and exit loop
                        for (j=uilen; j > i; j--)
                            ui[j] = ui[j-1] ; 
                        ui[i].u  = iri->pir->cpp[0].u ;
                        if (iri->pir->cps[0].s == poval->pbseg) 
                            ui[i].ib = 1 ;
                        else 
                            ui[i].ib = 0 ; 
                        uilen++ ; 
                        bAppendUVal = false ; 
                        break ; 
                    }
                    else if (tcomp_EQ(iri->pir->cpp[0].u, ui[i].u))
                    {   // Already dealt with
                        bAppendUVal = false ; 
                        break ; 
                    }
                }

                // If we get to here and append is still true then 
                // it was greater than all the entries in the list, 
                // and it wasn't equal to any entry in the list.
                if (bAppendUVal)
                {
                    ui[uilen].u = iri->pir->cpp[0].u ;
                    if (iri->pir->cps[0].s == poval->pbseg) 
                        ui[uilen].ib = 1 ;
                    else 
                        ui[uilen].ib = 0 ; 
                    uilen++ ; 
                }
            }
        }

        // Make sure we have the 0,1 end points included in the key points
        if (tcomp_NEZ(ui[0].u))
        {   // 0 point doesn't exist, so add and adjust array 
            pui[0].u = 0.0 ; 
            pui[0].ib = 0 ; 
            ui = pui ; 
            uilen++ ; 
        }

        if (tcomp_NEQ(ui[uilen-1].u, 1.0))
        {   // 1 doesn't exist, add to end of array
            ui[uilen].u = 1.0 ; 
            ui[uilen].ib = 0 ; 
            uilen++ ; 
        }

        
        // Now test around the key points whether the section is inside
        // or outside poval

        // Here we want to test the midpoint between pairs of key
        // points. Midpoints that are inside the oval are added to 
        // the oval clipping list, so that these sections are 
        // effectively marked as deleted for the final segment
        // stitching phase later.
        // Dec 30, 2003, 01:07 hours, Added logic here when the range is [0,1] 
        // only since in this case we may have had an end point intersect with the
        // oval even though the curve segment is not inside the oval. This is 
        // especially critical when the curve segment being tested is extremely short
        // since there was a condition where the midpoint actually tested as being
        // inside the oval when in fact it wasn't (error caused by tolerance limits
        // with large flat arcs making up the long sides of the oval). 
        if (uilen == 2 && tcomp_EQZ(ui[0].u) && tcomp_EQ(ui[1].u, 1.0))
        {   // Do special case testing
            if (poval->Inside(poseg->UPoint(0.95)))
            {
                if (poval->Inside(poseg->UPoint(0.05)))
                {   // Then both ends test as being inside so add it to 
                    // the clip list. 
                    UParameterPair upp(ui[0].u, ui[1].u) ;
                    if (ui[0].ib)
                        upp.status |= UParameterPair::UA_ISECT_BASE ; 
                    if (ui[1].ib)
                        upp.status |= UParameterPair::UB_ISECT_BASE ; 
                
                    InsertSortedUPPairList(clipList, upp) ;
                }
            }
        }
        else
        {   // Do Normal testing
            for (i=0; i < uilen - 1 ; i++)
            {
                if (poval->Inside(poseg->UPoint((ui[i].u + ui[i+1].u) / 2.0)))
                {
                    UParameterPair upp(ui[i].u, ui[i+1].u) ;
                    if (ui[i].ib)
                        upp.status |= UParameterPair::UA_ISECT_BASE ; 
                    if (ui[i+1].ib)
                        upp.status |= UParameterPair::UB_ISECT_BASE ; 
                
                    InsertSortedUPPairList(clipList, upp) ;
                }
            }
        }
    }
    else
    {   // Check if entire segment is inside the oval 
        if (poval->Inside(poseg->MidPoint()))
        {   // Then we are deleting the entire segment
            if (clipList.size() > 0)
                clipList.clear() ; 
            UParameterPair upp(0, 1) ;
            upp.status |= UParameterPair::FULLRANGE ;
            clipList.push_back(upp) ; 
            status |= CS_OVAL_CLIPPEDALL ; 
        }
        // else do nothing since the segment was completely 
        // outside the test oval
    }

    return 0 ; 
}




///////////////////////////////////////////////////////////////
// Oval offset functions
///////////////////////////////////////////////////////////////
static void AddStdOval(CS_OvalList &ovalList,
                       CS_SegPtr pbase, 
                       CS_SegPtr poffs, 
                       double &delta) 
{
    CS_Oval ovalrec ;         
    CS_POINT sp, ep, ccsp, ccep ; 
    CS_VECTOR vccs, vcce ; 

    // Check for and skip inverted arc condition
    if (poffs->SegmentType() == CS_Segment::ARC_TYPE)
    {
        if ((poffs->info & CRV_ARCCONVEX) || 
             tcomp_EQZ( ((CS_ArcSeg *)poffs)->rad ))
        {   // inverted arc, do not add
            return ; 
        }
    }

    ovalrec.status = 0 ; 

    if (delta < 0)
        ovalrec.status |= CS_OVAL_LEFTOFFSET ;
    else
        ovalrec.status |= CS_OVAL_RIGHTOFFSET ;


    sp = pbase->StartPoint() ; 
    ep = pbase->EndPoint() ; 

    ccsp = CS_LineSeg(sp, poffs->StartPoint()).MidPoint() ; 
    ccep = CS_LineSeg(ep, poffs->EndPoint()).MidPoint() ; 

    vccs = CS_VECTOR(ccsp, sp) ; 
    vcce = CS_VECTOR(ccep, ep) ; 

    ovalrec.pbseg = pbase ; // base segment pointer
    ovalrec.poseg = poffs->Copy() ; 

    ovalrec.arcA.ctr = ccsp ;
    ovalrec.arcA.rad = fabs(delta / 2.0) ;
    ovalrec.arcB.ctr = ccep ;
    ovalrec.arcB.rad = fabs(delta / 2.0) ;

    vccs.Reverse() ; 
    ovalrec.arcA.sa = vccs.AngleXY() ;
    ovalrec.arcB.sa = vcce.AngleXY() ;

    if (delta < 0)
    {   // Offset left
        ovalrec.arcA.swp = RADIAN180 ; 
        ovalrec.arcB.swp = RADIAN180 ; 
    }
    else
    {   // Offset right
        ovalrec.arcA.swp = -RADIAN180 ; 
        ovalrec.arcB.swp = -RADIAN180 ; 
    }

    ovalList.push_back(ovalrec) ; 
    ovalrec.poseg = 0 ; // make sure destructor leaves pointer alone
}


static void AddPieOval(CS_OvalList &ovalList,
                       CS_SegPtr pbase, 
                       CS_SegPtr poffs, 
                       double &delta) 
{
    CS_Oval ovalrec ;         
    CS_POINT sp, ep, ccsp, ccep ; 
    CS_VECTOR vccs, vcce ; 

    ovalrec.status = CS_OVAL_PIEWEDGE ; 

    if (delta < 0)
        ovalrec.status |= CS_OVAL_LEFTOFFSET ;
    else
        ovalrec.status |= CS_OVAL_RIGHTOFFSET ;

    // Only want the base segment end point which is the center of the 
    // reflex arc
    ep = pbase->EndPoint() ; 

    ccsp = CS_LineSeg(ep, poffs->StartPoint()).MidPoint() ; 
    ccep = CS_LineSeg(ep, poffs->EndPoint()).MidPoint() ; 

    vccs = CS_VECTOR(ccsp, ep) ; 
    vcce = CS_VECTOR(ccep, ep) ; 

    ovalrec.pbseg = pbase ; // base segment pointer
    ovalrec.poseg = poffs->Copy() ; 

    ovalrec.arcA.ctr = ccsp ;
    ovalrec.arcA.rad = fabs(delta / 2.0) ;
    ovalrec.arcB.ctr = ccep ;
    ovalrec.arcB.rad = fabs(delta / 2.0) ;

    vccs.Reverse() ; 
    ovalrec.arcA.sa = vccs.AngleXY() ;
    ovalrec.arcB.sa = vcce.AngleXY() ;

    if (delta < 0)
    {   // Offset left
        ovalrec.arcA.swp = RADIAN180 ; 
        ovalrec.arcB.swp = RADIAN180 ; 
    }
    else
    {   // Offset right
        ovalrec.arcA.swp = -RADIAN180 ; 
        ovalrec.arcB.swp = -RADIAN180 ; 
    }

    ovalList.push_back(ovalrec) ; 
    ovalrec.poseg = 0 ; // make sure destructor leaves pointer alone
}



// Sort the ovals by their left x coordinate (.l parameter)
static int OvalComp(const void *a, const void *b)
{
    CS_OvalArrayNode *pa, *pb ; 
    pa = (CS_OvalArrayNode *)a ; 
    pb = (CS_OvalArrayNode *)b ; 

    if (pa->poval->bndrect.l < pb->poval->bndrect.l)
        return -1 ; 
    else if (pa->poval->bndrect.l > pb->poval->bndrect.l)
        return 1 ; 
    return 0 ; // equal
}

static void OvalSwap(const void *a, const void *b)
{
    CS_OvalArrayNode *pa, *pb ; 
    CS_OvalArrayNode oantmp ; 
    pa = (CS_OvalArrayNode *)a ; 
    pb = (CS_OvalArrayNode *)b ; 

    // Swap the pointers
    oantmp = *pa ; 
    *pa = *pb ; 
    *pb = oantmp ; 
}


inline void AddSegmentToChain(CS_CurveChainList &activelist, 
                              CS_CurveChainList &finallist, 
                              CS_SegPtr pseg, double &delta, double *ptolerance=0)
{
    CS_CurveChain *pcrvchn ;
    bool bCurveProcessed ;

    CS_POINT crvsp(pseg->StartPoint()) ;
    CS_POINT crvep(pseg->EndPoint()) ;

    bCurveProcessed = false ;

    // We only test the last node here since if it can't connect 
    // to the last node then there is considerable overhead in 
    // connecting the curves up properly, which is done as a 
    // final step.
    // bool flattenArc = false ; 


    double pnttestTolerance ; 
    
    if (ptolerance)
    {
        pnttestTolerance = *ptolerance ; 
    }
    else
    {
        if (pseg->IsARC())
        {
            pnttestTolerance = fabs(((CS_ArcSeg *)pseg)->rad * 10e-4) ; 
        }
        else if (pseg->IsLINE())
        {
            CS_LineSeg *pls = (CS_LineSeg *)pseg ;
            pnttestTolerance = fabs((pls->sp.x + pls->ep.x + pls->sp.y + pls->ep.y) * 10e-5) ; 
        }
    }

    /*
    if (pseg->IsARC())
    {   
        // TO DO 
        // Test if this is now a flat arc also, and convert to a line
        // before adding it to the chains. 
        CS_ArcSeg *pas = (CS_ArcSeg *)pseg ; 
        if (tcomp_EQZ(pas->ChordHeight()))
            flattenArc = true ; 
    }
    */

    // The constants here are arbitrary tweak values.


    if (pseg->IsARC())
        pnttestTolerance = fabs(((CS_ArcSeg *)pseg)->rad * 10e-2) ; 

    if (pnttestTolerance > fabs(delta / 20.0))
        pnttestTolerance = fabs(delta / 20.0) ; 

    if (pnttestTolerance < COMPARETOLERANCE * 100.0)
        pnttestTolerance = COMPARETOLERANCE * 100.0 ;

    /*
    double pnttestTolerance = COMPARETOLERANCE * 100.0 ; 
    if (pseg->SegmentType() == CS_Segment::ARC_TYPE)
    {   
        CS_ArcSeg *pas = (CS_ArcSeg *)pseg ; 
        pnttestTolerance = pas->ArcLength() / 1000.0 ; 
        // Want to try and make sure we encompas the end point region properly. 

        // TO DO 
        // Test if this is now a flat arc also, and convert to a line
        // before adding it to the chains. 
        if (tcomp_EQZ(pas->ChordHeight()))
            flattenArc = true ; 
    }
    if (pnttestTolerance > delta / 50.0)
        pnttestTolerance = delta / 50.0 ; 
    if (pnttestTolerance < COMPARETOLERANCE * 10.0)
        pnttestTolerance = COMPARETOLERANCE * 10.0 ;
    */

    CS_CurveChainListItr iccl ;

    /* 
        If a very short segment is created right at the start/end point of the
        offset curve, and the length of the segment is within the pnttestTolerance
        value, then before this short segment gets added, the curves will end up
        being considered closed and the small segment will get discarded. 
        To trap this condition, check to see if the following conditions exist
        1) There is at least one curve in the final list
        2) The last curve in the final list is closed. 
        3) The distance between the final curve end points is not zero
        4) The segment being tested is shorter than the distance
        between the end and start points of the last final curve
    
        (#3 isn't really useful since it won't speed things up that much)
      
        If all the above conditions are met, then stuff this short segment
        into the last final curve
    */
    
    if (finallist.size() > 0)
    {
        iccl = finallist.end() ; 
        iccl-- ; // back up one
        pcrvchn = *iccl ;
        
        if (!pcrvchn->pcrv->Closed())
        {
            double dist = CS_Distance2D(pcrvchn->ep, pcrvchn->sp) ;
            double alen = pseg->ArcLength() ;
            // The points EQ test is so that we make sure that the exit 
            // condition to finalize the curve matches the logic below.
            
            // The distance test is simply another check that was added to filter
            // out the condition where the curve is already closed and we end up 
            // inserting a section into the closed curve that is not wanted. The
            // problem with this is if the very first segment is extremely short, 
            // (within the compare tolerance) and the next segment is long, then 
            // the dist > alen condition will end up being false and the section
            // will be discarded which is not what we want to happen. Thus the 
            // test was added to make sure that the dist is much less than the 
            // overall curve length that has already been chained

            if (tcomp_PointsEQ(pcrvchn->ep.p, crvsp.p, pnttestTolerance) && 
                tcomp_GEQ(dist, alen, pnttestTolerance) && 
                tcomp_GT(pcrvchn->pcrv->arclength, dist, pnttestTolerance * 10.0))
            {
                pcrvchn->pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ;
                pcrvchn->ep = crvep ;
                bCurveProcessed = true ;
            }
        }
    }
    
    if (!bCurveProcessed)
    {
        for (iccl = activelist.begin(); iccl != activelist.end(); iccl++)
        {
            pcrvchn = *iccl ;
            if (tcomp_PointsEQ(pcrvchn->ep.p, crvsp.p, pnttestTolerance))
            {   // then append this curve
                pcrvchn->pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ;
                pcrvchn->ep = crvep ;
                bCurveProcessed = true ;
                // Now check if we've closed this curve
                if (tcomp_PointsEQ(pcrvchn->sp.p, pcrvchn->ep.p, pnttestTolerance))
                {   // Then we've closed the curve so transfer it to the 
                    // final curve list
                    finallist.push_back(pcrvchn) ;
                    // We're breaking out of the loop so it is okay to delete 
                    // this node from the list
                    activelist.erase(iccl) ;
                }
                break ; 
            }
        }
    }
    
    if (!bCurveProcessed)
    {   // Then create a new curve in the active list
        pcrvchn = new CS_CurveChain ;
        pcrvchn->pcrv = new CS_Curve ;
        pcrvchn->sp = crvsp ;
        pcrvchn->ep = crvep ;
        pcrvchn->pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 

        // if (crvsp == crvep) used to be this

        if (tcomp_PointsEQ(crvsp.p, crvep.p, pnttestTolerance))
            finallist.push_back(pcrvchn) ; 
        else
            activelist.push_back(pcrvchn) ; 
    }
}

///////////////////////////////////////////////////////////////
// See RR-Vol2 pg 193 for a diagram of what is happening here
int OffsetOvals(CS_Curve &crv, double delta, CS_OvalList &ovalList)
{
    if (tcomp_EQZ(delta) || !crv.pStart)
        return -1 ; // nothing to do

    int wasclosed = crv.Closed() ; // save if the input curve is closed or not
    
    //////////////////////////////////////////////
    ///// Step 1 - generate the ovals. ///////////
    //////////////////////////////////////////////
    // ovalList  list where the set of all ovals is stored

    CS_SegPtr pwsa ;
    CS_SegPtr pwsb ; 
    CS_VECTOR vccs, vcce ; 

    CS_ArcSeg insertArc ; // temporary work space used to create insert arc
    CS_SegPtr pna ;
    CS_SegPtr pnb ;
    CS_VECTOR vtae, vtaetmp, vtbs ; // endpoint tangent vectors
    CS_POINT ctrpnt ; 
    int zx ;  // cross product z component
    // A end point and B start point of offset segs
    CS_POINT aoepnt, bospnt ; 

    // When looping we only offset the current segment and work out the 
    // inserted arc for the second segment. Note we must offset the second
    // segment to work out various parameters, but it cannot be changed
    // until the next offset step is taken

    CS_VECTOR vtanstart = crv.pStart->UTangent(0.0) ; 
    CS_POINT  startofspnt, startpnt ;

    // Offset the initial segment
    startpnt = crv.pStart->StartPoint() ;

    pna = crv.pStart ;
    pnb = pna->next ;
    vtae = pna->UTangent(1.0) ;


    // Note if we end up with a zero length arc then the start and
    // end points are returned as the center of the arc so that
    // we don't have to do any special testing here for that
    // condition. A final pass to delete all zero length arcs is
    // done after we've finished offseting
    pwsa = pwsb = 0 ; 
    if ((pwsa = pna->Copy()) != 0)
    {
        pwsa->Offset(delta) ; 
        startofspnt = pwsa->StartPoint() ;
    }

    while (pna && pnb)
    {
        // Make copy of the current segment and offset it 
        if (!(pwsa->info & CRV_ARCCONVEX))
        {   // Then add it to the oval list
            AddStdOval(ovalList, pna, pwsa, delta) ; 
        }   

        // Check for inserted reflex arc now.
        vtbs = pnb->UTangent(0.0) ;
        ctrpnt = pnb->StartPoint() ;
        zx = ZXOffsetArcDirection(vtae, vtbs, pna, pnb) ;

        // Save variable we need from B before we offset it
        // Note: we only need to store the tangent vector to handle the 
        // case where we insert an arc inwards and leave it with a zero
        // radius. This would make it impossible to calculate tangent
        // vectors (not really true since all we need are the swp and 
        // start angles)

        vtaetmp = pnb->UTangent(1.0) ;

        pwsb = pnb->Copy() ; 
        pwsb->Offset(delta) ;

        aoepnt = pwsa->EndPoint() ;
        bospnt = pwsb->StartPoint() ;

        if (OffsetInsertReflexArc(&insertArc, ctrpnt, aoepnt, bospnt, delta, zx))
        {   // Add the arc. 
            if (tcomp_EQZ(pwsb->uo))
                insertArc.uo = -1.0 ; // negative denotes an inverse arc section
            else
                insertArc.uo = -pwsb->uo ; // negative denotes an inverse arc section
            insertArc.pParent = pwsa->pParent ; 
            insertArc.cnt = pwsa->cnt ; 
            AddPieOval(ovalList, pna, &insertArc, delta) ; 
        }
    
        // Transfer temp variables over
        vtae = vtaetmp ; 
        delete pwsa ; 
        pwsa = pwsb ; // already done so shift it over
        pna = pnb ;
        pnb = pnb->next ;
    }


    // We always have to process the last segment for both open and
    // closed curves - thus this section of code is taken out of the 
    // if (wasclosed) block.
    if (!(pwsa->info & CRV_ARCCONVEX))
    {   // Then add it to the oval list
        AddStdOval(ovalList, pna, pwsa, delta) ; 
    }   


    // pn will point to the very last segment at this point
    if (wasclosed)
    {   // Then we have to calculate the offset for the last and first segment
        pnb = crv.pStart ; // set up the only variable we need to loop around

        ///////////////////////////////////
        ///  CUT AND PASTED FROM ABOVE  ///
        ///////////////////////////////////
        // Check for inserted reflex arc now.
        vtbs = pnb->UTangent(0.0) ;
        ctrpnt = pnb->StartPoint() ;
        zx = ZXOffsetArcDirection(vtae, vtbs, pna, pnb) ;

        // Save variable we need from B before we offset it
        // Note: we only need to store the tangent vector to handle the 
        // case where we insert an arc inwards and leave it with a zero
        // radius. This would make it impossible to calculate tangent
        // vectors (not really true since all we need are the swp and 
        // start angles)

        vtaetmp = pnb->UTangent(1.0) ;

        pwsb = pnb->Copy() ; 
        pwsb->Offset(delta) ;

        aoepnt = pwsa->EndPoint() ;
        bospnt = pwsb->StartPoint() ;

        if (OffsetInsertReflexArc(&insertArc, ctrpnt, aoepnt, bospnt, delta, zx))
        {   // Add the arc. 
            if (tcomp_EQZ(pwsb->uo))
                insertArc.uo = -1.0 ; // negative denotes an inverse arc section
            else
                insertArc.uo = -pwsb->uo ; // negative denotes an inverse arc section
            insertArc.pParent = pwsa->pParent ; 
            insertArc.cnt = pwsa->cnt ; 
            AddPieOval(ovalList, pna, &insertArc, delta) ; 
        }
        ////////////////////////////////////
        /// END CUT AND PASTE FROM ABOVE ///
        ////////////////////////////////////
    }

    delete pwsa; 

    return 0 ;
}


#ifdef _DEBUG
#define DEBUGSLOWOFFSET(a)    a      
#else
#define DEBUGSLOWOFFSET(a)       
#endif 


/*
    Extracted this comment from the header files, not sure where the best 
    place to put it is. 

    In the offset routines there is a "CS_CrvPnt cp;" variable defined within 
    the CS_Segment that points back to the original offset segment within the
    base curve in case this is important during processing to decide which 
    section of curve to remove or discard for example. 
    It is sometimes required to know which base segment was responsible 
    for a specific offset point on the offset curve. This point will map back
    to the original start point of the offset curve. 
*/


int CS_Curve::OffsetSlow(double delta, CS_CurveSet &curveset, double *ptolerance, CS_CurveSet *pfailedset)
{
    unsigned int i ; 
    int bInputWasClosed = Closed() ; 

            
#ifdef _DEBUG
    int flag = 0 ; 
    if (flag)
    {
        FILE *fpc = fopen("e:\\src\\csgeom2\\crvdump.txt", "wt") ; 
        this->WriteCurveToFile(fpc, 14) ; 
        fclose(fpc) ; 
    }
#endif

    if (tcomp_EQZ(delta))
    {
        CS_Curve *pcrv = new CS_Curve ; 
        pcrv->CopyCurve(*this) ; 
        curveset.AddCurve(pcrv) ; 
        return 0 ; 
    }

    if (bInputWasClosed && nodecnt == 1)
    {   // Then this is a single arc defining a full circle
        CS_ArcSeg *pas = (CS_ArcSeg *)pStart->Copy() ; 
        pas->info &= ~CRV_ARCCONVEX ; 
        pas->Offset(delta) ; 
        if (pas->info & CRV_ARCCONVEX)
            delete pas ; 
        else 
        {
            CS_Curve *pcrv = new CS_Curve ; 
            pcrv->Append(pas) ; 
            curveset.AddCurve(pcrv) ; 
        }
        return 0 ; 
    }

    DEBUGSLOWOFFSET
    (
        FILE *fp = 0 ; 
        fp = fopen("e:\\src\\csgeom2\\offs.log", "w") ; 

        // Dump out the activelist data for debug purposes
        if (fp)
        {
            fprintf(fp, " =================================================\n") ; 
            fprintf(fp, "Input Curve nodes=%d, arclength = %.12lf\n", nodecnt, ArcLength()) ; 

            CS_SegPtr pseg = pStart ; 
            while (pseg)
            {
                pseg->PrintPoints2D(fp) ; 
                pseg = pseg->next ; 
            }
        }
    ) ;

    CS_OvalList ovallist ; 
    OffsetOvals(*this, delta, ovallist) ; 
    if (ovallist.size() == 0)
        return 0 ; // nothing to do.

    /*
       Now filter out the the offset curves within the oval list that 
       are contained in the other curves

       1. Sort all the curves by intersection rectangles so that we
          don't have to test each curve against every single oval. To do
          this we have to remember the original order of the oval curves
          since this will be needed to stitch the offset curve sections
          back together again at the end. Plus we want to simply generate
          clip section regions as a list for each offset segment and then
          merge all the clip regions together in one step at the end of
          the clipping process. Thus for each clipping operation, we 
          clip the entire offset segment against the oval, even if other
          parts of the curve have been clipped away previously. The only
          exception to this rule is when we clip away the entire curve, 
          in which case no further testing for the curve is required. Thus 
          the merge function needs to be performed after every operation 
          to test for this condition.

       2. Once the final filter process before curve stitching requires
          finding all curves that are not connected to any of the other
          remaining curve sections. Thus for this step we extract all
          the remaining curve segments. Then any unconnected curve
          segments go through the following routine:
          i)  Find the nearest base curve segment to the current segment
          ii) Determine whether the segment is left or right of the 
              base segment
          iii) If LEFT and offset was RIGHT then discard, or 
               If RIGHT and offset was LEFT then discard,
               otherwise keep the segment (must decide later how to
               deal with these. It is likely that in this situation
               all remaining segments will be unconnected)

    */

    // Copy ovallist to an array for sorting, also calculate the bounding
    // rectangle for the ovals as we set the array pointers
    CS_OvalArrayNode *ovalarray = new CS_OvalArrayNode[ovallist.size()] ;
    CS_OvalListItr iol ;
    for (i=0, iol=ovallist.begin(); iol != ovallist.end(); i++, iol++)
    {
        ovalarray[i].poval = &(*iol) ;
        ovalarray[i].poval->SetBoundingRects() ;
    }

    // Sort the oval list array

    DEBUGSLOWOFFSET
    (
        {
            if (fp)
            {
                CS_OvalListItr iol ; 
                int xx = 0 ; 
                fprintf(fp, "===============\n") ; 
                fprintf(fp, "Before the Sort\n") ; 
                fprintf(fp, "===============\n") ; 
                for (i = 0 ; i < ovallist.size(); i++)
                {
                    CS_Oval *pov = ovalarray[i].poval ; 
                    fprintf(fp, "Oval %d: --------------\n", xx++) ;
                    pov->pbseg->PrintPoints2D(fp) ; 
                    pov->poseg->PrintPoints2D(fp) ; 
                }
            }
        }
    ) ; 


    QuickSort(ovalarray, (int)ovallist.size(), sizeof(CS_OvalArrayNode), 
              OvalComp, OvalSwap) ; 

    DEBUGSLOWOFFSET
    (
        {
            if (fp)
            {
                CS_OvalListItr iol ; 
                int xx = 0 ; 
                fprintf(fp, "===============\n") ; 
                fprintf(fp, "After the Sort\n") ; 
                fprintf(fp, "===============\n") ; 
                for (i = 0 ; i < ovallist.size(); i++)
                {
                    CS_Oval *pov = ovalarray[i].poval ; 
                    fprintf(fp, "Oval %d: --------------\n", xx++) ;
                    pov->pbseg->PrintPoints2D(fp) ; 
                    pov->poseg->PrintPoints2D(fp) ; 
                }
            }
        }
    ) ; 

    // Connect up all the internal list pointers now
    ovalarray[0].prev = 0 ; 
    ovalarray[ovallist.size()-1].next = 0 ; 
    for (i=1; i < ovallist.size() ; i++)
    {
        ovalarray[i].prev = &ovalarray[i-1] ;
        ovalarray[i-1].next = &ovalarray[i] ; 
    }

    // Intersect all the offset curves with each of the ovals that the offset
    // curves intersect with. This logic is similar to the curve-curve 
    // intersection done in the standard machining offset routine.

    // Note: we manually build the list here instead of basing it on a 
    // predefined template in order to eliminate the memory allocations
    // that are required for each node created in the list
    CS_OvalArrayNode *pan, *panFirst ; 
    panFirst = &ovalarray[0] ;
    for (i=0; i < ovallist.size(); i++)
    {
        pan = panFirst ; 
        while (pan)
        {
            if (pan != &ovalarray[i])
            {   // Don't test against self obviously
                if (ovalarray[i].poval->ofsrect.Right() < 
                    pan->poval->bndrect.Left())
                {   // Then skip this record
                    pan = pan->next ; 
                }
                else if (ovalarray[i].poval->bndrect.Left() > 
                         pan->poval->bndrect.Right())
                {   // Then delete this node from the test list
                    // since we'll never have to test against it any further
                    if (panFirst == pan)
                        panFirst = pan->next ; 
                    if (pan->prev)
                        pan->prev->next = pan->next ; 
                    if (pan->next)
                        pan->next->prev = pan->prev ; 
                    pan = pan->next ; 
                }
                else if (ovalarray[i].poval->ofsrect.Overlaps(pan->poval->bndrect))
                {   // Then test intersections, and merge in whatever ranges
                    // fall within the Oval
                    ovalarray[i].poval->AddToClipList(pan->poval) ; 
                    if (ovalarray[i].poval->status & CS_OVAL_CLIPPEDALL)
                        break ; 
                    pan = pan->next ; 
                }
                else
                {   // Move on to next record for testing
                    pan = pan->next ; 
                }
            }
            else
            {   // Skip to next node
                pan = pan->next ; 
            }
        }
    }

    /*
    CS_OvalArrayNode *pan, *panFirst ; 
    panFirst = &ovalarray[0] ;
    for (i=0; i < ovallist.len; i++)
    {
        pan = panFirst ; 
        while (pan)
        {
            if (pan != &ovalarray[i])
            {   // Don't test against self obviously
                if (ovalarray[i].poval->ofsrect.Overlaps(pan->poval->bndrect))
                {   // Then test intersections, and merge in whatever ranges
                    // fall within the Oval
                    ovalarray[i].poval->AddToClipList(pan->poval) ; 
                    if (ovalarray[i].poval->status & CS_OVAL_CLIPPEDALL)
                        break ; 
                }
            }
            pan = pan->next ; 
        }
    }
    */
    
    delete[] ovalarray ;

    ///////////////////////////////////////////////////////////////////
    // Each entry in the ovallist now has a series of clipList entries.
    // The clipList entries must now be merged together in order to 
    // reduce the offset segments to only those pieces that we want 
    // to consider during the final chaining/stitching process.
    ///////////////////////////////////////////////////////////////////
    int retstatus ; 
    UParmPairListItr pclipnode1, pclipnode2 ; 

    int xx = 0 ; 
    for (iol = ovallist.begin(); iol != ovallist.end(); iol++)
    {
        DEBUGSLOWOFFSET
        (
            if (fp)
            {
                fprintf(fp, "Oval #%d Before Merge\n", xx) ; 
                iol->poseg->PrintPoints2D(fp) ; 
                UParmPairListItr ipp ; 
                for (ipp = iol->clipList.begin(); ipp != iol->clipList.end(); ipp++)
                {
                    UParameterPair *pp ; 
                    pp = &(*ipp) ; 
                    fprintf(fp, "   cut (%12.10lf, %12.10lf) %08x\n", pp->ua, pp->ub, pp->status) ; 
                }
            }
        ) ; 

        if (!(iol->status & CS_OVAL_CLIPPEDALL))
        {   // Then process the list
            pclipnode1 = iol->clipList.begin() ; 
            if (pclipnode1 != iol->clipList.end())
            {
                UParameterPair *pp1, *pp2 ; 
                pp1 = &(*pclipnode1) ; 

                // See if we have to extend the first entry so 
                // that it covers the u=0 point.
                if (tcomp_NEZ(pp1->ua) && 
                    (pp1->status & UParameterPair::UA_ISECT_BASE))
                {   // Then stretch it back to u=0
                    pp1->ua = 0.0 ; 
                }

                pclipnode2 = pclipnode1 ; 
                pclipnode2++ ; 
                while (pclipnode2 != iol->clipList.end())
                {
                    pp2 = &(*pclipnode2) ; 
                    // Process the range between pp1 -> pp2
                    retstatus = pp1->MergeRange(pp2) ; 
                    if (retstatus & UParameterPair::DELETE_B)
                    {
                        iol->clipList.erase(pclipnode2) ; 
                        pclipnode2 = pclipnode1 ; 
                        pclipnode2++ ; 
                    }
                    else
                    {
                        pclipnode1 = pclipnode2 ; 
                        pp1 = pp2 ; 
                        pclipnode2++ ; 
                    }
                }

                // Finally test to see if we have to extend the 
                // last section to the u=1 value
                if (tcomp_NEQ(pp1->ub, 1.0) &&
                    (pp1->status & UParameterPair::UB_ISECT_BASE))
                {   // Then extend the last node
                    pp1->ub = 1.0 ; 
                    if (tcomp_EQZ(pp1->ua))
                    {
                        iol->clipList.clear() ; 
                        iol->clipList.push_back(UParameterPair(0,1)) ; 
                    }
                }

                if (iol->clipList.size() == 1)
                {
                    pp1 = &(*(iol->clipList.begin())) ;
                    if (tcomp_EQZ(pp1->ua) && tcomp_EQ(pp1->ub, 1.0)) 
                        iol->status |= CS_OVAL_CLIPPEDALL ; 
                }
            }
        }

        DEBUGSLOWOFFSET
        (
            if (fp)
            {
                fprintf(fp, "Oval #%d  After Merge\n", xx) ; 
                if (iol->clipList.begin() == iol->clipList.end())
                {   
                        fprintf(fp, "   Keep all\n") ; 
                }
                else
                {
                    UParmPairListItr ipp ; 
                    for (ipp = iol->clipList.begin(); ipp != iol->clipList.end(); ipp++)
                    {
                        UParameterPair *pp ; 
                        pp = &(*ipp) ; 
                        fprintf(fp, "   cut (%12.10lf, %12.10lf) %08x\n", pp->ua, pp->ub, pp->status) ; 
                    }
                }

                xx++ ; 
            }
        ) ; 
    }

    ///////////////////////////////////////////////////////////////////
    // Now we need to perform the final step of stitching the oval offset
    // curve sections which have not been marked for deletion together
    // into a continuous curve. This will generate the final output curves
    ///////////////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    // DEBUG - simply extract all the valid offset segments and 
    //         transfer them to a single curve
    ///////////////////////////////////////////////////////////////////
    /*
    CS_Curve *crv = new CS_Curve; 
    UParmPairListItr ippa, ippb ;
    for (iol=ovallist.begin(); iol != ovallist.end(); iol++)
    {
        if (!(iol->status & CS_OVAL_CLIPPEDALL))
        {   // Then extract the segments, see RR-Vol3 pg 18
            ippa= iol->clipList.begin() ; 
            if (ippa != iol->clipList.end())
            {
                // Check the first node for zero 
                if (tcomp_NEZ(ippa->ua))
                {   // Then output the [0,ua] range
                    crv->Append(iol->poseg->Copy(0, ippa->ua), 
                                    CS_NOENDPOINTADJUSTMENT) ;
                }
                ippb = ippa ; 
                ippb++ ; 
                for(; ippb != iol->clipList.end(); ippb++) 
                {
                    crv->Append(iol->poseg->Copy(ippa->ub, ippb->ua), 
                                                CS_NOENDPOINTADJUSTMENT) ;
                    ippa = ippb ; 
                }

                // Check to see if we need to add the last section 
                if (tcomp_NEQ(ippa->ub, 1.0))
                {
                    crv->Append(iol->poseg->Copy(ippa->ub, 1.0), 
                                    CS_NOENDPOINTADJUSTMENT) ;
                }
            }
            else
            {   // Keep the entire segment
                crv->Append(iol->poseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
            }

        }
    }
    curveset.AddCurve(crv) ; 
    */
    ///////////////////////////////////////////////////////////////////
    // End DEBUG
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////
    // Production: Chain together all remaining segments into curves
    ///////////////////////////////////////////////////////////////////
    CS_CurveChainList activelist ; // curves that are being built
    CS_CurveChainList finallist ;  // completed closed curves

    UParmPairListItr ippa, ippb ;

    // Now chain together all connected segments 

    for (iol = ovallist.begin(); iol != ovallist.end(); iol++)
    {
        if (!(iol->status & CS_OVAL_CLIPPEDALL))
        {   // Then extract the segments, see RR-Vol3 pg 18
            ippa = iol->clipList.begin() ; 
            if (ippa != iol->clipList.end())
            {
                // Check the first node for zero 
                if (tcomp_NEZ(ippa->ua))
                {   // Then output the [0,ua] range
                    AddSegmentToChain(activelist, finallist, iol->poseg->Copy(0, ippa->ua), 
                                        delta, ptolerance) ; 
                }
                ippb = ippa ; 
                ippb++ ; 
                while (ippb != iol->clipList.end()) 
                {
                    AddSegmentToChain(activelist, finallist, iol->poseg->Copy(ippa->ub, ippb->ua), 
                                        delta, ptolerance)  ;
                    ippa = ippb ; 
                    ippb++ ; 
                }

                // Check to see if we need to add the last section 
                if (tcomp_NEQ(ippa->ub, 1.0))
                {
                    AddSegmentToChain(activelist, finallist, iol->poseg->Copy(ippa->ub, 1.0), 
                                        delta, ptolerance) ; 
                }
            }
            else
            {   // Keep the entire segment
                AddSegmentToChain(activelist, finallist, iol->poseg->Copy(), 
                                    delta, ptolerance) ; 
            }
        }
    }

    // Finally transfer all the finished curves to the output curveset

    // Only add curves that have more than 1 segment in them

    CS_CurveChainListItr iccl ; 
    int crvcount = 0 ; 
    for (iccl = finallist.begin(); iccl != finallist.end(); iccl++)
    {
        (*iccl)->pcrv->DeleteShortSegments(COMPARETOLERANCE / 5.0) ;
        if (!tcomp_EQZ((*iccl)->pcrv->ArcLength()))
        {
            // Dump out the activelist data for debug purposes
            DEBUGSLOWOFFSET
            (
                if (fp)
                {
                    fprintf(fp, " ---    ---   ---   ---   ---   ---   ---   ---   \n") ; 
                    fprintf(fp, "Final Curve %d, arclength = %.12lf\n", ++crvcount,(*iccl)->pcrv->ArcLength()) ; 
                    CS_SegPtr pseg = (*iccl)->pcrv->pStart ; 
                    while (pseg)
                    {
                        pseg->PrintPoints2D(fp) ; 
                        pseg = pseg->next ; 
                    }
                }
            ) ; 
            // END DEBUG DUMP

            curveset.AddCurve((*iccl)->pcrv) ; 
            (*iccl)->pcrv = 0 ; // do not de-allocate this one
        }
        else
        {
            // Dump out the activelist data for debug purposes
            DEBUGSLOWOFFSET
            (
                if (fp)
                {
                    fprintf(fp, " ---    ---   ---   ---   ---   ---   ---   ---   \n") ; 
                    fprintf(fp, "Final Curve %d, arclength = %.12lf\n", ++crvcount,(*iccl)->pcrv->ArcLength()) ; 
                    CS_SegPtr pseg = (*iccl)->pcrv->pStart ; 
                    while (pseg)
                    {
                        pseg->PrintPoints2D(fp) ; 
                        pseg = pseg->next ; 
                    }
                }
            ) ; 
            // END DEBUG DUMP
        }
    }


    // The last thing that needs to be done here is to test for situations where 
    // two or more activelist curves hook up end to end almost perfectly with the 
    // exception of some short segements that are either missing or overlap. 
    // This problem typically occurs when large radius arc's are involved with
    // the offset curve and the trimming or inside/outside testing fails to
    // work properly due to roundoff error. Need to create a routine that compares
    // the endpoints that are close, checking for tangency and continuity at these
    // points and then if the curve looks good, connect them up so that they form
    // a completed final curve. 

    crvcount = 0 ; 
    for (iccl = activelist.begin(); iccl != activelist.end(); iccl++)
    {
        // Dump out the activelist data for debug purposes
        DEBUGSLOWOFFSET
        (
            if (fp)
            {
                fprintf(fp, " =================================================\n") ; 
                fprintf(fp, "Active Curve %d, arclength = %.12lf\n", ++crvcount,(*iccl)->pcrv->ArcLength()) ; 
                CS_SegPtr pseg = (*iccl)->pcrv->pStart ; 
                while (pseg)
                {
                    pseg->PrintPoints2D(fp) ; 
                    pseg = pseg->next ; 
                }
            }
        ) ; 
        // END DEBUG DUMP

        if ((*iccl)->pcrv->nodecnt > 1)
        {
            if (bInputWasClosed && (*iccl)->pcrv->Closed())
            {
                curveset.AddCurve((*iccl)->pcrv) ; 
                (*iccl)->pcrv = 0 ; // do not de-allocate this one
            }
            else if (!bInputWasClosed)
            {
                curveset.AddCurve((*iccl)->pcrv) ; 
                (*iccl)->pcrv = 0 ; // do not de-allocate this one
            }
            else if (pfailedset)
            {
                pfailedset->AddCurve((*iccl)->pcrv) ; 
                (*iccl)->pcrv = 0 ; // do not de-allocate this one
            }
        }
        else if (!bInputWasClosed && ((*iccl)->pcrv->nodecnt == 1) &&
                    (activelist.size() == 1)) 
        {   // Then offsetting a single line
            curveset.AddCurve((*iccl)->pcrv) ; 
            (*iccl)->pcrv = 0 ; // do not de-allocate this one
        }
        else if (pfailedset)
        {
            pfailedset->AddCurve((*iccl)->pcrv) ; 
            (*iccl)->pcrv = 0 ; // do not de-allocate this one
        }
        // else
        // {
        //    fprintf(fpDebugOut, "=============>> Activelist with %d element(s)\n", 
        //                         pcrvchn->pcrv->nodecnt) ; 
        // }
    }

	DEBUGSLOWOFFSET ( if (fp) fclose(fp) ; ) ; 
    ///////////////////////////////////////////////////////////////////
    // End Production
    ///////////////////////////////////////////////////////////////////

    return 0 ; 
}



// The segment defined within the clipee is cliped to the oval
// defined by the pclip parameter.
int ClipToOval(CS_Oval *pclipee, CS_Oval *pclip) 
{
    if (pclipee == pclip)
        return 0 ; // can't clip against itself


    return 0 ; 
}
