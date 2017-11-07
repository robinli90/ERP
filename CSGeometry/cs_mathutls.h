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
// mathutls.h - math utilities

#ifndef __CS_MATHUTLS_H__

#define __CS_MATHUTLS_H__

#ifndef FILE
#include <stdio.h>
#include <stdlib.h>
#endif

#define CS_NOTCLOSED    0x0001
#define CS_INFINITE     0x0002
#define CS_FOUND        0x0004
#define CS_NOTFOUND     0x8000      // also an error indicator
#define CS_OUTOFTOL     0x0008      // out of tolerance 
#define CS_MAXITERS     0x0010      // maximum number of iterations hit
#define CS_FOUNDLIMIT   0x0020      // reached limit radius during search. 

#define FBepsilon     (0.001) 

#define kCOMPARETOLERANCE  (1e-8)   // default compare tolerance for distances
#define kRADCOMPARETOLERANCE  (1e-8)   // default compare tolerance for radian angles

extern double COMPARETOLERANCE ; 
extern double RADCOMPARETOLERANCE ; 
extern FILE *fpDebugOut ; 


#define TOLERANCE_RESTORE       0
#define TOLERANCE_NORESTORE     1

class CS_Tolerance
{
public:
    double oldtol ; 
    double curtol ; 
    int mode ; 

    CS_Tolerance(int mode=TOLERANCE_RESTORE) ; 
    CS_Tolerance(double t, int mode=TOLERANCE_RESTORE) ; 
    ~CS_Tolerance() ;

    double Set(double t) ; 
    double Get() ; 
    double Scale(double s) ; 
    double Default() ; // set the tolerance to the default value
    double Restore() ;
} ;

// Need global variable to store chaining tolerance, would be nice to 
// have it initialized to 

extern const double RADIAN30 ;
extern const double RADIAN45 ; 
extern const double RADIAN60 ;
extern const double RADIAN90 ;
extern const double RADIAN135 ;
extern const double RADIAN180 ;
extern const double RADIAN225 ;
extern const double RADIAN270 ;
extern const double RADIAN315 ;
extern const double RADIAN360 ;

extern const double RADIANStoDEGREES ;
extern const double DEGREEStoRADIANS ;


// extracted from geometry.h
/*
#define RADIAN30        (0.52359877560)
#define RADIAN45        (0.78539816340)
#define RADIAN60        (1.04719755120)
#define RADIAN90        (1.57079632680)
#define RADIAN135       (2.35619449019)
#define RADIAN180       (3.14159265359)
#define RADIAN225       (3.92699081699)
#define RADIAN270       (4.71238898038)
#define RADIAN315       (5.49778714378)
#define RADIAN360       (6.28318530718)

#define RADIANStoDEGREES  (57.2957795131)
#define DEGREEStoRADIANS  (0.0174532925199)
*/

#define CS_ABSOLUTE     0x0000
#define CS_RELATIVE     0x0001
#define CS_MIRROR       0x0002


bool tcomp_EQZ(const double &a) ;
bool tcomp_NEZ(const double &a) ;
bool tcomp_EQ(const double &a, const double &b) ;
bool tcomp_NEQ(const double &a, const double &b) ; 
bool tcomp_LT(const double &a, const double &b) ;
bool tcomp_GT(const double &a, const double &b) ;
bool tcomp_LEQ(const double &a, const double &b) ;
bool tcomp_GEQ(const double &a, const double &b) ;
bool tcomp_EQZ(const double &a, const double &tol) ;
bool tcomp_NEZ(const double &a, const double &tol) ; 
bool tcomp_EQ(const double &a, const double &b, const double &tol) ;
bool tcomp_NEQ(const double &a, const double &b, const double &tol) ;
bool tcomp_LT(const double &a, const double &b, const double &tol) ;
bool tcomp_GT(const double &a, const double &b, const double &tol) ;
bool tcomp_LEQ(const double &a, const double &b, const double &tol) ;
bool tcomp_GEQ(const double &a, const double &b, const double &tol) ;

//! CS_Tolerance double structure
/*!
    Higher level definition of type double variable where the comparison
    operations are defined using the system tolerance. Note, none of
    the arithmetic operations (+,-,*,/,...) are defined. 
 */
struct TolDbl 
{
public:
    double d ; 

    TolDbl() { d=0.0; } ; 
    TolDbl(double x) : d(x) {} ; 
    TolDbl(const TolDbl &tb) {d = tb.d; } ; 

    bool operator<(TolDbl &b)  ; 
    bool operator<=(TolDbl &b) ; 
    bool operator==(TolDbl &b) ; 
    bool operator!=(TolDbl &b) ; 
    bool operator>(TolDbl &b)  ; 
    bool operator>=(TolDbl &b) ; 
} ;

bool operator< (const TolDbl &a, const TolDbl &b) ; 
bool operator<=(const TolDbl &a, const TolDbl &b) ; 
bool operator==(const TolDbl &a, const TolDbl &b) ; 
bool operator!=(const TolDbl &a, const TolDbl &b) ; 
bool operator> (const TolDbl &a, const TolDbl &b) ; 
bool operator>=(const TolDbl &a, const TolDbl &b) ; 

//! Returns true if the two points are equal 
/*!
    \param p1 pointer to double[3] array defining the first test point
    \param p2 pointer to double[3] array defining the second test point
    \return true if the points are equal within the system tolerance

    Note the tolerance defines a box around the the first point that the
    second point must be inside of and not a sphere. The length of the 
    side of the square box is equal to twice the system tolerance. 
 */
int PointsEQ(const double *p1, const double *p2) ;

//! Returns true if the two points are equal within the defined tolerance
/*!
    \param p1 pointer to double[3] array defining the first test point
    \param p2 pointer to double[3] array defining the second test point
    \param tol tolerance value to use instead of the current system tolerance
    \return true if the points are equal within the tolerance value

    Note the tolerance defines a box around the the first point that the
    second point must be inside of and not a sphere. The length of the 
    side of the square box is equal to twice the tolerance. 
 */
int tcomp_PointsEQ(const double *p1,const double *p2, const double &tol) ;


// Returns true if the two angles represent the same value within tolerance
/*!
    \param a first radian angle to test 
    \param b second radian angle to test
    \return if a and b are the same cartesian coordinate angle 

    This function takes the modulo 2PI value of a and b and then 
    does a system tolerance comparison of the two values. It also
    handles the situation where a=0+e and b=2PI-e where e is less 
    than 1/2 the system tolerance and reports these angles as being equal.
 */
bool AnglesEqual(double a, double b) ;


// Returns true if the two angles represent the same value within tolerance
/*!
    \param a first radian angle to test 
    \param b second radian angle to test
    \return if a and b are the same cartesian coordinate angle 

    This version doesn't call mod2PI immediately and thus is 
    slightly more efficient.
 */
int CS_AnglesEqual(double a, double b) ;


//! Adjusts angle so that it is in range [0,2PI)
double mod2PI(double x) ; 

//! Returns an angle from (-PI, PI] 
double NormalizeAngle(double phi) ;

//! Returns vector(x,y) angle in radians
/*!
    \param x the X component of 2D vector
    \param y the Y component of 2D vector
    \return the radian angle of the vector in polar coordinates

    Returns the angle [0,2PI) that a vector starting at the
    origin makes with the cartesian coordinate system.
    Standard positive angles, counterclockwise from the x-axis
    are generated in radians. 
 */
double angle360(double x, double y) ;

//!
double RoundTo(double d, int n) ; 

//! Round double value to nearest integer 
int RoundDouble(double d) ;


//! Divides i by r and returns the nearest integer result taking into 
//! account the decimal fraction portion of the division
int RoundInteger(int i, int r) ;


//! Converts the radian angle to an integer degree value in the range [0,359]
int AngleIntegerDegrees(double alpha) ;

//! Copies the 3D point
/*! 
    \param src pointer to double[3] array defining the source point
    \param dst pointer to double[3] array defining the destination point
 */
void CopyPoint(double *src, double *dst) ; 

//! Returns the chord height of an arc given the sweep angle in radians and the radius
double chordheight(double rad, double swp) ;


//! Returns the included angle for the arc given CW or CCW direction from sa->ea 
/*!
    \param sa the start angle of the arc in radians
    \param ea the end angle of the arc in radians
    \param dir the direction of the arc from sa to ea, use constants CW or CCW
    \return the included angle of the arc sweep in radians 

    This handles crossing over the x axis, for example

        arc_sweep(350 * DEGREEStoRADIANS, 10 * DEGREEStoRADIANS, CCW) ;

    would return a value equal to (20 * DEGREEStoRADIANS)
 */
double arc_sweep(double sa, double ea, int dir) ;


//! Returns the vector cross product c = a x b
/*!
    \param a pointer to double[3] array for the first input vector
    \param b pointer to double[3] array for the second input vector
    \param c pointer to double[3] array for the output crossproduct vector

    Returns the cross product result a x b thus a={1,0,0}, b={0,1,0}
    would result in c being set to {0,0,1}
 */
void crossprod(double *a, double *b, double *c) ;


////////////////////////
// General math routines
////////////////////////

//! returns ((counter + 1) % length) 
int ModuloInc(int counter, int length) ;

double SetCmpTol(double tolerance) ; 
double ReSetCmpTol() ; 

// Gauss-Jordan elimination
// On return matrix A[n,n] is inverted and the solution vectors are in B[n,m]
// m will typically be 1, but this allows mutiple sets of equations to be 
// solved at once if desired
int CS_gaussj(double *A,  // The A[n x n] input matrix
              int n,      // dimension of input matrix A
              double *B,  // right hand side vectors 
              int m)  ;   // number of column vectors to solve for in B


#define MaxVal(a,b)     ((a) > (b) ? (a) : (b))
#define MinVal(a,b)     ((a) < (b) ? (a) : (b))


//! Returns the u value incremented by delta
/*!
    \param u the starting parametric u value in the range [0,1]
    \param delta the incremental parameteric value to add to u
    \return the resultant parameteric u value

    Adds  delta to the u value and wraps around the curve adjusting for 
    start-end crossovers. Values greater than 1.0 in magnitude simply 
    end up looping around the curve multiple times. 
    Thus:
        UDeltaClosed(0.5,  0.2) == 0.7
        UDeltaClosed(0.5, -0.2) == 0.3
        UDeltaClosed(0.5,  0.6) == 0.1
        UDeltaClosed(0.5, -0.6) == 0.9
        UDeltaClosed(0.5,  2.0) == 0.5
        UDeltaClosed(0.5, -1.0) == 0.5  
 */
double UDeltaClosed(double u, double delta) ;

//! Returns the u value incremented by delta
/*!
    \param u the starting parametric u value in the range [0,1]
    \param delta the incremental parameteric value to add to u
    \return the resultant parameteric u value

    Adds delta to the u value stopping if an endpoint is reached

    Thus:
        UDeltaClosed(0.5,  0.2) == 0.7
        UDeltaClosed(0.5, -0.2) == 0.3
        UDeltaClosed(0.5,  0.6) == 0.0
        UDeltaClosed(0.5, -0.6) == 1.0
        UDeltaClosed(0.5,  2.0) == 1.0
        UDeltaClosed(0.5, -1.0) == 0.0  
 */
double UDeltaOpen(double u, double delta) ;

#endif