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
// linegeom.cpp - CS_LineSeg member functions and supporting functions

/////////////////////////////////////////////////////////////////////////
// LINE
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_vectors.h"
#include "cs_curves.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif


//////////////////////////////////
//////////////////////////////////
//  Basic CS_LINE class methods //
//////////////////////////////////
//////////////////////////////////
void CS_LINE::Reverse() 
{
    CS_POINT tmppnt ; 
    tmppnt = sp ; 
    sp = ep ;
    ep = tmppnt ; 
}

CS_POINT CS_LINE::UPoint(double u)
{
    CS_POINT p ;
    CS_VECTOR v(sp, ep) ;

    v = v * u ;
    p = sp + v ;

    CS_DEBUG(fprintf(fpDebugOut, "Line upoint(%.5lf)=(%.5lf %.5lf %.5lf)\n",
		u, p.p[0], p.p[1], p.p[2]) ; )
    return p ;
}

void CS_LINE::MTX3Mult(CS_MTX3 &m)
{   // Transform the end points of the line segment
    sp = m * sp ;
    ep = m * ep ;
}

void CS_LINE::Scale(double s)
{
    sp = sp * s ;
    ep = ep * s ;
}

void CS_LINE::Move(CS_VECTOR &v)
{
    sp = sp + v ;
    ep = ep + v ;
}

void CS_LINE::SetZ(double z)
{
    sp.z = z ; 
    ep.z = z ; 
}

void CS_LINE::Transform(double p[12])
{
    CS_MTX3 m3 ; 
    m3.m[0] = p[0] ; 
    m3.m[1] = p[1] ; 
    m3.m[2] = p[2] ; 
    m3.m[3] = p[4] ; 
    m3.m[4] = p[5] ; 
    m3.m[5] = p[6] ; 
    m3.m[6] = p[8] ; 
    m3.m[7] = p[9] ; 
    m3.m[8] = p[10] ; 

    MTX3Mult(m3) ; 

    Move(CS_VECTOR(p[3], p[7], p[11])) ; 
}

CS_POINT CS_LINE::MidPoint()
{
    CS_POINT mpnt ;
    mpnt = (ep + sp) / 2.0 ;
    return mpnt ;
}

CS_POINT CS_LINE::StartPoint()
{
    return sp ;
}

CS_POINT CS_LINE::EndPoint()
{
    return ep ;
}

double CS_LINE::ArcLength(void)
{
    CS_VECTOR v(sp, ep) ;
    return v.Mag() ;
}

double CS_LINE::XY_ArcLength(void)
{
    CS_VECTOR v(sp, ep) ;
    v.v[2] = 0.0 ;
    return v.Mag() ;
}

CS_POINT CS_LINE::Centroid(void)
{
    return MidPoint() ; 
}

CS_POINT CS_LINE::Centroid2D(void)
{
    CS_POINT p = MidPoint() ; 
    p.z = 0.0 ; 
    return p ;
}


CS_VECTOR CS_LINE::UTangent(double u)
{
    // For a line segment the tangent vector is simply the line
    // end point vector
    CS_VECTOR vtan(sp, ep) ;
    vtan = vtan.Unit() ;
    return vtan ;
}

int CS_LINE::PointSide(CS_POINT &p)
{
    CS_VECTOR vsp(sp, p) ; 
    CS_VECTOR vpe(p, ep) ; 
    double zc = ZCross(vsp, vpe) ;

    if (zc < 0)
        return CS_LEFTSIDE ;
    else if (zc > 0)
        return CS_RIGHTSIDE ; 
    return CS_COLLINEAR ;
}

int CS_LINE::Offset(double delta)
{
    CS_VECTOR ov(sp, ep) ; // create tangent vector
    ov = ov.Unit() ; // make it a unit vector
    // Now set the offset direction
    ov = ov.RightPerp() ;
    // scale the vector to the offset amount
    // -ve delta will offset to the left
    ov = ov * delta ;
    sp = sp + ov ;
    ep = ep + ov ;
    return 0 ; 
}

int CS_LINE::AdjustStartPoint(CS_POINT &pnt)
{
    sp = pnt ;
    return 0 ;
}

int CS_LINE::AdjustEndPoint(CS_POINT &pnt)
{
    ep = pnt ;
    return 0 ;
}

CS_RECT CS_LINE::BoundingRect()
{
    CS_RECT brect(sp, ep) ;
    return brect ;
}


//////////////////////////////////
//////////////////////////////////
// CS_LineSeg specific methods  //
//////////////////////////////////
//////////////////////////////////
CS_SegPtr CS_LineSeg::Copy()
{
    CS_LineSeg *pls = new CS_LineSeg ; 
    pls->info  = this->info ; 
    pls->uo    = this->uo ; 
    pls->sp    = this->sp ; 
    pls->ep    = this->ep ; 
    pls->pUserData = this->pUserData ; 
    pls->pParent = pParent ; 
    pls->cnt = cnt ; 
    return pls ; 
}


CS_SegPtr CS_LineSeg::Copy(double us, double ue)
{
    CS_LineSeg *pls = new CS_LineSeg ; 
    pls->info  = this->info ; 
    pls->uo    = this->uo ; 
    pls->sp    = this->sp ; 
    pls->ep    = this->ep ; 
    pls->pUserData = this->pUserData ; 
    pls->pParent = pParent ; 
    pls->cnt = cnt ; 
    pls->Trim(us, ue) ; 
    return pls ; 
}

void CS_LineSeg::Print(FILE *fp, int prec)
{
    if (!fp)
        fp = fpDebugOut ;
    char formatstr[256] ; 
    sprintf(formatstr, "LSeg:%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf,%%.%dlf\n",
                    prec, prec, prec, prec, prec, prec) ; 
    fprintf(fp, formatstr,  sp.p[0], sp.p[1], sp.p[2],
	                    ep.p[0], ep.p[1], ep.p[2]) ;
}


void CS_LineSeg::PrintPoints2D(FILE *fp, int prec)
{
    if (!fp)
        fp = fpDebugOut ;

    char formatstr[256] ; 
    sprintf(formatstr, "LSeg (%%.%dlf, %%.%dlf) -> (%%.%dlf, %%.%dlf)\n",
                                prec, prec, prec, prec) ; 
    fprintf(fp, formatstr,  sp.p[0], sp.p[1], ep.p[0], ep.p[1]) ;
}

