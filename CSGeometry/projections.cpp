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
// projections.cpp

#include <assert.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_plane.h"




// See "The NURBS BOOK" pg 237, GEOM ALGO'S RR-Vol5 Pg 38
int CS_PLANE::Project(CS_POINT &inpnt, 
                      const CS_VECTOR &vprj, 
                      CS_POINT &prjpnt)
{
    // inpnt = Pi
    // p = Q
    // n = N
    // vprj = W
    // prjpnt = Pi'
    double NW = CS_DotProduct(n, vprj) ; 

    // NW > 0 = project forward in same direction as normal vector
    // dpq > 0 = point is behind the plane (relative to the plane normal vector)

    int retcode = CS_PROJECT_ERROR ; 
    double dpq ;
    try {
        CS_VECTOR vpq(inpnt, p) ; // Q - Pi
        dpq = CS_DotProduct(n, vpq) ; 
        prjpnt = inpnt + (vprj * (dpq / NW)) ; 
        if (dpq > 0)
        {
            if (NW > 0)
            {   // point behind, projecting forward
                retcode = CS_PROJ_RESULT | CS_POINT_BELOW_PLANE ; 
            }
            else
            {
                // Point behind, projecting back
                retcode = CS_PROJVEC_AWAYFROM_PLANE  | CS_POINT_BELOW_PLANE ; 
            }
        }
        else
        {   // dpq < 0
            if (NW > 0)
            {   // point in front, projecting forward
                retcode = CS_PROJVEC_AWAYFROM_PLANE | 
                       CS_POINT_ABOVE_PLANE ; // point behind, proj to front
            }
            else
            {
                // point in front, projecting back to plane, so OK
                retcode = CS_PROJ_RESULT | CS_POINT_ABOVE_PLANE ; 
            }
        }
    }
    catch (...)
    {
        if (dpq < 0)
        {
            retcode = CS_POINT_ABOVE_PLANE | CS_PROJVEC_PLLTO_PLANE ; 
        }
        else
        {
            retcode = CS_POINT_BELOW_PLANE | CS_PROJVEC_PLLTO_PLANE ; 
        }
    }
    return retcode ; 
}

int CS_PLANE::Project(CS_VECTOR &invec, 
                      const CS_VECTOR &vprj, 
                      CS_VECTOR &prjvec)
{
    CS_POINT pin(invec) ; 
    CS_POINT pprj ; 
    int stat = Project(pin, vprj, pprj) ; 
    prjvec.x = pprj.x ; 
    prjvec.y = pprj.y ; 
    prjvec.z = pprj.z ; 
    return stat ; 
}



// See GEOM ALGOS RR-Vol 5 Pg 48 for cases
int CS_PLANE::Project(CS_LineSeg *pls, 
                      const CS_VECTOR &prjvec, 
                      CS_LineSeg &lnout) 
{
    CS_POINT spp, epp ; // start and end point projections
    int spstat = Project(pls->sp, prjvec, spp) ; 
    int epstat = Project(pls->ep, prjvec, epp) ; 

    if (spstat & epstat & CS_PROJ_RESULT)
    {   // Then we generated two points 
        // This is the standard case where the line is either behind
        // or in front of the plane and it is projected to the plane
        lnout.sp = spp ; 
        lnout.ep = epp ; 
        return CS_PROJ_RESULT ; 
    }
    else if ((spstat | epstat) & CS_PROJ_RESULT)
    {   // Then the start point hit the plane and the end point 
        // did not, or vice-versa so the line crosses the plane, need
        // to calculate the intersection point of the line and plane. 
        // See GEOM ALGOS RR-Vol5 pgs 46-47
        
        CS_VECTOR vab(pls->sp, pls->ep) ; // vector a to b
        CS_VECTOR vaap(pls->sp, spp) ; // line aa' 
        CS_VECTOR vbbp(pls->ep, epp) ; // line bb' 
        double magAB = vab.Mag() ; 
        double A = vaap.Mag() ; 
        double B = vbbp.Mag() ; 
        vab = vab.Unit() ; 
    
        // pntI is the intersection point of the line and plane
        CS_POINT pntI = pls->sp + vab * (A / (A+B) * magAB) ; 
        if ((spstat | epstat) & CS_PROJVEC_PLLTO_PLANE)
        {   // Then there isn't really a result, but because the 
            // line crosses the plane, return the plane intersection point
            lnout.sp = pntI ; 
            lnout.ep = pntI ; 
            return CS_PROJVEC_PLLTO_PLANE | CS_PROJLINE_POINT ; 
        }

        if (spstat & CS_PROJ_RESULT)
        {
            lnout.sp = spp ; 
            lnout.ep = pntI ; 
        }
        else
        {
            lnout.sp = pntI ; 
            lnout.ep = epp ; 
        }
        return CS_PROJ_RESULT | CS_PROJLINE_PARTIAL ;  
    }
    
    // So there were no projection points created. Thus we either 
    // projected away from the plane, or parallel to it. 
    if ((spstat | epstat) & CS_PROJVEC_PLLTO_PLANE)
        return CS_PROJVEC_PLLTO_PLANE ; 
    else if ((spstat | epstat) & CS_PROJVEC_AWAYFROM_PLANE)
        return CS_PROJVEC_AWAYFROM_PLANE ; 

    assert(0) ; 
    return CS_PROJECT_ERROR ; // should never get here
}


int CS_PLANE::Project(CS_Curve &incrv, 
                      const CS_VECTOR &prjvec, 
                      CS_Curve &projCrvOut,
                      double *ptol, int mode)
{
    if (!incrv.pStart)
        return CS_PROJ_NULLPOINTER ;

    double npd = CS_DotProduct(prjvec, n) ;
    if (tcomp_EQZ(npd))
        return CS_PROJVEC_PLLTO_PLANE ; 

    int stat= 0 ; 
    int retstat = 0 ; 
    CS_SegPtr pseg = incrv.pStart ;  
    CS_LineSeg lsp ; 
    while (pseg)
    {
        stat = Project((CS_LineSeg *)pseg, prjvec, lsp) ; 
        retstat |= stat ; 
        if (stat & CS_PROJ_RESULT)
        {
            if (mode && projCrvOut.pEnd)
            {
                if (!tcomp_PointsEQ(lsp.sp.p, projCrvOut.pEnd->EndPoint().p, *ptol))
                {
                    projCrvOut.Append(new CS_LineSeg(projCrvOut.pEnd->EndPoint(), 
                                                     lsp.sp), CS_NOENDPOINTADJUSTMENT) ; 
                }
            }
            projCrvOut.Append(new CS_LineSeg(lsp), CS_NOENDPOINTADJUSTMENT) ; 
        }
        pseg = pseg->next ; 
    }

    return retstat ; 
}

// See GeomAlgos RR-Vol5 pg 74
double CS_PLANE::Distance(CS_POINT &r) 
{
    CS_VECTOR vpr = r - p ; 
    double d = CS_DotProduct(n, vpr) ; 
    double m = n.Mag() ; 
    return d / m ; 
}

double CS_PLANE::DistanceNorm(CS_POINT &r) 
{
    CS_VECTOR vpr = r - p ; 
    double d = CS_DotProduct(n, vpr) ; 
    return d ; 
}


