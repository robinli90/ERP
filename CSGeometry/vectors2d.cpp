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
// vectors2d.cpp
#include <stdio.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_matrices.h"


///////////////////////////////////////////
// CS_VECTOR2D routines
///////////////////////////////////////////
CS_VECTOR2D::CS_VECTOR2D()
{
    v[0] = 0.0 ; 
    v[1] = 0.0 ; 
}

CS_VECTOR2D::CS_VECTOR2D(const CS_POINT2D &p)
{
    x = p.x ; 
    y = p.y ; 
}

CS_VECTOR2D::CS_VECTOR2D(const CS_POINT2D &p1, const CS_POINT2D &p2)
{
    x = p2.x - p1.x ; 
    y = p2.y - p1.y ; 
}

CS_VECTOR2D::~CS_VECTOR2D()
{
}

CS_VECTOR2D &CS_VECTOR2D::operator=(const CS_POINT2D &p)
{
    x = p.x ; 
    y = p.y ; 

    return *this ; 
}


CS_VECTOR2D CS_VECTOR2D::operator+(const CS_VECTOR2D &w)
{
    CS_VECTOR2D u ; 
    u.v[0] = v[0] + w.v[0] ; 
    u.v[1] = v[1] + w.v[1] ; 
    return u ; 
}

CS_VECTOR2D CS_VECTOR2D::operator+(const CS_POINT2D &w)
{
    CS_VECTOR2D u ; 
    u.v[0] = v[0] + w.p[0] ; 
    u.v[1] = v[1] + w.p[1] ; 
    return u ; 
}

CS_VECTOR2D CS_VECTOR2D::operator-()
{
    CS_VECTOR2D n ; 
    n.x = -x ; 
    n.y = -y ; 
    return n ; 
}

CS_VECTOR2D CS_VECTOR2D::operator-(const CS_VECTOR2D &w) 
{
    CS_VECTOR2D u ; 
    u.v[0] = v[0] - w.v[0] ; 
    u.v[1] = v[1] - w.v[1] ; 
    return u ; 
}

CS_VECTOR2D CS_VECTOR2D::operator-(const CS_POINT2D &w)
{
    CS_VECTOR2D u ; 
    u.v[0] = v[0] - w.p[0] ; 
    u.v[1] = v[1] - w.p[1] ; 
    return u ; 
}

int CS_VECTOR2D::operator==(const CS_VECTOR2D &vec)
{
    if (tcomp_EQ(v[0], vec.v[0]) &&
        tcomp_EQ(v[1], vec.v[1]))
        return 1 ; 
    return 0 ; 
}

int CS_VECTOR2D::operator!=(const CS_VECTOR2D &vec)
{
    if (tcomp_EQ(v[0], vec.v[0]) &&
        tcomp_EQ(v[1], vec.v[1]))
        return 0 ; 
    return 1 ; 
}

double CS_VECTOR2D::Mag() const
{
    return sqrt((v[0] * v[0]) + (v[1] * v[1])) ;
}

CS_VECTOR2D CS_VECTOR2D::Unit() 
{
    CS_VECTOR2D uv ; 
    uv = *this ; 
    double mag = Mag() ; 
    // TO DO - if it tests out that the magnitude is zero
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
    }
    return uv ; 
}

CS_VECTOR2D &CS_VECTOR2D::Reverse()
{
    v[0] = -v[0] ; 
    v[1] = -v[1] ; 
    return *this ; 
}

// returns dot product based angle
double CS_VECTOR2D::Angle(const CS_VECTOR2D &b) 
{
    // take the dot product
    //   x.y = |x||y|cos(t)
    double mag = Mag() * b.Mag() ; 
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
double CS_VECTOR2D::TurnAngle(const CS_VECTOR2D &b)
{
    double angle = Angle(b) ; 
    if (ZCross(*this, b) >= 0.0)
        return angle ; 
    return -angle ; 
}

// Return the angle that the vector makes in cartesian coordinates
// when projected onto the X-Y plane, this is the rotation about the Z axis
double CS_VECTOR2D::AngleXY() 
{
    return mod2PI(atan2(v[1], v[0])) ; 
}


CS_VECTOR2D &CS_VECTOR2D::Rotate(double alpha) 
{
    // First create the Rotation matrix for each of the angles
    CS_VECTOR2D u(*this) ; 

    x = u.x * cos(alpha) - u.y * sin(alpha) ; 
    y = u.x * sin(alpha) + u.y * cos(alpha) ; 

    return *this ; 
}


// Returns right perpendicular vector rotation in the XY plane 
CS_VECTOR2D CS_VECTOR2D::RightPerp()
{
    CS_VECTOR2D rpv ; 
    rpv.v[0] = v[1] ;
    rpv.v[1] = -v[0] ;
    return rpv ; 
}

// Returns right perpendicular vector rotation in the XY plane 
CS_VECTOR2D CS_VECTOR2D::LeftPerp()
{
    CS_VECTOR2D lpv ; 
    lpv.v[0] = -v[1] ;
    lpv.v[1] = v[0] ;
    return lpv ; 
}


CS_VECTOR2D CS_VECTOR2D::operator*(double s)
{
    CS_VECTOR2D r ; 
    r.v[0] = v[0] * s ; 
    r.v[1] = v[1] * s ; 
    return r ; 
}

CS_VECTOR2D &CS_VECTOR2D::operator*=(double s)
{
    v[0] *= s ; 
    v[1] *= s ; 
    return *this ; 
}

CS_VECTOR2D operator*(double s, CS_VECTOR2D &v) 
{
    CS_VECTOR2D r = v * s ; 
    return r ; 
}


// cross product
CS_VECTOR CS_VECTOR2D::operator*(const CS_VECTOR2D &w) 
{
    CS_VECTOR r(0,0) ; // not defined
    return r ; 
}


// Returns an arbitrary normal vector to the base vector in 3D space
// This vector is arbitrary since it can go in any direction
// on the plane which v (base vector) is normal to. 
// v below is *this vector, see notes RR-Vol1 pgs 40-45
CS_VECTOR CS_VECTOR2D::ArbNorm3D() 
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
            n.v[0] = 0,0 ; 
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

void CS_VECTOR2D::Print(FILE *fp)
{
    if (!fp)
        fp = fpDebugOut ; 
    fprintf(fp, "(%.12lf, %.12lf, %.12lf)", v[0], v[1], v[2]) ; 
}


double CS_DotProduct(const CS_VECTOR2D &a, const CS_VECTOR2D &b) 
{
    return ((a.x * b.x) + (a.y * b.y)) ;
}

double ZCross(const CS_VECTOR2D &a, const CS_VECTOR2D &b) 
{
    return (a.x * b.y) - (a.y * b.x) ; 
}

double DistanceSquared(const CS_POINT2D &p1, const CS_POINT2D &p2) 
{
    CS_POINT2D pa(p1) ; 
    CS_POINT2D pb(p1) ; 

    CS_POINT2D p3 = pb - pa ; 
    return ((p3.x * p3.x) + (p3.y * p3.y)) ;
}

double CS_Distance(const CS_POINT2D &p1, const CS_POINT2D &p2)
{
    CS_POINT2D pa(p1) ; 
    CS_POINT2D pb(p1) ; 

    CS_POINT2D p3 = pb - pa ; 
    return sqrt((p3.x * p3.x) + (p3.y * p3.y)) ;
}


double CS_Distance2D(const CS_POINT &p1, const CS_POINT &p2)
{
    CS_POINT p3 = p2 - p1 ; 
    return sqrt((p3.x * p3.x) + (p3.y * p3.y)) ;
}



// Create a vector from circular coordinates
CS_VECTOR2D CS_VECTOR2D_CIR(double r, double theta)
{
    CS_VECTOR2D vr ; // resultant CS_VECTOR2D
    vr.x = r * cos(theta) ; 
    vr.y = r * sin(theta) ; 
    return vr ; 
}

