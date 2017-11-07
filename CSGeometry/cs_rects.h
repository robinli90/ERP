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
// rects.h
#ifndef __RECTS_H__

#define __RECTS_H__


#include "math.h"
#include "cs_vectors.h"

////////////////////////////////////////////////////////////////////
// Rectangle class which stores the two diagonal corner points of
// a rectangle, defined by top, left, bottom, right
// Note: the Z component is ignored in rectangles
class CS_RECT {
public:
    double t,l,b,r ; 

    CS_RECT() { } ; 
    CS_RECT(double top, double left, double bottom, double right) ; 
    CS_RECT(CS_POINT &a, CS_POINT &b) ; 
    ~CS_RECT() { } ; 

    inline double Top() { return t ;} ; 
    inline double Left() {return l ; } ;
    inline double Bottom() {return b ; } ;
    inline double Right() {return r ; } ; 
    inline double Height() {return t - b ; } ;
    inline double Width() {return r - l ; } ; 
    inline double XCtr() { return (r + l) / 2.0 ; } ;
    inline double YCtr() { return (t + b) / 2.0 ; } ;

    CS_POINT TLPoint(){ return CS_POINT(l, t, 0) ; } 
    CS_POINT TRPoint(){ return CS_POINT(r, t, 0) ; } 
    CS_POINT BLPoint(){ return CS_POINT(l, b, 0) ; } 
    CS_POINT BRPoint(){ return CS_POINT(r, b, 0) ; } 

    //! Shifts the rectangle corners by the vector specified
    /*!
        \return reference to the resultant rectangle
        
        Shifts the rectangle in space by the vector. The Z component of 
        the vector is ignored and not used in any way to do the move.
        The rectangle is modified so that the result is:
            t = t + v.y ; 
            l = l + v.x ; 
            b = b + v.y ; 
            r = r + v.x ; 
     */
    CS_RECT &Move(CS_VECTOR &v)
    {
        t += v.y ; 
        l += v.x ; 
        b += v.y ; 
        r += v.x ; 
        return *this ; 
    }

    //! Enlarges or shrinks the rectangle by the scale factor. 
    /*! 
       Expands the rectangle by the scale factor specified. A scale
       factor of zero will leave the rectangle as it was. A negative 
       scale factor will shrink the rectangle and a positive scale factor
       will enlarge the rectangle. The centroid of the rectangle will 
       remain the same after this operation. A scale factor of 2 will 
       result in a rectangle who's sides are all three times as long as the 
       original since twice the current length of a side will be added to 
       each edge of the rectangle.
            Scale        Side Dimension 
                             delta %
               .               n.0     ^  Anything in this region causes
               .               n.0     |  the resulting rectangle to invert
               .               n.0     |  and grow to a larger size
             -5.0           -500.0     |
             -4.0           -400.0     |
             -3.0           -300.0    /
             -2.0           -200.0    ==> Inverted rectangle same as original
             -1.0           -100.0    ==> rectangle with zero area
              0.0              0.0    No Change
              1.0            100.0
              2.0            200.0
              3.0            300.0
              4.0            400.0
     */
    CS_RECT &Expand(double scale) ;

    //! Grows the rectangle outward by the current system tolerance
    /*!
        \return *this, reference to the modified rectangle.

        Performs the following operations:
        <ul>
            <li> t += tolerance
            <li> r += tolerance
            <li> b -= tolerance
            <li> l -= tolerance
        </ul>
     */
    CS_RECT &Grow() 
    {
        t += COMPARETOLERANCE ;
        r += COMPARETOLERANCE ;
        b -= COMPARETOLERANCE ;
        l -= COMPARETOLERANCE ;
        return *this ; 
    }

    //! Grows the rectangle outward by the amount specified.
    /*!
        \param amount the value added/subtracted from the rectangle sides
        \return *this, reference to the modified rectangle.

        Performs the following operations:
        <ul>
            <li> t += amount
            <li> r += amount
            <li> b -= amount
            <li> l -= amount
        </ul>
     */
    CS_RECT &Grow(double amount) 
    {
        t += amount ;
        r += amount ;
        b -= amount ;
        l -= amount ;
        return *this ; 
    }

    //! Returns the center point of the rectangle
    CS_POINT Center() ; 
    //! Returns the center point of the rectangle
    CS_POINT Centre() ; 

    //! Tests if the point is inside or on the rectangle. The default system
    //! tolerance is used when doing this test, thus if the point lies outside
    //! of an edge by lese than the tolerance amount, it will still test as
    //! being inside.
    int Inside(CS_POINT &pnt) ; 

    //! Tests if the point is inside or on the rectangle. The user specified
    //! tolerance is used when doing this test, thus if the point lies outside
    //! of an edge by less than the tolerance amount, it will still test as being 
    //! inside.
    int Inside(CS_POINT &pnt, const double &tol) ;

    //! Scale the rectangle by the input factor
    /*!
        The t,l,b, and r members are simply multiplied by the scale factor. 
        Keep in mind that unless the rectangle contains the origin, this will 
        shift the rectangle in space so that it covers a different area than
        before. Scaling the l parameter by 2 for example would shift the left
        edge x coordinate of the rectangle to the right if l > 0 was true. 
        If you need to shift the sides out while not moving the centroid of
        the rectangle, then use the Expand() or Grow() functions.
     */
    CS_RECT &Scale(double factor) ; 

    //! Result is union of both rectangles, returns *this
    /*!
       \param rect the other rectangle to form the union with
       \return reference to base rectangle (*this). The base rectangle is
       modified in the process and becomes the union of *this and rect.

        This is not a true union operation, the result is simply the new
        smallest bounding rectangle that includes both of the original rectangles. 
     */
    CS_RECT &Union(CS_RECT &rect) ; 

    // \todo - decide how to deal with the intersect concept whether we
    //    want to create a NULL rectangle when the two do not overlap
    //    or if we want to simply leave the original alone. Could set
    //    t,l,b,r all to inf or -inf and then wouldn't intersect 
    //    with anything else (sort of). Or add a status indicator 
    //    variable to define ISNULL, or compare all values for 
    //    equality in which case the rectangle is NULL. 
    // void Intersect(CS_RECT &rect) ; // intersection of both rectangles
    
    //! returns true if the two rectangles overlap (touch) anywhere
    /*!
        \param rect Second rectangle to compare against.
        \return true (1) if the rectangles overlap otherwise returns false. 

        The overlap test is done using full floating point precision,
        no tolerance factor is applied when testing for overlap. Thus
        if you need to allow for tolerance comparison, expand the 
        size of the rectangle first, using the Expand() function.
     */
    int Overlaps(CS_RECT &rect) ; 
} ; 

#ifndef CS_Curve 
class CS_Curve ; 
#endif

// 3D bounding boxes around a set of points
class CS_BoundBox
{
public:
    CS_POINT minpnt ; 
    CS_POINT maxpnt ; 

    CS_BoundBox() {} ; 
    
    //! Calls Init(d)
    CS_BoundBox(const double &d) ; 
    
    //! Initialize all minpnt.p[] to d and maxpnt.p[] to -d
    CS_BoundBox &Init(const double &d) ; 
    CS_BoundBox &UpdateMinMaxPnts(CS_POINT &p) ;
    CS_BoundBox &SetMinMaxPnts(CS_Curve *pcrv) ;

} ; 

#endif