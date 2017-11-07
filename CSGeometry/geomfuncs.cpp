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
// cs_geomfuncs.cpp


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

// There are very sketchy notes for nearest point in Geom Algo's RR-Vol4 Pgs.22-23
// Further sketchy notes are in Geom Algo's RR-Vol4 Pg.82

//! Returns the nearest point between the line and a circle, 
int NearestPointCircleLine2D(CS_CIRCLE &circ, CS_LINE &ln, CS_POINT &npc, CS_POINT &npl) 
{
    CS_POINT p1, p2 ; 
    int nisects = circ.Intersect2D(ln, p1, p2) ; 
    if (nisects == 0)
    {   // Then we have to work out the closest point between them
        p1 = ln.NearestPoint(circ.ctr) ; 
        // A vector from the circle center to the point p1 will pass
        // through the nearest point on the circle to the line
        CS_VECTOR v(circ.ctr, p1) ; 
        v = v.Unit() ; 
        npl = p1 ; 
        npc = circ.ctr + (v * circ.rad) ; 
        return 0 ; 
    }
    else if (nisects == 1)
    {
        npc = p1 ; 
        npl = p1 ; 
        return 1 ; 
    }
    else
    {
        npc = p1 ; 
        npl = p2 ; 
        return 2 ; 
    }

    // Should never get here
    return -1 ; 
}

int NearestPointCircleCircle2D(CS_CIRCLE &c1, CS_CIRCLE &c2, CS_POINT &np1, CS_POINT &np2) 
{
    CS_POINT p1, p2 ; 
    int nisects = c1.Intersect2D(c2, p1, p2) ; 
    if (nisects == 0)
    {   // Then we have to work out the closest point between them

        if (c1.Inside(c2))
        {   // C2 is inside C1
            CS_VECTOR v(c1.ctr, c2.ctr) ; 
            if (tcomp_EQZ(v.Mag()))
            {   // Then the circles are concentric and all points are the same
                // distance away from each other
                v = CS_VECTOR(1,0,0) ; 
                np1 = c1.ctr + v * c1.rad ; 
                np2 = c2.ctr + v * c2.rad ; 
                return 3 ;
            }
            v = v.Unit() ; 
            np1 = c1.ctr + v * c1.rad ; 
            np2 = c2.ctr + v * c2.rad ; 
        }
        else if (c2.Inside(c1))
        {   // C1 is inside C2
            CS_VECTOR v(c2.ctr, c1.ctr) ; 
            if (tcomp_EQZ(v.Mag()))
            {   // Then the circles are concentric and all points are the same
                // distance away from each other
                v = CS_VECTOR(1,0,0) ; 
                np1 = c1.ctr + v * c1.rad ; 
                np2 = c2.ctr + v * c2.rad ; 
                return 3 ;
            }
            v = v.Unit() ; 
            np1 = c1.ctr + v * c1.rad ; 
            np2 = c2.ctr + v * c2.rad ; 
        }
        else
        {   // Then the two circles are independent
            CS_VECTOR v(c1.ctr, c2.ctr) ; 
            v = v.Unit() ; 
            np1 = c1.ctr + v * c1.rad ; 
            np2 = c2.ctr - v * c2.rad ; 
        }
        return 0 ; 
    }
    else if (nisects == 1)
    {
        np1 = p1 ; 
        np2 = p1 ; 
        return 1 ; 
    }
    else
    {
        np1 = p1 ; 
        np2 = p2 ; 
        return 2 ; 
    }

    // Should never get here
    return -1 ; 
}



double CS_MinDistLineLine2D(CS_LineSeg *pl1, CS_LineSeg *pl2, 
                          CS_POINT *p1, CS_POINT *p2,
                          double *u1, double *u2)
{
    CS_POINT pnt ; 
    double mindist, d;
    double u ; 
    double uva[2], uvb[2] ; 


    int nisects = pl1->Intersect2D(*pl2, uva, uvb) ; 
    if (nisects > 0)
    {   // Then simply return the intersection point, in the case
        // of an overlap intersection return the first point

        if (p1)
            *p1 = pl1->UPoint(uva[0]) ; 
        if (p2)
            *p2 = pl2->UPoint(uvb[0]) ; 
        if (u1)
            *u1 = uva[0] ; 
        if (u2)
            *u2 = uvb[0] ; 
        return 0.0 ; // they touch thus the distance is zero. 
    }

    //////////////////////////////////////////////////
    // Test the start point of second seg to first seg
    pl1->PointOnSegment(pl2->sp, &u, &pnt) ; 
    // Initialize everything using this point
    d = CS_VECTOR(pl2->sp, pnt).Mag() ;
    mindist = d ; 
    if (p1)
        *p1 = pnt ;
    if (p2)
        *p2 = pl2->sp ; 
    if (u1)
        *u1 = u ; 
    if (u2) 
        *u2 = 0.0 ; 

    //////////////////////////////////////////////////
    // Test the end point of second seg to first seg
    pl1->PointOnSegment(pl2->ep, &u, &pnt) ; 
    d = CS_VECTOR(pl2->ep, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = pnt ;
        if (p2)
            *p2 = pl2->ep ; 
        if (u1)
            *u1 = u ; 
        if (u2) 
            *u2 = 1.0 ; 
    }


    //////////////////////////////////////////////////
    // Test the start point of first seg to second seg
    pl2->PointOnSegment(pl1->sp, &u, &pnt) ; 
    d = CS_VECTOR(pl1->sp, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = pl1->sp ; 
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 0.0 ; 
        if (u2) 
            *u2 = u ; 
    }

    //////////////////////////////////////////////////
    // Test the start point of first seg to second seg
    pl2->PointOnSegment(pl1->ep, &u, &pnt) ; 
    d = CS_VECTOR(pl1->ep, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = pl1->ep ; 
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 1.0 ; 
        if (u2) 
            *u2 = u ; 
    }

    return mindist ; 
}


double CS_MinDistArcLine2D(CS_ArcSeg *pa1, CS_LineSeg *pl2,
                         CS_POINT *p1, CS_POINT *p2,
                         double *u1, double *u2)
{
    CS_POINT pnt ; 
    double mindist, d;
    double u, uva[2], uvb[2] ; 

    int nisects = pa1->Intersect2D(*pl2, uva, uvb) ;
    if (nisects > 0)
    {   // Then we're done
        if (p1)
            *p1 = pa1->UPoint(uva[0]) ; 
        if (p2)
            *p2 = pl2->UPoint(uvb[0]) ; 
        if (u1)
            *u1 = uva[0] ; 
        if (u2)
            *u2 = uvb[0] ; 
        return 0.0 ; // they touch thus the distance is zero. 
    }

    // Else the two do not intersect so must do more testing
    // Test the start point of second seg to first seg
    CS_LINE ln(*pl2) ; 
    CS_CIRCLE circ(*pa1) ; 
    CS_POINT pntc, pntl ;

    nisects = NearestPointCircleLine2D(circ, ln, pntc, pntl) ; 

    CS_POINT ap1, ap2, ap3 ; 
    ap1 = pa1->StartPoint() ; 
    ap2 = pa1->EndPoint() ; 

    int test3rdpoint = 0 ; 

    if (nisects == 0)
    {   // we have 3 points to test (must include pntc as 3rd point)
        test3rdpoint = 1 ; 
        ap3 = pntc ; 
    }

    ////////////////////////////////////////////
    // Test the line start point against the arc 
    pa1->PointOnSegment(pl2->sp, &u, &pnt) ; 
    // Initialize everything using this point
    d = CS_VECTOR(pnt, pl2->sp).Mag() ;
    mindist = d ; 
    if (p1)
        *p1 = pnt ;
    if (p2)
        *p2 = pl2->sp ; 
    if (u1)
        *u1 = u ; 
    if (u2)
        *u2 = 0.0 ; 

    ////////////////////////////////////////////
    // Test the end point of second seg to first seg
    pa1->PointOnSegment(pl2->ep, &u, &pnt) ; 
    d = CS_VECTOR(pl2->ep, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = pnt ;
        if (p2)
            *p2 = pl2->ep ; 
        if (u1)
            *u1 = u ; 
        if (u2)
            *u2 = 1.0 ; 
    }



    ////////////////////////////////////////////
    // Test the start point of first seg to second seg
    pl2->PointOnSegment(ap1, &u, &pnt) ; 
    d = CS_VECTOR(ap1, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = ap1 ; 
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 0.0 ; 
        if (u2)
            *u2 = u ; 
    }

    ////////////////////////////////////////////
    // Test the start point of first seg to second seg
    pl2->PointOnSegment(ap2, &u, &pnt) ; 
    d = CS_VECTOR(ap2, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = ap2 ; 
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 1.0 ; 
        if (u2)
            *u2 = u ; 
    }

    if (test3rdpoint)
    {
        ////////////////////////////////////////////
        // Test the start point of first seg to second seg
        // only test this point if it's actually on the arc. 
        double uap3 ; 
        if (pa1->PointOnArc(ap3, &uap3))
        {
            pl2->PointOnSegment(ap3, &u, &pnt) ; 
            d = CS_VECTOR(ap3, pnt).Mag() ;
            if (d < mindist)
            {
                mindist = d ; 
                if (p1)
                    *p1 = ap3 ; 
                if (p2)
                    *p2 = pnt ; 
                if (u1)
                    *u1 = uap3 ; 
                if (u2)
                    *u2 = u ; 
            }
        }
    }

    return mindist ; 
}


double CS_MinDistArcArc2D(CS_ArcSeg *pa1, CS_ArcSeg *pa2, 
                         CS_POINT *p1, CS_POINT *p2,
                         double *u1, double *u2)
{
    CS_POINT pnt ; 
    double mindist, d;
    double u, uva[2], uvb[2] ; 

    CS_POINT sp1, ep1, sp2, ep2, m1pa, m1pb, m2pa, m2pb ;

    if (pa1->ctr == pa2->ctr)
    {
        sp1 = pa1->StartPoint() ; 
        sp2 = pa2->StartPoint() ; 
        CS_VECTOR v(sp1, sp2) ;   
        if (p1)
            *p1 = sp1 ; 
        if (p2)
            *p2 = sp2 ; 
        if (u1)
            *u1 = 0.0 ; 
        if (u2)
            *u2 = 0.0 ; 
        return v.Mag() ; 
    }


    int nisects = pa1->Intersect2D(*pa2, uva, uvb) ; 
    if (nisects > 0)
    {
        if (p1)
            *p1 = pa1->UPoint(uva[0]) ; 
        if (p2)
            *p2 = pa2->UPoint(uvb[0]) ; 
        if (u1)
            *u1 = uva[0] ; 
        if (u2)
            *u2 = uvb[0] ; 
        return 0.0 ; 
    }

    // The arcs don't intersect so proceed with more complicated process. 

    // Test the start point of second seg to first seg
    CS_CIRCLE c1(*pa1) ; 
    CS_CIRCLE c2(*pa2) ; 
    CS_POINT pntc1, pntc2 ;
    
    nisects = NearestPointCircleCircle2D(c1, c2, pntc1, pntc2) ; 

    sp1 = pa1->StartPoint() ; 
    ep1 = pa1->EndPoint() ; 

    sp2 = pa2->StartPoint() ; 
    ep2 = pa2->EndPoint() ; 

    // Note: points 1,2,5, and 6 are on the first arc, 3,4,7,8 on second arc
    int testm1apoint = 0 ; 
    int testm1bpoint = 0 ;
    int testm2apoint = 0 ;
    int testm2bpoint = 0 ;

    double um1a, um1b, um2a, um2b ; 

    if (nisects == 2)
    {   // Special case 7 (see notes RR-Vol4 pg 83)
        CS_VECTOR v(c1.ctr, c2.ctr) ; 
        v = v.Unit() ; 

        m1pa = c1.ctr + v * c1.rad ; 
        m1pb = c1.ctr - v * c1.rad ; 

        m2pa = c2.ctr + v * c2.rad ; 
        m2pb = c2.ctr - v * c2.rad ; 

        if (pa1->PointOnArc(m1pa, &um1a))
            testm1apoint = 1; 

        if (pa1->PointOnArc(m1pb, &um1b))
            testm1bpoint = 1; 

        if (pa2->PointOnArc(m2pa, &um2a))
            testm2apoint = 1; 

        if (pa2->PointOnArc(m2pb, &um2b))
            testm2bpoint = 1; 
    }
    else 
    {   // nisects == 1 or there are no intersects, but both of these 
        // conditions work out to the same logic since pntc1 and pntc2 
        // are set to the same point when there is 1 intersection
        // pntc1 and pntc2 are equal in this case
        m1pa = pntc1 ; 
        if (pa1->PointOnArc(m1pa, &um1a))
            testm1apoint = 1 ; 

        m2pa = pntc2 ; 
        if (pa2->PointOnArc(m2pa, &um2a))
            testm2apoint = 1 ; 
    }

    // Now the huge mess follows since there are a possible 8 cases
    ////////////////////////////////////////////
    pa1->PointOnArc(sp2, &u, &pnt) ; 
    // Initialize everything using this point
    d = CS_VECTOR(pnt, sp2).Mag() ;
    mindist = d ; 
    if (p1)
        *p1 = pnt ;
    if (p2)
        *p2 = sp2 ; 
    if (u1)
        *u1 = u ; 
    if (u2) 
        *u2 = 0.0 ; 

    ////////////////////////////////////////////
    pa1->PointOnArc(ep2, &u, &pnt) ; 
    d = CS_VECTOR(ep2, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = pnt ;
        if (p2)
            *p2 = ep2 ; 
        if (u1)
            *u1 = u ; 
        if (u2) 
            *u2 = 1.0 ; 
    }

    ////////////////////////////////////////////
    pa2->PointOnArc(sp1, &u, &pnt) ; 
    d = CS_VECTOR(sp1, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = sp1 ;
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 0.0 ; 
        if (u2) 
            *u2 = u ; 
    }

    ////////////////////////////////////////////
    pa2->PointOnArc(ep1, &u, &pnt) ; 
    d = CS_VECTOR(ep1, pnt).Mag() ;
    if (d < mindist)
    {
        mindist = d ; 
        if (p1)
            *p1 = ep1 ;
        if (p2)
            *p2 = pnt ; 
        if (u1)
            *u1 = 1.0 ; 
        if (u2) 
            *u2 = u ; 
    }


    if (testm1apoint)
    {
        ////////////////////////////////////////////
        // Test the 'mid' point of first seg to second seg
        pa2->PointOnArc(m1pa, &u, &pnt) ; 
        d = CS_VECTOR(m1pa, pnt).Mag() ;
        if (d < mindist)
        {
            mindist = d ; 
            if (p1)
                *p1 = m1pa ; 
            if (p2)
                *p2 = pnt ; 
            if (u1)
                *u1 = um1a ; 
            if (u2) 
                *u2 = u ; 
        }
    }

    if (testm1bpoint)
    {
        ////////////////////////////////////////////
        // Test the 'mid' point of first seg to second seg
        pa2->PointOnArc(m1pb, &u, &pnt) ; 
        d = CS_VECTOR(m1pb, pnt).Mag() ;
        if (d < mindist)
        {
            mindist = d ; 
            if (p1)
                *p1 = m1pb ; 
            if (p2)
                *p2 = pnt ; 
            if (u1)
                *u1 = um1b ; 
            if (u2) 
                *u2 = u ; 
        }
    }


    if (testm2apoint)
    {
        ////////////////////////////////////////////
        // Test the 'mid' point of second seg to first seg
        pa1->PointOnArc(m2pa, &u, &pnt) ; 
        d = CS_VECTOR(m2pa, pnt).Mag() ;
        if (d < mindist)
        {
            mindist = d ; 
            if (p1)
                *p1 = pnt ; 
            if (p2)
                *p2 = m2pa ; 
            if (u1)
                *u1 = u ; 
            if (u2) 
                *u2 = um2a ; 
        }
    }

    if (testm2bpoint)
    {
        ////////////////////////////////////////////
        // Test the 'mid' point of second seg to first seg
        pa1->PointOnArc(m2pb, &u, &pnt) ; 
        d = CS_VECTOR(m2pb, pnt).Mag() ;
        if (d < mindist)
        {
            mindist = d ; 
            if (p1)
                *p1 = pnt ; 
            if (p2)
                *p2 = m2pb ; 
            if (u1)
                *u1 = u ; 
            if (u2) 
                *u2 = um2b ; 
        }
    }

    return mindist ; 
}


double CS_MinDistance2D(CS_SegPtr ps1, CS_SegPtr ps2, 
                        CS_POINT *p1, CS_POINT *p2,
                        double *u1, double *u2)
{
    if (ps1->SegmentType() == CS_Segment::LINE_TYPE && 
        ps2->SegmentType() == CS_Segment::LINE_TYPE) 
    {   // Line - Line case
        return CS_MinDistLineLine2D((CS_LineSeg *)ps1, (CS_LineSeg *)ps2, p1, p2, u1, u2) ;
    }
    else if (ps1->SegmentType() == CS_Segment::ARC_TYPE && 
             ps2->SegmentType() == CS_Segment::LINE_TYPE) 
    {   // Line - Line case
        return CS_MinDistArcLine2D((CS_ArcSeg *)ps1, (CS_LineSeg *)ps2, p1, p2, u1, u2) ;
    }
    else if (ps1->SegmentType() == CS_Segment::LINE_TYPE && 
             ps2->SegmentType() == CS_Segment::ARC_TYPE) 
    {   // Line - Line case
        return CS_MinDistArcLine2D((CS_ArcSeg *)ps2, (CS_LineSeg *)ps1, p1, p2, u1, u2) ;
    }
    else if (ps1->SegmentType() == CS_Segment::ARC_TYPE && 
             ps2->SegmentType() == CS_Segment::ARC_TYPE) 
    {   // Line - Line case
        return CS_MinDistArcArc2D((CS_ArcSeg *)ps1, (CS_ArcSeg *)ps2, p1, p2, u1, u2) ;
    }

    // Shouldn't get to here
    return 0.0 ; 
}


double CS_MinDistance2D(CS_Curve *pc1, CS_Curve *pc2, 
                        CS_POINT *p1, CS_POINT *p2,
                        double *u1, double *u2)
{
    CS_POINT pnt1, pnt2, pwrk1, pwrk2 ; 
    CS_SegPtr ps1 = pc1->pStart ; 
    CS_SegPtr ps2 = pc2->pStart ; 
    CS_SegPtr psm1, psm2 ; 
    double dist, ut1, ut2, um1, um2 ; 
    double mindist = CS_MinDistance2D(ps1, ps2, &pnt1, &pnt2, &um1, &um2) ; 
    psm1 = ps1 ; 
    psm2 = ps2 ; 


    while (ps1)
    {
        ps2 = pc2->pStart ; 
        while (ps2) 
        {
            dist = CS_MinDistance2D(ps1, ps2, &pwrk1, &pwrk2, &ut1, &ut2) ; 
            if (dist < mindist)
            {
                mindist = dist ; 
                pnt1 = pwrk1 ; 
                pnt2 = pwrk2 ; 
                um1 = ut1 ; 
                um2 = ut2 ; 
                psm1 = ps1 ; 
                psm2 = ps2 ; 
            }
            ps2 = ps2->next ; 
        }
        ps1 = ps1->next ; 
    }

    if (p1)
        *p1 = pnt1 ; 
    if (p2)
        *p2 = pnt2 ; 
    if (u1)
        *u1 = pc1->SegU2CrvU(psm1, um1) ; 
    if (u2)
        *u2 = pc2->SegU2CrvU(psm2, um2) ; 
    return mindist ; 
}


int CS_GetPointInside(CS_CurvePtr pcrv, CS_POINT &inspnt)
{
    pcrv->Complete() ; 
    if (!pcrv->Closed())
        return -1 ; // shape is not closed, can't do anything

    
    CS_POINT a1 = pcrv->StartPoint() ; 
    CS_POINT b1 = pcrv->MidPoint() ; 
    CS_POINT a2, b2 ; 

    // First test the actual midpoint
    CS_POINT p = (a1 + b1) * 0.5 ; 
    
    // Set a1,a2 to the half section nearest the start point
    // and set b1,b2 to the half section nearest the mid point
    a2 = p ; 
    b2 = p ; 

    if (pcrv->PointInside(p))
    {
        inspnt = p ; 
        return 0 ; 
    }


    int count = 0 ;
    while (count++ < 1000)
    {
        p = (a1 + a2) * 0.5 ; 
        if (pcrv->PointInside(p))
        {
            inspnt = p ; 
            return 0 ; 
        }
        a2 = p ; 

        p = (b1 + b2) * 0.5 ;
        if (pcrv->PointInside(p))
        {
            inspnt = p ; 
            return 0 ; 
        }
        b2 = p ; 
    }

    return -1 ; // failed to find a suitable point
}


int CS_GetPointOutside(CS_CurvePtr pcrv, CS_POINT &outpnt)
{
    if (!pcrv->Closed())
        return -1 ; 

    CS_POINT sp = pcrv->StartPoint() ; 
    pcrv->SetBoundingRect() ; 
    outpnt = CS_POINT(pcrv->bndrect.r + pcrv->bndrect.Width() * 0.25, 
                    (pcrv->bndrect.t + pcrv->bndrect.b) * 0.5, 
                    sp.z) ;

    return 0 ; 
}



double CS_LineLineDist3D(CS_LINE &l1, CS_LINE &l2)
{
    double u1 = 0 ; 
    double u2 = 0 ; 
    CS_POINT p1, p2; 
    CS_LineLineNearestPoints(l1, l2, u1, u2) ;
    p1 = l1.UPoint(u1) ; 
    p2 = l2.UPoint(u2) ; 
    return CS_Distance(p1, p2) ; 
}
