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
// cs_fitcircle.h


#ifndef __CS_FITCIRCLE_H__
#define __CS_FITCIRCLE_H__

//! Fit circles inside or around curves
/*!
    Given points either on or near the curve circles are grown until they 
    intersect with the curve. A binary search is used to fit the circle
    so that it just touches the curve, thus the curve stops growing at
    the point where the first intersection with the curve is found. 
    Calling this function at small intervals along a closed curve
    will result in a set of points equivalent to a medial axis diagram
    for the curve. 
 */
class CS_FitCircleToCurve
{
public:
    CS_Curve *pcrv ; 
    CS_RECT cbrect ; // overall bounding rectangle
    CS_RECT *crvrect ; // array of bounding rectangles for the curve
    double u ; 
    CS_POINT upnt, lnpnt ; // u pnt and 1st line intersect point
    CS_VECTOR vtan ; 
    CS_VECTOR vctr ; 
    double maxrad ; // maxrad is set to the line pnt distance 
    double finalrad ; // final resultant radius
    int iters ; // total number of iterations processed
    int maxiters ; // default is 40 which should give about 9 sig figures

    int bLastWasTangent ; 

    //! Set true in IntersectCrvAndCirc() if a curve segment is completely
    //! inside the test circle
    int bFoundContainedSegment ; 
    CS_Segment *pcontainedseg ; 

    int tanerr ; // number of intersects at upnt that weren't reported as tangent
    int nisects ; // number of non-tangent intersects
    int ntangent ; // number of tangent intersects
    int done ; 

    // While searching for the first tangent intersection, keep track of the 
    // last intersect found as well as the radius. Also keep track of the last
    // tangent intersection found
    CS_POINT lastipnt, lasttanipnt ; 
    double lastirad, lasttanirad ; 

    //! Set of contact/intersection points of the fit circle to
    //! the shape that is being fitted
    CS_POINTList pntlst ; 

    CS_FitCircleToCurve() ; 
    ~CS_FitCircleToCurve() ; 

    //! Initialize the curve and the bounding rects for each segment
    /*!
        This must be called first, then call FitCircle(...)
     */
    void InitSegRects(CS_Curve *pcrv) ; 

    //! Called internally within FitCircle automatically
    /*!
        Initializes all the internal parameters for the next run.
     */
    void InitRun() ;

    //! Called internally within FitCircle automatically
    /*!
        Initializes all the internal parameters for the next run. Calls
        InitRun() member function internally. Used by 
        FitCircle(double&, CS_CIRCLE&, int, double).
     */
    void InitRun(double ucrv, int side=CS_LEFTSIDE) ;

    //! Called internally within FitCircle automatically
    /*!
        Initializes all the internal parameters for the next run. Calls
        InitRun() member function internally. Used by 
        FitCircle(double&, CS_VECTOR&, CS_CIRCLE&, double).
        The internal vctr variable is set to vsearch in this mode. 
     */
    void InitRun(double ucrv, CS_VECTOR &vsearch) ;
    
    //! Fit largest possible circle at the curve point u
    /*!
        \param u parameteric point along the curve to be tested
        \param retcirc the resultant largest circle
        \param side of the curve to fit, other side is ignored
        \param radtol tolerance exit condition for search loop 
        \return bit flag error code 
            <ul>
                <li>CS_FOUND     found circle</li>
                <li>CS_NOTCLOSED open curve warning</li>
                <li>CS_INFINITE  infinite circle result</li> 
                <li>CS_MAXITERS  hit max iterations</li> 
                <li>CS_NOTFOUND  error condition</li> 
            </ul>

        The routine takes the point given and increases the size of a 
        circle tangent to the curve at the given \a u point until an
        interesction point is found (an intersection which is not the tangent
        point obviously). The routine limits the maximum diameter of the 
        circle to the diagonal of the bounding rectangle for the input curve.
        If the input curve is not closed the routine will still try to fit 
        a circle and expand until the maximum diameter limit is reached.
        The side parameter controls which side of the curve the circle is
        placed during testing. For a CCW closed curve the default CS_LEFTSIDE
        will search for the largest fitting inside circle at the given u point.
        The radtol parameter controls when the internal binary search loop 
        exists. If two test circles have radii that match within an 
        amount less than radtol then the resultant circle is set at the
        average between these two values and the function returns. If the 
        radtol parameter is never reached then the routine exits after 40 
        iterations. If radtol is -1.0 then no tolerance testing is used and
        the function only exits if an exact fit is found, or the 40 iterations
        is reached. 
     */
    int FitCircle(double &u, CS_CIRCLE &retcirc, int side=CS_LEFTSIDE, double radtol=-1.0) ;


    //! Fit largest possible circle at the curve point u
    /*!
        \param u parameteric point along the curve to be tested
        \param vsearch direction of line that centre of fit circle will be on
        \param retcirc the resultant largest circle
        \param radtol tolerance exit condition for search loop 
        \return bit flag error code 
            <ul>
                <li>CS_FOUND     found circle</li>
                <li>CS_NOTCLOSED open curve warning</li>
                <li>CS_INFINITE  infinite circle result</li> 
                <li>CS_MAXITERS  hit max iterations</li> 
                <li>CS_NOTFOUND  error condition</li> 
            </ul>

        The routine takes the point given and increases the size of a 
        circle tangent to the curve at the given \a u point until an
        interesction point is found (an intersection which is not the tangent
        point obviously). The routine limits the maximum diameter of the 
        circle to the diagonal of the bounding rectangle for the input curve.
        If the input curve is not closed the routine will still try to fit 
        a circle and expand until the maximum diameter limit is reached.

        The difference between this function and the \a FitCircle() member
        function is that instead of growing the circle by moving the centre
        along the perpendicular line extending away from the curve, this 
        version searches along the direction sepcified by the vsearch vector.

        It only makes sense to use this version when the u point is at 
        an internal convex corner (convex with respect to somebody standing
        inside the shape).
          
        The radtol parameter controls when the internal binary search loop 
        exists. If two test circles have radii that match within an 
        amount less than radtol then the resultant circle is set at the
        average between these two values and the function returns. If the 
        radtol parameter is never reached then the routine exist after 40 
        iterations. If radtol is -1.0 then no tolerance testing is used and
        the function only exits if an exact fit is found, or the 40 iterations
        is reached. 
     */
    int FitCircle(double &u, CS_VECTOR &vsearch, CS_CIRCLE &retcirc, double radtol=-1.0) ;


    //! Return first circle which fits and exceeds a limit radius
    /*!
        \param u parameteric point along the curve to be tested
        \param limitRad radius to stop search at. 
        \param retcirc the resultant largest circle
        \param side of the curve to fit, other side is ignored
        \param radtol tolerance exit condition for search loop 
        \return bit flag error code 
            <ul>
                <li>CS_FOUND      found circle</li>
                <li>CS_FOUNDLIMIT rad exceeded limit rad value</li>
                <li>CS_NOTCLOSED  open curve warning</li>
                <li>CS_INFINITE   infinite circle result</li> 
                <li>CS_MAXITERS   hit max iterations</li> 
                <li>CS_NOTFOUND   error condition</li> 
            </ul>
     */
    int FitLimitCircle(double &u, double limitRad, 
                       CS_CIRCLE &retcirc, int side=CS_LEFTSIDE, double radtol=-1.0) ;


    //! Does the acutal processing for the FitCircle() member fucntion
    /*!
        \param u parameteric point along the curve to be tested
        \param retcirc the resultant largest circle
        \param radtol tolerance exit condition for search loop
        \param pLimitRad pointer to a limit radius when fitting

        Before calling this function the InitRun() function must be called
        to setup the various internal parameters correctly. 

        If the pLimitRad parameter is not null, then the processing behaves a little
        differently. In this case, as soon as a circle is found to fit whose radius
        exceeds the limit value the searching stops. Then the circle with a radius 
        exactly equal to the limit radius is returned. This is done by setting the
        centre point along a vector to the point on the curve from the center of
        the larger circle. 
     */
    int DoFit(double &u, CS_CIRCLE &retcirc, double radtol, double *pLimitRad=0) ; 

    //! Fit circle to curve at the test point
    /*!
        \param tstpnt [I] 2D point where the circle will grow from
        \param retrad [O] the resultant largest circle radius 
        \param radtol [I] resolution of result accuracy
        \return status flags
            <ul>
                <li>CS_FOUND     found circle</li>
                <li>CS_MAXITERS  hit max iterations</li> 
            </ul>

        The routine takes the point given and increases the size of a 
        circle at that point until an interesction with the curve occurs.
        If the circle is outside the bounding rectangle for the curve then
        the closest and furthest points of the curve's bounding rectangle
        define the search range used. Note this routine should always return
        a resultand radius value

        \verbatim
        CS_Curve *pcrv ; // curve to fit to
        CS_POINT pnt ; // fit test point
        double maxrad ; // max radius of circle centered at pnt
        
        CS_FitCircleToCurve fc  ; 
        fc.InitSegRects(pcrv) ;
        fc.FitCircle(pnt, maxrad) ;
        \endverbatim

     */
    int FitCircle(CS_POINT &tstpnt, double &retrad, double radtol=-1.0) ;
} ;

// Should probably get rid of these functions and just leave the class behind. 

//! Find largest fitting circle inside crv at point u
/*!
    \param crv input closed curve that the circle will be fit into
    \param u   parametric point along curve to test at 
    \param retcirc the resultant largest fitting circle
    \param side CS_LEFTSIDE (default) or CS_RIGHTSIDE
    \return bit flag error code 
        <ul>
            <li>0=ok</li>
            <li>0x0001=curve not closed</li>
            <li>0x0002=infinite circle, CS_INFINITE</li> 
        </ul>

    The routine takes the point given and increases the size of a 
    circle tangent to the curve at the given \a u point until an
    interesction point is found (an intersection which is not the tangent
    point obviously). The routine limits the maximum diameter of the 
    circle to the diagonal of the bounding rectangle for the input curve.
    If the input curve is not closed the routine will still try to fit 
    a circle and expand until the maximum diameter limit is reached.
    The side parameter controls which side of the curve the circle is
    placed during testing. For a CCW closed curve the default CS_LEFTSIDE
    will search for the largest fitting inside circle at the given u point.

    Note: If you need to call this more than once for a specific curve then
    it is much more efficient to use the CS_FitCircleToCurve class which maintains
    all the internal bounding rectangle information until it is destroyed. 
    Calling this function repeatidly will recreate this data each time. 
 */ 
int CS_FitCircle(CS_Curve &crv, double &u, CS_CIRCLE &retcirc, int side=CS_LEFTSIDE) ;


//! Find largest fitting circle inside crv at point pnt
/*!
    \param crv input closed curve that the circle will be fit into
    \param pnt point defining circle center
    \param retrad the radius of the circle at first contact with curve
    \return bit flag error code 
        <ul>
            <li>0=ok</li>
            <li>0x0001=curve undefined</li>
        </ul>

    The routine takes the point given and increases the a circle from a
    size of zero until it first touches some part of the curve. If the 
    point is on the curve then zero will be returned for the radius. 

    WARNING - NOT COMPLETED will not return valid result. 
 */ 
int CS_FitCircle(CS_Curve &crv, CS_POINT &pnt, double &retrad) ;


//! Find largest circle that will fit into shape near input pnt
/*!
    \param crv [I] the shape that the circle will fit into
    \param pnt [I] initial starting point defining center of the circle
    \param retcirc [O] the resultant output circle
    \param eps [I] maximum distance from pnt that retcirc's centre can be. 
    \return 0=OK, else error code (no errors currently)


 */
int CS_FitMaxCircle(CS_Curve &crv, CS_POINT &pnt, CS_CIRCLE &retcirc, double *eps=0) ;

//! Finds the maximum circle that will fit inside the shape. 
/*!
    \param shp must be a closed CCW curve that defines the shape
    \param ustep the u delta used to walk around the shape for testing
    \param retcirc the maximum circle
    \return status of the search, see below

    Calls fit circle repeatedly around the shape returning the maximum circle
    that was found. 

    If the shape is a circle and is CW CS_INFINITE will be returned. 

    Returns: 
        CS_NOTCLOSED : shape wasn't closed
        CS_INFINITE  : resultant circle is infinite
        CS_FOUND     : found a valid result. 

 */
int CS_FindMaxCircleInShape(CS_Curve &shp, double ustep, CS_CIRCLE &retcirc) ;

#endif