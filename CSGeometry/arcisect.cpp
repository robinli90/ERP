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
// arcisect.cpp - intersection routines for arc segments

/*
  From  http://forum.swarthmore.edu/dr.math/problems/circintersect.html

  for solving the intersection of 2 circles

I fed the equations into a computer, and it gave me this answer.  For
brevity of notation, I changed the equations to(x-a)^2 + (y-b)^2 == R
(x-c)^2 + (y-d)^2 == r.These are the two points:  
{{x -> (a^4 + a^2*b^2 - 2*a^3*c - b^2*c^2 + 2*a*c^3 - c^4 - 2*a^2*b*d + 
       2*b*c^2*d + a^2*d^2 - c^2*d^2 + a^2*r - 2*a*c*r + c^2*r - a^2*R + 
       2*a*c*R - c^2*R + b*((a - c)^2*
           (-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 6*a^2*c^2 - 
             2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 4*b^3*d - 
             8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 4*a*c*d^2 - 
             2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 4*a*c*r + 
             2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 2*b^2*R - 
             4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2))^(1/2) - 
       d*((a - c)^2*(-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 
             6*a^2*c^2 - 2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 
             4*b^3*d - 8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 
             4*a*c*d^2 - 2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 
             4*a*c*r + 2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 
             2*b^2*R - 4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2
             ))^(1/2))/(2*(a - c)*(a^2 + b^2 - 2*a*c + c^2 - 2*b*d + d^2)), 
   y -> (a^2*b + b^3 - 2*a*b*c + b*c^2 + a^2*d - b^2*d - 2*a*c*d + c^2*d - 
       b*d^2 + d^3 + b*r - d*r - b*R + d*R - 
       ((a - c)^2*(-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 
            6*a^2*c^2 - 2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 4*b^3*d - 
            8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 4*a*c*d^2 - 
            2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 4*a*c*r + 
            2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 2*b^2*R - 
            4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2))^(1/2))/
     (2*(a^2 + b^2 - 2*a*c + c^2 - 2*b*d + d^2))}, 
  {x -> (a^4 + a^2*b^2 - 2*a^3*c - b^2*c^2 + 2*a*c^3 - c^4 - 2*a^2*b*d + 
       2*b*c^2*d + a^2*d^2 - c^2*d^2 + a^2*r - 2*a*c*r + c^2*r - a^2*R + 
       2*a*c*R - c^2*R - b*((a - c)^2*
           (-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 6*a^2*c^2 - 
             2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 4*b^3*d - 
             8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 4*a*c*d^2 - 
             2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 4*a*c*r + 
             2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 2*b^2*R - 
             4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2))^(1/2) + 
       d*((a - c)^2*(-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 
             6*a^2*c^2 - 2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 4*b^3*d - 
             8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 4*a*c*d^2 - 
             2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 4*a*c*r + 
             2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 2*b^2*R - 
             4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2))^(1/2))/
     (2*(a - c)*(a^2 + b^2 - 2*a*c + c^2 - 2*b*d + d^2)), 
   y -> (a^2*b + b^3 - 2*a*b*c + b*c^2 + a^2*d - b^2*d - 2*a*c*d + c^2*d - 
       b*d^2 + d^3 + b*r - d*r - b*R + d*R + 
       ((a - c)^2*(-a^4 - 2*a^2*b^2 - b^4 + 4*a^3*c + 4*a*b^2*c - 
            6*a^2*c^2 - 2*b^2*c^2 + 4*a*c^3 - c^4 + 4*a^2*b*d + 4*b^3*d - 
            8*a*b*c*d + 4*b*c^2*d - 2*a^2*d^2 - 6*b^2*d^2 + 4*a*c*d^2 - 
            2*c^2*d^2 + 4*b*d^3 - d^4 + 2*a^2*r + 2*b^2*r - 4*a*c*r + 
            2*c^2*r - 4*b*d*r + 2*d^2*r - r^2 + 2*a^2*R + 2*b^2*R - 
            4*a*c*R + 2*c^2*R - 4*b*d*R + 2*d^2*R + 2*r*R - R^2))^(1/2))/
     (2*(a^2 + b^2 - 2*a*c + c^2 - 2*b*d + d^2))}}

*/


#include "math.h"

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)          
#define CS_DEBUGI(a)    
#define CS_DEBUGAL(a)   
#define CS_DEBUG2(a)    
#define CS_DEBUGIS1(a)  
#else
#define CS_DEBUG(a)     
#define CS_DEBUGI(a)    
#define CS_DEBUGAL(a)   
#define CS_DEBUG2(a)    
#define CS_DEBUGIS1(a)  
#endif

int CS_ArcSeg::PointOnSegment(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    if (toldist)
        return CS_ARC::PointOnArc(p, puval, pnpnt, *toldist) ; 
    else
        return CS_ARC::PointOnArc(p, puval, pnpnt) ; 
}


int CS_ArcSeg::PointOnSegment2D(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    if (toldist)
        return CS_ARC::PointOnArc2D(p, puval, pnpnt, *toldist) ; 
    else
        return CS_ARC::PointOnArc2D(p, puval, pnpnt) ; 
}



// Returns true or false indicating whether or not the point passed 
// lies physically on the segment. If puval != NULL then the u value
// of the point on the segment that is closest to p is returned in
// the space pointed to by puval. puval must point to a memory location
// with sufficient space to store a double. No memory is allocated. 
// Similarily pnpnt will be saved if it is not NULL 
int CS_ARC::PointOnArc(CS_POINT &p, double *puval, CS_POINT *pnpnt)
{
    int retval = 0 ;
    CS_VECTOR vcp = CS_VECTOR(ctr, p).Unit() ; // unit vec from center to pnt
    vcp.z = 0.0 ; 
    CS_POINT np = ctr + (vcp * rad) ;
    double phi ; 

    // TO DO - modify below to work in any plane not just XY plane
    phi = vcp.AngleXY() ; 
    if (AngleOnSweep(phi))
    {   // then the point is within the sweep of the arc segment
        if (np == p)
            retval = 1 ; // point was actually on the arc segment
        if (pnpnt) *pnpnt = np ; 
        if (puval) *puval = AngleU(phi) ; 
    }
    else if (pnpnt || puval) 
    {   // The point is not within the sweep of the arc so see which end pnt
        // of the arc it is closest to
        CS_POINT sp = StartPoint() ; 
        CS_POINT ep = EndPoint() ; 
        double l1 = CS_VECTOR(sp, p).Mag() ; 
        double l2 = CS_VECTOR(ep, p).Mag() ; 
        if (l1 < l2)
        {
            if (pnpnt) *pnpnt = sp ; 
            if (puval) *puval = 0.0 ; 
        }
        else
        {
            if (pnpnt) *pnpnt = ep ; 
            if (puval) *puval = 1.0 ; 
        }
    }

    return retval ; // returns true only if p touches the arc
}

int CS_ARC::PointOnArc2D(CS_POINT &p, double *puval, CS_POINT *pnpnt)
{
    double centerZ = ctr.z ; 
    double pZ = p.z ; 
    ctr.z = 0 ; // reset Z for 2D operation
    p.z = 0 ; 

    int retval = 0 ;
    CS_VECTOR vcp = CS_VECTOR(ctr, p).Unit() ; // unit vec from center to pnt
    vcp.z = 0.0 ; 
    CS_POINT np = ctr + (vcp * rad) ;
    double phi ; 

    // TO DO - modify below to work in any plane not just XY plane
    phi = vcp.AngleXY() ; 
    if (AngleOnSweep(phi))
    {   // then the point is within the sweep of the arc segment
        if (np == p)
            retval = 1 ; // point was actually on the arc segment
        if (pnpnt) *pnpnt = np ; 
        if (puval) *puval = AngleU(phi) ; 
    }
    else if (pnpnt || puval) 
    {   // The point is not within the sweep of the arc so see which end pnt
        // of the arc it is closest to
        CS_POINT sp = StartPoint() ; 
        CS_POINT ep = EndPoint() ; 
        double l1 = CS_VECTOR(sp, p).Mag() ; 
        double l2 = CS_VECTOR(ep, p).Mag() ; 
        if (l1 < l2)
        {
            if (pnpnt) *pnpnt = sp ; 
            if (puval) *puval = 0.0 ; 
        }
        else
        {
            if (pnpnt) *pnpnt = ep ; 
            if (puval) *puval = 1.0 ; 
        }
    }

    ctr.z = centerZ ; // restore the Z center value
    p.z = pZ ; 
    return retval ; // returns true only if p touches the arc
}


int CS_ARC::PointOnArc(CS_POINT &p, double *puval, CS_POINT *pnpnt, const double &toldist)
{
    int retval = 0 ;
    CS_VECTOR vcp = CS_VECTOR(ctr, p).Unit() ; // unit vec from center to pnt
    vcp.z = 0.0 ; 
    CS_POINT np = ctr + (vcp * rad) ;
    double phi ; 

    // TO DO - modify below to work in any plane not just XY plane
    phi = vcp.AngleXY() ; 
    if (AngleOnSweep(phi))
    {   // then the point is within the sweep of the arc segment
        if (tcomp_PointsEQ(np.p, p.p, toldist))
            retval = 1 ; // point was actually on the arc segment
        if (pnpnt) *pnpnt = np ; 
        if (puval) *puval = AngleU(phi) ; 
    }
    else if (pnpnt || puval) 
    {   // The point is not within the sweep of the arc so see which end pnt
        // of the arc it is closest to
        CS_POINT sp = StartPoint() ; 
        CS_POINT ep = EndPoint() ; 
        double l1 = CS_VECTOR(sp, p).Mag() ; 
        double l2 = CS_VECTOR(ep, p).Mag() ; 
        if (l1 < l2)
        {
            if (pnpnt) *pnpnt = sp ; 
            if (puval) *puval = 0.0 ; 
        }
        else
        {
            if (pnpnt) *pnpnt = ep ; 
            if (puval) *puval = 1.0 ; 
        }
    }

    return retval ; // returns true only if p touches the arc
}

int CS_ARC::PointOnArc2D(CS_POINT &p, double *puval, CS_POINT *pnpnt, const double &toldist)
{
    double centerZ = ctr.z ; 
    double pZ = p.z ; 
    ctr.z = 0 ; // reset Z for 2D operation
    p.z = 0 ; 

    int retval = 0 ;
    CS_VECTOR vcp = CS_VECTOR(ctr, p).Unit() ; // unit vec from center to pnt
    vcp.z = 0.0 ; 
    CS_POINT np = ctr + (vcp * rad) ;
    double phi ; 

    // TO DO - modify below to work in any plane not just XY plane
    phi = vcp.AngleXY() ; 
    if (AngleOnSweep(phi))
    {   // then the point is within the sweep of the arc segment
        if (tcomp_PointsEQ(np.p, p.p, toldist))
            retval = 1 ; // point was actually on the arc segment
        if (pnpnt) *pnpnt = np ; 
        if (puval) *puval = AngleU(phi) ; 
    }
    else if (pnpnt || puval) 
    {   // The point is not within the sweep of the arc so see which end pnt
        // of the arc it is closest to
        CS_POINT sp = StartPoint() ; 
        CS_POINT ep = EndPoint() ; 
        double l1 = CS_VECTOR(sp, p).Mag() ; 
        double l2 = CS_VECTOR(ep, p).Mag() ; 
        if (l1 < l2)
        {
            if (pnpnt) *pnpnt = sp ; 
            if (puval) *puval = 0.0 ; 
        }
        else
        {
            if (pnpnt) *pnpnt = ep ; 
            if (puval) *puval = 1.0 ; 
        }
    }

    ctr.z = centerZ ; // restore the Z center value
    p.z = pZ ; 
    return retval ; // returns true only if p touches the arc
}


inline static int ArcsInOppositeDirection(double &swpa, double &swpb)
{
    if ((swpa > 0 && swpb < 0) || 
        (swpa < 0 && swpb > 0))
        return 1 ; 
    return 0 ; 
}

// SEE Notes: RR-Vol.1 Pgs 4-23, RR-Vol.2 Pg 52
int CS_ArcSeg::Intersect2D(CS_SegPtr pseg, CS_IRECList *pisset)
{
    if (pseg->SegmentType() == CS_Segment::LINE_TYPE)
    {
        CS_LineSeg *plseg = (CS_LineSeg *)pseg ; 
        CS_POINT p1, p2 ; 
        int numisects, isectcnt ;  
        double phi1, phi2 ;
        double u ; 

        CS_CIRCLE cir(*this) ; 
        CS_LINE ln(*plseg) ;

        CS_DEBUGIS1(
            fprintf(fpDebugOut, "Arc-Line intersection:\n") ; 
            Print(fpDebugOut) ; 
            lseg.Print(fpDebugOut) ; 
        ) ; 

        numisects = cir.Intersect2D(ln, p1, p2) ;
    
        CS_DEBUGAL
        ( 
            fprintf(fpDebugOut, "  CAL ni=%d p1=", numisects) ; 
            p1.Print(fpDebugOut) ; fprintf(fpDebugOut, " p2=") ; 
            p2.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ; 
        )

        if (numisects == 0)
            return 0 ; // line and arc do not intersect anywhere

        if (numisects == 1)
        {   // Then line is tangent to the arc
            CS_VECTOR vcp = CS_VECTOR(ctr, p1).Unit() ; 
            CS_POINT np = ctr + (vcp * rad) ;
            phi1 = vcp.AngleXY() ; 
            if (AngleOnSweep(phi1))
            {   // Then this is an intersect point on the arc segment
                // Now make sure it intersects the line segment
                if (plseg->PointOnSegment2D(p1,&u))
                {   // Then it intersects both line and arc so we have valid
                    // intersection point.
                    
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->ipnt[0] = p1 ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 
                    pisrec->cpp[0].u = AngleU(phi1) ; 
                    pisrec->cpp[1].u = pisrec->cpp[0].u ; 
                    pisrec->cps[0].u = u ;
                    pisrec->cps[1].u = u ; 
                    pisrec->statinfo = CS_IREC::POINT | CS_IREC::TANGENT ; 

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    return 1 ; 
                }
            }
            return 0 ; 
        }
    
        // else we have two intersect points to test
        isectcnt = 0 ; 

        CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - B\n") ; )
    
        CS_VECTOR vcp1 = CS_VECTOR(ctr, p1).Unit() ; 
        CS_POINT np1 = ctr + (vcp1 * rad) ;
        phi1 = vcp1.AngleXY() ; 
        CS_DEBUGAL(fprintf(fpDebugOut,"  CAL -  phi1=%.3lf\n", phi1 * RADIANStoDEGREES) ;) 
        if (AngleOnSweep(phi1))
        {   // Then this is an intersect point on the arc segment
            if (plseg->PointOnSegment2D(p1, &u))
            {
                CS_IREC *pisrec = new CS_IREC ;
                pisrec->ipnt[0] = p1 ;
                pisrec->cpp[0].s = this ; 
                pisrec->cpp[1].s = this ; 
                pisrec->cps[0].s = pseg ; 
                pisrec->cps[1].s = pseg ; 
                pisrec->cpp[0].u = AngleU(phi1) ; 
                pisrec->cpp[1].u = pisrec->cpp[0].u ; 
                pisrec->cps[0].u = u ;
                pisrec->cps[1].u = u ; 
                pisrec->statinfo = CS_IREC::POINT ; 
                
                CS_AddIRECToIRECList(pisset, pisrec) ;

                isectcnt++ ; 
                CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - C\n") ; )
            }
        }
    
        CS_VECTOR vcp2 = CS_VECTOR(ctr, p2).Unit() ; 
        CS_POINT np2 = ctr + (vcp2 * rad) ;
        phi2 = vcp2.AngleXY() ; 
        CS_DEBUGAL(fprintf(fpDebugOut,"  CAL -  phi2=%.3lf\n", phi2 * RADIANStoDEGREES) ;) 
        if (AngleOnSweep(phi2))
        {   // Then this is an intersect point on the arc segment
            if (plseg->PointOnSegment2D(p2, &u))
            {
                CS_IREC *pisrec = new CS_IREC ;
                pisrec->ipnt[0] = p2 ;
                pisrec->cpp[0].s = this ; 
                pisrec->cpp[1].s = this ; 
                pisrec->cps[0].s = pseg ; 
                pisrec->cps[1].s = pseg ; 
                pisrec->cpp[0].u = AngleU(phi2) ; 
                pisrec->cpp[1].u = pisrec->cpp[0].u ; 
                pisrec->cps[0].u = u ;
                pisrec->cps[1].u = u ; 
                pisrec->statinfo = CS_IREC::POINT ; 
                
                CS_AddIRECToIRECList(pisset, pisrec) ;
                isectcnt++ ; 
                CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - D\n") ; )
            }
        }

        CS_DEBUG(
            fprintf(fpDebugOut,"   %d Arc-Line isects at ua(%.5lf, %.5lf) ub(%.5lf, %.5lf)\n", 
                           isectcnt, uva[0], uva[1], uvb[0], uvb[1]) ;)

        CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - E\n") ; )
        return isectcnt ; 
    }
    else if (pseg->SegmentType() == ARC_TYPE)
    {
        //////////////////////////////////////////////////////////////////////
        // Returns 0 if no intersects, 3 if arcs are coincident and 
        // then 1 or 2 for the number of intersect points if distinct 
        // points of intersection are found. If 3 is returned then the 
        // u points u1 and u2 define a section within the *this arc from
        // a UPoint(u1) to UPoint(u2). If the return value is 4 then the
        // overlap area resulted in two arc sections. One of the two arc 
        // sections may be a point in this situation. u1 defines the first 
        // arc section in the range [0,u1] and u2 defines the second arc
        // section range of [u2,1]. Note the if u1==0 then what we have is
        // a point and an arc section. If u2 == 1 we also have a point and 
        // an arc section except the arc section is at the start of the 
        // *this arc and the point is the same as the end point of the *this
        // arc. Note that if the two end points of the arc only are returned
        // then u1=0, u2=1 and n=2 (since we have two matching endpoints). 
        // uvals must be allocated to  double[2]
        //////////////////////////////////////////////////////////////////////
        CS_ArcSeg *paseg = (CS_ArcSeg *)pseg ; 
        
        // See notes Oct 5, 1998 pp 22-23  RR-Vol1 for definition of variables
        // Assume that circle 1 is this and circle 2 is arc
        CS_POINT p1, p2 ; 
        CS_CIRCLE c1(*this) ; 
        CS_CIRCLE c2(*paseg) ; 
        int numisects, isectcount ; 
        double s,e,a,b ; // angles for the end points of the arcs
        int n ; 


        if ((numisects = c1.Intersect2D(c2, p1, p2)) < 1)
            return 0 ; // no intersects found

        CS_DEBUGI
        (
            fprintf(fpDebugOut,"Arc-Arc intersect, numisects=%d  @ ==>\n  ", numisects) ; 
            p1.Print(fpDebugOut) ; fprintf(fpDebugOut," and ") ; 
            p2.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        ) ;


        if (numisects == 3)
        {   // Then the arcs overlap. Figure out which sections of the arcs overlap
            // and return the angle range for the *this arc in terms of u values
            // for the overlap section (coincident section) 

            // Make sure that the start and end angles are oriented in the CCW
            // direction for testing purposes
            if (swp > 0)
            {
                s = mod2PI(sa) ; 
                e = mod2PI(sa + swp) ; 
            }
            else
            {
                e = mod2PI(sa) ; 
                s = mod2PI(sa + swp) ; 
            }


            if (paseg->swp > 0)
            {
                a = mod2PI(paseg->sa) ; 
                b = mod2PI(paseg->sa + paseg->swp) ; 
            }
            else
            {
                b = mod2PI(paseg->sa) ; 
                a = mod2PI(paseg->sa + paseg->swp) ; 
            }


            // See page 22-23 or RR-Vol1 for logic description
            // see updates page 52 RR-Vol2
            n = 0 ; 
 
            if (!AngleOnSweep(a)) 
            {   // Cases {1,2,3,4,5} possible
                if (!AngleOnSweep(b)) 
                {   // We are testing for case 1 and 5 
                    if (paseg->AngleOnSweep(s))
                    {   // Case 5
                        // Since we enclose all of the base arc we
                        // don't have to test it's orientation here
                        CS_IREC *pisrec = new CS_IREC ;
                        pisrec->ipnt[0] = StartPoint() ;
                        pisrec->ipnt[1] = EndPoint() ; 
                        pisrec->cpp[0].s = this ; 
                        pisrec->cpp[1].s = this ; 
                        pisrec->cps[0].s = pseg ; 
                        pisrec->cps[1].s = pseg ; 
                        pisrec->cpp[0].u = 0.0 ;  
                        pisrec->cpp[1].u = 1.0 ; 
                        
                        if (swp > 0)
                        {
                            pisrec->cps[0].u = paseg->AngleU(s) ; 
                            pisrec->cps[1].u = paseg->AngleU(e) ; 
                        }
                        else
                        {   // Arc was reversed
                            pisrec->cps[0].u = paseg->AngleU(e) ; 
                            pisrec->cps[1].u = paseg->AngleU(s) ; 
                        }

                        pisrec->statinfo = CS_IREC::OVERLAP ; 
                        if (ArcsInOppositeDirection(swp, paseg->swp))
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
            
                        CS_AddIRECToIRECList(pisset, pisrec) ;; 
                        n = 1 ;
                    }
                    else
                    {   // Case 1
                        n = 0 ; 
                    }
                }
                else if (AnglesEqual(b,s)) 
                {   // Case 2
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 
                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = 0.0 ; 
                        pisrec->cpp[1].u = 0.0 ; 
                    }
                    else
                    {
                        pisrec->cpp[0].u = 1.0 ; 
                        pisrec->cpp[1].u = 1.0 ; 
                    }
                    
                    pisrec->ipnt[0] = UPoint(pisrec->cpp[0].u) ;

                    if (paseg->swp > 0)
                    {
                        pisrec->cps[0].u = 1.0 ; 
                        pisrec->cps[1].u = 1.0 ; 
                    }
                    else
                    {   // Arc was reversed
                        pisrec->cps[0].u = 0.0 ; 
                        pisrec->cps[1].u = 0.0 ; 
                    }
                    pisrec->statinfo = CS_IREC::POINT ; 

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else if (AngleInSweep(b))
                {   // Case 3
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 

                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = 0.0 ; 
                        pisrec->cpp[1].u = AngleU(b) ; 
                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = paseg->AngleU(s) ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = paseg->AngleU(s) ; 
                            pisrec->cps[1].u = 0.0 ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        pisrec->cpp[0].u = AngleU(b) ; 
                        pisrec->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(s) ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(s) ; 
                        }
                    }

                    pisrec->ipnt[0] = UPoint(pisrec->cpp[0].u) ;
                    pisrec->ipnt[1] = UPoint(pisrec->cpp[1].u) ;

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else
                {   // Case 4 
                    // All of base arc so no direction testing needed
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->cpp[0].u = 0.0 ; 
                    pisrec->cpp[1].u = 1.0 ; 

                    pisrec->ipnt[0] = StartPoint() ;
                    pisrec->ipnt[1] = EndPoint() ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 

                    // secondary arc logic same as case 3
                    if (swp > 0)
                    {
                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = paseg->AngleU(s) ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = paseg->AngleU(s) ; 
                            pisrec->cps[1].u = 0.0 ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(s) ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(s) ; 
                        }
                    }

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
            }
            else if (AnglesEqual(a,s)) 
            {   // Possible cases are {6,7,8}
                if (AngleInSweep(b))
                {   // Case 6
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 

                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = 0.0 ; 
                        pisrec->cpp[1].u = AngleU(b) ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 0.0 ;
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        pisrec->cpp[0].u = AngleU(b) ;
                        pisrec->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 0.0 ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 1.0 ;
                        }
                    }

                    pisrec->ipnt[0] = UPoint(pisrec->cpp[0].u) ; 
                    pisrec->ipnt[1] = UPoint(pisrec->cpp[1].u) ; 

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else
                {   // Case 7 and 8
                    // All of base arc so no direction test needed
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->cpp[0].u = 0.0 ; 
                    pisrec->cpp[1].u = 1.0 ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 
                    
                    pisrec->ipnt[0] = StartPoint() ; 
                    pisrec->ipnt[1] = EndPoint() ; 

                    if (swp > 0)
                    {
                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            if (AnglesEqual(b, e))
                                pisrec->cps[1].u = 1.0 ; 
                            else
                                pisrec->cps[1].u = paseg->AngleU(e) ; 
                        }
                        else
                        {
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                            
                            pisrec->cps[0].u = 1.0 ; 
                            if (AnglesEqual(b, e))
                                pisrec->cps[1].u = 0.0 ; 
                            else
                                pisrec->cps[1].u = paseg->AngleU(e) ; 
                        }
                    }
                    else
                    {
                        if (paseg->swp > 0)
                        {
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 

                            if (AnglesEqual(b, e))
                                pisrec->cps[0].u = 1.0 ; 
                            else
                                pisrec->cps[0].u = paseg->AngleU(e) ; 
                            pisrec->cps[1].u = 0.0 ; 
                        }
                        else
                        {

                            if (AnglesEqual(b, e))
                                pisrec->cps[0].u = 0.0 ; 
                            else
                                pisrec->cps[0].u = paseg->AngleU(e) ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                    }

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
            }
            else if (AngleInSweep(a))
            {   // Cases {9,10,11,12,13}
                if (AngleInSweep(b))
                {   // Test cases 9 and 13
                    if (paseg->AngleInSweep(s))
                    {   // Case 13
                        // For this case we end up with two overlaps 
                        CS_IREC *pisrecA = new CS_IREC ;
                        pisrecA->cpp[0].s = this ; 
                        pisrecA->cpp[1].s = this ; 
                        pisrecA->cps[0].s = pseg ; 
                        pisrecA->cps[1].s = pseg ; 

                        CS_IREC *pisrecB = new CS_IREC ;
                        pisrecB->cpp[0].s = this ; 
                        pisrecB->cpp[1].s = this ; 
                        pisrecB->cps[0].s = pseg ; 
                        pisrecB->cps[1].s = pseg ; 

                        pisrecA->statinfo = CS_IREC::OVERLAP ; 
                        pisrecB->statinfo = CS_IREC::OVERLAP ; 

                        if (swp > 0)
                        {
                            pisrecA->cpp[0].u = 0.0 ; 
                            pisrecA->cpp[1].u = AngleU(b) ;
                            
                            pisrecB->cpp[0].u = AngleU(a) ; 
                            pisrecB->cpp[1].u = 1.0 ;

                            if (paseg->swp > 0)
                            {
                                pisrecA->cps[0].u = paseg->AngleU(s) ;
                                pisrecA->cps[1].u = 1.0 ;

                                pisrecB->cps[0].u = 0.0 ;
                                pisrecB->cps[1].u = paseg->AngleU(e) ;
                            }
                            else
                            {
                                pisrecA->cps[0].u = paseg->AngleU(s) ;
                                pisrecA->cps[1].u = 0.0 ;

                                pisrecB->cps[0].u = 1.0 ;
                                pisrecB->cps[1].u = paseg->AngleU(e) ;
                                
                                pisrecA->statinfo |= CS_IREC::BREVERSED ; 
                                pisrecB->statinfo |= CS_IREC::BREVERSED ; 
                            }
                        }
                        else
                        {
                            pisrecA->cpp[0].u = AngleU(b) ;
                            pisrecA->cpp[1].u = 1.0 ; 
                            
                            pisrecB->cpp[0].u = 0.0 ;
                            pisrecB->cpp[1].u = AngleU(a) ; 

                            if (paseg->swp > 0)
                            {
                                pisrecA->cps[0].u = 1.0 ;
                                pisrecA->cps[1].u = paseg->AngleU(s) ;

                                pisrecB->cps[0].u = paseg->AngleU(e) ;
                                pisrecB->cps[1].u = 0.0 ;

                                pisrecA->statinfo |= CS_IREC::BREVERSED ; 
                                pisrecB->statinfo |= CS_IREC::BREVERSED ; 
                            }
                            else
                            {
                                pisrecA->cps[0].u = 0.0 ;
                                pisrecA->cps[1].u = paseg->AngleU(s) ;

                                pisrecB->cps[0].u = paseg->AngleU(e) ;
                                pisrecB->cps[1].u = 1.0 ;
                            }
                        }

                        pisrecA->ipnt[0] = UPoint(pisrecA->cpp[0].u) ;
                        pisrecA->ipnt[1] = UPoint(pisrecA->cpp[1].u) ; 

                        pisrecB->ipnt[0] = UPoint(pisrecB->cpp[0].u) ;
                        pisrecB->ipnt[1] = UPoint(pisrecB->cpp[1].u) ; 

                        CS_AddIRECToIRECList(pisset, pisrecA) ; 
                        CS_AddIRECToIRECList(pisset, pisrecB) ; 
                        n = 2 ; 
                    }
                    else
                    {   // Case 9
                        CS_IREC *pisrec = new CS_IREC ;
                        pisrec->cpp[0].s = this ; 
                        pisrec->cpp[1].s = this ; 
                        pisrec->cps[0].s = pseg ; 
                        pisrec->cps[1].s = pseg ; 

                        pisrec->statinfo = CS_IREC::OVERLAP ; 

                        if (swp > 0)
                        {
                            pisrec->cpp[0].u = AngleU(a) ; 
                            pisrec->cpp[1].u = AngleU(b) ; 

                            if (paseg->swp > 0)
                            {
                                pisrec->cps[0].u = 0.0 ; 
                                pisrec->cps[1].u = 1.0 ; 
                            }
                            else
                            {   // Arc was reversed
                                pisrec->cps[0].u = 1.0 ; 
                                pisrec->cps[1].u = 0.0 ;
                                pisrec->statinfo |= CS_IREC::BREVERSED ; 
                            }
                        }
                        else
                        {
                            pisrec->cpp[0].u = AngleU(b) ; 
                            pisrec->cpp[1].u = AngleU(a) ; 

                            if (paseg->swp > 0)
                            {
                                pisrec->cps[0].u = 1.0 ; 
                                pisrec->cps[1].u = 0.0 ; 
                                pisrec->statinfo |= CS_IREC::BREVERSED ; 
                            }
                            else
                            {   // Arc was reversed
                                pisrec->cps[0].u = 0.0 ; 
                                pisrec->cps[1].u = 1.0 ;
                            }

                        }

                        pisrec->ipnt[0] = UPoint(pisrec->cpp[0].u) ; 
                        pisrec->ipnt[1] = UPoint(pisrec->cpp[1].u) ; 

                        // All of secondary arc so no direction test needed
                        CS_AddIRECToIRECList(pisset, pisrec) ;
                        n = 1 ; 
                    }
                }
                else if (AnglesEqual(b,e))
                {   // Case 10  
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 

                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = AngleU(a) ; 
                        pisrec->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                        else
                        {   // Arc was reversed
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 0.0 ;
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        pisrec->cpp[0].u = 0.0 ; 
                        pisrec->cpp[1].u = AngleU(a) ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 0.0 ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                        else
                        {   // Arc was reversed
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 1.0 ;
                        }

                    }

                    pisrec->ipnt[0] = UPoint(pisrec->cpp[0].u) ; 
                    pisrec->ipnt[1] = UPoint(pisrec->cpp[1].u) ; 

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else if (!AngleOnSweep(b))
                {   // Case 11
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    pisrec->statinfo = CS_IREC::OVERLAP ; 

                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = AngleU(a) ; 
                        pisrec->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(e) ; 
                        }
                        else
                        {   // Arc was reversed
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = paseg->AngleU(e) ; 
                            pisrec->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        pisrec->cpp[0].u = 0.0 ;
                        pisrec->cpp[1].u = AngleU(a) ;

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = paseg->AngleU(e) ;
                            pisrec->cps[1].u = 0.0 ;
                            pisrec->statinfo |= CS_IREC::BREVERSED ;
                        }
                        else
                        {   // Arc was reversed
                            pisrec->cps[0].u = paseg->AngleU(e) ; 
                            pisrec->cps[1].u = 1.0 ;
                        }
                    }

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else    
                {   // Case 12
                    // For this case: end up with two intesection set records
                    // one a point record and the other an overlap record
                    // Arbitrarily make the first record the point definition
                    CS_IREC *pisrec1 = new CS_IREC ;
                    pisrec1->cpp[0].s = this ; 
                    pisrec1->cpp[1].s = this ; 
                    pisrec1->cps[0].s = pseg ; 
                    pisrec1->cps[1].s = pseg ; 

                    CS_IREC *pisrec2 = new CS_IREC ;
                    pisrec2->cpp[0].s = this ; 
                    pisrec2->cpp[1].s = this ; 
                    pisrec2->cps[0].s = pseg ; 
                    pisrec2->cps[1].s = pseg ; 

                    pisrec1->statinfo = CS_IREC::POINT ; 
                    pisrec2->statinfo = CS_IREC::OVERLAP ; 

                    if (swp > 0)
                    {
                        pisrec1->cpp[0].u = 0.0 ; 
                        pisrec1->cpp[1].u = 0.0 ; 

                        pisrec2->cpp[0].u = AngleU(a) ; 
                        pisrec2->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec2->cps[0].u = 0.0 ; 
                            pisrec2->cps[1].u = paseg->AngleU(e) ; 
                        }
                        else
                        {
                            pisrec2->cps[0].u = 1.0 ; 
                            pisrec2->cps[1].u = paseg->AngleU(e) ; 
                            pisrec2->statinfo |= CS_IREC::BREVERSED ; 
                        }
                    }
                    else
                    {
                        pisrec1->cpp[0].u = 1.0 ; 
                        pisrec1->cpp[1].u = 1.0 ; 

                        pisrec2->cpp[0].u = 0.0 ; 
                        pisrec2->cpp[1].u = AngleU(a) ; 

                        if (paseg->swp > 0)
                        {
                            pisrec2->cps[0].u = paseg->AngleU(e) ; 
                            pisrec2->cps[1].u = 0.0 ; 
                            pisrec2->statinfo |= CS_IREC::BREVERSED ; 
                        }
                        else
                        {
                            pisrec2->cps[0].u = paseg->AngleU(e) ; 
                            pisrec2->cps[1].u = 1.0 ; 
                        }
                    }


                    // only define first point for point records
                    pisrec1->ipnt[0] = UPoint(pisrec1->cpp[0].u) ; 
                    
                    pisrec2->ipnt[0] = UPoint(pisrec2->cpp[0].u) ; 
                    pisrec2->ipnt[1] = UPoint(pisrec2->cpp[1].u) ; 
                    
                    CS_AddIRECToIRECList(pisset, pisrec1) ; 
                    CS_AddIRECToIRECList(pisset, pisrec2) ; 
                    n = 2 ; 
                }
            }
            else if (AnglesEqual(a,e))
            {   // Cases {14,15,16} 
                if (!AngleOnSweep(b))
                {   // Case 14
                    CS_IREC *pisrec = new CS_IREC ;
                    pisrec->cpp[0].s = this ; 
                    pisrec->cpp[1].s = this ; 
                    pisrec->cps[0].s = pseg ; 
                    pisrec->cps[1].s = pseg ; 

                    if (swp > 0)
                    {
                        pisrec->cpp[0].u = 1.0 ; 
                        pisrec->cpp[1].u = 1.0 ; 
                        pisrec->ipnt[0]   = EndPoint() ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 0.0 ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                    }
                    else
                    {
                        pisrec->cpp[0].u = 0.0 ; 
                        pisrec->cpp[1].u = 0.0 ; 
                        pisrec->ipnt[0]   = StartPoint() ; 

                        if (paseg->swp > 0)
                        {
                            pisrec->cps[0].u = 0.0 ; 
                            pisrec->cps[1].u = 0.0 ; 
                        }
                        else
                        {
                            pisrec->cps[0].u = 1.0 ; 
                            pisrec->cps[1].u = 1.0 ; 
                        }
                    }

                    pisrec->statinfo = CS_IREC::POINT ; 

                    CS_AddIRECToIRECList(pisset, pisrec) ;
                    n = 1 ; 
                }
                else if (AnglesEqual(b,s))
                {   // Case 15
                    // in this situation we have the two endpoints which touch
                    // Here we still have to do direction testing because we want
                    // the [0] and [1] array positions to match to corresponding
                    // intersection points for a and b
                    CS_IREC *pisrec1 = new CS_IREC ;
                    pisrec1->cpp[0].s = this ; 
                    pisrec1->cpp[1].s = this ; 
                    pisrec1->cps[0].s = pseg ; 
                    pisrec1->cps[1].s = pseg ; 

                    CS_IREC *pisrec2 = new CS_IREC ;
                    pisrec2->cpp[0].s = this ; 
                    pisrec2->cpp[1].s = this ; 
                    pisrec2->cps[0].s = pseg ; 
                    pisrec2->cps[1].s = pseg ; 


                    if (swp > 0)
                    {
                        pisrec1->cpp[0].u = 0.0 ; 
                        pisrec1->cpp[1].u = 0.0 ; 
                        pisrec2->cpp[0].u = 1.0 ; 
                        pisrec2->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec1->cps[0].u = 1.0 ; 
                            pisrec1->cps[1].u = 1.0 ; 
                            pisrec2->cps[0].u = 0.0 ; 
                            pisrec2->cps[1].u = 0.0 ;
                        }
                        else
                        {
                            pisrec1->cps[0].u = 0.0 ; 
                            pisrec1->cps[1].u = 0.0 ; 
                            pisrec2->cps[0].u = 1.0 ; 
                            pisrec2->cps[1].u = 1.0 ;
                        }
                    }
                    else
                    {
                        pisrec1->cpp[0].u = 0.0 ; 
                        pisrec1->cpp[1].u = 0.0 ; 
                        pisrec2->cpp[0].u = 1.0 ; 
                        pisrec2->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec1->cps[0].u = 0.0 ; 
                            pisrec1->cps[1].u = 0.0 ; 
                            pisrec2->cps[0].u = 1.0 ; 
                            pisrec2->cps[1].u = 1.0 ;
                        }
                        else
                        {
                            pisrec1->cps[0].u = 1.0 ; 
                            pisrec1->cps[1].u = 1.0 ; 
                            pisrec2->cps[0].u = 0.0 ; 
                            pisrec2->cps[1].u = 0.0 ;
                        }
                    }

                    
                    // These two points are the same
                    pisrec1->ipnt[0] = UPoint(pisrec1->cpp[0].u) ;
                    pisrec1->ipnt[1] = UPoint(pisrec1->cpp[1].u) ;

                    // And these two points are the same
                    pisrec2->ipnt[0] = UPoint(pisrec2->cpp[0].u) ;
                    pisrec2->ipnt[1] = UPoint(pisrec2->cpp[1].u) ;

                    pisrec1->statinfo = CS_IREC::POINT ; 
                    pisrec2->statinfo = CS_IREC::POINT ; 

                    CS_AddIRECToIRECList(pisset, pisrec1) ; 
                    CS_AddIRECToIRECList(pisset, pisrec2) ; 
                    n = 2 ; 
                }
                else
                {   // Case 16
                    CS_IREC *pisrec1 = new CS_IREC ;
                    pisrec1->cpp[0].s = this ; 
                    pisrec1->cpp[1].s = this ; 
                    pisrec1->cps[0].s = pseg ; 
                    pisrec1->cps[1].s = pseg ; 

                    CS_IREC *pisrec2 = new CS_IREC ;
                    pisrec2->cpp[0].s = this ; 
                    pisrec2->cpp[1].s = this ; 
                    pisrec2->cps[0].s = pseg ; 
                    pisrec2->cps[1].s = pseg ; 

                    pisrec1->statinfo = CS_IREC::OVERLAP ; 
                    pisrec2->statinfo = CS_IREC::POINT ; 

                    if (swp > 0)
                    {
                        pisrec1->cpp[0].u = 0.0 ; 
                        pisrec1->cpp[1].u = AngleU(b) ; 
                        pisrec2->cpp[0].u = 1.0 ; 
                        pisrec2->cpp[1].u = 1.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec1->cps[0].u = AngleU(s) ; 
                            pisrec1->cps[1].u = 1.0 ; 

                            pisrec2->cps[0].u = 0.0 ; 
                            pisrec2->cps[1].u = 0.0 ; 
                        }
                        else
                        {
                            pisrec1->cps[0].u = AngleU(s) ; 
                            pisrec1->cps[1].u = 0.0 ; 
                            pisrec1->statinfo |= CS_IREC::BREVERSED ; 

                            pisrec2->cps[0].u = 1.0 ; 
                            pisrec2->cps[1].u = 1.0 ; 
                        }
                    }
                    else
                    {
                        pisrec1->cpp[0].u = AngleU(b) ; 
                        pisrec1->cpp[1].u = 1.0 ; 
                        pisrec2->cpp[0].u = 0.0 ; 
                        pisrec2->cpp[1].u = 0.0 ; 

                        if (paseg->swp > 0)
                        {
                            pisrec1->cps[0].u = 1.0 ; 
                            pisrec1->cps[1].u = AngleU(s) ; 
                            pisrec1->statinfo |= CS_IREC::BREVERSED ; 

                            pisrec2->cps[0].u = 0.0 ; 
                            pisrec2->cps[1].u = 0.0 ; 
                        }
                        else
                        {
                            pisrec1->cps[0].u = 0.0 ; 
                            pisrec1->cps[1].u = AngleU(s) ; 

                            pisrec2->cps[0].u = 1.0 ; 
                            pisrec2->cps[1].u = 1.0 ; 
                        }
                    }

                    // 2 overlap points to be defined
                    pisrec1->ipnt[0] = UPoint(pisrec1->cpp[0].u) ;
                    pisrec1->ipnt[1] = UPoint(pisrec1->cpp[1].u) ;
                    
                    // and single intersect point to be defined
                    pisrec2->ipnt[0] = UPoint(pisrec2->cpp[0].u) ;

                    CS_AddIRECToIRECList(pisset, pisrec1) ; 
                    CS_AddIRECToIRECList(pisset, pisrec2) ; 
                    n = 2 ; 
                }
            }
            return n ; 
        }

        ///////////////////////////////////////////////////////////////
        // Else we have a standard intersection between two arcs
        // with at least one intersection point see if the points lie on
        // both of the arc segments
        CS_VECTOR vc1p1(ctr, p1)  ;
        CS_VECTOR vc2p1(paseg->ctr, p1) ; 
        isectcount = 0 ; 
        a = vc1p1.AngleXY() ;
        b = vc2p1.AngleXY() ;
        CS_DEBUG(fprintf(fpDebugOut,"Angle A=%.3lfdeg B=%.3lfdeg\n",
                    a * RADIANStoDEGREES, b * RADIANStoDEGREES)) ; 

        if (AngleOnSweep(a) && paseg->AngleOnSweep(b))
        {   // Then this point is on both arcs so it is a valid intersect point
            CS_IREC *pisrec = new CS_IREC ;
            pisrec->cpp[0].s = this ; 
            pisrec->cpp[1].s = this ; 
            pisrec->cps[0].s = pseg ; 
            pisrec->cps[1].s = pseg ; 

            pisrec->cpp[0].u = pisrec->cpp[1].u = AngleU(a) ; 
            pisrec->cps[0].u = pisrec->cps[1].u = paseg->AngleU(b) ;

            pisrec->ipnt[0] = p1 ; 
            pisrec->statinfo = CS_IREC::POINT ; 
            if (numisects == 1)
                pisrec->statinfo |= CS_IREC::TANGENT ; 
            CS_AddIRECToIRECList(pisset, pisrec) ;

            isectcount++ ;
        }

        if (numisects > 1)
        {   // Test the second point to see it is on both arcs
            CS_VECTOR vc1p2(ctr, p2) ;
            CS_VECTOR vc2p2(paseg->ctr, p2) ; 
            a = vc1p2.AngleXY() ;
            b = vc2p2.AngleXY() ;
            if (AngleOnSweep(a) && paseg->AngleOnSweep(b))
            {   // Then this point is on both arcs so it is a valid intersect point
                CS_IREC *pisrec = new CS_IREC ;
                pisrec->cpp[0].s = this ; 
                pisrec->cpp[1].s = this ; 
                pisrec->cps[0].s = pseg ; 
                pisrec->cps[1].s = pseg ; 

                pisrec->cpp[0].u = pisrec->cpp[1].u = AngleU(a) ; 
                pisrec->cps[0].u = pisrec->cps[1].u = paseg->AngleU(b) ;

                pisrec->ipnt[0] = p2 ; 
                pisrec->statinfo = CS_IREC::POINT ; 
                CS_AddIRECToIRECList(pisset, pisrec) ;

                isectcount++ ;
            }
        }

        return isectcount ; 
    }

    // Else we have an unhandled segment type so do nothing for now
    return 0 ; 

}

// Calculate the intersection of a line segment and an arc segment
// uvals must be allocated to  double[2]
int CS_ArcSeg::Intersect2D(CS_LineSeg &lseg, double *uva, double *uvb)
{
    CS_POINT p1, p2 ; 
    int numisects, isectcnt ;  
    double phi1, phi2 ;
    double u ; 

    CS_CIRCLE cir(*this) ; 
    CS_LINE ln(lseg) ;

    CS_DEBUGIS1(
        fprintf(fpDebugOut,"Arc-Line intersection:\n") ; 
        Print(fpDebugOut) ; 
        lseg.Print(fpDebugOut) ; 
    ) ; 

    numisects = cir.Intersect2D(ln, p1, p2) ;
    
    CS_DEBUGAL
    ( 
        fprintf(fpDebugOut,"  CAL ni=%d p1=", numisects) ; 
        p1.Print(fpDebugOut) ; fprintf(fpDebugOut," p2=") ; 
        p2.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
    )


    if (numisects == 0)
        return 0 ; // line and arc do not intersect anywhere

    if (numisects == 1)
    {   // Then line is tangent to the arc
        CS_VECTOR vcp = CS_VECTOR(ctr, p1).Unit() ; 
        CS_POINT np = ctr + (vcp * rad) ;
        phi1 = vcp.AngleXY() ; 
        if (AngleOnSweep(phi1))
        {   // Then this is an intersect point on the arc segment
            // Now make sure it intersects the line segment
            if (lseg.PointOnSegment2D(p1,&u))
            {   // Then it intersects both line and arc so we have valid
                // intersection point.
                uva[0] = AngleU(phi1) ; 
                uvb[0] = u ; 
                CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - A\n") ; )
                return 1 ; 
            }
        }
        return 0 ; 
    }
    
    // else we have two intersect points to test
    isectcnt = 0 ; 

    CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - B\n") ; )
    
    CS_VECTOR vcp1 = CS_VECTOR(ctr, p1).Unit() ; 
    CS_POINT np1 = ctr + (vcp1 * rad) ;
    phi1 = vcp1.AngleXY() ; 
    CS_DEBUGAL(fprintf(fpDebugOut,"  CAL -  phi1=%.3lf\n", phi1 * RADIANStoDEGREES) ;) 
    if (AngleOnSweep(phi1))
    {   // Then this is an intersect point on the arc segment
        if (lseg.PointOnSegment2D(p1, &u))
        {
            uva[isectcnt] = AngleU(phi1) ; 
            uvb[isectcnt] = u ; 
            isectcnt++ ; 
            CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - C\n") ; )
        }
    }
    
    CS_VECTOR vcp2 = CS_VECTOR(ctr, p2).Unit() ; 
    CS_POINT np2 = ctr + (vcp2 * rad) ;
    phi2 = vcp2.AngleXY() ; 
    CS_DEBUGAL(fprintf(fpDebugOut,"  CAL -  phi2=%.3lf\n", phi2 * RADIANStoDEGREES) ;) 
    if (AngleOnSweep(phi2))
    {   // Then this is an intersect point on the arc segment
        if (lseg.PointOnSegment2D(p2, &u))
        {
            uva[isectcnt] = AngleU(phi2) ; 
            uvb[isectcnt] = u ; 
            isectcnt++ ; 
            CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - D\n") ; )
        }
    }

    CS_DEBUG(
        fprintf(fpDebugOut,"   %d Arc-Line isects at ua(%.5lf, %.5lf) ub(%.5lf, %.5lf)\n", 
                       isectcnt, uva[0], uva[1], uvb[0], uvb[1]) ;)

    CS_DEBUGAL(fprintf(fpDebugOut,"   CAL - E\n") ; )
    return isectcnt ; 
}


//////////////////////////////////////////////////////////////////////
// Returns 0 if no intersects, 3 if arcs are coincident and 
// then 1 or 2 for the number of intersect points if distinct 
// points of intersection are found. If 3 is returned then the 
// u points u1 and u2 define a section within the *this arc from
// a UPoint(u1) to UPoint(u2). If the return value is 4 then the
// overlap area resulted in two arc sections. One of the two arc 
// sections may be a point in this situation. u1 defines the first 
// arc section in the range [0,u1] and u2 defines the second arc
// section range of [u2,1]. Note the if u1==0 then what we have is
// a point and an arc section. If u2 == 1 we also have a point and 
// an arc section except the arc section is at the start of the 
// *this arc and the point is the same as the end point of the *this
// arc. Note that if the two end points of the arc only are returned
// then u1=0, u2=1 and n=2 (since we have two matching endpoints). 
// uvals must be allocated to  double[2]
//
// TO DO - clean this up and integrate with the Arc-Seg intersect
//         routine above. 
//////////////////////////////////////////////////////////////////////
int CS_ArcSeg::Intersect2D(CS_ArcSeg &arc, double *uva, double *uvb)
{
    // See notes Oct 5, 1998 pp 22-23  RR-Vol1 for definition of variables
    // Assume that circle 1 is this and circle 2 is arc
    CS_POINT p1, p2 ; 
    CS_CIRCLE c1(*this) ; 
    CS_CIRCLE c2(arc) ; 
    int numisects, isectcount ; 
    double s,e,a,b ; // angles for the end points of the arcs
    int n ; 


    if ((numisects = c1.Intersect2D(c2, p1, p2)) < 1)
        return 0 ; // no intersects found

    CS_DEBUGI
    (
        fprintf(fpDebugOut,"Arc-Arc intersect, numisects=%d  @ ==>\n  ", numisects) ; 
        p1.Print(fpDebugOut) ; fprintf(fpDebugOut," and ") ; 
        p2.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
    ) ;


    if (numisects == 3)
    {   // Then the arcs overlap. Figure out which sections of the arcs overlap
        // and return the angle range for the *this arc in terms of u values
        // for the overlap section (coincident section) 

        // Make sure that the start and end angles are oriented in the CCW
        // direction for testing purposes
        if (swp > 0)
        {
            s = mod2PI(sa) ; 
            e = mod2PI(sa + swp) ; 
        }
        else
        {
            e = mod2PI(sa) ; 
            s = mod2PI(sa + swp) ; 
        }


        if (arc.swp > 0)
        {
            a = mod2PI(arc.sa) ; 
            b = mod2PI(arc.sa + arc.swp) ; 
        }
        else
        {
            b = mod2PI(arc.sa) ; 
            a = mod2PI(arc.sa + arc.swp) ; 
        }


        // See page 22-23 or RR-Vol1 for logic description
        // see updates page 52 RR-Vol2
        n = 0 ; 
     
        if (!AngleOnSweep(a)) 
        {   // Cases {1,2,3,4,5} possible
            if (!AngleOnSweep(b)) 
            {   // We are testing for case 1 and 5 
                if (arc.AngleOnSweep(s))
                {   // Case 5
                    // Since we enclose all of the base arc we
                    // don't have to test it's orientation here
                    uva[0] = 0.0 ; 
                    uva[1] = 1.0 ; 
                    if (arc.swp > 0)
                    {
                        uvb[0] = arc.AngleU(s) ; 
                        uvb[1] = arc.AngleU(e) ; 
                    }
                    else
                    {   // Arc was reversed
                        uvb[0] = arc.AngleU(e) ; 
                        uvb[1] = arc.AngleU(s) ; 
                    }
                    n = 3 ;
                }
                else
                {   // Case 1
                    n = 0 ; 
                }
            }
            else if (AnglesEqual(b,s)) 
            {   // Case 2
                if (swp > 0)
                    uva[0] = 0.0 ; 
                else
                    uva[0] = 1.0 ; 

                if (arc.swp > 0)
                    uvb[0] = 1.0 ; 
                else
                    uvb[0] = 0.0 ; 
                n = 1 ; 
            }
            else if (AngleInSweep(b))
            {   // Case 3
                if (swp > 0)
                {
                    uva[0] = 0.0 ; 
                    uva[1] = AngleU(b) ; 
                }
                else
                {
                    uva[0] = AngleU(b) ; 
                    uva[1] = 1.0 ; 
                }

                if (arc.swp > 0)
                {
                    uvb[0] = arc.AngleU(s) ; 
                    uvb[1] = 1.0 ; 
                }
                else
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = arc.AngleU(s) ; 
                }
                n = 3 ; 
            }
            else
            {   // Case 4 
                // All of base arc so no direction testing needed
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ; 

                // secondary arc logic same as case 3
                if (arc.swp > 0)
                {
                    uvb[0] = arc.AngleU(s) ; 
                    uvb[1] = 1.0 ; 
                }
                else
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = arc.AngleU(s) ; 
                }
                n = 3 ; 
            }
        }
        else if (AnglesEqual(a,s)) 
        {   // Possible cases are {6,7,8}
            if (AngleInSweep(b))
            {   // Case 6
                if (swp > 0)
                {
                    uva[0] = 0.0 ; 
                    uva[1] = AngleU(b) ; 
                }
                else
                {
                    uva[0] = AngleU(b) ; 
                    uva[1] = 1.0 ; 
                }

                // All of secondary arc so no direction test needed
                uvb[0] = 0.0 ; 
                uvb[1] = 1.0 ; 

                n = 3 ; 
            }
            else
            {   // Case 7 and 8
                // All of base arc so no direction test needed
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ;
                
                if (AnglesEqual(b,e))
                {   // Case 7
                    uvb[0] = 0.0 ; 
                    uvb[1] = 1.0 ; 
                }
                else
                {   // Case 8
                    if (arc.swp > 0)
                    {
                        uvb[0] = 0.0 ; 
                        uvb[1] = arc.AngleU(e) ; 
                    }
                    else
                    {
                        uvb[0] = arc.AngleU(e) ; 
                        uvb[1] = 1.0 ; 
                    }
                }

                n = 3 ; 
            }
        }
        else if (AngleInSweep(a))
        {   // Cases {9,10,11,12,13}
            if (AngleInSweep(b))
            {   // Test cases 9 and 13
                if (arc.AngleInSweep(s))
                {   // Case 13
                    if (swp > 0)
                    {
                        uva[0] = AngleU(b) ; 
                        uva[1] = AngleU(a) ; 
                    }
                    else
                    {
                        uva[0] = AngleU(a) ; 
                        uva[1] = AngleU(b) ; 
                    }

                    if (arc.swp > 0)
                    {
                        uvb[0] = arc.AngleU(e) ; 
                        uvb[1] = arc.AngleU(s) ; 
                    }
                    else
                    {
                        uvb[0] = arc.AngleU(s) ; 
                        uvb[1] = arc.AngleU(e) ; 
                    }

                    n = 4 ; 
                }
                else
                {   // Case 9
                    if (swp > 0)
                    {
                        uva[0] = AngleU(a) ; 
                        uva[1] = AngleU(b) ; 
                    }
                    else
                    {
                        uva[0] = AngleU(b) ; 
                        uva[1] = AngleU(a) ; 
                    }

                    // All of secondary arc so no direction test needed
                    uvb[0] = 0.0 ; 
                    uvb[1] = 1.0 ; 
                    n = 3 ; 
                }
            }
            else if (AnglesEqual(b,e))
            {   // Case 10  
                if (swp > 0)
                {
                    uva[0] = AngleU(a) ; 
                    uva[1] = 1.0 ; 
                }
                else
                {
                    uva[0] = 0.0 ; 
                    uva[1] = AngleU(a) ; 
                }

                // All of secondary arc so no direction test needed
                uvb[0] = 0.0 ; 
                uvb[1] = 1.0 ; 
                n = 3 ;
            }
            else if (!AngleOnSweep(b))
            {   // Case 11
                if (swp > 0)
                {
                    uva[0] = AngleU(a) ; 
                    uva[1] = 1.0 ; 
                }
                else
                {
                    uva[0] = 0.0 ;
                    uva[1] = AngleU(a) ; 
                }

                if (arc.swp > 0)
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = arc.AngleU(e) ; 
                }
                else
                {
                    uvb[0] = arc.AngleU(e) ; 
                    uvb[1] = 1.0 ; 
                }

                n = 3 ; 
            }
            else    
            {   // Case 12
                if (swp > 0)
                {
                    uva[0] = 0.0 ; 
                    uva[1] = AngleU(a) ; 
                }
                else
                {
                    uva[0] = AngleU(a) ; 
                    uva[1] = 1.0 ; 
                }

                if (arc.swp > 0)
                {
                    uvb[0] = arc.AngleU(e) ; 
                    uvb[1] = 1.0 ; 
                }
                else
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = arc.AngleU(e) ; 
                }

                n = 4 ; 
            }
        }
        else if (AnglesEqual(a,e))
        {   // Cases {14,15,16} 
            if (!AngleOnSweep(b))
            {   // Case 14
                if (swp > 0)
                    uva[0] = 1.0 ; 
                else
                    uva[0] = 0.0 ; 

                if (arc.swp > 0)
                    uvb[0] = 0.0 ; 
                else
                    uvb[0] = 1.0 ; 

                n = 1 ; 
            }
            else if (AnglesEqual(b,s))
            {   // Case 15
                // in this situation we have the two endpoints which touch
                // Here we still have to do direction testing because we want
                // the [0] and [1] array positions to match to corresponding
                // intersection points for a and b

                if (swp > 0)
                {
                    uva[0] = 0.0 ; 
                    uva[1] = 1.0 ; 
                }
                else
                {
                    uva[0] = 1.0 ; 
                    uva[1] = 0.0 ; 
                }

                if (arc.swp > 0)
                {
                    uvb[0] = 1.0 ; 
                    uvb[1] = 0.0 ; 
                }
                else
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = 1.0 ; 
                }
                n = 2 ; 
            }
            else
            {   // Case 16
                if (swp > 0)
                {
                    uva[0] = AngleU(b) ; 
                    uva[1] = 1.0 ; 
                }
                else
                {
                    uva[0] = 0.0 ; 
                    uva[1] = AngleU(b) ; 
                }

                if (arc.swp > 0)
                {
                    uvb[0] = 0.0 ; 
                    uvb[1] = arc.AngleU(s) ; 
                }
                else
                {
                    uvb[0] = arc.AngleU(s) ; 
                    uvb[1] = 1.0 ; 
                }
                n = 4 ; 
            }
        }
        return n ; 
    }

    ///////////////////////////////////////////////////////////////
    // Else we have a standard intersection between two arcs
    // with at least one intersection point see if the points lie on
    // both of the arc segments
    CS_VECTOR vc1p1(ctr, p1)  ;
    CS_VECTOR vc2p1(arc.ctr, p1) ; 
    isectcount = 0 ; 
    a = vc1p1.AngleXY() ;
    b = vc2p1.AngleXY() ;
    CS_DEBUG(fprintf(fpDebugOut,"Angle A=%.3lfdeg B=%.3lfdeg\n",
                a * RADIANStoDEGREES, b * RADIANStoDEGREES)) ; 

    if (AngleOnSweep(a) && arc.AngleOnSweep(b))
    {   // Then this point is on both arcs so it is a valid intersect point
        uva[isectcount] = AngleU(a) ; 
        uvb[isectcount] = arc.AngleU(b) ;
        isectcount++ ;
    }

    if (numisects > 1)
    {   // Test the second point to see it is on both arcs
        CS_VECTOR vc1p2(ctr, p2)  ;
        CS_VECTOR vc2p2(arc.ctr, p2) ; 
        a = vc1p2.AngleXY() ;
        b = vc2p2.AngleXY() ;
        if (AngleOnSweep(a) && arc.AngleOnSweep(b))
        {   // Then this point is on both arcs so it is a valid intersect point
            uva[isectcount] = AngleU(a) ; 
            uvb[isectcount] = arc.AngleU(b) ;
            isectcount++ ;
        }
    }

    return isectcount ; 
}
