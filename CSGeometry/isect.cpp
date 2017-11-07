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
// isect.cpp - intersection routines for line and arc segments

#include "math.h"

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)          
#define CS_DEBUGI(a)    
#define CS_DEBUGAL(a)   
#define CS_DEBUG2(a)    
#define CS_DEBUGIS1(a)  
#else
#define CS_DEBUG(a)     
#define CS_DEBUGI(a)    
#define CS_DEBUGAL(a)   
#define CS_DEBUG2(a)    
#define CS_DEBUGIS1(a)  
#endif


/////////////////////////////////////////////////////////////////////////
//////////////////     CS_IREC               ////////////////////////////
/////////////////////////////////////////////////////////////////////////

// defined completely in the header for now

// IRECList support functions
//! returns true if the point is one of the intersection points in the list
int CS_PointInIRECList(CS_POINT &pnt, CS_IRECList &irlist) 
{
    CS_IRECListItr iri ; 
    for (iri = irlist.begin(); iri != irlist.end(); iri++)
    {
        if (iri->Point0() == pnt) 
            return 1 ; 
        if (iri->Status() & CS_IREC::OVERLAP)
        {
            if (iri->Point1() == pnt) 
                return 1 ; 
        }
    }

    return 0 ; 
}

int CS_PointInIRECList(CS_POINT &pnt, CS_IRECList &irlist, double tol) 
{
    CS_IRECListItr iri ; 
    for (iri = irlist.begin(); iri != irlist.end(); iri++)
    {
        if (tcomp_PointsEQ(iri->Point0().p, pnt.p, tol)) 
            return 1 ; 
        if (iri->Status() & CS_IREC::OVERLAP)
        {
            if (tcomp_PointsEQ(iri->Point1().p, pnt.p, tol)) 
                return 1 ; 
        }
    }

    return 0 ; 
}


///////////////////////////////////////////////////////////////////////////////
// CS_LineSeg intersection class routines
///////////////////////////////////////////////////////////////////////////////
int CS_LINE::Collinear(CS_LineSeg &b) 
{
    CS_LINE la(*this) ;
    CS_LINE lb(b) ;
    return la.Collinear(lb) ;
}

int CS_LINE::Collinear2D(CS_LineSeg &b) 
{
    CS_LINE la(*this) ;
    CS_LINE lb(b) ;
    return la.Collinear2D(lb) ;
}


/////////////////////////////////////////////////////////////////////////////
// This returns the parameterized u value along the line defined by the
// line segment. The line segment has a u range of [0,1]
// Thus if the point is on the section before the start point of the 
// line then the u value returned is <0. If the point is on the section
// after the endpoint of the line segment, then u>1
// If the point is on the infinite line true is returned, otherwise false is 
// returned. The uvalue is set to correspond to the point of the line 
// nearest to the point pnt passed in.
// Note the u value returned is oriented in relation to the actual direction
// of the line segment. The actual sp and ep are what the t value is relative
// to.
int CS_LINE::UParmClosestToPoint(CS_POINT p, double *puval, CS_POINT *pnpnt)
{
    CS_LINE ln(*this) ; // generate line
    CS_POINT np = ln.NearestPoint(p) ; 

    // Work out where along the line np is 
    CS_VECTOR v(sp, ep) ; 
    double t ; 
    int retval, collinear ; 

    // First test special case of a zero length line
    if (tcomp_EQZ(v.Mag()))
    {
        if (puval) *puval = 0.0 ;
        if (pnpnt) *pnpnt = sp ; 
        if (sp == p) 
            return 1 ; // point was on the segment (sort of)
        return 0 ; // point was not on the segment
    }

    t = 0.0 ; 
    retval = 0 ; 
    collinear = 0 ; 
    
    if (tcomp_NEQ(v.v[0], 0.0))
    {   // Then use the x component to calculate t
        t = (np.p[0] - sp.p[0]) / v.v[0] ; 
    }
    else if (tcomp_NEQ(v.v[1], 0.0)) 
    {   // Then use the y component to calculate t
        t = (np.p[1] - sp.p[1]) / v.v[1] ; 
    }
    else // z component can't be zero at this point
    {   // Use the z component to calculate t
        t = (np.p[2] - sp.p[2]) / v.v[2] ; 
    }

    // Check if the point is collinear (along the line segment)
    CS_VECTOR vnp ; 
    if (sp == p)
        vnp = p - ep ; 
    else
        vnp = p - sp ; 

    
    // If the cross product is zero then p is collinear with sp,ep line
    CS_DEBUG(fprintf(fpDebugOut, "V=") ; v.Print(fpDebugOut) ; 
             fprintf(fpDebugOut, " vnp=") ; vnp.Print(fpDebugOut) ;
             fprintf(fpDebugOut, "\n") ; )

    CS_VECTOR vcross = v * vnp ; 
    CS_DEBUG(fprintf(fpDebugOut, "  vcross=") ; vcross.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; )


    if (CS_VECTOR(0,0,0) == vcross)
    {   // Then the points are on the same line
        collinear = 1 ; 
        CS_DEBUG(fprintf(fpDebugOut, "POnSeg is collinear\n") ; )
    }

    CS_DEBUG(fprintf(fpDebugOut, "   Nearest point t=%.6lf\n", t); )

    if (puval) *puval = t ; 
    if (pnpnt) *pnpnt = np ; 

    return collinear ; 
}


int CS_LINE::PointOnLine(CS_POINT &p, double *puval, CS_POINT *pnpnt)
{
    int collinear ;
    double t ; 
    CS_POINT np ; 
    collinear = UParmClosestToPoint(p, &t, &np) ;
    
    if (puval) *puval = t ; 
    if (pnpnt) *pnpnt = np ; 

    return collinear ; 
}


// \todo add toldist capabilities to the line testing
int CS_LineSeg::PointOnSegment(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    int retval ; 
    int collinear ;
    double t ; 
    CS_POINT np ; 
    
    retval = 0 ; 
    collinear = UParmClosestToPoint(p, &t, &np) ;

    if (tcomp_GEQ(t, 0.0) && tcomp_LEQ(t, 1.0)) 
    {   // Then the nearest point is on the line segment
        if (puval) *puval = t ; 
        if (pnpnt) *pnpnt = np ; 
        if (collinear)
        {
            CS_DEBUG(fprintf(fpDebugOut, "Point is on the line\n") ;)
            retval = 1 ; 
        }
    }
    else
    {   // The point is not on the line segment
        CS_DEBUG(fprintf(fpDebugOut, "Point is not on the line\n"); )
        if (t < 0)
        {
            if (puval) *puval = 0.0 ; 
            if (pnpnt) *pnpnt = sp ; 
        }
        else
        {   // t > 1 
            if (puval) *puval = 1.0 ; 
            if (pnpnt) *pnpnt = ep ; 
        }
    }

    return retval ; 
}


int CS_LineSeg::PointOnSegment2D(CS_POINT &p, double *puval, CS_POINT *pnpnt, double *toldist)
{
    double sz, ez, pz ; 
    sz = sp.z ; 
    ez = ep.z ; 
    pz = p.z ; 
    sp.z = 0 ; 
    ep.z = 0 ; 
    p.z  = 0 ; 

    int retval ; 
    int collinear ;
    double t ; 
    CS_POINT np ; 
    
    retval = 0 ; 
    collinear = UParmClosestToPoint(p, &t, &np) ;

    if (tcomp_GEQ(t, 0.0) && tcomp_LEQ(t, 1.0)) 
    {   // Then the nearest point is on the line segment
        if (puval) *puval = t ; 
        if (pnpnt) *pnpnt = np ; 
        if (collinear)
        {
            CS_DEBUG(fprintf(fpDebugOut, "Point is on the line\n") ;)
            retval = 1 ; 
        }
    }
    else
    {   // The point is not on the line segment
        CS_DEBUG(fprintf(fpDebugOut, "Point is not on the line\n"); )
        if (t < 0)
        {
            if (puval) *puval = 0.0 ; 
            if (pnpnt) *pnpnt = sp ; 
        }
        else
        {   // t > 1 
            if (puval) *puval = 1.0 ; 
            if (pnpnt) *pnpnt = ep ; 
        }
    }

    sp.z = sz ; 
    ep.z = ez ; 
    p.z  = pz ; 

    return retval ; 
}


int CS_LineSeg::Intersect2D(CS_SegPtr pseg, CS_IRECList *pisset)
{
    if (pseg->SegmentType() == ARC_TYPE)
    {   // Then this is a LINE-ARC intersection
        CS_ArcSeg *pas = (CS_ArcSeg *)pseg ; 

        CS_POINT p1, p2 ; 
        int numisects, isectcnt ;  
        double u ; 

        CS_CIRCLE cir(*pas) ; 
        CS_LINE ln(*this) ;

        numisects = cir.Intersect2D(ln, p1, p2) ;
    
        if (numisects == 0)
        {
            CS_DEBUG(fprintf(fpDebugOut, "No intersects from CS_LINE intersect call\n") ;) 
            return 0 ; // line and arc do not intersect anywhere
        }

        if (numisects == 1)
        {   // Then line is tangent to the arc and there is only 1 intersect
            if (PointOnSegment2D(p1, &u))
            {
                // Next test if it's on the arc segment
                CS_VECTOR vcp(pas->ctr, p1) ;
                double phi = vcp.AngleXY() ; 
                if (pas->AngleOnSweep(phi))
                {
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = pir->cpp[1].u = u ;
                    pir->cps[0].u = pir->cps[1].u = pas->AngleU(phi) ;
                    pir->ipnt[0] = p1 ;
                    pir->statinfo = CS_IREC::POINT | CS_IREC::TANGENT ; 
                
                    CS_AddIRECToIRECList(pisset, pir) ;
                    return 1 ; // found the 1 intersect point so return the u value
                }
            }
            CS_DEBUG(fprintf(fpDebugOut, "No intersects from CS_LINE intersect call\n") ;) 
            return 0 ; // no intersect
        }
    
        // else we have two intersect points to test
        isectcnt = 0 ; 
        if (PointOnSegment2D(p1, &u))
        {   // Then first point is a valid intersection point
            CS_VECTOR vcp(pas->ctr, p1) ;
            double phi = vcp.AngleXY() ; 
            if (pas->AngleOnSweep(phi))
            {
                CS_IREC *pir = new CS_IREC ;
                pir->cpp[0].s = pir->cpp[1].s = this ; 
                pir->cps[0].s = pir->cps[1].s = pseg ; 
                pir->cpp[0].u = pir->cpp[1].u = u ;
                pir->cps[0].u = pir->cps[1].u = pas->AngleU(phi) ;
                pir->ipnt[0] = p1 ;
                pir->statinfo = CS_IREC::POINT ; 
            
                CS_AddIRECToIRECList(pisset, pir) ;
                isectcnt++ ; 
            }
        }

        if (PointOnSegment2D(p2, &u))
        {   // Then first point is a valid intersection point
            CS_VECTOR vcp(pas->ctr, p2) ;
            double phi = vcp.AngleXY() ; 
            if (pas->AngleOnSweep(phi))
            {
                CS_IREC *pir = new CS_IREC ;
                pir->cpp[0].s = pir->cpp[1].s = this ; 
                pir->cps[0].s = pir->cps[1].s = pseg ; 
                pir->cpp[0].u = pir->cpp[1].u = u ;
                pir->cps[0].u = pir->cps[1].u = pas->AngleU(phi) ;
                pir->ipnt[0] = p2 ;
                pir->statinfo = CS_IREC::POINT ; 
            
                CS_AddIRECToIRECList(pisset, pir) ; 
                isectcnt++ ; 
            }
        }

        return isectcnt ; 
        // return pseg->Intersect2D(this, pisset) ; 
    }
    else if (pseg->SegmentType() == CS_Segment::LINE_TYPE)
    {
        CS_LineSeg *pls = (CS_LineSeg *)pseg ; 

        CS_LINE l1(*this) ; 
        CS_LINE l2(*pls) ; 

        int numisects ; 
        CS_POINT p1, p2 ; 

        CS_DEBUG(fprintf(fpDebugOut, "\nEntered LSeg-LSeg Intersect routine\n"); )
        // First test if the lines are collinear
        numisects = l1.Intersect2D(l2, p1) ; 

        if (numisects == 0)
        {   // Lines are parallel but not colinear and thus never intersect
            return 0 ; 
        }
        else if (numisects == 2)
        {   // Collinear line case
            ////////////////////////////////////////////////////////////////
            // See notes  RR-VOL1 pg 20 for diagrams of the various cases
            // as defined for this logic. Further more detailed notes are
            // in RR-VOL2 pgs 46-47
            ////////////////////////////////////////////////////////////////
            // First generate all t values in terms of the base line
            CS_DEBUG(fprintf(fpDebugOut, "Lines overlap in intersect\n") ;)

            CS_VECTOR v(sp, ep) ;
            double ua, ub ; // u coords on the *this line of the end points of the 
            // secondary line. The ua and ub values are used to determine what case
            // exists. 

            double us, ue ; // These are the u coords on the pls secondary line 
            // where the primary line's start and end coordinates occur. 

            CS_VECTOR vab(pls->sp, pls->ep) ; 

            // Use the largest component for scaling for best accuracy
            // Because the lines overlap, they are parallel so the largest 
            // components will be the same for both lines
            if (fabs(v.v[0]) > fabs(v.v[1]))
            {   // ua, ub, us, ue are all u coords along the same *this segment
                ua = (pls->sp.p[0] - sp.p[0]) / v.v[0] ; 
                ub = (pls->ep.p[0] - sp.p[0]) / v.v[0] ; 

                us = (sp.p[0] - pls->sp.p[0]) / vab.v[0] ; 
                ue = (ep.p[0] - pls->sp.p[0]) / vab.v[0] ; 
            }
            else
            {   // ua, ub, us, ue are all u coords along the same *this segment
                ua = (pls->sp.p[1] - sp.p[1]) / v.v[1] ; 
                ub = (pls->ep.p[1] - sp.p[1]) / v.v[1] ; 

                us = (sp.p[1] - pls->sp.p[1]) / vab.v[1] ; 
                ue = (ep.p[1] - pls->sp.p[1]) / vab.v[1] ; 
            }

            if (CS_DotProduct(v, vab) > 0.0)
            {   // Then lines go in same direction
                if (ua < 0.0)
                {
                    if (ub < 0.0) return 0 ; // case 1

                    if (tcomp_EQZ(ub)) 
                    {   // Case 2
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = pir->cpp[1].u = 0.0 ;
                        pir->cps[0].u = pir->cps[1].u = 1.0 ;
                        pir->ipnt[0] = StartPoint() ;
                        pir->statinfo = CS_IREC::POINT | CS_IREC::TANGENT ; 
            
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    if (ub < 1.0)
                    {   // Case 3
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = 0.0 ; 
                        pir->cpp[1].u = ub ;
                        pir->cps[0].u = us ; 
                        pir->cps[1].u = 1.0 ;
                        pir->ipnt[0] = StartPoint() ;
                        pir->ipnt[1] = UPoint(ub) ;
                        pir->statinfo = CS_IREC::OVERLAP ; 
            
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    // Case 4,5
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = 1.0 ;
                    pir->cps[0].u = us ; 
                    if (tcomp_EQ(ue,1.0))
                        pir->cps[1].u = 1.0 ; 
                    else
                        pir->cps[1].u = ue ; 

                    pir->ipnt[0] = StartPoint() ;
                    pir->ipnt[1] = EndPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP ; 
        
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_EQZ(ua))
                {   
                    if (ub < 1.0)
                    {   // Case 6
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = 0.0 ; 
                        pir->cpp[1].u = ub ;
                        pir->cps[0].u = 0.0 ; 
                        pir->cps[1].u = 1.0 ;
                        pir->ipnt[0] = StartPoint() ;
                        pir->ipnt[1] = pseg->EndPoint() ;
                        pir->statinfo = CS_IREC::OVERLAP ; 
            
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    // Case 7, 8
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = 1.0 ;
                    pir->cps[0].u = 0.0 ; 
                    if (tcomp_EQ(ue,1.0))
                        pir->cps[1].u = 1.0 ; // force to exactly 1.0 (case 7)
                    else
                        pir->cps[1].u = ue ;  // case 8
                    pir->ipnt[0] = StartPoint() ;
                    pir->ipnt[1] = EndPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP ; 
        
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_LT(ua,1.0))
                {
                    if (tcomp_LT(ub,1.0))
                    {   // Case 9
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = ua ; 
                        pir->cpp[1].u = ub ;
                        pir->cps[0].u = 0.0 ; 
                        pir->cps[1].u = 1.0 ;
                        pir->ipnt[0] = pseg->StartPoint() ;
                        pir->ipnt[1] = pseg->EndPoint() ;
                        pir->statinfo = CS_IREC::OVERLAP ; 
            
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ;
                    }
                    // Case 10, 11
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = ua ; 
                    pir->cpp[1].u = 1.0 ;
                    pir->cps[0].u = 0.0 ; 
                    if (tcomp_EQ(ue,1.0))
                        pir->cps[1].u = 1.0 ; // case 10
                    else
                        pir->cps[1].u = ue ;  // case 11
                    pir->ipnt[0] = pseg->StartPoint() ;
                    pir->ipnt[1] = EndPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP ; 
        
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_EQ(ua, 1.0))
                {   // Case 12
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 1.0 ; 
                    pir->cpp[1].u = 1.0 ;
                    pir->cps[0].u = 0.0 ; 
                    pir->cps[1].u = 0.0 ;
                    pir->ipnt[0] = EndPoint() ;
                    pir->statinfo = CS_IREC::POINT | CS_IREC::TANGENT ; 
        
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
            }
            else
            {   // Reverse lines situation
                if (ua > 1.0)
                {
                    if (ub > 1.0) return 0 ; // case 14

                    if (tcomp_EQ(ub, 1.0)) 
                    {   // Case 15 - single point
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = 1.0 ; 
                        pir->cpp[1].u = 1.0 ;
                        pir->cps[0].u = 1.0 ; 
                        pir->cps[1].u = 1.0 ;
                        pir->ipnt[0] = EndPoint() ;
                        pir->statinfo = CS_IREC::POINT | CS_IREC::TANGENT ; 
        
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    if (tcomp_GT(ub, 0.0))
                    {   // Case 16
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = ub ; 
                        pir->cpp[1].u = 1.0 ;
                        pir->cps[0].u = 1.0 ; 
                        pir->cps[1].u = ue ;
                        pir->ipnt[0] = pseg->EndPoint() ;
                        pir->ipnt[1] = EndPoint() ;
                        pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
        
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    // Case 17,18
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = 1.0 ;
                    if (tcomp_EQ(us, 1.0))
                        pir->cps[0].u = 1.0 ; 
                    else
                        pir->cps[0].u = us ; 
                    pir->cps[1].u = ue ;
                    pir->ipnt[0] = StartPoint() ;
                    pir->ipnt[1] = EndPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
    
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_EQ(ua, 1.0))
                {   
                    if (ub > 0.0)
                    {   // Case 19
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = ub ; 
                        pir->cpp[1].u = 1.0 ;
                        pir->cps[0].u = 1.0 ; 
                        pir->cps[1].u = 0.0 ;
                        pir->ipnt[0] = pseg->EndPoint() ;
                        pir->ipnt[1] = EndPoint() ;
                        pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
        
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ; 
                    }
                    // Case 20, 21 
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = 1.0 ;
                    if (tcomp_EQ(us, 1.0))
                        pir->cps[0].u = 1.0 ; // force to exactly 1.0 (case 20) 
                    else
                        pir->cps[0].u = us ; // case 21
                    pir->cps[1].u = 0.0 ;
                    pir->ipnt[0] = StartPoint() ;
                    pir->ipnt[1] = EndPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
    
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_GT(ua,0.0))
                {   // cases 22,23,24
                    if (ub > 0.0)
                    {   // Case 22
                        CS_IREC *pir = new CS_IREC ;
                        pir->cpp[0].s = pir->cpp[1].s = this ; 
                        pir->cps[0].s = pir->cps[1].s = pseg ; 
                        pir->cpp[0].u = ub ; 
                        pir->cpp[1].u = ua ;
                        pir->cps[0].u = 1.0 ; 
                        pir->cps[1].u = 0.0 ;
                        pir->ipnt[0] = pseg->EndPoint() ;
                        pir->ipnt[1] = pseg->StartPoint() ;
                        pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
        
                        CS_AddIRECToIRECList(pisset, pir) ; 
                        return 1 ;
                    }
                    // Case 23, 24
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = ua ;
                    if (tcomp_EQ(us, 1.0))
                        pir->cps[0].u = 1.0 ; // case 23
                    else
                        pir->cps[0].u = us ; // case 24
                    pir->cps[1].u = 0.0 ;
                    pir->ipnt[0] = StartPoint() ;
                    pir->ipnt[1] = pseg->StartPoint() ;
                    pir->statinfo = CS_IREC::OVERLAP | CS_IREC::BREVERSED ; 
    
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
                else if (tcomp_EQZ(ua))
                {   // Case 25
                    CS_IREC *pir = new CS_IREC ;
                    pir->cpp[0].s = pir->cpp[1].s = this ; 
                    pir->cps[0].s = pir->cps[1].s = pseg ; 
                    pir->cpp[0].u = 0.0 ; 
                    pir->cpp[1].u = 0.0 ;
                    pir->cps[0].u = 0.0 ; 
                    pir->cps[1].u = 0.0 ;
                    pir->ipnt[0] = StartPoint() ;
                    pir->statinfo = CS_IREC::POINT | CS_IREC::BREVERSED | CS_IREC::TANGENT ; 
    
                    CS_AddIRECToIRECList(pisset, pir) ; 
                    return 1 ; 
                }
            }
           
            // cases 13 and 26
            return 0 ; // no intersection overlap
        }

        // Otherwise the lines intersect at a point
        CS_DEBUG
        (
            fprintf(fpDebugOut, "Testing point ") ;
            p1.Print(fpDebugOut) ; 
            fprintf(fpDebugOut, " with PointOnSegment2D()\n") ; 
        )

        double u1, u2 ; 
        if (PointOnSegment2D(p1, &u1) && pls->PointOnSegment2D(p1, &u2))
        {
            CS_DEBUG(fprintf(fpDebugOut, "Point is on segment\n") ;)

            // Standard line cross intersection
            CS_IREC *pir = new CS_IREC ;
            pir->cpp[0].s = pir->cpp[1].s = this ; 
            pir->cps[0].s = pir->cps[1].s = pseg ; 
            pir->cpp[0].u = u1 ; 
            pir->cpp[1].u = u1 ;
            pir->cps[0].u = u2 ; 
            pir->cps[1].u = u2 ;
            pir->ipnt[0] = p1 ; 
            pir->statinfo = CS_IREC::POINT ; 

            CS_AddIRECToIRECList(pisset, pir) ; 
            return 1 ; 
        }

        CS_DEBUG(fprintf(fpDebugOut, "Point not on segment\n") ;)
        return 0 ; 
    }
    // else  Unhandled type
    return 0 ; 
}


int CS_LineSeg::Intersect2D(CS_ArcSeg &cas, double *uva, double *uvb)
{
    CS_POINT p1, p2 ; 
    int numisects, isectcnt ;  
    double u ; 

    CS_CIRCLE cir(cas) ; 
    CS_LINE ln(*this) ;

    numisects = cir.Intersect2D(ln, p1, p2) ;
    
    if (numisects == 0)
    {
        CS_DEBUG(fprintf(fpDebugOut, "No intersects from CS_LINE intersect call\n") ;) 
        return 0 ; // line and arc do not intersect anywhere
    }

    if (numisects == 1)
    {   // Then line is tangent to the arc and there is only 1 intersect
        if (PointOnSegment2D(p1, &u))
        {
            // Next test if it's on the arc segment
            CS_VECTOR vcp(cas.ctr, p1) ;
            double phi = vcp.AngleXY() ; 
            if (cas.AngleOnSweep(phi))
            {
                uva[0] = u ; 
                uvb[0] = cas.AngleU(phi) ; 
                return 1 ; // found the 1 intersect point so return the u value
            }
        }
        CS_DEBUG(fprintf(fpDebugOut, "No intersects from CS_LINE intersect call\n") ;) 
        return 0 ; // no intersect
    }
    
    // else we have two intersect points to test
    isectcnt = 0 ; 
    if (PointOnSegment2D(p1, &u))
    {   // Then first point is a valid intersection point
        CS_VECTOR vcp(cas.ctr, p1) ;
        double phi = vcp.AngleXY() ; 
        if (cas.AngleOnSweep(phi))
        {
            uva[isectcnt] = u ;
            uvb[isectcnt] = cas.AngleU(phi) ; 
            isectcnt++ ; 
        }
    }

    if (PointOnSegment2D(p2, &u))
    {   // Then first point is a valid intersection point
        CS_VECTOR vcp(cas.ctr, p2) ;
        double phi = vcp.AngleXY() ; 
        if (cas.AngleOnSweep(phi))
        {
            uva[isectcnt] = u ;
            uvb[isectcnt] = cas.AngleU(phi) ; 
            isectcnt++ ; 
        }
    }

    return isectcnt ; 
}


/////////////////////////////////////////////////////////////////
// Line-Line intersection
// See notes Oct 5, 1998, pp 20-21 RR-Vol1 about overlapping 
// This was corrected Sept 2, 2000. pp 46-49 RR-Vol2
// colinear line intersections
int CS_LineSeg::Intersect2D(CS_LineSeg &cls, double *uva, double *uvb)
{
    CS_LINE l1(*this) ; 
    CS_LINE l2(cls) ; 

    int numisects ; 
    CS_POINT p1, p2 ; 

    CS_DEBUG(fprintf(fpDebugOut, "\nEntered LSeg-LSeg Intersect routine\n"); )
    // First test if the lines are collinear
    numisects = l1.Intersect2D(l2, p1) ; 

    if (numisects == 0)
    {   // Lines are parallel but not colinear and thus never intersect
        return 0 ; 
    }
    else if (numisects == 2)
    {   // Collinear line case
        // First generate all t values in terms of the base line
        CS_DEBUG(fprintf(fpDebugOut, "Lines overlap in intersect\n") ;)
        
        CS_VECTOR v(sp, ep) ;
        double ua, ub ; // uvalues for line cls in terms of the parametric 
        // equation of the base line (*this)
        double us, ue ; // u values for the cls line
        CS_VECTOR vab(cls.sp, cls.ep) ; 

        if (!tcomp_EQZ(v.v[0]))
        {
            ua = (cls.sp.p[0] - sp.p[0]) / v.v[0] ; 
            ub = (cls.ep.p[0] - sp.p[0]) / v.v[0] ; 
            us = (sp.p[0] - cls.sp.p[0]) / vab.v[0] ; 
            ue = (ep.p[0] - cls.sp.p[0]) / vab.v[0] ; 
        }
        else
        {
            ua = (cls.sp.p[1] - sp.p[1]) / v.v[1] ; 
            ub = (cls.ep.p[1] - sp.p[1]) / v.v[1] ; 
            us = (sp.p[1] - cls.sp.p[1]) / vab.v[1] ; 
            ue = (ep.p[1] - cls.sp.p[1]) / vab.v[1] ; 
        }

        if (CS_DotProduct(v, vab) > 0.0)
        {   // Then lines go in same direction
            if (ua < 0.0)
            {
                if (ub < 0.0) return 0 ; // case 1

                if (tcomp_EQZ(ub)) 
                {   // Case 2
                    uva[0] = 0.0 ; 
                    uvb[0] = 1.0 ; 
                    return 1 ; 
                }
                if (ub < 1.0)
                {   // Case 3
                    uva[0] = 0.0 ; 
                    uva[1] = ub ; 
                    uvb[0] = us ; 
                    uvb[1] = 1.0 ; 
                    return 2 ; 
                }
                // Case 4,5
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ; 
                uvb[0] = us ; 
                if (tcomp_EQ(ue,1.0))
                    uvb[1] = 1.0 ; // case 4
                else
                    uvb[1] = ue ;  // case 5
                return 2 ; 
            }
            else if (tcomp_EQZ(ua))
            {   
                if (ub < 1.0)
                {   // Case 6
                    uva[0] = 0.0 ; 
                    uva[1] = ub ; 
                    uvb[0] = 0.0 ; 
                    uvb[1] = 1.0 ; 
                    return 2 ; 
                }
                // Case 7, 8
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ; 
                uvb[0] = 0.0 ; 
                if (tcomp_EQ(ue, 1.0))
                    uvb[1] = 1.0 ; // force to exactly 1.0 (case 7)
                else
                    uvb[1] = ue ; // case 8
                return 2 ; 
            }
            else if (tcomp_LT(ua,1.0))
            {
                if (tcomp_LT(ub,1.0))
                {   // Case 9
                    uva[0] = ua ; 
                    uva[1] = ub ; 
                    uvb[0] = 0.0 ; 
                    uvb[1] = 1.0 ; 
                    return 2 ;
                }
                // Case 10, 11
                uva[0] = ua ; 
                uva[1] = 1.0 ; 
                uvb[0] = 0.0 ; 
                if (tcomp_EQ(ue, 1.0))
                    uvb[1] = 1.0 ; // case 10
                else
                    uvb[1] = ue ;  // case 11
                return 2 ; 
            }
            else if (tcomp_EQ(ua, 1.0))
            {   // Case 12
                uva[0] = 1.0 ; 
                uvb[0] = 0.0 ; 
                return 1 ; 
            }
        }
        else
        {   // Reverse lines situation
            if (ua > 1.0)
            {
                if (ub > 1.0) return 0 ; // case 14

                if (tcomp_EQ(ub, 1.0)) 
                {   // Case 15
                    uva[0] = 1.0 ; 
                    uvb[0] = 1.0 ; 
                    return 1 ; 
                }
                if (tcomp_GT(ub, 0.0))
                {   // Case 16
                    uva[0] = ub ; 
                    uva[1] = 1.0 ; 
                    uvb[0] = 1.0 ; 
                    uvb[1] = ue ; 
                    return 2 ; 
                }
                // Case 17,18
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ; 
                if (tcomp_EQ(us, 1.0))
                    uvb[0] = 1.0 ; // case 17
                else
                    uvb[0] = us ;  // case 18
                uvb[1] = ue ; 
                return 2 ; 
            }
            else if (tcomp_EQ(ua, 1.0))
            {   
                if (ub > 0.0)
                {   // Case 19
                    uva[0] = ub ; 
                    uva[1] = 1.0 ; 
                    uvb[0] = 1.0 ; 
                    uvb[1] = 0.0 ; 
                    return 2 ; 
                }
                // Case 20, 21 
                uva[0] = 0.0 ; 
                uva[1] = 1.0 ; 
                if (tcomp_EQ(us, 1.0))
                    uvb[0] = 1.0 ; // force to exactly 1.0 (case 20)
                else
                    uvb[0] = us ; // case 21
                uvb[1] = 0.0 ; 
                return 2 ; 
            }
            else if (tcomp_GT(ua,0.0))
            {   // cases 22,23,24
                if (ub > 0.0)
                {   // Case 22
                    uva[0] = ub ; 
                    uva[1] = ua ; 
                    uvb[0] = 1.0 ; 
                    uvb[1] = 0.0 ; 
                    return 2 ;
                }
                // Case 23, 24
                uva[0] = 0.0 ; 
                uva[1] = ua ; 
                if (tcomp_EQ(us, 1.0))
                    uvb[0] = 1.0 ; // case 10
                else
                    uvb[0] = us ;  // case 11
                uvb[1] = 0.0 ; 
                return 2 ; 
            }
            else if (tcomp_EQZ(ua))
            {   // Case 12
                uva[0] = 0.0 ; 
                uvb[0] = 0.0 ; 
                return 1 ; 
            }
        }
           
        // cases 13 and 26
        return 0 ; // no intersection overlap
    }

    // Otherwise the lines intersect at a point
    CS_DEBUG
    (
        fprintf(fpDebugOut, "Testing point ") ;
        p1.Print(fpDebugOut) ; 
        fprintf(fpDebugOut, " with PointOnSegment2D()\n") ; 
    )

    double u1, u2 ; 
    if (PointOnSegment2D(p1, &u1) && cls.PointOnSegment2D(p1, &u2))
    {
        CS_DEBUG(fprintf(fpDebugOut, "Point is on segment\n") ;)
        uva[0] = u1 ; 
        uvb[0] = u2 ; 
        return 1 ; 
    }

    CS_DEBUG(fprintf(fpDebugOut, "Point not on segment\n") ;)
    return 0 ; 
}



////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////
// CS_Curve intersect routines
//
//  The three CS_Curve intersect routines return 0 if there are no errors
//  and an error code if something goes wrong. The number of intersects
//  found is defined within the CS_ISectSet variables
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// The intersection record U values generated are relative to the 
// individual segments, and intersection records are merged together as 
// required during processing if requested. 
// The return value is the number of new intersection records added 
// to the intersection set that is passed in. 
// If bNoISSmerge is false (the default) then the intsection records
// are connected together. Note for this to work properly, any existing
// entries in the intersection set, must occur before the new values
// generated along the curve, and they must be in ascending u order
// relative to the overall CS_Curve. The intersection merging also assumes
// that any intersections generated will be unique. Thus no overlapping 
// input segments will be sent to the Intersect2D() func as input.
// Keep in miind that by doing the merge, segment pointers to the 
// B segments will be lost for internal overlap sections. These 
// segments will completely overlap the base (*this) curve and thus 
// can in theory be picked up from each end, but if the internal 
// B overlap segments need to be kept, then set bNoISSmerge to true. 
/*
    CS_SegPtr pseg ; 
    CS_ListNode *pln = pisset->Last() ; 
    CS_IntersectRec *pira, *pirb ; 

    // Clean up the intersection records so they are relative to the overall 
    // CS_Curve (*this)
    if (pln == 0)
        pln = pisset->First() ; 

    while (pln)
    {
        if (pln->next)
        {   // See if these two can be connected
            // First convert the u values to the overall curve.
            pira = pisset->GetData(pln) ; 
            pirb = pisset->GetData(pln->next) ; 

            if ((pira->statinfo & CS_IREC::OVERLAP) && 
                (pira->statinfo & CS_IREC::OVERLAP) &&
                (tcomp_EQ(pira->uaend, 1.0) && tcomp_EQZ(pirb->uastart)) )
            {   // Then we merge these two records into one
                pira->uaend = pirb->uaend ; 
                pira->psegAend = pirb->psegAstart ; 
                pira->psegBend = pirb->psegBstart ; 
                pira->ipnt2 = pirb->ipnt2 ; 
            }
        }
        pln = pln->next ; 
    }

    return isectcount ; 

*/


// Do a simple segment to segment intersection and return the number of
// intersections found.
int CS_Curve::Intersect2D(CS_SegPtr pseg, CS_IRECList *pisset) 
{
    int isectcount = 0 ; 
    CS_SegPtr psn = pStart ; 
    while (psn)
    {
        isectcount += psn->Intersect2D(pseg, pisset) ;
        psn = psn->next ; 
    }

    return isectcount ; 

}



// TO DO - need to optimize this for long curve by doing an initial pre sort.
// Intersect all segments against one another
int CS_Curve::Intersect2D(CS_Curve *pcrv, CS_IRECList *pisset) 
{
    int i, j ; 
    CS_SegPtr psn ; 

    CS_RECT *pbbthis = new CS_RECT[this->nodecnt+1] ; 
    CS_RECT *pbbcrv =  new CS_RECT[pcrv->nodecnt+1] ; 

    // Apply the tolerance expansion here, so that the overlap tests
    // don't have to do multiple tolerance compares. BoundingRect()
    // overlap compares do not use tolerance.

    i = 0 ; 
    psn = pStart ; 
    while (psn)
    {
        pbbthis[i] = psn->BoundingRect() ; 
        pbbthis[i].Grow(0.0005) ; 
        i++ ; 
        psn = psn->next ; 
    }

    i = 0 ; 
    psn = pcrv->pStart ; 
    while (psn)
    {
        pbbcrv[i] = psn->BoundingRect() ; 
        pbbcrv[i].Expand(0.0005) ; 
        i++ ; 
        psn = psn->next ; 
    }

    // Now intersect all the curves against one another. This is complicated by 
    // the situation where we have overlapping curves. When this occurs we must
    // remember where the overlap starts and then create one continuous 
    // section until the overlap ends. This the intersection records generated
    // along the way have to be merged together. In this situation we'll usually
    // be changing the last IntersectRec data values. Also while processing, 
    // have to make sure that the segment node U values are correct. 
    psn = pStart ; 
    i = 0 ; 
    while (psn)
    {   // Set all bounding boxes for both curves
        CS_SegPtr psnb = pcrv->pStart ; 
        j = 0 ; 
        while (psnb)
        {
            if (pbbthis[i].Overlaps(pbbcrv[j]))
            {
                psn->Intersect2D(psnb, pisset) ; 
            }
            psnb = psnb->next ; 
            j++ ; 
        }
        psn = psn->next ; 
        i++ ; 
    }

    delete[] pbbcrv ; 
    delete[] pbbthis ; 

    return 0 ; 
}

