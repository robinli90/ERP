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
// bezier.cpp


#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_cadfuncs.h"
#include "cs_bezier.h"

#ifndef max
#define max(a,b)    ((a > b) ? a : b)
#endif

CS_POINT CS_BezierPoint(CS_BezierCrv &ctrlPnts, double u)
{
    /* TODO - optimize this for N=3 thru N=6 into straight code without the loop counter
        For N=n (where N is the number of points)
         u0 = the desired point on the curve
         u1 = (1-u0)
         Pr = resultant point
         P0, P1, P2, Pn-1 are the input points

        N=3
            Pr = u1 * (u1 * P0 + u0 * P1) + u0 * (u1 * P1 + u0 * P2) 

        N=4
            Pr = u1 * (u1 * (u1 * P0 + u0 * P1) + u0 * (u1 * P1 + u0 * P2)) + 
                 u0 * (u1 * (u1 * P1 + u0 * P2) + u0 * (u1 * P2 + u0 * P3)) ; 

            and so on. 
    */ 

    CS_BezierCrv p = ctrlPnts ; // copy control points locally
    int n = (int)p.size() ; 
    double u1 = 1.0-u ; 

    // See notes 
    for (int i=1; i < n ; i++)
    {
        for (int j=0; j < n - i; j++)
            p[j] = (p[j] * u1) + (p[j+1] * u) ;
    }

    return p[0] ; 
}


// returns the iteration count for the pass through, iter is set to tolcount when 
// a new arc is initiated. 
static int ApproximateCurve(CS_Curve &rescrv, CS_BezierCrv &pvec, int tolcount, 
                            double us, double ue, const double &toldist)
{
    double um = (us+ue)/2.0 ; 
    CS_POINT ps = CS_BezierPoint(pvec, us) ; 
    CS_POINT pm = CS_BezierPoint(pvec, um) ; 
    CS_POINT pe = CS_BezierPoint(pvec, ue) ; 
    CS_ArcSeg *parc = new CS_ArcSeg ; 
    parc->Arc3Points(ps, pm, pe) ; 

    int i ; 
    double u ;
    double du = (ue - us) / (tolcount + 1) ;
    CS_POINT p ; 
        
    bool dosplit = false ;
    
    for (u = us + du, i = 0; i < tolcount; i++, u += du)
    {
        p = CS_BezierPoint(pvec, u) ; 
        if (!parc->PointOnArc(p, 0, 0, toldist))
        {
            dosplit = true ; 
            break ; 
        }
    }

    int divcount = 0 ; 
    if (dosplit)
    {
        delete parc ; 
        divcount = 1 ; 
        divcount += ApproximateCurve(rescrv, pvec, tolcount, us, um, toldist) ; 
        divcount += ApproximateCurve(rescrv, pvec, tolcount, um, ue, toldist) ; 
    }
    else
    {   // Add the arc to the result curve
        rescrv.Append(parc) ; 
    }

    return divcount ; 
}

int CS_BezierToCurve(CS_Curve &rescrv, CS_BezierCrv &pvec, 
                        double us, double ue, int tolcount, const double toldist)
{
    int retval = 0 ; 
    if (pvec.size() == 2)
    {   // Then we know it's a line segment so just add it
        rescrv.Append(new CS_LineSeg(pvec[0], pvec[1]), CS_NOENDPOINTADJUSTMENT) ; 
        return 0 ; // done.
    }

    double um = (us+ue)/2.0 ; 
    CS_POINT ps = CS_BezierPoint(pvec, us) ; 
    CS_POINT pm = CS_BezierPoint(pvec, um) ; 
    CS_POINT pe = CS_BezierPoint(pvec, ue) ; 
    
    CS_LineSeg ls(ps, pe) ; 
    if (ls.PointSide(pm) == CS_COLLINEAR)
    {   // Close enough to straight line so done
        rescrv.Append(new CS_LineSeg(ls), CS_NOENDPOINTADJUSTMENT) ; 
        retval = 0 ; 
    }
    else
    {
        int divcount = ApproximateCurve(rescrv, pvec, tolcount, us, ue, toldist) ;
    }

    return retval ; 
}
    

// Given the 4 input parameters works out the final P1 point
int CS_CalcBezierArcMidPnt(CS_POINT &P0, CS_POINT &P2, 
                           CS_VECTOR &vs, CS_VECTOR &ve,
                           CS_POINT &P1) 
{
    double u0 = 0 ; 
    double u2 = 0 ; 
    if (CS_LineLineNearestPoints(P0, vs, P2, ve, u0, u2) != CS_NONCOLLINEAR)
    {
        P1 = (P0+P2) * 0.5 ; 
        return -1 ;
    }

    CS_POINT pc = P0 + vs * u0 ; 
    CS_POINT qc = P2 + ve * u2 ; 
    P1 = (pc + qc) / 2.0 ; 

    return 0 ; 
}

    
