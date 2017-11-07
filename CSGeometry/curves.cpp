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
// curves.cpp - Class for curve, lines, arcs, and splines
//		Spline capabilities will be added to later but should be kept
//		in mind while developing the class

/*
  General Notes:

  Offsetting:
    The offset functions are called with a delta parameter specification.
    A positive delta means offset the curve to the right a distance of
    delta, where a right perpendicular vector of magnitude delta would
    translate the original startpoint to the new startpoint. A negative
    delta offsets curves to the left. When CS_Curve's are offset the logic
    within the CS_Curve handles offsetting the internal arcs and lines in
    the proper direction. If an arc segment becomes inverted when offset 
    (offset into the center by more than the radius) then the status bit 
    CS_ARCOFSINV is set for the arc, and the arc's direction gets flipped.

    TO DO -
    Bad boundary curves (open curves,or curves that fold back on
    themselves, end points do not connect exactly, etc...) should be
    filtered out right at the start. We need to add these features
    to the CreateChainedBoundaries() command. This should probably
    be a new command added to the geometry library, where a group
    of curve segments is chained together in sets based on various
    parameters. These parameters would be i) segment end points must
    be tangent or if two branches possible give priority to the tangent
    (or non-tangent) segment. Filter out overlapping segments, and so on.

    TO DO -
    The logic for inserting segments into the front of a curve list where
    the orientation of the segment has to be checked, needs fixing/redoing.

    TO DO -
    Trim commands added to all the curves and segments based on U parms
    and points passed in as input for the trim.


*/

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
#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_chain.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif

char *strstartis(char *str, char *buffer)
{
    int n ;
    n = (int)strlen(str) ;
    if (strncmp(str,buffer,n) == 0)
    return (buffer + n) ;
    return NULL ;
}


//////////////////////////////////////////////////////////////////
// CrvPnt structure member functions
//////////////////////////////////////////////////////////////////
double CS_CrvPnt::UCrv()
{
    if (!s)
        return -1 ; 

    if (s->pParent)
        return s->pParent->SegU2CrvU(s, u) ; 
    return u ; 
}


CS_POINT CS_CrvPnt::Point()
{ 
    return s->UPoint(u) ; 
} ; 


    //! Adjusts a u=1 to the start of the next segment
CS_CrvPnt &CS_CrvPnt::AdjustToStart()
{
    if (!s->pParent)
        return *this ; 

    if (tcomp_GEQ(u, 1.0))
    {
        if (s->next)
        {
            s = s->next ; 
            u = 0.0 ; 
        }
        else if (s->pParent->Closed())
        {
            s = s->pParent->Next(s) ; 
            u = 0.0 ; 
        }
    }

    return *this ; 
}


    //! Returns true if the curve points are the same point on the same curve. 
int CS_CrvPntsEQ(CS_Curve *pcrv, CS_CrvPnt &a, CS_CrvPnt &b)
{
    if (a.s == b.s)
    {
        if (tcomp_EQ(a.u, b.u))
            return 1 ; 
    }
    else if (tcomp_EQ(a.u, 1.0) && tcomp_EQZ(b.u))
    {
        if (pcrv->statflags & CS_CLOSEDCURVE)
        {
            if (pcrv->Next(a.s) == b.s)
                return 1 ; 
        }
        else
        {
            if (a.s->next == b.s)
                return 1 ; 
        }
    }
    else if (tcomp_EQ(a.u, 0.0) && tcomp_EQ(b.u, 1.0))
    {
        if (pcrv->statflags & CS_CLOSEDCURVE)
        {
            if (pcrv->Next(b.s) == a.s)
                return 1 ; 
        }
        else
        {
            if (b.s->next == a.s)
                return 1 ; 
        }
    }
    return 0 ; 
}

int CS_CrvPntsNEQ(CS_Curve *pcrv, CS_CrvPnt &a, CS_CrvPnt &b)
{
    if (CS_CrvPntsEQ(pcrv, a, b))
        return 0 ; 
    return 1 ; 
}



/*
//////////////////////////////////////////////////////////////////
// Nodes in the CS_Curve curve list class
//////////////////////////////////////////////////////////////////
CS_SegNode::CS_SegNode()
{
    prev = NULL ;
    next = NULL ;
    uo = 0.0 ;
}

CS_SegNode::~CS_SegNode()
{
    if (pseg)
	delete pseg ;
}
*/

//////////////////////////////////////////////////////////////////
// Curve class - list of arcs, lines, splines
//////////////////////////////////////////////////////////////////

CS_Curve::CS_Curve()
{
    nodecnt = 0 ;
    statflags = 0 ;
    arclength = 0.0 ;
    pStart = pEnd = NULL ;
    pUserData = 0 ; 
    pcnmap = 0 ; 
    CS_DEBUG(fprintf(fpDebugOut, "Called CS_Curve() constructor\n") ;)
}

CS_Curve::~CS_Curve() 
{
    Destroy() ; // free all memory for the curve
}

// Copy constructor for the curve
CS_Curve::CS_Curve(const CS_Curve &crv)
{
    CS_DEBUG(fprintf(fpDebugOut, "Called CS_Curve() copy constructor\n") ;)

    nodecnt = 0 ;
    statflags = 0 ;
    arclength = 0.0 ;
    pStart = pEnd = NULL ;

    pUserData = crv.pUserData ; 
    pcnmap = crv.pcnmap ; 
    bndrect = crv.bndrect ; 

    CS_SegPtr pn = crv.pStart ;

    // TO DO - rewrite using the new CopySegment features
    while (pn)
    {
        if (pn->SegmentType() == CS_Segment::ARC_TYPE)
	{   // Then create an arc
	    CS_ArcSeg *pnewseg = new CS_ArcSeg((CS_ArcSeg *)pn) ;
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg) ;
	}
        else if (pn->SegmentType() == CS_Segment::LINE_TYPE)
	{   // Then create a line
	    CS_LineSeg *pnewseg = new CS_LineSeg((CS_LineSeg *)pn) ;
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg) ;
	}
	else
	{
	    CS_DEBUG(fprintf(fpDebugOut, "Types error in CS_Curve::CS_Curve(CS_Curve&)\n") ;)
	}
	pn = pn->next ;
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;

    CS_DEBUG(fprintf(fpDebugOut, "WARNING: Called CS_Curve(CS_Curve&) copy constructor\n") ;)
}


int CS_Curve::CopyCurve(const CS_Curve &crv)
{
    Destroy() ; 
    pUserData = crv.pUserData ; 
    pcnmap = crv.pcnmap ; 
    bndrect = crv.bndrect ; 
    
    CS_SegPtr pn = crv.pStart ;

    CS_DEBUG(fprintf(fpDebugOut, "Called CS_Curve::CopyCurve(CS_Curve &)\n") ; )

    // TO DO - rewrite using the new CopySegment features
    while (pn)
    {
        if (pn->SegmentType() == CS_Segment::ARC_TYPE)
	{   // Then create an arc
	    CS_ArcSeg *pnewseg = new CS_ArcSeg((CS_ArcSeg *)pn) ;
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg, CS_NOENDPOINTADJUSTMENT) ;
	}
        else if (pn->SegmentType() == CS_Segment::LINE_TYPE)
	{   // Then create a line
	    CS_LineSeg *pnewseg = new CS_LineSeg((CS_LineSeg *)pn) ;
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg, CS_NOENDPOINTADJUSTMENT) ;
	}
	else
	{
	    CS_DEBUG(fprintf(fpDebugOut, "Couldn't match types in CS_Curve:CopyCurve()\n") ;)
	}
	pn = pn->next ;
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;

    if (pn == NULL)
	return 1 ;
    return 0 ;
}


CS_Curve *CS_Curve::CopyCurve()
{
    CS_CurvePtr pcrv = new CS_Curve ; 
    pcrv->CopyCurve(*this) ; 
    return pcrv ; 
}

// TO DO - test this function out to see if it works right
CS_Curve &CS_Curve::operator=(const CS_Curve &crv)
{
    Destroy() ; 
    pUserData = crv.pUserData ; 
    pcnmap = crv.pcnmap ; 
    bndrect = crv.bndrect ; 

    CS_SegPtr pn = crv.pStart ;

    CS_DEBUG(fprintf(fpDebugOut, "Entered CS_Curve::operator=(CS_Curve&)\n") ; )

    // TO DO - rewrite using the new CopySegment features
    while (pn)
    {
        if (pn->SegmentType() == CS_Segment::ARC_TYPE)
	{   // Then create an arc
	    CS_ArcSeg *pnewseg = new CS_ArcSeg((CS_ArcSeg *)pn) ;
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg, CS_NOENDPOINTADJUSTMENT) ;
	}
        else if (pn->SegmentType() == CS_Segment::LINE_TYPE)
	{   // Then create a line
	    CS_LineSeg *pnewseg = new CS_LineSeg((CS_LineSeg *)pn);
            pnewseg->cp = pn->cp ; 
            pnewseg->pUserData = pn->pUserData ; 
	    Append(pnewseg, CS_NOENDPOINTADJUSTMENT) ;
	}
	else
	{
	    CS_DEBUG(fprintf(fpDebugOut, "Couldn't match types CS_Curve::operator=()\n") ;)
	}
	pn = pn->next ;
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;

    return *this ;
}

void CS_Curve::SetParentPointers() 
{
    CS_SegPtr psn = pStart ; 
    while (psn) 
    {
        psn->pParent = this ; 
        psn = psn->next ; 
    }
} 


//! Walk along each curve segment, stopping at the to crv point,
CS_CrvPnt CS_Curve::StepTo(CS_CrvPnt &from, CS_CrvPnt &to)
{
    CS_CrvPnt cp ; 
    if (from.s == to.s)
    {
        if (tcomp_LT(from.u, to.u))
        {
            cp.s = to.s ; 
            cp.u = to.u ; 

            return cp ; 
        }
        // else we are walking right around the curve
    }
    
    if (tcomp_EQ(from.u, 1.0))
    {   // Then already at the end of this segment which is same
        // as start of next so want to skip one segment
        cp.s = from.s->pParent->Next(from.s) ; 
        if (cp.s == to.s)
        {
            cp.u = to.u ; 
            return cp ; 
        }

        cp.s = from.s->pParent->Next(cp.s) ; 
        cp.u = 0.0 ; 
    }
    else
    {
        cp.s = from.s->pParent->Next(from.s) ; 
        cp.u = 0.0 ; 
    }

    return cp ; 
}

//! Walk backwards along each curve segment, stopping at the to crv point,
CS_CrvPnt CS_Curve::StepBackTo(CS_CrvPnt &from, CS_CrvPnt &to)
{
    CS_CrvPnt cp ; 
    if (from.s == to.s)
    {
        if (tcomp_GT(from.u, to.u))
        {
            cp.s = to.s ; 
            cp.u = to.u ; 

            return cp ; 
        }
        // else we are walking right around the curve
    }
    
    if (tcomp_NEZ(from.u)) 
    {
        cp.s = from.s ; 
        cp.u = 0.0 ; 
    }
    else
    {
        cp.s = from.s->pParent->Prev(from.s) ; 
        if (from.s == to.s)
            cp.u = to.u ; 
        else
            cp.u = 0.0 ; 
    }

    return cp ; 
}


void CS_Curve::Replace(CS_SegPtr pnode, CS_SegPtr pnewseg)
{
    // Want to replace the old with the new and update the arclength
    // as well, note this arclength change should be approximately 0.0
    arclength -= pnode->ArcLength() ; // subtract old value
    arclength += pnewseg->ArcLength() ;     // and add the new value

    if (pnode->StartPoint() != pnewseg->StartPoint())
	pnewseg->Reverse() ; // then flip it around so the orientation is right

    pnewseg->prev    = pnode->prev ; 
    pnewseg->next    = pnode->next ; 
    pnewseg->uo      = pnode->uo ; 
    pnewseg->cnt     = pnode->cnt ; 
    pnewseg->pParent = pnode->pParent ; 
    
    if (pStart == pnode)
        pStart = pnewseg ; 
    
    if (pEnd == pnode)
        pEnd = pnewseg ; 
    
    if (pnode->prev)
        pnode->prev->next = pnewseg ; 
    
    if (pnode->next)
        pnode->next->prev = pnewseg ; 

    delete pnode ; // free up the memory for the previous segment
}


void CS_Curve::CrvU2SegU(double u, CS_SegPtr &pseg, double &useg)
{
    // See notes Geom Algo's 4 pg 25
    pseg = USegment(u) ; 
    double ulenseg = SegmentULength(pseg) ; 

    if (tcomp_LEQ(u, pseg->uo))
        useg = 0.0 ; 
    else if (tcomp_GEQ(u, pseg->uo + ulenseg))
        useg = 1.0 ; 
    else 
    {
        useg = (u - pseg->uo) / ulenseg ; 
        if (useg < 0.0)
            useg = 0.0 ; 
        else if (useg > 1.0) 
            useg = 1.0 ; 
    }
}


void CS_Curve::CrvU2SegU(double u, CS_CrvPnt &cp)
{
    // See notes Geom Algo's 4 pg 25
    cp.s = USegment(u) ; 
    double ulenseg = SegmentULength(cp.s) ; 

    if (tcomp_LEQ(u, cp.s->uo))
        cp.u = 0.0 ; 
    else if (tcomp_GEQ(u, cp.s->uo + ulenseg))
        cp.u = 1.0 ; 
    else 
    {
        cp.u = (u - cp.s->uo) / ulenseg ; 
        if (cp.u < 0.0)
            cp.u = 0.0 ; 
        else if (cp.u > 1.0) 
            cp.u = 1.0 ; 
    }
}


double CS_Curve::CrvU2SegU(double u, CS_SegPtr pseg)
{
    double ulenseg = SegmentULength(pseg) ; 

    if (tcomp_LEQ(u, pseg->uo))
        return 0.0 ; 
    else if (tcomp_GEQ(u, pseg->uo + ulenseg))
        return 1.0 ; 
    else 
    {
        double uret = (u - pseg->uo) / ulenseg ; 
        if (uret < 0.0)
            return 0.0 ; 
        else if (uret > 1.0) 
            return 1.0 ; 
        return uret ; 
    }
}

double CS_Curve::FastCrvU2SegU(double u, CS_SegPtr pseg)
{
    return (u - pseg->uo) / SegmentULength(pseg) ; 
}


void CS_Curve::CrvU2SegU(double u, CS_SegPtr pshint, CS_CrvPnt &cp)
{
    // See notes Geom Algo's 4 pg 25
    if (!pshint)
    {
        CrvU2SegU(u, cp) ; 
    }
    else
    {   
        if (u < 0.0)
            u = 0.0 ; 
        else if (u > 1.0)
            u = 1.0 ; 

        if (u > pshint->uo)
        {   // Then we have to move forward from the start of the segment
            while (pshint->next && u > pshint->next->uo)
                pshint = pshint->next ; // search forwards
        }
        else
        {   // Have to move backwards to find the segment
            while (pshint->prev && u < pshint->uo)
                pshint = pshint->prev ; 
        }

        double ue = 1.0 ; 
        if (pshint->next)
            ue = pshint->next->uo ; 

        cp.s = pshint ; 

        // Now work out the u value ;
        double ulenseg = SegmentULength(cp.s) ; 
        cp.u = (u - pshint->uo) / ulenseg ; 

        // Adjust up useg for any rounding errors
        if (cp.u < 0.0)
            cp.u = 0.0 ; 
        else if (cp.u > 1.0) 
        {
            if (cp.s->next)
            {
                cp.s = cp.s->next ; 
                cp.u = 0.0 ; 
            }
            else
            {
                cp.u = 1.0 ; 
            }
        }
    }
}


CS_CrvPnt CS_Curve::UCrvPnt(double ucrv)
{
    CS_CrvPnt cp ;
    CrvU2SegU(ucrv, cp.s, cp.u) ;
    return cp ; 
}


// Sets the start of the curve to the segment pnewStart. 
// Note: pnewStart has to be part of the existing curve or else
// all kinds of memory problems will occur. No test is done to make
// sure that pnewStart is part of the curve.
void CS_Curve::SetStartSegment(CS_SegPtr pnewStart) 
{
    if (pnewStart == pStart)
        return ; // nothing to do
    
    // No need to test for single node curve since test above
    // also tests that condition 

    // First connect up the current start and end nodes
    pStart->prev = pEnd ; 
    pEnd->next = pStart ; 

    pStart = pnewStart ; 
    pEnd = pnewStart->prev ; // note the only node without a prev point 
    // is pStart and test for pnewStart == pStart condition on entry

    pStart->prev = 0 ; 
    pEnd->next = 0 ; 
}


void CS_Curve::SetStartPoint(double u)
{
    CS_POINT newsp = UPoint(u) ; 
    CS_SegPtr pseg = USegment(u) ; 
    // Get the relative u point along the segment that matches the input u value
    double ulenseg = SegmentULength(pseg) ; 
    if (tcomp_EQ(pseg->uo, u))
    {   // Then simply set this segment as the curve start point
        SetStartSegment(pseg) ; 
    }
    else if (tcomp_EQ(pseg->uo + ulenseg, u))
    {   
        SetStartSegment(Next(pseg)) ; 
    }
    else
    {   // The start point is somewhere along the pseg segment
        pseg = Split(u) ;
        if (pseg)
            SetStartSegment(pseg) ; 
    }
}

CS_SegPtr CS_Curve::AddPoint(CS_POINT &p)
{
    if (!pStart) 
    {
        pStart = new CS_LineSeg(p, p) ; 
        pStart->prev = 0 ; 
        pStart->next = 0 ; 
	pEnd = pStart ;
	nodecnt = 1 ;
        arclength = 0 ; 
    }
    else if ((pStart == pEnd) && 
             (pStart->StartPoint() == pStart->EndPoint()) )
    {   // Then we have a single point defined so far
        CS_LineSeg *pls = static_cast<CS_LineSeg *>(pStart) ; 
        pls->ep = p ; 
        arclength = pls->ArcLength() ; 
    }
    else 
    {
        CS_LineSeg *pls = new CS_LineSeg(pEnd->EndPoint(), p) ; 
        Append(pls, CS_NOADJUST) ; 
    }

    return pEnd ; 
}


CS_SegPtr CS_Curve::Append(CS_SegPtr pseg, int NoEndpointAdjustment)
{
    pseg->prev = 0 ; 
    pseg->next = 0 ; 
    nodecnt += 1 ;
    arclength += pseg->ArcLength() ;

    if (pStart == NULL)
    {	// then create the Head node (1st entry)
	pStart = pseg ;
	pEnd = pseg ;
	nodecnt = 1 ;
    }
    else
    {
	pEnd->next = pseg ;
	pseg->prev = pEnd ;
	pEnd = pseg ;
	pseg->next = 0 ;
    }
    // Now we want to adjust the orientation of the newly added curve so that
    // the direction with the existing curve makes sense. If the end points
    // don't match up then no orientation adjustment is made
    if (!NoEndpointAdjustment)
	AdjustSegmentDirection(pseg) ;

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID | CS_UVALUE_VALID) ;

    return pseg ; // success
}


CS_SegPtr CS_Curve::Insert(CS_SegPtr pins,
			     CS_SegPtr pseg,
			     int NoEndpointAdjustment)
{
    pseg->prev = 0 ; 
    pseg->next = 0 ; 
    nodecnt += 1 ;
    arclength += pseg->ArcLength() ;

    if (pins == NULL)
    {	// We are initializing the list or inserting in the 
        // front of the curve
        if (pStart) 
        {   // Insert in front of curve
            pStart->prev = pseg ; 
            pseg->next = pStart ; 
            pseg->prev = 0 ; 
            pStart = pseg ; 
	    if (!NoEndpointAdjustment)
		AdjustSegmentDirection(pseg) ;
        }
        else
        {   // initialize a brand new curve
	    pStart = pseg ;
	    pEnd = pseg ;
	    nodecnt = 1 ;
        }
        return pseg ; 
    }
    else if (pins == pStart)
    {	// Then we pushing onto the front of the list
	pseg->next = pStart ;
	pStart->prev = pseg ;
        pseg->prev = 0 ; 
	pStart = pseg ; // set the new Head element
    }
    else
    {	// Else we inserting inside the list
	// (i.e) there is a node in front of pins
	pins->prev->next = pseg ;
	pseg->prev = pins->prev ;
	pseg->next = pins ;
	pins->prev = pseg ;
    }

    if (!NoEndpointAdjustment)
	AdjustSegmentDirection(pseg) ;

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID | CS_UVALUE_VALID) ;

    return pseg ;
}


CS_SegPtr CS_Curve::InsertAfter(CS_SegPtr pins,
			          CS_SegPtr pseg,
			          int NoEndpointAdjustment)
{
    nodecnt += 1 ;
    arclength += pseg->ArcLength() ;

    if (pins == NULL)
    {	// Then this is the first node in the list
	// or default to the append operation
	if (pStart)
	{   // We will do an append as the default case
	    pEnd->next = pseg ;
	    pseg->prev = pEnd ;
	    pEnd = pseg ;
	    pseg->next = 0 ;
	    if (!NoEndpointAdjustment)
		AdjustSegmentDirection(pseg) ;
	}
	else
	{   // initialize the curve
	    pStart = pseg ;
	    pEnd = pseg ;
	    nodecnt = 1 ;
	}
	return pseg ;
    }

    // Else we are inserting after a valid node
    pseg->next = pins->next ; // set this first so we save it
    pins->next = pseg ;	     // now adjust current node
    pseg->prev = pins ;	     // set the new nodes prev pointer
    if (pseg->next != NULL)
    {	// Then we haven't added to the end of the list
	pseg->next->prev = pseg ;
    }
    else
    {	// otherwsie we did so adjust the end pointer
	pEnd = pseg ;
    }
    if (!NoEndpointAdjustment)
	AdjustSegmentDirection(pseg) ;

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID | CS_UVALUE_VALID) ;

    return pseg ;
}




// Make sure this segment is oriented in the right direction to the previous one
void CS_Curve::AdjustSegmentDirection(CS_SegPtr pn)
{
    if (pn->prev != NULL)
    {	// Then orient the previous and this segment
	// Note if there are already two segments in the list then no
	// reversal can take place since those segments are already oriented

	// See RR-Vol1 Pgs 73-74 for notes on this logic
	double ss, se, es, ee ;
	ss = DistanceSquared(pn->prev->StartPoint(),
			     pn->StartPoint()) ;

	se = DistanceSquared(pn->prev->StartPoint(),
			     pn->EndPoint()) ;

	es = DistanceSquared(pn->prev->EndPoint(),
			     pn->StartPoint()) ;

	ee = DistanceSquared(pn->prev->EndPoint(),
			     pn->EndPoint()) ;

	int q,r,s,t,u,v ;
	q = ss < se ;
	r = ss < es ;
	s = ss < ee ;
	t = se < es ;
	u = se < ee ;
	v = es < ee ;

	CS_DEBUGCREATE(fprintf(fpDebugOut, "q=%d r=%d s=%d t=%d u=%d v=%d\n",q,r,s,t,u,v)) ;

	if (!r && v && !t)
	    return ; // we don't have to do anything
	else if (!s && !v && !u)
	{
	    pn->Reverse() ; // reverse this curve
	    return ;
	}
	else if ((!q && t && u) && (nodecnt == 2))
	{   // then we can reverse both segments
	    pn->prev->Reverse() ;
	    pn->Reverse() ;
	    return ;
	}
	else if ((q && r && s) && (nodecnt == 2))
	{
	    pn->prev->Reverse() ;
	    return ;
	}
	else
	{
	    CS_DEBUGCREATE(
		fprintf(fpDebugOut, "Couldn't adjust end point\n") ;
	    )
	}
    }
    else if (pn->next != NULL)
    {	// Orient this segment with the next one
	// Note if there are already two segments in the list then no
	// reversal can take place since those segments are already oriented
	double ss, se, es, ee ;
	ss = DistanceSquared(pn->next->StartPoint(),
			     pn->StartPoint()) ;

	se = DistanceSquared(pn->next->StartPoint(),
			     pn->EndPoint()) ;

	es = DistanceSquared(pn->next->EndPoint(),
			     pn->StartPoint()) ;

	ee = DistanceSquared(pn->next->EndPoint(),
			     pn->EndPoint()) ;

	if (tcomp_EQZ(se))
	    return ; // we don't have to do anything
	else if (tcomp_EQZ(ss))
	{
	    pn->Reverse() ; // reverse this curve
	    return ;
	}
	else if (tcomp_EQZ(es) && (nodecnt == 2))
	{   // then we can reverse both segments
	    pn->next->Reverse() ;
	    pn->Reverse() ;
	    return ;
	}
	else if (tcomp_EQZ(ee) && (nodecnt == 2))
	{   // The reverse only the next curve
	    pn->next->Reverse() ;
	    return ;
	}
	else
	{
	    CS_DEBUGCREATE(
		fprintf(fpDebugOut, "Couldn't adjust end point\n") ;
	    )
	}
    }
}

/*
void CS_Curve::AdjustSegmentDirection(CS_SegNode *pn)
{
    if (pn->prev != NULL)
    {	// Then orient the previous and this segment
	// Note if there are already two segments in the list then no
	// reversal can take place since those segments are already oriented
	if (pn->prev->pseg->EndPoint() == pn->pseg->StartPoint())
	    return ; // we don't have to do anything
	else if (pn->prev->pseg->EndPoint() == pn->pseg->EndPoint())
	{
	    pn->pseg->Reverse() ; // reverse this curve
	    return ;
	}
	else if ((pn->prev->pseg->StartPoint() == pn->pseg->EndPoint()) &&
		 (nodecnt == 2))
	{   // then we can reverse both segments
	    pn->prev->pseg->Reverse() ;
	    pn->pseg->Reverse() ;
	    return ;
	}
	else if ((pn->prev->pseg->StartPoint() == pn->pseg->StartPoint()) &&
		 (nodecnt == 2))
	{
	    pn->prev->pseg->Reverse() ;
	    return ;
	}
	else
	{
	    CS_DEBUGCREATE(
		fprintf(fpDebugOut, "Couldn't adjust end point\n") ;
	    )
	}
    }
    else if (pn->next != NULL)
    {	// Orient this segment with the next one
	// Note if there are already two segments in the list then no
	// reversal can take place since those segments are already oriented
	if (pn->pseg->EndPoint() == pn->next->pseg->StartPoint())
	    return ; // we don't have to do anything
	else if (pn->pseg->StartPoint() == pn->next->pseg->StartPoint())
	{
	    pn->pseg->Reverse() ; // reverse this curve
	    return ;
	}
	else if ((pn->pseg->StartPoint() == pn->next->pseg->EndPoint()) &&
		 (nodecnt == 2))
	{   // then we can reverse both segments
	    pn->prev->pseg->Reverse() ;
	    pn->pseg->Reverse() ;
	    return ;
	}
	else if ((pn->pseg->EndPoint() == pn->next->pseg->EndPoint()) &&
		 (nodecnt == 2))
	{   // The reverse only the next curve
	    pn->next->pseg->Reverse() ;
	    return ;
	}
	else
	{
	    CS_DEBUGCREATE(
		fprintf(fpDebugOut, "Couldn't adjust end point\n") ;
	    )
	}
    }
}
*/

void CS_Curve::Reset()
{
    Destroy() ;
}

void CS_Curve::Destroy()
{
    CS_SegPtr pn = pStart ;
    CS_SegPtr ptmp ;

    while (pn != NULL)
    {
	ptmp = pn ;
	pn = pn->next ;
	delete ptmp ;
    }

    pStart = NULL ;
    pEnd = NULL ;
    nodecnt = 0 ;
    statflags = 0 ;
    arclength = 0.0 ;
    if (pcnmap)
    {
        delete pcnmap ; 
        pcnmap = 0 ; 
    }
}

//! Delete segment from the curve and free segment's memory 
/*! 
 \param psn pointer to segment node to be deleted
 Delete the node from the curve. Note this node must be part of this
 curve since no check is done to make sure we are in fact deleting a
 node from the current curve. If this node is not part of this curve
 list then things get messy (they break). No end point adjustment 
 is done thus the prev and next curves endpoints will not match up
 after the segment is deleted. Caller must ensure curve integrity if
 this is required.
 Note: currently only makes sense to use this when deleting
	nodes from the front or back of the list
 */    
void CS_Curve::Delete(CS_SegPtr psn)
{
    if (psn == NULL)
	return ;

    if (nodecnt == 1)
    {	// Then there is only one node in the list
	// Note pStart and pEnd should be equal
	pStart = pEnd = NULL ;
	arclength = 0.0 ;
	nodecnt = 0 ;
	delete psn ;
	return ;
    }
    // Else there is more than 1 node in the list

    arclength -= psn->ArcLength() ;
    nodecnt -= 1 ;
    if (psn == pStart)
    {
	pStart = psn->next ;
	pStart->prev = NULL ;
	delete psn ;
	return ;
    }
    else if (psn == pEnd)
    {
	pEnd = psn->prev ;
	pEnd->next = NULL ;
	delete psn ;
	return ;
    }
    // else the node is surrounded by two other nodes
    psn->prev->next = psn->next ;
    psn->next->prev = psn->prev ;
    delete psn ;

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID | CS_UVALUE_VALID) ;

}



CS_SegPtr CS_Curve::Remove(CS_SegPtr psn)
{
    if (psn == NULL)
	return 0 ;

    if (nodecnt == 1)
    {	// Then there is only one node in the list
	// Note pStart and pEnd should be equal
	pStart = pEnd = NULL ;
	arclength = 0.0 ;
	nodecnt = 0 ;
	return 0 ;
    }
    // Else there is more than 1 node in the list

    arclength -= psn->ArcLength() ;
    nodecnt -= 1 ;
    if (psn == pStart)
    {
	pStart = psn->next ;
	pStart->prev = NULL ;
	return pStart ;
    }
    else if (psn == pEnd)
    {
	pEnd = psn->prev ;
	pEnd->next = NULL ;
        psn = 0 ; 
        if (Closed())
            psn = pStart ; 
	return psn ;
    }
    // else the node is surrounded by two other nodes
    psn->prev->next = psn->next ;
    psn->next->prev = psn->prev ;

    psn = psn->next ;
    if (!psn && Closed())
        psn = pStart ;
    
    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID | CS_UVALUE_VALID) ;

    return psn ;
}

///////////////////////////////////////////////////////////////////
// Load curve lists from file
// A single CURVE-END section is read from the file. After reading
// the END parameter the routine returns. The curves read in are
// appended to the end of the existing curve if any.
// Returns true if read a new curve otherwise returns false
///////////////////////////////////////////////////////////////////
int CS_Curve::ReadFromFile(FILE *crvfl)
{
    char buffer[1024] ;
    int readmode ;
    int readcurve ;

    readcurve = 0 ; // set true if curve is added to
    readmode = 0 ;

    while(fgets(buffer, 1023, crvfl) != NULL)
    {
	CS_DEBUG(fprintf(fpDebugOut, "CS_Curve::ReadFromFile() Input buffer='%s'", buffer) ;)

	if (!readmode)
	{
	    if (strstartis("CURVE", buffer) != NULL)
	    {	// Then this is a new curve definition
		readmode = 1 ;
	    }
	}
	else
	{   // We are currently reading a line string
	    // we ignore eveything up until the first curve is started
	    if (strstartis("LINE", buffer) != NULL)
	    {
		// string, curvelist
		CS_LineSeg *pls = new CS_LineSeg ;

		sscanf(&buffer[5],"%lf %lf %lf %lf %lf %lf",
			    &pls->sp.p[0], &pls->sp.p[1], &pls->sp.p[2],
			    &pls->ep.p[0], &pls->ep.p[1], &pls->ep.p[2]) ;
		CS_DEBUG(fprintf(fpDebugOut, "Read line (%lf %lf %lf) (%lf %lf %lf)\n",
			    pls->sp.p[0], pls->sp.p[1], pls->sp.p[2],
			    pls->ep.p[0], pls->ep.p[1], pls->ep.p[2]) ;)
		Append(pls) ;
		readcurve = 1 ;
	    }
	    else if (strstartis("ARC", buffer) != NULL)
	    {
		CS_POINT ctr ;
		double radius, sang, sweep ;
		int arcdir ;

		CS_ArcSeg *pas = new CS_ArcSeg ;

		sscanf(&buffer[4], "%lf %lf %lf %lf %lf %lf %d",
			&ctr.p[0], &ctr.p[1], &ctr.p[2],
			&radius, &sang, &sweep, &arcdir) ;

		pas->ctr = ctr ;
		pas->rad = radius ;
		pas->swp = fabs(sweep) ;
	        pas->sa = mod2PI(sang) ;

		if (arcdir == CW)
		{   // Then we have to adjust the parameters for the arc
                    pas->swp = -pas->swp ; 
		}
		Append(pas) ;

		readcurve = 1 ;
	    }
	    else if (strstartis("ENDCURVE", buffer) != NULL)
	    {
		readmode = 0 ; // end of curve reached
		break ; // we want to return at this point
	    }
	}
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;

    return readcurve ;
}

// Reverse the direction of the curve list
void CS_Curve::Reverse()
{
    CS_SegPtr pn ;
    CS_SegPtr plast ;
    CS_SegPtr p1 ;
    // swap the front and back pointers
    pn = pStart ;
    pStart = pEnd ;
    pEnd = pn ;

    plast = NULL ; // last node processed
    // Now reverse the actual list
    while (pn != NULL)
    {
	CS_DEBUG(fprintf(fpDebugOut, "reversing curve in CS_Curve:Reverse()\n") ;)
	pn->Reverse() ;
	p1 = pn->next ;
        if (p1)
            pn->uo = 1.0 - p1->uo ; 
        else 
            pn->uo = 0.0 ; 
	pn->next = plast ;
	pn->prev = p1 ;
	plast = pn ; // set last to current node
	pn = p1 ;
    }

    // The last node processed should be the new head node
    if (plast != pStart)
    {
	CS_DEBUG(fprintf(fpDebugOut, "CS_Curve:Reverse() error, tail pointer incorrect\n") ;)
    }
}

// Complete is ReadFromFile
void CS_Curve::WriteCurveToFile(FILE* fl, int prec)
{
    CS_SegPtr pn ;
    char formatstr[256] ; 

    pn = pStart ; // get start of the list
    fprintf(fl, "CURVE\n") ; 
    while (pn != NULL)
    {
        if (pn->SegmentType() == CS_Segment::LINE_TYPE)
	{
	    CS_LineSeg *pline = (CS_LineSeg *)pn ;
            sprintf(formatstr, "LINE %%.%dlf %%.%dlf %%.%dlf %%.%dlf %%.%dlf %%.%dlf\n",
                            prec, prec, prec, prec, prec, prec) ;  
	    fprintf(fl, formatstr,
		pline->sp.p[0], pline->sp.p[1], pline->sp.p[2],
		pline->ep.p[0], pline->ep.p[1], pline->ep.p[2]) ;
	}
        else if (pn->SegmentType() == CS_Segment::ARC_TYPE)
	{
	    int dir ;
	    double sa, swp ;
	    CS_ArcSeg *parc = (CS_ArcSeg *)pn ;
	    sa = parc->sa ;
	    swp = fabs(parc->swp) ;
            dir = parc->swp > 0 ? CCW : CW ;

            sprintf(formatstr, "ARC %%.%dlf %%.%dlf %%.%dlf %%.%dlf %%.%dlf %%.%dlf %%d\n",
                            prec, prec, prec, prec, prec, prec) ;  

            fprintf(fl, formatstr,
			parc->ctr.p[0],parc->ctr.p[1],parc->ctr.p[2],
			parc->rad, sa, swp, dir) ;
	}
	else
	{
	    CS_DEBUG(
	      fprintf(fpDebugOut, "Eror: unknown segment type in WriteOutCurveList()\n") ;)
	}
	pn = pn->next ;
    }
    fprintf(fl, "ENDCURVE\n") ; 
}

// converts the input value from a length to a u delta. 
double CS_Curve::ArcLengthToDeltaU(double alen) 
{
    if (!(statflags & CS_ARCLENGTH_VALID))
        CalcArcLength() ; 

    return alen / arclength ; 
}

double CS_Curve::DeltaUToArcLength(const double &uo, const double &uf)
{
    if (!(statflags & CS_ARCLENGTH_VALID))
        CalcArcLength() ; 

    if (tcomp_EQ(uo, uf))
        return 0.0 ; 
    
    if (statflags | CS_CLOSEDCURVE)
    {
        if (uo < uf)
            return (uf-uo) * arclength ; 
        return (1.0 - uo + uf) * arclength ; 
    }
    
    // Else it's an open curve
    if (uo < uf)
        return (uf-uo) * arclength ; 
    return (1.0 - uo) * arclength ; 
}

double CS_Curve::UMid(const double &ua, const double &ub) 
{
    if (ua < ub) 
        return ua + (ub-ua) / 2.0 ; 
    double du = (1.0 - ua + ub) / 2.0 ; 
    double u = ua + du ; 
    if (u > 1.0)
        u = u - 1.0 ; 
    return u ; 
}

double CS_Curve::UMidShortest(const double &ua, const double &ub) 
{
    return CS_UMidShortest(ua, ub, Closed()) ;
}


int CS_Curve::UOnSection(double u, double ua, double ub) 
{   // TODO optimize the Closed() testing so that it just tests
    // the status bit. 
    return ::UOnSection(u, ua, ub, Closed()) ;
}


int CS_Curve::UInSection(double u, double ua, double ub)
{   // TODO optimize the Closed() testing so that it just tests
    // the status bit. 
    return ::UInSection(u, ua, ub, Closed()) ;
}



// Also updates the nodecnt variable
double CS_Curve::CalcArcLength()
{
    CS_SegPtr pn ;
    pn = pStart ;
    arclength = 0.0 ;
    nodecnt = 0 ; 
    while (pn)
    {
	arclength += pn->ArcLength() ;
        pn->cnt = nodecnt++ ; 
	pn = pn->next ;
    }
    statflags |= CS_ARCLENGTH_VALID | CS_NODECNT_VALID ;
    return arclength ;
}


double CS_Curve::ArcLength() 
{
    if (statflags & CS_ARCLENGTH_VALID)
        return arclength ;
    return CalcArcLength() ; 
}


double CS_Curve::CalcXYArcLength()
{
    CS_SegPtr pn ;
    pn = pStart ;
    XYarclength = 0.0 ;
    nodecnt = 0 ; 
    while (pn)
    {
	XYarclength += pn->XY_ArcLength() ;
        pn->cnt = nodecnt++ ; 
	pn = pn->next ;
    }

    // Set the following status bits
    statflags |= CS_XY_ARCLENGTH_VALID | CS_NODECNT_VALID ;

    return XYarclength ;
}

//! Force a calculation for the XYarclength variable if calc is true
double CS_Curve::XY_ArcLength(int calc)
{
    if (calc)
	return CalcXYArcLength() ;
    return XYarclength ;
}

CS_POINT CS_Curve::Centroid()
{
    CS_SegPtr psn = pStart ; 
    CS_POINT centroid(0,0,0) ; 

    while (psn)
    {
        centroid += psn->Centroid() * psn->ArcLength() ; 
        psn = psn->next ; 
    }

    centroid /= arclength ; 
    return centroid ; 
}

CS_POINT CS_Curve::Centroid2D()
{
    CS_SegPtr psn = pStart ; 
    CS_POINT centroid(0,0,0) ; 

    while (psn)
    {
        centroid += psn->Centroid2D() * psn->ArcLength() ; 
        psn = psn->next ; 
    }

    centroid /= arclength ; 
    return centroid ; 
}



// This returns the point on the curve at that U value. If pnpnt is not
// NULL then the actual segnode used in the calculation of the final 
// point value is also returned
CS_POINT CS_Curve::UPoint(double u, CS_SegPtr *pnpnt, int srchmode)
{
    CS_POINT pnt(0,0,0) ;

    if (!pStart)
        return pnt ; 

    int pointset ;

    if (u < 0.0)
        u = 0.0 ; 
    else if (u > 1.0)
        u = 1.0 ; 

    if (srchmode == CS_SEARCHBYARCLENGTH)
    {
        if (arclength > 0.0)
        {
            CS_SegPtr pn ;
	    double sumlen, alen, ulen ;
	    pn = pStart ;
	    ulen = arclength * u ; // length along curve @ u-point
	    // First we have to find the segment that the U value lies on
	    sumlen = 0 ;

	    CS_DEBUG(fprintf(fpDebugOut, "Calculating upoint(%.5lf)\n", u)) ;

	    pointset = 0 ;

	    while (pn)
	    {
	        alen = pn->ArcLength() ;
	        if (tcomp_GEQ((sumlen + alen), ulen))
	        {	// Then this is the segment the u-point is on
		    // We want the incremental length along this segment so we
		    // have to generate an internal u value to generate the
		    // required point.
		    double uo, uf, upi ;
		    uo = sumlen / arclength ;
		    uf = (sumlen + alen) / arclength ;
		    upi = (u - uo) / (uf - uo) ;

		    CS_DEBUG(fprintf(fpDebugOut, "uo=%.5lf  uf= %.5lf  upi=%.5lf\n",
				        uo, uf, upi) ; )

		    pnt = pn->UPoint(upi) ;
                    if (pnpnt)
                        *pnpnt = pn ; 
		    pointset = 1 ;
		    break ;
	        }
	        else
	        {
		    sumlen += alen ;
	        }
	        pn = pn->next ;
	    }

	    if (!pointset)
	    {   // Then we went through the entire curve and didn't reach the required
	        // arc length. This might occur in a case where the user requests an
	        // XY_Point(1.0 - eps) where eps is some exceedingly small value.
	        // We are filtering this case at the start but this extra test requires
	        // no extra time really so we include it here just to make sure that
	        // a valid value is returned.
                if (pnpnt)
                    *pnpnt = pEnd ; 
	        pnt = EndPoint() ;
	    }
        }
        else
        {
	    CS_DEBUG(fprintf(fpDebugOut, "arclength of CS_Curve <= 0 in CS_Curve::UPoint()\n") ;)
        }
        return pnt ;
    }
    else
    {   // Find the UPoint based on uo values in the seg nodes

        CS_SegPtr pn ;
        CS_SegPtr plast ; 

	pn = plast = pStart ;

	while (pn)
	{
            if (u < pn->uo)
                break ; 
            plast = pn ; 
            pn = pn->next ; 
        }
        // plast points to the segment that the u value occurs on 

        // Now work out the actual point (See Notes RR-VOL1 Pg 140)
        double ue, uo, ur ; 
        
        if (pn)
            ue = pn->uo ; // found segment with larger u value start
        else 
            ue = 1.0 ; // went off the end

        uo = plast->uo  ; // plast is the segment that has the point on it

        ur = (u - uo) / (ue - uo) ; 

        if (pnpnt)
            *pnpnt= plast ; 

        pnt = plast->UPoint(ur) ; 
        return pnt ; 
    }

    return pnt ; // error condition if we get here
}




// Returns the very first segment node found that contains the u value 
// passed. This can be a segment who's endpoint matches the u value
// Currently this walks along the curve by calculating segment arc lengths
// search mode can be:
//   CS_SEARCHBYARCLENGTH      0 
//   CS_SEARCHBYUVALUE         1 
// default = CS_SEARCHBYARCLENGTH

CS_SegPtr CS_Curve::USegment(double u, int searchmode)
{
    CS_POINT pnt(0,0,0) ;
    int pointset ;
    CS_SegPtr pn ;

    if (tcomp_LT(u, 0.0) || tcomp_GT(u, 1.0))
        return 0 ; // not valid

    if (searchmode == CS_SEARCHBYARCLENGTH)
    {
        pn = 0 ; 

        if (arclength > 0.0)
        {
	    double sumlen, ulen ;
	    pn = pStart ;
	    ulen = arclength * u ; // length along curve @ u-point
	    // First we have to find the segment that the U value lies on
	    sumlen = 0 ;

	    CS_DEBUG(fprintf(fpDebugOut, "Calculating upoint(%.5lf)\n", u)) ;

	    pointset = 0 ;

	    while (pn)
	    {
                sumlen += pn->ArcLength() ;
	        if (tcomp_GEQ(sumlen, ulen))
	        {	// Then this is the segment the u-point is on
		    // We want the incremental length along this segment so we
		    // have to generate an internal u value to generate the
		    // required point.
                    return pn ; 
	        }
	        else
	        {
	        }
	        pn = pn->next ;
	    }

            pn = pEnd ; 
        }
        else
        {
	    CS_DEBUG(fprintf(fpDebugOut, "arclength of CS_Curve <= 0 in CS_Curve::UPoint()\n") ;)
        }
    
        return pn ;
    }
    else
    {   // Search the curve by uo's
        // Walk along the curve until we find the u value required
	// First we have to find the segment that the U value lies on

        CS_SegPtr plast ; 

	pointset = 0 ;
	pn = plast = pStart ;

	while (pn)
	{
            if (u < pn->uo)
                break ; 
            plast = pn ; 
            pn = pn->next ; 
        }
        // plast points to the segment that the u value occurs on 

        return plast ;
    }

    return 0 ; 
}


CS_SegPtr *CS_Curve::BuildSegArray()
{
    if (nodecnt <= 0)
        return 0 ; 
    CS_SegPtr *psa, pseg ; 
    psa = new CS_SegPtr[nodecnt] ; 
    
    int i = 0 ; 
    pseg = pStart ; 
    while (pseg && i < nodecnt)
    {
        psa[i++] = pseg ; 
        pseg = pseg->next ; 
    }

    return psa ; 
}


//! Uses the psegarray to quickly find the U point of the segment
/*!
    \param u value on curve for the point to be returned
    \param psegarray array of segments so that a binary search of uo values can be done
    \return the point on the curve at u
 */
CS_POINT CS_Curve::FastUPoint(double u, CS_SegPtr *psa) 
{
    CS_SegPtr pseg = FastUSegment(u, psa) ;
    if (pseg)
    {
        double useg = CrvU2SegU(u, pseg) ;
        return pseg->UPoint(useg) ; 
    }
    return CS_POINT(0,0,0) ; 
}


static inline int lessThanNextUo(double u, CS_SegPtr *psa, int i, int nodecount)
{
    if (i >= nodecount - 1)
        return 1 ; // must be true since this is the end of the curve
    if (tcomp_LEQ(u, psa[i+1]->uo))
        return 1 ; 
    return 0 ; 
}

//! Uses the psegarray to quickly find the U point of the segment
/*!
    \param u value on curve for the segment to be returned
    \param psegarray array of segments so that a binary search of uo values can be done
    \return the segment in the curve that contains the point at u
 */
CS_SegPtr CS_Curve::FastUSegment(double u, CS_SegPtr *psa)
{
    // Note: an extra node is add to the end of the curve that has 
    // a null segment pointer
    int a = 0 ; 
    int b = nodecnt ; 
    int i = nodecnt / 2 ; 
    // Binary search for alen
    do {
        if (tcomp_LT(u, psa[i]->uo)) 
        {   // move backwards
            b = i ; 
            i = (a+b)/2 ; 
        }
        else if (lessThanNextUo(u, psa, i, nodecnt))
        {   // Found the segment section
            return psa[i] ; 
        }
        else
        {   // Then can keep moving up 
            a = i ; 
            i = (a+b)/2 ; 
        }
    } while(true) ;
    return 0 ; 
}



////////////////////////////////////////////////////////////////////////////
// This returns the U point along the curve assuming the curve us projected
// onto the XY plane. Note that the Z component is still returned from the
// original curve in case this value is required. Thus if you want the actual
// projection point onto the XY plane, then set the z component to 0 before
// using the point returned by this function. It's purpose is to walk along
// the curve with U values while ignoring the Z component in calculating the
// distance walked along the curve.
// You can see that the only difference between this and the routine above
// is that the XY plane projected arclen is used in the calculations instead
// of the true arclength.
// The routine CalcXYArcLength() must be called before using this routine.
////////////////////////////////////////////////////////////////////////////
CS_POINT CS_Curve::XY_UPoint(double u, CS_SegPtr *pnpnt)
{

    CS_POINT pnt(0,0,0) ;
    // First calculate the xy projection arclength
    double xyarclen = XYarclength ;
    int pointset ;

    if (tcomp_GEQ(u, 1.0))
    {
        if (pnpnt)
            *pnpnt = pEnd ; 
	pnt = EndPoint() ; // no difference at the end of the curve
    }
    else if (xyarclen > 0.0)
    {
	double sumlen, alen, ulen ;
	CS_SegPtr pn = pStart ;
	ulen = xyarclen * u ; // length along curve @ u-point
	// First we have to find the segment that the U value lies on
	sumlen = 0.0 ;

	CS_DEBUG(fprintf(fpDebugOut, "Calculating upoint(%.5lf)\n", u)) ;

	pointset = 0 ;

	while (pn)
	{
	    alen = pn->XY_ArcLength() ;
	    if (tcomp_GEQ((sumlen + alen), ulen))
	    {	// Then this is the segment the u-point is on
		// We want the incremental length along this segment so we
		// have to generate an internal u value to generate the
		// required point.
		double uo, uf, upi ;
		uo = sumlen / xyarclen ;
		uf = (sumlen + alen) / xyarclen ;
		upi = (u - uo) / (uf - uo) ;

		CS_DEBUG(fprintf(fpDebugOut, "uo=%.5lf  uf= %.5lf  upi=%.5lf\n",
				    uo, uf, upi) ; ) ;

                if (pnpnt)
                    *pnpnt = pn ; 
		pnt = pn->UPoint(upi) ;
		pointset = 1 ;
		break ;
	    }
	    else
	    {
		sumlen += alen ;
	    }
	    pn = pn->next ;
	}

	if (!pointset)
	{   // Then we went through the entire curve and didn't reach the required
	    // arc length. This might occur in a case where the user requests an
	    // XY_Point(1.0 - eps) where eps is some exceedingly small value.
	    // We are filtering this case at the start but this extra test requires
	    // no extra time really so we include it here just to make sure that
	    // a valid value is returned.
            if (pnpnt)
                *pnpnt = pEnd ; 
	    pnt = EndPoint() ;
	}
    }
    else
    {
	CS_DEBUG(fprintf(fpDebugOut, "arclength of CS_Curve <= 0 in CS_Curve::XY_UPoint()\n") ;)
    }
    return pnt ;
}


CS_VECTOR CS_Curve::UTangent(double u)
{
    // We proceed in almost identical fashion to the UPoint routine
    // except we ask for the Tangent vector at the end
    CS_VECTOR vtan ;
    int pointset ;

    if (arclength > 0)
    {
	double sumlen, alen, ulen ;
	CS_SegPtr pn ;
        CS_SegPtr plast ;
	pn = pStart ;
	ulen = arclength * u ; // length along curve @ u-point
	// First we have to find the segment that the U value lies on
	sumlen = 0 ;
	pointset = 0 ;
	plast = pn ;
	while (pn)
	{
	    alen = pn->ArcLength() ;
	    if (tcomp_GEQ((sumlen + alen), ulen))
	    {	// Then this is the segment the u-point is on
		// We want the incremental length along this segment so we
		// have to generate an internal u value to generate the
		// required point.
		double uo, uf, upi ;
		uo = sumlen / arclength ;
		uf = (sumlen + alen) / arclength ;
		upi = (u - uo) / (uf - uo) ;
		vtan = pn->UTangent(upi) ;
		pointset = 1 ;
		break ;
	    }
	    else
	    {
		sumlen += alen ;
	    }
	    plast = pn ;
	    pn = pn->next ;
	}

	if (!pointset)
	{   // Then we went through the entire curve and didn't reach the required
	    // arc length. This might occur in a case where the user requests an
	    // XY_Point(1.0 - eps) where eps is some exceedingly small value.
	    // We are filtering this case at the start but this extra test requires
	    // no extra time really so we include it here just to make sure that
	    // a valid value is returned.
	    if (!plast)
	    {
		CS_DEBUG(fprintf(fpDebugOut, "CS_Curve::UTangent() error, plast not defined\n")) ;
	    }
	    else
	    {
		vtan = plast->UTangent(1.0) ; // want tangent of the end point
	    }
	}
    }

    return vtan ;
}


// Moves forwards FBepsilon relative to the length of the segment. 
CS_VECTOR CS_Curve::TanVectorForwards(CS_SegPtr pn, double ux, double epsilon)
{
    ux += epsilon ; 

    if (tcomp_GT(ux, 1.0))
    {   // Then move to the next segment
        ux = FBepsilon ; 
        if (statflags & CS_CLOSEDCURVE)
        {   // Then simply shift forwards
            pn = Next(pn) ; 
        }
        else
        {   // Check if we can or not
            if (pn == pEnd)
                ux = 1.0 ; // can't go past the end in this case
            else
                pn = pn->next ; 
        }
    }

    return pn->UTangent(ux) ; 
}


// Tangent in forward direction at the point specified
CS_VECTOR CS_Curve::TanVectorForwardsExact(CS_SegPtr pn, double ux, double epsilon)
{
    if (ux > 1.0)
        ux = 1.0 ; 
    if (ux < 0.0)
        ux = 0.0 ; 

    if (tcomp_EQ(ux, 1.0, epsilon))
    {   // Then we are at the exact end point of the curve. So use the tangent
        // of the next segment as the forward direction
        CS_SegPtr pnxt = NextES(pn) ; 
        if (!pnxt)
            return pn->UTangent(1.0) ; 
        return pnxt->UTangent(0.0) ; 
    }
    return pn->UTangent(ux) ; 
}

// Tangent looking backwards on curve at the point specified 
CS_VECTOR CS_Curve::TanVectorBackwards(CS_SegPtr pn, double ux, double epsilon)
{
    ux -= epsilon ; 

    if (tcomp_LT(ux, 0.0))
    {   // Then move to the previous segment
        ux = 1.0 - FBepsilon ; 
        if (statflags & CS_CLOSEDCURVE)
        {   // Then simply shift backwards
            pn = Prev(pn) ; 
        }
        else
        {   // Check if we can or not
            if (pn == pStart)
                ux = 0.0 ; // can't go backwards past start in this case
            else
                pn = pn->prev ; 
        }
    }

    return pn->UTangent(ux) ; 
}

// Tangent looking backwards on curve at the point specified
CS_VECTOR CS_Curve::TanVectorBackwardsExact(CS_SegPtr pn, double ux, double epsilon)
{
    if (ux > 1.0)
        ux = 1.0 ; 
    if (ux < 0.0)
        ux = 0.0 ; 

    if (tcomp_EQ(ux, 0.0, epsilon))
    {   // Then we are at the exact start point of the curve. So use the tangent
        // of the previous segment as the reverse direction tangent
        CS_SegPtr pprv = PrevES(pn) ; 
        if (!pprv)
            return pn->UTangent(0.0) ; 
        return pprv->UTangent(1.0) ; 
    }
    return pn->UTangent(ux) ; 
}



//! Return curve point +/- deltau from cp. deltau w.r.t overall curve. 
CS_CrvPnt CS_Curve::CrvPntDeltaU(CS_CrvPnt &cp, const double &deltau)
{
    CS_CrvPnt cpret ; 
    double ucp = cp.UCrv() ; 
    double ud = UNorm(ucp + deltau) ; 
    double uns ;

    CS_SegPtr pseg ;

    if (ud > ucp)
    {   // Search forward for the new u coord. 
        pseg = cp.s ; 
        uns = NextSegU(pseg) ; 

        while (tcomp_GEQ(ud, uns))
        {
            if (pseg->next)
                pseg = pseg->next ; 
            else 
            {   // Found the point at the very end of the curve
                cpret.s = pseg ; 
                cpret.u = 1.0 ; 
                return cpret ; // done
            }
            uns = NextSegU(pseg) ; 
        }

        // The ud point is on the current pseg segment
    }
    else
    {   // Search backwards for the uc point
        pseg = cp.s ; 
        while (tcomp_LEQ(ud, pseg->uo))
        {
            if (pseg->prev)
                pseg = pseg->prev ; 
            else 
            {   // Found the point at the start of the curve
                cpret.s = pseg ; 
                cpret.u = 0.0 ; 
                return cpret ; // done
            }
        }

        // The ud point is on the current pseg segment
        uns = NextSegU(pseg) ; // make sure u next seg is valid
    }

    double useglen = uns - pseg->uo ; 
    double useg ; 
    if (tcomp_GT(useglen, 0.0))
        useg = (ud - pseg->uo) / (uns - pseg->uo) ; 
    else 
        useg = 0.0 ; // doesn't really matter where on a zero length segment

    cpret.s = pseg ; 
    cpret.u = useg ; 

    return cpret ; 
}



CS_VECTOR CS_Curve::RightBisector(const double &u, double ueps)
{
    CS_VECTOR vtf = UTangent(UNorm(u+ueps)) ; 
    CS_VECTOR vtb = UTangent(UNorm(u-ueps)) ; 

    vtf = vtf.RightPerp() ; 
    vtb = vtb.RightPerp() ; 

    return CS_BisectorVector(vtb, vtf) ; 
}

CS_VECTOR CS_Curve::RightBisector(CS_CrvPnt &cp, double ueps)
{
    CS_CrvPnt cpf = CrvPntDeltaU(cp, ueps) ;
    CS_CrvPnt cpb = CrvPntDeltaU(cp, -ueps) ;
    CS_VECTOR vtf = cpf.s->UTangent(cpf.u) ; 
    CS_VECTOR vtb = cpb.s->UTangent(cpb.u) ; 

    vtf = vtf.RightPerp() ; 
    vtb = vtb.RightPerp() ; 

    return CS_BisectorVector(vtb, vtf) ; 
}

CS_VECTOR CS_Curve::LeftBisector(const double &u, double ueps)
{
    CS_VECTOR vtf = UTangent(UNorm(u+ueps)) ; 
    CS_VECTOR vtb = UTangent(UNorm(u-ueps)) ; 

    vtf = vtf.LeftPerp() ; 
    vtb = vtb.LeftPerp() ; 

    return CS_BisectorVector(vtb, vtf) ; 
}

CS_VECTOR CS_Curve::LeftBisector(CS_CrvPnt &cp, double ueps)
{
    CS_CrvPnt cpf = CrvPntDeltaU(cp, ueps) ;
    CS_CrvPnt cpb = CrvPntDeltaU(cp, -ueps) ;
    CS_VECTOR vtf = cpf.s->UTangent(cpf.u) ; 
    CS_VECTOR vtb = cpb.s->UTangent(cpb.u) ; 

    vtf = vtf.LeftPerp() ; 
    vtb = vtb.LeftPerp() ; 

    return CS_BisectorVector(vtb, vtf) ; 
}


CS_SegPtr CS_Curve::GetAt(int n)
{
    CS_SegPtr pn = pStart ;
    int i = 0 ;
    while (pn)
    {
	if (i == n)
	    return pn ;
	pn = pn->next ;
	i++ ;
    }
    return NULL ; // out of range doesn't exist
}


void CS_Curve::PrintCurve(int endpoints, FILE *fp)
{
    CS_SegPtr pn = pStart ;
    if (!fp)
        return ; 

    CS_DEBUG(fprintf(fp, "Curve has %d nodes, arclen=%.8lf\n",nodecnt,arclength);)
    while (pn)
    {
	if (endpoints)
	{
            if (pn->SegmentType() == CS_Segment::ARC_TYPE)
		fprintf(fp, "A") ;
	    else
		fprintf(fp, "L") ;
	    pn->StartPoint().Print(fp) ;
	    fprintf(fp, " ===> ") ;
	    pn->EndPoint().Print(fp) ;
	    fprintf(fp, "\n") ;
	}
	else
	{
	    pn->Print(fp) ;
	    fprintf(fp, "  uo=%.8lf\n", pn->uo) ;
	}
	pn = pn->next ;
    }
    CS_DEBUG(fprintf(fp,"\n") ;)
}

void CS_Curve::Print(int endpoints, FILE *fp)
{
    CS_SegPtr pn = pStart ;
    if (!fp)
        fp = stdout ; 

    CS_DEBUG(fprintf(fp, "Curve has %d nodes, arclen=%.8lf\n",nodecnt,arclength);)
    while (pn)
    {
	if (endpoints)
	{
            if (pn->SegmentType() == CS_Segment::ARC_TYPE)
		fprintf(fp, "A") ;
	    else
		fprintf(fp, "L") ;
	    pn->StartPoint().Print(fp) ;
	    fprintf(fp, " ===> ") ;
	    pn->EndPoint().Print(fp) ;
	    fprintf(fp, "\n") ;
	}
	else
	{
	    pn->Print(fp) ;
	    fprintf(fp, "  uo=%.8lf\n", pn->uo) ;
	}
	pn = pn->next ;
    }
    CS_DEBUG(fprintf(fp,"\n") ;)
}


//! Returns true if the curve represents a closed boundary.
int CS_Curve::Closed(double *ptol)
{
    statflags &= ~CS_CLOSEDCURVE ;

    if (nodecnt < 1)
	return 0 ;
    // Probably had to do this circle test since the arc endpoint routine didn't
    // return exactly the correct result in some situation. This really shouldn't
    // be requried.
    if (nodecnt == 1)
    {
        if (pStart->SegmentType() == CS_Segment::ARC_TYPE)
	{
	    CS_ArcSeg *pas = (CS_ArcSeg *)pStart ;
	    if (tcomp_EQ(fabs(pas->swp), RADIAN360))
	    {
		statflags |= CS_CLOSEDCURVE ;
		return 1 ;
	    }
	    return 0 ;
	}
    }

    if (ptol)
    {
        if (tcomp_PointsEQ(pStart->UPoint(0.0).p, pEnd->UPoint(1.0).p, *ptol))
        {
	    statflags |= CS_CLOSEDCURVE ;
	    return 1 ;
        }
    }
    else
    {
        if (pStart->UPoint(0.0) == pEnd->UPoint(1.0))
        {
	    statflags |= CS_CLOSEDCURVE ;
	    return 1 ;
        }
    }
    return 0 ;
}


//////////////////////////////////////////////////////////////////
// Return true if point p is physically on the curve, return the
// u value along the curve of this point on the curve. If true is
// returned then pnpnt and p will be equal. If false is returned
// the the point p was not on the curve, and the u value and pnpnt
// returned will be of the point on the curve closest to the point
// p. If puval is NULL, or pnpnt is NULL then their values are
// not returned, and only the status is returned. These values
// since they are calculated in the process of determining if the
// point p is on the curve, are made available if required.
int CS_Curve::PointOnCurve(CS_POINT &p, double *puval, 
                           CS_POINT *pnpnt, CS_SegPtr *pseg, double *puseg)
{
    return PointOnSegment(p, puval, pnpnt, pseg, puseg) ;
}

int CS_Curve::PointOnCurve(CS_POINT &p, CS_CrvPnt &cp, double *puval, 
                           CS_POINT *pnpnt)
{
    return PointOnSegment(p, puval, pnpnt, &cp.s, &cp.u) ;
}


int CS_Curve::PointOnSegment(CS_POINT &p, double *puval, 
                             CS_POINT *pnpnt, CS_SegPtr *pseg, double *puseg)
{
    CS_SegPtr pn = pStart ;
    double dnearest ;
    double uvals[2] ;
    double dist ;
    CS_POINT npnt ;

    dnearest = 9.99e99 ;

    while (pn)
    {
	if (pn->PointOnSegment(p, uvals, &npnt))
	{   // p == npnt in this case
	    // Then the point was physically on the segment so we
	    // can stop the search since we can't get any closer
	    // Calculate the u point at this location
	    if (pnpnt)
		*pnpnt = npnt ;
	    if (puval)
	    {
		*puval = ((arclength * pn->uo) +
			  (uvals[0] * pn->ArcLength())) /
			    arclength ;
	    }
            if (pseg)
                *pseg = pn ; 
            if (puseg)
                *puseg = uvals[0] ; 
	    return 1 ; // return true
	}
	else
	{   // Point wasn't on the segment so do nearest testing
            if (pnpnt || puval || pseg)
            {   // Only do these calculations if we need to return values
                // otherwise we're wasting time
	        CS_VECTOR vdist(p, npnt) ;
                dist = vdist.Mag() ; 
	        if (dist < dnearest)
	        {
                    dnearest = dist ; 
		    if (pnpnt)
		        *pnpnt = npnt ;
		    if (puval)
		    {
		        *puval = ((arclength * pn->uo) +
			          (uvals[0] * pn->ArcLength())) /
				    arclength ;
		    }
                    if (pseg)
                        *pseg = pn ; 
                    if (puseg)
                        *puseg = uvals[0] ; 
	        }
            }
	}
	pn = pn->next ;
    }
    // If we get to here then we've only found the nearest point but the
    // point didn't lie physically on the curve anywhere
    return 0 ;
}


// Returns the length in terms of U of the segment
// range of result = (0,1] (or == 0 if curve psn == NULL)
double CS_Curve::SegmentULength(CS_SegPtr psn)
{
    if (!psn)
        return 0 ; 

    if (psn->next == 0)
    {   // Then this is the last segment thus the length is 
        // 1-ustart
        return 1.0 - psn->uo ; 
    }

    return psn->next->uo - psn->uo ; 
}

double CS_Curve::ULength(const double &ua, const double &ub)
{
    if (statflags & CS_CLOSEDCURVE)
    {   // Closed curve
        if (tcomp_LT(ua, ub))
        {   // Normal operation
            return ub - ua ; 
        }
        else if (tcomp_EQ(ua, ub))
        {   // Full loop
            return 1.0 ; 
        }
        else
        {   // Wraps past the start
            return 1.0 - ua + ub ; 
        }
    }
    else
    {   // Open curve
        if (tcomp_LT(ua, ub))
        {   // Normal operation
            return ub - ua ; 
        }
        else if (tcomp_EQ(ua, ub))
        {   // zero length
            return 0.0 ; 
        }
        else
        {   // Attempt to go past the end of the curve
            return 1.0 - ua ; 
        }
    }
    assert(0) ; // can't get here
}

double CS_Curve::ULength(const CS_CrvPnt &cpfrom, const CS_CrvPnt &cpto)
{
    double ulen = 0.0 ; 
    CS_CrvPnt cplast = cpfrom ; 
    // Take first step so we only have to test end condition

    if (cplast.s == cpto.s)
    {
        if (tcomp_LEQ(cplast.u, cpto.u))
        {
            ulen += (cplast.s->ArcLength() / arclength) * (cpto.u - cplast.u) ; 
            return ulen ; 
        }
    }

    ulen = (cplast.s->ArcLength() / arclength) * (1.0 - cplast.u) ; 
    cplast.s = Next(cplast.s) ; 
    cplast.u = 0.0 ; 

    do {
        if (cplast.s == cpto.s)
        {
            if (tcomp_LT(cplast.u, cpto.u))
                ulen += (cplast.s->ArcLength() / arclength) * (cpto.u - cplast.u) ; 
            return ulen ; 
        }

        // Always adding a full segment here
        ulen += (cplast.s->ArcLength() / arclength) ; 
        cplast.s = Next(cplast.s) ; 
        cplast.u = 0.0 ; 
    } while (1) ; 
}


double CS_Curve::SegU2CrvU(CS_SegPtr pseg, double useg) 
{
    return pseg->uo + useg * pseg->ArcLength() / arclength ; 
}

double CS_Curve::SegU2CrvU(CS_CrvPnt &cp)
{
    return cp.s->uo + cp.u * cp.s->ArcLength() / arclength ; 
}

double CS_Curve::UNorm(double utst) 
{
    if (utst < 0.0) 
    {
        if (Closed()) 
        {
            double uint ; 
            double frac = modf(utst, &uint) ;
            return (1.0 + frac) ; // since frac is negative number
        }
        else
        {
            return 0.0 ; 
        }
    }
    else if (utst > 1.0)
    {
        if (Closed())
        {
            double uint ; 
            double frac = modf(utst, &uint) ;
            return frac ; // since frac is positive number
        }
        else
        {
            return 1.0 ; 
        }
    }
    // Else it's in range already so return it. 
    return utst ; 
}


// Re-calculate the uo parameters for each segment node
// TO DO - make this is automatic as part of the Append, Insert, InsertAfter
//	    and any delete node operations
void CS_Curve::SetUParameters()
{
    CS_SegPtr pn ;
    double alen = 0, ucur ;
    pn = pStart ;

    if (tcomp_EQZ(arclength) || !(statflags & CS_ARCLENGTH_VALID))
    {
        CalcArcLength() ; 
        if (tcomp_EQZ(arclength))
            return ; // nothing to do because we have a zero length curve
    }

    nodecnt = 0 ; 
    ucur = 0.0 ;
    while (pn)
    {
	pn->uo = ucur ;
        pn->cnt = nodecnt++ ; 
	alen += pn->ArcLength() ;
	ucur = alen / arclength ;
	pn = pn->next ;
    }

    statflags |= CS_ARCLENGTH_VALID | CS_UVALUE_VALID | CS_NODECNT_VALID ;
}

void CS_Curve::Finalize()
{
    CalcArcLength() ; 
    SetUParameters() ; 
    Closed() ; 
}




void CS_Curve::Transform(CS_MTX4 &mx)
{
    CS_SegPtr pn = pStart ;
    while (pn)
    {
	pn->Transform(mx.m) ;
	pn = pn->next ;
    }
}

void CS_Curve::MTX3Mult(CS_MTX3 &m)
{
    CS_SegPtr pn = pStart ;
    while (pn)
    {
	pn->MTX3Mult(m) ;
	pn = pn->next ;
    }
}

void CS_Curve::Mirror(CS_LINE &mirrorline)
{
    // TO DO 
}

void CS_Curve::Scale(double s)
{
    CS_SegPtr pn = pStart ;
    while (pn)
    {
	pn->Scale(s) ;
	pn = pn->next ;
    }
}

void CS_Curve::Move(CS_VECTOR &v)
{
    CS_SegPtr pn ;
    pn = pStart ;
    while(pn)
    {
	pn->Move(v) ;
	pn = pn->next ;
    }
}

void CS_Curve::SetZ(double z)
{
    CS_SegPtr pn = pStart ; 
    while (pn)
    {
        pn->SetZ(z) ; 
        pn = pn->next ; 
    }
}

void CS_Curve::ResetNextPoint()
{
    statflags |= CS_NEXTSTART ; 
    psegnext = pStart ; 
}


CS_POINT CS_Curve::StartPoint()
{
    statflags &= ~CS_NEXTSTART ; // reset next start CS_NEXTEND
    if (pStart)
    {
        psegnext = pStart ; 
	return pStart->StartPoint() ;
    }
    psegnext = 0 ; 
    return CS_POINT(0,0,0) ;
}

CS_SegPtr CS_Curve::NextPoint(CS_POINT &p)
{
    if (psegnext)
    {
        if (statflags & CS_NEXTSTART)
        {
            p = psegnext->StartPoint() ; 
            statflags &= ~CS_NEXTSTART ; // reset next start
        }
        else
        {
            p = psegnext->EndPoint() ;
            psegnext = psegnext->next ; 
        }
    }
    else
    {
        statflags &= ~CS_NEXTSTART ; 
    }
    return psegnext ; 
}


CS_POINT CS_Curve::EndPoint()
{
    if (pEnd)
	return pEnd->EndPoint() ;
    return CS_POINT(0,0,0) ;
}


// Friend functions for CS_Curve

int CS_SameCurveUPoints(CS_Curve *pcrv, double u1, double u2, double *tol) 
{
    if (tol)
    {
        if (tcomp_EQ(u1, u2, *tol))
            return 1 ; 
        if (pcrv->Closed() &&
                ((tcomp_EQZ(u1, *tol) && tcomp_EQ(u2, 1.0, *tol)) ||
                (tcomp_EQ(u1, 1.0, *tol) && tcomp_EQZ(u2, *tol)))
        )
        {   // Then closed curve and the end point matches the start point
            return 1 ; 
        }
    }
    else
    {
        if (tcomp_EQ(u1, u2))
            return 1 ; 
        if (pcrv->Closed() &&
                ((tcomp_EQZ(u1) && tcomp_EQ(u2, 1.0)) ||
                (tcomp_EQ(u1, 1.0) && tcomp_EQZ(u2)))
        )
        {   // Then closed curve and the end point matches the start point
            return 1 ; 
        }
    }

    return 0 ; 
}


//! Closest segment end point on the pcrv to the given cp point
/*!

*/
CS_CrvPnt CS_ClosestEndPoint(CS_Curve *pcrv, CS_POINT &pnt) 
{
    CS_CrvPnt cp ; 
    double u ; 
    CS_POINT p ; 

    pcrv->PointOnCurve(pnt, &u, &p, &cp.s, &cp.u) ; 

    CS_CrvPnt cpret ; 
    if (cp.u >= 0.5)
    {
        if (cp.s->next)
        {
            cpret.s = cp.s->next ; 
            cpret.u = 0.0 ; 
        }
        else
        {
            cpret.s = cp.s ; 
            cpret.u = 1.0 ; 
        }
    }
    else
    {
        cpret.s = cp.s ; 
        cpret.u = 0.0 ; 
    }

    return cpret ; 
}

//! Closest segment end point on the pcrv to the given u point on the curve
CS_CrvPnt CS_ClosestEndPoint(CS_Curve *pcrv, double ucrv) 
{
    CS_CrvPnt cp = pcrv->UCrvPnt(ucrv) ; 

    CS_CrvPnt cpret ; 
    if (cp.u >= 0.5)
    {
        if (cp.s->next)
        {
            cpret.s = cp.s->next ; 
            cpret.u = 0.0 ; 
        }
        else
        {
            cpret.s = cp.s ; 
            cpret.u = 1.0 ; 
        }
    }
    else
    {
        cpret.s = cp.s ; 
        cpret.u = 0.0 ; 
    }

    return cpret ; 
}


double CS_UCrvDelta(double us, double ue)
{
    if (us > ue)
        return 1.0 - us + ue ; 
    return ue - us ; 
}


double CS_CrvULen2SegULen(double ulen, CS_Curve &crv, CS_SegPtr &pseg) 
{
    return ulen * crv.arclength/ pseg->ArcLength() ; 
}

int UOnSection(double u, double ua, double ub, int isClosed) 
{   // TODO optimize the Closed() testing so that it just tests
    // the status bit. 
    if (ua < ub)
    {
        if (tcomp_GEQ(u, ua) && tcomp_LEQ(u, ub))
            return 1 ; 
        return 0 ; 
    }
    else
    {
        if (isClosed)
        {
            if (tcomp_GEQ(u, ua) || tcomp_LEQ(u, ub))
                return 1 ; 
            return 0 ; 
        }
    }
    return 0 ; 
}


int UInSection(double u, double ua, double ub, int isClosed)
{   // TODO optimize the Closed() testing so that it just tests
    // the status bit. 
    if (ua < ub)
    {
        if (tcomp_GT(u, ua) && tcomp_LT(u, ub))
            return 1 ; 
        return 0 ; 
    }
    else
    {
        if (isClosed)
        {
            if (tcomp_GT(u, ua) || tcomp_LT(u, ub))
                return 1 ; 
            return 0 ; 
        }
    }
    return 0 ; 
}

