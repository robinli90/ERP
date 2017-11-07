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
// matrices.cpp - matrix classes

#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_matrices.h"


// Create a rotation matrix defined by the two vectors
// note to get the Z axis vector we can take the cross product 
// (x * y) 
// TO DO - see if this is used anywhere since the vectors typically
// should be in the column direction not assigned by row
CS_MTX3::CS_MTX3(CS_VECTOR &x, CS_VECTOR &y)
{
    CS_VECTOR z = x * y ; // take cross product
    
    // Make sure the 3 axis are unit vectors
    x = x.Unit() ; 
    y = y.Unit() ; 
    z = z.Unit() ; 

    m[0] = x.v[0] ; 
    m[1] = x.v[1] ; 
    m[2] = x.v[2] ; 
    m[3] = y.v[0] ; 
    m[4] = y.v[1] ; 
    m[5] = y.v[2] ; 
    m[6] = z.v[0] ; 
    m[7] = z.v[1] ; 
    m[8] = z.v[2] ; 
}


CS_MTX3::CS_MTX3(CS_MTX4 &m4)
{
    m[0] = m4.m[0] ;
    m[1] = m4.m[1] ;
    m[2] = m4.m[2] ;
    m[3] = m4.m[4] ;
    m[4] = m4.m[5] ;
    m[5] = m4.m[6] ;
    m[6] = m4.m[8] ;
    m[7] = m4.m[9] ;
    m[8] = m4.m[10] ;
}


// These are standard right hand rule rotations
// x->y
// y->z
// z->x

CS_MTX3::CS_MTX3(double alpha, double beta, double phi) 
{
    CS_MTX3 Rz ; 
    Rz.m[0] = cos(alpha) ; 
    Rz.m[1] = -sin(alpha) ;
    Rz.m[2] = 0 ; 
    Rz.m[3] = sin(alpha) ; 
    Rz.m[4] = cos(alpha) ; 
    Rz.m[5] = 0 ; 
    Rz.m[6] = 0 ; 
    Rz.m[7] = 0 ; 
    Rz.m[8] = 1.0 ; 

    CS_MTX3 Rx ; 
    Rx.m[0] = 1.0 ; 
    Rx.m[1] = 0 ; 
    Rx.m[2] = 0 ; 
    Rx.m[3] = 0 ; 
    Rx.m[4] = cos(beta) ; 
    Rx.m[5] = -sin(beta) ; 
    Rx.m[6] = 0 ; 
    Rx.m[7] = sin(beta) ; 
    Rx.m[8] = cos(beta) ; 

    CS_MTX3 Ry ; 
    Ry.m[0] = cos(phi) ; 
    Ry.m[1] = 0 ; 
    Ry.m[2] = sin(phi) ; 
    Ry.m[3] = 0 ; 
    Ry.m[4] = 1.0 ; 
    Ry.m[5] = 0 ; 
    Ry.m[6] = -sin(phi) ; 
    Ry.m[7] = 0 ; 
    Ry.m[8] = cos(phi) ; 

    // TODO - see if creating a temp var for Rz*Rx optimizes the time
    *this = Rz * Rx ; 
    *this = *this * Ry ; 
}

CS_MTX3 &CS_MTX3::SetXRot(const double &th) 
{
    m[0] = 1.0 ; 
    m[1] = 0 ; 
    m[2] = 0 ; 
    m[3] = 0 ; 
    m[4] = cos(th) ; 
    m[5] = -sin(th) ; 
    m[6] = 0 ; 
    m[7] = sin(th) ; 
    m[8] = cos(th) ; 

    return *this ; 
}


CS_MTX3 &CS_MTX3::SetYRot(const double &th)
{
    m[0] = cos(th) ; 
    m[1] = 0 ; 
    m[2] = sin(th) ; 
    m[3] = 0 ; 
    m[4] = 1.0 ; 
    m[5] = 0 ; 
    m[6] = -sin(th) ; 
    m[7] = 0 ; 
    m[8] = cos(th) ; 

    return *this ; 
}

CS_MTX3 &CS_MTX3::SetZRot(const double &th)
{
    m[0] = cos(th) ; 
    m[1] = -sin(th) ;
    m[2] = 0 ; 
    m[3] = sin(th) ; 
    m[4] = cos(th) ; 
    m[5] = 0 ; 
    m[6] = 0 ; 
    m[7] = 0 ; 
    m[8] = 1.0 ; 

    return *this ; 
}


void CS_MTX3::Identity()
{
    m[0] = 1.0 ; 
    m[1] = 0.0 ; 
    m[2] = 0.0 ; 
    m[3] = 0.0 ; 
    m[4] = 1.0 ; 
    m[5] = 0.0 ; 
    m[6] = 0.0 ; 
    m[7] = 0.0 ; 
    m[8] = 1.0 ; 
}

int CS_MTX3::operator==(const CS_MTX3 &m3)
{
    if (tcomp_NEQ(m[0], m3.m[0]) ||
        tcomp_NEQ(m[1], m3.m[1]) ||
        tcomp_NEQ(m[2], m3.m[2]) ||
        tcomp_NEQ(m[3], m3.m[3]) ||
        tcomp_NEQ(m[4], m3.m[4]) ||
        tcomp_NEQ(m[5], m3.m[5]) ||
        tcomp_NEQ(m[6], m3.m[6]) ||
        tcomp_NEQ(m[7], m3.m[7]) ||
        tcomp_NEQ(m[8], m3.m[8]))
        return 0 ; 
    return 1 ; 
}

int CS_MTX3::operator!=(const CS_MTX3 &m3) 
{
    if (tcomp_NEQ(m[0], m3.m[0]) ||
        tcomp_NEQ(m[1], m3.m[1]) ||
        tcomp_NEQ(m[2], m3.m[2]) ||
        tcomp_NEQ(m[3], m3.m[3]) ||
        tcomp_NEQ(m[4], m3.m[4]) ||
        tcomp_NEQ(m[5], m3.m[5]) ||
        tcomp_NEQ(m[6], m3.m[6]) ||
        tcomp_NEQ(m[7], m3.m[7]) ||
        tcomp_NEQ(m[8], m3.m[8]))
        return 1 ; 
    return 0 ; 
}


CS_MTX3 &CS_MTX3::operator=(const CS_MTX3 &m3)
{
    m[0] = m3.m[0] ;
    m[1] = m3.m[1] ;
    m[2] = m3.m[2] ;
    m[3] = m3.m[3] ;
    m[4] = m3.m[4] ;
    m[5] = m3.m[5] ;
    m[6] = m3.m[6] ;
    m[7] = m3.m[7] ;
    m[8] = m3.m[8] ;
    return *this ; 
}

CS_MTX3 &CS_MTX3::operator=(const CS_MTX4 &m4)
{
    m[0] = m4.m[0] ;
    m[1] = m4.m[1] ;
    m[2] = m4.m[2] ;
    m[3] = m4.m[4] ;
    m[4] = m4.m[5] ;
    m[5] = m4.m[6] ;
    m[6] = m4.m[8] ;
    m[7] = m4.m[9] ;
    m[8] = m4.m[10] ;
    return *this ; 
}


CS_MTX3 CS_MTX3::operator+(const CS_MTX3 &n)
{
    CS_MTX3 res ; 
    int i ; 
    for (i=0;i<9;i++)
        res.m[i] = m[i] + n.m[i] ; 
    return res ; 
}

CS_MTX3 CS_MTX3::operator-(const CS_MTX3 &n)
{
    CS_MTX3 res ; 
    int i ; 
    for (i=0;i<9;i++)
        res.m[i] = m[i] - n.m[i] ; 
    return res ; 
}

CS_MTX3 CS_MTX3::operator-()
{
    CS_MTX3 res ; 
    int i ; 
    for (i=0;i<9;i++)
        res.m[i] = -m[i] ; 
    return res ; 
}

CS_MTX3 CS_MTX3::operator*(const CS_MTX3 &n)
{
    CS_MTX3 res ; 
    int r, c, i; 

    // r=row, c=column, i=index
    for (r=0;r<3;r++)
    {
        for (c=0;c<3;c++)
        {
            res.m[r * 3 + c] = 0 ; 
            for (i=0;i<3;i++) res.m[r * 3 + c] += m[r * 3 + i] * n.m[i * 3 + c] ; 
        }
    }
    return res ; 
}

CS_MTX3 CS_MTX3::operator*(double k)
{
    CS_MTX3 mxs ; 
    for (int i=0; i < 9; i++)
        mxs.m[i] = m[i] * k ; 
    return mxs ; 
}


double CS_MTX3::Deteminant()
{
    return (m[0] * ((m[4] * m[8]) - (m[5] * m[7]))) + 
           (m[1] * ((m[5] * m[6]) - (m[3] * m[8]))) + 
           (m[2] * ((m[3] * m[7]) - (m[4] * m[6]))) ; 
}


// Invert the matrix
int CS_MTX3::Invert()
{
    CS_VECTOR b(0,0,0) ; 
    return CS_gaussj(m, 3, b.v, 1) ;
}

CS_MTX3 &CS_MTX3::Transpose()
{
    // 0 1 2 
    // 3 4 5
    // 6 7 8
    //
    // Gets transposed to 
    //
    // 0 3 6 
    // 1 4 7
    // 2 5 8
    //

    double t ;
    t = m[1] ; 
    m[1] = m[3] ; 
    m[3] = t ; 

    t = m[2] ; 
    m[2] = m[6] ; 
    m[6] = t ; 

    t = m[5] ; 
    m[5] = m[7] ; 
    m[7] = t ; 

    return *this ; 
}

CS_MTX3 &CS_MTX3::Rotate(double alpha, double beta, double phi) 
{
    CS_MTX3 rmx(alpha, beta, phi) ; 
    *this = *this * rmx ; 
    return *this ; 
}


// Creates the rotation transform matrix to transform the
// vector (0,0,1) to the vector v
// The X and Y axis vectors are arbitrarily oriented by this 
// function. 
void CS_MTX3::RotTransformZ(CS_VECTOR v12)
{
    CS_VECTOR v13 ;

    if (tcomp_EQZ(v12.v[0]) && tcomp_EQZ(v12.v[1]))
    {
        v13 = v12 + CS_VECTOR(10,0,0) ; 
    }
    else
    {
        v13 = v12 + CS_VECTOR(0,0,10) ; 
    }
    
    CS_VECTOR rz = v12.Unit() ;
    CS_VECTOR rx = v13 * v12 ; // cross product
    rx = rx.Unit() ; 
    CS_VECTOR ry = rz * rx ; // final vector

    // What we are doing is taking the three unit vectors along the
    // axes of the rotated system and assigning these column vectors
    // the the final rotation matrix. These vectors are the columns
    // of the rotation matrix. This makes sense since it is the only
    // possible solution after you multiply by the three unit vectors
    // (1,0,0) (0,1,0) and (0,0,1)

    // x vector assigned to first column
    m[0] = rx.v[0] ; 
    m[3] = rx.v[1] ; 
    m[6] = rx.v[2] ; 

    m[1] = ry.v[0] ; 
    m[4] = ry.v[1] ; 
    m[7] = ry.v[2] ; 

    m[2] = rz.v[0] ; 
    m[5] = rz.v[1] ; 
    m[8] = rz.v[2] ; 
}


// Note vx,vy, and vz must all be orthoganal to one another
// for this call to work. They must also form a standard right
// handed system. 
void CS_MTX3::RotTransform(CS_VECTOR vx, CS_VECTOR vy, CS_VECTOR vz)
{
    // What we are doing is taking the three unit vectors along the
    // axes of the rotated system and assigning these column vectors
    // the the final rotation matrix. These vectors are the columns
    // of the rotation matrix. This makes sense since it is the only
    // possible solution after you multiply by the three unit vectors
    // (1,0,0) (0,1,0) and (0,0,1)
    vx = vx.Unit() ; 
    vy = vy.Unit() ; 
    vz = vz.Unit() ; 
    // x vector assigned to first column
    m[0] = vx.v[0] ; 
    m[3] = vx.v[1] ; 
    m[6] = vx.v[2] ; 

    m[1] = vy.v[0] ; 
    m[4] = vy.v[1] ; 
    m[7] = vy.v[2] ; 

    m[2] = vz.v[0] ; 
    m[5] = vz.v[1] ; 
    m[8] = vz.v[2] ; 
}


CS_MTX3 operator*(double k, const CS_MTX3 &mx) 
{
    CS_MTX3 mxs ; 
    for (int i=0; i < 9; i++)
        mxs.m[i] = mx.m[i] * k ; 
    return mxs ; 
}


CS_VECTOR operator*(const CS_MTX3 &m, const CS_VECTOR &v)
{
    CS_VECTOR r ; // result
    r.x = m.m[0] * v.x + m.m[1] * v.y + m.m[2] * v.z ; 
    r.y = m.m[3] * v.x + m.m[4] * v.y + m.m[5] * v.z ; 
    r.z = m.m[6] * v.x + m.m[7] * v.y + m.m[8] * v.z ; 
    return r ; 
}


CS_POINT operator*(const CS_MTX3 &m, const CS_POINT &p)
{
    CS_POINT r ; // result
    r.x = m.m[0] * p.x + m.m[1] * p.y + m.m[2] * p.z ; 
    r.y = m.m[3] * p.x + m.m[4] * p.y + m.m[5] * p.z ; 
    r.z = m.m[6] * p.x + m.m[7] * p.y + m.m[8] * p.z ; 
    return r ; 
}

CS_POINT operator*(const CS_MTX4 &m, const CS_POINT &p)
{
    CS_POINT r ; // result
    r.x = m.m[0] * p.x + m.m[1] * p.y + m.m[2]  * p.z + m.m[3] ; 
    r.y = m.m[4] * p.x + m.m[5] * p.y + m.m[6]  * p.z + m.m[7] ; 
    r.z = m.m[8] * p.x + m.m[9] * p.y + m.m[10] * p.z + m.m[11] ; 
    return r ; 
}

CS_VECTOR operator*(const CS_MTX4 &m, const CS_VECTOR &v)
{
    CS_VECTOR r ; // result
    r.x = m.m[0] * v.x + m.m[1] * v.y + m.m[2]  * v.z ; 
    r.y = m.m[4] * v.x + m.m[5] * v.y + m.m[6]  * v.z ; 
    r.z = m.m[8] * v.x + m.m[9] * v.y + m.m[10] * v.z ; 
    return r ; 
}


CS_MTX4 operator*(double k, const CS_MTX4 &mx)
{
    CS_MTX4 mxs ; // scaled matrix
    for (int i=0; i < 12; i++)
        mxs.m[i] = mx.m[i] * k ; 

    return mxs ; 
}


void CS_MTX4::Print(FILE *fp)
{
    fprintf(fp, "%10.4f %10.4f %10.4f %10.4f\n", m[0], m[1], m[2],  m[3]) ; 
    fprintf(fp, "%10.4f %10.4f %10.4f %10.4f\n", m[4], m[5], m[6],  m[7]) ; 
    fprintf(fp, "%10.4f %10.4f %10.4f %10.4f\n", m[8], m[9], m[10], m[11]) ; 
}