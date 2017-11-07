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
// clipping.cpp

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_cadfuncs.h"

int LineSegInsideRect(CS_RECT &rect, CS_LineSeg &lseg)
{
    // See if the segment is completely inside the rectangles
    if ((tcomp_GEQ(lseg.sp.x, rect.l) && tcomp_LEQ(lseg.ep.x, rect.r)) && 
        (tcomp_GEQ(lseg.sp.y, rect.b) && tcomp_LEQ(lseg.sp.y, rect.t)) && 
        (tcomp_GEQ(lseg.ep.y, rect.b) && tcomp_LEQ(lseg.ep.y, rect.t)))
    {   // The line is completely inside the rectangle return entire segment
        return 1 ; 
    }
    return 0 ; 
}

int LineSegOutSideRect(CS_RECT &rect, CS_LineSeg &lseg)
{
    if ((tcomp_LEQ(lseg.ep.x, rect.l) || tcomp_GEQ(lseg.sp.x, rect.r)) || 
        (tcomp_LEQ(lseg.sp.y, rect.b) && tcomp_LEQ(lseg.ep.y, rect.b)) || 
        (tcomp_GEQ(lseg.sp.y, rect.t) && tcomp_GEQ(lseg.ep.y, rect.t)))
    {   // The line is completely outside the rectangle, result is nothing
        return 1 ; 
    }
    return 0 ; 
}

// Only the XY plane is considered here
int CS_ClipLineToRect(CS_RECT &rect, CS_LineSeg *ps, CS_SegmentList &seglist) 
{
    // The line case is simple since we only have to work out 
    // absolute differences
    int retcount = 0 ; 
    CS_LineSeg lseg(*ps) ; 
    // Orient it so that goes from left to right to simplify the logic
    int reversed = 0 ; 
    if (lseg.sp.x > lseg.ep.x)
    {
        lseg.Reverse() ; 
        reversed = 1 ; 
    }

    if (LineSegOutSideRect(rect, lseg))
    {   // Then outside so nothing to do.
        return 0 ; 
    }

    // See if the segment is completely inside the rectangles
    if (LineSegInsideRect(rect, lseg))
    {   // The line is completely inside the rectangle return entire segment
        CS_LineSeg *pls = (CS_LineSeg *)lseg.Copy() ; 
        seglist.AddSegment(pls) ; 
        return 1 ; 
    }

    // Gets messy in this case

    //////////////////////////////////////////////////////////////////////
    // Test left vertical wall of rectangle
    CS_LineSeg ls(CS_POINT(rect.l, rect.b, 0), CS_POINT(rect.l, rect.t, 0)) ; 
    int nisects ; 
    double uva[2] ; 
    double uvb[2] ; 
    
    nisects = ls.Intersect2D(lseg, uva, uvb) ;
    if (nisects == 1) 
    {   // Then split the segment
        if (tcomp_NEZ(uvb[0]) && tcomp_NEQ(uvb[0], 1.0))
        {   // Intersection occured at somewhere other than an end point
            CS_LineSeg *lsc ; 
            lsc = (CS_LineSeg *)lseg.Copy(uvb[0], 1.0) ; 
            CS_ClipLineToRect(rect, lsc, seglist) ; 
            delete lsc ; 
            return seglist.nseg ;
        }
    }
    else if (nisects == 2)
    {   // We have an overlap, in which case throw everything out
        return 0 ; 
    }

    // No intersections, keep trying
    // Test the right vertical wall 
    ls.sp.x = rect.r ;
    ls.ep.x = rect.r ; 

    nisects = ls.Intersect2D(lseg, uva, uvb) ;
    if (nisects == 1) 
    {   // Then split the segment
        if (tcomp_NEZ(uvb[0]) && tcomp_NEQ(uvb[0], 1.0))
        {   // Intersection occured at somewhere other than an end point
            CS_LineSeg *lsc ; 
            lsc = (CS_LineSeg *)lseg.Copy(0.0, uvb[0]) ; 
            retcount = CS_ClipLineToRect(rect, lsc, seglist) ; 
            delete lsc ; 
            return seglist.nseg  ;
        }
    }
    else if (nisects == 2)
    {   // We have an overlap, in which case throw everything out
        return 0 ; 
    }

    // No intersections, keep trying
    // Now test the horizontal segments, orient the curve up
    if (lseg.sp.y > lseg.ep.y)
    {
        lseg.Reverse() ; 
        reversed ^= 0x01 ; // toggle reversed state
    }

    // Test the bottom boundary 1st
    ls.sp.x = rect.l ;
    ls.sp.y = rect.b ; 

    ls.ep.x = rect.r ; 
    ls.ep.y = rect.b ; 

    nisects = ls.Intersect2D(lseg, uva, uvb) ;
    if (nisects == 1) 
    {   // Then split the segment
        CS_LineSeg *lsc ; 
        if (tcomp_NEZ(uvb[0]) && tcomp_NEQ(uvb[0], 1.0))
        {   // Intersection occured at somewhere other than an end point
            lsc = (CS_LineSeg *)lseg.Copy(uvb[0], 1.0) ; 
            // Note we know this curve doesn't touch the left or right
            // sides but it might go through the top of the rect
            // so keep testing
            retcount = CS_ClipLineToRect(rect, lsc, seglist) ; 
            delete lsc ; 
            return seglist.nseg ;
        }
    }
    else if (nisects == 2)
    {   // We have an overlap, in which case throw everything out
        return 0 ; 
    }


    // Test the top boundary 1st
    ls.sp.y = rect.t ; 
    ls.ep.x = rect.t ; 

    nisects = ls.Intersect2D(lseg, uva, uvb) ;
    if (nisects == 1) 
    {   // Then split the segment
        if (tcomp_NEZ(uvb[0]) && tcomp_NEQ(uvb[0], 1.0))
        {   // Intersection occured at somewhere other than an end point
            CS_LineSeg *lsc ; 
            lsc = (CS_LineSeg *)lseg.Copy(0.0, uvb[0]) ; 
            // Note we know this curve doesn't touch the left, right, 
            // or the bottom boundaries, this it is safe to terminate
            // at this point
            seglist.AddSegment(lsc) ; 
            return seglist.nseg ;
        }
    }
    else if (nisects == 2)
    {   // We have an overlap, in which case throw everything out
        return 0 ; 
    }

    return 0 ; 
}

int CS_ClipArcToRect(CS_RECT &rect, CS_ArcSeg *pas, CS_SegmentList &seglist) 
{
    // Here we follow a different approach. Create a curve representing the
    // rectangular box. Then intersect the arc with the box. Then split the
    // arc up where ever there's an intersection. Then extract each curve
    // section that is inside the box.

    CS_Curve box ; 
    CS_LineSeg *pls ; 
    pls = new CS_LineSeg(CS_POINT(rect.l, rect.b, 0), 
                         CS_POINT(rect.r, rect.b, 0)) ; 
    box.Append(pls) ; 
    pls = new CS_LineSeg(CS_POINT(rect.r, rect.b, 0), 
                         CS_POINT(rect.r, rect.t, 0)) ; 
    box.Append(pls) ; 
    pls = new CS_LineSeg(CS_POINT(rect.r, rect.t, 0), 
                         CS_POINT(rect.l, rect.t, 0)) ; 
    box.Append(pls) ; 
    pls = new CS_LineSeg(CS_POINT(rect.r, rect.t, 0), 
                         CS_POINT(rect.r, rect.b, 0)) ; 
    box.Append(pls) ; 


    // CS_IntersectSet isectset ;
    pas->pParent = 0 ; 
    
    CS_IRECList islist ; 
    box.Intersect2D(pas, &islist) ; 
    CS_SortIntersectSetByUValue(islist, 1) ; 
    // 1= do secondary sort on the B segment data (the *pas arc in this case)
    // which is why it's parent pointer is set to NULL before we start

    CS_DeleteCommonIntersectionPoints(islist) ; 

    if (islist.size() == 0)
    {
        if (box.PointInside(pas->StartPoint()))
        {
            CS_ArcSeg *parc = (CS_ArcSeg *)pas->Copy() ; 
            seglist.AddSegment(parc) ; 
            return seglist.nseg ; 
        }
        return 0 ; 
    }

    CS_IRECListItr iri ; 
    // Want to extract all arc sections
    double upnt = 0.0 ; // start at the start of the arc
    for (iri = islist.begin(); iri != islist.end(); iri++)
    {
        CS_IREC *pisr = iri->pir ; 
        if (tcomp_EQ(upnt, pisr->cps[0].u))
        {   // This can happen at the start and end of the curve
            continue ; 
        }

        CS_ArcSeg *parc = (CS_ArcSeg *)pas->Copy(upnt, pisr->cps[0].u) ; 
        if (box.PointInside(parc->MidPoint()))
        {   // Add the arc to the clipping return set
            seglist.AddSegment(parc) ; 
        }
        else
            delete parc ; 
        upnt = pisr->cps[0].u ; 
    }


    // Split the arc up into multiple sections

    return seglist.nseg ; 
}

int CS_ClipToRect(CS_RECT &rect, CS_SegPtr pseg, CS_SegmentList &seglist) 
{
    if (pseg->SegmentType() == CS_Segment::LINE_TYPE)
        CS_ClipLineToRect(rect, (CS_LineSeg *)pseg, seglist) ; 
    else if (pseg->SegmentType() == CS_Segment::ARC_TYPE)
        CS_ClipArcToRect(rect, (CS_ArcSeg *)pseg, seglist) ; 

    return 0 ; 
}
