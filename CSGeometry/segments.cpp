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

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_curves.h"




CS_Segment::CS_Segment()
{
     uo = 0.0 ; 
     info = 0 ;
     pUserData = 0 ; 
     pParent = 0 ; 
     prev = 0 ; 
     next = 0 ; 
}

CS_Segment::CS_Segment(CS_SegPtr pseg)
{
     info       = pseg->info ;
     pUserData  = pseg->pUserData ; 
     uo         = pseg->uo ; 
     pParent    = pseg->pParent ; 
     cnt        = pseg->cnt ; 
     
     // These must be initialized externally
     prev       = 0 ; 
     next       = 0 ; 
}

CS_Segment::~CS_Segment()
{
}

///////////////////////////////////////////////////////////////
//  NULL_TYPE	0
//  POINT_TYPE	1
//  LINE_TYPE	2
//  ARC_TYPE	3
//  SPLINE_TYPE 4
//  CURVE_TYPE	5   // multiple points, lines, arcs, splines
// Note: only LINE_TYPE and ARC_TYPE are ever used. This is
//   not likely to change in the near future
///////////////////////////////////////////////////////////////
int CS_Segment::SegmentType()
{
    return -1 ; // INVALID TYPE
}

void CS_Segment::Print(FILE *fp, int prec)
{
}

void CS_Segment::PrintPoints2D(FILE *fp, int prec)
{
}


void CS_Segment::Reverse()
{
}

CS_SegPtr CS_Segment::Copy()
{
    return 0 ; 
}


CS_SegPtr CS_Segment::Copy(double us, double ue)
{
    return 0 ; 
}


CS_POINT CS_Segment::UPoint(double u)
{
    CS_POINT upnt ;
    return upnt ;
}

void CS_Segment::SetZ(double z)
{
}

void CS_Segment::Move(CS_VECTOR &v)
{
}

void CS_Segment::MTX3Mult(CS_MTX3 &m)
{
}

void CS_Segment::Scale(double s)
{
}

void CS_Segment::Transform(double p[12])
{
}

int CS_Segment::Similar(CS_SegPtr psb)
{
    return 0 ; 
}


CS_POINT CS_Segment::MidPoint()
{
    CS_POINT mpnt ;
    return mpnt ;
}

CS_POINT CS_Segment::StartPoint()
{
    CS_POINT pnt ;
    return pnt ;
}

CS_POINT CS_Segment::EndPoint()
{
    CS_POINT pnt ;
    return pnt ;
}


double CS_Segment::ArcLength(void)
{
    return 0.0 ;
}

CS_POINT  CS_Segment::Centroid(void)
{
    return CS_POINT(0,0,0) ;
}

CS_POINT CS_Segment::Centroid2D(void)
{
    return CS_POINT(0,0,0) ;
}


double CS_Segment::XY_ArcLength(void)
{
    return 0.0 ;
}


CS_VECTOR CS_Segment::UTangent(double u)
{
    CS_VECTOR vtan ;
    return vtan ;
}

int CS_Segment::Offset(double delta)
{
    return 0 ; 
}

/*
int CS_Segment::Intersect2D(CS_SegPtr pseg, CS_IntersectList *pisset)
{
    return 0 ; 
}
*/

int CS_Segment::PointSide(CS_POINT &pnt)
{
    return 0 ; 
}


int CS_Segment::PointOnSegment(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    return 0 ;
}

int CS_Segment::PointOnSegment2D(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    return 0 ;
}

int CS_Segment::AdjustStartPoint(CS_POINT &pnt)
{
    return 1 ; // failed since not overidden
}

int CS_Segment::AdjustEndPoint(CS_POINT &pnt)
{
    return 1 ; // failed since not overidden
}

CS_RECT CS_Segment::BoundingRect()
{
    return CS_RECT(0,0,0,0) ;
}

