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
// stretch.cpp


#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_shapes.h"
#include "cs_cadfuncs.h"


// Stretches a section of a curve by offsetting one segment, calculating 
// adjoining intersections and then reconnecting everything for the final
// output curve.
//
// See notes: CAD Applications I pgs. 57-61
//

#ifndef min
#define min(a,b)        ((a < b) ? (a) : (b) ) 
#endif

#ifndef max
#define max(a,b)        ((a > b) ? (a) : (b) ) 
#endif


int CS_Stretch3(CS_Curve &sc, CS_POINT &frmpnt, CS_POINT &topnt, 
                double stepSize, int stepMode,
                CS_Curve*& prescrv, CS_Curve** pstretchSection)
{
    CS_SegPtr pAB = 0 ; 
    CS_POINT pntnear ; 
    CS_VECTOR ofsvect(frmpnt, topnt) ; 
    double unear, ubseg ; 

    sc.PointOnCurve(frmpnt, &unear, &pntnear, &pAB, &ubseg) ; 
    if (!pAB)
    {   // Didn't find a nearest segment, sc is probably undefined
        return -1 ; 
    }

    int side = pAB->PointSide(topnt) ; 
    CS_VECTOR vtan = pAB->UTangent(ubseg) ; 

    double ofsdist ; 

    // Set the offset distance appropriately
    if (pAB->SegmentType() == CS_Segment::LINE_TYPE)
    {
        if (side == CS_LEFTSIDE)
        {
            CS_VECTOR vperp = vtan.LeftPerp() ; 
            ofsdist = -fabs(CS_DotProduct(ofsvect, vperp)) ; 
        }
        else
        {
            CS_VECTOR vperp = vtan.RightPerp() ; 
            ofsdist = fabs(CS_DotProduct(ofsvect, vperp)) ; 
        }
    }
    else
    {
        CS_ArcSeg *pas = (CS_ArcSeg *)pAB ; 
        CS_VECTOR vcp(pas->ctr, topnt) ; 
        ofsdist = fabs(pas->rad - vcp.Mag()) ; 
        if (side == CS_LEFTSIDE)
            ofsdist = -ofsdist ; 
    }

    if (stepSize != 0.0)
    {   // Adjust the ofsDist parameter
        double signm ; 
        if (ofsdist < 0.0)
            signm = -1.0 ; 
        else 
            signm = 1.0 ; 
        if (stepMode == 1)
        {
            ofsdist = signm * stepSize ; 
        }
        else
        {
            ofsdist = fabs(ofsdist) ; 
            int nstep = (int)(ofsdist / stepSize) ; 
            double newofs = stepSize * nstep ; 
            if ((ofsdist - newofs) > (stepSize / 2.0))
                nstep += 1 ; 
            ofsdist = stepSize * nstep * signm ; 
        }
    }


    // Now offset the base segment. See CAD Apps I pg.62
    // (ignore page 61 as the logic on page 61 has been abandoned)
    CS_SegPtr pCA = sc.Prev(pAB) ;
    CS_SegPtr pBD = sc.Next(pAB) ;

    // If the rads are not zero at the end then filleting is performed
    // to re-insert the arc that was defined there
    double CArad = 0.0 ; 
    double BDrad = 0.0 ; 

    // The pEAcrv and the pBFcrv and added to either side of the modified
    // base curve section as the last stage in processing
    CS_Curve *pEAcrv = new CS_Curve ;
    CS_Curve *pBFcrv = new CS_Curve ;

    // The end point of pEAcrv and the startpoint of pBFcrv define the 
    // new endpoints of the base curve section that is moved at the end
    int nECA, nBDF ;

    // First work out how to handle the Ao end of the line (start point)
    if ((pCA->SegmentType() == CS_Segment::LINE_TYPE) &&
        (pAB->SegmentType() == CS_Segment::LINE_TYPE))
    {   // Then we are simply intersecting two lines
        nECA = 1 ; // we're modifying one segment in the ECA curve section
        CS_LineSeg *pa = (CS_LineSeg *)pCA->Copy() ;
        CS_LineSeg *pm = (CS_LineSeg *)pAB->Copy() ;
        pm->Offset(ofsdist) ;
        
        // Need to work out the pick points that get passed to the 
        // extend-trim command
        CS_LINE la(*(CS_LineSeg*)pa) ; 
        CS_LINE lm(*(CS_LineSeg*)pm) ; 

        CS_POINT ipnt ; 
        int nisects = la.Intersect2D(lm, ipnt) ;
        // Note, the two lines must intersect since they intersected before

        double ua, um ; 
        pa->PointOnSegment(ipnt, &ua) ;
        pm->PointOnSegment(ipnt, &um) ;

        ua = ua - 0.1 * ua ;
        um = um + 0.1 * (1.0 - um) ; 

        CS_ExTrimEndpoints(pa, pa->UPoint(ua), pm, pm->UPoint(um)) ;
        pEAcrv->Append(pa) ;
        delete pm ; 
    }
    else if ((pCA->SegmentType() == CS_Segment::ARC_TYPE) &&
             (pAB->SegmentType() == CS_Segment::LINE_TYPE))
    {   // Connected to an arc segment
        nECA = 2 ; // we're modifying two segments in the ECA curve section
        CS_ArcSeg *pas = (CS_ArcSeg*)pCA ; 
        CArad = pas->rad ; 

        CS_SegPtr pEC = sc.Prev(pCA) ;
        CS_SegPtr pa = pEC->Copy() ;
        CS_SegPtr pm = pAB->Copy() ;
        pm->Offset(ofsdist) ;

        int nisects ;
        CS_POINT ipnt1, ipnt2 ;

        if (pa->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_LINE la(*(CS_LineSeg*)pa) ;
            CS_LINE lb(*(CS_LineSeg*)pm) ;
            nisects = la.Intersect2D(lb, ipnt1) ;
        }
        else
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pa) ;
            CS_LINE lb(*(CS_LineSeg*)pm) ;
            nisects = ca.Intersect2D(lb, ipnt1, ipnt2) ;
        }

        int dofailsafe = 0 ; 
        if (nisects == 0)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ua, um ; 
            pa->PointOnSegment(ipnt1, &ua) ;
            pm->PointOnSegment(ipnt1, &um) ;
            ua = ua - 0.1 * ua ;
            um = um + 0.1 * (1.0 - um) ; 
            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua), pm, pm->UPoint(um)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Tangent intersection
            double ua1, ua2, um1, um2 ; 
            pa->PointOnSegment(ipnt1, &ua1) ;
            pm->PointOnSegment(ipnt1, &um1) ;
            pa->PointOnSegment(ipnt2, &ua2) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            
            ua1 = max(ua1, ua2) ; 
            um1 = min(um1, um2) ; 
            ua1 = ua1 - 0.1 * ua1 ;
            um1 = um1 + 0.1 * (1.0 - um1) ; 

            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua1), pm, pm->UPoint(um1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pa ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pa = new CS_LineSeg ; 
            pa->sp = pEC->StartPoint() ; 
            pa->ep = pm->StartPoint() ; 
        
            pEAcrv->Append(pa) ; 
            delete pm ; 
        }
    }
    else if ((pCA->SegmentType() == CS_Segment::LINE_TYPE) &&
             (pAB->SegmentType() == CS_Segment::ARC_TYPE))
    {   // Connected to an arc segment
        nECA = 1 ; // we're modifying two segments in the ECA curve section
        CS_SegPtr pa = pCA->Copy() ;
        CS_SegPtr pm = pAB->Copy() ;
        pm->Offset(ofsdist) ;

        int nisects ;
        CS_LINE la(*(CS_LineSeg*)pa) ;
        CS_CIRCLE cb(*(CS_ArcSeg*)pm) ;
        CS_POINT ipnt1, ipnt2 ;

        int dofailsafe = 0 ; 
        nisects = la.Intersect2D(cb, ipnt1, ipnt2) ;

        if (nisects == 0)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ua, um ; 
            pa->PointOnSegment(ipnt1, &ua) ;
            pm->PointOnSegment(ipnt1, &um) ;
            ua = ua - 0.1 * ua ;
            um = um + 0.1 * (1.0 - um) ; 
            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua), pm, pm->UPoint(um)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Tangent intersection
            double ua1, ua2, um1, um2 ; 
            pa->PointOnSegment(ipnt1, &ua1) ;
            pm->PointOnSegment(ipnt1, &um1) ;
            pa->PointOnSegment(ipnt2, &ua2) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            
            ua1 = max(ua1, ua2) ; 
            um1 = min(um1, um2) ; 
            ua1 = ua1 - 0.1 * ua1 ;
            um1 = um1 + 0.1 * (1.0 - um1) ; 

            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua1), pm, pm->UPoint(um1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pa ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pa = new CS_LineSeg ; 
            pa->sp = pCA->StartPoint() ; 
            pa->ep = pm->StartPoint() ; 
        
            pEAcrv->Append(pa) ; 
            delete pm ; 
        }
    }
    else if ((pCA->SegmentType() == CS_Segment::ARC_TYPE) &&
             (pAB->SegmentType() == CS_Segment::ARC_TYPE))
    {   // Connected to an arc segment
        nECA = 2 ; // we're modifying two segments in the ECA curve section
        CS_ArcSeg *pas = (CS_ArcSeg*)pCA ; 
        CArad = pas->rad ; 

        CS_SegPtr pEC = sc.Prev(pCA) ;
        CS_SegPtr pa = pEC->Copy() ;
        CS_SegPtr pm = pAB->Copy() ;
        pm->Offset(ofsdist) ;

        CS_POINT ipnt1, ipnt2 ;
        int nisects ;

        if (pa->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_LINE la(*(CS_LineSeg*)pa) ;
            CS_CIRCLE cb(*(CS_ArcSeg*)pm) ;
            nisects = la.Intersect2D(cb, ipnt1, ipnt2) ;
        }
        else
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pa) ;
            CS_CIRCLE cb(*(CS_ArcSeg*)pm) ;
            nisects = ca.Intersect2D(cb, ipnt1, ipnt2) ;
        }

        int dofailsafe = 0 ; 
        if (nisects == 0 || nisects == 3)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ua, um ; 
            pa->PointOnSegment(ipnt1, &ua) ;
            pm->PointOnSegment(ipnt1, &um) ;
            ua = ua - 0.1 * ua ;
            um = um + 0.1 * (1.0 - um) ; 
            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua), pm, pm->UPoint(um)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Standard intersect
            double ua1, ua2, um1, um2 ; 
            pa->PointOnSegment(ipnt1, &ua1) ;
            pm->PointOnSegment(ipnt1, &um1) ;
            pa->PointOnSegment(ipnt2, &ua2) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            
            ua1 = max(ua1, ua2) ; 
            um1 = min(um1, um2) ; 
            ua1 = ua1 - 0.1 * ua1 ;
            um1 = um1 + 0.1 * (1.0 - um1) ; 

            if (CS_ExTrimEndpoints(pa, pa->UPoint(ua1), pm, pm->UPoint(um1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pEAcrv->Append(pa) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pa ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pa = new CS_LineSeg ; 
            pa->sp = pEC->StartPoint() ; 
            pa->ep = pm->StartPoint() ; 
        
            pEAcrv->Append(pa) ; 
            delete pm ; 
        }
    }


    if ((pAB->SegmentType() == CS_Segment::LINE_TYPE) &&
        (pBD->SegmentType() == CS_Segment::LINE_TYPE))
    {   // Then we are simply intersecting two lines
        nBDF = 1 ; // we're modifying one segment in the BDF curve section
        CS_LineSeg *pm = (CS_LineSeg *)pAB->Copy() ;
        CS_LineSeg *pb = (CS_LineSeg *)pBD->Copy() ;
        pm->Offset(ofsdist) ;
        
        // Need to work out the pick points that get passed to the 
        // extend-trim command
        CS_LINE lm(*(CS_LineSeg*)pm) ; 
        CS_LINE lb(*(CS_LineSeg*)pb) ; 

        CS_POINT ipnt ; 
        int nisects = lm.Intersect2D(lb, ipnt) ;
        // Note, the two lines must intersect since they intersected before

        double ub, um ; 
        pm->PointOnSegment(ipnt, &um) ;
        pb->PointOnSegment(ipnt, &ub) ;

        um = um - 0.1 * um ;
        ub = ub + 0.1 * (1.0 - ub) ; 

        CS_ExTrimEndpoints(pm, pm->UPoint(um), pb, pb->UPoint(ub)) ;
        pBFcrv->Append(pb) ;
        delete pm ; 
    }
    else if ((pAB->SegmentType() == CS_Segment::ARC_TYPE) &&
             (pBD->SegmentType() == CS_Segment::LINE_TYPE))
    {   // Connected to an arc segment
        nBDF = 1 ; // we're modifying one segment in the BDF curve section
        CS_SegPtr pm = pAB->Copy() ;
        CS_SegPtr pb = pBD->Copy() ;
        pm->Offset(ofsdist) ;

        int nisects ;
        CS_POINT ipnt1, ipnt2 ;

        if (pb->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pm) ;
            CS_LINE lb(*(CS_LineSeg*)pb) ;
            nisects = ca.Intersect2D(lb, ipnt1, ipnt2) ;
        }
        else
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pm) ;
            CS_CIRCLE cb(*(CS_ArcSeg*)pb) ;
            nisects = ca.Intersect2D(cb, ipnt1, ipnt2) ;
        }

        int dofailsafe = 0 ; 
        if (nisects == 0 || nisects == 3)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ub, um ; 
            pm->PointOnSegment(ipnt1, &um) ;
            pb->PointOnSegment(ipnt1, &ub) ;
            um = um - 0.1 * um ;
            ub = ub + 0.1 * (1.0 - ub) ; 
            if (CS_ExTrimEndpoints(pm, pm->UPoint(um), pb, pb->UPoint(ub)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Tangent intersection
            double ub1, ub2, um1, um2 ; 
            pm->PointOnSegment(ipnt1, &um1) ;
            pb->PointOnSegment(ipnt1, &ub1) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            pb->PointOnSegment(ipnt2, &ub2) ;
            
            um1 = max(um1, um2) ; 
            ub1 = min(ub1, ub2) ; 
            um1 = um1 - 0.1 * um1 ;
            ub1 = ub1 + 0.1 * (1.0 - ub1) ; 

            if (CS_ExTrimEndpoints(pm, pm->UPoint(um1), pb, pb->UPoint(ub1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pb ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pb = new CS_LineSeg ; 
            pb->sp = pm->EndPoint() ; 
            pb->ep = pBD->EndPoint() ; 
        
            pBFcrv->Append(pb) ; 
            delete pm ; 
        }
    }
    else if ((pAB->SegmentType() == CS_Segment::LINE_TYPE) &&
             (pBD->SegmentType() == CS_Segment::ARC_TYPE))
    {   // Connected to an arc segment
        nBDF = 2 ; // we're modifying two segments in the ECA curve section
        CS_ArcSeg *pas = (CS_ArcSeg*)pBD ; 
        BDrad = pas->rad ; 

        CS_SegPtr pDF = sc.Next(pBD) ;
        CS_SegPtr pm = pAB->Copy() ;
        CS_SegPtr pb = pDF->Copy() ;
        pm->Offset(ofsdist) ;

        int nisects ;
        CS_POINT ipnt1, ipnt2 ;

        if (pb->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_LINE la(*(CS_LineSeg*)pm) ;
            CS_LINE lb(*(CS_LineSeg*)pb) ;
            nisects = la.Intersect2D(lb, ipnt1) ;
        }
        else
        {
            CS_LINE la(*(CS_LineSeg*)pm) ;
            CS_CIRCLE cb(*(CS_ArcSeg*)pb) ;
            nisects = la.Intersect2D(cb, ipnt1, ipnt2) ;
        }


        int dofailsafe = 0 ; 

        if (nisects == 0 || nisects == 3)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ub, um ; 
            pm->PointOnSegment(ipnt1, &um) ;
            pb->PointOnSegment(ipnt1, &ub) ;
            um = um - 0.1 * um ;
            ub = ub + 0.1 * (1.0 - ub) ; 
            if (CS_ExTrimEndpoints(pm, pm->UPoint(um), pb, pb->UPoint(ub)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Tangent intersection
            double ub1, ub2, um1, um2 ; 
            pm->PointOnSegment(ipnt1, &um1) ;
            pb->PointOnSegment(ipnt1, &ub1) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            pb->PointOnSegment(ipnt2, &ub2) ;
            
            um1 = max(um1, um2) ; 
            ub1 = min(ub1, ub2) ; 
            um1 = um1 - 0.1 * um1 ;
            ub1 = ub1 + 0.1 * (1.0 - ub1) ; 

            if (CS_ExTrimEndpoints(pm, pm->UPoint(um1), pb, pb->UPoint(ub1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pb ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pb = new CS_LineSeg ; 
            pb->sp = pm->EndPoint() ; 
            pb->ep = pDF->EndPoint() ; 
        
            pBFcrv->Append(pb) ; 
            delete pm ; 
        }
    }
    else if ((pAB->SegmentType() == CS_Segment::ARC_TYPE) &&
             (pBD->SegmentType() == CS_Segment::ARC_TYPE))
    {   // Connected to an arc segment
        nBDF = 2 ; // we're modifying two segments in the ECA curve section
        CS_ArcSeg *pas = (CS_ArcSeg*)pBD ; 
        BDrad = pas->rad ; 

        CS_SegPtr pDF = sc.Next(pBD) ;
        CS_SegPtr pm = pAB->Copy() ;
        CS_SegPtr pb = pDF->Copy() ;
        pm->Offset(ofsdist) ;

        int nisects ;
        CS_POINT ipnt1, ipnt2 ;

        if (pb->SegmentType() == CS_Segment::LINE_TYPE)
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pm) ;
            CS_LINE lb(*(CS_LineSeg*)pb) ;
            nisects = ca.Intersect2D(lb, ipnt1, ipnt2) ;
        }
        else
        {
            CS_CIRCLE ca(*(CS_ArcSeg*)pm) ;
            CS_CIRCLE cb(*(CS_ArcSeg*)pb) ;
            nisects = ca.Intersect2D(cb, ipnt1, ipnt2) ;
        }


        int dofailsafe = 0 ; 
        if (nisects == 0 || nisects == 3)
        {   // No intersections, nothing to do
            dofailsafe = 1 ; 
        }
        else if(nisects == 1)
        {   // Tangent intersection
            double ub, um ; 
            pm->PointOnSegment(ipnt1, &um) ;
            pb->PointOnSegment(ipnt1, &ub) ;
            um = um - 0.1 * um ;
            ub = ub + 0.1 * (1.0 - ub) ; 
            if (CS_ExTrimEndpoints(pm, pm->UPoint(um), pb, pb->UPoint(ub)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }
        else if(nisects == 2)
        {   // Standard intersect
            double ub1, ub2, um1, um2 ; 
            pm->PointOnSegment(ipnt1, &um1) ;
            pb->PointOnSegment(ipnt1, &ub1) ;
            pm->PointOnSegment(ipnt2, &um2) ;
            pb->PointOnSegment(ipnt2, &ub2) ;
            
            um1 = max(um1, um2) ; 
            ub1 = min(ub1, ub2) ; 
            um1 = um1 - 0.1 * um1 ;
            ub1 = ub1 + 0.1 * (1.0 - ub1) ; 

            if (CS_ExTrimEndpoints(pm, pm->UPoint(um1), pb, pb->UPoint(ub1)))
            {
                dofailsafe = 1 ; 
            }
            else
            {
                pBFcrv->Append(pb) ;
                delete pm ; 
            }
        }

        if (dofailsafe)
        {
            delete pb ; 
            delete pm ; 

            CS_SegPtr pm = pAB->Copy() ;
            pm->Offset(ofsdist) ; 

            CS_LineSeg *pb = new CS_LineSeg ; 
            pb->sp = pm->EndPoint() ; 
            pb->ep = pDF->EndPoint() ; 
        
            pBFcrv->Append(pb) ; 
            delete pm ; 
        }
    }


    // Now have all the curve sections we need, only have to extract out the 
    // remaining parts and piece everything together.

    CS_Curve *pstretch = new CS_Curve ; 

    // Step one is to connect together the stretched curve segments
    if (pAB->SegmentType() == CS_Segment::LINE_TYPE)
    {
        CS_LineSeg *pabls = new CS_LineSeg ; 
        pabls->sp = pEAcrv->EndPoint() ; 
        pabls->ep = pBFcrv->StartPoint() ; 

        CS_SegPtr pfillet ;

        pstretch->AddCurve(pEAcrv) ; 
        pfillet = pstretch->pEnd ; 
        pstretch->Append(pabls) ;
        if (CArad != 0.0) pstretch->FilletSegments(pfillet, CArad) ;
        pfillet = pstretch->pEnd ; 
        pstretch->AddCurve(pBFcrv) ; 
        if (BDrad != 0.0) pstretch->FilletSegments(pfillet, BDrad) ;
    }
    else
    {   
        CS_ArcSeg *pabls = (CS_ArcSeg *)pAB->Copy() ;
        pabls->SetSPEP(pEAcrv->EndPoint(), pBFcrv->StartPoint(), 
                            pabls->swp >= 0.0 ? CCW : CW) ; 

        CS_SegPtr pfillet ;

        pstretch->AddCurve(pEAcrv) ; 
        pfillet = pstretch->pEnd ; 
        pstretch->Append(pabls) ;
        if (CArad != 0.0) pstretch->FilletSegments(pfillet, CArad) ;
        pfillet = pstretch->pEnd ; 
        pstretch->AddCurve(pBFcrv) ; 
        if (BDrad != 0.0) pstretch->FilletSegments(pfillet, BDrad) ;
    }

    // Now need to figure out what portion of the original curve needs 
    // to be extracted and added to the final output curve
    CS_Curve *pfinal ; 
    CS_SegPtr ps ;
    CS_SegPtr pe ; 

    ps = sc.Prev(pAB) ; 
    if (nECA == 2)
        ps = sc.Prev(ps) ; 

    pe = sc.Next(pAB) ; 
    if (nBDF == 2)  
        pe = sc.Next(pe) ; 

    if (sc.Closed())
    {
        pfinal = sc.CopySection(pe, ps, 1.0, 0.0, SEGMENTBASED_UVALUES) ; 
        if (pstretchSection)
        {
            *pstretchSection = new CS_Curve ; 
            (*pstretchSection)->CopyCurve(*pstretch) ; 
        }
        pfinal->AddCurve(pstretch) ; 
    }
    else
    {
        pfinal = sc.CopySection(sc.pStart, ps, 0.0, 0.0, SEGMENTBASED_UVALUES) ; 
        if (pstretchSection)
        {
            *pstretchSection = new CS_Curve ; 
            (*pstretchSection)->CopyCurve(*pstretch) ; 
        }
        pfinal->AddCurve(pstretch) ; 
        pfinal->AddCurve(sc.CopySection(pe, sc.pEnd, 1.0, 1.0, SEGMENTBASED_UVALUES)) ;  
    }
    pfinal->Complete() ; 
    prescrv = pfinal ; 

    return 0 ; 
}