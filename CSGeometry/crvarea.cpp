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
// crvarea.cpp - Geometric processing routines related to CS_Curve's


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


// Local funtion prototypes 
int ArcSplitIntoQuads(CS_ArcSeg &arcin, CS_ArcSeg &quad1, CS_ArcSeg &quad2,
                      CS_ArcSeg &quad3, CS_ArcSeg &quad4) ;
double ArcIntegralArea(CS_ArcSeg &arc) ;


#define quad1_VALID        0x0001
#define quad2_VALID        0x0002
#define quad3_VALID        0x0004
#define quad4_VALID        0x0008


#define DEBUGARCS(a)        a 


/////////////////////////////////////////////////////////////////////////////
// See Notes: RR-VOL3 pgs 158-166 for reference to the equations used as well
// as the variables and what they represent
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// Integral equations for Arc area centroid calculations
/////////////////////////////////////////////////////////////////////////

inline double YBarArcNum(double &x, double &r, double &cx, double &cy)
{
    double cosx = cos(x) ; 
    double sinx = sin(x) ; 
    return r * ((-r * r * cosx * cosx * cosx / 3.0) + 
                (r * cx * sinx * sinx / 2.0) +  
                (r * cy * (x / 2.0 + sin(2.0 * x) / 4.0)) + (cx * cy * sinx)) ;
}

inline double YBarArcDen(double &x, double &r, double &cx) 
{
    return r * ((r * (x / 2.0 + sin(2.0 * x) / 4.0)) + cx * sin(x)) ; 
}

void YBarArcAreaCentroid(CS_ArcSeg &arc, double &area, double &ybar)
{
    double ea = arc.sa + arc.swp ; 

    area = YBarArcDen(ea, arc.rad, arc.ctr.x) - 
            YBarArcDen(arc.sa, arc.rad, arc.ctr.x) ;
    
    if (tcomp_NEZ(area))
        ybar = (YBarArcNum(ea, arc.rad, arc.ctr.x, arc.ctr.y) - 
            YBarArcNum(arc.sa, arc.rad, arc.ctr.x, arc.ctr.y)) / area ; 
    else
        ybar = 0.0 ; 
}


inline double XBarArcNum(double &x, double &r, double &cx, double &cy)
{
    double cosx = cos(x) ; 
    double sinx = sin(x) ; 
    return -r * ((r * r * sinx * sinx * sinx / 3.0) + 
                (r * cy * sinx * sinx / 2.0) +  
                (r * cx * (x / 2.0 - sin(2.0 * x) / 4.0)) - (cx * cy * cosx)) ;
}

inline double XBarArcDen(double &x, double &r, double &cy) 
{
    return -r * ((r * (x / 2.0 - sin(2.0 * x) / 4.0)) - cy * cos(x)) ; 
}

void XBarArcAreaCentroid(CS_ArcSeg &arc, double &area, double &xbar)
{
    double ea = arc.sa + arc.swp ; 

    area = XBarArcDen(ea, arc.rad, arc.ctr.y) - 
            XBarArcDen(arc.sa, arc.rad, arc.ctr.y) ;

    if (tcomp_NEZ(area))
        xbar = (XBarArcNum(ea, arc.rad, arc.ctr.x, arc.ctr.y) - 
                XBarArcNum(arc.sa, arc.rad, arc.ctr.x, arc.ctr.y)) / area ; 
    else
        xbar = 0.0 ; 
}



void ArcAreaCentroidIntegral(CS_ArcSeg &arc, CS_POINT &centroid, double &xarea, double &yarea)
{
    XBarArcAreaCentroid(arc, xarea, centroid.x) ; 
    YBarArcAreaCentroid(arc, yarea, centroid.y) ; 
}


/////////////////////////////////////////////////////////////////////////
// Integral equations for Line area centroid calculations
/////////////////////////////////////////////////////////////////////////

void LineAreaCentroidIntegral(CS_LineSeg &line, CS_POINT &centroid, double &xarea, double &yarea)
{
    double b, m ; 
    line.LineParameters2D(m, b) ; 
    double x0, x1 ; 
    x0 = line.sp.x ; 
    x1 = line.ep.x ; 

    xarea = (m * x1 * x1 / 2.0 + b * x1) - (m * x0 * x0 / 2.0 + b * x0) ;

    double xnum = (m * x1 * x1 * x1 / 3.0 + b * x1 * x1 / 2.0) 
                        - (m * x0 * x0 * x0 / 3.0 + b * x0 * x0 / 2.0) ;


    // Now work out the variables to process everything for area above
    // and below the Y axis. Everything is rotated 90degrees from 
    // the normal orientation
    CS_VECTOR v(line.sp, line.ep) ; 
    if (tcomp_EQZ(v.v[1])) 
    {   // Vertical line (i.e parallel to y-axis)
        m = 0.0 ; 
        b = 0.0 ; 
    }
    else
    {
        m = v.x / v.y ; 
        b = -(m * line.sp.y) + line.sp.x ; 
    }

    x0 = line.sp.y ; 
    x1 = line.ep.y ; 

    yarea = (m * x1 * x1 / 2.0 + b * x1) - (m * x0 * x0 / 2.0 + b * x0) ;

    double ynum = (m * x1 * x1 * x1 / 3.0 + b * x1 * x1 / 2.0) 
                        - (m * x0 * x0 * x0 / 3.0 + b * x0 * x0 / 2.0) ;

    if (tcomp_NEZ(xarea))
        centroid.x = xnum / xarea ; 
    else
        centroid.x = 0 ; 

    if (tcomp_NEZ(yarea))
        centroid.y = ynum / yarea ; 
    else
        centroid.y = 0 ; 
}

CS_POINT CS_Curve::AreaCentroid()
{
    if (!Closed())
        return CS_POINT(0,0,0) ; 

    CS_SegPtr psn = pStart ; 
    double xarea = 0.0 ; 
    double yarea = 0.0 ; 
    double xbar = 0.0 ; 
    double ybar = 0.0 ; 
    CS_POINT centroid ; 
    CS_POINT pnt ; 

    double sumXAXI = 0.0 ; 
    double sumAXI = 0.0 ; 

    double sumYAYI = 0.0 ; 
    double sumAYI = 0.0 ; 
    
    while (psn) 
    {
        if (psn->SegmentType() == CS_Segment::ARC_TYPE)
        {
            ArcAreaCentroidIntegral(*(CS_ArcSeg *)psn, pnt, xarea, yarea) ; 
        }
        else
        {
            LineAreaCentroidIntegral(*(CS_LineSeg *)psn, pnt, xarea, yarea) ; 
        }
        sumXAXI += pnt.x * xarea ; 
        sumAXI += xarea ; 
        sumYAYI += pnt.y * yarea ; 
        sumAYI += yarea ; 

        psn = psn->next ; 
    }

    return CS_POINT(sumXAXI / sumAXI, sumYAYI /  sumAYI, 0.0) ; 
}

double ArcIntegralArea(CS_ArcSeg &arc)
{
    double r = arc.rad ; 
    double alpha = arc.sa ; 
    double beta = arc.sa + arc.swp ; 
    double d1, d2 ; 
    double area ; 

    d1 = arc.ctr.p[1] * (cos(beta) - cos(alpha)) ;
    d2 = (beta / 2.0) - (sin(2.0 * beta) / 4.0) - 
         (alpha / 2.0) + (sin(2.0 * alpha) / 4.0) ;
    
    area = r * (d1 - (r * d2)) ; 

    return area ; 
}


//////////////////////////////////////////////////////////////////////////
// Might want to change the area function later so that CW=+ve which
// would be consistent with the way the integral works out automatically
// The current convention was used because it conforms to the definition
// in a Calculus text on how Green's Functions are oriented and calculated
// When integrating with polar coordinates, it makes more sense to have 
// positive areas in the CCW direction, but in Cartesian coordinates the 
// reverse is true - sort of. 
//////////////////////////////////////////////////////////////////////////
// CCW curve = +ve area, CW curve = -ve area
double CS_Curve::Area()
{
    if (!Closed())
        return 0.0 ;

    double areatmp ; 
    double area = 0.0 ; 

    CS_SegPtr pn = pStart ;
    CS_ArcSeg quad1, quad2, quad3, quad4 ;
    double m, b ;
    CS_VECTOR vvert(0,1,0) ;

    // Loop through and calculate the area for each of the curves
    while (pn)
    {
        if (pn->SegmentType() == CS_Segment::LINE_TYPE)
        {   // Add in the area for the line segment
            CS_LineSeg *pls = (CS_LineSeg *)pn ; 
            CS_VECTOR vseg(pls->sp, pls->ep) ; 
            
            if (!tcomp_EQZ(vseg.v[0]))
            {   // Then we don't have a vertical line segment so it's
                // OK to calculate the area under this section of the 
                // curve.
                pls->LineParameters2D(m, b) ; 

                // area from integral equation
                areatmp = (m * (pls->ep.p[0] * pls->ep.p[0] - 
                                pls->sp.p[0] * pls->sp.p[0]) / 2.0) +
                          (b * (pls->ep.p[0] - pls->sp.p[0])) ; 

                // Do not need to work out if the curve goes left or right
                // since this is handled by the direction of the x values 
                // from sp to ep if ep is left of sp, then due to the
                // orientation of the integral limits we will get a 
                // negative result.
           
                area += areatmp ; 
            }
        }
        else if (pn->SegmentType() == CS_Segment::ARC_TYPE)
        {
            area += ArcIntegralArea(*((CS_ArcSeg *)pn)) ; 

            /*
            // use this code section to test ArcSplitNorthSouth()
            int validarcs ; 
            validarcs = ArcSplitNorthSouth(*((CS_ArcSeg *)pn->pseg), 
                                    quad1, quad2, quad3, quad4) ;

            // Now add in the areas under all the arcs
            if (validarcs & quad1_VALID)
                area += ArcIntegralArea(quad1) ; 
            
            if (validarcs & quad2_VALID)
                area += ArcIntegralArea(quad2) ; 
            
            if (validarcs & quad3_VALID)
                area += ArcIntegralArea(quad3) ; 
            
            if (validarcs & quad4_VALID)
                area += ArcIntegralArea(quad4) ; 
            */
        }

        pn = pn->next ; 
    }

    return -area ;
}


// Returns the value of the flag indicating which return arcs are valid
// The input arc cannot have a sweep > 360 degrees. If it does then this 
// logic will return invalid results 
int ArcSplitIntoQuads(CS_ArcSeg &arcin, 
                       CS_ArcSeg &quad1, CS_ArcSeg &quad2,
                       CS_ArcSeg &quad3, CS_ArcSeg &quad4)
{
    int validarcs = 0 ;
    double sa, ea ;

    // Want sa and ea based on a CCW arc
    if (arcin.swp > 0)
    {
        sa = mod2PI(arcin.sa) ;
        ea = sa + arcin.swp ;
    }
    else
    {
        sa = mod2PI(arcin.sa + arcin.swp) ; 
        ea = sa - arcin.swp ; // adding sweep since swp < 0 in this case
    }

    // sa, ea are oriented CCW and sa < ea is guaranteed

    DEBUGARCS(fprintf(fpDebugOut, "Splitting arc\n") ; arcin.Print(fpDebugOut) ; ) ;

    if (sa >= RADIAN180)
    {   // The input arc starts in the southern hemisphere
        if (ea > RADIAN360)
        {   // Then it crosses into north so we want to split the arc into
            // at least 2 segments, possibly 3 segments
            validarcs |= quad3_VALID ;
            validarcs |= quad1_VALID ;
            
            quad3.ctr = arcin.ctr ; 
            quad3.sa = sa ; 
            quad3.swp = RADIAN360 - sa ; 
            quad3.rad = arcin.rad ; 
            if (arcin.ArcDir() == CW)
                quad3.Reverse() ; 
            
            quad1.ctr = arcin.ctr ; 
            quad1.sa = 0.0 ; 
            quad1.rad = arcin.rad ; 
            quad1.swp = fabs(arcin.swp) - fabs(quad3.swp) ; 
            if (arcin.ArcDir() == CW)
                quad1.Reverse() ; 

            DEBUGARCS(
                fprintf(fpDebugOut, "Into quad3=\n") ; quad3.Print(fpDebugOut) ; 
                fprintf(fpDebugOut, " and quad1=\n") ; quad1.Print(fpDebugOut) ; 
                ) ; 
            
            if (fabs(quad1.swp) > RADIAN180)
            {   // This is the 3 arc sections case
                validarcs |= quad4_VALID ; 
                
                quad4.ctr = arcin.ctr ; 
                quad4.sa = RADIAN180 ; 
                quad4.rad = arcin.rad ; 
                quad4.swp = fabs(quad1.swp) - RADIAN180 ;
                if (arcin.ArcDir() == CW)
                    quad4.Reverse() ; 

                DEBUGARCS(
                    fprintf(fpDebugOut, " and quad4=\n") ; quad4.Print(fpDebugOut) ; 
                ) ; 

                if (arcin.ArcDir() == CCW)
                    quad1.swp = RADIAN180 ; 
                else
                    quad1.swp = -RADIAN180 ;
            }
            
            DEBUGARCS(fprintf(fpDebugOut, "\n"))  ; 
        }
        else
        {   // We only have the quad3 arc to worry about
            validarcs |= quad3_VALID ;
            quad3 = arcin ; 
            DEBUGARCS(
                fprintf(fpDebugOut, "quad3 only=\n") ; quad3.Print(fpDebugOut) ; 
                fprintf(fpDebugOut, "\n") ;
            ) ; 
        }
    }
    else
    {   // The input arc starts in the northern hemisphere
        if (ea > RADIAN180)
        {   // Then it crosses into south so we want to split the arc into
            // at least 2 segments, possibly 3 segments
            validarcs |= quad1_VALID ;
            validarcs |= quad3_VALID ;             
            
            quad1.ctr = arcin.ctr ; 
            quad1.sa = sa ; 
            quad1.rad = arcin.rad ; 
            quad1.swp = RADIAN180 - sa ; 
            if (arcin.ArcDir() == CW)
                quad1.Reverse() ; 
            
            quad3.ctr = arcin.ctr ; 
            quad3.sa = RADIAN180 ; 
            quad3.swp = fabs(arcin.swp) - fabs(quad1.swp) ;
            quad3.rad = arcin.rad ; 
            if (arcin.ArcDir() == CW)
                quad3.Reverse() ; 

            DEBUGARCS(
                fprintf(fpDebugOut, "Into quad1=\n") ; quad1.Print(fpDebugOut) ; 
                fprintf(fpDebugOut, " and quad3=\n") ; quad3.Print(fpDebugOut) ; 
                ) ; 

            if (fabs(quad3.swp) > RADIAN180)
            {   // This is the 3 arc sections case
                validarcs |= quad2_VALID ; 
                
                quad2.ctr = arcin.ctr ; 
                quad2.sa = 0.0 ; 
                quad2.rad = arcin.rad ; 

                quad2.swp = fabs(quad3.swp) - RADIAN180 ;
                if (arcin.ArcDir() == CW)
                    quad2.Reverse() ; 

                DEBUGARCS(
                    fprintf(fpDebugOut, " and quad2=\n") ; quad2.Print(fpDebugOut) ; 
                ) ; 

                if (arcin.ArcDir() == CCW)
                    quad3.swp = RADIAN180 ; 
                else
                    quad3.swp = -RADIAN180 ;
            }
            DEBUGARCS(fprintf(fpDebugOut, "\n"))  ; 
        }
        else
        {   // We only have the quad1 arc to worry about
            validarcs |= quad1_VALID ;
            quad1 = arcin ;
             DEBUGARCS(
                fprintf(fpDebugOut, "quad1 only=\n") ; quad1.Print(fpDebugOut) ; 
                fprintf(fpDebugOut, "\n") ;
            ) ; 
       }
    }
    return validarcs ; 
}