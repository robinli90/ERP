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
// shapes.h - class definitions for general shapes processing



#ifndef __CS_SHAPES_H__

#define __CS_SHAPES_H__

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"


#define INFINITE_MODE   1
#define SEGMENT_MODE    2



// General functions
int IntersectLineAndCircle2D(CS_LINE &ln, CS_CIRCLE &cir, 
                             CS_POINT &p1, CS_POINT &p2) ;


//////////////////////////////////////////////////////////
// Simple line testing routines
#define CS_LEFTSIDE         -1
#define CS_RIGHTSIDE         1
#define CS_BOTHSIDES         0   
#define CS_COLLINEAR         0
#define CS_PARALLEL          2
#define CS_NONCOLLINEAR      3

//! Returns one of CS_LEFTSIDE, CS_RIGHTSIDE, CS_COLLINEAR
/*!
    \param l line to test against
    \param p point to test 
    \return the side of the line that the point is on

    The vectors l.sp->p and p->l.ep are generated and a cross product taken. 
    If the z component of the cross product is less than zero then CS_LEFTSIDE
    is returned, and similarily if the z component is greater than zero 
    CS_RIGHTSIDE is returned. No tolerance is used in this comparison. 
    If the z component of the cross product is exactly zero then the function
    returns CS_COLLINEAR. 
 */
int PointSide(CS_LINE &l, CS_POINT &p) ;


//! Returns true if all 3 points are on the same line
/*!
    \param pa first test point
    \param pb second test point
    \param pc third test point
    \return true if all points are in a line

    Takes the z component of the cross product of the vectors pa->pb and 
    pb->pc. If the z component is zero within the current tolerance limit
    setting, then true (1) is returned, otherwise false (0) is returned. 
    If you want to have an exact collinear test you could use the PointSide()
    function which only returns CS_COLLINEAR if the z component of the 
    cross product is exactly zero (within the floating point precision of
    a double). 
 */
int CS_Collinear(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc) ; 


//! lines AB to BC make a left turn 
/*!
    \param pa first input point (start of 1st line)
    \param pb second input point (end of 1st, start of 2nd line)
    \param pc third input point (end of 2nd line)
    \return 1 if the points define a left turn, 0 otherwise. If the 
    two lines are collinear then true will be returned. 
 */
int PointsTurnLeft(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc) ; 

//! lines AB to BC make a right turn 
/*!
    \param pa first input point (start of 1st line)
    \param pb second input point (end of 1st, start of 2nd line)
    \param pc third input point (end of 2nd line)
    \return 1 if the points define a right turn, 0 otherwise. If the 
    two lines are collinear then true will be returned. 
 */
int PointsTurnRight(CS_POINT &pa, CS_POINT &pb, CS_POINT &pc) ; 

//! Returns the lines tangent to the circle passing through the point
/*! 
    \param pnt Input point for tangency test
    \param circ Input circle for tangency test
    \param tanl1 First tangent line if defined
    \param tanl2 Second tangent line if defined
    \return The number of tangent lines defined, {0,1,2}.

    If a tangent is defined, then the pnt passed in will be 
    the tanl1.sp and/or tanl2.sp. The end point of the line(s) will
    be the tangency point on the circle. If the point is outside the 
    circle then two tangents will be returned. If the point is on the 
    circle then one tangent is returned, and the second point of the 
    line in this case is 1 unit away from the point of tangency in 
    the CCW direction of the circle. Points inside the circle 
    return no tangents.
 */
int CS_PointCircleTangent(CS_POINT &pnt, CS_CIRCLE &circ, 
                          CS_LineSeg &tanl1, CS_LineSeg &tanl2) ;

//! Returns the lines tangent to the circle passing through the point
/*! 
    \param pnt Input point for tangency test
    \param arc Input arc (which defines the circle) for tangency test
    \param tanl1 First tangent line if defined
    \param tanl2 Second tangent line if defined
    \return The number of tangent lines defined, {0,1,2}.

    Arc is converted to circle and then does
    return CS_PointCircleTangent(pnt, circ, tanl1, tanl2).
 */
int CS_PointCircleTangent(CS_POINT &pnt, CS_ArcSeg &arc, 
                           CS_LineSeg &tanl1, CS_LineSeg &tanl2) ;

//! Returns the lines tangent to the circle passing through the point
/*! 
    \param pnt Input point for tangency test
    \param circ Input circle for tangency test
    \param tp1 First tangent point on the circle defined
    \param tp2 Second tangent point on the cirle if defined
    \return The number of tangent points defined, {0,1,2}.

    To generate the tangency lines simply form lines from the
    input point to the points returned. If 1 is returned, then 
    the tangent point on the circle is set to tp1 (tp1=pnt)
    and tp2 is set to a point one unit distance away from tp1
    tangent to the circle in the left perpendicular direction
    relative to the circle ctr->tp1 vector.
    If 2 is returned, then tp1 and tp2 are set to the two
    tangency points on the circle. 
 */
int CS_PointCircleTangent(CS_POINT &pnt, CS_CIRCLE &circ, 
                          CS_POINT &tp1, CS_POINT &tp2) ;

//! Returns the lines tangent to the circle passing through the point
/*! 
    \param cir0 1st input circle for tangency testing 
    \param cir1 2nd input circle for tangency testing 
    \param lns Must point to CS_LineSeg[4] array to accept tangent lines
    \return The number of tangent lines defined, {0,..,4}.

    The tangent line end points are the tangent points where the lines touch 
    the two circles. The start point of the line the tangency point on 
    cir0 and the end point is the tangency point on cir1. If the two 
    circles touch at a single point then three tangent lines are returned
    and the tangent line passing through the contact point (which 
    separates the two circles) starts at the contact point and ends
    one unit away in the CCW direction tangent vector of the first
    circle (cir0). If one circle is completely inside the other, or
    the circles have the same centers, then no tangents are returned.
 */
int CS_CircleCircleTangent(CS_CIRCLE &cir0, CS_CIRCLE &cir1, CS_LineSeg lns[]) ;

//! Returns the lines tangent to the circle passing through the point
/*! 
    \param arc0 1st input arc for tangency testing 
    \param arc1 2nd input arc for tangency testing 
    \param lns Must point to CS_LineSeg[4] array to accept tangent lines
    \return The number of tangent lines defined, {0,..,4}.

    Converts the arcs to circles and does
        return CS_CircleCircleTangent(cir0, cir1, lns[]) ;
 */
int CS_CircleCircleTangent(CS_ArcSeg &arc0, CS_ArcSeg &arc1, CS_LineSeg lns[]) ;


//! Returns the lines tangent to the arc passing through the point
/*! 
    \param pnt the test point the tangent line must pass thru
    \param arc the arc to the lines are to be tangent to
    \param tlns these are the tangency lines, must be allocated length 2
    \return The number of tangent lines defined, {0,1,2}.

    Converts the arc to a circle and does a tangency test, and 
    then makes sure the tangent line is actually on the arc. 
    Only those tangents that are on the arc are returned. 
 */
int CS_PointArcTangent(CS_POINT &pnt, CS_ArcSeg &arc, CS_LINE tlns[]) ;


//! Returns the triangular area enclosed by the three points using 
//! the cross product of ab x ac
double CS_AreaBy3Pnts(CS_POINT &a, CS_POINT &b, CS_POINT &c) ; 

//! Returns the two lines that touch the outermost extremeties of the shape
/*!
    \param crv input curve to find tangent lines to 
    \param tpnt the input test point that the tangent lines must pass through
    \param tln1 the first output tangent line found
    \param tln2 the second output tangent line found
    \return the number of tangent lines found. This can be 0, 1, or 2

    If no tangent lines are found then the point was inside the shape. 
    If one tangent line is returned then the point was on the shape boundary
    curve, and thus the tangent returned is the tangent at that point. In 
    the case of a single tangent line, only tln1 will be set, tln2 will be
    left unchanged. If 2 is returned then both tln1 and tln2 are updated. 
 */
int CS_CurveTangents(CS_Curve &crv, CS_POINT &tpnt, CS_LINE &tln1, CS_LINE &tln2) ;

//! Returns true if the two lines are parallel
/*!
    \param l1 the first line to test
    \param l2 the second line to test
    \return 1 if parallel otherwise 0

    Test to see if the magnitude of the cross product of the tangent vectors
    formed from the two line segments is zero within the current 
    tolerance setting. If cross product magnitude is zero then the
    lines are considered to be parallel.
 */
int CS_LinesParallel(CS_LineSeg &l1, CS_LineSeg &l2) ; 

#endif