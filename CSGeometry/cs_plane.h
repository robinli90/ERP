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
// cs_plane.h

#ifndef __CS_PLANE_H__
#define __CS_PLANE_H__

#include "cs_geomdefs.h"
#include "cs_vectors.h"
#include "cs_curves.h"

#define CS_POINT_ALONG_NORMAL   0x01
#define CS_POINT_ON_PLANE       0x02
#define CS_POINT_ABOVE_PLANE    0x04
#define CS_POINT_BELOW_PLANE    0x08
#define CS_POINT_INFRONT        (CS_POINT_ABOVE_PLANE | CS_POINT_ON_PLANE)
#define CS_POINT_INBACK         (CS_POINT_BELOW_PLANE | CS_POINT_ON_PLANE)


#define CS_PROJ_RESULT              0x0100
#define CS_PROJVEC_PLLTO_PLANE      0x0010 
#define CS_PROJVEC_AWAYFROM_PLANE   0x0020
#define CS_PROJECT_ERROR            0x0040
#define CS_PROJPNT_ERRMASK          {CS_PROJVEC_AWAYFROM_PLANE | CS_PROJVEC_PLLTO_PLANE}
#define CS_PROJLINE_PARTIAL         0x0200
#define CS_PROJLINE_POINT           0x0400

#define CS_PROJ_NULLPOINTER         0x10000000

//! Definition of a fully constrained plane in 3D space
/*!
    A normal plane definition only requires 4 constants to fully locate the plane in 
    3D space whereas we are using 4 points here. The standard form is 

            ax + by + cz + d = 0 ; 

    {a,b,c} can be treated as a vector defining the normal to the plane, and d is the 
    negative of the dot product of {a,b,c} and the point on the plane. Or

    if v = {a,b,c}   and p = (p.x, p.y, p.z) the point on the plane
     

        ax + by + cz = v . p 

    Where v . p is the dot product of v and p. This gives
            
        a*x + b*y + c*z = a*p.x + b*p.y + c*p.z

    And d = -(a*p.x + b*p.y + c*p.z)
    
    More often though we are usually interested in taking some point on the plane or a 
    normal vector to the plane so that is how things are going to be stored here. 

 */
class CS_PLANE
{
public:
    //! Unit normal vector to the plane
    CS_VECTOR n ; 

    //! Point on the plane
    CS_POINT  p ; 

    CS_PLANE() {} ; 
    CS_PLANE(CS_POINT &pnt, CS_VECTOR &norm) : n(pnt), p(pnt) {} ; 


    CS_POINT &SetOrigin(CS_POINT &org) { p = org ; return p ; } 
    CS_POINT &Origin() {return p ; } 

    CS_VECTOR &SetNormal(CS_VECTOR &v) { n = v ; return n ; } 
    CS_VECTOR &Normal() {return n ; } 


    //! Returns true if the planes are equivalent
    /*!
        \param p the plane to test against
        \return true if the planes are the same. 
        
        Tests to see if if the normal vectors are identical and if the 
        point p.pnt is on the plane *this and if both are true then 
        it returns true, otherwise it returns false. 

        Thus the points defining the two planes don't have to be the 
        same for this function to return true. they simply have to lie
        on the same plane. 
     */
    bool operator==(const CS_PLANE &b) ; 

    //! Returns side of plane the pnt is on
    /*!
        \param pnt the point to test
        \return the side of the plane the point is on
        Uses logic similar to the NearestPoint() function to determine
        which side of the plane the point is on 

        Return values
        <ul>
            <li>CS_POINT_ON_PLANE     = pnt was on the plane, thus pnt is the returned point
            <li>CS_POINT_ABOVE_PLANE  = pnt was above the plane (in front of plane)
            <li>CS_POINT_BELOW_PLANE  = pnt was below the plane (behind the plane)
        </ul>
     */
    int PointSide(const CS_POINT &pnt) ;


    //! Intersect the line and the plane
    /*! 
        \param ls line segment to test
        \param ipnt intersectino point on the plane
        \param useg if not null then will be set to u value along ls of the intersection point. 
        \return status of the intersection

        returns 0 if the point is on the line segment, 1 if the point is 
        outside the line segment. If useg is not NULL then the u parm on the
        line segment is also returned. If there is no unique solution then
        -1 is returned (line is on the plane). 
     */
    int Intersect(CS_LineSeg &ls, CS_POINT &ipnt, double *useg) ; 


    //! Intersect the line and the plane
    /*! 
        \param sp start point of line segment to intersect
        \param ep end point of line segment to intersect
        \param ipnt intersectino point on the plane
        \param useg if not null then will be set to u value along ls of the intersection point. 
        \return status of the intersection

        returns 0 if the point is on the line segment, 1 if the point is 
        outside the line segment. If useg is not NULL then the u parm on the
        line segment is also returned. If there is no unique solution then
        -1 is returned (line is on the plane). 
     */
    int Intersect(CS_POINT &sp, CS_POINT &ep, CS_POINT &ipnt, double *useg) ; 


    //! Nearest point on the plane to the input point. 
    /*!
        \param pnt the point to test
        \param stat status return information if defined
        \return nearest point on the plane to the input point pnt

        Returns the nearest point on the plane to the point \a pnt.
        If stat is not null, then it is made up of the following ORed values:
        <ul>
            <li>CS_POINT_ALONG_NORMAL = point is along the normal vector defining the plane
            <li>CS_POINT_ON_PLANE     = pnt was on the plane, thus pnt is the returned point
            <li>CS_POINT_ABOVE_PLANE  = pnt was above the plane
            <li>CS_POINT_BELOW_PLANE  = pnt was below the plane
        </ul>

        The concept of above and below the plane is defined by the normal vector. 
        If the dot product of the normal vector and the vector from the returned 
        point to the input point is positive, then the point is considered to 
        be above the plane. If the dot product is negative it is below the plane.
        Or in other words. on the side of the plane in the normal vector direction
        is above, and in the reverse normal direction is below. 

        When CS_POINT_ALONG_NORMAL is returned this means that the point pnt is on
        the same line formed by p and n that define the plane. 
        
        If stat == (CS_POINT_ALONG_NORMAL | CS_POINT_ON_PLANE) then (pnt == p) must
        also be true (the point passed in for testing is the same point that defines
        the plane). 
     */
    CS_POINT NearestPoint(CS_POINT &pnt, int *stat=0) ;

    //! define plane by 3 points
    /*!
        \param p1 first point, and the origin of resultant plane
        \param p2 second point
        \param p3 third point
        \return error conditions

        Sets the normal vector n and origin p that define the plane. 
        If the 3 points are all on a line then -1 is returned and 
        nothing is changed. 
     */
    int PlaneBy3Points(CS_POINT &p1, CS_POINT &p2, CS_POINT &p3) ; 

    //! Project the inpnt onto the plane along the vprj vector
    /*!
        \param inpnt the input point to be projected
        \param vprj the projection vector
        \param prjpnt the output projection point on the plane. 
        \return status information

        Return codes:
            CS_PROJ_RESULT - point projected OK, result generated
            CS_PROJVEC_AWAYFROM_PLANE - point is projected away from plane
            CS_PROJVEC_PLLTO_PLANE - no solution, projection direction parallel to plane

        Note that if CS_PROJVEC_AWAYFROM_PLANE is returned, the prjpnt will be 
        set to the point on the plane as if the projection vector were reversed. 
     */
    int Project(CS_POINT &inpnt, const CS_VECTOR &vprj, CS_POINT &prjpnt) ;

    //! Converts vectors to points and calls the above point projection function. 
    int Project(CS_VECTOR &invec, const CS_VECTOR &vprj, CS_VECTOR &prjvec) ; 

    //! Project line to the surface of the plane
    /*!
        \param pls the line to project to the plane
        \param prjvec projection vector direction
        \param lnout the output projection line
        \return status information

        A number of possible conditions can occur, the line could be in front
        or behind the plane to start with, or it could pass through the plane. 
        The projection vector will move the line towards, away from, or parallel
        to the plane. 

        The parallel direction where the line crosses the plane could 
        theoretically generate a ray in the projection vector direction
        starting from the point where the line passes through the plane. 
        Since the length of the line is arbitrary (infinite), in this case
        a zero length line where the start and end points match is returned. 

        If the line crosses the plane and is not parallel then a partial 
        line projection is returned. 

        Return values
            CS_PROJ_RESULT - some for of result was generated
            CS_PROJLINE_PARTIAL - line crossed plane so the projected line up to the
                plane only is generated, the portion of the input line behind the 
                plane is ignored in the result.
            CS_PROJVEC_PLLTO_PLANE 
            CS_PROJLINE_POINT - projection vector was parallel to plane but 
                crossed plane so return the plane intersection point. 
     */
    int Project(CS_LineSeg *pls, const CS_VECTOR &prjvec, CS_LineSeg &lnout) ;


    //! Project the input curve along the prjcrv vector onto the plane
    /*!
        \param incrv the input curve to be projected onto the plane
        \param prjvec the projection direction vector pointing towards the plane
        \param projCrvOut the output projected curve on the plane
        \param tol tolerance to use for end point comparison when mode=true
        \param mode set true to force a closed curve on return.
        \return 0=OK, else error code

        If the prjvec when overlayed at the startpoint of the incrv points
        away from the plane, then no result will be generated. 

        Return values
            0x00001 - the projection vector points away from the plane. 
            0x00002 - unknown error occured. 
            0x00004 - null input curve
            0x00008 - zero direction vector
            0x00010 - projection vector is parallel to plane

        NOTE: Only line segments are supported, arcs will result in memory referencing 
            errors and produce junk results. 
            
        If mode is false and the resultant curve is open then not all end points 
        will be connected. Setting mode true will force the curve to be closed since 
        extra line segments are automatically inserted into the curve if there are gaps. 
        However, there is no final test to make sure the overall start and end point
        are connected. 

        TODO extend to arcs through bezier curves (must upgrade to allow for 
        CS_BezierSegs)

     */
    int Project(CS_Curve &incrv, const CS_VECTOR &prjvec, CS_Curve &projCrvOut, 
                double *tol=&COMPARETOLERANCE, int mode=0) ;


    //! Returns the shortest (perpendicular) distance of the point to the plane
    /*!
        WARNING: the normal vector n must be defined as a unit vector for this 
        to return the correct result, otherwise, use the standard distance 
        function which will also divide by the normal vectors magnitude. 
     */
    double DistanceNorm(CS_POINT &p) ; 

    //! Returns the shortest (perpendicular) distance of the point to the plane
    double Distance(CS_POINT &p) ; 

} ;



#endif