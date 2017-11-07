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
// crvAreaMoments.cpp


#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)	
#else
#define CS_DEBUG(a)
#endif


inline double arcIyIntegrand(double a, double r, double x, double y)
{
    return -r * r * r * r * (a / 8.0 - sin(4.0 * a) / 32.0) + 
           -(2.0 * r * r * r * x * pow(sin(a), 3.0) / 3.0) + 
           -(r * r * x * x * (a / 2.0 - sin(2.0 * a) / 4.0)) + 
            (r * r * r * y * pow(cos(a), 3.0) / 3.0) + 
           -(r * r * x * y * sin(a) * sin(a)) +
            (r * x * x * y * cos(a)) ;
}

inline double arcIxIntegrand(double a, double r, double x, double y)
{
    return r * r * r * r * (a / 8.0 - sin(4.0 * a) / 32.0) + 
          -(2.0 * r * r * r * y * pow(cos(a), 3.0) / 3.0) + 
           (r * r * y * y * (a / 2.0 + sin(2.0 * a) / 4.0)) + 
           (r * r * r * x * pow(sin(a), 3.0) / 3.0) + 
           (r * r * x * y * sin(a) * sin(a)) +
           (r * x * y * y * sin(a)) ;
}



double XArcAreaMomentOfInertia(CS_ArcSeg *pa)
{
    return  arcIxIntegrand(pa->sa + pa->swp, pa->rad, pa->ctr.x, pa->ctr.y) - 
            arcIxIntegrand(pa->sa, pa->rad, pa->ctr.x, pa->ctr.y) ; 
}

double YArcAreaMomentOfInertia(CS_ArcSeg *pa)
{
    return  arcIyIntegrand(pa->sa + pa->swp, pa->rad, pa->ctr.x, pa->ctr.y) - 
            arcIyIntegrand(pa->sa, pa->rad, pa->ctr.x, pa->ctr.y) ; 
}

double XLineAreaMomentOfInertia(CS_LineSeg *pl)
{
    CS_VECTOR v(pl->sp, pl->ep) ; 
    if (tcomp_EQZ(v.y)) 
    {   // Vertical line (i.e parallel to y-axis)
        return 0 ; 
    }

    double b, m ; 
    m = v.x / v.y ; 
    b = -(m * pl->sp.y) + pl->sp.x ; 
    double x0, x1 ; 
    x0 = pl->sp.y ; // limits of integration start
    x1 = pl->ep.y ; // limits of integration end

    return (x1 * x1 * x1 * (m * x1 / 4.0 + b / 3.0)) - 
           (x0 * x0 * x0 * (m * x0 / 4.0 + b / 3.0)) ;
}


double YLineAreaMomentOfInertia(CS_LineSeg *pl)
{
    CS_VECTOR v(pl->sp, pl->ep) ; 
    if (tcomp_EQZ(v.x)) 
    {   // Vertical line (i.e parallel to y-axis)
        return 0 ; 
    }

    double b, m ; 
    pl->LineParameters2D(m, b) ; 
    double x0, x1 ; 
    x0 = pl->sp.x ; // limits of integration start
    x1 = pl->ep.x ; // limits of integration end

    return (x1 * x1 * x1 * (m * x1 / 4.0 + b / 3.0)) - 
           (x0 * x0 * x0 * (m * x0 / 4.0 + b / 3.0)) ;
}


// Calculate the area moments of inertia for the closed area defined
// by the *this curve. If the curve is not closed Ix and Iy are not
// modified and 1 is returned, else 0 is returned. 
// By default, (when pref=NULL ) the Ix, and Iy
// values returned are relative to the X and Y axes respectively. 
// To generate the centroidal area moment of inertia result, 
// pass the centroid point for the area in pcentroid. 
//  The forumlas used to shift to centroid position are:
//   Ix = Ixo + Adx^2
//   Iy = Iyo + Ady^2 
// where Ixo, Iyo are the centroidal area moments of inertia. 
// A is the area, and dx and dy are the distances of the centroid
// from the x and y axes respectively. 

int CS_Curve::AreaMomentOfInertia(double &Ix, double &Iy, CS_POINT *pcentroid)
{
    if (!Closed())
        return 1 ; 

    CS_SegPtr psn = pStart ; 

    double sumIx = 0.0 ; 
    double sumIy = 0.0 ; 

    while (psn) 
    {
        if (psn->SegmentType() == CS_Segment::ARC_TYPE)
        {
            sumIx += XArcAreaMomentOfInertia((CS_ArcSeg *)psn) ; 
            sumIy += YArcAreaMomentOfInertia((CS_ArcSeg *)psn) ; 
        }
        else
        {
            sumIx += XLineAreaMomentOfInertia((CS_LineSeg *)psn) ; 
            sumIy += YLineAreaMomentOfInertia((CS_LineSeg *)psn) ; 
        }

        psn = psn->next ; 
    }

    Ix = fabs(sumIx) ; 
    Iy = fabs(sumIy) ; 

    // Now adjust to the reference point if required
    if (pcentroid)
    {   // Need to do more calculations
        double A = fabs(Area()) ; 
        Ix -= A * (pcentroid->y * pcentroid->y) ; 
        Iy -= A * (pcentroid->x * pcentroid->x) ; 
    }

    return 0 ; 
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//                          /
// Product of Inertia  Ixy=|xydxdy
//                         / 
//                        A
// 
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

inline double arcIxyIntegrand(double a, double r, double x, double y)
{
    double r2 = r * r ; 
    double r3 = r * r * r ; 
    return r * 0.5 * 
               ((-r3 * pow(cos(a), 4.0) / 4.0) +
                (-2.0 * r2 * x * pow(cos(a), 3.0) / 3.0) + 
                (r * x * x * sin(a) * sin(a) / 2.0) +
                (r2 * y / 3.0 * (cos(a) * cos(a) * sin(a) + 2.0 * sin(a))) + 
                (2.0 * r * x * y * (a / 2.0 + sin(2.0 * a) / 4.0)) + 
                (x * x * y * sin(a))
               ) ;
}




double ArcAreaProductOfInertia(CS_ArcSeg *pa)
{
    return  arcIxyIntegrand(pa->sa + pa->swp, pa->rad, pa->ctr.x, pa->ctr.y) - 
            arcIxyIntegrand(pa->sa, pa->rad, pa->ctr.x, pa->ctr.y) ; 
}

double LineAreaProductOfInertia(CS_LineSeg *pl)
{
    CS_VECTOR v(pl->sp, pl->ep) ; 
    // Using the transformed x/y axis since the arc equation used dy's and not dx's
    if (tcomp_EQZ(v.y)) 
    {   // Horizontal line (i.e parallel to x-axis)
        return 0 ; 
    }

    double b, m ; 
    m = v.x / v.y ; 
    b = -(m * pl->sp.y) + pl->sp.x ; 
    double x0, x1 ; 
    x0 = pl->sp.y ; // limits of integration start
    x1 = pl->ep.y ; // limits of integration end

    return 0.5 * ((x1 * x1 * (m * m * x1 * x1 / 4.0 + 2.0 * m * b * x1 / 3.0 + b * b / 2.0)) - 
                  (x0 * x0 * (m * m * x0 * x0 / 4.0 + 2.0 * m * b * x0 / 3.0 + b * b / 2.0))) ; 
}


/*
    Y axis code if required
double LineAreaProductOfInertia(CS_LineSeg *pl)
{
    CS_VECTOR v(pl->sp, pl->ep) ; 
    if (tcomp_EQZ(v.x) || tcomp_EQZ(v.y)) 
    {   // Vertical or horizontal line (i.e parallel to y or x axis)
        return 0 ; 
    }

    double b, m ; 
    pl->LineParameters2D(m, b) ; 
    double y0, y1 ; 
    y0 = pl->sp.y ; // limits of integration start
    y1 = pl->ep.y ; // limits of integration end

    return -0.5 / m / m *
                ((y1 * y1 * (y1 * y1 / 4.0 - 2.0 * b * y1 / 3.0 + b * b / 2.0)) - 
                 (y1 * y1 * (y1 * y1 / 4.0 - 2.0 * b * y1 / 3.0 + b * b / 2.0))) ; 
}
*/

// If the centroid parameter is passed in then the Ixy value is adjusted 
// to the centroid of the area as defined by the point passed in. The 
// formula used is:
//    Ixy = Ixyc + dxdyA 
// Where Ixy is the product of inertia relative to the X and Y axes,
// Ixyc is the product of inertia relative to the centroid, and 
// dx,dy  are simply the distance to the centroid from the X and Y
// axes respectively. A is the area of the enclosed region. 

int CS_Curve::AreaProductOfInertia(double &Ixy, CS_POINT *pcentroid)
{
    if (!Closed())
        return 1 ; 

    SetDirection(CCW) ; 
    CS_SegPtr psn = pStart ; 

    double sumIxy = 0.0 ; 

    while (psn) 
    {
        if (psn->SegmentType() == CS_Segment::ARC_TYPE)
        {
            sumIxy += ArcAreaProductOfInertia((CS_ArcSeg *)psn) ; 
        }
        else
        {
            sumIxy += LineAreaProductOfInertia((CS_LineSeg *)psn) ; 
        }

        psn = psn->next ; 
    }

    Ixy = sumIxy ; 
    
    // Now adjust to the reference point if required
    if (pcentroid)
    {   // Need to do more calculations
        double A = fabs(Area()) ; 
        Ixy -= A * (pcentroid->x * pcentroid->y) ; 
    }


    return 0 ; 

}



CS_VECTOR CS_Curve::PrincipalAxis(int mode)
{
    CS_VECTOR vpamax ; // vector of the principal axis for Imax
    if (!Closed()) 
        return vpamax ; // null result

    double alpha1 = 0.0 ; 
    double Ix     = 0.0 ; 
    double Iy     = 0.0 ; 
    double Ixy    = 0.0 ; 

    CS_POINT centroid = AreaCentroid() ; 
    AreaMomentOfInertia(Ix, Iy, &centroid) ; 
    AreaProductOfInertia(Ixy, &centroid) ; 

    if (tcomp_EQZ(Ixy))
    {
        alpha1 = 0.0 ; 
    }
    else if (tcomp_EQ(Ix, Iy))
    {   // Then the angle is +/-45 degrees
        alpha1 = RADIAN45 ; 
    }
    else
    {
        alpha1 = atan(2.0 * Ixy / (Iy - Ix)) / 2.0 ; 
    }

    vpamax = CS_VECTOR(1,0,0) ; 
    double alpha2 = alpha1 + RADIAN90 ; 

    // See which axis is maximum
    double I1 = (Ix + Iy) / 2.0 + (Ix - Iy) / 2.0 * cos(2.0 * alpha1)
                                - Ixy * sin(2.0 * alpha1) ; 
    double I2 = (Ix + Iy) / 2.0 + (Ix - Iy) / 2.0 * cos(2.0 * alpha2)
                                - Ixy * sin(2.0 * alpha2) ; 

    if (mode == CS_MINIMUM)
    {
        if (I1 < I2)
            vpamax.Rotate(alpha1) ; 
        else 
            vpamax.Rotate(alpha2) ; 
    }
    else
    {   // Want the maximum angle
        if (I1 > I2)
            vpamax.Rotate(alpha1) ; 
        else 
            vpamax.Rotate(alpha2) ; 
    }

    return vpamax ; 
}
