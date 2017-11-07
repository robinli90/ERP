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
// cs_cadfuncs.h - utility functions useful for CAD applications


#ifndef __CS_CADFUNCS_H__
#define __CS_CADFUNCS_H__


#define CS_EXTRIM_1ST_SEGMENT         0x0001
#define CS_EXTRIM_2ND_SEGMENT         0x0002
#define CS_EXTRIM_BOTH_SEGMENTS       (CS_EXTRIM_1ST_SEGMENT | CS_EXTRIM_2ND_SEGMENT)

// Curve type functions

//! Extends or trims the two curves to their intersection point
/*!
    \param sega pointer to first segment to trim or extend
    \param ppa control point for the first segment
    \param segb pointer to the second segment to trim or extend
    \param ppb control point for the second segment
    \return 0 on success, otherwise an error code is returned.

    The portions retained is that which is nearest the point passed 
    in corresponding to the segment. When the segment does not extend 
    to an intersection point then that(those) curve(s) is(are) extended. 
    Thus possible outcomes are trim-trim, extend-trim, trim-extend, or 
    extend-extend.

    If the two segments do not intersect after extending their end points
    then the function fails and an error code is returned. Currently
    the only error code defined is 2=No Intersection, and 3=collinear
    lines thus the trim/extend is undefined.
  */
int CS_ExTrimEndpoints(CS_SegPtr sega, CS_POINT &ppa, 
                       CS_SegPtr segb, CS_POINT &ppb) ;

//! Extends or trims the first curve to the intersection point
/*!
    \param sega pointer to the segment to trim or extend
    \param ppa control point for the first segment
    \param segb pointer to segment defining the trim/extend boundary
    \param ppb control point for the second segment
    \return 0 on success, otherwise an error code is returned.

    The portions retained is that which is nearest the point passed 
    in corresponding to the segment. When the segment does not extend 
    to an intersection point then that(those) curve(s) is(are) extended. 
    Thus possible outcomes are trim or extend of the first segment, 
    as well as no action in the case of an error.

    If the two segments do not intersect after extending their end points
    then the function fails and an error code is returned. Currently
    the only error code defined is 2=No Intersection, and 3=collinear
    lines (the trim/extend is undefined).
  */
int CS_ExTrimFirstEndpoint(CS_SegPtr sega, CS_POINT &ppa, 
                           CS_SegPtr segb, CS_POINT &ppb) ;

//! Find the furthest perpendicular point from the line on the test segment 
/*!
    \param ptestseg the segment that the resultant point must be on
    \param line the reference line segment the distance is being measured from
    \param side controls the side of the line to limit testing to
    \return the furthest point from the line on the segment

    Returns the furthest perpendicular point from the line that is still on 
    the given test segment. If the side is specified as CS_RIGHTSIDE, or 
    CS_LEFTSIDE then only that part of the segment that is on the right 
    or left of the line respectively is used in determining the furthest point. 
    The default value of side is CS_BOTHSIDES (note this is not the same as
    CS_LEFTSIDE | CS_RIGHTSIDE since CS_LEFTSIDE=-1 and CS_RIGHTSIDE=1)

    Note: This only works on the 2D XY plane.
 */
CS_POINT FurthestPointOnSegToLine(CS_SegPtr ptestseg, CS_LINE &line, int side = CS_BOTHSIDES)  ;

//! Stretch a section of a curve based on the control points, and save result in prescrv
/*!
    \param sc    Input curve to be stretched
    \param frmpnt The from point defining the stretch delta
    \param topnt  The to point defining the stretch delta
    \param stepSize Incremental step control distance
    \param stepMode Defines how the stretch behaves, range is [0,2]
    \param prescrv The output resultant curve
    \param pstretchSection  Output part of the curve that was actually modified
    \return The status of the stretch operation. 0=success, greater than 0 
    means there was a warning, less than 0 indicates a error condition

    The from and to points define which segment of the curve is to be stretched
    and how far the section is to be stretched. The curve segment that is 
    nearest the from point defines the base curve that will be offset initially.
    The length of the line connecting the from point to the two point defines
    the offset distance (stretch distance) for the base curve segment. The 
    naming stretch 3 means that the base curve and possibly the two 
    connecting curves are shifted while the curves connected to the 1,2 or 3
    base curves are the curve segments that are actually stretched. The 
    stretch operation depends on what type of geometry is connected to the 
    base curve. See CS_Stretch1 if you only want to shift the base curve and
    modify the two directly adjacent curve sections. 

    If the stepMode is set to 0 then this parameter is ignored, if the value
    is 1 however, when the stepSize is non-zero, the step will only 
    be a single increment of stepSize in either the plus or minus direction.
    If stepMode is 2, then the stretch distance can be any +/- multiple 
    of stepSize.

    Pass a pointer to a valid CS_Curve* if the curve section that was 
    actually modified is required. 

 */

int CS_Stretch3(CS_Curve &sc, CS_POINT &frmpnt, CS_POINT &topnt, 
                double stepSize, int stepMode,
                CS_Curve*& prescrv, CS_Curve** pstretchSection=0) ;


//! Return the closest points on the two lines
/*!
    \param l1 the first input line to test
    \param l2 the second input line to test
    \param u1 the u parameter at closest point on line \a l1
    \param u2 the u parameter at closest point on line \a l2
    \returns CS_NONCOLLINEAR, CS_PARALLEL or CS_COLLINEAR

    This function creates unit vectors for the parameteric representation
    of the lines and then calls the parametric form of this function. 
    See:
        CS_LineLineNearestPoints(CS_POINT &P0, CS_VECTOR &vu, 
                                 CS_POINT &Q0, CS_VECTOR &vv, 
                                 double &up, double &uq) 
    for further details. 
 */
int CS_LineLineNearestPoints(CS_LINE &l1, CS_LINE &l2, double &u1, double &u2) ;


//! Return the closest points on the two lines
/*!
    \param P0 base point defining first parameteric line 
    \param vu vector defining the first parameteric line
    \param Q0 base point defining second parameteric line
    \param vv vector defining the second parameteric line
    \param up the u parameter at closest point on first line
    \param uq the u parameter at closest point on second line
    \returns CS_NONCOLLINEAR, CS_PARALLEL or CS_COLLINEAR

    If there is a basic single solution then CS_NONCOLLINEAR is returned. 
    If the lines are parallel and do not touch one another then a solution
    incorporating the start point of the first line is generated and 
    CS_PARALLEL is returned. If the two lines are identical then 
    the u points are set based on the start point of line one and 
    CS_COLLINEAR is returned. 

    This function works in both 2D and 3D. 

 */
int CS_LineLineNearestPoints(CS_POINT &P0, CS_VECTOR &vu, 
                             CS_POINT &Q0, CS_VECTOR &vv, 
                             double &up, double &uq) ;


//! Cross hatch the area within xcrv
/*!
    \param xcrv defines the boundary of the cross hatching. 
    \param angle angle of the lines in degrees
    \param spacing distance between hatch lines
    \param ppnts resultant hatching line segment endpoints in point pairs
    \param maxpnts maximum number of ppnts that can be stored.
    \return number of hatching line segments generated. 

    The cross hatching angle is relative to the X axis. Zero degrees = parallel 
    to X axis and 90 degrees = parallel to Y axis. 

    The ppnts array contains pairs of points defining the endpoints of the hatch 
    lines. The return value is the number of points returned, thus the number
    of cross hatch lines will be n/2. 
 */
int CS_XHatchLines(CS_Curve &xcrv, 
                   const double &degangle, 
                   const double &spacing, 
                   CS_POINT *ppnts, 
                   int maxpnts) ;

#endif