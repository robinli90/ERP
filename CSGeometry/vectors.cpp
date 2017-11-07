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
// vectors.cpp
#include <stdio.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_matrices.h"


// Global error string space
char szGeomErrString[4096] ; 



///////////////////////////////////////////
// CS_VECTOR routines
///////////////////////////////////////////

CS_VECTOR::CS_VECTOR(const CS_POINT &p)
{
    v[0] = p.p[0] ; 
    v[1] = p.p[1] ; 
    v[2] = p.p[2] ; 
}

CS_VECTOR::CS_VECTOR(const CS_POINT &p1, const CS_POINT &p2)
{
    v[0] = p2.p[0] - p1.p[0] ; 
    v[1] = p2.p[1] - p1.p[1] ; 
    v[2] = p2.p[2] - p1.p[2] ; 
}

CS_VECTOR::~CS_VECTOR()
{
}

CS_VECTOR &CS_VECTOR::operator=(const CS_POINT &p)  
{
    v[0] = p.p[0] ; 
    v[1] = p.p[1] ; 
    v[2] = p.p[2] ; 

    return *this ; 
}


CS_VECTOR CS_VECTOR::operator+(const CS_VECTOR &w) const 
{
    CS_VECTOR u ; 
    u.v[0] = v[0] + w.v[0] ; 
    u.v[1] = v[1] + w.v[1] ; 
    u.v[2] = v[2] + w.v[2] ; 
    return u ; 
}

CS_VECTOR CS_VECTOR::operator+(const CS_POINT &w) const
{
    CS_VECTOR u ; 
    u.v[0] = v[0] + w.p[0] ; 
    u.v[1] = v[1] + w.p[1] ; 
    u.v[2] = v[2] + w.p[2] ; 
    return u ; 
}

CS_VECTOR CS_VECTOR::operator-() const
{
    CS_VECTOR n ; 
    n.x = -x ; 
    n.y = -y ; 
    n.z = -z ;
    return n ; 
}

CS_VECTOR CS_VECTOR::operator-(const CS_VECTOR &w) const   
{
    CS_VECTOR u ; 
    u.v[0] = v[0] - w.v[0] ; 
    u.v[1] = v[1] - w.v[1] ; 
    u.v[2] = v[2] - w.v[2] ; 
    return u ; 
}

CS_VECTOR CS_VECTOR::operator-(const CS_POINT &w) const 
{
    CS_VECTOR u ; 
    u.v[0] = v[0] - w.p[0] ; 
    u.v[1] = v[1] - w.p[1] ; 
    u.v[2] = v[2] - w.p[2] ; 
    return u ; 
}

int CS_VECTOR::operator==(const CS_VECTOR &vec) const 
{
    if (tcomp_NEQ(v[0], vec.v[0]) ||
        tcomp_NEQ(v[1], vec.v[1]) || 
        tcomp_NEQ(v[2], vec.v[2]))
        return 0 ; 
    return 1 ; 
}

int CS_VECTOR::operator!=(const CS_VECTOR &vec) const  
{
    if (tcomp_NEQ(v[0], vec.v[0]) ||
        tcomp_NEQ(v[1], vec.v[1]) ||
        tcomp_NEQ(v[2], vec.v[2]))
        return 1 ; 
    return 0 ; 
}

double CS_VECTOR::Mag(void) const 
{
    return sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])) ;
}

CS_VECTOR CS_VECTOR::Unit() const
{
    CS_VECTOR uv ; 
    uv = *this ; 
    double mag = Mag() ; 
    // TO DO - if the if tests out that the magnitude is zero
    // then we should do another test to see if it makes sense
    // to attempt to stretch the vector out to a unit value. 
    // For example testing each component for exact 0 equality
    // and seeing if one component != 0 and then setting the 
    // unit vector to point in that direction. Have to think
    // about this a little more.
    if (tcomp_NEZ(mag))
    {
        uv.v[0] = v[0] / mag ; 
        uv.v[1] = v[1] / mag ; 
        uv.v[2] = v[2] / mag ; 
    }
    else 
    {
        uv.v[0] = 0.0 ; 
        uv.v[1] = 0.0 ; 
        uv.v[2] = 0.0 ; 
    }
    return uv ; 
}

bool CS_VECTOR::Parallel(const CS_VECTOR &b)
{
    CS_VECTOR va = this->Unit() ; 
    CS_VECTOR vb = b.Unit() ; 
    return va.UnitVecsParallel(vb) ;
}

bool CS_VECTOR::UnitVecsParallel(const CS_VECTOR &b)
{
    if (tcomp_EQ(fabs(CS_DotProduct(*this, b)), 1.0)) 
        return true ; 
    return false ; 
}



CS_VECTOR &CS_VECTOR::Reverse()
{
    v[0] = -v[0] ; 
    v[1] = -v[1] ; 
    v[2] = -v[2] ; 
    return *this ; 
}

// returns dot product based angle
double CS_VECTOR::Angle(const CS_VECTOR &b) 
{
    // take the dot product
    //   x.y = |x||y|cos(t)
    double mthis = Mag() ; 
    double bmag = b.Mag() ; 
    double mag = mthis * b.Mag() ; 
    if (mag != 0)
    {
        mag = CS_DotProduct(*this, b) / mag ; 
        if (mag >= 1.0)
            return 0.0 ; 
        if (mag <= -1.0)
            return RADIAN180 ; 
        return acos(mag) ; 
    }
    return -RADIAN360 ; // error condition (equivalent to 0 degrees)
}

// Returns the angle that the base vector must be turned to end up
// pointing in the same direction as the b vector. -ve values rotate
// to the right (or CW) and +ve values rotate to the left (CCW)
double CS_VECTOR::TurnAngle(const CS_VECTOR &b)
{
    double angle = Angle(b) ; 
    if (ZCross(*this, b) >= 0.0)
        return angle ; 
    return -angle ; 
}

// Return the angle that the vector makes in cartesian coordinates
// when projected onto the X-Y plane, this is the rotation about the Z axis
double CS_VECTOR::AngleXY() 
{
    return mod2PI(atan2(v[1], v[0])) ; 
    /*
    double a, x, y ; 
    x = v[0] ;
    y = v[1] ;

    // check for vertical case
    if (tcomp_EQZ(x))
    {
        if (y > 0)
            a = RADIAN90 ;
        else // Else y negative
            a = -RADIAN90 ;
    }
    else
    {
        a = atan (y / x) ; 
        if (x < 0)
            a += RADIAN180 ; 
    }
    return a ; 
    */
}


// Return the angle that the vector makes in cartesian coordinates
// when projected onto the X-Z plane, this is the rotation about the Y axis
double CS_VECTOR::AngleZX() 
{
    return mod2PI(atan2(v[0], v[2])) ; 
    /*
    double a, x, y ; 
    x = v[2] ;
    y = v[0] ;

    // check for vertical case
    if (tcomp_EQZ(x))
    {
        if (y > 0)
            a = RADIAN90 ;
        else // Else y negative
            a = -RADIAN90 ;
    }
    else
    {
        a = atan (y / x) ; 
        if (x < 0)
            a += RADIAN180 ; 
    }
    return a ; 
    */
}

// Return the angle that the vector makes in cartesian coordinates
// when projected onto the Y-Z plane, this is the rotation about the X axis
double CS_VECTOR::AngleYZ() 
{
    return mod2PI(atan2(v[2], v[1])) ; 
    /*
    double a, x, y ; 
    x = v[1] ;
    y = v[2] ;

    // check for vertical case
    if (tcomp_EQZ(x))
    {
        if (y > 0)
            a = RADIAN90 ;
        else // Else y negative
            a = -RADIAN90 ;
    }
    else
    {
        a = atan (y / x) ; 
        if (x < 0)
            a += RADIAN180 ; 
    }
    return a ; 
    */
}

CS_VECTOR &CS_VECTOR::Rotate(double alpha, double beta, double phi) 
{
    // First create the Rotation matrix for each of the angles
    CS_MTX3 m(alpha, beta, phi) ; 
    *this = m * (*this) ; 
    return *this ; 
}


// Returns right perpendicular vector rotation in the XY plane 
CS_VECTOR CS_VECTOR::RightPerp()
{
    CS_VECTOR rpv ; 
    rpv.v[0] = v[1] ;
    rpv.v[1] = -v[0] ;
    return rpv ; 
}

// Returns right perpendicular vector rotation in the XY plane 
CS_VECTOR CS_VECTOR::LeftPerp()
{
    CS_VECTOR lpv ; 
    lpv.v[0] = -v[1] ;
    lpv.v[1] = v[0] ;
    return lpv ; 
}


CS_VECTOR CS_VECTOR::operator*(const double &s) const
{
    CS_VECTOR r ; 
    r.v[0] = v[0] * s ; 
    r.v[1] = v[1] * s ; 
    r.v[2] = v[2] * s ; 
    return r ; 
}

CS_VECTOR &CS_VECTOR::operator*=(const double &s) 
{
    v[0] *= s ; 
    v[1] *= s ; 
    v[2] *= s ; 
    return *this ; 
}

CS_VECTOR &CS_VECTOR::operator/=(const double &s)
{
    v[0] /= s ; 
    v[1] /= s ; 
    v[2] /= s ; 
    return *this ; 
}

CS_VECTOR &CS_VECTOR::operator+=(const CS_VECTOR &b)
{
    v[0] += b.x ; 
    v[1] += b.y ; 
    v[2] += b.z ; 
    return *this ; 
}

CS_VECTOR &CS_VECTOR::operator-=(const CS_VECTOR &b)
{
    v[0] -= b.x ; 
    v[1] -= b.y ; 
    v[2] -= b.z ; 
    return *this ; 
}

CS_VECTOR &CS_VECTOR::operator+=(const CS_POINT &b)
{
    v[0] += b.x ; 
    v[1] += b.y ; 
    v[2] += b.z ; 
    return *this ; 
}

CS_VECTOR &CS_VECTOR::operator-=(const CS_POINT &b)
{
    v[0] -= b.x ; 
    v[1] -= b.y ; 
    v[2] -= b.z ; 
    return *this ; 
}




CS_VECTOR operator*(double s, CS_VECTOR &v) 
{
    CS_VECTOR r = v * s ; 
    return r ; 
}


// cross product
CS_VECTOR CS_VECTOR::operator*(const CS_VECTOR &w) const 
{
    CS_VECTOR r ; 
    r.v[0] = (v[1] * w.v[2]) - (v[2] * w.v[1]) ; 
    r.v[1] = (v[2] * w.v[0]) - (v[0] * w.v[2]) ; 
    r.v[2] = (v[0] * w.v[1]) - (v[1] * w.v[0]) ; 
    return r ; 
}

CS_VECTOR CS_VECTOR::operator*(CS_VECTOR &w) const
{
    CS_VECTOR r ; 
    r.v[0] = (v[1] * w.v[2]) - (v[2] * w.v[1]) ; 
    r.v[1] = (v[2] * w.v[0]) - (v[0] * w.v[2]) ; 
    r.v[2] = (v[0] * w.v[1]) - (v[1] * w.v[0]) ; 
    return r ; 
}

CS_VECTOR CS_CrossProduct(const CS_VECTOR &va, const CS_VECTOR &vb)
{
    return va * vb ; 
}

// Returns an arbitrary normal vector to the base vector in 3D space
// This vector is arbitrary since it can go in any direction
// on the plane which v (base vector) is normal to. 
// v below is *this vector, see notes RR-Vol1 pgs 40-45
CS_VECTOR CS_VECTOR::ArbNorm3D() 
{
    CS_VECTOR n ; // resultant normal vector
    if (tcomp_EQZ(Mag()))
        return n ; // no solution

    // The special cases we have to deal with are if v is any of
    // the following  (a,0,0) (0,a,0) (0,0,a) (a,a,0) (a,0,a) (0,a,a) 
    // Note: the (0,0,0) case was handled above with the magnitude test
    

    if (tcomp_NEZ(v[0]))
    {   // (a,0,0) (a,a,0) (a,0,a) (a,a,a) 
        if (tcomp_NEZ(v[1]))
        {   // (a,a,a) (a,a,0)
            // An XY plane vector will be our result
            // Use -1 + 1 + 0 = 0
            n.v[0] = -1 / v[0] ; 
            n.v[1] = 1 / v[1] ; 
            n.v[2] = 0.0 ; 
        }
        else if (tcomp_NEZ(v[2]))
        {   // (a,0,a) 
            // Use -1 + 0 + 1 = 0
            n.v[0] = -1 / v[0] ; 
            n.v[1] = 0.0 ;
            n.v[2] = 1 / v[2] ; 
        }
        else
        {   // (a,0,0) 
            // Use -1 + 0 + 1 = 0
            n.v[0] = 0.0 ; 
            n.v[1] = 1.0 ;
            n.v[2] = 1.0 ; 
        }
    }
    else if (tcomp_NEZ(v[1]))
    {   // (0,a,0) (0,a,a) 
        if (tcomp_NEZ(v[2]))
        {   // (0,a,a)
            // Use 0 - 1 + 1 = 0
            n.v[0] = 0.0 ; 
            n.v[1] = -1 / v[1] ; 
            n.v[2] = 1 / v[2] ; 
        }
        else 
        {   // (0,a,0) 
            // Use 1 + 0 + 1 = 0
            n.v[0] = 1.0 ; 
            n.v[1] = 0.0 ;
            n.v[2] = 1.0 ; 
        }
    }
    else
    {   // (0,0,a)
        n.v[0] = 1.0 ; 
        n.v[1] = 1.0 ; 
        n.v[0] = 0.0 ;
    }
    return n.Unit() ; 
}

void CS_VECTOR::Print(FILE *fp)
{
    if (!fp)
        fp = fpDebugOut ; 
    fprintf(fp, "(%.12lf, %.12lf, %.12lf)", v[0], v[1], v[2]) ; 
}


double CS_DotProduct(const CS_VECTOR &a, const CS_VECTOR &b) 
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z)) ;
}

double CS_DotProduct(const CS_POINT &pa, const CS_POINT &pb)
{
    return pa.x * pb.x + pa.y * pb.y + pa.z * pb.z ; 
}

double ZCross(const CS_VECTOR &a, const CS_VECTOR &b) 
{
    return (a.x * b.y) - (a.y * b.x) ; 
}

double DistanceSquared(const CS_POINT &p1, const CS_POINT &p2) 
{
    CS_POINT p3 = p2 - p1 ; 
    return ((p3.x * p3.x) + (p3.y * p3.y) + (p3.z * p3.z)) ;
}

double CS_Distance(const CS_POINT &p1, const CS_POINT &p2) 
{
    CS_POINT p3 ; 
    p3 = p2 - p1 ; 
    return sqrt((p3.x * p3.x) + (p3.y * p3.y) + (p3.z * p3.z)) ;
}


//! Returns the bisector of v1 and v2 (vector in between v1 and v2) 
CS_VECTOR CS_BisectorVector(const CS_VECTOR &v1, const CS_VECTOR &v2) 
{
    CS_VECTOR v1u = v1 ;
    CS_VECTOR v2u = v2 ;
    v1u = v1u.Unit() ; 
    v2u = v2u.Unit() ; 

    CS_VECTOR vbi = v1u + v2u ; 
    return vbi.Unit() ; 
}


//! Returns the bisector of v1 and v2 (vector in between v1 and v2) 
CS_VECTOR2D CS_BisectorVector(const CS_VECTOR2D &v1, const CS_VECTOR2D &v2)
{
    CS_VECTOR2D v1u = v1 ;
    CS_VECTOR2D v2u = v2 ;
    v1u = v1u.Unit() ; 
    v2u = v2u.Unit() ; 

    CS_VECTOR2D vbi = v1u + v2u ; 
    return vbi.Unit() ; 
}



// Create a vector from circular coordinates
CS_VECTOR CS_VECTOR_SPHERE(double r, double theta, double phi)
{
    CS_VECTOR vr ; // resultant CS_VECTOR
    vr.x = r * sin(theta) * cos(phi) ; 
    vr.y = r * sin(theta) * sin(phi) ; 
    vr.z = r * cos(theta) ; 
    return vr ; 
}

// Create vector from cylindrical coordinates
CS_VECTOR CS_VECTOR_CYL(double r, double phi, double z)
{
    CS_VECTOR vr ; // resultant CS_VECTOR
    vr.x = r * cos(phi) ; 
    vr.y = r * sin(phi) ; 
    vr.z = z ; 
    return vr ; 
}


CS_VECTOR CS_ArbNorm3D(CS_VECTOR &v)
{
    CS_VECTOR arbv ; 
    if (tcomp_EQZ(v.Mag()))
    {
        arbv.x = 0 ;
        arbv.y = 0 ;
        arbv.z = 0 ;
    }
    else 
    {
        //  The special cases we have to deal with are if v is any of
        //  the following  (a,0,0) (0,a,0) (0,0,a) (a,a,0) (a,0,a) (0,a,a)
        //  Note: the (0,0,0) case was handled above with the magnitude test
    
        if (tcomp_NEZ(v.x))
        {
            // (a,0,0) (a,a,0) (a,0,a) (a,a,a)
            if (tcomp_NEZ(v.y)) 
            {
                //  (a,a,a) (a,a,0)
                //  An XY plane vector will be our result
                //  Use -1 + 1 + 0 = 0
                arbv.x = -1 / v.x ;
                arbv.y = 1 / v.y ;
                arbv.z = 0 ;
            }
            else if (tcomp_NEZ(v.z)) 
            {
                //  (a,0,a)
                //  Use -1 + 0 + 1 = 0
                arbv.x = -1 / v.x ;
                arbv.y = 0 ;
                arbv.z = 1 / v.z ;
            }
            else
            {
                // (a,0,0)
                // Use -1 + 0 + 1 = 0
                arbv.x = 0.0 ;
                arbv.y = 1.0 ;
                arbv.z = 1.0 ;
            }
        }
        else if (tcomp_NEZ(v.y)) 
        {
            // (0,a,0) (0,a,a)
            if (tcomp_NEZ(v.z)) 
            {
                // (0,a,a)
                //  Use 0 - 1 + 1 = 0
                arbv.x = 0 ;
                arbv.y = -1 / v.y ;
                arbv.z = 1 / v.z ;
            }
            else
            {
                // (0,a,0)
                // Use 1 + 0 + 1 = 0
                arbv.x = 1 ;
                arbv.y = 0 ;
                arbv.z = 1 ;
            }
        }
        else
        {
            //  (0,0,a)
            arbv.x = 1 ;
            arbv.y = 1 ;
            arbv.z = 0 ;
        }
    }
    return arbv ; 
}