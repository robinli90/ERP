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
// shapes.cpp - standard geometric shapes and entities for 
//              general processing

#include "math.h"
#include "cs_shapes.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)          
#define CS_DEBUG2(a)         
#else
#define CS_DEBUG(a)         
#define CS_DEBUG2(a)       
#endif
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CS_CLINE - general line class
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

CS_LINE::CS_LINE(CS_LineSeg &l)
{
    sp = l.sp ; 
    ep = l.ep ; 
}

CS_LINE::CS_LINE(CS_POINT &p1, CS_POINT &p2) 
{
    sp = p1 ; 
    ep = p2 ; 
}

int CS_LINE::LineParameters2D(double &m, double &b)
{
    // In the case where the line is vertical we will set m=0 and b = 0
    CS_VECTOR v(sp, ep) ; 

    if (tcomp_EQZ(v.v[0])) 
    {   // Vertical line
        m = 0.0 ; 
        b = 0.0 ; 
        return -1 ;
    }

    m = v.y / v.x ; 
    b = -(m * sp.x) + sp.y ; 
    return 0 ; 
}

int CS_LINE::Collinear(CS_LINE &b)
{
    CS_VECTOR ab(sp, ep) ; 
    CS_VECTOR cd(b.sp, b.ep) ; 
    CS_VECTOR ac ; 

    if (sp == b.sp)
        ac = CS_VECTOR(sp, b.ep) ; 
    else
        ac = CS_VECTOR(sp, b.sp) ;
    
    if (tcomp_EQZ(ab.Mag()) || tcomp_EQZ(ac.Mag()))
        return 0 ; // lines are undefined

    ab = ab.Unit() ; 
    cd = cd.Unit() ; 
    ac = ac.Unit() ; 

    if ((CS_VECTOR(0,0,0) == (ab * cd)) && 
        (CS_VECTOR(0,0,0) == (ab * ac)))
    {
        return 1 ; 
    }

    return 0 ; 
}


int CS_LINE::Collinear2D(CS_LINE &b)
{
    CS_VECTOR ab(sp, ep) ; 
    CS_VECTOR cd(b.sp, b.ep) ; 
    CS_VECTOR ac ; 

    ab.z = 0 ; 
    ab.z = 0 ; 

    cd.z = 0 ; 
    cd.z = 0 ; 

    if (sp == b.sp)
        ac = CS_VECTOR(sp, b.ep) ; 
    else
        ac = CS_VECTOR(sp, b.sp) ;

    ac.z = 0 ; 
    ac.z = 0 ; 
    
    if (tcomp_EQZ(ab.Mag()) || tcomp_EQZ(ac.Mag()))
        return 0 ; // lines are undefined

    ab = ab.Unit() ; 
    cd = cd.Unit() ; 
    ac = ac.Unit() ; 

    if ((CS_VECTOR(0,0,0) == (ab * cd)) && 
        (CS_VECTOR(0,0,0) == (ab * ac)))
    {
        return 1 ; 
    }

    return 0 ; 
}



//////////////////////////////////////////////////////////////////////////////
/*
    int CS_LINE::Intersect2D(CS_LINE &l1, CS_POINT &ipnt)

    Inputs: Two line segment paramters l1 and l2 for the
        intersection operation. Only the xy components of the lines are considered 
        when doing the intersect. The z component is ignored.

    Outputs: The intersection point if there is one. If the return value is 
        0 then the ipnt parameter is not affected since no intersect was found

    Returns: The number of intersects found. 1 = ipnt has value of intersection
        point. 0 = no intersection found and ipnt is unchanged. If the lines
        are collinear then the number of intersects returned is 2, and the 
        ipnt returned is either the X or Y intercept

    Comments:

*/
//////////////////////////////////////////////////////////////////////////////
int CS_LINE::Intersect2D(CS_LINE &b, CS_POINT &ipnt)
{
    // First calculate direction vectors for the lines
    CS_VECTOR v = (ep - sp) ; 
    CS_VECTOR w = (b.ep - b.sp) ; 
    
    v.z = 0.0 ; // eliminate z component
    w.z = 0.0 ; // eliminate z component

    if (tcomp_EQZ(v.Mag()) || tcomp_EQZ(w.Mag()))
        return 0 ; // lines are undefined

    v = v.Unit() ; 
    w = w.Unit() ; 

    // Test if the lines are collinear, cross product is zero and they share a 
    // common point.
    if ((v * w) == CS_VECTOR(0,0,0))
    {   // Then the lines are parallel
        // Now test for collinear case
        if (Collinear2D(b))
        {
            CS_DEBUG(fprintf(fpDebugOut, "    ======= COLINEAR LINES ========    \n")) ; 
            ipnt = sp ; // all points are intersection points so simply
            return 2 ;  // return a point on the line
        }
        else
        {   // no intersection since lines parallel
            CS_DEBUG(fprintf(fpDebugOut, "    ======= PARALLEL LINES ========    \n")) ; 
            return 0 ; 
        }
    }

    /*
     definition of parametric line is S(t)=Q+vt where Q is point on the
     line and v is a vector along the line. For two lines to intersect
     defined by A=P+vs and B=Q+wt where P and Q are points on the lines
     A and B respectively, and v and w are vectors along the lines, and 
     finally s and t are the parametric variables.
     Then at the intersection point P+vs=Q+wt must hold which results
     in 2 equations in two unknows.

        (Px,Py)+(vx,vy)s = (Qx,Qy)+(wx,wy)t
        .
        . (see notes Oct 2, 1998, Pg.7)
        .
        B(t) = Q + wt 

    */

    double x = sp.x - b.sp.x ; 
    double y = sp.y - b.sp.y ; 

    // calculate the delta determinant
    double d = (w.y * v.x) - (w.x * v.y) ; 
    double d2 = (w.x * y) - (w.y * x) ; 

    if (tcomp_EQZ(d))
    {
        return 0 ; // no solution to set of equations
    }

    double s = d2 / d ; 

    ipnt = sp + (v * s) ; 

    CS_DEBUG
    (
        fprintf(fpDebugOut, "CS_LINES intersect @ ") ; 
        ipnt.Print(fpDebugOut) ; 
        fprintf(fpDebugOut, "\n") ; 
    )
    return 1 ; // generated the intersection point
}

int CS_LINE::Intersect2D(CS_CIRCLE &cir, CS_POINT &p1, CS_POINT &p2)
{
    return IntersectLineAndCircle2D(*this, cir, p1, p2) ; 
}


//! Parametric intersect of two 3D lines, returns 0=no solution
//! 1=OK or 2=collinear
int CS_LINE::Intersect(CS_LINE &ln, double &s, double &t)
{
    // See notes Geom Algo's RR-Vol4  Pg 148
    CS_POINT P(sp) ; 
    CS_POINT Q(ln.sp) ; 
    CS_VECTOR u(sp,ep) ; 
    CS_VECTOR v(ln.sp,ln.ep) ; 
    CS_VECTOR w(P,Q) ; 
    double D ; // denominator determinant or distance 
    double um = u.Mag() ; 
    double vm = v.Mag() ; 

    if (tcomp_EQZ(um) || tcomp_EQZ(vm))
        return 0 ; // one of the lines is undefined. 

    // 1) Check if the two lines are collinear
    if (u == v)
    {   // Then they go in the same direction
        if (CS_Collinear(sp, ep, ln.sp))
        {
            // Parametrically match t to s.
            s = 0 ; 
            t = w.Mag() / vm ; 
            if (CS_DotProduct(u, v) < 0)
            {   // Lines go in opposite direction
                t = -t ; // thus reverse parameterization
            }
            return 2 ; // lines are the same
        }
        // Otherwise there is no solution
        return 0 ; // no solution
    }

    if (tcomp_EQZ(u.x) && tcomp_EQZ(v.x))
    {   // Then attempt solution in YZ plane
        D = u.z * v.y - u.y * v.z ;
        if (tcomp_EQZ(D))
        {   // Then there is no solution 
            return 0 ; 
        }

        s = (w.z * v.y - w.y * v.z) / D ; 
        t = (u.y * w.z - u.z * w.y) / D ; 
        return 1 ; 
    }
    else if (tcomp_EQZ(u.y) && tcomp_EQZ(v.y))
    {   // Then attempt solution in XZ plane
        D = u.z * v.x - u.x * v.z ;
        if (tcomp_EQZ(D))
        {   // Then there is no solution 
            return 0 ; 
        }

        s = (w.z * v.x - w.x * v.z) / D ; 
        t = (u.x * w.z - u.z * w.x) / D ; 
        return 1 ; 
    }

    // Then attempt solution in XY plane
    D = u.y * v.x - u.x * v.y ;
    if (tcomp_EQZ(D))
    {   // Then there is no solution 
        return 0 ; 
    }

    s = (w.y * v.x - w.x * v.y) / D ; 
    t = (u.x * w.y - u.y * w.x) / D ; 
    return 1 ; 
}

///////////////////////////
// Nearest point on a line
// See notes RR-Vol1 Pg 24
///////////////////////////
CS_POINT CS_LINE::NearestPoint(CS_POINT &r) 
{
    double t ; 
    CS_VECTOR v(sp, ep) ; // vector along the line
    CS_POINT np = sp ; 

    if (tcomp_NEZ(v.Mag()))
    {   // Then we can do the calculation
        CS_VECTOR rp(r - sp) ; 
        t = CS_DotProduct(rp, v) / CS_DotProduct(v, v) ; 
        np = sp + (v * t) ; 
    }
    return np ; 
}


double CS_LINE::Slope() 
{
    double dx = ep.p[0] - sp.p[0] ; // delta x or the run
    double dy = ep.p[1] - sp.p[1] ; // delta y or the rise
    if (tcomp_EQZ(dx))
    {
        if (dy > 0)
            return HUGE_VAL ; 
        else
            return -HUGE_VAL ; 
    }
    return dy / dx ; 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CS_CIRCLE - general circle class
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
CS_CIRCLE::CS_CIRCLE()
{
    ctr = CS_POINT(0,0,0) ; 
    rad = 0 ; 
}


CS_CIRCLE::CS_CIRCLE(CS_ArcSeg &arc)
{
    ctr = arc.ctr ; 
    rad = arc.rad ; 
}

CS_CIRCLE::CS_CIRCLE(CS_POINT &p, double radius)
{
    ctr = p ; 
    rad = radius ; 
}


CS_RECT CS_CIRCLE::BoundingRect()
{
    CS_RECT r ; 
    r.l = ctr.x - rad ; 
    r.t = ctr.y + rad ; 
    r.b = ctr.y - rad ; 
    r.r = ctr.x + rad ; 
    return r ; 
}


/////////////////////////////////////////////////////////////////////////
/*
    Calculate the intersection of a line and a circle
        (see notes Sep 29, 1998. Pgs 1-5)
    
    Upon entry the *this circle is circle 1 and cir=circle 2
    if swapped is true then the sense of which is which is reversed
    returns 0 1 or 2 intersect points. If the circles do not touch 
    (spread apart in space or one is completely inside the other)
    then there is no solution and 0 is returned and neither p1 or p2
    is affected.  If the circles are 
    tangent to one another then there is a single intersection point
    at the point of tangency and p1 is set to this point, p2 is not
    affected. Otherwise the circles cross over one another in exactly
    two points, p1 is set to one point and p2 the other.
*/
 


/////////////////////////////////////////////////////////////////////////
/*
    Calculate the intersection of 2 circles 
        (see notes Sep 29, 1998. Pgs 1-5)
    
    Upon entry the *this circle is circle 1 and cir=circle 2
    if swapped is true then the sense of which is which is reversed
    returns 0 1 or 2 intersect points. If the circles do not touch 
    (spread apart in space or one is completely inside the other)
    then there is no solution and 0 is returned and neither p1 or p2
    is affected.  If the circles are 
    tangent to one another then there is a single intersection point
    at the point of tangency and p1 is set to this point, p2 is not
    affected. Otherwise the circles cross over one another in exactly
    two points, p1 is set to one point and p2 the other.
    If the circles are coincident then neither p1 or p2 is set but 
    3 is returned for the number of intersection points
*/
 
int CS_CIRCLE::Intersect2D(CS_CIRCLE &cir, CS_POINT &p1, CS_POINT &p2) 
{
    double r1, r2, x1, x2, d, h, k ;
    int swapped ; 
    CS_VECTOR vc21 ; // vector from center_2 -> center_1
    CS_POINT pc2 ; 

    // fprintf(fpDebugOut, "CIRC-CIRC\n") ; 
    
    if (rad > cir.rad)
    {   // then we are swapping the sense of circle 1 and 2
        swapped = 1 ; 
        r1 = cir.rad ; 
        r2 = rad ; 
        vc21 = CS_VECTOR(ctr, cir.ctr) ; 
        pc2 = ctr ; 
    }
    else
    {
        swapped = 0 ; 
        r1 = rad ; 
        r2 = cir.rad ; 
        vc21 = CS_VECTOR(cir.ctr, ctr) ; 
        pc2 = cir.ctr ; 
    }

    vc21.z = 0.0 ; 

    // fprintf(fpDebugOut, "C-C (a)\n") ; 

    d = vc21.Mag() ; // distance between centers 
    if (tcomp_EQZ(d))
    {
        if (tcomp_EQ(r1,r2))
            return 3 ; // coincident circles
        return 0 ; // same centers but different diameters
    }

    // fprintf(fpDebugOut, "C-C (b)\n") ; 

    if (tcomp_LT(r1 + r2,d) || tcomp_GT(r2 - r1, d))
    {   // Then there is no solution
        return 0 ; 
    }

    // Test tangency case where the circles touch.
    // There are two possible cases here, the small circle is outside 
    // the larger circle (the first _EQ test condition) or the small
    // circle is inside the larger circle which is the second part of
    // the if test.

    // fprintf(fpDebugOut, "C-C (c)\n") ; 

    if (tcomp_EQ(r1 + r2, d) || tcomp_EQ(r2 - r1, d))
    {   // Then the circles touch at a single point
        // The intersection point then is along the vc21 vector
        // from the center_2 point at a distance of rad_2
        p1 = pc2 + (vc21.Unit() * r2) ; 
        return 1 ; // only 1 intersect point
    }
    
    // fprintf(fpDebugOut, "C-C (d)\n") ; 

    /* Decided to ignore this case and simply return 0 for no intersects
       This logic was moved to the previous test condition since it 
       represents a single intersect point
    if (tcomp_EQ(r1 + r2, d))
    {
        // Note the EQ to case in the LE (first test) tests for 
        // coincident circles in which case we have an infinite number
        // number of solutions
        return -1 ; 
    }
    */

    // Else we will have 2 intersect points for the 2 circles
    k = (r1 * r1) - (r2 * r2) ;
    x2 = ((d * d) - k) / (2.0 * d) ; 
    x1 = d - x2 ; 
    h = sqrt((r1 * r1) - (x1 * x1)) ; 
    vc21 = vc21.Unit() ; 
    CS_POINT p = pc2 + (vc21 * x2) ; 
    p1 = p + (vc21.RightPerp() * h) ; 
    p2 = p + (vc21.LeftPerp() * h) ; 
    return 2 ; 
}


int CS_CIRCLE::Intersect2D(CS_LINE &ln, CS_POINT &p1, CS_POINT &p2) 
{
    return IntersectLineAndCircle2D(ln, *this, p1, p2) ; 
}

double CS_CIRCLE::Area()
{
    return RADIAN180 * rad * rad ; // pi*r^2
}


// See notes Oct 14/98, RR-Vol1 pp.34-35
// Used by both CS_LINE class and CS_CIRCLE class
// From 'Computer Graphics, Principals and Practive, 2nd Ed." pg 1100
int IntersectLineAndCircle2D(CS_LINE &ln, CS_CIRCLE &cir, 
                             CS_POINT &p1, CS_POINT &p2) 
{
    double B, C, t, disc ; 
    CS_VECTOR v(ln.sp,ln.ep) ; 
    CS_VECTOR vpq(cir.ctr, ln.sp) ; 

    // Set to zero since we are doing a 2D intersection
    v.z = 0.0 ; 
    vpq.z = 0.0 ; 
    
    // If we take the unit vector of V the A=1.0 and can be dropped 
    // from the equations since CS_DotProduct(unitvec,unitvec) = 1.0 always
    /*
    // The equations below are extracted exactly from Foley. A is 
    // eliminated by first making v a unit vector, since the 
    // v.v dot product is always 1.0. The only time this would 
    // not be true is if v is a zero vector.
    double A ; 
    A = CS_CS_DotProductuct(v, v) ; 
    B = 2 * CS_DotProduct(v, vpq) ; 
    C = CS_DotProduct(vpq, vpq) - (cir.rad * cir.rad) ; 
    
    disc = (B * B) - (4 * A * C) ; 
    if (tcomp_LT(disc, 0.0))
    {
        CS_DEBUG2(fprintf(fpDebugOut, "discrminant=%.6lf < 0 No solution\n", disc);) ;
        return 0 ; // no solution
    }
    else if (tcomp_EQZ(disc))
    {   // Then there is a single solution and line is tangent to 
        // the circle
        t = -B / (2.0 * A) ; 
        p1 = ln.sp + (v * t) ; 

        CS_DEBUG2(fprintf(fpDebugOut, "Ln-Cir Tangent intersect @") ; p1.Print(fpDebugOut) ;
                  fprintf(fpDebugOut, "\n") ; )

        return 1 ; 
    }

    // else we have two unique solutions
    t = (-B + sqrt(disc)) / (2.0 * A) ; 
    p1 = ln.sp + (v * t) ; 
    t = (-B - sqrt(disc)) / (2.0 * A) ; 
    p2 = ln.sp + (v * t) ; 

    CS_DEBUG2(fprintf(fpDebugOut, "Ln-Cir intercepts ") ; p1.Print(fpDebugOut) ; fprintf(fpDebugOut, " ") ; 
              p2.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ; )
    */

    v = v.Unit() ; 

    B = 2 * CS_DotProduct(v, vpq) ; 
    C = CS_DotProduct(vpq, vpq) - (cir.rad * cir.rad) ; 
    
    disc = (B * B) - (4 * C) ; 
    if (tcomp_LT(disc, 0.0))
    {
        // Make doubly sure there is no intersection at a tangent by
        // using the nearest point technique.
        CS_Tolerance tol ; 
        t = tol.Scale(50.0) ; 
        // after re-adjusting tolerance test once more to see if worth 
        // doing the test
        if (tcomp_EQZ(disc))
        {   // Almost 0 so test nearest point
            CS_LINE tstln(ln.sp, ln.ep) ; 
            tstln.sp.z = cir.ctr.z ; 
            tstln.ep.z = cir.ctr.z ; 
            CS_POINT np = tstln.NearestPoint(cir.ctr) ; 
            v = CS_VECTOR(cir.ctr, np) ; 
            v.z = 0 ; // 2D intersection
            tol.Set(t) ; // set the tolerance back to what it was
            // for the magnitude testing
            if (tcomp_EQ(v.Mag(), cir.rad))
            {   // Then we do have a tangency condition
                p1 = np ; 
                p1.z = cir.ctr.z ; 
                return 1 ; 
            }
        }
        CS_DEBUG2(fprintf(fpDebugOut, "discrminant=%.6lf < 0 No solution\n", disc);) ;
        return 0 ; // no solution
    }
    else if (tcomp_EQZ(disc))
    {   // Then there is a single solution and line is tangent to 
        // the circle
        t = -B / (2.0) ; 
        p1 = ln.sp + (v * t) ; 
        p1.z = cir.ctr.z ; 

        CS_DEBUG2(fprintf(fpDebugOut, "Ln-Cir Tangent intersect @") ; p1.Print(fpDebugOut) ;
                  fprintf(fpDebugOut, "\n") ; ) ;
        return 1 ; 
    }

    // else we have two unique solutions
    t = (-B + sqrt(disc)) / (2.0) ; 
    p1 = ln.sp + (v * t) ; 
    p1.z = cir.ctr.z ; 
    t = (-B - sqrt(disc)) / (2.0) ; 
    p2 = ln.sp + (v * t) ; 
    p2.z = cir.ctr.z ; 

    return 2 ; 
}

CS_POINT CS_CIRCLE::NearestPoint(CS_POINT &p) 
{
    CS_VECTOR vcp= CS_VECTOR(ctr, p).Unit() ; 
    CS_POINT np ; 
    if (tcomp_EQZ(vcp.Mag()))
    {
        np = ctr + CS_VECTOR(1.0, 0.0) * rad ; 
    }
    else
    {
        np = ctr + (vcp * rad) ; 
    }
    return np ; 
}

// Returns true if the point is inside the circle
int CS_CIRCLE::Inside(CS_POINT &p)
{
    CS_VECTOR v(ctr, p) ; 
    if (tcomp_LT(v.Mag(), rad))
        return 1 ; 
    return 0 ; 

}

int CS_CIRCLE::Inside(CS_CIRCLE &c)
{
    CS_VECTOR v(ctr, c.ctr) ; 
    if (tcomp_LT(v.Mag() + c.rad, rad))
        return 1 ; 
    return 0 ; 

}

int CS_CIRCLE::Inside(CS_LINE &l)
{
    if (!Inside(l.sp))
        return 0 ; 
    if (!Inside(l.ep))
        return 0 ; 
    return 1 ; 
}

int CS_CIRCLE::Inside(CS_ARC &a)
{
    CS_CIRCLE c(a.ctr, a.rad) ; 
    if (Inside(c))
        return 1 ; // completely inside 

    // Else have to test further
    
    // See if the arc intersects with the circle
    CS_ArcSeg acir(ctr, 0, RADIAN360, rad) ; 
    CS_ArcSeg aseg(a) ; 
    double uva[2], uvb[2] ; 
    int nisects = acir.Intersect2D(aseg, uva, uvb) ;
    if (nisects > 0)
        return 0 ; // can't be inside it it intersected the circle

    // Else check one end point of the arc
    if (tcomp_LT(CS_Distance2D(ctr, aseg.StartPoint()), c.rad))
        return 1 ; 
    return 0 ; 
}


// Returns true if the point is inside or on the circle
int CS_CIRCLE::InsideOrOn(CS_POINT &p)
{
    CS_VECTOR v(ctr, p) ; 
    if (tcomp_LEQ(v.Mag(), rad))
        return 1 ; 
    return 0 ; 

}


int CS_CIRCLE::InsideOrOn(CS_CIRCLE &c)
{
    CS_VECTOR v(ctr, c.ctr) ; 
    if (tcomp_LEQ(v.Mag() + c.rad, rad))
        return 1 ; 
    return 0 ; 

}

//* Returns location of point in relation to the line. CS_LEFTSIDE
//* result the point is on the left side of the line. 
int PointSide(CS_LINE &l, CS_POINT &p)
{
    CS_VECTOR vsp(l.sp, p) ; 
    CS_VECTOR vpe(p, l.ep) ; 
    double zc = ZCross(vsp, vpe) ;

    if (zc < 0)
        return CS_LEFTSIDE ;
    else if (zc > 0)
        return CS_RIGHTSIDE ; 
    return CS_COLLINEAR ;
}


int CS_Collinear(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc)
{
    CS_VECTOR va(pa, pb) ; 
    CS_VECTOR vb(pb, pc) ; 
    double zc = ZCross(va, vb) ;

    if (tcomp_EQZ(zc))
        return 1 ;
    return 0 ; 
}


// Lines ab to bc make a left turn 
// The colinear case will return true
int PointsTurnLeft(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc)  
{
    CS_VECTOR vsp(pa, pb) ; 
    CS_VECTOR vpe(pb, pc) ; 
    double zc = ZCross(vsp, vpe) ;

    if (zc < 0)
        return 0 ;
    return 1 ; 
}


// Lines ab to bc make a right turn 
// The colinear case will return true
int PointsTurnRight(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc)  
{
    CS_VECTOR vsp(pa, pb) ; 
    CS_VECTOR vpe(pb, pc) ; 
    double zc = ZCross(vsp, vpe) ;

    if (zc > 0)
        return 0 ;
    return 1 ; 
}


// returns true if the lines are parallel
int CS_LinesParallel(CS_LineSeg &l1, CS_LineSeg &l2)
{
    CS_VECTOR v1(l1.sp, l1.ep) ; 
    CS_VECTOR v2(l2.sp, l2.ep) ; 
    CS_VECTOR vx = v1 * v2 ; 

    if (tcomp_EQZ(vx.Mag()))
        return 1 ; 
    return 0 ; 
}