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
// vectors.h 

#ifndef __CS_VECTORS_H__

#define __CS_VECTORS_H__ 


#include <stdio.h>

extern char szGeomErrString[] ; 

class CS_VECTOR ; 
class CS_VECTOR2D ; 

////////////////////////////////////////////////////////////////////////////
// 2 Dimensional points and vectors
////////////////////////////////////////////////////////////////////////////

class CS_POINT2D {
public:

    union {
        double p[2] ; 
        struct {
            double x ; 
            double y ;
        } ;
    } ;


    CS_POINT2D() { x=0.0; y=0.0; }

    CS_POINT2D(double *pnt) : x(pnt[0]), y(pnt[1]) {}  

    CS_POINT2D(double i, double j) : x(i), y(j) {}

    CS_POINT2D operator*(double s) ; 

    CS_POINT2D operator/(double d) ; 

    CS_POINT2D operator-() ;

    CS_POINT2D operator-(const CS_POINT2D &pnt) ; 

    CS_POINT2D operator-(const CS_VECTOR2D &v) ; 

    CS_POINT2D operator+(const CS_VECTOR2D &v) ; 

    CS_POINT2D operator+(const CS_POINT2D &pnt) ; 

    double operator*(const CS_POINT2D &pnt) ; // dot product

    int operator==(const CS_POINT2D &pnt) ; 

    int operator!=(const CS_POINT2D &pnt) ; 


    CS_POINT2D &Set(double xv=0.0, double yv=0.0)
    {
        x = xv ; 
        y = yv ;
        return *this ; 
    }

    CS_POINT2D &Set(double *p)
    {
        x = p[0] ; 
        y = p[1] ;
        return *this ; 
    }

    void Print(FILE *fp=0) ; 
} ; 


class CS_VECTOR2D {
public:
    union {
        double v[2] ; 
        struct {
            double x ; 
            double y ;
        } ;
    } ;


    CS_VECTOR2D() ;

    CS_VECTOR2D(double *vec) : x(vec[0]), y(vec[1]) {}  

    CS_VECTOR2D(double i, double j) : x(i), y(j) {} 

    CS_VECTOR2D(const CS_POINT2D &p) ; 

    CS_VECTOR2D(const CS_POINT2D &p1, const CS_POINT2D &p2) ; 

    ~CS_VECTOR2D() ;

    //! Rotates the vector by alpha radians
    CS_VECTOR2D &Rotate(double alpha) ; 

    //! reverses the direction of the vector
    CS_VECTOR2D &Reverse() ; 

    //! returns a unit vector 
    CS_VECTOR2D Unit() ; 
    
    //! returns a left perpendicular vector 
    /*!
        The vector returned is the same magnitude as the base vector. There
        is no normalization done to return a unit vector
     */
    CS_VECTOR2D RightPerp() ; 
    
    //! returns a right perpendicular vector
    /*!
        The vector returned is the same magnitude as the base vector. There
        is no normalization done to return a unit vector
     */
    CS_VECTOR2D LeftPerp() ;  
    
    //! returns a vector normal to *this in arbitrary direction
    CS_VECTOR ArbNorm3D() ; 
                              

    //! Magnitude of the vector
    double Mag() const ; 
    
    // Returns the angle between the two vectors in radians.
    /*!
        \param b the second vector to test angle against

        The dot product of the two vectors is used to calculate
        the angle between the two vectors using the formula:
        \f$ {x*y}\frac{|x|*|y|}=cos(\alpha)\f$
        The result is always in the range \f$[0,\pi]\f$ unless
        one or both of the vectors has zero length in which case
        -RADIAN360 is returned to indicate the error (which is 
        the same as returning 0 degrees).
     */
    double Angle(const CS_VECTOR2D &b) ; // returns dot product based angle
    
    //! +ve/-ve rotation angle from *this to b in radians
    /*!
        \param b the second vector to test against

        This will return the angle in radians required to rotate the base
        vector so that it points in the same direction as the b vector.
        The range of the value returned is \f$[-\pi,\pi]\f$
     */
    double TurnAngle(const CS_VECTOR2D &b) ; 

    //! Returns angle in radians vector makes with the XY plane
    double AngleXY() ;

    //! returns true if each component matches within current tolerance
    int operator==(const CS_VECTOR2D &vec) ;   

    // point by point tolerance comparison 
    int operator!=(const CS_VECTOR2D &vec) ;   

    // convert point to vector
    CS_VECTOR2D &operator=(const CS_POINT2D &p) ; 

    //! add the two vectors
    CS_VECTOR2D  operator+(const CS_VECTOR2D &w) ; 

    //! add point to the vector components
    CS_VECTOR2D  operator+(const CS_POINT2D &p) ; 

    //! subtract the two vectors
    CS_VECTOR2D  operator-(const CS_VECTOR2D &w) ;
    
    //! Subtracts the point from the vector components
    CS_VECTOR2D  operator-(const CS_POINT2D &p) ; 

    //! Returns a vector in the reverse direction
    CS_VECTOR2D operator-() ; 
    
    //! scale each vector component by s
    CS_VECTOR2D operator*(double s) ; 

    //! scale each vector component by s
    CS_VECTOR2D &operator*=(double s) ;

    // returns the 3D cross product vector 
    CS_VECTOR  operator*(const CS_VECTOR2D &w) ; 

    void Print(FILE *fp=0) ; 
} ;


// Create vectors from circular and cylindrical coordinates
CS_POINT2D CS_POINT2D_CIR(double r, double theta) ;

CS_VECTOR2D CS_VECTOR2D_CIR(double r, double theta) ;

CS_VECTOR2D operator*(double s, CS_VECTOR2D &v) ; // scaling operation

double ZCross(const CS_VECTOR2D &a, const CS_VECTOR2D &b) ; 

CS_VECTOR CS_CrossProduct(const CS_VECTOR &va, const CS_VECTOR &vb) ; 

double CS_DotProduct(const CS_VECTOR2D &a, const CS_VECTOR2D &b) ; 

double DistanceSquared(const CS_POINT2D &p1, const CS_POINT2D &p2)  ;

double CS_Distance(const CS_POINT2D &a, const CS_POINT2D &b) ; 



// tolerance point comparison, if the tolerance pointer is NULL
// then the default tolerance value is used
// int tol_pntCompEQ(const CS_POINT2D &pa, const CS_POINT2D &pb, double *tol=0) ;
// use this instead (defined elsewhere) int tcomp_PointsEQ(const double *p1,const double *p2, const double &tol) ;



////////////////////////////////////////////////////////////////////////////
// 3 Dimensional points and vectors
////////////////////////////////////////////////////////////////////////////


class CS_POINT {
public:

    union {
        double p[3] ; 
        struct {
            double x ; 
            double y ;
            double z ;
        } ;
    } ;


    CS_POINT() {x = 0.0; y = 0.0; z = 0.0 ; } 

    CS_POINT(const CS_VECTOR2D &v2) { x=v2.x; y=v2.y; z=0.0; }

    CS_POINT(const CS_POINT2D &v2) { x=v2.x; y=v2.y; z=0.0; }

    CS_POINT(const CS_VECTOR &v) ; 

    CS_POINT(double *pnt) : x(pnt[0]), y(pnt[1]), z(pnt[2]) {} 

    CS_POINT(double i, double j, double k=0.0) : x(i), y(j), z(k) {} 

    CS_POINT &operator=(const CS_POINT2D &a) 
    {
        x = a.x ; 
        y = a.y ; 
        z = 0.0 ; 
        return *this ; 
    }


    CS_POINT &operator=(const CS_VECTOR2D &a) 
    {
        x = a.x ; 
        y = a.y ; 
        z = 0.0 ; 
        return *this ; 
    }

    //! convert vector to point
    CS_POINT &operator=(const CS_VECTOR &a) ;

    CS_POINT  operator*(double s) ; 
    
    CS_POINT  operator/(double d) ; 

    CS_POINT  operator-() ;

    CS_POINT  operator-(const CS_POINT &pnt) const ; 

    CS_POINT  operator-(const CS_VECTOR &v) const ; 

    CS_POINT  operator+(const CS_VECTOR &v) ; 

    CS_POINT  operator+(const CS_POINT &pnt) ; 

    CS_POINT& operator+=(const CS_POINT &pnt) ; 

    CS_POINT& operator-=(const CS_POINT &pnt) ; 

    CS_POINT& operator+=(const CS_VECTOR &pnt) ; 

    CS_POINT& operator-=(const CS_VECTOR &pnt) ; 

    CS_POINT& operator/=(const double &s) ; 

    CS_POINT& operator*=(const double &s) ; 

    double operator*(const CS_POINT &pnt) ; // dot product

    int operator==(const CS_POINT &pnt) ; 

    int operator!=(const CS_POINT &pnt) ; 

    CS_POINT &Set(double xv=0.0, double yv=0.0, double zv=0.0)
    {
        x = xv ; 
        y = yv ;
        z = zv ;
        return *this ; 
    }

    CS_POINT &Set(double *p)
    {
        x = p[0] ; 
        y = p[1] ;
        z = p[2] ;
        return *this ; 
    }


    void Print(FILE *fp=0) ; 
} ; 


typedef list<CS_POINT> CS_POINTList ;
typedef list<CS_POINT>::iterator CS_POINTListItr ;

class CS_VECTOR {
public:
    union {
        double v[3] ; 
        struct {
            double x ; 
            double y ;
            double z ;
        } ;
    } ;


    CS_VECTOR() {x = 0.0; y = 0.0; z = 0.0 ; }  

    CS_VECTOR(const CS_VECTOR2D &v2) { x=v2.x; y=v2.y; z=0.0; }

    CS_VECTOR(const CS_POINT2D &v2) { x=v2.x; y=v2.y; z=0.0; }

    CS_VECTOR(double *vec) : x(vec[0]) , y(vec[1]), z(vec[2]) {} 

    CS_VECTOR(double i, double j, double k=0.0) : x(i), y(j), z(k) {} 

    CS_VECTOR(const CS_POINT &p) ; 

    //! Create vector from p1 to p2
    CS_VECTOR(const CS_POINT &p1, const CS_POINT &p2) ; 

    ~CS_VECTOR() ;

    //! Rotate the vector in 3D space by given radian angles
    /*!
        \param alpha rotation angle in XY plane in radians
        \param beta rotation angle in ZX plane in radians
        \param phi rotation angle in YZ plane in radians
        \return reference to the vector after the rotation.

        The *this vector is modified by this operation.
     */
    CS_VECTOR &Rotate(double alpha, double beta=0.0, double phi=0.0) ; 

    //! reverses the direction of the vector
    CS_VECTOR &Reverse() ; 

    //! returns a unit vector 
    CS_VECTOR Unit() const ; 
    
    //! returns a right perpendicular vector 
    /*!
        The vector returned is the same magnitude as the base vector. There
        is no normalization done to return a unit vector. Also this happens
        in the XY plane. The Z component is ignored in generating the right
        perpendicular vector.
     */
    CS_VECTOR RightPerp() ; 
    
    //! returns a left perpendicular vector
    /*!
        The vector returned is the same magnitude as the base vector. There
        is no normalization done to return a unit vector. Also this happens
        in the XY plane. The Z component is ignored in generating the right
        perpendicular vector.
     */
    CS_VECTOR LeftPerp() ;  
    
    //! returns a vector normal to *this in arbitrary direction
    CS_VECTOR ArbNorm3D() ; 

    //! Returns magnitude of the vector
    double Mag(void) const ; 

    // Returns the angle between the two vectors in radians.
    /*!
        \param b the second vector to test angle against

        The dot product of the two vectors is used to calculate
        the angle between the two vectors using the formula:
        \f$ \frac{\vec{x} \cdot \vec{y}}{\|x\| \|y\|}=cos(\alpha) \f$
        The result is always in the range \f$[0,\pi]\f$ unless
        one or both of the vectors has zero length in which case
        -RADIAN360 is returned to indicate the error (which is 
        the same as returning 0 degrees).
     */
    double Angle(const CS_VECTOR &b) ; // returns dot product based angle
    
    //! +ve/-ve rotation angle from *this to b in radians
    /*!
        \param b the second vector to test against

        This will return the angle in radians required to rotate the base
        vector so that it points in the same direction as the b vector.
        The range of the value returned is \f$[-\pi,\pi]\f$
     */
    double TurnAngle(const CS_VECTOR &b) ; 

    //! returns the angle the vector makes on the XY plane in radians
    double AngleXY() ;

    //! returns the angle the vector makes on the ZX plane in radians
    double AngleZX() ;

    //! returns the angle the vector makes on the YZ plane in radians
    double AngleYZ() ;


    //! returns true if the vectors are parallel
    /*!
        If the two parallels point in the same direction or in the exact 
        opposite directions then it returns true, otherwise the function
        returns false. 

        The test is done using tolerance. 
     */
    bool Parallel(const CS_VECTOR &b) ;

    //! Same as Parallel() but both vectors must be normalized unit vectors
    bool CS_VECTOR::UnitVecsParallel(const CS_VECTOR &b) ;


    //! tolerance comparison for equality
    int operator==(const CS_VECTOR &vec) const ;   

    //! tolerance comparison for inequality
    int operator!=(const CS_VECTOR &vec) const;   

    //! convert point to vector
    CS_VECTOR &operator=(const CS_POINT &p) ; 

    //! The z component is set to zero
    CS_VECTOR &operator=(const CS_POINT2D &a) 
    {
        x = a.x ; 
        y = a.y ; 
        z = 0.0 ; 
        return *this ; 
    }

    //! The z component is set to zero
    CS_VECTOR &operator=(const CS_VECTOR2D &a)
    {
        x = a.x ; 
        y = a.y ; 
        z = 0.0 ; 
        return *this ; 
    }

    CS_VECTOR  operator+(const CS_VECTOR &w) const ; 

    CS_VECTOR  operator+(const CS_POINT &p) const ; 

    CS_VECTOR  operator-(const CS_VECTOR &w) const ; 

    CS_VECTOR  operator-(const CS_POINT &p) const ; 

    CS_VECTOR  operator-() const ; 

    CS_VECTOR  operator*(const double &s) const ; // scale

    //! returns the cross product of *this and w vectors
    CS_VECTOR  operator*(const CS_VECTOR &w) const ; 

    CS_VECTOR  operator*(CS_VECTOR &w) const  ; 


    // oeprator functions which modify the vector
    CS_VECTOR& operator+=(const CS_POINT &pnt) ; 

    CS_VECTOR& operator-=(const CS_POINT &pnt) ; 

    CS_VECTOR& operator+=(const CS_VECTOR &pnt) ; 

    CS_VECTOR& operator-=(const CS_VECTOR &pnt) ; 

    CS_VECTOR& operator/=(const double &s) ; 

    CS_VECTOR& operator*=(const double &s) ; 

    void Print(FILE *fp=0) ; 
} ;


// Create vectors from circular and cylindrical coordinates

//! Define point with standard spherical coordinates
CS_POINT CS_POINT_SPHERE(double r, double theta, double phi) ;

//! Define point with standard cylindrical coordinates
CS_POINT CS_POINT_CYL(double r, double phi, double z) ;

//! Define vector with standard spherical coordinates
CS_VECTOR CS_VECTOR_SPHERE(double r, double theta, double phi) ;

//! Define vector with standard cylindrical coordinates
CS_VECTOR CS_VECTOR_CYL(double r, double phi, double z) ;

//! scale vector by s
CS_VECTOR operator*(double s, CS_VECTOR &v) ; // scaling operation

//! Returns just the Z component of the cross product of the two vectors
double ZCross(const CS_VECTOR &a, const CS_VECTOR &b) ; 

//! Returns dot product of the two vectors
double CS_DotProduct(const CS_VECTOR &va, const CS_VECTOR &vb) ;  

//! Returns the square of the distance between the two points
double DistanceSquared(const CS_POINT &p1, const CS_POINT &p2) ;

//! Returns the distance between the two points
double CS_Distance(const CS_POINT &a, const CS_POINT &b)  ; 

//! XY plane projection distance between the two points
double CS_Distance2D(const CS_POINT &p1, const CS_POINT &p2) ;

//! Returns the bisector of v1 and v2 (vector in between v1 and v2) 
CS_VECTOR CS_BisectorVector(const CS_VECTOR &v1, const CS_VECTOR &v2)  ; 

//! Returns the bisector of v1 and v2 (vector in between v1 and v2) 
CS_VECTOR2D CS_BisectorVector(const CS_VECTOR2D &v1, const CS_VECTOR2D &v2) ; 

//! tolerance point comparison, if the tolerance pointer is NULL then default tolerance is used
// int tol_pntCompEQ(const CS_POINT &pa, const CS_POINT &pb, double *tol=0) ;
// Use this instead   int tcomp_PointsEQ(const double *p1,const double *p2, const double &tol) ;


//! An array of points definition
typedef vector<CS_POINT> CS_PointVec ; 
typedef list<CS_POINT> CS_PointList ; 
typedef CS_PointList::iterator CS_PointListItr ; 

//! Creates an arbitrary normal vector to the vector v
CS_VECTOR CS_ArbNorm3D(const CS_VECTOR &v) ; 


#endif