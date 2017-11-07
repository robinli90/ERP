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
// points2d.cpp

#include <stdio.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_matrices.h"


const char CS_COPYRIGHT_MESSAGE[] = "Copyright 1991-2004, Cadamation Systems, All rights reserved." ; 


CS_POINT2D CS_POINT2D::operator-(const CS_POINT2D &s) 
{
    CS_POINT2D r ; 
    r.p[0] = p[0] - s.p[0] ; 
    r.p[1] = p[1] - s.p[1] ; 
    return r ;
}

CS_POINT2D CS_POINT2D::operator+(const CS_POINT2D &pnt) 
{
    CS_POINT2D r ; 
    r.p[0] = p[0] + pnt.p[0] ; 
    r.p[1] = p[1] + pnt.p[1] ; 
    return r ; 
}

CS_POINT2D CS_POINT2D::operator+(const CS_VECTOR2D &v) 
{
    CS_POINT2D r ; 
    r.p[0] = p[0] + v.v[0] ; 
    r.p[1] = p[1] + v.v[1] ; 
    return r ; 
}

CS_POINT2D CS_POINT2D::operator-()
{
    CS_POINT2D negp ;
    negp.p[0] = -p[0] ; 
    negp.p[1] = -p[1] ; 
    return negp ; 
}

CS_POINT2D CS_POINT2D::operator-(const CS_VECTOR2D &v) 
{
    CS_POINT2D r ; 
    r.p[0] = p[0] - v.v[0] ; 
    r.p[1] = p[1] - v.v[1] ; 
    return r ; 
}

CS_POINT2D CS_POINT2D::operator/(double d) 
{
    CS_POINT2D r ; // returns a zero point if d==0
    if (d != 0)
    {
        r.p[0] = p[0] / d ; 
        r.p[1] = p[1] / d ; 
    }
    return r ;
}

// Dot product
double CS_POINT2D::operator*(const CS_POINT2D &pnt) 
{
    double d ; 
    d = (p[0] * pnt.p[0]) + (p[1] * pnt.p[1]) ;  
    return d ; 
}

// Scaling factor
CS_POINT2D CS_POINT2D::operator*(double s) 
{
    CS_POINT2D r ; 
    r.p[0] = p[0] * s ; 
    r.p[1] = p[1] * s ; 
    return r ; 
}

int CS_POINT2D::operator==(const CS_POINT2D &pnt)
{
    if (tcomp_NEQ(p[0], pnt.p[0]) || 
        tcomp_NEQ(p[1], pnt.p[1]))
        return 0 ; 
    return 1 ; 
}

int CS_POINT2D::operator!=(const CS_POINT2D &pnt)
{
    if (tcomp_NEQ(p[0], pnt.p[0]) || 
        tcomp_NEQ(p[1], pnt.p[1]))
        return 1 ; 
    return 0 ; 
}

void CS_POINT2D::Print(FILE *fp)
{
    if (!fp)
        fp = fpDebugOut ; 
    fprintf(fp, "(%.12lf, %.12lf)", p[0], p[1]) ; 
}

// Create a point from circular coordinates
CS_POINT2D CS_POINT2D_CIR(double r, double theta)
{
    CS_POINT2D p ; // resultant CS_VECTOR2D
    p.p[0] = r * cos(theta) ; 
    p.p[1] = r * sin(theta) ; 
    return p ; 
}

