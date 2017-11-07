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
// mathutls.cpp - simple math utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define __mathutls_cpp__

#include "cs_geomdefs.h"
#include "cs_mathutls.h"


#define RMRDEBUG(a)     


#ifndef CW
#define CW  1
#define CCW 0
#endif


// The global output dumping ground
FILE *fpDebugOut = stdout ; 

const double RADIAN30      =  (acos(0.0) / 3.0) ;
const double RADIAN45      =  (acos(0.0) * 0.5) ;
const double RADIAN60      =  (acos(0.0) / 3.0 * 2.0) ;
const double RADIAN90      =  (acos(0.0)) ;
const double RADIAN135     =  (acos(0.0) * 1.5) ;
const double RADIAN180     =  (acos(0.0) * 2.0) ;
const double RADIAN225     =  (acos(0.0) * 2.5) ;
const double RADIAN270     =  (acos(0.0) * 3.0) ; 
const double RADIAN315     =  (acos(0.0) * 3.5) ;
const double RADIAN360     =  (acos(0.0) * 4.0) ; 

const double RADIANStoDEGREES  = (90.0 / acos(0.0)) ;
const double DEGREEStoRADIANS  = (acos(0.0) / 90.0) ;

// const double RADIANStoDEGREES = (180.0 / RADIAN180) ;
// const double DEGREEStoRADIANS = (RADIAN180 / 180.0) ;

double COMPARETOLERANCE = kCOMPARETOLERANCE ;
double RADCOMPARETOLERANCE = kRADCOMPARETOLERANCE ;

double SetCmpTol(double tolerance) 
{
    double oldtol = COMPARETOLERANCE ;
    COMPARETOLERANCE = tolerance ; 
    return oldtol ; 
}

double ReSetCmpTol() 
{
    double oldtol = COMPARETOLERANCE ;
    COMPARETOLERANCE = kCOMPARETOLERANCE ; 
    return oldtol ; 
}


CS_Tolerance::CS_Tolerance(int m)
{
    mode = m ; 
    oldtol = COMPARETOLERANCE ; 
    curtol = COMPARETOLERANCE ; 
}

CS_Tolerance::CS_Tolerance(double tol, int m)
{
    oldtol = COMPARETOLERANCE ; 
    curtol = COMPARETOLERANCE = tol ; 
    mode = m ; 
}

CS_Tolerance::~CS_Tolerance()
{
    if (mode == TOLERANCE_RESTORE)
        COMPARETOLERANCE = oldtol ; 
}

double CS_Tolerance::Set(double tol)
{
    double lasttol = COMPARETOLERANCE ; 
    curtol = COMPARETOLERANCE = tol ; 
    return lasttol ; 
}

double CS_Tolerance::Get()
{
    return curtol ; 
}

double CS_Tolerance::Scale(double s)
{
    double lasttol = curtol ; 
    curtol = curtol * s ; 
    COMPARETOLERANCE = curtol ;
    return lasttol ; 
}

double CS_Tolerance::Default()
{
    double lasttol = curtol ; 
    // Set the default compare tolerance
    // k=constant
    curtol = COMPARETOLERANCE = kCOMPARETOLERANCE ;
    return lasttol ; 
}

double CS_Tolerance::Restore()
{
    curtol = COMPARETOLERANCE = oldtol ;
    return curtol ; 
}

//! Round the value d to n decimal places.
/*!
    \param d the number to be rounded
    \param n the number of decimal digits to round to (10^-n)

    This function works as follows:
    
   -# Shift the decimal to the right of the digit to be rounded by 
    multiplying by 10^n where n = the number of decimal places to round to
   -# Truncate the number up or down depending on whether the original 
    number is positive or negative.
   -# Subtract the original value and the truncated value to see if the 
    remainder is > 0.5 and if so add 1 to the result (-1 if negative)
   -# Scale the value back by dividing by the original multiplier
   
   This will generate a result that is likely close to what you expect
   but trailing digits (after roundoff offset) are not guaranteed to be zero. 
 */
double RoundTo(double d, int n) 
{
    double x1, x2, r ;
    double pn = pow(10.0, (double)n) ; 
    
    // Want to truncate the number
    x2 = d * pn ; 
    
    if (d > 0.0)
        x1 = floor(x2) ; 
    else
        x1 = ceil(x2) ; 
    
    r = x2 - x1 ; 

    if (fabs(r) >= 0.5)
    {
        if (d > 0.0) 
            x1 += 1.0 ; 
        else
            x1 -= 1.0 ; 
    }
    d = x1 / pn ; 
    return d ; 
}

//! Round double value to nearest integer 
int RoundDouble(double d)
{   // floor
    int a,b ; 
    a = (int)floor(d) ;
    b = (int)ceil(d) ; 
    if (fabs(d - (double)a) > fabs(d - (double)b))
        return b ; 
    return a ;
}
 
// Round integer value to nearest value divisible by r
int RoundInteger(int i, int r) 
{
    int x, y, neg, ret ; 
    double d ; 
    if (r == 0)
        return i ; // can't round so do nothing

    neg = 0 ; 
    if (i < 0)
    {
        neg = 1 ; 
        i = -i ;  // negate i
    }

    r = abs(r) ; // make sure r is positive
    y = i / r ; 
    x = i % r ; 
    // Now we want to determine if x is closer to 0 or r
    // if closer to 0 do nothing and return (x * r) else
    // return (x * r) + r 
    d = (double)r / 2.0 ; 

    if ((double)x > d)
        ret = (y * r) + r ; 
    else
        ret = (y * r) ; 

    if (neg)
        ret = -ret ; 
    
    return ret ; 
}

bool tcomp_EQZ(const double &a)
{
    if (((a - COMPARETOLERANCE) < 0.0) &&
            ((a + COMPARETOLERANCE) > 0.0))
        return true ;
    return false ;
}

bool tcomp_NEZ(const double &a)
{
    if (((a - COMPARETOLERANCE) < 0.0) &&
            ((a + COMPARETOLERANCE) > 0.0))
        return false ;
    return true ;
}


bool tcomp_EQ(const double &a, const double &b)
{
    if ((a > (b - COMPARETOLERANCE)) &&
        (a < (b + COMPARETOLERANCE)))
        return true ;
    return false ;
}

bool tcomp_NEQ(const double &a, const double &b)
{
    if ((a < (b - COMPARETOLERANCE)) ||
        (a > (b + COMPARETOLERANCE)))
        return true ;
    return false ;
}

bool tcomp_LT(const double &a, const double &b)
{
    if (a < (b - COMPARETOLERANCE)) 
        return true ;
    return false ;
}

bool tcomp_GT(const double &a, const double &b)
{
    if (a > (b + COMPARETOLERANCE)) 
        return true ;
    return false ;
}

bool tcomp_LEQ(const double &a, const double &b)
{
    if (a < (b + COMPARETOLERANCE))
        return true ;
    return false ;
}

bool tcomp_GEQ(const double &a, const double &b)
{
    if (a > (b - COMPARETOLERANCE)) 
        return true ;
    return false ;
}



//////////////////////////////////////////////////////////////////////////
// Tolerance compare where the tolerance is passed as a parameter
bool tcomp_EQZ(const double &a, const double &tol)
{
    if (((a - tol) < 0.0) &&
            ((a + tol) > 0.0))
        return true ;
    return false ;
}

bool tcomp_NEZ(const double &a, const double &tol)
{
    if (((a - tol) < 0.0) &&
            ((a + tol) > 0.0))
        return false ;
    return true ;
}


bool tcomp_EQ(const double &a, const double &b, const double &tol)
{
    if ((a > (b - tol)) &&
        (a < (b + tol)))
        return true ;
    return false ;
}

bool tcomp_NEQ(const double &a, const double &b, const double &tol)
{
    if ((a < (b - tol)) ||
        (a > (b + tol)))
        return true ;
    return false ;
}

bool tcomp_LT(const double &a, const double &b, const double &tol)
{
    if (a < (b - tol)) 
        return true ;
    return false ;
}

bool tcomp_GT(const double &a, const double &b, const double &tol)
{
    if (a > (b + tol)) 
        return true ;
    return false ;
}

bool tcomp_LEQ(const double &a, const double &b, const double &tol)
{
    if (a < (b + tol))
        return true ;
    return false ;
}

bool tcomp_GEQ(const double &a, const double &b, const double &tol)
{
    if (a > (b - tol)) 
        return true ;
    return false ;
}


////////////////////////////////////////
////////////////////////////////////////
// Tolerance Double Member Functions  //
////////////////////////////////////////
////////////////////////////////////////
bool TolDbl::operator<(TolDbl &b)  { return tcomp_LT(d, b.d)  ; } 
bool  TolDbl::operator<=(TolDbl &b) { return tcomp_LEQ(d, b.d) ; } 
bool  TolDbl::operator==(TolDbl &b) { return tcomp_EQ(d, b.d)  ; } 
bool  TolDbl::operator!=(TolDbl &b) { return tcomp_NEQ(d, b.d) ; } 
bool  TolDbl::operator>(TolDbl &b)  { return tcomp_GT(d, b.d)  ; } 
bool  TolDbl::operator>=(TolDbl &b) { return tcomp_GEQ(d, b.d) ; } 

// Tolerance Double Friend Functions
bool  operator< (const TolDbl &a, const TolDbl &b)  { return tcomp_LT (a.d, b.d) ; } 
bool  operator<=(const TolDbl &a, const TolDbl &b)  { return tcomp_LEQ(a.d, b.d) ; }
bool  operator==(const TolDbl &a, const TolDbl &b)  { return tcomp_EQ (a.d, b.d) ; }
bool  operator!=(const TolDbl &a, const TolDbl &b)  { return tcomp_NEQ(a.d, b.d) ; }
bool  operator> (const TolDbl &a, const TolDbl &b)  { return tcomp_GT (a.d, b.d) ; }
bool  operator>=(const TolDbl &a, const TolDbl &b)  { return tcomp_GEQ(a.d, b.d) ; }


// Returns true if the two angles represent the same value within tolerance
bool AnglesEqual(double a, double b)
{
    a = mod2PI(a) ; 
    b = mod2PI(b) ; 

    // If they are right at 0 and 2pi then adjust 0 to 2pi and test
    if ((a < RADCOMPARETOLERANCE / 2.0) && (b > (RADIAN360 - RADCOMPARETOLERANCE / 2.0)))
    {
        return true ; 
    }
    else if ((b < RADCOMPARETOLERANCE / 2.0) && (a > (RADIAN360 - RADCOMPARETOLERANCE / 2.0)))
    {
        return true ; 
    }

    return tcomp_EQ(a, b, RADCOMPARETOLERANCE) ; 
}

//! Another method which doesn't call mod2PI if it's not needed
int CS_AnglesEqual(double a1, double a2)
{
    if (tcomp_EQ(a1, a2, RADCOMPARETOLERANCE))
        return 1 ; 

    if (tcomp_GEQ(fabs(a1-a2), RADIAN360, RADCOMPARETOLERANCE))
    {
        a1 = mod2PI(a1) ;
        a2 = mod2PI(a2) ;

        if (tcomp_EQ(a1, a2, RADCOMPARETOLERANCE))
            return 1 ; 
        if (tcomp_EQ(fabs(a1-a2), RADIAN360, RADCOMPARETOLERANCE))
            return 1 ; 
    }
    return 0 ; 
}

//! Adjusts angle so that it is in range [0,2PI)
double mod2PI(double x)
{
    double y = fmod(x, RADIAN360) ; 
    if (y < 0) 
        y += RADIAN360 ; 
    return y ; 
}

//! Returns an angle from (-PI, PI] 
double NormalizeAngle(double phi) 
{
    phi = mod2PI(phi) ;
    if (phi > RADIAN180)
    {   // Then we want to make it negative
        phi -= RADIAN360 ;
    }
    return phi ; 
}


/*!
    \param x the X component of 2D vector
    \param y the Y component of 2D vector
    \return the radian angle of the vector in polar coordinates

    Returns the angle [0,2PI) that a vector starting at the
    origin makes with the cartesian coordinate system.
    Standard positive angles, counterclockwise from the x-axis
    are generated in radians. 
 */
double angle360(double x, double y)
{
   double a ;
   // check for vertical case
   if (tcomp_EQZ(x))
   {
      if (y > 0)
         return (RADIAN90) ;
      else
         return (RADIAN270) ;
   }
   else
   {
      a = fabs(atan (y / x)) ;
      if (tcomp_EQ(a,0.0))
         if (x >= 0.0)
            return 0.0 ;
         else
            return RADIAN180 ;
      if (x > 0 && y > 0)
         return a ; // quad I
      else if (x > 0 && y < 0)
         return (RADIAN360 - a) ; // quad IV
      else if (x < 0 && y > 0)
         return (RADIAN180 - a) ; // quad II
   }
   // x < 0 && y < 0 case, quad III
   return (RADIAN180 + a) ; /* default result */
}


void CopyPoint(double *src, double *dst) 
{
    dst[0] = src[0] ; 
    dst[1] = src[1] ; 
    dst[2] = src[2] ; 
}

// Converts the angle to degrees and rounds to a positive integer value
int AngleIntegerDegrees(double alpha)
{
    int a ; 
    alpha = mod2PI(alpha) ; 
    a = (int)(alpha * 180.0 / RADIAN180)  ; 
    return a ; 
}

/* included angle for the arc given CW or CCW direction from sa->ea */
double arc_sweep(double sa, double ea, int arcdir)
{
    sa = mod2PI(sa) ;
    ea = mod2PI(ea) ; 

   // CCW case being assumed
   if (arcdir == CW)
   {
      if (sa < ea)
         return (RADIAN360 - ea + sa) ;
      else
         return (sa - ea) ;
   }
   else
   {
      if (sa < ea)
         return (ea - sa) ;
      else
         return (RADIAN360 - sa + ea) ;
   }
}

// Returns the chord height of an Arc given the sweep angle and the radius
// Se notes in Geom Algo's RR-Vol1 Pgs 90-93
double chordheight(double rad, double swp) 
{
    double x = sin(swp / 4.0) ; 
    return 2.0 * rad * x * x ; 
}

void crossprod(double *a, double *b, double *c) 
{
    c[0] = (a[1] * b[2]) - (a[2] * b[1]) ; 
    c[1] = (a[2] * b[0]) - (a[0] * b[2]) ; 
    c[2] = (a[0] * b[1]) - (a[1] * b[0]) ; 
}

int PointsEQ(const double *p1, const double *p2)
{
    if (tcomp_NEQ(p1[0], p2[0]) ||
        tcomp_NEQ(p1[1], p2[1]) ||
        tcomp_NEQ(p1[2], p2[2]))
        return 0 ; 
    return 1 ; 
}

int tcomp_PointsEQ(const double *p1, const double *p2,const double &tol)
{
    if (tcomp_NEQ(p1[0], p2[0], tol) ||
        tcomp_NEQ(p1[1], p2[1], tol) ||
        tcomp_NEQ(p1[2], p2[2], tol))
        return 0 ; 
    return 1 ; 
}


int ModuloInc(int counter, int length) 
{
    counter++ ; 
    if (length)
    {   // Then must do modulo logic
        if (counter >= length) 
            counter = 0 ; 
    }
    // otherwise the modulo wrap around will occur in the 
    // accumulator of the processor
    return counter ; 
}  


//! Adds the delta to the u value and wraps around the curve adjusting for 
//! start-end crossovers. Values greater than 1.0 in magnitude simply 
//! end up looping around the curve multiple times. 
double UDeltaClosed(double uv, double delta)
{
    delta = fmod(delta, 1.0) ; 
    uv += delta ; 
    if (uv > 1.0) 
        uv -= 1.0 ; 
    else if (uv < 0.0)
        uv += 1.0 ; 
    return uv ; 
}

//! Moves along an open curve, attempting to move past an end point
//! will stop at the end point.
double UDeltaOpen(double uv, double delta)
{
    uv += delta ; 
    if (uv > 1.0) 
        uv = 1.0 ; 
    else if (uv < 0.0)
        uv = 0.0 ; 
    return uv ; 
}


