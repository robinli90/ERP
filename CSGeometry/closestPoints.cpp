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
// closestPoints.cpp

// See notes RR-Geom Vol 4 Pgs 164-165


// THIS IS ALREADY DONE - IT"S CALLED CS_MinDistance2D()
// MAYBE the method below is simpler. 

#include "math.h"

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_geomalgos.h"


int CS_ClosestPoints2D(CS_LineSeg *psa, CS_LineSeg *psb, double &uanear, double &ubnear)
{
    if (!psa || !psb)
        return 0 ; 

    double ua[2], ub[2] ;
    int nisects = psa->Intersect2D(*psb, ua, ub) ; 
    if (nisects > 0)
    {
        uanear = ua[0] ; 
        ubnear = ub[0] ; 
        return 1 ;
    }

    CS_POINT npa, npb ;
    CS_POINT as, pasosb, ae, paeosb, bs, pbsosa, be, pbeosa ; 
    double ubsona, ubeona, uasonb, uaeonb ;

    as = psa->StartPoint() ; 
    ae = psa->EndPoint() ; 
    bs = psb->StartPoint() ; 
    be = psb->EndPoint() ; 
    
    psa->PointOnSegment2D(bs, &ubsona, &pbsosa) ; 
    psa->PointOnSegment2D(be, &ubeona, &pbeosa) ; 
    psb->PointOnSegment2D(as, &uasonb, &pasosb) ; 
    psb->PointOnSegment2D(ae, &uaeonb, &paeosb) ; 

    double mindist ; 
    double dist = CS_Distance(bs, pbsosa) ; 
    mindist = dist ; 
    uanear = ubsona ; 
    ubnear = 0.0 ; 

    if ((dist = CS_Distance(be, pbeosa)) < mindist)
    {
        mindist = dist ; 
        uanear = ubeona ; 
        ubnear = 1.0 ; 
    }

    if ((dist = CS_Distance(as, pasosb)) < mindist)
    {
        mindist = dist ; 
        uanear = 0.0 ; 
        ubnear = uasonb ; 
    }

    if ((dist = CS_Distance(ae, paeosb)) < mindist)
    {
        mindist = dist ; 
        uanear = 1.0 ; 
        ubnear = uaeonb ; 
    }

    return 2 ; 
}


int CS_ClosestPoints2D(CS_LineSeg *psa, CS_ArcSeg *psb, double &uanear, double &ubnear)
{
    /*
    if (!psa || !psb)
        return 0 ; 

    double ua[2], ub[2] ;
    int nisects = psa->Intersect2D(*psb, ua, ub) ; 
    if (nisects > 0)
    {
        uanear = ua[0] ; 
        ubnear = ub[0] ; 
        return 1 ;
    }

    CS_LINE ln(*psa) ; 
    CS_CIRCLE cir(*psb) ; 

    ln.

    CS_POINT npa, npb ;
    CS_POINT as, pasosb, ae, paeosb, bs, pbsosa, be, pbeosa ; 
    double ubsona, ubeona, uasonb, uaeonb ;

    as = psa->StartPoint() ; 
    ae = psa->EndPoint() ; 
    bs = psb->StartPoint() ; 
    be = psb->EndPoint() ; 
    
    psa->PointOnSegment2D(bs, &ubsona, &pbsosa) ; 
    psa->PointOnSegment2D(be, &ubeona, &pbeosa) ; 
    psb->PointOnSegment2D(as, &uasonb, &pasosb) ; 
    psb->PointOnSegment2D(ae, &uaeonb, &paeosb) ; 

    double mindist ; 
    double dist = CS_Distance(bs, pbsosa) ; 
    mindist = dist ; 
    uanear = ubsona ; 
    ubnear = 0.0 ; 

    if ((dist = CS_Distance(be, pbeosa)) < mindist)
    {
        mindist = dist ; 
        uanear = ubeona ; 
        ubnear = 1.0 ; 
    }

    if ((dist = CS_Distance(as, pasosb)) < mindist)
    {
        mindist = dist ; 
        uanear = 0.0 ; 
        ubnear = uasonb ; 
    }

    if ((dist = CS_Distance(ae, paeosb)) < mindist)
    {
        mindist = dist ; 
        uanear = 1.0 ; 
        ubnear = uaeonb ; 
    }

    return 2 ; 
    */

    return 0 ; 
}


int CS_ClosestPoints2D(CS_SegPtr psa, CS_SegPtr psb, double &ua, double &ub)
{
    int rv ; 
    if (psa->IsLINE())
    {
        if (psb->IsLINE())
            rv = CS_ClosestPoints((CS_LineSeg*)psa, (CS_LineSeg*)psb, ua, ub) ; 
        else if (psb->IsARC())
            rv = CS_ClosestPoints((CS_LineSeg*)psa, (CS_ArcSeg*)psb, ua, ub) ; 
    }
    else if (psa->IsARC())
    {
        if (psb->IsLINE())
            rv = CS_ClosestPoints((CS_LineSeg*)psb, (CS_ArcSeg*)psa, ub, ua) ; 
        else if (psb->IsARC())
            rv = CS_ClosestPoints((CS_ArcSeg*)psa, (CS_ArcSeg*)psb, ua, ub) ; 
    }
    return rv ; 
}


