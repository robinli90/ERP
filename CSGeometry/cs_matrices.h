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
// matrices.h - matrix classes

#ifndef __CS_MATRICES_H__ 

#define __CS_MATRICES_H__

#include <math.h>
#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"

/* 
    Notes on coordinate system transformations. 

    If for example you have a CSYS with an origin of C and a transformation 
    matrix of M. Then to get a point in ABS space to the transformed CSYS
    you would need to do: 

    TODO: complete this discussion

 */


struct CS_MTX4 ;

// Standard 3x3 matrix for general math operations
//
// 0 1 2 
// 3 4 5
// 6 7 8
//
class CS_MTX3 {
public:
    double m[9] ; // 3 by 3 matrix, in row order
    // Thus m[i][j] = m[i*3+j]

    CS_MTX3() {} ; 
    CS_MTX3(CS_VECTOR &x, CS_VECTOR &y) ;
    CS_MTX3(CS_MTX4 &m4) ; 

    // The three vectors are dumped into the 0, 1 and 2 columns
    // of the matrix respectively
    CS_MTX3(CS_VECTOR x, CS_VECTOR y, CS_VECTOR z)
    {
        // Make sure the 3 axis are unit vectors
        x = x.Unit() ; 
        y = y.Unit() ; 
        z = z.Unit() ; 

        m[0] = x.v[0] ; 
        m[3] = x.v[1] ; 
        m[6] = x.v[2] ; 
        m[1] = y.v[0] ; 
        m[4] = y.v[1] ; 
        m[7] = y.v[2] ; 
        m[2] = z.v[0] ; 
        m[5] = z.v[1] ; 
        m[8] = z.v[2] ; 
    }

    //! Set up a transform matrix based on axis rotation angles
    /*!
        \param alpha rotation of the X->Y plane around Z axis angle
        \param beta  rotation of the Y->Z plane around X axis angle
        \param phi   rotation of the Z->X plane around Y axis angle

        The arrows above indicate which axis is being rotated towards 
        the other axis. Thus X->Y means the x axis is being rotated 
        towards the y axis, which forms a standard right handed system
        rotation. The other rotations are in the direction that points
        in the unit vector direction of the axis that is being rotated
        around. 

        The way this is done is by defining three separate rotation 
        matrices Rz(alpha), Rx(beta), and Ry(phi). The the product

                    Rz * Rx * Ry 

        defines the final transformation matrix. Thus first the XY plane
        is rotated, then the YZ plane is rotated, and then the ZX plane 
        is rotated. 
     */
    CS_MTX3(double alpha, double beta=0.0, double phi=0.0) ; 

    void Identity() ; 
    CS_MTX3 &Set(double *d) { m[0] = d[0] ; m[1] = d[1] ; m[2] = d[2] ; 
                              m[3] = d[3] ; m[4] = d[4] ; m[5] = d[5] ; 
                              m[6] = d[6] ; m[7] = d[7] ; m[8] = d[8] ; 
                              return *this; } ; 
    int operator==(const CS_MTX3 &m3) ; 
    int operator!=(const CS_MTX3 &m3) ; 
    CS_MTX3 &operator=(const CS_MTX3 &m3) ;
    CS_MTX3 &operator=(const CS_MTX4 &m4) ;
    CS_MTX3 operator-() ; 
    CS_MTX3 operator+(const CS_MTX3 &n) ; 
    CS_MTX3 operator-(const CS_MTX3 &n) ; 
    CS_MTX3 operator*(const CS_MTX3 &n) ; 
    CS_MTX3 operator*(double k) ; 
    double Deteminant() ; 
    int Invert() ; // inverts the matrix, returns non-zero if singular
    CS_MTX3 &Transpose() ;
    CS_MTX3 &Rotate(double alpha, double beta=0.0, double phi=0.0) ; 

    CS_MTX3 &SetXRot(const double &th) ; 
    CS_MTX3 &SetYRot(const double &th) ; 
    CS_MTX3 &SetZRot(const double &th) ; 

    CS_MTX3 SetXVec(CS_VECTOR &x)
    {
        // Make sure the 3 axis are unit vectors
        m[0] = x.v[0] ; 
        m[3] = x.v[1] ; 
        m[6] = x.v[2] ; 
        return *this ;
    }

    CS_MTX3 SetYVec(CS_VECTOR &y)
    {
        // Make sure the 3 axis are unit vectors
        m[1] = y.v[0] ; 
        m[4] = y.v[1] ; 
        m[7] = y.v[2] ; 
        return *this ;
    }

    CS_MTX3 SetZVec(CS_VECTOR &z)
    {
        // Make sure the 3 axis are unit vectors
        m[2] = z.v[0] ; 
        m[5] = z.v[1] ; 
        m[8] = z.v[2] ; 
        return *this ;
    }


    void RotTransform(CS_VECTOR vx, CS_VECTOR vy, CS_VECTOR vz) ;
    void RotTransformZ(CS_VECTOR vz) ; // vz=result after transform of (0,0,1)
} ;

CS_MTX3 operator*(double k, const CS_MTX3 &mx) ; 
CS_VECTOR operator*(const CS_MTX3 &m, const CS_VECTOR &v) ; 
CS_POINT operator*(const CS_MTX3 &m, const CS_POINT &v) ; 


/*************************************************************************
   Coordinate system transformation matrices used for view window
   display type transformations. These are optimized to minimize the 
   number of MACD's performed as well as all other overhead usually 
   associated with matrix calculations.
 *************************************************************************/

/**
    Applies a 2D matrix coordinate system transformation allowing
    full rotation and translation (shear and scaling are also possible)
    Matrix is defined as :
            M2 = | a b tx |
                 | c d ty |
                 | 0 0 1  |

    where the last row is not stored nor is it used in the calculations

  ABS coordinates is the coordinate system stored within the raw CAD
  data (the line and arc segments etc...)
 */

struct CS_MTX2
{
    double m[6] ; // in the order a, b, tx, c, d, ty

    CS_MTX2()
    {
        m[0] = m[4] = 1.0 ;
        m[1] = m[2] = m[3] = m[5] = 0.0 ;
    };

    // Returns -1 error code if the scale is bad,
    // else returns 0.
    int Init(int width, int height, double scale)
    {
        if (tcomp_LEQ(scale, 0.0))
            return -1 ;
        // Define the view screen window size in ABS coordinates
        CS_VECTOR2D wrkview(width, height) ;
        
        m[0] = scale ; 
        m[1] = 0.0 ; 
        m[3] = 0.0 ; 
        m[4] = -scale ; // y axis is reversed for standard view

        wrkview *= 1.0 / scale ;
        m[2] = wrkview.x / 2.0 ; 
        m[5] = wrkview.y / 2.0 ; 
        return 0 ; 
    }

    // Does no checking of the scale value which must me > 0
    // Used when changing the zoom level from 
    void ChangeScale(double oldscale, double newscale) 
    {
        double s = newscale / oldscale ;
        m[0] *= s ;
        m[1] *= s ;
        m[2] *= s ;
        m[3] *= s ;
        m[4] *= s ;
        m[5] *= s ;
    }

    void SetTxy(double x, double y)
    {
        m[2] = x ;
        m[5] = y ;
    }

    // Perform the transformation, and return the result in 
    // integer coordinates. n must point to an array 
    // of 2 integers on entry.
    void XForm(CS_POINT2D &p, int *n) 
    {   // May want to add a rounding version of this also 
        n[0] = (int)(m[0] * p.x + m[1] * p.y + m[2]) ;
        n[1] = (int)(m[3] * p.x + m[4] * p.y + m[5]) ;
    }

    // Perform the transformation, and return the result in 
    // integer coordinates. d must point to an array 
    // of 2 doubles on entry.
    void XForm(CS_POINT2D &p, double *d) 
    {   // May want to add a rounding version of this also 
        d[0] = m[0] * p.x + m[1] * p.y + m[2] ;
        d[1] = m[3] * p.x + m[4] * p.y + m[5] ;
    }

    // Returns the inverse transformation matrix
    // Not an efficient call thus intended to be used sparingly.
    CS_MTX2 Inverse()
    {   // Cramer's Rule for the 2x2 matrix inverse
        CS_MTX2 minv ; 
    
        double q = 1.0 / (m[0] * m[4] - m[1] * m[3]) ; 
        minv.m[0] =  q * m[4] ; 
        minv.m[1] = -q * m[1] ; 
        minv.m[3] = -q * m[3] ; 
        minv.m[4] =  q * m[0] ; 

        // Take negative of the translation vector component
        minv.m[2] = -m[2] ; 
        minv.m[5] = -m[5] ; 
        
        return minv ; 
    } 


    void Rotate(double theta) 
    {
        double m0 = m[0] ; 
        double m3 = m[3] ; 

        double costheta = cos(theta) ; 
        double sintheta = sin(theta) ; 

        m[0] = m0 * costheta  + m[1] * sintheta ; 
        m[1] = m0 * -sintheta + m[1] * costheta ; 
        m[3] = m3 * costheta  + m[4] * sintheta ; 
        m[4] = m3 * -sintheta + m[4] * costheta ; 
    }

    // Vector v is assumed to be in ABS coordinates
    void Pan(CS_VECTOR2D &v)
    {
        // First scale the vector properly
        CS_VECTOR2D vpan(v.x * m[0] + v.y * m[1], 
                         v.x * m[3] + v.y * m[4]) ;    
        m[2] += vpan.x ;
        m[5] += vpan.y ;
    }

    void Pan(double x, double y)
    {
        // First scale the vector properly
        CS_VECTOR2D vpan(x * m[0] + y * m[1], 
                         x * m[3] + y * m[4]) ;    
        m[2] += vpan.x ;
        m[5] += vpan.y ;
    }

    void Pan(int x, int y)
    {
        // First scale the vector properly
        CS_VECTOR2D vpan(x * m[0] + y * m[1], 
                         x * m[3] + y * m[4]) ;    
        m[2] += vpan.x ;
        m[5] += vpan.y ;
    }


} ;


/**
    Applies a 3D matrix coordinate system transformation allowing
    full rotation and translation (shear and scaling are also possible)
    Matrix is defined as :
            M4 = | a b c tx |
                 | e f g ty |
                 | h i j tz |
                 | 0 0 0 1  |

          m[] index positions as follows
            M4 = | 0  1   2  3 |
                 | 4  5   6  7 |
                 | 8  9  10 11 |
                 | na na na na |


    where the last row is not stored nor is it used in the calculations
 */


struct CS_MTX4
{
    double m[12] ; // in the order a,b,c,tx,e,f,g,ty,h,i,j,tz


    CS_MTX4() {} ; 
    CS_MTX4(const CS_MTX3 &m3)
    {
        m[0]  = m3.m[0] ; 
        m[1]  = m3.m[1] ; 
        m[2]  = m3.m[2] ; 

        m[4]  = m3.m[3] ; 
        m[5]  = m3.m[4] ; 
        m[6]  = m3.m[5] ; 

        m[8]  = m3.m[6] ; 
        m[9]  = m3.m[7] ; 
        m[10] = m3.m[8] ; 

        m[3]  = 0.0 ; 
        m[7]  = 0.0 ; 
        m[11] = 0.0 ; 
    }

    CS_MTX4(const CS_MTX3 &m3, const CS_POINT &p)
    {
        m[0]  = m3.m[0] ; 
        m[1]  = m3.m[1] ; 
        m[2]  = m3.m[2] ; 

        m[4]  = m3.m[3] ; 
        m[5]  = m3.m[4] ; 
        m[6]  = m3.m[5] ; 

        m[8]  = m3.m[6] ; 
        m[9]  = m3.m[7] ; 
        m[10] = m3.m[8] ; 

        m[3]  = p.x ; 
        m[7]  = p.y ; 
        m[11] = p.z ; 
    }

    CS_MTX4(const CS_MTX3 &m3, const CS_VECTOR &v)
    {
        m[0]  = m3.m[0] ; 
        m[1]  = m3.m[1] ; 
        m[2]  = m3.m[2] ; 

        m[4]  = m3.m[3] ; 
        m[5]  = m3.m[4] ; 
        m[6]  = m3.m[5] ; 

        m[8]  = m3.m[6] ; 
        m[9]  = m3.m[7] ; 
        m[10] = m3.m[8] ; 

        m[3]  = v.x ; 
        m[7]  = v.y ; 
        m[11] = v.z ; 
    }


    // Sets the NULL transform or identity transform
    // ie Mv=v
    void Identity()
    { 
        m[0] = m[5] = m[10] = 1.0 ; 
        m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = 0.0 ; 
    }; 

    CS_POINT Origin() 
    {
        CS_POINT p(m[3], m[7], m[11]) ;
        return p ; 
    }

    CS_MTX4 &SetOrigin(CS_POINT &p) 
    {
        m[3]  = p.x ; 
        m[7]  = p.y ; 
        m[11] = p.z ; 
        return *this ; 
    }

    CS_MTX4 &SetX(double &d) { m[3]  = d ; return *this; }
    CS_MTX4 &SetY(double &d) { m[7]  = d ; return *this; }
    CS_MTX4 &SetZ(double &d) { m[11] = d ; return *this; }


    CS_MTX4 &SetXVec(CS_VECTOR &x)
    {
        // Make sure the 3 axis are unit vectors
        m[0] = x.v[0] ; 
        m[4] = x.v[1] ; 
        m[8] = x.v[2] ; 
        return *this ;
    }

    CS_MTX4 &SetYVec(CS_VECTOR &y)
    {
        // Make sure the 3 axis are unit vectors
        m[1] = y.v[0] ; 
        m[5] = y.v[1] ; 
        m[9] = y.v[2] ; 
        return *this ;
    }

    CS_MTX4 &SetZVec(CS_VECTOR &z)
    {
        // Make sure the 3 axis are unit vectors
        m[2] = z.v[0] ; 
        m[6] = z.v[1] ; 
        m[10] = z.v[2] ; 
        return *this ;
    }

    CS_MTX4 &SetXYZO(CS_VECTOR &vx, CS_VECTOR &vy, CS_VECTOR &vz, CS_POINT &org) 
    {
        SetXVec(vx) ; 
        SetYVec(vy) ; 
        SetZVec(vz) ; 
        SetOrigin(org) ; 
        return *this ; 
    }


    CS_VECTOR GetXVec()
    {
        CS_VECTOR v ; 
        v.x = m[0] ; 
        v.y = m[4] ; 
        v.z = m[8] ; 
        return v ; 
    }

    CS_VECTOR GetYVec()
    {
        CS_VECTOR v ; 
        v.x = m[1] ; 
        v.y = m[5] ; 
        v.z = m[9] ; 
        return v ; 
    }

    CS_VECTOR GetZVec()
    {
        CS_VECTOR v ; 
        v.x = m[2]  ; 
        v.y = m[6]  ; 
        v.z = m[10] ; 
        return v ; 
    }

    CS_MTX4 &operator=(CS_MTX3 &m3)
    {
        m[0]  = m3.m[0] ; 
        m[1]  = m3.m[1] ; 
        m[2]  = m3.m[2] ; 

        m[4]  = m3.m[3] ; 
        m[5]  = m3.m[4] ; 
        m[6]  = m3.m[5] ; 

        m[8]  = m3.m[6] ; 
        m[9]  = m3.m[7] ; 
        m[10] = m3.m[8] ; 

        m[3]  = 0.0 ; 
        m[7]  = 0.0 ; 
        m[11] = 0.0 ; 

        return *this ; 
    }

    int operator==(const CS_MTX4 &b)
    {
        if (tcomp_NEQ(m[0], b.m[0]) || tcomp_NEQ(m[1], b.m[1])   || tcomp_NEQ(m[2], b.m[2]) || 
            tcomp_NEQ(m[3], b.m[3]) || tcomp_NEQ(m[4], b.m[4])   || tcomp_NEQ(m[5], b.m[5]) || 
            tcomp_NEQ(m[6], b.m[6]) || tcomp_NEQ(m[7], b.m[7])   || tcomp_NEQ(m[8], b.m[8]) || 
            tcomp_NEQ(m[9], b.m[9]) || tcomp_NEQ(m[10], b.m[10]) || tcomp_NEQ(m[11], b.m[11]))
            return 0 ; 
        return 1 ; 
    }

    int operator!=(const CS_MTX4 &b)
    {
        if (tcomp_NEQ(m[0], b.m[0]) || tcomp_NEQ(m[1], b.m[1])   || tcomp_NEQ(m[2], b.m[2]) || 
            tcomp_NEQ(m[3], b.m[3]) || tcomp_NEQ(m[4], b.m[4])   || tcomp_NEQ(m[5], b.m[5]) || 
            tcomp_NEQ(m[6], b.m[6]) || tcomp_NEQ(m[7], b.m[7])   || tcomp_NEQ(m[8], b.m[8]) || 
            tcomp_NEQ(m[9], b.m[9]) || tcomp_NEQ(m[10], b.m[10]) || tcomp_NEQ(m[11], b.m[11]))
            return 1 ; 
        return 0 ; 
    }


    CS_MTX4 operator*(double k)
    {
        CS_MTX4 mxs ; 
        for (int i=0; i < 12; i++)
            mxs.m[i] = m[i] * k ; 

        return mxs ; 
    }

    CS_MTX4 &operator*=(double k)
    {
        for (int i=0; i < 12; i++)
            m[i] *= k ; 

        return *this ; 
    }

    // Convert the input X,Y point to screen coordinates
    void ToScreen(CS_POINT &p, int *screen) 
    {   // May want to add a rounding version of this also 
        // TO DO - add all the necessary perspective and camera orientation 
        // capabilities to this transformation. Will have to pass in a 
        // Camera matrix definition to generate the proper screen coordinates.
        // Currently all this returns is the XY plane style top down view.
        screen[0] = (int)(m[0] * p.x  +  m[1] * p.y  +  m[2] * p.z  +  m[3]) ; 
        screen[1] = (int)(m[4] * p.x  +  m[5] * p.y  +  m[6] * p.z  +  m[7]) ; 
    }

    CS_MTX4 &Rotate(double theta) 
    {
        CS_MTX3 m3(*this) ; 
        m3.Identity() ; 
        m3.Rotate(theta) ; 
        m[0]  = m3.m[0] ; 
        m[1]  = m3.m[1] ; 
        m[2]  = m3.m[2] ; 

        m[4]  = m3.m[3] ; 
        m[5]  = m3.m[4] ; 
        m[6]  = m3.m[5] ; 

        m[8]  = m3.m[6] ; 
        m[9]  = m3.m[7] ; 
        m[10] = m3.m[8] ; 

        return *this ; 
    }
    
    void Pan(CS_VECTOR &v) 
    {
        m[3]  += v.x ; 
        m[7]  += v.y ;
        m[11] += v.z ;
    } 

    void SetTranslation(CS_VECTOR &v)
    {
        m[3]  = v.x ; 
        m[7]  = v.y ;
        m[11] = v.z ;
    }

    CS_VECTOR GetTranslation()
    {
        CS_VECTOR  v ; 
        v.x = m[3]  ; 
        v.y = m[7]  ;
        v.z = m[11] ;
        return v ; 
    }

    CS_MTX3 GetTransform()
    {
        CS_MTX3 m3 ; 
        m3.m[0] = m[0]  ; 
        m3.m[1] = m[1]  ; 
        m3.m[2] = m[2]  ; 
        
        m3.m[3] = m[4]  ; 
        m3.m[4] = m[5]  ; 
        m3.m[5] = m[6]  ; 
        
        m3.m[6] = m[8]  ; 
        m3.m[7] = m[9]  ; 
        m3.m[8] = m[10] ; 
        return m3 ; 
    }

    //! Do the transformation multiply only, and not the translation
    CS_VECTOR Mult3x3(CS_VECTOR &v) 
    {
        CS_VECTOR vx ; 
        vx.x = m[0] * v.x + m[1] * v.y + m[2]  * v.z ; 
        vx.y = m[4] * v.x + m[5] * v.y + m[6]  * v.z ; 
        vx.z = m[8] * v.x + m[9] * v.y + m[10] * v.z ; 
        return vx ; 
    }


    CS_POINT  Mult3x3(CS_POINT  &p) 
    {
        CS_POINT px ; 
        px.x = m[0] * p.x + m[1] * p.y + m[2]  * p.z ; 
        px.y = m[4] * p.x + m[5] * p.y + m[6]  * p.z ; 
        px.z = m[8] * p.x + m[9] * p.y + m[10] * p.z ; 
        return px ; 
    }

    void Print(FILE *fp) ; 
} ;

CS_POINT operator*(const CS_MTX4 &m, const CS_POINT &p) ; 
CS_VECTOR operator*(const CS_MTX4 &m, const CS_VECTOR &v) ; 
CS_MTX4 operator*(double k, const CS_MTX4 &mx) ;

#endif