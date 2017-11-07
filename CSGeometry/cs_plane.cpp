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
// cs_plane.cpp

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_plane.h"


// The intersection of a line segment with a plane
int CS_PLANE::Intersect(CS_LineSeg &ls, CS_POINT &ipnt, double *useg)
{
    double num = CS_DotProduct(n, CS_VECTOR(ls.sp, p)) ; 
    double den = CS_DotProduct(n, CS_VECTOR(ls.sp, ls.ep)) ; 
    if (tcomp_EQZ(den))
        return -1 ; 
    double u = num / den ; 
    ipnt = ls.UPoint(u) ; 

    if (useg)
        *useg = u ; 

    if (tcomp_GEQ(u, 0.0) && tcomp_LEQ(u, 1.0))
        return 0 ; // line intersects with the plane
    return 1 ; // line does not intersect the plane
}


// The intersection of a line segment with a plane
int CS_PLANE::Intersect(CS_POINT &sp, CS_POINT &ep, CS_POINT &ipnt, double *useg)
{
    double num = CS_DotProduct(n, CS_VECTOR(sp, p)) ; 
    double den = CS_DotProduct(n, CS_VECTOR(sp, ep)) ; 
    if (tcomp_EQZ(den))
        return -1 ; 
    double u = num / den ; 
    CS_LineSeg ls(sp, ep) ; 
    ipnt = ls.UPoint(u) ; 

    if (useg)
        *useg = u ; 

    if (tcomp_GEQ(u, 0.0) && tcomp_LEQ(u, 1.0))
        return 0 ; 
    return 1 ; 
}



bool CS_PLANE::operator==(const CS_PLANE &b)
{
    if (tcomp_EQ(fabs(CS_DotProduct(n, b.n)), 1.0))
    {
        if (PointSide(b.p) == CS_POINT_ON_PLANE)
        {   // Then these planes are equivalent
            return true ; 
        }
    }
    return false ; 
}

int CS_PLANE::PointSide(const CS_POINT &pnt)
{   
    int side = 0 ;
    CS_VECTOR vp(p, pnt) ; 
    double dp = CS_DotProduct(vp, n) ; 

    if (tcomp_EQZ(dp))
    {
        side = CS_POINT_ON_PLANE ; 
    }
    else 
    {
        if (tcomp_GT(dp, 0)) 
            side |= CS_POINT_ABOVE_PLANE ; 
        else 
            side |= CS_POINT_BELOW_PLANE ; 
    }
    return side ; 
}


// See Geom Algo's RR-Vol5 pg 41
CS_POINT CS_PLANE::NearestPoint(CS_POINT &pnt, int *stat)
{   
    CS_VECTOR vp(p, pnt) ; 
    double dp = CS_DotProduct(vp, n) ; 

    if (stat)
    {
        if (tcomp_EQZ(dp))
        {
            *stat = CS_POINT_ON_PLANE ; 
            if (p == pnt)
                *stat |= CS_POINT_ALONG_NORMAL ; 
            return pnt ; 
        }
        else 
        {
            if ( tcomp_EQ( fabs(dp), vp.Mag() ) ) 
                *stat = CS_POINT_ALONG_NORMAL ;

            if (tcomp_GT(dp, 0)) 
                *stat |= CS_POINT_ABOVE_PLANE ; 
            else 
                *stat |= CS_POINT_BELOW_PLANE ; 
        }
    }

    CS_POINT pntOnPlane = pnt - (n * dp) ; 
    return pntOnPlane ; 
}


int CS_PLANE::PlaneBy3Points(CS_POINT &p1, CS_POINT &p2, CS_POINT &p3)
{
    CS_VECTOR p1p2(p1, p2) ; 
    CS_VECTOR p1p3(p1, p3) ; 

    CS_VECTOR vx = p1p2 * p1p3 ; 
    if (tcomp_EQZ(vx.Mag()))
        return -1 ; 

    n = vx.Unit() ; 
    p = p1 ; 
    return 0 ; 
}
