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
// cadfuncs.cpp - Geometric processing routines related to CS_Curve's,
//  specifically these are CAD user interface like operations


#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_cadfuncs.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)	
#else
#define CS_DEBUG(a)
#endif


// Function prototypes local to this file only
static int extLineLine(CS_LineSeg *psa, CS_POINT &ppa,
                       CS_LineSeg *psb, CS_POINT &ppb,
                       int mode = CS_EXTRIM_BOTH_SEGMENTS) ;
static int extLineArc(CS_LineSeg *psa, CS_POINT &ppa,
                      CS_ArcSeg *psb, CS_POINT &ppb,
                      int mode = CS_EXTRIM_BOTH_SEGMENTS) ;
static int extArcArc(CS_ArcSeg *psa, CS_POINT &ppa,
                     CS_ArcSeg *psb, CS_POINT &ppb,
                     int mode = CS_EXTRIM_BOTH_SEGMENTS) ;
static void extendArcParameters(CS_ArcSeg *paseg, CS_POINT &ipnt, 
                         CS_POINT &asspnt, CS_POINT &aepnt, 
                         CS_POINT &ppnt) ;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Extend And Trim Two Curve Segments
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Takes two curve segments and extends them to intersect or trims
// them at the intersect point. The curve pick points on the segments
// are used to decide which intersect to trim at (nearest to pick point)
// in those situations when there are two intersections to decide from
// The two segments are modified to represent the final result. An error
// code is returned if something goes wrong
int CS_ExTrimEndpoints(CS_SegPtr sega, CS_POINT &ppa, 
                       CS_SegPtr segb, CS_POINT &ppb) 
{
    if (sega->SegmentType() == CS_Segment::LINE_TYPE && 
        segb->SegmentType() == CS_Segment::LINE_TYPE)
    {
        return extLineLine((CS_LineSeg *)sega, ppa, (CS_LineSeg *)segb, ppb) ; 
    }
    else if (sega->SegmentType() == CS_Segment::LINE_TYPE &&
             segb->SegmentType() == CS_Segment::ARC_TYPE)
    {
        return extLineArc((CS_LineSeg *)sega, ppa, (CS_ArcSeg *)segb, ppb) ; 
    }
    else if (sega->SegmentType() == CS_Segment::ARC_TYPE &&
             segb->SegmentType() == CS_Segment::LINE_TYPE)
    {
        return extLineArc((CS_LineSeg *)segb, ppb, (CS_ArcSeg *)sega, ppa) ; 
    }
    else if (sega->SegmentType() == CS_Segment::ARC_TYPE &&
             segb->SegmentType() == CS_Segment::ARC_TYPE)
    {
        return extArcArc((CS_ArcSeg *)sega, ppa, (CS_ArcSeg *)segb, ppb) ; 
    }
    return 1 ; // unhandled curve type(s) passed in 
}

int CS_ExTrimFirstEndpoint(CS_SegPtr sega, CS_POINT &ppa, 
                           CS_SegPtr segb, CS_POINT &ppb) 
{
    if (sega->SegmentType() == CS_Segment::LINE_TYPE && 
        segb->SegmentType() == CS_Segment::LINE_TYPE)
    {
        return extLineLine((CS_LineSeg *)sega, ppa, (CS_LineSeg *)segb, ppb,
                            CS_EXTRIM_1ST_SEGMENT) ;
    }
    else if (sega->SegmentType() == CS_Segment::LINE_TYPE &&
             segb->SegmentType() == CS_Segment::ARC_TYPE)
    {
        return extLineArc((CS_LineSeg *)sega, ppa, (CS_ArcSeg *)segb, ppb,
                            CS_EXTRIM_1ST_SEGMENT) ;
    }
    else if (sega->SegmentType() == CS_Segment::ARC_TYPE &&
             segb->SegmentType() == CS_Segment::LINE_TYPE)
    {
        return extLineArc((CS_LineSeg *)segb, ppb, (CS_ArcSeg *)sega, ppa,
                            CS_EXTRIM_2ND_SEGMENT) ;
    }
    else if (sega->SegmentType() == CS_Segment::ARC_TYPE &&
             segb->SegmentType() == CS_Segment::ARC_TYPE)
    {
        return extArcArc((CS_ArcSeg *)sega, ppa, (CS_ArcSeg *)segb, ppb,
                            CS_EXTRIM_1ST_SEGMENT) ;

    }
    return 1 ; // unhandled curve type(s) passed in 
}


static int extLineLine(CS_LineSeg *psa, CS_POINT &ppa,
                       CS_LineSeg *psb, CS_POINT &ppb,
                       int mode)
{
    int nisects ; 
    CS_LINE la(*psa) ; 
    CS_LINE lb(*psb) ; 
    CS_POINT ipnt ; 

    nisects = la.Intersect2D(lb, ipnt) ;
    if (nisects != 1)
    {   // The lines are parallel or collinear and so we can't do this 
        // operation
        if (nisects > 1)
            return 3 ; 
        return 2 ; 
    }
    
    // There is one intersection point, now must decide if we are extending
    // or triming the line segments
    // Need to get the parametric u value of the point with respect to the 
    // two curves
    double ua, ub ; 
    double uppa, uppb ; 
    
    // Get uparms of the intersection point
    psa->UParmClosestToPoint(ipnt, &ua) ;
    psb->UParmClosestToPoint(ipnt, &ub) ;

    psa->UParmClosestToPoint(ppa, &uppa) ;
    psb->UParmClosestToPoint(ppb, &uppb) ;

    // If the u value is < 0 we move sp to ipnt
    // If the u value is > 1 we move the ep to ipnt
    // If the u value is in the range [0,1] then we are trimming the line.
    //      in this case we have to decide if we are removing the start of
    //      the line segment or the end. We want to keep the section of the
    //      line nearest to the pickpoint. See Notes RR-Vol1 pgs 114-116

    // Adjust line segment a
    if (mode & CS_EXTRIM_1ST_SEGMENT)
    {
        if (ua < 0 || uppa >= ua)
            psa->sp = ipnt ; 
        else 
            psa->ep = ipnt ; 
    }

    // Adjust line segment b
    if (mode & CS_EXTRIM_2ND_SEGMENT)
    {
        if (ub < 0 || uppb >= ub)
            psb->sp = ipnt ; 
        else 
            psb->ep = ipnt ; 
    }

    return 0 ; 
}   


static int extLineArc(CS_LineSeg *psa, CS_POINT &ppa,
                      CS_ArcSeg *psb, CS_POINT &ppb,
                      int mode)
{
    int nisects ; 
    CS_LINE la(*psa) ; 
    CS_CIRCLE cb(*psb) ; 
    CS_POINT ipnt1, ipnt2, ipnt ; 

    nisects = la.Intersect2D(cb, ipnt1, ipnt2) ;
    if (nisects == 0)
    {   // No intersections, nothing to do
        return 2 ; 
    }
    
    // There are 1 or 2 intersection points, must decide if we are extending
    // or triming the curve segments
    if (nisects == 1)
    {   // Tangent intersect, only have to consider one intersect point
        ipnt = ipnt1 ; 
    }
    else
    {   // 2 intersections
        if (DistanceSquared(ipnt1, ppa) < DistanceSquared(ipnt2, ppa))
            ipnt = ipnt1 ; 
        else
            ipnt = ipnt2 ; 
    }

    // Need to get the parametric u value of the point with respect to the 
    // two curves
    double ua, uppa ; 
    
    // Get uparms of the intersection point
    psa->UParmClosestToPoint(ipnt, &ua) ;
    psa->UParmClosestToPoint(ppa, &uppa) ;


    // For line segment:
    // If the u value is < 0 we move sp to ipnt
    // If the u value is > 1 we move the ep to ipnt
    // If the u value is in the range [0,1] then we are trimming the line.
    //      in this case we have to decide if we are removing the start of
    //      the line segment or the end. We want to keep the section of the
    //      line nearest to the pickpoint. See Notes RR-Vol1 pgs 114-116
    // Adjust line segment
    if (mode & CS_EXTRIM_1ST_SEGMENT)
    {
        if (ua < 0 || uppa >= ua)
            psa->sp = ipnt ; 
        else 
            psa->ep = ipnt ; 
    }


    if (mode & CS_EXTRIM_2ND_SEGMENT)
    {
        // Adjust the arc segment
        int oldarcdir = CCW ; 

        if (psb->ArcDir() == CW)
        {   // Then the arc is reversed. Set it to be CCW during these calculations
            oldarcdir = CW ; 
            psb->SetCCW() ;
        }
    
        CS_POINT aspnt = psb->StartPoint() ; 
        CS_POINT aepnt = psb->EndPoint() ; 

        // We want to keep the section of the arc that has the pick point on it
        // Thus check the pick point angle and create two arcs, sp->ip and ip->ep
        // then test to see which of these two arcs the pick point is on and keep
        // that arc. This test only works if the intersection point is on the 
        // sweep of the original arc. If the intersection point is not on the
        // sweep of the original arc, then we want to move the end point of the
        // arc that is closest to the intersection point.


        // Calculate the angle of the pick point now.
        CS_VECTOR vcip(psb->ctr, ipnt) ; 
        double vciangle = vcip.AngleXY() ; 
    
        if (psb->AngleOnSweep(vciangle))
        {
            CS_VECTOR vcpp(psb->ctr, ppb) ; 
            double vangle = vcpp.AngleXY() ; 

            CS_ArcSeg asi ; 
            CS_ArcSeg aie ; 

            asi = *psb ; 
            aie = *psb ; 
    
            asi.SetSPEP(aspnt, ipnt, CCW) ; 
            aie.SetSPEP(ipnt, aepnt, CCW) ; 
            if (aie.AngleOnSweep(vangle))
            {   // Then we will move the start point of the arc to the 
                // intersection point
                *psb = aie ; 
            }
            else
            {   // Pick point was closest to the end point of the arc
                *psb = asi ;
            }
        }
        else
        {   // The intersection point is not on the original arc and thus
            // we are extending one end of the arc to the intersection point.
            // Extend the end closest to the pick point
            if (DistanceSquared(aspnt, ppb) < DistanceSquared(aepnt, ppb))
            {   // Then move the start point of the arc
                psb->SetSPEP(ipnt, aepnt, CCW) ; 
            }
            else
            {
                psb->SetSPEP(aspnt, ipnt, CCW) ; 
            }
        }

        if (oldarcdir == CW)
            psb->SetCW() ; 
    }

    return 0 ; 
}

// Steals some logic from the LineArc case
static int extArcArc(CS_ArcSeg *psa, CS_POINT &ppa,
                     CS_ArcSeg *psb, CS_POINT &ppb,
                     int mode)
{
    int nisects ; 
    CS_CIRCLE ca(*psa) ; 
    CS_CIRCLE cb(*psb) ; 
    CS_POINT ipnt1, ipnt2, ipnt ; 

    nisects = ca.Intersect2D(cb, ipnt1, ipnt2) ;
    if (nisects == 0)
    {   // No intersections, nothing to do
        return 2 ; 
    }

    // There are 1 or 2 intersection points, must decide if we are extending
    // or triming the curve segments

    int oldadir, oldbdir ; 

    CS_POINT aspnt, aepnt, bspnt, bepnt ; 
    // Orient both arcs CCW and then switch back at the end
    oldadir = psa->ArcDir() ; 
    oldbdir = psb->ArcDir() ; 

    psa->SetCCW() ; 
    psb->SetCCW() ; 
        
    aspnt = psa->StartPoint() ; 
    aepnt = psa->EndPoint() ; 
    bspnt = psb->StartPoint() ; 
    bepnt = psb->EndPoint() ; 

    if (nisects == 1)
    {   // Tangent intersect, only have to consider one intersect point
        ipnt = ipnt1 ; 
    }
    else if (nisects == 2)
    {   // 2 intersections

        // Figure out which intersect point we want to work with
        // The first arc picked is the one that controls which intersection
        // point will be used
        CS_ArcSeg as1, as2 ; 
        as1 = *psa ; 
        as2 = *psa ; 
        
        if (DistanceSquared(ppa, aspnt) < 
            DistanceSquared(ppa, aepnt)) 
        {   // Then walk along in the CW direction to find the intersection 
            // going from the sp on arc a
            as1.SetSPEP(ppa, ipnt1, CW) ; 
            as2.SetSPEP(ppa, ipnt2, CW) ; 
            if (as1.ArcLength() < as2.ArcLength())
                ipnt = ipnt1 ; 
            else 
                ipnt = ipnt2 ; 
        }
        else
        {   // Walk along arc CCW to find the intersection point
            // going from ep on arc a
            as1.SetSPEP(ppa, ipnt1, CCW) ; 
            as2.SetSPEP(ppa, ipnt2, CCW) ; 
            if (as1.ArcLength() < as2.ArcLength())
                ipnt = ipnt1 ; 
            else 
                ipnt = ipnt2 ; 
        }
    }
    else if (nisects == 3)
    {   // Then we are dealing with two arcs that have identical rad and 
        // center points. In this case we simply want to extend the arcs
        // so that their end points touch (we'll have 2 arcs that look like
        // a single arc segment)
        // This logic works out to be same as above, except the intesect 
        // point is simply one of the arc end points. Use the arc 1 end
        // point nearest to ppa
        if (DistanceSquared(ppa, aspnt) < 
            DistanceSquared(ppa, aepnt)) 
        {   // Then walk along in the CW direction to find the intersection 
            // going from the sp on arc a
            ipnt = aspnt ; 
        }
        else
        {
            ipnt = aepnt ; 
        }
    }
    else
    {
        // Some error occured in the intersection routine
        return 4 ; 
    }

    if (mode & CS_EXTRIM_1ST_SEGMENT)
    {
        extendArcParameters(psa, ipnt, aspnt, aepnt, ppa) ; 
        if (oldadir == CW)
            psa->SetCW() ; 
    }

    if (mode & CS_EXTRIM_2ND_SEGMENT)
    {
        extendArcParameters(psb, ipnt, bspnt, bepnt, ppb) ; 
        if (oldbdir == CW)
            psb->SetCW() ; 
    }

    return 0 ; 
}

static void extendArcParameters(CS_ArcSeg *paseg, CS_POINT &ipnt, 
                                CS_POINT &aspnt, CS_POINT &aepnt, 
                                CS_POINT &ppnt)
{
    CS_VECTOR vcip(paseg->ctr, ipnt) ; 
    double vciangle = vcip.AngleXY() ; 
    
    if (paseg->AngleOnSweep(vciangle))
    {
        CS_VECTOR vcpp(paseg->ctr, ppnt) ; 
        double vangle = vcpp.AngleXY() ; 
        
        CS_ArcSeg asi ; 
        CS_ArcSeg aie ; 
        
        asi = *paseg ; 
        aie = *paseg ; 
        
        asi.SetSPEP(aspnt, ipnt, CCW) ; 
        aie.SetSPEP(ipnt, aepnt, CCW) ; 
        if (aie.AngleOnSweep(vangle))
        {   // Then we will move the start point of the arc to the 
            // intersection point
            *paseg = aie ; 
        }
        else
        {   // Pick point was closest to the end point of the arc
            *paseg = asi ;
        }
    }
    else
    {   // The intersection point is not on the original arc and thus
        // we are extending one end of the arc to the intersection point.
        // Extend the end closest to the pick point
        if (DistanceSquared(aspnt, ppnt) < DistanceSquared(aepnt, ppnt))
        {   // Then move the start point of the arc
            paseg->SetSPEP(ipnt, aepnt, CCW) ; 
        }
        else
        {
            paseg->SetSPEP(aspnt, ipnt, CCW) ; 
        }
    }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// Returns the point on the segment that is furthest away from the line
// See RR-Vol3 pg 118. The side parameter determines whether or not we
// want points on the left side only (CS_LEFTSIDE), right side only 
// (CS_RIGHTSIDE), or either side (CS_BOTHSIDES) which is the default.
CS_POINT FurthestPointOnSegToLine(CS_SegPtr ptestseg, CS_LINE &line, int side) 
{
    CS_POINT testpnt[4] ; 
    CS_POINT nearpnt[4] ; 
    int i, npnts ; 

    // Assign all the necessary critical points
    npnts = 0 ; 
    if (ptestseg->SegmentType() == CS_Segment::ARC_TYPE)
    {
        CS_ArcSeg *pseg = (CS_ArcSeg *)ptestseg ;
        CS_POINT cp ; 
        testpnt[npnts++] = pseg->StartPoint() ; 
        testpnt[npnts++] = pseg->EndPoint() ;
        cp = line.NearestPoint(pseg->ctr) ; 
        CS_VECTOR vca(cp, pseg->ctr) ; 
        if (vca.Mag() == 0)
        {
            vca = CS_VECTOR(line.sp, line.ep) ; 
            vca = vca.RightPerp() ; 
        }
        vca = vca.Unit() ; 
        // Have to test if these points are actually on the arc
        if (pseg->AngleOnSweep(vca.AngleXY()))
            testpnt[npnts++] = pseg->ctr + (vca * pseg->rad) ; 
        vca.Reverse() ; 
        if (pseg->AngleOnSweep(vca.AngleXY()))
            testpnt[npnts++] = pseg->ctr + (vca * pseg->rad) ; 
            
    }
    else if (ptestseg->SegmentType() == CS_Segment::LINE_TYPE)
    {
        testpnt[npnts++] = ptestseg->StartPoint() ; 
        testpnt[npnts++] = ptestseg->EndPoint() ;
    }

    for (i=0 ; i < npnts; i++)
        nearpnt[i] = line.NearestPoint(testpnt[i]) ; 

    // Extract the one we want
    CS_POINT leftmostPnt, rightmostPnt ; 
    double d ; 
    double leftmostDist = 0.0 ; 
    double rightmostDist = 0.0 ; 
    leftmostPnt = CS_LineSeg(line.sp, line.ep).MidPoint() ; 
    rightmostPnt = leftmostPnt ; 
    
    for (i=0; i < npnts; i++)
    {
        d = CS_VECTOR(testpnt[i], nearpnt[i]).Mag() ; 
        if (PointSide(line, testpnt[i]) == CS_LEFTSIDE)
        {
            if (d > leftmostDist)
            {
                leftmostDist = d ; 
                leftmostPnt = testpnt[i] ; 
            }
        }
        else
        {
            if (d > rightmostDist)
            {
                rightmostDist = d ; 
                rightmostPnt = testpnt[i] ; 
            }
        }
    }

    if (side == CS_BOTHSIDES)
    {
        if (rightmostDist > leftmostDist)
            return rightmostPnt ; 
        return leftmostPnt ; 
    }
    else if (side == CS_RIGHTSIDE)
        return rightmostPnt ; 
    return leftmostPnt ; 
}


// Return the closest points on two lines. 
int CS_LineLineNearestPoints(CS_LINE &l1, CS_LINE &l2, double &u1, double &u2)
{
    // Convert the lines to parametric form and then call function below. 
    CS_VECTOR v1(l1.sp, l1.ep) ; 
    v1 = v1.Unit() ; 
    CS_VECTOR v2(l2.sp, l2.ep) ; 
    v2 = v2.Unit() ; 
    // Note: unitizing the vectors is not really required, but may help
    // avoid cases where the lines are not well behaved (2 points very close
    // together for example). 
    return CS_LineLineNearestPoints(l1.sp, v1, l2.sp, v2, u1, u2) ; 
}


// Same as above but using parametric line representation
int CS_LineLineNearestPoints(CS_POINT &P0, CS_VECTOR &vu, 
                             CS_POINT &Q0, CS_VECTOR &vv, 
                             double &up, double &uq)
{
    // First see if the two lines intersect
    CS_LINE l1(P0, P0+vu) ; 
    CS_LINE l2(Q0, Q0+vv) ; 
    CS_POINT ip ; 
    double u1 = 0 ; 
    double u2 = 0 ; 

    switch(l1.Intersect(l2, u1, u2))
    {
        case 1 : // lines intersect at a point
            up = u1 ; 
            uq = u2 ; 
            return CS_NONCOLLINEAR ; 
        case 2 :
            up = u1 ; 
            uq = u2 ; 
            return CS_COLLINEAR ; 
    }
    
    // Else they don't intersect so find the closest point of approach
    // on the two lines. 


    // For two lines P(s) and Q(t) where P(s) = P0 + s.u where s is the 
    // parameter and u is a unit vector in the direction of the line P0
    // and similarily Q(t) = Q0 + t.v where v is a vector in the direcion 
    // of the line Q. 
    //  See Geom Algo's RR-Vol4 pg 142. 
    CS_VECTOR wo(P0, Q0) ; 
    double a =  CS_DotProduct(vu, vu) ; 
    double b = -CS_DotProduct(vu, vv) ; 
    double c = -CS_DotProduct(vv, vv) ; 
    double d = -CS_DotProduct(vu, wo) ; 
    double e = -CS_DotProduct(vv, wo) ; 

    double D = a*c - b*b ;
    if (tcomp_EQZ(D))
    {   // Lines parallel
        up = 0 ; 
        if (tcomp_NEZ(e))
            uq = d / e ; 
        else 
            uq = 0 ; 

        if (CS_Collinear(P0, P0+vu, Q0))
            return CS_COLLINEAR ; 
        return CS_PARALLEL ; 
    }

    // Else basic single solution result
    up = (d*c - b*e) / D ; 
    uq = (a*e - b*d) / D ; 
    return CS_NONCOLLINEAR ;
}

