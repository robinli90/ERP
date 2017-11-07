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
// crvgeom.cpp - Geometric processing routines related to CS_Curve's


#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)	
#else
#define CS_DEBUG(a)
#endif



// #define DIRECTIONBYPOINTINSIDE  // changes SetDirection() mode of operation

#define NUMBEROFRAYS	5

double CS_UMidShortest(double ua, double ub, int closed)
{
    if (!closed || fabs(ua - ub) <= 0.5)
        return (ua + ub) / 2.0 ; 

    // Otherwise we have to map one point closer to the other, do the 
    // midpoint calculation, and then normalize the result
    if (ua < ub)
        ua += 1.0 ; 
    else 
        ub += 1.0 ; 

    return fmod((ua + ub) / 2.0, 1.0) ; 
}


int CS_Curve::Inside(CS_POINT &p, double raylen, int skipSetBounds)
{
    return PointInside(p, raylen, skipSetBounds) ; 
}

int CS_Curve::PointInside(CS_POINT &p, double raylen, int skipSetBounds)
{
    CS_DEBUG(fprintf(fpDebugOut,"Entered PointInside") ; p.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n")) ;

    if (!Closed())
    {
	// fprintf(fpDebugOut, "Not closed\n") ;
	return 0 ; // can't be inside if the curve is not closed
    }

    if (!skipSetBounds)
        SetBoundingRect() ; // generate bounding box for this curve

    int insideflag = 0 ; 
    
    double oldtol = SetCmpTol(0.0) ;
    insideflag = bndrect.Inside(p) ; 
    SetCmpTol(oldtol) ; // set it back after this test

    if (!insideflag)
    {   // the point is not inside the bounding rectangle so no need
        // to do further testing, simply return false
        return 0 ;  
    }


    if (tcomp_EQZ(raylen))
    {
        double width, height ;
        // TO DO - see if we can eliminate the fabs() calls here (were originally put
        // in for safety reasons maybe?)
        width = fabs(bndrect.Width()) ;
        height = fabs(bndrect.Height()) ;
        if (width > height)
	    raylen = width * 1.5 ;
        else
	    raylen = height * 1.5 ;
    }


    // First establish vectors for the 5 ray directions
    int i ;
    int oddcnt, evencnt ;
    double dtheta, rayrotation ;

    dtheta = RADIAN360 / (double)(NUMBEROFRAYS + 1) ;
    rayrotation = dtheta ;

    oddcnt = 0 ;
    evencnt = 0 ;

    for (i=0; i < NUMBEROFRAYS; i++)
    {
	CS_LineSeg lray ; // random test rays, curve intersect test
	CS_VECTOR vray ;
	vray = CS_VECTOR(1, 0, 0) ; // initialize the ray vector
	vray.Rotate(rayrotation, 0, 0) ; // rotate ray in XY plane
	lray = CS_LineSeg(p, p + (vray * raylen)) ;

	////////////////////////////////////////////////////////////////////
	// Here we do the actual testing where we intersect the rays with
	// curve. We will end up with 5 intersection sets. Note that if any
	// of the rays have 0 intersections, then the point is definitely
	// outside of the closed Curve and we can stop searching
	////////////////////////////////////////////////////////////////////
	// Creat the intersection set with the ray
	CS_IRECList isset ; // intersection set

	CS_DEBUG(fprintf(fpDebugOut, "Intersecting:\n   "); lray.Print(fpDebugOut) ; ) ;

	Intersect2D(&lray, &isset) ; // intersect the curves

	CS_DEBUG(fprintf(fpDebugOut,"Intersection set is:\n ") ; isset.PrintSet(fpDebugOut) ;) ;

        CS_SortIntersectSetByUValue(isset) ; 
        CS_DeleteCommonIntersectionPoints(isset) ; 

	if (isset.size() == 0)
	    return 0 ; // the point is not inside the curve loop

	if ((isset.size() % 2) == 1)
	{   // Then the number of intersections is odd
	    oddcnt += 1 ;
	}
	else
	{   // Number of intersections is even
	    evencnt += 1 ;
	}

	rayrotation += dtheta ; // increment for next ray creation
    }

    CS_DEBUG(
	fprintf(fpDebugOut, "\n\n\nInside test Odd=%d, even=%d\n\n", oddcnt, evencnt) ;
    ) ;

    if (evencnt < oddcnt)
    {   // then we got mainly odd counts and thus it is inside
	return 1 ; 
    }
    
    // Even counts occured more often so the point is outside
    return 0 ; 
}



int CS_Curve::MergeCollinearLines() 
{
    CS_SegPtr pseg = pStart ; 
    int delcount = 0 ; 
    while (pseg)
    {
        if (pseg->next)
        {
            if(pseg->SegmentType() == CS_Segment::LINE_TYPE &&
               pseg->next->SegmentType() == CS_Segment::LINE_TYPE)
            {
                CS_LineSeg *pl1 = (CS_LineSeg *)pseg ; 
                CS_LineSeg *pl2 = (CS_LineSeg *)pseg->next ; 
                if (pl1->Collinear(*pl2))
                {   // Then they are the same line
                    pl1->ep = pl2->ep ; 
                    Delete(pl2) ; 
                    delcount++ ; 
                }
            }
        }
        else if (Closed() && pStart->SegmentType() == CS_Segment::LINE_TYPE 
                          && pEnd->SegmentType() == CS_Segment::LINE_TYPE)
        {
                CS_LineSeg *pl1 = (CS_LineSeg *)pStart ; 
                CS_LineSeg *pl2 = (CS_LineSeg *)pEnd ; 
                if (pl1->Collinear(*pl2))
                {   // Then they are the same line
                    pl1->sp = pl2->sp ; 
                    Delete(pl2) ;
                    delcount++ ; 
                    break ; // we're done (and deleted the pseg node)
                }
        }
        pseg = pseg->next ; 
    }
    return 0 ; 
}


// Deletes segments shorter than minLength. If a series of segments 
// less than minLength are connected together, then they are joined 
// together in bunches until each newly generated segment is longer
// than minLength
int CS_Curve::DeleteShortSegments(double minLength) 
{
    int deleteCount = 0 ; 
    int bWasClosed = Closed() ; 
    double seglength ; 
    CS_SegPtr psx ; 

    CS_SegPtr psn = pStart ; 
    while (psn)
    {   
        seglength = psn->ArcLength() ; 
        if (seglength < minLength)
        {   // Delete the segment
            psx = psn->next ;
            if (!psx && bWasClosed)
            {   // Then there is something to do
                psx = Next(psn) ;
            }
            if (psx)
                psx->AdjustStartPoint(psn->StartPoint()) ; 
            psx = psn ; 
            psn = psn->next ; 
            Delete(psx) ; 
            deleteCount++ ; 
            continue ; 
        }
        psn = psn->next ;
    }

    return deleteCount ; 
}


// Convert arcs whose chord height is less than the chtol parameter to
// straight line segments
int CS_Curve::ConvertFlatArcs(double chtol, int copyuser)
{
    int crvtcount ;
    double cheight ;
    CS_SegPtr pn = pStart ;

    int bIsClosed = Closed() ; 

    crvtcount = 0 ;
    while (pn)
    {
        if (pn->SegmentType() == CS_Segment::ARC_TYPE)
	{   // Then test it out
	    CS_ArcSeg *pas = (CS_ArcSeg *)pn ;
	    cheight = pas->ChordHeight() ;
	    if (cheight <= chtol)
	    {	// Then convert to a line segment
                CS_POINT sp ; 
                
                if (pas->prev)
                    sp = pas->prev->EndPoint() ; 
                else
                {
                    if (bIsClosed)
		        sp = pEnd->EndPoint() ; 
                    else
                        sp = pas->StartPoint() ; 
                }

                CS_POINT ep ; 

                if (pas->next)
                    ep = pas->next->StartPoint() ; 
                else
                {
                    if (bIsClosed)
		        ep = pStart->StartPoint() ; 
                    else
                        ep = pas->EndPoint() ; 
                }

		CS_LineSeg *pls = new CS_LineSeg(sp, ep) ;
		CS_DEBUG(fprintf(fpDebugOut,"Replaced arc cheight=%lg\n", cheight)) ;
		Replace(pn, pls) ; // replace pas
                if (copyuser)
                    pls->pUserData = pn->pUserData ; 
		crvtcount++ ;
                pn = pls ; 
	    }
	    else
	    {
		CS_DEBUG(
		    fprintf(fpDebugOut, "In Tol: The chord height is %lg\n", cheight)) ;
	    }
	}
	pn = pn->next ;
    }
    return crvtcount ;
}


/////////////////////////////////////////////////////////////////////
// Walk through the curve and match up the end points exactly, using
// the mean distance between current end points for correction.
/////////////////////////////////////////////////////////////////////
int CS_Curve::ConnectEndPoints(double *ptol)
{
    CS_SegPtr pn = pStart ;
    int retcode = 0 ;

    while (pn)
    {
	if (pn->next)
	{   // Then we can correct the two segments
	    retcode |= CS_MatchEndPoints(pn, pn->next) ;
	}
	pn = pn->next ;
    }
    if (Closed(ptol) && nodecnt > 1)
    {	// Then we can correct the last segment with the first also
	retcode |= CS_MatchEndPoints(pEnd, pStart) ;
    }
    return retcode ; 
}

// Sets the internal bounding rectangle for the curve
void CS_Curve::SetBoundingRect()
{
    bndrect = CS_RECT(0,0,0,0) ;
    CS_SegPtr pnode = pStart ;
    if (pnode)
	bndrect = pnode->BoundingRect() ;
    else
	return ; // nothing to do

    pnode = pnode->next ;
    while (pnode)
    {
	bndrect.Union(pnode->BoundingRect()) ;
	pnode = pnode->next ;
    }
}


// Set the direction of a closed curve in the CCW/CW direction.


int CS_Curve::SetDirection(int orientation, double *parea)
{
    if (!Closed())
    {   // Then there is no inside or outside so simply return
        return 1 ; 
    }

    // #ifdef DIRECTIONBYPOINTINSIDE
    // // The way the routine works is it takes the tangent vector from the start 
    // // point of the curve. Then if generates a point just to the left of the
    // // curve start point and checks to see if this point is inside the curve. 
    // // If the point is inside then the curve is CCW, otherise the curve us CW
    // // and the curve is reversed so that it ends pu being CCW
    // 
    // // Set the direction by testing if a left perp or right perp point
    // // is inside the curve
    // CS_VECTOR uvstart = UTangent(0.05) ; 
    // CS_VECTOR uvleft = uvstart.LeftPerp() ; 
    // 
    // CS_POINT testpnt = UPoint(0.05) ; 
    // testpnt = testpnt + (COMPARETOLERANCE * 1000.0 * uvleft) ; 
    // 
    // int pinside = PointInside(testpnt) ; 
    // if ((!pinside && (orientation == CCW)) || 
    //      (pinside && (orientation == CW)))
    // {   // Then we want to reverse the curve
    //     Reverse() ; 
    // }
    // // else the curve goes in the proper direction
    // #else
    
    // Set the direction by calculating the area inside the curve. CCW
    // means the area is positive and CW gives a -ve area
    // Note that this method is more robust
    double crvarea = Area() ; 
    if (parea) *parea = crvarea ; 
    if ((crvarea < 0 && orientation == CCW) ||
        (crvarea > 0 && orientation == CW))
        Reverse() ; // then we have to reverse the entire curve

    // #endif

    return 0 ; 
}


// Split the curve at the given u value
// This basically splits the segment where the u value occurs. If the 
// u value is at a start/end point of one of the segments nothing is done
// and the segment who's start point is at the upoint is returned.
// For a closed curve if a split is done at u=1.0 then the segment
// pStart is returned. Otherwise the newly created segment is
// returned. If pspnt is not null then the point where the split
// is done is returned (this will be the start point of the returned
// segment). pspnt must point to a valid CS_POINT with memory already
// allocated for it.
// NOTE: the CS_Segment uo parameters must be valid upon entry 
//       (call SetUParameters to ensure this, unless of course you're
//        doing something where you want to fool the routines by 
//        passing invalid u parameters)
CS_SegPtr CS_Curve::Split(double usplit, CS_POINT *pspnt)
{
    // Have to find the segment with this u value along the curve
    CS_SegPtr pn ;
    CS_POINT upnt ; 

    // we want the segment where point occurs
    upnt = UPoint(usplit, &pn, CS_SEARCHBYUVALUE) ; 

    CS_POINT ssp, sep ; 
    ssp = pn->StartPoint() ;
    sep = pn->EndPoint() ;

    if (ssp == upnt)
    {   // Then we are trying to split an existing end node
        if (pspnt)
            *pspnt = upnt ;
        return pn ;
    }
    else if (sep == upnt)
    {   // The end point matches the u split point
        // Thus return the start segment if the curve is closed, but if
        // the curve is open the return the end segment
        
        pn = pn->next ; 
        if (!pn)
        {
            if (Closed())
                pn = pStart ; 
            else
                pn = pEnd ; 
        }

        if (pspnt)
            *pspnt = upnt ; 
        return pn ; 
    }

    // else split this segment
    // Create two new segments from the existing segment
    // Re-adjust the uo's for the split segment and the new segment

    if (pn->SegmentType() == CS_Segment::LINE_TYPE)
    {   // Then create new line segment and update the existing segment
        CS_LineSeg *plsa = (CS_LineSeg *)pn ; // the existing segment
        CS_LineSeg *plsb = new CS_LineSeg ; 
        // We are splitting up this line segment at the upnt which
        // we already have so all we have to do is stuff in the extra
        // segment after updating the all the endpoints
        plsb->sp = upnt ; 
        plsb->ep = plsa->ep ; 
        plsa->ep = upnt ; 
        if (pspnt) 
            *pspnt = upnt ; 
        CS_SegPtr pnewseg ; 
        arclength -= plsb->ArcLength() ; // subtract arclength because 
        // InsertAfter will add it back 
        pnewseg = InsertAfter(pn, plsb, CS_NOENDPOINTADJUSTMENT) ; 

        // The new segment's uo is simply the u value passed into the
        // function originally
        pnewseg->uo = usplit ; 

        return pnewseg ; 
    }
    else if(pn->SegmentType() == CS_Segment::ARC_TYPE)
    {   // Split the arc segment
        CS_ArcSeg *pasa = (CS_ArcSeg *)pn ; 
        CS_ArcSeg *pasb = new CS_ArcSeg ; 
        // simply update new arc sweep and start angle params
        // Need to know the split point angle though

        // Create vector from center of circle to the split point
        CS_VECTOR vcs(pasa->ctr, upnt) ; 
        double eang ; // current end angle
        pasb->rad = pasa->rad ; 
        pasb->ctr = pasa->ctr ; 
        pasb->sa = vcs.AngleXY() ; 
        
        eang = pasa->sa + pasa->swp ; // save current end angle
        
        if (pasa->ArcDir() == CCW)
        {
            pasa->swp = arc_sweep(pasa->sa, pasb->sa, CCW) ; 
            pasb->swp = arc_sweep(pasb->sa, eang, CCW) ; 
        }
        else
        {
            pasa->swp = -arc_sweep(pasa->sa, pasb->sa, CW) ; 
            pasb->swp = -arc_sweep(pasb->sa, eang, CW) ; 
        }

        if (pspnt) 
            *pspnt = upnt ; 
        
        CS_SegPtr pnewseg ; 
        arclength -= pasb->ArcLength() ; // subtract because
        // InsertAfter will add it back
        pnewseg = InsertAfter(pn, pasb, CS_NOENDPOINTADJUSTMENT) ;             
        
        pnewseg->uo = usplit ;

        return pnewseg ; 
    }

    return 0 ; // some error occured
}


//! note if you try to split the end of an open line segment then NULL is returned
CS_SegPtr CS_Curve::Split(CS_CrvPnt &cp, CS_POINT *pspnt)
{
    // Have to find the segment with this u value along the curve
    CS_SegPtr pn ;
    CS_POINT upnt = cp.Point() ; 

    if (tcomp_EQZ(cp.u))
    {   // Then we are trying to split an existing end node
        if (pspnt)
            *pspnt = upnt ;
        return cp.s ;
    }
    else if (tcomp_EQ(cp.u, 1.0))
    {   // The end point matches the u split point
        // Thus return the start segment if the curve is closed, but if
        // the curve is open the return the end segment
        
        pn = cp.s->next ; 
        if (!pn)
        {
            if (Closed())
                pn = pStart ; 
        }

        if (pspnt)
            *pspnt = upnt ; 
        return pn ; 
    }

    // else split this segment
    // Create two new segments from the existing segment
    // Re-adjust the uo's for the split segment and the new segment

    if (cp.s->IsLINE())
    {   // Then create new line segment and update the existing segment
        CS_LineSeg *plsa = (CS_LineSeg *)cp.s ; // the existing segment
        CS_LineSeg *plsb = new CS_LineSeg ; 
        // We are splitting up this line segment at the upnt which
        // we already have so all we have to do is stuff in the extra
        // segment after updating the all the endpoints
        plsb->sp = upnt ; 
        plsb->ep = plsa->ep ; 
        plsa->ep = upnt ; 
        if (pspnt) 
            *pspnt = upnt ; 
        CS_SegPtr pnewseg ; 
        arclength -= plsb->ArcLength() ; // subtract arclength because 
        // InsertAfter will add it back 
        pnewseg = InsertAfter(cp.s, plsb, CS_NOENDPOINTADJUSTMENT) ; 

        // The new segment's uo is simply the u value passed into the
        // function originally
        pnewseg->uo = cp.UCrv() ; 

        return pnewseg ; 
    }
    else if(cp.s->IsARC())
    {   // Split the arc segment
        CS_ArcSeg *pasa = (CS_ArcSeg *)cp.s ; 
        CS_ArcSeg *pasb = new CS_ArcSeg ; 
        // simply update new arc sweep and start angle params
        // Need to know the split point angle though

        // Create vector from center of circle to the split point
        CS_VECTOR vcs(pasa->ctr, upnt) ; 
        double eang ; // current end angle
        pasb->rad = pasa->rad ; 
        pasb->ctr = pasa->ctr ; 
        pasb->sa = vcs.AngleXY() ; 
        
        eang = pasa->sa + pasa->swp ; // save current end angle
        
        if (pasa->ArcDir() == CCW)
        {
            pasa->swp = arc_sweep(pasa->sa, pasb->sa, CCW) ; 
            pasb->swp = arc_sweep(pasb->sa, eang, CCW) ; 
        }
        else
        {
            pasa->swp = -arc_sweep(pasa->sa, pasb->sa, CW) ; 
            pasb->swp = -arc_sweep(pasb->sa, eang, CW) ; 
        }

        if (pspnt) 
            *pspnt = upnt ; 
        
        CS_SegPtr pnewseg ; 
        arclength -= pasb->ArcLength() ; // subtract because
        // InsertAfter will add it back
        pnewseg = InsertAfter(cp.s, pasb, CS_NOENDPOINTADJUSTMENT) ;             
        
        pnewseg->uo = cp.UCrv() ;

        return pnewseg ; 
    }

    return 0 ; // some error occured
}




//! Break out (delete) a section of the current curve. 
/*!
    \param u1 start u value along curve to break out from
    \param u2 ending u value along curve to break out to
    \crv2 set the second curve in cases where two curves result
    \return returns true if crv2 is set, otherwise returns false
    Breaks out (deletes) the section of the curve defined from 
    u1 to u2. If u1 > u2 and the curve is closed then the section 
    of the curve spanning the start point is removed, this will 
    even work on open curves where the effect will be to trim
    off both ends of the curve. 
 */
int CS_Curve::Break(double u1, double u2, CS_Curve &crv2)
{
    // If u1 <= 0 then simply trim the start of the line off
    CalcArcLength() ; 
    SetUParameters() ; 

    if (tcomp_LEQ(u1, 0.0))
    {
        TrimStart(u2) ; 
        return 0 ; 
    }

    // If u2 >= 1.0 then trim off the end of the line
    if (tcomp_GEQ(u2, 1.0))
    {
        TrimEnd(u1) ; 
        return 0 ; 
    }

    if (u1 > u2)
    {   // break out section from end to start 
        // triming out sections [u1,1],[0,u2]
        // See Notes RR-VOL1 pgs 136-137
        // Assuming that this will only occur when curve is closed
        TrimEnd(u1) ; 
        TrimStart(u2 / u1) ; 

        return 0 ; 
    }

    // If we get to here then we are cutting out a section in the middle of 
    // the curve

    int wasclosed = Closed() ; 

    // First we want to split the original curve at the two u values
    CS_POINT pnt1 ; 
    CS_POINT pnt2 ; 
    
    CS_SegPtr psn1 = Split(u1, &pnt1) ;
    CS_SegPtr psn2 = Split(u2, &pnt2) ; 

    // psn1 should now point to the segment which is to be removed from the 
    // the original curve. psn2 points to the start of the new curve (if 
    // original was closed) or to the start of the second curve (if orginal
    // was open). Thus we have two cases to deal with depending on whether
    // the original curve was opened or closed

    // Note: by inserting breaks into the original curve we will not
    // change the open/closed status of the original curve (unless of 
    // course the curve is self intersecting, which is why we have to 
    // save this value before starting
    if (wasclosed)
    {   // Then we have to re-arrange the segments so that psn2 is the new 
        // start segment for the curve.

        // hook the start and end segments together
        pEnd->next = pStart ; 
        pStart->prev = pEnd ; 

        pEnd = psn1->prev ; 
        pStart = psn2 ; 

        pEnd->next = 0 ; 
        pStart->prev = 0 ; 

        // adjust arclength for the new curve
        arclength -= psn1->ArcLength() ;
        nodecnt -= 1 ; 

        // Finally delete psn1
        delete psn1 ;

        // We didn't update crv2 so return false
        return 0 ;
    }

    // Else the original curve was opened so fill in the second curve
    crv2.Destroy() ; // make sure the second curve is empty

    // can simply move the block of segments from one CS_Curve to the 
    // other by adjusting pointers and such
    crv2.pStart = psn2 ; 
    crv2.pEnd = pEnd ;

    pEnd = psn1->prev ; 

    pEnd->next = 0 ; 
    pStart->prev = 0 ; 

    delete psn1 ; // delete the segment representing the actual break section

    // Now we have to fix up the nodecnt and arclength variables
    Finalize() ; 
    crv2.Finalize() ; 

    return 1 ; // return true since we modified crv2
}


// See Geom Algo's RR-Vol5 pg 79
int CS_Curve::Slice(CS_CrvPnt &p1, CS_CrvPnt &p2, CS_CurvePtr &pslice) 
{
    int ret = 0 ; 
    p1.AdjustToStart() ; 
    p2.AdjustToStart() ; 

    double u1 = p1.UCrv() ; 
    double u2 = p2.UCrv() ; 

    pslice = new CS_Curve ; 

    if (u1 > u2) 
    {   // Swap them
        CS_CrvPnt cptmp ; 
        cptmp.s = p1.s ; 
        cptmp.u = p1.u ; 
        p1.s = p2.s ; 
        p1.u = p2.u ; 
        p2.s = cptmp.s ; 
        p2.u = cptmp.u ; 
    }

    CS_POINT P1 = p1.Point() ; 
    CS_POINT P2 = p2.Point() ; 

    if (p1.s == p1.s->pParent->pStart && tcomp_EQZ(p1.u))
    {   // Case 2 where the start end point of the curve is one of the slice points
        pslice = new CS_Curve ; // create new curve
        CS_SegPtr splitseg = p2.s ; 
        if (!tcomp_EQZ(p2.u))
        {   // Then have to split the segment up
            splitseg = SplitSegment(p2) ; 
        }
        
        Divide(splitseg, *pslice) ; 

        CS_LineSeg *pls = new CS_LineSeg(P2, StartPoint()) ; 
        Append(pls, CS_NOADJUST) ; 
        Complete(NODIR) ; 

        pls = new CS_LineSeg(pslice->EndPoint(), P2) ; 
        pslice->Insert(pslice->pStart, pls, CS_NOADJUST) ; 
        pslice->Complete(NODIR) ; 
    }
    else
    {   // Case 1 slice, 
        pslice = new CS_Curve ; // create new curve

        CS_SegPtr splitseg = p1.s ; 
        if (!tcomp_EQZ(p1.u))
        {   // Then have to split the segment up
            splitseg = SplitSegment(p1) ; 
        }
        
        Divide(splitseg, *pslice) ; 

        splitseg = p2.s ; 
        if (!tcomp_EQZ(p2.u))
        {   // Then have to split the segment up
            splitseg = SplitSegment(p2) ;
        }

        CS_Curve *ptmpcrv = new CS_Curve ;
        pslice->Divide(splitseg, *ptmpcrv) ;

        CS_LineSeg *pls = new CS_LineSeg(P2, P1) ;
        pslice->Insert(pslice->pStart, pls, CS_NOADJUST) ;
        pslice->Complete(NODIR) ; 

        pls = new CS_LineSeg(P1, P2) ;
        Append(pls, CS_NOADJUST) ; 
        AddCurve(ptmpcrv) ; 
        Complete(NODIR) ; 
    }

    return ret ; 
}


CS_SegPtr CS_Curve::SplitSegment(CS_CrvPnt &cp) 
{
    if (tcomp_EQZ(cp.u) || tcomp_GEQ(cp.u, 1.0))
        return 0 ; 

    CS_SegPtr pseg = cp.s->Copy() ; 
    pseg->TrimStart(cp.u) ; 
    cp.s->TrimEnd(cp.u) ; 

    cp.s->next = pseg ; 
    pseg->prev = cp.s ; 

    if (cp.s == pEnd)
        pEnd = pseg ; // update the new end segment

    pseg->uo = cp.s->uo + (cp.s->ArcLength() / arclength) ; 
    pseg->pParent = cp.s->pParent ; 
    nodecnt++ ; 
    return pseg ; 
}


/*!
 Divide the curve up into two where everything from pdivseg
 on is put into crv2. crv2 is cleared out on entry
 */
void CS_Curve::Divide(CS_SegPtr pdivseg, CS_Curve &crv2) 
{
    if (!pdivseg)
        return ; // nothing to do

    crv2.Reset() ; 

    if (pdivseg == pStart) 
    {   // Then crv2 is set equal to crv and this curve is reset
        crv2.pStart = pStart ; 
        crv2.pEnd = pEnd ; 
        crv2.arclength = arclength ; 
        crv2.nodecnt = nodecnt ; 
        crv2.bndrect = bndrect ; 
        crv2.XYarclength = XYarclength ; 
        crv2.statflags = statflags ; 

        pStart = 0 ; 
        pEnd = 0 ;
        arclength = 0 ; 
        nodecnt = 0 ; 
        bndrect = CS_RECT(0,0,0,0) ; 
        XYarclength = 0 ; 
        statflags = 0 ; 
       
        return ; 
    }

    // Otherwise we are going to end up with 2 separate curves
    crv2.pStart = pdivseg ; 
    crv2.pEnd = pEnd ; 
    pEnd = pdivseg->prev ;

    crv2.pStart->prev = 0 ; 
    pEnd->next = 0 ; 

    CalcArcLength() ; 
    crv2.CalcArcLength() ; 
}

// Add pcrv to *this
CS_Curve &CS_Curve::AddCurve(CS_Curve *pcrv, int mode)
{
    CS_SegPtr psn ;
    CS_SegPtr psnnext ;
    psn = pcrv->pStart ; 
    if (psn)
    {
        if (mode == CS_ADJUST_STARTPOINT)
        {   // Then make sure the start point of pcrv matches up 
            // to the end point of the base (this) curve
            if (pEnd)
            {
                psn->AdjustStartPoint(pEnd->EndPoint()) ; 
            }
        }
        else if (mode == CS_ADJUST_ENDPOINT)
        {   // Then adjust this curves endpoint to the startpoint
            // of pcrv
            if (pEnd)
            {
                arclength -= pEnd->ArcLength() ; 
                pEnd->AdjustEndPoint(psn->StartPoint()); 
                arclength += pEnd->ArcLength() ; 
            }
        }
        else if (mode == CS_ADJUST_APPENDCURVE_ENDPOINTS)
        {
            if (EndPoint() == pcrv->EndPoint())
                pcrv->Reverse() ; 
        }
        else if (mode == CS_ADJUST_BASECURVE_ENDPOINTS)
        {
            if (StartPoint() == pcrv->StartPoint())
                Reverse() ; 
        }


        while (psn)
        {   
            // Save the next pointer since we are going to change it to 
            // the base curve list
            psnnext = psn->next ; 

            // This is the code copied from the Append operation except
            // we don't have to allocate anything in this case
            nodecnt += 1 ;
            arclength += psn->ArcLength() ;

            if (pStart == NULL)
            {	// then create the Head node (1st entry)
	        pStart = psn ;
	        pEnd = psn ;
                psn->prev = 0 ; 
                psn->next = 0 ; 
	        nodecnt = 1 ;
            }
            else
            {
	        pEnd->next = psn ;
	        psn->prev = pEnd ;
	        pEnd = psn ;
	        psn->next = 0 ;
            }

            // Set pointer for the next node
            psn = psnnext ; 
        }
    }

    // Set these pointers to null so the pcrv destructor doesn't 
    // do anything to the segments that were transferred over.
    pcrv->pStart = 0 ; 
    pcrv->pEnd = 0 ; 
    delete pcrv ; 

    return *this ; 
}

CS_Curve &CS_Curve::InsertCurve(CS_Curve *pcrv, int mode)
{
    CS_SegPtr psn ;
    CS_SegPtr psnprev ;
    psn = pcrv->pEnd ; 
    if (psn)
    {
        if (mode == CS_ADJUST_STARTPOINT)
        {   // Then make sure the start point of pcrv matches up 
            // to the end point of the base (this) curve
            if (pStart)
            {
                arclength -= pStart->ArcLength() ; 
                pStart->AdjustStartPoint(pcrv->EndPoint()) ; 
                arclength += pStart->ArcLength() ; 
            }
        }
        else if (mode == CS_ADJUST_ENDPOINT)
        {   // Then adjust this curves endpoint to the startpoint
            // of pcrv
            if (psn)
            {
                psn->AdjustEndPoint(pStart->StartPoint()); 
            }
        }
        else if (mode == CS_ADJUST_APPENDCURVE_ENDPOINTS)
        {
            if (StartPoint() == pcrv->StartPoint())
                pcrv->Reverse() ; 
        }
        else if (mode == CS_ADJUST_BASECURVE_ENDPOINTS)
        {
            if (EndPoint() == pcrv->EndPoint())
                Reverse() ; 
        }


        while (psn)
        {   
            // Save the next pointer since we are going to change it to 
            // the base curve list
            psnprev = psn->prev ; 

            // This is the code copied from the Append operation except
            // we don't have to allocate anything in this case
            nodecnt += 1 ;
            arclength += psn->ArcLength() ;

            if (pStart == NULL)
            {	// then create the Head node (1st entry)
	        pStart = psn ;
	        pEnd = psn ;
                psn->prev = 0 ; 
                psn->next = 0 ; 
	        nodecnt = 1 ;
            }
            else
            {
	        pStart->prev = psn ;
	        psn->next = pStart ;
	        pStart = psn ;
	        psn->prev = 0 ;
            }

            // Set pointer for the next node
            psn = psnprev ; 
        }
    }

    // Set these pointers to null so the pcrv destructor doesn't 
    // do anything to the segments that were transferred over.
    pcrv->pStart = 0 ; 
    pcrv->pEnd = 0 ; 
    delete pcrv ; 

    return *this ; 
}


// Curve support functions
int CS_MatchEndPoints(CS_SegPtr pa, CS_SegPtr pb)
{
    CS_POINT epa, spb ;
    epa = pa->EndPoint() ;
    spb = pb->StartPoint() ;
    if (epa.p[0] == spb.p[0] &&
	epa.p[1] == spb.p[1] &&
	epa.p[2] == spb.p[2])
    {	// Then they already match exactly so there is nothing to do
	return 0 ;
    }

    // Else we take the midpoint of the two as the new end point
    CS_POINT pmid ;
    pmid = (epa + spb) / 2.0 ;

    pa->AdjustEndPoint(pmid) ;
    pb->AdjustStartPoint(pmid) ;

    return 1 ; // ends modified
}

