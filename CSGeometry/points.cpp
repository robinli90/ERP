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
// points.cpp

#include <stdio.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_matrices.h"

CS_POINT::CS_POINT(const CS_VECTOR &v)
{
    x = v.x ; 
    y = v.y ; 
    z = v.z ; 
}


CS_POINT &CS_POINT::operator=(const CS_VECTOR &a) 
{
    x = a.x ; 
    y = a.y ; 
    z = a.z ; 
    return *this ; 
}


CS_POINT CS_POINT::operator-(const CS_POINT &s) const
{
    CS_POINT r ; 
    r.p[0] = p[0] - s.p[0] ; 
    r.p[1] = p[1] - s.p[1] ; 
    r.p[2] = p[2] - s.p[2] ; 
    return r ;
}

CS_POINT CS_POINT::operator+(const CS_POINT &pnt) 
{
    CS_POINT r ; 
    r.p[0] = p[0] + pnt.p[0] ; 
    r.p[1] = p[1] + pnt.p[1] ; 
    r.p[2] = p[2] + pnt.p[2] ; 
    return r ; 
}

CS_POINT CS_POINT::operator+(const CS_VECTOR &v) 
{
    CS_POINT r ; 
    r.p[0] = p[0] + v.v[0] ; 
    r.p[1] = p[1] + v.v[1] ; 
    r.p[2] = p[2] + v.v[2] ; 
    return r ; 
}

CS_POINT CS_POINT::operator-()
{
    CS_POINT negp ;
    negp.p[0] = -p[0] ; 
    negp.p[1] = -p[1] ; 
    negp.p[2] = -p[2] ; 
    return negp ; 
}

CS_POINT CS_POINT::operator-(const CS_VECTOR &v) const
{
    CS_POINT r ; 
    r.p[0] = p[0] - v.v[0] ; 
    r.p[1] = p[1] - v.v[1] ; 
    r.p[2] = p[2] - v.v[2] ; 
    return r ; 
}

CS_POINT CS_POINT::operator/(double d) 
{
    CS_POINT r ; // returns a zero point if d==0
    if (d != 0)
    {
        r.p[0] = p[0] / d ; 
        r.p[1] = p[1] / d ; 
        r.p[2] = p[2] / d ; 
    }
    return r ;
}

// Dot product
double CS_POINT::operator*(const CS_POINT &pnt) 
{
    return (x * pnt.x) + (y * pnt.y) + (z * pnt.z) ;  
}

// Scaling factor
CS_POINT CS_POINT::operator*(double s) 
{
    CS_POINT r ; 
    r.p[0] = p[0] * s ; 
    r.p[1] = p[1] * s ; 
    r.p[2] = p[2] * s ; 
    return r ; 
}

CS_POINT &CS_POINT::operator*=(const double &s)
{
    x *= s ; 
    y *= s ; 
    z *= s ; 
    return *this ; 
}

CS_POINT &CS_POINT::operator/=(const double &s)
{
    x /= s ; 
    y /= s ; 
    z /= s ; 
    return *this ; 
}

CS_POINT &CS_POINT::operator+=(const CS_VECTOR &b)
{
    x += b.x ; 
    y += b.y ; 
    z += b.z ; 
    return *this ; 
}

CS_POINT &CS_POINT::operator-=(const CS_VECTOR &b)
{
    x -= b.x ; 
    y -= b.y ; 
    z -= b.z ; 
    return *this ; 
}

CS_POINT &CS_POINT::operator+=(const CS_POINT &b)
{
    x += b.x ; 
    y += b.y ; 
    z += b.z ; 
    return *this ; 
}

CS_POINT &CS_POINT::operator-=(const CS_POINT &b)
{
    x -= b.x ; 
    y -= b.y ; 
    z -= b.z ; 
    return *this ; 
}

int CS_POINT::operator==(const CS_POINT &pnt)
{
    if (tcomp_NEQ(p[0], pnt.p[0]) || 
        tcomp_NEQ(p[1], pnt.p[1]) || 
        tcomp_NEQ(p[2], pnt.p[2]))
        return 0 ; 
    return 1 ; 
}

int CS_POINT::operator!=(const CS_POINT &pnt)
{
    if (tcomp_NEQ(p[0], pnt.p[0]) || 
        tcomp_NEQ(p[1], pnt.p[1]) || 
        tcomp_NEQ(p[2], pnt.p[2]))
        return 1 ; 
    return 0 ; 
}

void CS_POINT::Print(FILE *fp)
{
    if (!fp)
        fp = fpDebugOut ; 
    fprintf(fp, "(%.12lf, %.12lf, %.12lf)", p[0], p[1], p[2]) ; 
}

CS_POINT CS_POINT_SPHERE(double r, double theta, double phi)
{
    CS_POINT p ; // resultant CS_VECTOR
    p.p[0] = r * sin(theta) * cos(phi) ; 
    p.p[1] = r * sin(theta) * sin(phi) ; 
    p.p[2] = r * cos(theta) ; 
    return p ; 
}

CS_POINT CS_POINT_CYL(double r, double phi, double z)
{
    CS_POINT p ; // resultant CS_VECTOR
    p.p[0] = r * cos(phi) ; 
    p.p[1] = r * sin(phi) ; 
    p.p[2] = z ; 
    return p ; 
}

