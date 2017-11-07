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
// arcgeom.cpp - special geometric routines applying to arcs

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif

/////////////
// CS_ARC  //
/////////////

// arcdir == CW or CCW, the start point determines the radius

void CS_ARC::SetCtrSPEP(CS_POINT &newctr, CS_POINT &sp, CS_POINT &ep, int direction) 
{
    ctr = newctr ; 
    CS_VECTOR vs(ctr, sp) ;
    CS_VECTOR ve(ctr, ep) ;
    double asp, aep ;
    asp = vs.AngleXY() ;
    aep = ve.AngleXY() ;
    swp = arc_sweep(asp, aep, direction) ;
    sa = asp ;
    if (direction == CW)
    {   // It's CW so reverse the sweep
	swp = -swp ;
    }
    rad = vs.Mag() ;
}

void CS_ARC::SetSPEP(CS_POINT &sp, CS_POINT &ep, int arcdir)
{
    CS_VECTOR vs(ctr, sp) ;
    CS_VECTOR ve(ctr, ep) ;
    double asp, aep ;
    asp = vs.AngleXY() ;
    aep = ve.AngleXY() ;
    swp = arc_sweep(asp, aep, arcdir) ;
    sa = asp ;
    if (arcdir == CW)
    {   // It's CW so reverse the sweep
	swp = -swp ;
    }
    rad = vs.Mag() ;
}


// force the arc segment clockwise
void CS_ARC::SetCW()
{
    if (swp > 0)
        CS_ARC::Reverse() ; 
    // else it's already CW
}

void CS_ARC::SetCCW()
{
    if (swp < 0)
        CS_ARC::Reverse() ; 
}

// Given an angle which is contained within the arc. return the U value
// for the point along the arc at that angle
double CS_ARC::AngleU(double alpha)
{
    // First we need to determine which end we are working from.
    // The U value is calculated as a ratio of the angle deltas from the
    // start point. Work it assuming a CCW arc and if the arc is reversed
    // the the result is max((1-u),0) that was calculated. The max
    // function is just in case we get a negative number after the subtract
    if (tcomp_EQZ(swp, RADCOMPARETOLERANCE))
	return 0.0 ; // doesn't matter since arc is so short anyway

    double start_angle = mod2PI(sa) ; 

    alpha = mod2PI(alpha) ; // [0,2PI)
    double u ;

    if (CS_AnglesEqual(start_angle, alpha))
    {
        return 0.0 ;
    }
    else
    {
        double swp2 ; 
        swp2 = arc_sweep(start_angle, alpha, swp > 0 ? CCW : CW) ;
        u = swp2 / fabs(swp) ; 

        return u ; 
    }
    return -1 ; // error (can't ever get here anyways)
}


// Returns the angle along the arc at the given u value. u must be in
// the range 0 to 1. The angles range [sa, sa+swp] is mapped onto the
// the [0,1] range to get the end result. The angle returned is in
// radians.
double CS_ARC::UAngle(double u)
{
    // The angle swp is our effective delta, where a udelta of 0 corresponds
    // to an angle delta of 0 and a udelta of 1.0 is an angle delta = swp
    return mod2PI(sa + u * swp) ;
}

//! \f$u\in[0,1]\f$ assumes arc is parallel to the XY plane
CS_POINT CS_ARC::UPoint(double u)
{
    CS_POINT upnt ;
    double phi = UAngle(u) ; 

    upnt.p[0] = rad * cos(phi) ;
    upnt.p[1] = rad * sin(phi) ;
    upnt.p[2] = 0 ;

    upnt = upnt + ctr ;

    if (pxfrm)
        upnt = *pxfrm * upnt ; 

    return upnt ;
}


//! Returns the side of the arc that the point lies on
int CS_ARC::PointSide(CS_POINT &pnt)
{
    CS_POINT pntnear ;
    double unear ;

    if (PointOnArc(pnt, &unear, &pntnear))
        return CS_COLLINEAR ; 

    if (tcomp_GT(unear, 0.0) && tcomp_LT(unear, 1.0))
    {   // Then the point is within the sweep of the arc
        CS_VECTOR vcp(ctr, pnt) ; 
        if (vcp.Mag() < rad)
        {   // Then it's inside the circle defined by the arc
            if (swp > 0)
                return CS_LEFTSIDE ; 
            return CS_RIGHTSIDE ;
        }
        // else it's outside the circle defined by the arc
        if (swp < 0)
            return CS_LEFTSIDE ; 
        return CS_RIGHTSIDE ;
    }

    // Else we have to use the end point tangent lines to determine the 
    // side that the point is on. (See notes Geom Algo's Vol4 pg 15)
    CS_VECTOR vtan ; 
    CS_POINT lnpnt ; 
    if (unear <= 0.5)
    {   // Then use start point tangent line
        vtan = UTangent(0.0) ; 
        lnpnt = StartPoint() ; 
    }
    else
    {   // use end point tangent line
        vtan = UTangent(1.0) ; 
        lnpnt = EndPoint() ; 
    }

    CS_LINE tstln(lnpnt, lnpnt + vtan) ; 
    int side = tstln.PointSide(pnt) ; 
    if (side == CS_COLLINEAR)
    {
        if (swp > 0)
        {   // The CCW arc
            return CS_RIGHTSIDE ; 
        }
        else
        {   // CW arc 
            return CS_LEFTSIDE ; 
        }   
    }
    
    return side ;
}


//////////////////////////////////////////////////////////////////////////
// TO DO - this doesn't really work since if an arc gets rotated about an
//   axis by more than 90 degrees, then its direction (CW,CCW) flips
//   after passing that point. So for this to work, the arc must have
//   and two orientation vectors (vx,vy) say which define the plane that
//   the arc is in. From vx, and vy we can generate vz which gives us
//   our final rotation direction. Thus by applying the matrix transform
//   to all the components, vx, vy, center, and start angle, then we
//   reliably rotate the arc in space.
// Since for now we are processing things in a 2D plane, the only rotation
// we have to worry about is one where we rotate about the Y axis 180 degrees
// effectively mirroring the arc across the y axis, or similarly for the
// X axis. In either of these two cases the direction of the arc must flip
// If the z component of the vcs x vce changes sign after the rotation,
// then flip the arcs direction.

/*
void CS_ARC::MTX3Mult(CS_MTX3 &m)
{
    CS_POINT sp = StartPoint() ;
    CS_POINT mp = MidPoint() ; 
    CS_POINT ep = EndPoint() ;
    CS_VECTOR vcsold(ctr, sp) ;
    CS_VECTOR vceold(ctr, ep) ;

    // CS_POINT ep = EndPoint() ;
    sp = m * sp ;
    ep = m * ep ;
    ctr = m * ctr ;
    // Now work out the new start angle
    CS_VECTOR vcs(ctr, sp) ;
    CS_VECTOR vce(ctr, ep) ;

    double zco, zcn ;

    if (tcomp_EQ(swp, RADIAN180))
    {
        CS_VECTOR vcmold(ctr, mp) ; 
        mp = m * mp ;
        CS_VECTOR vcm(ctr, mp) ; 
        zco = ZCross(vcsold, vcmold) ; 
        zcn = ZCross(vcs, vcm) ; 
    }
    else    
    {   // Simply take cross products of center->end points line segments
        zco = ZCross(vcsold, vceold) ;
        zcn = ZCross(vcs, vce) ;
    }

    if ((zco > 0 && zcn < 0) ||
	(zco < 0 && zcn > 0))
    {	// This is a standard case where the start and end point vectors are
        // not colinear
        // Here we have flipped the arc over
	// Thus the direction has changed
        swp = -swp ; 
    }
    sa = vcs.AngleXY() ;
}

*/

// This was redone, replacing the code above which didn't deal with
// scaling transformations
void CS_ARC::MTX3Mult(CS_MTX3 &mx)
{
    CS_POINT sp = StartPoint() ;
    CS_POINT mp = MidPoint() ; 
    CS_POINT ep = EndPoint() ;

    sp = mx * sp ;
    mp = mx * mp ;
    ep = mx * ep ;

    Arc3Points(sp, mp, ep) ;
}

void CS_ARC::Scale(double s)
{
    ctr = ctr * s ;
    rad = rad * s ;
}

void CS_ARC::Move(CS_VECTOR &v)
{
    ctr = ctr + v ;
}

void CS_ARC::SetZ(double z)
{
    ctr.z = z ; 
}


void CS_ARC::Transform(double p[12])
{
    CS_MTX3 m3 ; 
    m3.m[0] = p[0] ; 
    m3.m[1] = p[1] ; 
    m3.m[2] = p[2] ; 
    m3.m[3] = p[4] ; 
    m3.m[4] = p[5] ; 
    m3.m[5] = p[6] ; 
    m3.m[6] = p[8] ; 
    m3.m[7] = p[9] ; 
    m3.m[8] = p[10] ; 

    MTX3Mult(m3) ; 

    Move(CS_VECTOR(p[3], p[7], p[11])) ; 
}

CS_POINT CS_ARC::MidPoint(void)
{
    return UPoint(0.5) ;
}

CS_POINT CS_ARC::StartPoint(void)
{
    return UPoint(0.0) ;
}

CS_POINT CS_ARC::EndPoint(void)
{
    return UPoint(1.0) ;
}

double CS_ARC::ArcLength(void)
{
    return rad * fabs(swp) ; 
}

CS_POINT CS_ARC::Centroid(void)
{
    return CS_ARC::Centroid2D() ; 
}

// Arc must be parallel to XY plane for this result to work
CS_POINT CS_ARC::Centroid2D(void)
{
    if (tcomp_EQ(swp, RADIAN360, RADCOMPARETOLERANCE))
        return ctr ; 
    if (tcomp_EQZ(swp, RADCOMPARETOLERANCE))
        return StartPoint() ; 

    double ea = sa + swp ; 

    CS_POINT centroid ; 
    centroid.x = rad * (sin(ea) - sin(sa)) / (ea - sa) ; 
    centroid.y = rad * (cos(sa) - cos(ea)) / (ea - sa) ; 
    
    // Translate the centroid based on the center of the arc
    centroid += ctr ; // this takes care of Z component as well

    return centroid ; 
}


CS_VECTOR CS_ARC::UTangent(double u)
{
    CS_POINT tpnt = UPoint(u) ;
    CS_VECTOR vrtan = tpnt - ctr ;
    vrtan = vrtan.Unit() ;
    if (swp < 0)  
	return vrtan.RightPerp() ;
    else
	return vrtan.LeftPerp() ;

}


int CS_ARC::Offset(double delta)
{
    if (((swp < 0) && (delta > 0.0)) ||
	((swp > 0) && (delta < 0.0)))
    {	// Then we are shifting the arc towards the center
	delta = fabs(delta) ;
	if (delta > rad)
	{
	    rad = delta - rad ;
            // Inverts the sense of the arc
            // used when offsetting towards the center through a distance 
            // greater than the radius of the circle
            // The start angle is going to be pi rads from the current start
            // angle since it is being reflected through the center of the arc
            // The sweep of the arc will not change.
            sa = mod2PI(sa + RADIAN180) ; 
            return CRV_ARCCONVEX ; // set inversion indicator
        }
	else
	{
	    rad = rad - delta ;
	}
    }
    else
    {	// We are shifting the arc out from the center
	rad += fabs(delta) ;
    }
    return 0 ; 
}

int CS_ARC::ArcDir()
{
    if (swp < 0)
	return CW ;
    return CCW ;
}

// returns true if phi is within sweep of the arc including the endpoints
int CS_ARC::AngleOnSweep(double phi)
 {
    // Check for the full circle special case
    if (tcomp_EQ(fabs(swp), RADIAN360, RADCOMPARETOLERANCE))
        return 1 ; // must be true

    // For this test we use positive angles only
    double start_angle, end_angle ;

    phi = mod2PI(phi) ;

    // For this logic to work the Arc has to be CCW
    // thus start_angle and end_angle are CCW along the arc
    if (swp > 0)
    {
        start_angle = mod2PI(sa) ;
        end_angle = mod2PI(sa + swp) ;
    }
    else
    {
        end_angle = mod2PI(sa) ;
        start_angle = mod2PI(sa + swp) ;
    }

    CS_DEBUGAL(fprintf(fpDebugOut,
	"Testing angle %.5lf on arc sa=%.5lf ea=%.5lf swp=%.5lf\n",
		phi, start_angle, end_angle, swp) ;)

    if (end_angle < start_angle)
    {	// first test case if we cross the +x axis with the arc
	CS_DEBUGAL(fprintf(fpDebugOut, "  End<Start\n")) ;
	if (tcomp_LEQ(phi, end_angle, RADCOMPARETOLERANCE) 
            || tcomp_GEQ(phi, start_angle, RADCOMPARETOLERANCE))
	{
	    CS_DEBUGAL(fprintf(fpDebugOut,"  AonSwp (1)\n")) ;
	    return 1 ; // then angle is contained in the arc
	}
    }
    else
    {
	CS_DEBUGAL(fprintf(fpDebugOut,"  End >= Start\n")) ;
	if ((tcomp_GEQ(phi, start_angle, RADCOMPARETOLERANCE) && 
             tcomp_LEQ(phi, end_angle, RADCOMPARETOLERANCE)) 
            || (tcomp_LEQ(phi + RADIAN360, end_angle, RADCOMPARETOLERANCE))) 
	{
	    CS_DEBUGAL(fprintf(fpDebugOut,"  AonSwp (2)\n")) ;
	    return 1 ;
	}

    }
    CS_DEBUGAL(fprintf(fpDebugOut,"  AonSwp (0)\n")) ;

    // Test one last special case at the 0/2pi boundary
    if (tcomp_EQ(RADIAN360, phi, RADCOMPARETOLERANCE))
        phi = 0 ; 
    if (tcomp_EQ(RADIAN360, start_angle, RADCOMPARETOLERANCE))
        start_angle = 0 ; 
    if (tcomp_EQ(RADIAN360, end_angle, RADCOMPARETOLERANCE))
        end_angle = 0 ; 

    if (tcomp_EQ(phi, start_angle, RADCOMPARETOLERANCE) || 
        tcomp_EQ(phi, end_angle, RADCOMPARETOLERANCE))
        return 1 ; 
    return 0 ;
}

// returns true if phi is within sweep of the arc including the endpoints
int CS_ARC::AngleOnSweepX(double phi)
{
    // Check for the full circle special case
    if (tcomp_EQ(swp, RADIAN360, RADCOMPARETOLERANCE))
        return 1 ; // must be true

    // For this test we use positive angles only
    double start_angle, end_angle ;

    phi = mod2PI(phi) ;

    // For this logic to work the Arc has to be CCW
    // thus start_angle and end_angle are CCW along the arc
    if (swp > 0)
    {
        start_angle = mod2PI(sa) ;
        end_angle = mod2PI(sa + swp) ;
    }
    else
    {
        end_angle = mod2PI(sa) ;
        start_angle = mod2PI(sa + swp) ;
    }

    if (end_angle < start_angle)
    {	// first test case if we cross the +x axis with the arc
	CS_DEBUGAL(fprintf(fpDebugOut, "  End<Start\n")) ;
	if (phi <= end_angle || phi >= start_angle)
	{
	    return 1 ; // then angle is contained in the arc
	}
    }
    else
    {
	CS_DEBUGAL(fprintf(fpDebugOut,"  End >= Start\n")) ;
	if ((phi >= start_angle && phi <= end_angle) || 
            (phi == 0.0 && end_angle >= RADIAN360) ||
            (phi >= RADIAN360 && end_angle >= RADIAN360)) 
	{
	    return 1 ;
	}

    }


    return 0 ;
}


// returns true if phi is within sweep of the arc not
// including the endpoints
int CS_ARC::AngleInSweep(double phi)
{
    // For this test we use positive angles only
    double start_angle, end_angle ;

    phi = mod2PI(phi) ;

    if (swp > 0)
    {
        start_angle = mod2PI(sa) ;
        end_angle = mod2PI(sa + swp) ;
    }
    else
    {
        end_angle = mod2PI(sa) ;
        start_angle = mod2PI(sa + swp) ;
    }

    if (end_angle < start_angle)
    {	// first test case if we cross the +x axis with the arc
	if (tcomp_LT(phi, end_angle, RADCOMPARETOLERANCE) || 
            tcomp_GT(phi, start_angle, RADCOMPARETOLERANCE))
	    return 1 ; // then arc is contained in the arc
    }
    else
    {
	if (tcomp_GT(phi, start_angle, RADCOMPARETOLERANCE) && 
            tcomp_LT(phi, end_angle, RADCOMPARETOLERANCE))
	    return 1 ;
    }
    return 0 ;
}

double CS_ARC::ChordHeight()
{
    // fprintf(fpDebugOut,"Chord height for r=%lg  swp=%lg\n", rad, swp) ;
    return chordheight(rad, fabs(swp)) ;
}


// TO DO - when the plane of the arc is incorporated into the arc logic
//	    this routine must be updated to allow for coordinate transforms
//	Right now assume arcs are always in the XY plane.
double CS_ARC::XY_ArcLength(void)
{
    return rad * fabs(swp) ; // the sweep is always > 0
}

int CS_ARC::Arc3Points(CS_POINT &apnt, CS_POINT &mpnt, CS_POINT &bpnt)
{
    int retcode ;

    if (apnt == bpnt)
    {   // Then we are defining a full circle. The midpoint mpnt
        // is the opposite side of the circle
        // Or if the midpoint is the same as apnt or bpnt, then 
        // we have a very short arc segment
        if (((apnt + bpnt) / 2.0) == mpnt)
        {   // Short arc case
            // Since it is difficult to calculate a radius in this situation
            // keep the rad reasonably small, and base it on the coordinate
            // magintudes. 
            CS_VECTOR vab(apnt, bpnt) ; 
            if (tcomp_EQZ(vab.Mag()))
            {   // Then we have a microscopic arc which is effectively
                // a single point
                ctr = mpnt ; 
                rad = 0 ; 
                swp = 0 ; 
                sa = 0 ; 
                return 1 ; // indicate possible error condition
            }
            rad = ((fabs(mpnt.x) + fabs(mpnt.y)) + 10.0) / 2.0 ; 
            CS_VECTOR vabrp ; 
            vab = vab.Unit() ;
            vabrp = vab.RightPerp() ; 

            ctr = mpnt + vabrp * rad ; 
            sa = vabrp.AngleXY() ; 
            swp = 0 ; 
            return 2 ; // indicate possible error condition
        }

        // else full circle case
        ctr = (apnt + mpnt) / 2.0 ; 
        rad = CS_VECTOR(ctr, apnt).Mag() ; 
        sa = 0 ; 
        swp = RADIAN360 ; 
        return 0 ; 
    }

    CS_LINE lam(apnt, mpnt) ;
    CS_LINE lmb(mpnt, bpnt) ;
    CS_VECTOR vam(apnt, mpnt) ;
    CS_VECTOR vmb(mpnt, bpnt) ;
    CS_VECTOR vamp, vmbp ;
    vamp = vam.RightPerp() ;
    vmbp = vmb.RightPerp() ;
    CS_POINT midam = (apnt + mpnt) / 2.0 ;
    CS_POINT midmb = (mpnt + bpnt) / 2.0 ;
    CS_LINE rblam(midam, midam + (vamp * 10.0)) ;
    CS_LINE rblmb(midmb, midmb + (vmbp * 10.0)) ;

    // Now want the intersection of the two right bisector lines
    CS_POINT cpnt ;
    retcode = rblam.Intersect2D(rblmb, cpnt) ;
    if (retcode == 2)
    {	// Then the two right bisector's are collinear which means that we
	// can't deal with this case (TO DO - verify this is true)
        // This will only occur if the arc is a full circle, or
        // is so short that it is almost a single point, both cases
        // which we've dealt with above.
	return 2 ;
    }
    else if (retcode == 0)
    {	// Then the lines are parallel and don't intersect, which can't work
	return 1 ;
    }

    // The intersection point is the new center
    ctr = cpnt ;

    // Reset the arc based on the new center, direction will be the same

    if (ZCross(vam, vmb) > 0)
    {	// Then we have a CCW arc
        SetSPEP(apnt, bpnt, CCW) ;
    }
    else
    {	// It's a CW arc
        SetSPEP(apnt, bpnt, CW) ;
    }

    return 0 ; // success
}

// TO DO - fix the endpoint adjustment so that instead of the 
// midpoint, a more accurate adjusted mid point is used
// Set the start point of the arc to the point pnt
int CS_ARC::AdjustStartPoint(CS_POINT &pnt)
{
    // Get the current end point for the arc
    CS_POINT epnt = EndPoint() ;
    CS_POINT mpnt = MidPoint() ;
    return Arc3Points(pnt, mpnt, epnt) ;
}

// Set the end point of the arc to the point pnt using the 
// same start and mid points 
int CS_ARC::AdjustEndPoint(CS_POINT &pnt)
{
    // Get the current start point for the arc
    CS_POINT spnt = StartPoint() ;
    CS_POINT mpnt = MidPoint() ;
    return Arc3Points(spnt, mpnt, pnt) ;
}

///////////////////////////////////////////////////////////////////////////
// Arc bounding box. This works out the bounding box for an arc. It takes
// all the arc key points which are the quadrant points and the end points
// for the arc. It then does a min-max calculation based on this set of 
// points and returns the smallest enclosing box.
// 
// To return the smallest bounding pie shape defined by the arc, then this
// routine can easily be extended by simply including the center of the arc 
// as one of the test points. 
// See Notes RR-Vol1 pg 105
///////////////////////////////////////////////////////////////////////////
#ifndef min
#define min(a,b)        ((a < b) ? a : b ) 
#endif

#ifndef max
#define max(a,b)        ((a > b) ? a : b ) 
#endif


CS_RECT CS_ARC::BoundingRect()
{
    CS_RECT brect ;
    CS_POINT pr ; // quadrant points on the arc

    CS_POINT sp = StartPoint() ; 
    CS_POINT ep = EndPoint() ; 

    brect.l = min(sp.p[0], ep.p[0]) ;
    brect.t = max(sp.p[1], ep.p[1]) ;
    brect.r = max(sp.p[0], ep.p[0]) ;
    brect.b = min(sp.p[1], ep.p[1]) ;
    
    if (AngleOnSweep(0.0)) 
    {
        pr = UPoint(AngleU(0.0)) ;
        if (pr.p[0] < brect.l)
            brect.l = pr.p[0] ; 
        if (pr.p[0] > brect.r)
            brect.r = pr.p[0] ; 
        if (pr.p[1] < brect.b)
            brect.b = pr.p[1] ; 
        if (pr.p[1] > brect.t)
            brect.t = pr.p[1] ; 
    }

    if (AngleOnSweep(RADIAN90)) 
    {
        pr = UPoint(AngleU(RADIAN90)) ;
        if (pr.p[0] < brect.l)
            brect.l = pr.p[0] ; 
        if (pr.p[0] > brect.r)
            brect.r = pr.p[0] ; 
        if (pr.p[1] < brect.b)
            brect.b = pr.p[1] ; 
        if (pr.p[1] > brect.t)
            brect.t = pr.p[1] ; 
    }

    if (AngleOnSweep(RADIAN180)) 
    {
        pr = UPoint(AngleU(RADIAN180)) ;
        if (pr.p[0] < brect.l)
            brect.l = pr.p[0] ; 
        if (pr.p[0] > brect.r)
            brect.r = pr.p[0] ; 
        if (pr.p[1] < brect.b)
            brect.b = pr.p[1] ; 
        if (pr.p[1] > brect.t)
            brect.t = pr.p[1] ; 
    }

    if (AngleOnSweep(RADIAN270))
    {
        pr = UPoint(AngleU(RADIAN270)) ;
        if (pr.p[0] < brect.l)
            brect.l = pr.p[0] ; 
        if (pr.p[0] > brect.r)
            brect.r = pr.p[0] ; 
        if (pr.p[1] < brect.b)
            brect.b = pr.p[1] ; 
        if (pr.p[1] > brect.t)
            brect.t = pr.p[1] ; 
    }

    return brect ;
}



////////////////////////////////
// CS_ArcSeg specific methods //
////////////////////////////////
CS_SegPtr CS_ArcSeg::Copy()
{
    CS_ArcSeg *pas = new CS_ArcSeg ; 
    pas->info = info ; 
    pas->uo   = uo ; 
    pas->rad  = rad ; 
    pas->ctr  = ctr ; 
    pas->sa   = sa ; 
    pas->swp  = swp ; 
    if (pxfrm)
    {
        pas->pxfrm = new CS_MTX3 ; 
        *(pas->pxfrm) = *pxfrm ; 
    }
    pas->pUserData = pUserData ; 
    pas->pParent = pParent ; 
    pas->cnt = cnt ; 
    return pas ; 
}


CS_SegPtr CS_ArcSeg::Copy(double us, double ue)
{
    CS_ArcSeg *pas = new CS_ArcSeg ; 
    pas->info = info ; 
    pas->uo   = uo ; 
    pas->rad  = rad ; 
    pas->ctr  = ctr ; 
    pas->sa   = sa ; 
    pas->swp  = swp ; 
    pas->pUserData = pUserData ; 
    if (pxfrm)
    {
        pas->pxfrm = new CS_MTX3 ; 
        *(pas->pxfrm) = *pxfrm ; 
    }
    pas->pParent = pParent ; 
    pas->cnt = cnt ; 
    pas->Trim(us, ue) ; 
    return pas ; 
}



void CS_ArcSeg::Print(FILE *fp, int prec)
{
    if (!fp)
        fp = fpDebugOut ; 
    
    char formatstr[256] ; 
    sprintf(formatstr, "ASeg:%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf,%%s\n",
                    prec, prec, prec, prec, prec, prec) ; 
    fprintf(fp, formatstr,  ctr.p[0], ctr.p[1], ctr.p[2], rad, sa, swp,
	                swp < 0 ? "CW" : "CCW") ;
}

void CS_ArcSeg::PrintPoints2D(FILE *fp, int prec)
{
    if (!fp)
        fp = fpDebugOut ; 
    CS_POINT sp, ep ; 
    sp = StartPoint() ; 
    ep = EndPoint() ; 

    char formatstr[256] ; 
    sprintf(formatstr, "ASeg (%%.%dlf, %%.%dlf) -> (%%.%dlf, %%.%dlf) r=%%.%dlf sa=%%.%dlf swp=%%.%dlf dir=%%s\n",
                    prec, prec, prec, prec, prec, prec, prec) ; 

    fprintf(fp, formatstr, sp.x, sp.y, ep.x, ep.y, rad, sa, swp,
	swp < 0 ? "CW" : "CCW") ;
}




