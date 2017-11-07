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
// NMcrvfuncs.cpp - Numerical Method type curve functions

#pragma warning( disable : 4786 )

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
#include "cs_chain.h"
#include "cs_nmcurves.h"

CS_SegPtr CS_FastSegVector::Find(double x)
{
    // Note: an extra node is added to the end of the curve that has 
    // a null segment pointer
    int k = (int)vs.size() ; 

    if (x <= vs[0].x)
        return vs[0].pseg ; 
    if (x >= vs[k-1].x)
        return vs[k-1].pseg ; 

    int j = 0 ; 
    int i = (j+k) / 2 ; 
    
    // Binary search for alen
    do {
        if (x < vs[i].x) 
        {
            k = i ; 
            i = (j+k)/2 ; 
        }
        else if (tcomp_LEQ(x, vs[i+1].x))
        {   // Found the segment section
            return vs[i].pseg ; 
        }
        else
        {   // Then can keep moving up 
            j = i ; 
            i = (j+k)/2 ; 
        }
    } while(true) ;
    return 0 ; 
}








CS_PntCurveBuilder::CS_PntCurveBuilder()
{
    mode = NOMODE ; 
    np = 0 ; 
    pcrv = 0 ; 
}


//! Incorporate the point p into the arc. p should be close to one of the end 
//! points of the arc for this to work reliably. The point p must not be 
//! within the sweep of the arc otherwise the arc will end up being 
//! reduced in size (See notes Geom Algos RR.Vol-4 pg 130-131)
void CS_PntCurveBuilder::IncludeArcPoint(double pointangle)
{
    double alpha = arc.UAngle(0.5) ; 
    double beta =  mod2PI(alpha + RADIAN180) ; 
    double omega = (RADIAN360 - fabs(arc.swp)) / 2.0 ; 

    CS_ARC arcbsa, arcbea ; 
    if (arc.swp < 0)
    {
        arcbsa.sa = arc.sa ; 
        arcbsa.swp = omega ; 
        arcbea.sa = beta ; 
        arcbea.swp = omega ; 
    }
    else
    {
        arcbsa.sa = beta ; 
        arcbsa.swp = omega ; 
        arcbea.sa = arc.sa + arc.swp ; 
        arcbea.swp = omega ; 
    }

    if (arcbsa.AngleOnSweep(pointangle))
    {   // Then move the start angle
        if (arc.swp < 0)
            arc.swp -= arc_sweep(pointangle, arc.sa, CW) ; 
        else
            arc.swp += arc_sweep(pointangle, arc.sa, CCW) ; 
        
        arc.sa = pointangle ; 
    }
    else
    {   // Move the end angle 
        if (arc.swp < 0)
            arc.swp -= arc_sweep(arc.sa + arc.swp, pointangle, CW) ; 
        else
            arc.swp += arc_sweep(arc.sa + arc.swp, pointangle, CCW) ; 
    }
}


int CS_PntCurveBuilder::AddPoint(CS_POINT &nextpnt, CS_CrvPnt &cp) 
{
    double ut ; 
    if (mode == LINEMODE)
    {   
        if (line.PointOnLine(nextpnt, &ut))
        {   // Then want to absorb this point into the line
            if (ut < 0.0)
            {
                rcp[0] = cp ; 
                line.sp = nextpnt ; 
            }
            else if (ut > 1.0)
            {
                rcp[1] = cp ; 
                line.ep = nextpnt ;
            }
            else
            {   // moving backwards 
                int xxx = 0 ; 
                xxx ++ ; 
            }
        }
        else 
        {   // The point is not on the line so add the current line
            // segment to the curve being built and then reset for 
            // the next point
            CS_LineSeg *pls = new CS_LineSeg(line) ;
            pls->cp = rcp[0] ;
            pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ;
        
            mode = NEXTSEG ;
            rcp[0] = rcp[1] ;
            rcp[1] = cp ; 
            pl[0] = line.ep ; 
            pl[1] = nextpnt ; 
            np = 2 ; 
        }
    }
    else if (mode == ARCMODE)
    {   // Test if the point is on the circle defined by the arc
        CS_VECTOR vctr(arc.ctr, nextpnt) ;
        if (tcomp_EQ(vctr.Mag(), arc.rad))
        {   // Have to absorb this point into the arc, to do this want
            // to get a u coordinate for the point relative to the existing
            // arc and then adjust the start angle and sweep based on 
            // where this point falls. 
            if (!arc.PointOnArc(nextpnt, &ut))
            {   // Then have to figure out which end to extend
                double pointang = vctr.AngleXY() ;
                IncludeArcPoint(pointang) ;
                rcp[1] = cp ; 
            }
        }
        else
        {   // The point defines a new arc or line so save the current
            // arc and reset for next curve segment
            CS_ArcSeg *pas = new CS_ArcSeg(arc) ;
            pas->cp = rcp[0] ;
            pcrv->Append(pas, CS_NOENDPOINTADJUSTMENT) ; 

            mode = NEXTSEG ;
            rcp[0] = rcp[1] ;
            rcp[1] = cp ; 
            pl[0] = arc.EndPoint() ; 
            pl[1] = nextpnt ; 
            np = 2 ; 
        }
    }
    else
    {   // No mode currently active so see what type of curve we 
        // are building and set the state accordingly.
        if (np < 2)
        {   // Simply add the point to the list
            if (np == 0)
                rcp[0] = cp ; 
            else
                rcp[1] = cp ; 
            pl[np++] = nextpnt ; 
        }
        else
        {   // This is the third point
            // no should be 2 at this point so grab the last two points
            // plus the current point and figure out what mode to set. 
            if (CS_Collinear(pl[0], pl[1], nextpnt))
            {   // Then create a line
                rcp[1] = cp ; 
                line.sp = pl[0] ; 
                line.ep = nextpnt ; 
                np = 2 ; 
                mode = LINEMODE ; 
            }
            else
            {
                arc.Arc3Points(pl[0], pl[1], nextpnt) ;
                if (fabs(arc.swp) > RADIAN45)
                {
                    CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
                    pls->cp = rcp[0] ;
                    pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ;

                    mode = NEXTSEG ; 
                    rcp[0] = rcp[1] ; 
                    rcp[1] = cp ; 
                    pl[0] = pl[1] ; 
                    pl[1] = nextpnt ; 
                    np = 2 ; 
                }
                else
                {
                    rcp[1] = cp ; 
                    np = 2 ; 
                    mode = ARCMODE ; 
                }
            }
        }
    }
    return mode ; 
}

void CS_PntCurveBuilder::CompleteSegment()
{
    if (mode == LINEMODE)
    {
        CS_LineSeg *pls = new CS_LineSeg(line) ; 
        pls->cp = rcp[0] ;  
        pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (mode == ARCMODE)
    {
        CS_ArcSeg *pas = new CS_ArcSeg(arc) ; 
        pas->cp = rcp[0] ;  
        pcrv->Append(pas, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (np > 1)
    {   // In no mode, so take the last two points and add the line
        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
        pls->cp = rcp[0] ; 
        pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }

    // Now initialize the last point to the first point again. 
    rcp[0] = rcp[1] ; 
    pl[0] = pcrv->EndPoint() ; 
    np = 1 ; 
    mode = NOMODE ;
}


