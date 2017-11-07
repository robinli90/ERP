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
// cs_geomutils.h



//! Returns the nearest points between the line and a circle. 
/*!
    \param circ circle to test
    \param ln line to test
    \param npl nearest point on the line
    \param npc nearest point on the circle
    \return number of intersections between the line and the circle
    
    If the return value is 0 then npl is the nearest point on the line and
    npc is the nearest point on the circle. If there is a single intersection
    then npl will equal npc. If there are two intersection points, then npl and
    npc will be the two intersection points.
 */
int NearestPointCircleLine2D(CS_CIRCLE &circ, CS_LINE &ln, CS_POINT &npc, CS_POINT &npl) ;

//! Returns the nearest pointn between two circles. 
/*!
    \param c1 first circle to test
    \param c2 second circle to test
    \param np1 nearest point on the line
    \param np2 nearest point on the circle
    \return number of intersections between the line and the circle
    
    If the return value is 0 then np1 is the nearest point on the first circle and
    np2 is the nearest point on the second circle. If there is a single intersection
    then np1 will equal np2. If there are two intersection points, then np1 and
    np2 will be the two intersection points.
 */
int NearestPointCircleCircle2D(CS_CIRCLE &c1, CS_CIRCLE &c2, CS_POINT &np1, CS_POINT &np2) ;


//! Returns the minimum distance between the two segments. 
/*!
    \param pl1 pointer to the first line segment to test
    \param pl2 pointer to the second line segment to test
    \param p1 if not NULL then set to the minimum distance point on the first segment
    \param p2 if not NULL then set to the minimum distance point on the second segment
    \param u1 if not NULL then set to the u value along the first segment
    \param u2 if not NULL then set to the u value along the second segment 
    \return the minimum distance between the two line segments.

    If the segments intersect then p1 and p2 are set to the intersection point 
    (if p1 and/or p2 are not NULL), and the distance returned is zero. If any of
    p1, p2, u1, u2 are not NULL pointers they must point to valid memory areas 
    since no memory allocation is done inside the function.

    In the case of an overlap intersection, the start of the intersection overlap
    with respect to the pl1 segment is returned as the intersection point. If 
    you need to know the full range of the intersection then you must do a 
    separate intersection operation. 
 */
double CS_MinDistLineLine2D(CS_LineSeg *pl1, CS_LineSeg *pl2, 
                            CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ;

//! Returns the minimum distance between an arc and line segment. 
/*!
    \param pas1 pointer to the arc segment to test
    \param pl2 pointer to the line segment to test
    \param p1 if not NULL then set to the minimum distance point on the first segment
    \param p2 if not NULL then set to the minimum distance point on the second segment
    \param u1 if not NULL then set to the u value along the first segment
    \param u2 if not NULL then set to the u value along the second segment 
    \return the minimum distance between the arc and line segments.

    If the segments intersect then p1 and p2 are set to the intersection point(s) 
    (if p1 and/or p2 are not NULL), and the distance returned is zero. If any of
    p1, p2, u1, u2 are not NULL pointers they must point to valid memory areas 
    since no memory allocation is done inside the function.
 */
double CS_MinDistArcLine2D(CS_ArcSeg *pas1, CS_LineSeg *pl2, 
                           CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ;

//! Returns the minimum distance between the two arc segments. 
/*!
    \param pas1 pointer to the first line segment to test
    \param pas2 pointer to the second line segment to test
    \param p1 if not NULL then set to the minimum distance point on the first segment
    \param p2 if not NULL then set to the minimum distance point on the second segment
    \param u1 if not NULL then set to the u value along the first segment
    \param u2 if not NULL then set to the u value along the second segment 
    \return the minimum distance between the two line segments.

    If the segments intersect then p1 and p2 are set to the intersection point 
    (if p1 and/or p2 are not NULL), and the distance returned is zero. If any of
    p1, p2, u1, u2 are not NULL pointers they must point to valid memory areas 
    since no memory allocation is done inside the function.

    In the case of an overlap intersection, the start of the intersection overlap
    with respect to the pas1 segment is returned as the intersection point. If 
    you need to know the full range of the intersection then you must do a 
    separate intersection operation. 
 */
double CS_MinDistArcArc2D(CS_ArcSeg *pas1, CS_ArcSeg *pas2, 
                          CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ;

// double CS_MinDistCrvCrv2D(CS_Curve *pc1, CS_Curve *pc2, 
//                           CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ;

//! Returns the minimum distance between the two segments. 
/*!
    \param ps1 the first segment to test
    \param ps2 the second segment to test
    \param p1 if not NULL then set to the minimum distance point on the first segment
    \param p2 if not NULL then set to the minimum distance point on the second segment
    \param u1 if not NULL then set to the u value along the first segment
    \param u2 if not NULL then set to the u value along the second segment 
    \return the minimum distance between the two segments.
    
    If the segments intersect then p1 and p2 are set to the intersection point 
    (if p1 and/or p2 are not NULL), and the distance returned is zero. If any of
    p1, p2, u1, u2 are not NULL pointers they must point to valid memory areas 
    since no memory allocation is done inside the function.
 */
double CS_MinDistance2D(CS_SegPtr ps1, CS_SegPtr ps2, 
                        CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ;

//! Returns the minimum distance between the two curves. 
/*!
    \param pc1 the first curve to test
    \param pc2 the second curve to test
    \param p1 if not NULL then set to the minimum distance point on the first curve
    \param p2 if not NULL then set to the minimum distance point on the second curve 
    \param u1 if not NULL then set to the u value along the first curve
    \param u2 if not NULL then set to the u value along the second curve
    \return the minimum distance between the two curves.

    If there are multiple possible solutions, then the first one found is returned,
    which is determined by doing an in order walk of each segment on the two
    curves. This runs in order O(n1 * n2) time where n1 is the number of segments 
    in the first curve and n2 is the number of segments in the second curve. 

    If any of p1, p2, u1, u2 are not NULL pointers they must point to valid 
    memory areas since no memory allocation is done inside the function.
 */
double CS_MinDistance2D(CS_Curve *pc1, CS_Curve *pc2, 
                        CS_POINT *p1=0, CS_POINT *p2=0, double *u1=0, double *u2=0) ; 


//! Returns the minimum distance between two lines
/*!
    \param l1 the 1st input line to test
    \param l2 the 2nd input line to test
    \return the minimum distance in between l1 and l2

    This function calls int CS_LineLineNearestPoints(...) to 
    work out the minimum distance. If the two lines intersect
    then 0 is returned. 
 */
double CS_LineLineDist3D(CS_LINE &l1, CS_LINE &l2) ;
