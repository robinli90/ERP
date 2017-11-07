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
// cs_bezier.h

#ifndef __CS_BEZIER_H__
#define __CS_BEZIER_H__

#include "cs_geomdefs.h"
#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_shapes.h"


/*!
    A CS_BezierCrv defines the control points for a bezier curve. Thus
    the set of points effectively could also be called a Bezier curve
    instead of Bezier points. The CS_BezierCrv description was used
    since it is more indicative of what is actually being stored
    within the data structure. 
 */
typedef vector<CS_POINT> CS_BezierCrv ; 

/*!
    Iterator for walking through the CS_BezierCrv vector. Also 
    can be used as a pointer to a member within the CS_BezierCrv
    array. Normally the vector is accessed with integer indexing 
    but is included for completeness. 
 */
typedef vector<CS_POINT>::iterator CS_BezierCrvItr ; 


/*! 
    Defines a single continuous Bezier curve made up of separate 
    Bezier curve sections. A Bezier curve is the equivalent of a CS_Curve
    made up of Bezier sections. 
 */
typedef vector<CS_BezierCrv> CS_BezierChn ; 


/*! 
    Iterator for walking a Bezier curve list
 */
typedef vector<CS_BezierCrv>::iterator CS_BezierChnItr ; 

/*!
    The Bezier curve set contains separate bezier curve lists.
 */
typedef vector<CS_BezierChn> CS_BezierChnSet ;


//! Convert a parametric B(u) curve to an actual 3D point
/*!
    \param bzvec vector of control points defining the Bezier curve
    \param u parameteric coordinate along the curve \f$u\in[0,1]\f$
    \return the 3D point

    Uses successive approximation divide by two property of Bezier curves
    to generate the point on the curve. The number of iterations is 
    linear with the degree of the curve (length of the bzvec vector).
 */
CS_POINT CS_BezierPoint(CS_BezierCrv &bzvec, double u) ;


//! Approximate a Bezier curve with lines and arcs
/*!
    \param rescrv the output resultant curve
    \param pvec Bezier definition control vector. 
    \param uo the parameteric start point on the Bezier curve (default=0)
    \param uf the parameteric end point on the Bezier curve (default=1)
    \param tolcount determines how many iterations to perform when 
            approximating arcs (default=3)
    \param toldist tolerance distance to be used in the iterative search, default=kCOMPARETOLERANCE
    \return returns 0 on success, else an error code is returned

    The approximation is performed by taking two current end points (which get progressively 
    closer together as the approximation progresses) and the midpoint of those two 
    points. Then if all three points lie on the same arc a match counter is increased by
    1. If tolcount successive approximations all lie on the same arc, then the arc 
    is said to approximate that section of the curve accurately and the recursive routine
    exists. Otherwise the arc is split at the initial midpoint and the process continues
    with the two half sections. 
 */
int CS_BezierToCurve(CS_Curve &rescrv, CS_BezierCrv &pvec,
                     double uo=0.0, double uf=1.0, int tolcount=3, 
                     double toldist=kCOMPARETOLERANCE) ;

//! Work out the Bezier compound arc midpoint
/*!
    \param P0 the start point of the curve (control point P0)
    \param P2 the end point of the curve (control point P2)
    \param vs the tangent vector at the P0 control point
    \param ve the tangent vector at the P2 control point
    \param P1 the output mid control point 
    \return 0 on success, else an error code is returned. 

    The P0,vs point vector pair and the P2,ve pair define two lines which
    are intersected. The plane that the two lines define even if they do
    not intersect becomes the XY projection plane (X'Y') for this process. The 
    P0 point will lie on the plane and the P2,ve line will be parallel
    to the X'Y' plane. The P1 point will lie at the intersection of the 
    two lines as viewed top down on the X'Y' plane, at the minimum distance
    midpoint between the two lines. Another way of thinking about this is,
    if the two lines don't intersect in 3D space then create two planes
    one on each along the two lines. Then orient the planes so that each 
    is parallel to and never contacts the line that does not lie on it. 
    This way you end up with two parallel planes spaced by the minimum 
    distance between the two lines. The point P1 will lie on the plane 
    midway between the two parallel planes. 

    For this to work correctly the vs and ve vectors must intersect, thus 
    if they are parallel then the P0 and P2 end points must be on the same 
    plane as the vector directions. Otherwise it is impossible to generate
    a single center point and still have all the Bezier curve requirements
    met. If vs and ve are parallel but on different planes, then you would 
    need at least 2 internal points to create the Bezier curve that would
    result. 

    This is intended to be used with a smooth unwrapped curve where there
    are no discontinuities along the Z axis transitions (all segments join 
    at tangent start/end sections)
 */
int CS_CalcBezierArcMidPnt(CS_POINT &P0, CS_POINT &P2,   
                           CS_VECTOR &vs, CS_VECTOR &ve, 
                           CS_POINT &P1) ;

#endif