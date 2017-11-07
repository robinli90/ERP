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
// convexhull.cpp - create the convex hull for a general CS_Curve
// object

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
#include "cs_QuickSort.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#include "cs_offset.h"

#include "cs_chain.h"
#include "cs_convexhull.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif


#define CS_CH_FORWARD       1   // moving in the forward direction
#define CS_CH_BACKWARD      2   // moving in the backward direction




static int compPOINTS(const void *a, const void *b)
{
    CS_POINT *pa = (CS_POINT *)a ; 
    CS_POINT *pb = (CS_POINT *)b ; 

    if (pa->x < pb->x)
        return -1 ; 
    else if (pa->x > pb->x)
        return 1 ; 
    else if (pa->y < pb->y)
        return -1 ; 
    else if (pa->y > pb->y)
        return 1 ; 
    return 0 ; 
}


//! Given an input set of random points generate the convex hull polygon.
/*!
    \param ppnts pointer to array of 2D input points
    \param npnts number of points in the array
    \return convex hull curve (made up of line segments). The calling
    routine must de-allocate the returned curve with the operator delete

    Returns the resultant curve if more than 3 points are passed in
    Note if the 3 points are collinear then the curve returned
    will be 4 line segments  two straight out, and two that walk
    back straight back over the original two. 

    The logic for this code is derived from 
    "Computational Geometry Algorithms and Applications" Springer 1997 
    pgs. 6-7
 */
CS_Curve *CalcHullPoints(CS_POINT *ppnts, int npnts)
{
    if (npnts < 3) 
        return 0 ; 
    qsort(ppnts, npnts, sizeof(CS_POINT), compPOINTS) ; 

    CS_POINT *pupper = new CS_POINT[npnts] ; 
    CS_POINT *plower = new CS_POINT[npnts] ; 
    
    int i, uplen, lowlen ; 

    pupper[0] = ppnts[0] ; 
    pupper[1] = ppnts[1] ; 
    uplen = 2 ; 

    for (i=2; i < npnts; ++i)
    {
        pupper[uplen++] = ppnts[i] ; 
        while ((uplen > 2) && 
               PointsTurnLeft(pupper[uplen-3], pupper[uplen-2], pupper[uplen-1]))
        {   // Delete the middle element pup[uplen-2]
            pupper[uplen-2] = pupper[uplen-1] ; 
            uplen -- ; 
        }
    }


    plower[0] = ppnts[npnts-1] ; 
    plower[1] = ppnts[npnts-2] ; 
    lowlen = 2 ; 

    for (i=npnts-2; i>=0; --i)
    {
        plower[uplen++] = ppnts[i] ; 
        while ((lowlen > 2) && 
               PointsTurnLeft(plower[lowlen-3], plower[lowlen-2], plower[lowlen-1]))
        {   // Delete the middle element pup[uplen-2]
            plower[lowlen-2] = plower[lowlen-1] ; 
            lowlen-- ; 
        }
    }

    // Build the resultant curve
    CS_Curve *pcrv = new CS_Curve ; 
    for (i=0; i < uplen-1; ++i)
        pcrv->Append(new CS_LineSeg(pupper[i], pupper[i+1]), CS_NOENDPOINTADJUSTMENT) ;  

    for (i=0; i < lowlen-1; ++i) ; 
        pcrv->Append(new CS_LineSeg(plower[i], plower[i+1]), CS_NOENDPOINTADJUSTMENT) ; 

    return pcrv ; 
}


static int compCS_CHTestData(const void *a, const void *b)
{
    CS_ListNode *pa = *((CS_ListNode **)a) ;
    CS_ListNode *pb = *((CS_ListNode **)b) ;

    CS_CHTestData *ptda = (CS_CHTestData *)pa->pdata ; 
    CS_CHTestData *ptdb = (CS_CHTestData *)pb->pdata ; 

    if (ptda->u0 < ptdb->u0)
        return -1 ; 
    else if (ptda->u0 > ptdb->u0)
        return 1 ; 
    else if (ptda->u1 < ptdb->u1)
        return -1 ; 
    else if (ptda->u1 > ptdb->u1)
        return 1 ; 
    return 0 ; 
}

static void swapCS_CHTestData(const void *a, const void *b)
{
    CS_ListNode *pa = *((CS_ListNode **)a) ;
    CS_ListNode *pb = *((CS_ListNode **)b) ;
    void *ptmp = pa->pdata ; 
    pa->pdata = pb->pdata ; 
    pb->pdata = ptmp ; 
}

// sorts the data list by u value and then groups these into 
// a data list. If there is no data in the input list then 
// NULL is returned, otherwise the first (smallest u0 set) 
// set is returned. The CS_CHTestDataList must be deallocated
// with ' delete pointerReturned '
CS_CHTestDataList *ExtractFirstDataSet(CS_CHTestDataList &tdlist)
{
    if (tdlist.Length() == 0)
        return 0 ; 

    int i ; 
    CS_ListNode **ptdn = new CS_ListNode*[tdlist.Length() + 2] ; 
    CS_ListNode *pln = tdlist.First() ; 
    i=0 ; 
    while (pln)
    {
        ptdn[i++] = pln ; 
        pln = pln->next ; 
    }

    // First sort the test data by u0 value 
    QuickSort(ptdn, tdlist.Length(), sizeof(CS_ListNode *), 
                    compCS_CHTestData, swapCS_CHTestData) ; 
    delete[] ptdn ; 

    CS_CHTestData *ptd ; 
    CS_CHTestDataList *pwrklist = 0 ; 
    pln = tdlist.First() ; 
    double ulast = -1.0 ; 
    while (pln)
    {
        ptd = tdlist.GetData(pln) ; 
        if (tcomp_NEQ(ptd->u0, ulast))
        {
            if (pwrklist)
                return pwrklist ; 
        }
        ulast = ptd->u0 ; 
        if (!pwrklist)
            pwrklist = new CS_CHTestDataList ;
        pwrklist->Append(*ptd) ; 
        pln = pln->next ; 
    }

    return pwrklist ; 
}




// Returns true if the two segments intersect one another and the 
// intersection points do not fall on the end points of the first
// segment only. If the intersection is at an end point of the 2nd
// segment then true can still be returned. At least one intersection
// point must be within the range (0,1) using tolerance on the 
// first segment to return true.
static bool CrossesFirstSegment(CS_SegPtr psa, CS_SegPtr psb)
{
    CS_IRECList islist ; 
    CS_IREC *pirec ; 
    
    // Do the intersection
    psa->Intersect2D(psb, &islist) ; 

    CS_IRECListItr iri ; 
    for (iri = islist.begin(); iri != islist.end(); iri++)
    {   // If we intersect at anywhere other than the endpoints
        // then don't want to keep the line segment
        pirec = iri->pir ; 
        if (tcomp_NEQ(pirec->cpp[0].u, 0.0) && tcomp_NEQ(pirec->cpp[0].u, 1.0))
        {
            return true ; 
        }
    }

    return false ; 
}


// Upon entry segment 0 and 1 must be oriented CW (since this is the 
// traversal direction around the convex hull perimiter).
// The curves modified are indicated with the mask value that is returned
int CalcHullSegmentARC_ARC(CS_ArcSeg *pseg0, CS_ArcSeg *pseg1, CS_Curve **prescrv) 
{
    CS_POINT pntA, pntB, pntC, pntD ; 
    CS_VECTOR vtB = pseg0->UTangent(1.0) ; 

    pntA = pseg0->StartPoint() ; 
    pntB = pseg0->EndPoint() ; 
    pntC = pseg1->StartPoint() ; 
    pntD = pseg1->EndPoint() ; 

    CS_CHTestDataList tdlist ; 
    CS_CHTestData tdata ; 
    CS_LineSeg tanlns[4] ; // tangent lines in arc-arc testing
    double uv, uv2 ; 
    int i, ntans ; 

    /////////////////////////////////////////////////////
    // See RR-Vol3 pg 99 for this logic (rough outline)
    /////////////////////////////////////////////////////

    /////////////////////////////////////////////////////
    // Check to make sure the segments aren't connected
    /////////////////////////////////////////////////////
    CS_Curve *prcrv ; 
    CS_VECTOR vtC(pseg1->UTangent(0.0)) ; 
    double turnAngle = vtB.TurnAngle(vtC) ;

    if (tcomp_NEQ(turnAngle, -RADIAN180) && 
        tcomp_LEQ(turnAngle, COMPARETOLERANCE * 10))
    {   // Then this is a straight thru or right turn so no need 
        // to do any further testing. 
        return 0 ; 
    }

    ////////////////////////////////////////////////
    // Check if we have to a valid AD bridge line 
    ////////////////////////////////////////////////
    CS_LineSeg lntest ; 
    lntest.sp = pntA ; 
    lntest.ep = pntD ; 

    if ((PointSide(CS_LINE(lntest), pntB) == CS_RIGHTSIDE) &&
        (tcomp_LT(fabs(pseg0->swp), RADIAN180) || tcomp_LT(fabs(pseg1->swp),RADIAN180)) &&
        !CrossesFirstSegment(pseg0, &lntest) &&
        !CrossesFirstSegment(pseg1, &lntest))
    {   // Then we have a valid AD line situation
        *prescrv = new CS_Curve ; 
        (*prescrv)->Append(new CS_LineSeg(pntA, pntD), CS_NOENDPOINTADJUSTMENT) ; 
        return CS_CH_BRIDGEDALL ; 
    }

    ////////////////////////////////////
    // Test the Arc0:Arc1 tangent lines
    ////////////////////////////////////
    // Note: tanlns will be directed from arc0 to arc1
    ntans = CS_CircleCircleTangent(*pseg0, *pseg1, tanlns) ;
    // Check which of the tangent lines to keep
    // Note only the outside tangent lines need to be considered
    for (i=0; (i < ntans) && (i < 2); i++)
    {   
        if (pseg0->PointOnSegment(tanlns[i].sp, &uv) &&
            pseg1->PointOnSegment(tanlns[i].ep, &uv2))
        {   // Then keep this tangent line for testing
            tdata.u0 = uv ; 
            tdata.u1 = uv2 ; 
            // Reverse sp and ep since we started from point C
            tdata.pnt0 = tanlns[i].sp ; 
            tdata.pnt1 = tanlns[i].ep ; 
            tdata.status = 0 ; 
            tdlist.Append(tdata) ; 
        }
    }

    if (tdlist.Length() == 0)
        return 0 ; 

    ////////////////////////////
    ////////////////////////////
    // First stage completed. //
    ////////////////////////////
    ////////////////////////////
    // next want to perform the test data filtering by sorting the 
    // u values on arc0 and taking the minimum u value set and then 
    // extracting the leftmost direction tangent line as the path 
    // to follow. 
    CS_VECTOR vbridge ; 
    CS_CHTestData *ptd, *ptdmin ; 
    
    // Now want the leftmost vector
    // This will be the one with the smallest u0 value
    double u0min = 2.0 ; 
    CS_ListNode *pln = tdlist.First() ; 
    while (pln)
    {
        ptd = tdlist.GetData(pln) ; 
        if (ptd->u0 < u0min)
        {
            u0min = ptd->u0 ; 
            ptdmin = ptd ; 
        }
        pln = pln->next ; 
    }

    /////////////////////////////
    /////////////////////////////
    // Second stage completed. //
    /////////////////////////////
    /////////////////////////////
    // Finally want to trim the arcs if necessary and return
    // the trimmed (or deleted) arcs as well as the bridging 
    // tangent line in the resultant curve.
    int retmask = 0 ; 
    prcrv = new CS_Curve ; 

    // ptdmax points to the bridge line that we have to trim the arcs
    // to (or based on the bridge delete the arcs)
    if (tcomp_GT(ptdmin->u0, 0.0))
    {   // Then want to include section of the first arc
        prcrv->Append(pseg0->Copy(0.0, ptdmin->u0), CS_NOENDPOINTADJUSTMENT) ;
        retmask |= CS_CH_MODFIEDSEG_0 ; 
    }
    else
    {
        retmask |= CS_CH_DELETEDSEG_0 | CS_CH_MODFIEDSEG_0 ;
    }

    // Not sure if we need to do this test, think test can be removed
    // simply add every time.
    prcrv->Append(new CS_LineSeg(ptdmin->pnt0, ptdmin->pnt1), CS_NOENDPOINTADJUSTMENT) ; 
    retmask |= CS_CH_BRIDGECREATED ;

    if (tcomp_LT(ptdmin->u1, 1.0))
    {   // Then want to include section of the first arc
        prcrv->Append(pseg1->Copy(ptdmin->u1, 1.0), CS_NOENDPOINTADJUSTMENT) ;
        retmask |= CS_CH_MODFIEDSEG_1 ; 
    }
    else
    {
        retmask |= CS_CH_DELETEDSEG_1 | CS_CH_MODFIEDSEG_0 ;
    }

    if (prcrv->nodecnt > 0)
        *prescrv = prcrv ; 
    else
        delete prcrv ; 

    return retmask ; 
}


// Upon entry segment 0 and 1 must be oriented CW (since this is the 
// traversal direction around the convex hull perimiter).
// The curves modified are indicated with the mask value that is returned
int CalcHullSegmentARC_LINE(CS_ArcSeg *pseg0, CS_LineSeg *pseg1, CS_Curve **prescrv) 
{
    CS_POINT pntA, pntB, pntC, pntD ; 
    CS_VECTOR vtB = pseg0->UTangent(1.0) ; 

    pntA = pseg0->StartPoint() ; 
    pntB = pseg0->EndPoint() ; 
    pntC = pseg1->StartPoint() ; 
    pntD = pseg1->EndPoint() ; 

    CS_CHTestDataList tdlist ; 
    CS_CHTestData tdata ; 
    CS_LineSeg tanlns[4] ; // tangent lines in arc-arc testing
    double uv ; 
    int i, ntans ; 

    /////////////////////////////////////////////////////
    // See RR-Vol3 pg 99 for this logic (rough outline)
    /////////////////////////////////////////////////////


    ////////////////////////////////////////////////
    // Check if we have a valid AD bridge line 
    ////////////////////////////////////////////////
    CS_VECTOR vtC(pseg1->UTangent(0.0)) ; 

    CS_LineSeg lntest ; 
    lntest.sp = pntA ; 
    lntest.ep = pntD ; 

    if ((PointSide(CS_LINE(lntest), pntB) == CS_RIGHTSIDE) &&
        !CrossesFirstSegment(pseg0, &lntest))
    {   // Then we have a valid AD line situation
        *prescrv = new CS_Curve ; 
        (*prescrv)->Append(new CS_LineSeg(pntA, pntD), CS_NOENDPOINTADJUSTMENT) ; 
        return CS_CH_BRIDGEDALL ; 
    }


    double turnAngle = vtB.TurnAngle(vtC) ;

    if (tcomp_NEQ(turnAngle, -RADIAN180) && tcomp_LEQ(turnAngle, 0.0))
    {   // Then this is a right turn so no need to do 
        // any further testing. 
        return 0 ; 
    }



    ////////////////////////////////////
    // Test the Arc0:pntD tangent lines
    ////////////////////////////////////
    // Note: tanlns will be directed from pntD to arc0
    ntans = CS_PointCircleTangent(pntD, *pseg0, tanlns[0], tanlns[1]) ;
    // Check which of the tangent lines to keep
    for (i=0; i < ntans; i++)
    {   
        if (pseg0->PointOnSegment(tanlns[i].ep, &uv))
        {   // Then so far we want to keep this line
            tdata.u0 = uv ; 
            tdata.u1 = 1.0 ; 
            // Reverse sp and ep since we started from point C
            tdata.pnt0 = tanlns[i].ep ; 
            tdata.pnt1 = tanlns[i].sp ; 
            tdata.status = 0 ; 
            tdlist.Append(tdata) ; 
        }
    }

    if (tdlist.Length() == 1)
    {   // Check if the line segment has been overlayed
        // exactly (tangency calculation tolerance problems
        CS_CHTestData *ptdtmp = tdlist.GetData(tdlist.First()) ; 
        if (tcomp_EQ(ptdtmp->u0, 1.0))
        {   // Then the angle filter above didn't work and 
            return 0 ; 
        }
    }

    if (tdlist.Length() == 0)
        return 0 ; 

    ////////////////////////////
    ////////////////////////////
    // First stage completed. //
    ////////////////////////////
    ////////////////////////////
    // next want to perform the test data filtering by sorting the 
    // u values on arc0 and taking the minimum u value set and then 
    // extracting the leftmost direction tangent line as the path 
    // to follow. 
    CS_VECTOR vbridge ; 
    CS_CHTestData *ptd, *ptdmin ; 
    
    // Now want the leftmost vector
    // This will be the one with the smallest u0 value
    double u0min = 2.0 ; 
    CS_ListNode *pln = tdlist.First() ; 
    while (pln)
    {
        ptd = tdlist.GetData(pln) ; 
        if (ptd->u0 < u0min)
        {
            u0min = ptd->u0 ; 
            ptdmin = ptd ; 
        }
        pln = pln->next ; 
    }

    /////////////////////////////
    /////////////////////////////
    // Second stage completed. //
    /////////////////////////////
    /////////////////////////////
    // Finally want to trim the arcs if necessary and return
    // the trimmed (or deleted) arcs as well as the bridging 
    // tangent line in the resultant curve.
    int retmask = 0 ; 
    CS_Curve *prcrv ; 
    prcrv = new CS_Curve ; 

    // ptdmax points to the bridge line that we have to trim the arcs
    // to (or based on the bridge delete the arcs)
    if (tcomp_GT(ptdmin->u0, 0.0))
    {   // Then want to include section of the first arc
        prcrv->Append(pseg0->Copy(0.0, ptdmin->u0), CS_NOENDPOINTADJUSTMENT) ;
        retmask |= CS_CH_MODFIEDSEG_0 ; 
    }
    else
    {
        retmask |= CS_CH_DELETEDSEG_0 | CS_CH_MODFIEDSEG_0 ;
    }

    // Not sure if we need to do this test, think test can be removed
    // simply add every time.
    prcrv->Append(new CS_LineSeg(ptdmin->pnt0, ptdmin->pnt1), CS_NOENDPOINTADJUSTMENT) ; 
    retmask |= CS_CH_BRIDGECREATED | CS_CH_MODFIEDSEG_1 | CS_CH_DELETEDSEG_1;

    if (prcrv->nodecnt > 0)
        *prescrv = prcrv ; 
    else
        delete prcrv ; 

    return retmask ; 
}



// Upon entry segment 0 and 1 must be oriented CW (since this is the 
// traversal direction around the convex hull perimiter).
// The curves modified are indicated with the mask value that is returned
int CalcHullSegmentLINE_ARC(CS_LineSeg *pseg0, CS_ArcSeg *pseg1, CS_Curve **prescrv) 
{
    CS_POINT pntA, pntB, pntC, pntD ; 
    CS_VECTOR vtB = pseg0->UTangent(1.0) ; 

    pntA = pseg0->StartPoint() ; 
    pntB = pseg0->EndPoint() ; 
    pntC = pseg1->StartPoint() ; 
    pntD = pseg1->EndPoint() ; 

    CS_CHTestDataList tdlist ; 
    CS_CHTestData tdata ; 
    CS_LineSeg tanlns[4] ; // tangent lines in arc-arc testing
    double uv ; 
    int i, ntans ; 

    /////////////////////////////////////////////////////
    // See RR-Vol3 pg 99 for this logic (rough outline)
    /////////////////////////////////////////////////////

    /////////////////////////////////////////////////////
    // Check to make sure the segments aren't connected
    /////////////////////////////////////////////////////
    CS_VECTOR vtC(pseg1->UTangent(0.0)) ; 
    double turnAngle = vtB.TurnAngle(vtC) ;

    if (tcomp_NEQ(turnAngle, -RADIAN180) && tcomp_LEQ(turnAngle, 0.0))
    {   // Then this is a straight thru or right turn so no need 
        // to do any further testing. 
        return 0 ; 
    }

    ////////////////////////////////////////////////
    // Check if we have to a valid AD bridge line 
    ////////////////////////////////////////////////
    CS_LineSeg lntest ; 
    lntest.sp = pntA ; 
    lntest.ep = pntD ; 

    if ((PointSide(CS_LINE(lntest), pntB) == CS_RIGHTSIDE) &&
        !CrossesFirstSegment(pseg1, &lntest))
    {   // Then we have a valid AD line situation
        *prescrv = new CS_Curve ; 
        (*prescrv)->Append(new CS_LineSeg(pntA, pntD), CS_NOENDPOINTADJUSTMENT) ; 
        return CS_CH_BRIDGEDALL ; 
    }

    ////////////////////////////////////
    // Test the Arc0:pntD tangent lines
    ////////////////////////////////////
    // Note: tanlns will be directed from pntD to arc0
    ntans = CS_PointCircleTangent(pntA, *pseg1, tanlns[0], tanlns[1]) ;
    // Check which of the tangent lines to keep
    for (i=0; i < ntans; i++)
    {   
        if (pseg1->PointOnSegment(tanlns[i].ep, &uv))
        {   // Then so far we want to keep this line
            tdata.u0 = 0.0 ; 
            tdata.u1 = uv ; 
            // Reverse sp and ep since we started from point C
            tdata.pnt0 = tanlns[i].sp ; 
            tdata.pnt1 = tanlns[i].ep ; 
            tdata.status = 0 ; 
            tdlist.Append(tdata) ; 
        }
    }

    if (tdlist.Length() == 1)
    {   // Check if the line segment has been overlayed
        // exactly (tangency calculation tolerance problems
        CS_CHTestData *ptdtmp = tdlist.GetData(tdlist.First()) ; 
        if (tcomp_EQZ(ptdtmp->u1))
        {   // Then the angle filter above didn't work and 
            return 0 ; 
        }
    }

    if (tdlist.Length() == 0)
        return 0 ; 

    ////////////////////////////
    ////////////////////////////
    // First stage completed. //
    ////////////////////////////
    ////////////////////////////
    // next want to perform the test data filtering by sorting the 
    // u values on arc1 and taking the maximum u1 value set and then 
    // extracting the leftmost direction tangent line as the path 
    // to follow. 
    CS_VECTOR vbridge ; 
    CS_CHTestData *ptd, *ptdmax ; 
    
    // Now want the leftmost vector
    // This will be the one with the smallest u0 value
    double u0max = -1.0 ; 
    CS_ListNode *pln = tdlist.First() ; 
    while (pln)
    {
        ptd = tdlist.GetData(pln) ; 
        if (ptd->u1 > u0max)
        {
            u0max = ptd->u1 ; 
            ptdmax = ptd ; 
        }
        pln = pln->next ; 
    }

    /////////////////////////////
    /////////////////////////////
    // Second stage completed. //
    /////////////////////////////
    /////////////////////////////
    // Finally want to trim the arcs if necessary and return
    // the trimmed (or deleted) arcs as well as the bridging 
    // tangent line in the resultant curve.
    int retmask = 0 ; 
    CS_Curve *prcrv ; 
    prcrv = new CS_Curve ; 

    prcrv->Append(new CS_LineSeg(ptdmax->pnt0, ptdmax->pnt1), CS_NOENDPOINTADJUSTMENT) ; 
    retmask |= CS_CH_BRIDGECREATED | CS_CH_MODFIEDSEG_0 | CS_CH_DELETEDSEG_0 ;

    // ptdmax points to the bridge line that we have to trim the arcs
    // to (or based on the bridge delete the arcs)
    if (tcomp_LT(ptdmax->u1, 1.0))
    {   // Then want to include section of the first arc
        prcrv->Append(pseg1->Copy(ptdmax->u1, 1.0), CS_NOENDPOINTADJUSTMENT) ;
        retmask |= CS_CH_MODFIEDSEG_1 ; 
    }
    else
    {
        retmask |= CS_CH_DELETEDSEG_1 | CS_CH_MODFIEDSEG_1 ;
    }


    if (prcrv->nodecnt > 0)
        *prescrv = prcrv ; 
    else
        delete prcrv ; 

    return retmask ; 
}


// The line segment pointers passed in must be directed from 0 to 1 such that
// pseg0->End == pseg1->Start. Otherwise the logic becomes extremely messy
// to deal with. Thus the curves are connected and the only test required
// for lines is to see if they make a left turn in which case both segments
// are deleted and the bridge goes from pseg0->Start to pseg1->End
// The curves modified are indicated with the mask value that is returned
int CalcHullSegmentLINE_LINE(CS_LineSeg *pseg0, CS_LineSeg *pseg1, CS_Curve **prescrv) 
{
    if (PointSide(CS_LINE(*pseg0), pseg1->ep) != CS_RIGHTSIDE)
    {   // Then delete the segments 
        CS_Curve *pcrv = new CS_Curve ; 
        pcrv->Append(new CS_LineSeg(pseg0->sp, pseg1->ep)) ; 
        *prescrv = pcrv ; 
        return CS_CH_BRIDGEDALL ; 
    }
    return 0 ; 
}

int CalcHullSegment(CS_SegPtr pseg0, CS_SegPtr pseg1, CS_Curve **prescrv) 
{
    int retval = 0 ; 
    if (pseg0->SegmentType() == CS_Segment::ARC_TYPE)
    {
        if (pseg1->SegmentType() == CS_Segment::ARC_TYPE)
        {   // ARC-ARC case
            retval = CalcHullSegmentARC_ARC((CS_ArcSeg *)pseg0, (CS_ArcSeg *)pseg1, prescrv) ; 
        }
        else
        {   // ARC-LINE
            retval = CalcHullSegmentARC_LINE((CS_ArcSeg *)pseg0, (CS_LineSeg *)pseg1, prescrv) ; 
        }
    }
    else if(pseg0->SegmentType() == CS_Segment::LINE_TYPE)
    {
        if (pseg1->SegmentType() == CS_Segment::ARC_TYPE)
        {   // ARC-ARC case
            retval = CalcHullSegmentLINE_ARC((CS_LineSeg *)pseg0, (CS_ArcSeg *)pseg1, prescrv) ; 
        }
        else
        {   // LINE-LINE
            retval = CalcHullSegmentLINE_LINE((CS_LineSeg *)pseg0, (CS_LineSeg *)pseg1, prescrv) ; 
        }
    }
    return retval ; 
}


int DeleteInnerLoops(CS_Curve *pcrv, int curveDirection)
{

    CS_IRECList islist ; 
    if (!pcrv->SelfIntersect(CW, islist))
        return 0 ; 

    // Make sure the map for this curve is empty
    pcrv->pcnmap->clear() ; 

    CS_Chain chain ; 
    // create the IntersectData record within pcrv
    chain.AddIntersectDataToCurves(islist) ; 
    chain.SetFwdRevPointers(pcrv) ; 

    // The pid structure now points to CS_ISRInfo records
    int innercount, lastinnercount ; 
    CS_CurveSet chaincrvs ; 

    chain.ChainAllLoops(pcrv->pcnmap, chaincrvs, CS_Chain::LEFT) ;

    // Find the outermost loop. Do this by taking the first
    // curve that is not inside any of the other curves
    CS_Curve *pc, *pcb ; 

    CS_CurveVecItr pln ; 
    chaincrvs.InitIterator() ; 
    innercount = 0 ; 
    while (pc = chaincrvs.NextCurve()) 
    {
        lastinnercount = innercount ; 
        for (pln = chaincrvs.crvlist.begin(); pln != chaincrvs.crvlist.end(); pln++)
        {
            pcb = *pln ; 
            if (pc == pcb)
                continue ; 
            // Test if pc is inside pcb
            if (pcb->PointInside(pc->UPoint(0.1)))
            {
                innercount++ ; 
                pcb->statflags |= CS_CURVEINSIDE ;
            }
        }
        
        if (lastinnercount == innercount)
            break ; 
    }

    if (pc)
    {
        pcrv->Destroy() ;
        pcrv->CopyCurve(*pc) ; 
    }
        
    return innercount ; 
}

// The segments within the curve sets are processed to generate 
// a convex hull contour. The CS_Curves need not be closed or
// well defined for the process to function, as all the segments
// are extracted and preprocessed as the first step in the 
// convex hull procedure. The return value is a curve defining
// the convex hull. If no data is passed in then NULL is 
// returned.
// TO DO - change everything so that it works with CCW as the 
// base curve direction (since this is the default everywhere else)
CS_Curve *CS_ConvexHull(CS_Curve &crv)
{
    if (crv.nodecnt < 2)
        return 0 ; 

    int retval ; 
    CS_Curve *phullcrv ; 
    CS_SegPtr psn ;
    CS_SegPtr psn0 ;
    CS_SegPtr psn1 ; 
    CS_ArcSeg *parc ; 

    CS_Curve *prescrv = new CS_Curve ; 
    // copy the curve but convert CCW arcs to lines
    crv.SetDirection(CW) ; 
    psn = crv.pStart ; 
    while (psn)
    {
        if (psn->SegmentType() == CS_Segment::ARC_TYPE)
        {
            parc = (CS_ArcSeg *)psn ; 
            if (parc->swp > 0)
            {   // Then this is a CCW arc so convert to a line
                prescrv->Append(
                    new CS_LineSeg(parc->StartPoint(), parc->EndPoint()),
                    CS_NOENDPOINTADJUSTMENT) ; 
            }
            else
            {
                prescrv->Append(psn->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
            }
        }
        else
        {
            prescrv->Append(psn->Copy(), CS_NOENDPOINTADJUSTMENT) ;
        }
        psn = psn->next ; 
    }

    // Now walk through all the segments generating the 
    // convex hull from the set of curves.

    bool convexhullChanged  ; 

    do 
    {   // Repeat entire process until the convex hull stabilizes
        convexhullChanged = false ; 
        psn = prescrv->pStart; 
        while (psn && (prescrv->nodecnt > 2))
        {
            phullcrv = 0 ; 
            psn0 = psn ; 
            psn1 = prescrv->Next(psn) ; 
            retval = CalcHullSegment(psn0, psn1, &phullcrv) ;
            if (retval)
            {   // Then have to merge in the new section
                convexhullChanged = true ; 
                psn = psn0 ; 
                while (phullcrv->pStart)
                {
                    psn = prescrv->InsertAfter(psn, 
                                               phullcrv->pStart->Copy(), 
                                               CS_NOENDPOINTADJUSTMENT) ; 
                    phullcrv->Delete(phullcrv->pStart) ; 
                }

                psn = psn0->prev ; 

                if (retval && CS_CH_MODFIEDSEG_0)
                    prescrv->Delete(psn0) ; 
                if (retval && CS_CH_MODFIEDSEG_1)
                    prescrv->Delete(psn1) ; 

                if (!psn)
                    psn = prescrv->pStart ; 
            }
            else
                psn = psn->next ; 
        }

        // Now test for self intersecting loops in the result curve
        if (convexhullChanged)
        {
            DeleteInnerLoops(prescrv, CW) ;
        }
    }  while (convexhullChanged) ; 

    if (prescrv->nodecnt > 1)
        prescrv->ConnectEndPoints() ; 

    return prescrv ;
}


