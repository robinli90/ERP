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
// circtan.cpp - tangent lines to circles

#include <math.h>
#include "cs_shapes.h"
#include "cs_curves.h"


// Returns the number of tangents that were created. 
// tanl1 is set to the first tangent line if any and tanl2
// is set to the second tangent line if any.
// See Geom Algo RR-Vol 3 pg 87 for notes
int CS_PointCircleTangent(CS_POINT &pnt, CS_ArcSeg &arc, 
                          CS_LineSeg &tanl1, CS_LineSeg &tanl2)
{
    CS_CIRCLE circ(arc) ; 
    return CS_PointCircleTangent(pnt, circ, tanl1, tanl2) ; 
}


int CS_PointCircleTangent(CS_POINT &pnt, CS_CIRCLE &circ, 
                          CS_LineSeg &tanl1, CS_LineSeg &tanl2)
{
    CS_VECTOR vcp(circ.ctr, pnt) ; 
    double vcpmag = vcp.Mag() ; 
    if (tcomp_LT(vcpmag, circ.rad))
        return 0 ; // point inside circle, thus no tangent result possible
    if (tcomp_EQ(vcpmag, circ.rad))
    {   // Then the point is on the circle and there is a single 
        // tangent line. Create a line that extends one unit in 
        // either direction of the tangency point.
        CS_VECTOR vrp = vcp.Unit().RightPerp() ; 
        tanl1 = CS_LineSeg(pnt, pnt - vrp) ; 
        // Changed Oct 16, 2002
        // tanl1 = CS_LineSeg(pnt + vrp, pnt - vrp) ; 
        return 1 ; 
    }
    double alpha = acos(circ.rad / vcpmag) ; 
    CS_VECTOR vca = vcp.Unit() ; 
    CS_VECTOR vcb = vca ; 

    vca.Rotate(alpha) ; 
    vcb.Rotate(-alpha) ; 

    tanl1 = CS_LineSeg(pnt, circ.ctr + (vca * circ.rad)) ;
    tanl2 = CS_LineSeg(pnt, circ.ctr + (vcb * circ.rad)) ;

    return 2 ; 
}


int CS_PointCircleTangent(CS_POINT &pnt, CS_CIRCLE &circ, 
                          CS_POINT &tp1, CS_POINT &tp2)
{
    CS_VECTOR vcp(circ.ctr, pnt) ; 
    double vcpmag = vcp.Mag() ;
    if (tcomp_LT(vcpmag, circ.rad))
        return 0 ; // point inside circle, thus no tangent result possible
    if (tcomp_EQ(vcpmag, circ.rad))
    {   // Then the point is on the circle and there is a single 
        // tangent line. Create a line that extends one unit in
        // either direction of the tangency point.
        CS_VECTOR vrp = vcp.Unit().RightPerp() ;
        tp1 = pnt ;
        tp2 = pnt - vrp ;
        // Changed Oct 16, 2002
        // tanl1 = CS_LineSeg(pnt + vrp, pnt - vrp) ;
        return 1 ;
    }
    double alpha = acos(circ.rad / vcpmag) ;
    CS_VECTOR vca = vcp.Unit() ;
    CS_VECTOR vcb = vca ;

    vca.Rotate(alpha) ;
    vcb.Rotate(-alpha) ;

    tp1 = circ.ctr + (vca * circ.rad) ;
    tp2 = circ.ctr + (vcb * circ.rad) ;

    return 2 ;
}


// Returns the number of tangents generated, which will be 
// either 0,2,3, or 4. A result with 1 tangent line will 
// never occur. plns must point to an array of 4 lines
// See notes Geom Algo RR-Vol3 pg 84-85

int CS_CircleCircleTangent(CS_ArcSeg &arc0, CS_ArcSeg &arc1, CS_LineSeg *plns) 
{
    return CS_CircleCircleTangent(CS_CIRCLE(arc0), CS_CIRCLE(arc1), plns) ; 
}

int CS_CircleCircleTangent(CS_CIRCLE &cir0, CS_CIRCLE &cir1, CS_LineSeg *plns) 
{
    if (cir0.ctr == cir1.ctr)
        return 0 ; 

    CS_CIRCLE *pc0, *pc1 ; 
    // Want circle 0 to have the larger of the 2 rads
    bool swapped = false ; 

    if (cir0.rad > cir1.rad)
    {   // Set pointers normally
        pc0 = &cir0 ; 
        pc1 = &cir1 ;
    }
    else
    {   // else swap
        pc1 = &cir0 ; 
        pc0 = &cir1 ;
        swapped = true ; 
    }

    CS_VECTOR vc01(pc0->ctr, pc1->ctr) ; 
    double vc01mag = vc01.Mag() ; 
    if (tcomp_LT(vc01mag, pc0->rad - pc1->rad))
    {   // Then one circle is inside the other and no solution exists
        return 0 ; 
    }

    if (tcomp_EQ(vc01mag, pc0->rad - pc1->rad))
    {   // Then the two circles touch at a point, and one is inside
        // the other (See diagram RR-Vol3 pg 88)
        CS_VECTOR vcu = vc01.Unit() ; 
        CS_POINT p = pc0->ctr + (vcu * pc0->rad) ;  
        plns[0] = CS_LineSeg(p, p + vcu.RightPerp()) ; 
        return 1 ; 
    }

    int tangentcount ; 
    double alpha ;

    CS_VECTOR vcl, vcr, vcu ;
    
    if (tcomp_EQ(cir0.rad, cir1.rad))
    {   // Then we can't use the triangle formulas since the tangent
        // lines are parallel and don't form any triangle.
        // Simply take right and left perp vectors
        alpha = RADIAN90 ; 
    }
    else
    {   // Use triangle forumlas
        alpha = acos((pc0->rad - pc1->rad) / vc01mag) ; 
    }

    vcu = vc01.Unit() ; 
    vcl = vcu ; 
    vcr = vcu ; 

    vcl.Rotate(alpha) ; 
    vcr.Rotate(-alpha) ; 

    // Generate the 2 solutions that we know to exist for sure
    plns[0] = CS_LineSeg(pc0->ctr + (vcl * pc0->rad), pc1->ctr + (vcl * pc1->rad)) ;
    plns[1] = CS_LineSeg(pc0->ctr + (vcr * pc0->rad), pc1->ctr + (vcr * pc1->rad)) ;

    tangentcount = 2 ; 


    if (tcomp_EQ(vc01mag, pc0->rad + pc1->rad))
    {   // Then the two circles are touching each other and we end up 
        // with 3 tangent lines
        CS_VECTOR vlp(vcu.LeftPerp()) ; 
        CS_POINT p(pc0->ctr + (vcu * pc0->rad)) ; 
        plns[2] = CS_LineSeg(p, p + vlp) ; 
        tangentcount += 1 ; 
    }
    else if (tcomp_GT(vc01mag, pc0->rad + pc1->rad))
    {   // Then we have 2 more tangent lines to define
        // See notes RR-Vol3 pg 89
        double t = vc01mag / (1.0 + (pc0->rad / pc1->rad)) ;
        alpha = acos(pc1->rad / t) ; 

        vcl = vcu ; 
        vcr = vcu ; 

        vcl.Rotate(alpha) ; 
        vcr.Rotate(-alpha) ; 

        plns[2] = CS_LineSeg(pc0->ctr + (vcl * pc0->rad), pc1->ctr - (vcl * pc1->rad)) ;
        plns[3] = CS_LineSeg(pc0->ctr + (vcr * pc0->rad), pc1->ctr - (vcr * pc1->rad)) ;

        tangentcount += 2 ; 
    }

    if (swapped)
    {   // Then flip the tangent lines around
        for (int i=0; i < tangentcount; i++)
            plns[i].Reverse() ; 
    }

    return tangentcount ; 
}


int CS_PointArcTangent(CS_POINT &pnt, CS_ArcSeg &arc, CS_LINE tlns[])
{
    CS_POINT  tp1, tp2 ; 

    int retcount = 0 ; 
    int ntans = CS_PointCircleTangent(pnt, CS_CIRCLE(arc), tp1, tp2) ;
    switch (ntans)
    {
        case 0 :
            return 0 ; // nothing to do
        case 1 :
            // See if the point is on the arc.
            if (arc.PointOnArc(tp1))
            {
                tlns[0].sp = tp1 ; 
                tlns[0].ep = tp2 ; 
                return 1 ; 
            }
            return 0 ; 
            break ; 
        case 2:
            int retcount = 0 ; 
            if (arc.PointOnArc(tp1))
            {
                tlns[retcount].sp = pnt ; 
                tlns[retcount].ep = tp1 ; 
                retcount++ ; 
            }

            if (arc.PointOnArc(tp2))
            {
                tlns[retcount].sp = pnt ; 
                tlns[retcount].ep = tp2 ; 
                retcount++ ; 
            }
            return retcount ; 
    }
    return 0 ; // something went wrong, shouldn't get to here.
}

int CS_CurveTangents(CS_Curve &crv, CS_POINT &tpnt, CS_LINE &tln1, CS_LINE &tln2)
{
    if (crv.PointInside(tpnt))
        return 0 ; 

    CS_LineSeg *ptls = new CS_LineSeg[(crv.nodecnt + 1) * 2] ; 
    CS_SegPtr *ptsegs = new CS_SegPtr[(crv.nodecnt + 1) * 2] ;
    CS_LINE tlns[2] ; 
    crv.SetBoundingRect() ; 
    // Get max dimensions
    double maxdim = sqrt(crv.bndrect.Width() * crv.bndrect.Width() + 
                         crv.bndrect.Height() *crv.bndrect.Height()) * 2.0 ; 

    int ntans = 0 ; 
    CS_SegPtr ps = crv.pStart ; 
    // Generate a set of all possible tangents
    while (ps)
    {
        // The only way a line segment can be tangent to the point is if the 
        // point is actually on the line itself. 
        if (ps->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_LineSeg *pls = (CS_LineSeg *)ps ; 
            tlns[0] = CS_LINE(*pls) ; 
            if (tlns[0].PointOnLine(tpnt))
            {   // Then the point forms a tangent with this line segment
                // Add it to the test set
                ptsegs[ntans] = ps ; 
                // Extend the line so that it will intersect the shape
                // when the final testing is done.
                CS_VECTOR v(tlns[0].sp, tlns[0].ep) ; 
                v = v.Unit() ; 
                tlns[0].sp = tlns[0].sp - v * maxdim ; 
                tlns[0].ep = tlns[0].ep + v * maxdim ; 
                ptls[ntans] = CS_LineSeg(tlns[0]) ; 

                ntans++ ; 
            }
        }
        else if (ps->SegmentType() == CS_Segment::ARC_TYPE)
        {   // Test the arc case
            CS_ArcSeg *pas = (CS_ArcSeg *)ps ; 
                

            int tcnt = CS_PointArcTangent(tpnt, *pas, tlns) ;
            for (int i=0; i < tcnt; i++)
            {
                ptsegs[ntans] = ps ; 
                // Extend the line so that it will intersect the shape
                // when the final testing is done.
                CS_VECTOR v(tlns[i].sp, tlns[i].ep) ; 
                v = v.Unit() ; 
                tlns[i].sp = tlns[i].sp - v * maxdim ; 
                tlns[i].ep = tlns[i].ep + v * maxdim ; 
                ptls[ntans] = CS_LineSeg(tlns[i]) ; 
                ntans++ ; 
            }
        }
        ps = ps->next ; 
    }

    // Now filter out all the extraneous invalid tangency lines, these 
    // will all intersect the shape at more than one point other than
    // the tangency point.
    int tanrescount = 0 ; 
    for (int i=0; i < ntans; i++)
    {
        CS_IRECList isl ; 
        crv.Intersect2D(&ptls[i], &isl) ; 
        CS_DeleteCommonIntersections(isl) ;
        
        if (isl.size() == 1)
        {   // This is a tangent since it intersects at a single 
            // point on the curve
            if (tanrescount == 0)
            {
                tln1 = ptls[i] ; 
                tanrescount++ ; 
            }
            else 
            {
                tln2 = ptls[i] ; 
                tanrescount++ ; 
                break ; // done, found the two tangent lines
            }
            
        }
    }

    delete[] ptsegs ; 
    delete[] ptls ; 

    return tanrescount ; 
}
