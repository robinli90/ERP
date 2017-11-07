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
// ofsevents.cpp
#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma warning (disable : 4786)

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

// Need cslibs for the QuickSort routine
#include <csstdlibs/cslib.h>


#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"

#include "cs_offset.h"
#include "cs_offsoval.h"

#include "cs_QuickSort.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)                
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// This is the event list class function section
UEventList::UEventList()
{
    ResetVars() ; 
}

void UEventList::ResetVars()
{
    plist = 0 ; 
    listlen = 0 ; 
    alloclen = 0 ;
    eventSets = 0 ; 
    numSets = 0 ; 
}


void UEventList::DumpList(FILE *fp)
{
    int i ; 
    int es ; 
    int esetvalue ;
    int einfo ; 
    es = 0 ; // step through event sets

    if (!fp)
        fp = fpDebugOut ; 

    for (i=0; i < listlen; i++)
    {
        esetvalue = -1 ; 
        if (es < numSets)
        {
            if (i == eventSets[es])
            {
                esetvalue = i ; 
                es++ ; 
            }
        }

        if (esetvalue >= 0)
            fprintf(fp, "%3d %3d %3d %3d %10.9f ", 
                    i, plist[i].pevent->primIDX, plist[i].pevent->scndIDX, 
                       esetvalue, plist[i].u) ; 
        else
            fprintf(fp, "%3d %3d %3d     %10.9f ", 
                    i, plist[i].pevent->primIDX, plist[i].pevent->scndIDX, 
                       plist[i].u) ; 

        einfo = plist[i].einfo ; 

        if (einfo & UEVENT_INTERSECTION)
            fprintf(fp, "IX: ") ; 

        if (einfo & UEVENT_OVERLAP)
            fprintf(fp, "OV: ") ; 

        if (einfo & UEVENT_INVERTARC)
            fprintf(fp, "IA: ") ; 

        int statcount = 0 ; 

        if (einfo & UEVENT_PRIMARYRECORD) 
        {
            fprintf(fp, "PRIREC ") ; 
            statcount++ ; 
        }
        else
        {   // Suck in the status info from the actual event record
            einfo |= plist[i].pevent->status ; 
        }

        if (einfo & UEVENT_STARTPOINT) 
        {
            fprintf(fp, "ST_PNT ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_CROSSOVER) 
        {
            fprintf(fp, "X_OVER ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_TOUCHOFF) 
        {
            fprintf(fp, "TOUCHO ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_OVERLAPBREVERSE) 
        {
            fprintf(fp, "OVBREV ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_DELETED) 
        {
            fprintf(fp, "DELETE ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_OVERLAPDELETED) 
        {
            fprintf(fp, "OVDELT ") ; 
            statcount++ ; 
        }
        
        if (einfo & UEVENT_LEFT) 
        {
            fprintf(fp, "U_LEFT ") ; 
            statcount++ ; 
        }

        if (einfo & UEVENT_RIGHT) 
        {
            fprintf(fp, "URIGHT ") ; 
            statcount++ ; 
        }

        while (statcount++ < 4) 
            fprintf(fp, "       ") ;

        plist[i].pevent->pnt.Print(fp) ; 

        // if (plist[i].einfo & UEVENT_OVERLAP)
        // {   // Print out the two segments
        //     fprintf(fp, "\n") ; 
        //     plist[i].pevent->psna->pseg->Print(fp) ; 
        //     plist[i].pevent->psnb->pseg->Print(fp) ; 
        // }

        fprintf(fp, "\n") ; 
    }
}

UEventList::~UEventList()
{
    for (int i=0; i < listlen; i++)
    {
        if (plist[i].einfo & UEVENT_PRIMARYRECORD)
        {   // Then de-allocate the UEvent memory
            free(plist[i].pevent) ; 
        }
    }

    if (eventSets)
        delete[] eventSets ;

    // Finally free up the the list memory
    free(plist) ; 
}


// Is this the absolute endpoint of a closed curve
// make this into a macro - might be better
int UEventList::IsEndPoint(CS_Curve *pc, CS_SegPtr pseg, double useg)
{
    if ((pseg == pc->pEnd) && tcomp_EQ(useg, 1.0))
        return 1 ; 
    return 0 ; 
}

// The Load...() calls were implemented to deal with the complication
// that became evident on Sept 2, 2000. The issue is that for the 
// MergeScanDelete operation to work properly all intersection events
// that occur at the same point along a curve have to have the same
// u value. When multiple intersections occur right at the start or end
// of a curve, then several of the intersections could have a u value
// 0 while others will have a value of 1. Thus when the Sort is done
// this events won't get properly grouped together. The solution is 
// to remap the u=1 intersections to u=0 (move the segment that they
// occur on as well). The logic to deal with all this got rather 
// involved so the Load...() calls were created to deal with it and
// thus simplify the code in the main Offset() routine. 
// When Microsoft fixes inlining we should make these two calls inline.

// Load an intersection event
void UEventList::OffsetIXEvent(CCISNode *pisn, int i, int j,
                               double *uvi, double *uvj)
{
    UEvent uevent ; 
    int eventtype ; 
    int counti, countj ;
    double uli, ulj ; // ulengths
    double usegi, usegj ; 
    double ucrvi, ucrvj ; 
    CS_SegPtr psni ;
    CS_SegPtr psnj ; 

    psni = pisn[i].psn ; 
    psnj = pisn[j].psn ;

    uevent.pnt = psni->UPoint(uvi[0]) ; 

    uli = pisn[i].pcrv->SegmentULength(psni) ; 
    ulj = pisn[j].pcrv->SegmentULength(psnj) ; 

    usegi = uvi[0] ; 
    usegj = uvj[0] ; 

    ucrvi = psni->uo + usegi * uli ; 
    ucrvj = psnj->uo + usegj * ulj ; 

    counti = pisn[i].count ; 
    countj = pisn[j].count  ; 

    // If one eventoccurs at the overall Curve u=1.0 point
    // and the overall base curved forms a closed loop, 
    // then we have to map the u=1.0 event to the start of the 
    // curve at u=0.0, and proceed after that

    if (pisn[i].pcrv->statflags & CS_CLOSEDCURVE)
    {
        // Note: both segments cannot have u values of 1.0 since
        // they are not sequential and they are different segments
        // So we only need to one or the other, not both (thus the
        // else if in the logic)

        // This could cause problems where we tolerance shift the end point
        // without actually changing the event point. May have to do some
        // extra testing around all the IsEndPoint tests

        if (IsEndPoint(pisn[i].pcrv, psni, usegi))
        {   // Then remap i event to 0.0
            // psni must point to last segment in the curve so 
            // jump to start segment, and adjust the associated
            // variables for the new segment
            psni = pisn[i].pcrv->pStart ; 
            // usegi must also be equal to 1.0 since this has to 
            // be the end point of the segment, so we are remapping
            // this to 0.0 as well
            usegi = 0.0 ; 
            ucrvi = 0.0 ;
            counti = 0 ; 
        }
        else if (IsEndPoint(pisn[j].pcrv, psnj, usegj))
        {   // remap the j event to 0.0
            psnj = pisn[j].pcrv->pStart ;
            usegj = 0.0 ; 
            ucrvj = 0.0 ;
            countj = 0 ; 
        }
    }
       
    
    // Now orient for which event overall u starts first
    if (psni->uo < psnj->uo)
    {
        uevent.psna = psni ;
        uevent.psnb = psnj ;
        uevent.pca = pisn[i].pcrv ; 
        uevent.pcb = pisn[j].pcrv ; 
        uevent.u1 = usegi ; 
        uevent.u2 = usegj ; 
        uevent.cnta = counti ; 
        uevent.cntb = countj ; 
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ua = ucrvi ; 
        uevent.ub = ucrvj ; 
    }
    else
    {   // j node comes before the i node
        uevent.psnb = psni ;
        uevent.psna = psnj ;
        uevent.pcb = pisn[i].pcrv ; 
        uevent.pca = pisn[j].pcrv ; 
        uevent.u2 = usegi ; 
        uevent.u1 = usegj ; 
        uevent.cntb = counti ; 
        uevent.cnta = countj ; 
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ub = ucrvi ; 
        uevent.ua = ucrvj ; 
    }
    
    // Only need set the one bit in this case
    UEvent *pevent ; 
    eventtype = UEVENT_INTERSECTION ;
    pevent = AppendPrimary(eventtype, uevent) ; 
    AppendSecondary(eventtype, pevent) ; 
}


void UEventList::OffsetOVLPEvent(CCISNode *pisn, int i, int j,
                                 double *uvi, double *uvj)
{
    UEvent uevent ; 
    int eventtype ; 
    int counti, countj ; 
    double uli, ulj ; // ulengths
    double usegi, usegj ; 
    double ucrvi, ucrvj ; 
    CS_SegPtr psni ;
    CS_SegPtr psnj ;
    // Parameters specific to the overlapped case
    CS_VECTOR vi, vj ; 
    bool reversed ; 
    double theta ; 

    psni = pisn[i].psn ; 
    psnj = pisn[j].psn ; 

    /////////////////////////////////////////////////////////////////////////
    // For overlaps we will create 2 record, one at the start of the overlap
    // and the other at the end, thus we may end up effectively splitting an
    // overlap across two segments if we have to move one of the points 
    // to the start of the overall curve. This won't affect processing
    // later on since the CopySection() routine deals with sections that
    // span the end-start boundary of the curve. (Or in other words
    // a call such as CopySection(ua, ub) where ua > ub is valid)

    //////////////////////////////////////////////////////////////
    // Need the direction information from the original curves
    // Must do this step first since it affects everything.
    // Note: this will work for arcs as well since the arcs
    // overlap and the points are common
    vi = psni->UTangent(uvi[0]) ; 
    vj = psnj->UTangent(uvj[0]) ; 
    theta = vi.Angle(vj) ; 
    reversed = false ; 
    if (theta > RADIAN90 || theta < -RADIAN90)
    {
        reversed = true ;
    }


    // Note can remove this test and the vector reverse logic above
    // once this is confirmed to be valid. The uvj[0] > uvj[1] is 
    // the simplest way to test for the reverse condition and will
    // always be true and valid if the intersection routines are
    // working correctly. Thus this is a secondary check of the 
    // intersection routines.
    if (uvj[0] > uvj[1])
    {
        if (!reversed)
        {
            sprintf(szGeomErrString, "Reverse error in IXOverlap") ; 
        }
    }


    uli = pisn[i].pcrv->SegmentULength(psni) ; 
    ulj = pisn[j].pcrv->SegmentULength(psnj) ; 

    //////////////////////////////////////
    //////////////////////////////////////
    // 1st overlap intersection point
    //////////////////////////////////////
    //////////////////////////////////////
    usegi = uvi[0] ; 
    usegj = uvj[0] ; 
    ucrvi = psni->uo + usegi * uli ; 
    ucrvj = psnj->uo + usegj * ulj ; 
    counti = pisn[i].count ; 
    countj = pisn[j].count ; 

    uevent.pnt = psni->UPoint(usegi) ; 

    // now test remapping of 1st intersection point
    if (pisn[i].pcrv->statflags & CS_CLOSEDCURVE)
    {
        // Note: both segments cannot have u values of 1.0 since
        // they are not sequential and they are different segments
        // So we only need test one or the other, not both (thus the
        // else if in the logic)
        if (IsEndPoint(pisn[i].pcrv, psni, usegi))
        {   // Then remap i event to 0.0
            // psni must point to last segment in the curve so 
            // jump to start segment, and adjust the associated
            // variables for the new segment
            psni = pisn[i].pcrv->pStart ; 
            // usegi must also be equal to 1.0 since this has to 
            // be the end point of the segment, so we are remapping
            // this to 0.0 as well
            usegi = 0.0 ; 
            ucrvi = 0.0 ;
            counti = 0 ; 
        }
        else if (IsEndPoint(pisn[j].pcrv, psnj, usegj))
        {   // remap the j event to 0.0
            psnj = pisn[j].pcrv->pStart ;
            usegj = 0.0 ; 
            ucrvj = 0.0 ;
            countj = 0 ; 
        }
    }
       

    // If we swap records for Overlaps, then we have to check the 
    // OVERLAPBREVERSE bit and adjust the STARTPOINT values for 
    // each of the events created. Must also take into consideration
    // the fact that the overlap uvi[] and uvj[] values are ordered.
    // Thus uvi[0] < uvi[1] will always hold but, uvj[0] > uvj[1] 
    // will be true if the curves are reversed.
    bool bSwapped = false ; 

    // Now orient for which event overall u starts first
    if (psni->uo < psnj->uo)
    {
        uevent.psna = psni ;
        uevent.psnb = psnj ;
        uevent.pca = pisn[i].pcrv ; 
        uevent.pcb = pisn[j].pcrv ; 
        uevent.u1 = usegi ; 
        uevent.u2 = usegj ; 
        uevent.cnta = counti ;
        uevent.cntb = countj ;
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ua = ucrvi ; 
        uevent.ub = ucrvj ; 
    }
    else
    {   // j node comes before the i node
        uevent.psnb = psni ;
        uevent.psna = psnj ;
        uevent.pcb = pisn[i].pcrv ; 
        uevent.pca = pisn[j].pcrv ; 
        uevent.u2 = usegi ; 
        uevent.u1 = usegj ; 
        uevent.cntb = counti ;
        uevent.cnta = countj ;
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ub = ucrvi ; 
        uevent.ua = ucrvj ; 
        bSwapped = true ; 
    }

    // See notes RR-Vol2 pgs 58-60
    eventtype = UEVENT_OVERLAP ; // this has to be set
    if (reversed)
    {
        eventtype |= UEVENT_OVERLAPBREVERSE ; // mask in reversed condition
    }

    if (bSwapped)
    {   // Finally need to test for the STARTPOINT condition
        // Then normally the A section would have been the overlap start
        // but now it will be the B section that defines this node 
        // as to whether or not it is a start or end point. Thus 
        // we set STARTPOINT only if it wasn't reversed
        if (!reversed)
            eventtype |= UEVENT_STARTPOINT ; 
    }
    else
    {   // Weren't swapped so both points are start points
        eventtype |= UEVENT_STARTPOINT ; 
    }

    UEvent *pevent ; 
    pevent = AppendPrimary(eventtype, uevent) ; 
    // toggle the STARTPOINT bit for the secondary record if the B (or 
    // secondary curve) is reversed
    if (reversed)
        eventtype ^= UEVENT_STARTPOINT ; // exclusive OR the startpoint bit
    AppendSecondary(eventtype, pevent) ; 


    ///////////////////////////////////
    ///////////////////////////////////
    // 2nd Overlap Intersection point
    ///////////////////////////////////
    ///////////////////////////////////
    // restore pointers in case one was modified
    psni = pisn[i].psn ;
    psnj = pisn[j].psn ;

    usegi = uvi[1] ; 
    usegj = uvj[1] ; 
    ucrvi = psni->uo + usegi * uli ; 
    ucrvj = psnj->uo + usegj * ulj ; 

    counti = pisn[i].count ; 
    countj = pisn[j].count ; 

    uevent.pnt = psni->UPoint(usegi) ; 

    // now test remapping of 1st intersection point
    if (pisn[i].pcrv->statflags & CS_CLOSEDCURVE)
    {
        // Note: both segments cannot have u values of 1.0 since
        // they are not sequential and they are different segments
        // So we only need to one or the other, not both (thus the
        // else if in the logic)
        if (IsEndPoint(pisn[i].pcrv, psni, usegi))
        {   // Then remap i event to 0.0
            // psni must point to last segment in the curve so 
            // jump to start segment, and adjust the associated
            // variables for the new segment
            psni = pisn[i].pcrv->pStart ; 
            // usegi must also be equal to 1.0 since this has to 
            // be the end point of the segment, so we are remapping
            // this to 0.0 as well
            usegi = 0.0 ; 
            ucrvi = 0.0 ;
            counti = 0 ; 
        }
        else if (IsEndPoint(pisn[j].pcrv, psnj, usegj))
        {   // remap the j event to 0.0
            psnj = pisn[j].pcrv->pStart ;
            usegj = 0.0 ; 
            ucrvj = 0.0 ;
            countj = 0 ; 
        }
    }
       

    // Now orient for which event overall u starts first
    // Note !bSwapped  is same as (psni->uo < psnj->uo) at this point
    // NO NO NO, this had to be modified since statement above is not 
    // true when an overall ucurve value of 1.0 gets promoted to 0.0 
    // in the above section. Then the swapping should not occur here
    // if it occured above (possibly in all cases but not sure)

    bSwapped = false ; 
    if (psni->uo < psnj->uo)
    {
        uevent.psna = psni ;
        uevent.psnb = psnj ;
        uevent.pca = pisn[i].pcrv ; 
        uevent.pcb = pisn[j].pcrv ; 
        uevent.u1 = usegi ; 
        uevent.u2 = usegj ; 
        uevent.cnta = counti ;
        uevent.cntb = countj ;
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ua = ucrvi ; 
        uevent.ub = ucrvj ; 
    }
    else
    {   // j node comes before the i node
        uevent.psnb = psni ;
        uevent.psna = psnj ;
        uevent.pcb = pisn[i].pcrv ; 
        uevent.pca = pisn[j].pcrv ; 
        uevent.u2 = usegi ; 
        uevent.u1 = usegj ; 
        uevent.cntb = counti ;
        uevent.cnta = countj ;
        // To calculate the overall U values we need the
        // relative U length for each segment
        uevent.ub = ucrvi ; 
        uevent.ua = ucrvj ; 
        bSwapped = true ; 
    }

    eventtype = UEVENT_OVERLAP ; // this has to be set
    if (reversed)
    {
        eventtype |= UEVENT_OVERLAPBREVERSE ; // mask in reversed condition

        // This if is the same as testing (bSwapped && reversed) since
        // we're inside the reversed if
        if (bSwapped) 
        {   // Finally need to test for the STARTPOINT condition
            // Then normally the A section would have been the overlap start
            // but now it will be the B section that defines this node 
            // as to whether or not it is a start or end point. Thus 
            // we set STARTPOINT only if it was reversed
            // Because this is the second point this is the start point
            // if they're reversed and the original base curve was the 
            // end point.
            eventtype |= UEVENT_STARTPOINT ; 
        }
        // else both forward so not start point
    }

    pevent = AppendPrimary(eventtype, uevent) ; 

    // toggle the STARTPOINT bit for the secondary record if the B (or 
    // secondary curve) is reversed
    if (reversed)
        eventtype ^= UEVENT_STARTPOINT ; // exclusive OR the startpoint bit
    AppendSecondary(eventtype, pevent) ; 
}

void UEventList::OffsetInvArcEvent(CCISNode *pisn, int i)
{
    // Note: all the segment B values are not really used anywhere
    // since all the required information is in the A data. But to 
    // simplify the number of different cases that must be tested 
    // in merge scan we set them to the same as the A values.
    // This is required since in MergeScan we compare the uevent
    // value by segment and segment value and use the B values 
    // if it is not the UEVENT_PRIMARYRECORD data node.

    UEvent uevent ; 
    double ulen ;
    int eventtype ; 

    // Define the inverted arc start event
    uevent.psna = pisn[i].psn ;
    uevent.psnb = pisn[i].psn ; // For MergeScan
    uevent.pca = pisn[i].pcrv ; 
    uevent.pcb = pisn[i].pcrv ; 
    uevent.u1 = 0.0 ; 
    uevent.u2 = 0.0 ; // For MergeScan
    // To calculate the overall U values we need the
    // relative U length for each segment
    ulen = pisn[i].pcrv->SegmentULength(pisn[i].psn) ; // need this for later

    uevent.pnt = pisn[i].psn->StartPoint() ; 

    uevent.ua = pisn[i].psn->uo ; 
    uevent.ub = pisn[i].psn->uo ; // For MergeScan
    uevent.cnta = pisn[i].count ; 
    uevent.cntb = pisn[i].count ; // MergeScan and sorting

    // Only need set the one bit in this case
    eventtype = UEVENT_INVERTARC | UEVENT_STARTPOINT ;
    AppendPrimary(eventtype, uevent) ; 

    // Don't think we have to check the end of the inverse arc 
    // events for remapping from 1.0 to 0.0 u values. The reason
    // is that we're skipping ahead to the first crossover in the
    // merge logic, and since it is the arc end we are clearing the 
    // the inv arc condition. If the 0.0 point is an intersection
    // we would also clear the modal on inv arc bit indicator as
    // well so this still works out.Regardless will do so anyways
    // and figure this out later.

    double usegi ; 
    double ucrvi ; 

    usegi = 1.0 ; 
    ucrvi = pisn[i].psn->uo + ulen ; 

    uevent.pnt = pisn[i].psn->EndPoint() ; 

    CS_SegPtr psn = pisn[i].psn ;
    int countiIn = pisn[i].count ;

    // Now add the inverted arc end event
    if (pisn[i].pcrv->statflags & CS_CLOSEDCURVE)
    {
        // Note: both segments cannot have u values of 1.0 since
        // they are not sequential and they are different segments
        // So we only need to one or the other, not both (thus the
        // else if in the logic)
        if (IsEndPoint(pisn[i].pcrv, psn, 1.0))
        {   // Then remap i event to 0.0
            // psni must point to last segment in the curve so 
            // jump to start segment, and adjust the associated
            // variables for the new segment
            psn = pisn[i].pcrv->pStart ; 
            // usegi must also be equal to 1.0 since this has to 
            // be the end point of the segment, so we are remapping
            // this to 0.0 as well
            usegi = 0.0 ; 
            ucrvi = 0.0 ;
            countiIn = 0 ; 
        }
    }


    uevent.psna = psn ;
    uevent.psnb = psn ; // For MergeScan
    uevent.pca = pisn[i].pcrv ; 
    uevent.pcb = pisn[i].pcrv ; 
    uevent.u1 = usegi ; 
    uevent.u2 = usegi ; // Note used but simplifies MergeScan logic
    uevent.ua = ucrvi ; 
    uevent.ub = ucrvi ; // For MergeScan
    uevent.cnta = countiIn ; 
    uevent.cntb = countiIn ; // For MergeScan
    eventtype = UEVENT_INVERTARC ;
    AppendPrimary(eventtype, uevent) ; 
}
 

// This is called normally for inverted arc and intersection type events
// but for an overlap this must be called twice, once for the overlap
// start and once for the overlap end. On the overlap calls the 
// UEVENT_STARTPOINT bit must be set in the eventtype that is passed in
// mode=0 is default and means we are appending Offset style events, 
// (events which occur within the same curve). If mode==1 then the 
// event is being created solely for the curve in question since the 
// other event happens on a different curve (boolean, pocketing)


// TO DO - might want to look at using some type of heuristic for an
// optimal value for UEVENT_ALLOCBLKSIZE instead of the fixed constant
// that is currently used.
UEvent *UEventList::AppendPrimary(int eventtype, UEvent &event) 
{
    if (listlen + 2 > alloclen)
    {   // Then we need to allocate more memory
        UEventRecord *precs = 
            (UEventRecord *)realloc(plist, sizeof(UEventRecord) * 
                                    (alloclen + UEVENT_ALLOCBLKSIZE)) ; 
        if (precs)
        {
            plist = precs ; 
            alloclen += UEVENT_ALLOCBLKSIZE ;
        }
        else
        {   // A memory error occured
            return 0 ; // return NULL pointer
        }
    }
    
    // Allocate space for the event definition
    UEvent *pevent = (UEvent *)malloc(sizeof(UEvent)) ; 
    if (!pevent)
        return 0 ; // error

    // Save the new event data
    *pevent = event ; // copy over the event data
    pevent->status = 0 ; 

    // Make sure it is a primary record
    pevent->primIDX = listlen ; 
    plist[listlen].einfo = eventtype | UEVENT_PRIMARYRECORD ; 
    plist[listlen].pevent = pevent ;
    plist[listlen].usort = event.cnta + event.u1 ;
    plist[listlen].irsIDX = -1 ; 
    plist[listlen].ireIDX = -1 ; 
    plist[listlen++].u = event.ua ;  

    return pevent  ; // success
}


// Call this when the UEvent has already been allocated, and we don't need
// more memory allocated. 
UEvent *UEventList::AppendSecondary(int eventtype, UEvent *pevent) 
{
    if (listlen + 2 > alloclen)
    {   // Then we need to allocate more memory
        UEventRecord *precs =
            (UEventRecord *)realloc(plist, sizeof(UEventRecord) *
                                    (alloclen + UEVENT_ALLOCBLKSIZE)) ;
        if (precs)
        {
            plist = precs ;
            alloclen += UEVENT_ALLOCBLKSIZE ;
        }
        else
        {   // A memory error occured
            return 0 ; // return NULL pointer
        }
    }

    // Make sure it is not a primary record
    pevent->scndIDX = listlen ;
    plist[listlen].einfo = eventtype & ~UEVENT_PRIMARYRECORD ;
    plist[listlen].pevent = pevent ;
    plist[listlen].usort = pevent->cntb + pevent->u2 ;
    plist[listlen].irsIDX = -1 ;
    plist[listlen].ireIDX = -1 ;
    plist[listlen++].u = pevent->ub ;

    return pevent  ; // success
}


// Based on all the changes made sorting by arc, overlap and intersect
// as the third key accomplishes nothing. The only thing that is required
// here is to have inverse arcs appear last in an event set. Thus we
// have to treat inverse arcs as a special case
int ueventComp(const void *a, const void *b)
{
    UEventRecord *pa = (UEventRecord *)a ; 
    UEventRecord *pb = (UEventRecord *)b ; 

    // want to sort by cnta and then cntb within
    // thus if (pa->cnt,cntb > pb->cnta,cntb) etc.. is what we
    // want to do. This creates for levels of keys involved with 
    // this sort.
    
    // Sort by U values as accurately as is possible
    if (pa->usort > pb->usort)
        return 1 ; 
    else if (pa->usort == pb->usort)
    {
        // Next make sure the segments appear in proper U order
        // at the U event node (A before B before C etc...)
        // But all overlaps must appear first which has priority
        // See RR-Vol 2 pg 38,53-55 for updated notes,
        // This was further updated by scanning through at the start
        // of MergeScan and effectively shifting overlap events up
        // to the top. See RR-Vol2 pg 83 for another update.

        //////////////////////////////////////////////////////////////////
        // This will be insufficient if tolerance testing in the merge
        // scan happens to put the inverse arc first
        // First do the invert arc testing
        // if (pa->einfo & UEVENT_INVERTARC)
        //     return 1 ; // inverse arc is always greater
        // else if (pb->einfo & UEVENT_INVERTARC) 
        //     return -1 ; // a LT b since b is INVARC
        // Inverted arcs are now shifted to bottom before the MergeScan
        //////////////////////////////////////////////////////////////////

        if (pa->pevent->cnta > pb->pevent->cnta)
            return 1 ; 
        else if (pa->pevent->cnta == pb->pevent->cnta)
        {
            if (pa->pevent->cntb > pb->pevent->cntb)
                return 1 ; 
            else if (pa->pevent->cntb == pb->pevent->cntb)
            {
                return 0 ; 
            }
        }
    }
    return -1 ; // else LT
}

// Swaps two UEventRecord structures and updates the primary and
// secondary index values within the pevent members that the event
// records refer to. For offsetting the primIDX and scndIDX values
// are not used, thus we do not have to worry about how the indexes
// are remapped when a PRIMARY and a SECONDARY record are swapped.
// For boolean operations, within the pevent member the A data
// will always be primary, and the B will always be secondary. 
// Effectively, the PRIMARYRECORD status bit is not used when doing
// boolean operations.  If an event record is PRIMARY, then we only 
// want to repoint the primIDX value of the pevent member. Likewise
// if it is a !PRIMARYRECORD, then only update the scndIDX pevent
// member variable. This will handle all situations correctly (for
// either offset or boolean operations).
// See RR-Vol2 pg 151 
void ueventSwap(const void *x, const void *y)
{
    int i ; 
    UEventRecord *px = (UEventRecord *)x ; 
    UEventRecord *py = (UEventRecord *)y ; 

    // Temporary values of the indexes within the x and y records
    
    // Swap the records
    UEventRecord uetmp = *px ; 
    *px = *py ; 
    *py = uetmp ; 

    // Now swap the reverse lookup index reference values
    if (px->einfo & UEVENT_PRIMARYRECORD)
    {
        i = px->pevent->primIDX ; 
        px->pevent->primIDX = py->pevent->primIDX ; 
        py->pevent->primIDX = i ;
    }
    else
    {
        i = px->pevent->scndIDX ; 
        px->pevent->scndIDX = py->pevent->scndIDX ; 
        py->pevent->scndIDX = i ;
    }
    
    // Done
}

// Note because the U sorting is not exact due to floating point
// tolerance issues. Make sure to map all the U values to adjusted
// coincident values during the pre-processing step so that we 
// can quickly test for == u values during the actual offset step
void UEventList::SortList()
{
    QuickSort(plist, listlen, sizeof(UEventRecord), 
                    ueventComp, ueventSwap) ; 
}


////////////////////////////////////////////////////////////////
// Merge Scan and Delete nodes
////////////////////////////////////////////////////////////////

// The TestMatchingEvent() was required since we abandoned checking
// against the plist[i].u value for testing. After moving to 
// checking the seg and seg uvalue, we had to introduce this
// test function, since identical overall u values can occur on 
// different segments, if the event occurs at the intersection
// of two segments.
// If the testing of segments and U values proves to be in
// inadequate to ensure reliability, then move to a model 
// where the actual point is tested to determine which set
// it belongs to. By using a higher tolerance for the merge
// than in the actual segment building part of the algorithm
// where the common index chains are linked together, we 
// should be able to ensure that the routine never fails. 
// Note these two tolerances will have to be chosen 
// well and may even require a scanning step to check and 
// see the minimum distance between two non-common points.

// This testing is proving to be the biggest problem to making
// everything work correctly. If it weren't for floating point
// round off errors then everything would be easy. 
// Changing now to testing by points, as mentioned above.
// During the final curve stitching we always have to adjust 
// the start node of the segment that is being attached to 
// exactly match the end node of the previous section. When 
// stitching curves together, we also do not want an tolerance
// compare failure to occur, which means that during this test 
// phase we want to bump up the tolerance slightly. We will use
// a factor of 20% above what is currently selected and then
// set it back when done. Note, this breaks the multithreading
// capabilities since another offset routine can no longer
// be called simultaneously in this event.

// Eventually had to abandon the point testing and revert to the code
// shown below


// Returns true if the two events refer to the same overall U point
bool UEventList::TestMatchingEvent(int i, int j)
{
    ///////////////////////////////////////////////////////
    // Can't use points for this - see Page 69 RR-Vol2
    // if (plist[i].pevent->pnt == plist[j].pevent->pnt)
    //     return true ; 
    ///////////////////////////////////////////////////////
    if (i == j)
        return true ; 
    ///////////////////////////////////////////////////////////////
    // Ran into compare tolerance problems with the following code
    // Everything worked except when it came time to stitch the records
    // back together, since end points didn't correctly match up. 
    // The failure was from taking the wrong curve section due
    // to an event point comparison test difference between actual
    // point testing and segment u value testing. 
    // The only way to fix this problem is by sorting events within
    // the event set based on decreasing or increasing index values
    // and always extracting the minimum u event (see RR-Vol2 pg70)
    ///////////////////////////////////////////////////////////////
    CS_Curve *pcrv ; 
    CS_CrvPnt cpi, cpj ; 
    
    // Note for the pcrv pointer, for the offset routine, pca and pcb will
    // both point to the same curve so we can set pcrv to whatever we like.
    // For the boolean operations, both i and j will both either be PRIMARY or
    // both won't be primary, one cannot be primary while the other is. 
    // The reason is that the event list B that is generated for the 
    // secondary curve is defined completely with non-primary events. All 
    // the primary events are defined within the A curve. Thus we can get
    // away with setting pcrv within the first if statement only. 

    // NOTE: if the logic is extended to handle intersection of more 
    // than two curves simultaneously, revisit this logic to make sure
    // everything still works out OK.

    // Feb 6, 2001 - new issue discovered (again this thing is proving to 
    // be the single biggest problem with the whole process). Problem 
    // occurs as follows: a very short inverse arc is created which is
    // then tested against a nearby intersection point. Now one end of
    // the inverse arc is within the tolerance of an actual intersetion
    // point and when the SequentialSegments() test was done it 
    // incorrectly returned true. Thus an inverse arc event was lumped
    // together with an intersection event, and then later on in the index
    // processing all the curve sections were labelled as being connected
    // to inverse arcs (I think this is what happened at least) and 
    // thus no curves were output when one curve should have been.

    if (plist[i].einfo & UEVENT_PRIMARYRECORD)
    {
        pcrv = plist[i].pevent->pca ; 
        cpi.s = plist[i].pevent->psna ; 
        cpi.u = plist[i].pevent->u1 ; 
    }
    else
    {
        pcrv = plist[i].pevent->pcb ; 
        cpi.s = plist[i].pevent->psnb ; 
        cpi.u = plist[i].pevent->u2 ; 
    }
    
    if (plist[j].einfo & UEVENT_PRIMARYRECORD)
    {
        cpj.s = plist[j].pevent->psna ; 
        cpj.u = plist[j].pevent->u1 ; 
    }
    else
    {
        cpj.s = plist[j].pevent->psnb ; 
        cpj.u = plist[j].pevent->u2 ; 
    }
    
    // Now test if these represent the same overall U point
    if ((cpj.s == cpi.s) && tcomp_EQ(cpi.u, cpj.u))
        return true ; // same point for sure
    
    // Feb 6, 2001 - adding test here to see if one
    // event is an intersection and the other an inverse
    // arc and if they are then don't return true
    // if (plist[i].pevent->status & UEVENT_INVERTARC) && 
    //     plist[j].pevent->status & UEVENT_INVERTARC)

    if (pcrv->SequentialSegments(&cpi, &cpj))
        return true ; 
    // Else these are not the same points, and thus events
    /////////////////////////////////////////////////////////////////////
    // End of u and segment based code test
    /////////////////////////////////////////////////////////////////////

    return false ; 
}


// Merge the overlap sections into continuous runs. Thus say we have
// three overlap sections defined by {us0,ue0},{us1,ue1},{us2,ue2} 
// (usi,esi are the u values of each overlap section at the start and the
// end) that are contiguous so that ue0==us1 and ue1==us2, we want to
// eliminate the inner overlap definitions so that what we are left with
// is {us0,ue2}. This will simplify the final stage offset processing since
// we won't have to test the fact that we are already within an overlap 
// section. Note, all intersections and invert arc definitions in between
// {us0,ue2} are left alone. To simplify processing the inner overlap 
// sections will be marked as deleted so that they do not affect further
// processing. Compressing the array will simply waste time
// We also partition the events into sets based on their U value. Each 
// event is assigned a set number and the event's own index count within
// that set. Thus if an event needs to scan other events within its 
// immediate set it can do so without having to continuously call the 
// tcomp_XX routine which can be time consuming. An event set is defined
// as all events with the same u value in the stage 1 offset curve.

int UEventList::MergeOverlaps()
{

    if (listlen == 0)
        return 0 ; // nothing to do

    MergeParameters mrgprms ; 
    int i ;

    // Initliaze uLast to the first u value in the list
    mrgprms.setStartIDX = 0 ; 
    mrgprms.setCount = 0 ; 


    eventSets = new int[listlen + 4] ; 

    // Set to -1 ; 
    memset(eventSets, 0xff, sizeof(int) * (listlen + 4)) ; 

    // Need this defined in MergeScanAndDelete but we save time 
    // by allocating it once
    // sublist = new int[listlen+4][2] ; 
    ovlprecs = new UEventRecord[listlen+4] ; 

    int lastMatchIndex ; 
    bool ueventsMatch ; 

    lastMatchIndex = 0 ; 

    // Temporarily increase the tolerance by reducing the compare constant
    // by a factor of 12.5 times (1/.08) 
    // Tolerance tol  ;
    // tol.Scale(0.08) ; 

    for (i=0; i < listlen; i++)
    {
        ueventsMatch = TestMatchingEvent(i, lastMatchIndex) ;

        /////////////////////////////////////////////////////////////
        // Old Logic
        // if (the count is not 0) AND (the current or previous event 
        // was an inverse arc OR the previous uevent doesn't match 
        // this one) then MergeScanAndDelete()
        // if ((i != 0) && 
        //     (lastWasInvertArc || !ueventsMatch ||
        //           (plist[i].einfo & UEVENT_INVERTARC)))
        // This was the logic before but fails when the invert arc
        // end lies exactly on an intersection point. The reason is
        // that a valid open area will then be classified as having
        // an inverted arc segment when in fact it doesn't since the
        // bit is not cleared in time. 
        /////////////////////////////////////////////////////////////


        if (!ueventsMatch)
        {   // New u set starting
            MergeScanAndDelete(mrgprms, i) ;
            lastMatchIndex = i ; 
        }
        
        plist[i].setCount = mrgprms.setCount ; 
    }

    // Clean up the last u event set
    MergeScanAndDelete(mrgprms, i) ;

    numSets = mrgprms.setCount ; // save the number of Event sets

    delete[] ovlprecs ;
    // delete[] sublist ; // no longer required

    return mrgprms.setCount ; 
}


// set start and end indexes (se is actually the last set entry + 1)
void UEventList::MoveInvArcsToEnd(int setstart, int setend) 
{
    int i ; 
    ///////////////////////////////////////////////////////////////////////////
    // Here we have to do is to bubble sort the Inverse arcs to the
    // bottom without changing the relative positions of any other entries in 
    // the list. Note: we should only ever have at most 2 inverse arc records
    // within a single event set, and if there are two then one will be an
    // end event and the other a start event. The order of these two will 
    // matter since we are storing bInvertArc as an on off type condition
    // thus the end event must be sorted to appear before the start event
    // in that situation. see RR-Vol2 pg 84-87
    ///////////////////////////////////////////////////////////////////////////
    UEventRecord iaevent[4] ; 
    int nia ; // number of ia arcs in set
    // Scan for positions
    nia = 0 ; 
    for (i=setstart; i < setend; i++)
    {
        if (plist[i].einfo & UEVENT_INVERTARC)
        {   // save copy of inverse arc event record
            iaevent[nia++] = plist[i] ; 
        }
        else
        {   // This is not an invert arc record
            if (nia > 0)
            {   // Then bubble the records up
                plist[i-nia] = plist[i] ; // shift record back
            }
        }
    }
    
    // TO DO - remove this code once debugging is completed
    CS_FAULTASSERT(
        if (nia > 2)
        {   // Want to memory fault here to trap error during debugging
            int *pint ; 
            pint = 0 ; 
            *pint = 1 ; // memory fault here
        }
    ) ; 
        
    // Do final insert back of the invert arcs
    if (nia == 1)
    {   // Save it at the end
        plist[setend-1] = iaevent[0] ; 
    }
    else if (nia == 2)
    {   // Have to order the two correctly at the end of list
        if (iaevent[0].einfo & UEVENT_STARTPOINT)
        {   // Then we want this record last
            plist[setend-2] = iaevent[1] ; 
            plist[setend-1] = iaevent[0] ; 
        }
        else
        {   // iaevent[0] is an Endpoint so it should be first
            plist[setend-2] = iaevent[0] ; 
            plist[setend-1] = iaevent[1] ; 
        }
    }
}


// Returns the number of overlaps counted
int UEventList::MoveOverlapsToTop(int setstart, int setend) 
{
    int i ; 
    ///////////////////////////////////////////////////////////////////////////
    // Here we are bubble sorting the Overlap events to the 
    // bottom without changing the relative positions of any other entries in 
    // the list. Note: we should only ever have at most 2 overlap records
    // within a single event set, and if there are two then one will be an
    // end event and the other a start event. 
    // See RR-Vol2 Pg 136
    // Works the same as the move invert arcs except we shift everything that
    // isn't an overlap down
    ///////////////////////////////////////////////////////////////////////////
    int novs ; // number of overlaps in the event set
    // Scan for positions
    novs = 0 ; 
    for (i=setend - 1;  i >= setstart; i--)
    {
        if (plist[i].einfo & UEVENT_OVERLAP)
        {   // save copy of inverse arc event record
            ovlprecs[novs++] = plist[i] ; 
        }
        else
        {   // This is not an invert arc record
            if (novs > 0)
            {   // Then bubble the records up
                plist[i+novs] = plist[i] ; // shift record back
            }
        }
    }

    // Insert back the overlaps (must reverse order since they were 
    // stored in reverse -> REV+REV = FWD)
    for (i=0; i < novs; i++)
        plist[setstart+i] = ovlprecs[novs-i-1] ; 

    return novs ; 
}

/*
  Tests to see if the two events represent the equivalent condition
  This results when we have a case as shown here:

                

          C                    _ B
           \                   /|
            \                /
             \             /
              \          / 
               \       /
                \    /
               E \ /
                / \
               /    \
              /       \
             /          \
            /             \
           /                \
          /                   \  |
         /                     _\
 
        A                         D

 

  The two lines for each curve have a break in them at the intersection
  point. Thus curve section AEB intersects curve CED right at the common
  point E. This normally results in 4 intersection results: A with C, 
  A with D, B with C, and B with D (the A B and C D intersections are 
  already filtered out by this point). We call these AC, AD, BC, BD for 
  simplicity. Now each of these all represent the same intersection
  event. So we only need deal with one of them when doing the index 
  counting step. 

  Thus we are passed in two indexes I and J and must decide if they 
  represent equivalent events. Each event points to two segments a and
  b, then we proceed as follows. 

  if (I.a == J.a) && (I.b == J.b)
  {
        identical match so return true 
        Note: this condition occurs when we promote the 1.0 overall curve
        event to the 0.0 start segment. Then we end up with these duplicate
        events.
  }

  if (Sequential(I.a, J.a) && Sequential(I.b, J.b))
        return true (matched)

  if (Sequential(I.a, J.a) && (I.b == J.b))
        return true (matched)

  if ((I.a == J.a) && Sequential(I.b, J.b))
        return true (matched)


  thus we should work out the Sequential(I.a, J.a) and the 
  Sequential(I.b, J.b) conditions in advance since they will 
  be required several times in the if testing.


  */

int UEventList::EquivalentEvents(int i, int j)
{

    int sameA, sameB ; 

    // We do all the following tests in order of simplest to most complex
    // to minimize the amount of time spent in this function call.
    if (plist[i].pevent->psna == plist[j].pevent->psna)
        sameA = 1 ; 
    else
        sameA = 0 ; 

    if (plist[i].pevent->psnb == plist[j].pevent->psnb)
        sameB = 1 ; 
    else
        sameB = 0 ; 

    if (sameA && sameB)
        return 1 ; // return match (true)

    int ijAseq, ijBseq ; 


    CS_Curve *pcrv ;

    pcrv = plist[i].pevent->pca ;

    CS_CrvPnt cpi(plist[i].pevent->psna, plist[i].pevent->u1) ; 
    CS_CrvPnt cpj(plist[j].pevent->psna, plist[j].pevent->u1) ; 

    if (pcrv->SequentialSegments(&cpi, &cpj))
    {
        ijAseq = 1 ;
    }
    else
    {
        ijAseq = 0 ;
    }


    if (ijAseq && sameB)
        return 1 ;

    pcrv = plist[i].pevent->pcb ;

    cpi.s = plist[i].pevent->psnb ;
    cpi.u = plist[i].pevent->u2 ; 

    cpj.s = plist[j].pevent->psnb ;
    cpj.u = plist[j].pevent->u2 ; 

    if (pcrv->SequentialSegments(&cpi, &cpj))
    {
        ijBseq = 1 ;
    }
    else
    {
        ijBseq = 0 ;
    }

    if ((sameA && ijBseq) || (ijAseq && ijBseq))
        return 1 ;

    return 0 ; // not equivalent events
}

void UEventList::MergeScanAndDelete(MergeParameters &mp, int nextIDX)
{
    // perhaps a better name for nextIDX is endIDX within this function

    // First check if there is any overlap deletion required.
    // The purpose here is two fold: 1) to merge overlap sections when 
    // the end and start node of two adjacent overlaps occur in the same
    // set then they can both be deleted. This can be detected simply 
    // by testing for two overlap events within the same set. 2) To
    // delete redundant intersection definitions which will occur if
    // an intersection occurs right at the connection point between 
    // line segments. A worst case scenario could have multiple common
    // intersections that must be deleted. See RR-Vol1 pg.173 for diagrams
    // outlining the different conditions.

    // Also see updated notes pgs 53-55 RR-Vol2

    // We also have to keep track of how many events remain in the group
    // since if all events are deleted then we don't want to increment 
    // the setCount variable.
    int i,j ; 
    int keeperCount, deletedCount, setLength ; 

    setLength = nextIDX - mp.setStartIDX ; 

    // The sublist (substitution list) is where we maintain the list 
    // of from-to substitutions. This is used to move overlap events
    // into the proper spot when a intersection record which is part
    // of the overlap group happens to occur before the overlap event.
    int ovlpcnt = 0 ; 
    // int sublen = 0 ; 
    // memset(sublist, 0, sizeof(int[2]) * setLength) ; 

    // Maintain the event sets array. Since this routine is entered for the start
    // of each potentially valid event set, we want to initialize the value here
    eventSets[mp.setCount] = mp.setStartIDX ;

    keeperCount = 0 ; // # events that were keepers
    deletedCount = 0 ; // # of events deleted
    

    // First move all the inverse arcs to the end of the event set
    // This does nothing in the boolean code but is safe to do.
    MoveInvArcsToEnd(mp.setStartIDX, nextIDX) ; 
    ovlpcnt = MoveOverlapsToTop(mp.setStartIDX, nextIDX) ; 

    ////////////////////////////////////////////////////////////////////////
    // POSSIBLE ERROR SOURCE for multiple overlap intersection condition
    ////////////////////////////////////////////////////////////////////////
    // Now if there are two overlaps then we delete them both. Note, this
    // may not always work (although not sure yet) See RR-Vol2 pg 93-94
    // for a discussion of what might happen and how we would have to extend
    // the logic here to refine when exactly we have to delete 2+ overlap
    // events at a single node. (Dealing with this Sept 10,2000)
    // The above has been dealt with but not fully tested yet    

    if (ovlpcnt == 2)
    {
        // The two overlaps must be a start-end pair 
        // Extract the endedness of each section
        // The case where we want to delete the two overlaps
        // occurs when the two segments are also sequential 
        // Thus the psna's must both be sequential before we
        // delete the records 

        // From the sort the two overlaps will be the first and second
        // records
        
        i = mp.setStartIDX ; 
        j = i + 1 ; 

        int endstart = 0 ; // true if == 0x03 at the end
        // Start=0x01, End=0x02

        // Test out section I
        if (plist[i].einfo & UEVENT_STARTPOINT)
            endstart |= 0x01 ; 
        else
            endstart |= 0x02 ; 

        // Test out section J
        if (plist[j].einfo & UEVENT_STARTPOINT)
            endstart |= 0x01 ; 
        else
            endstart |= 0x02 ; 


        // Note the only way two overlap events can be sequential is if 
        // they are end-start events. Note even if the end-start occurs
        // on a segment that reverses on itself, we want to delete the 
        // pair since nothing interesting happens in this case.
        if (endstart == 0x03)
        {   // Then continue testing for OVERLAP end-start deletion
            if (EquivalentEvents(i, j))
            {
                plist[i].einfo |= (UEVENT_OVERLAPDELETED | UEVENT_DELETED) ;
                plist[j].einfo |= (UEVENT_OVERLAPDELETED | UEVENT_DELETED) ;
                deletedCount += 2 ; 
            }
        }
    }
    else if (ovlpcnt > 2)
    {
        CS_FAULTASSERT
        (
            int *abc ; 
            abc = 0 ; 
            *abc = 1 ; 
        ) ; 
    }


    // Logic below is being worked into the actual scan loop. 
    // See RR-Vol2 pp.88-90 for a discussion of what changes were made
    // and why. The overlap record can't be simply moved to the start
    // it has to be moved up based upon the matching set of records 
    // that it is combined with. Also we want to override the XOVER 
    // or TOUCH condition using the overlap record to override the
    // intersection record we are overwriting.
    /*
    else if (ovlpcnt == 1)
    {   // Then this is a valid start or end overlap record so we
        // have to make sure that the first node in the event set
        // is marked as being an overlap type. This is because the
        // first record will never be deleted. 
        if (ovlpIDX[0] != mp.setStartIDX)
        {
            // We need to match the overlap status bits to the 
            // actual overlap record. Thus mask out the overlap data
            // from the actual record and copy those bits only into the 
            // first record.
            plist[mp.setStartIDX].einfo |= 
                plist[ovlpIDX[0]].einfo & 
                (UEVENT_OVERLAP | UEVENT_STARTPOINT | UEVENT_OVERLAPBREVERSE) ; 
        }
    }
    */


    for (i=mp.setStartIDX; i < nextIDX; i++)
    {
        if (plist[i].einfo & UEVENT_INVERTARC)
        {   // We always keep the inverted arc events since they will 
            // never be duplicated
            keeperCount += 1 ; 
        }
        else 
        {   // It's an intersection or an overlap event 
            // so we have to apply the same intersection reduction
            // logic to both record types. Because overlap type records
            // are located first, they have priority and are saved over
            // an equivalent intersection through the use of sublist.

            // Do the intersection reduction logic
            for (int j=i+1; j < nextIDX; j++)
            {
                if (plist[j].einfo & UEVENT_INVERTARC)
                    continue ; // not included in this test

                if (plist[j].einfo & UEVENT_DELETED) 
                    continue ; // don't want to delete it twice

                if (EquivalentEvents(i,j))
                {
                    plist[j].einfo |= UEVENT_DELETED ; 
                    deletedCount++ ; 
                }
            }
            
            // If this event was not deleted previously then it
            // adds to the keeper count
            if (!(plist[i].einfo & UEVENT_DELETED))
                keeperCount += 1 ; 
        }

        if ((keeperCount + deletedCount) == setLength)
            break ; // done
    }

    if (deletedCount == setLength)
    {   // Then we are completely deleting this event set so
        // don't increment the setCount becuase the only events
        // within the set are the two overlaps (which must be 
        // an end and start combination)
        
        // Because this set was completely deleted we want to reset the 
        // last entry in the eventSets array before adjusting setCount
        eventSets[mp.setCount] = -1 ; // mark as undefined
        
        mp.setCount-- ; // decrement here so the increment later
        // has no effect
    }
    
    mp.setStartIDX = nextIDX ; 
    mp.setCount++ ; 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


CS_CurveChain::CS_CurveChain()
{
    status = 0 ; 
}

CS_CurveChain::~CS_CurveChain()
{
    if (pcrv)
        delete pcrv ; // delete the CS_Curve 
    // The default CS_List destructor will get rid of the rest of memory
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

