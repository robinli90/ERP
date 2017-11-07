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
// arcutils.cpp - functions to support processing of arcs


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


int CS_ArcToLinesInsideMode(CS_ARC &arc, double &tol, double &swpstep, int &nsteps)
{
    if (tcomp_EQZ(arc.rad))
        return -1 ; 
    double alpha = 4.0 * asin(sqrt(tol / (2.0 * arc.rad))) ; 
    if (tcomp_EQZ(alpha))
        return -2 ; 
    
    int n = (int)(fabs(arc.swp / alpha)) + 1 ; 
    swpstep = arc.swp / n ; 
    nsteps = n ; 
    return 0 ; 
}


// See notes Geom Algo's RR-Vol4 pgs173-184, especially 184
int CS_ArcToLines(CS_ARC &arc, double &tol, CS_Curve &crv, int mode)
{
    double swpstep ; 
    int nsteps ; 
    int retcode = CS_ArcToLinesInsideMode(arc, tol, swpstep, nsteps) ;
    if (retcode)
        return retcode ; 

    CS_POINT p0, p1 ; 
    crv.Reset() ; 
    p0 = arc.StartPoint() ; 

    for (int n=1; n <= nsteps; n++)
    {
        p1 = arc.UPoint(arc.AngleU(arc.sa + swpstep * (double)n)) ; 
        crv.Append(new CS_LineSeg(p0, p1), CS_NOENDPOINTADJUSTMENT) ; 
        p0 = p1 ; 
    }

    return 0 ; 
}


