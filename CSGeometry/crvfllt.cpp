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
// crvfllt.cpp - curve class filleting routines
// Creates - Line-Line Line-Arc style fillets

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)     a
#else
#define CS_DEBUG(a)
#endif



// Fillet the curve with the given radius
int CS_Curve::Fillet(double frad, double minfrad, double divfactor, int searchfillet)
{
    if (tcomp_EQZ(frad))
        return nodecnt ;  // nothing to do

    bool bReduceRadMode = false ; 

    if (tcomp_GT(minfrad, 0.0) && tcomp_GT(divfactor, 1.0))
        bReduceRadMode = true ; 

    int nFilletFailureCount = 0 ; 
    int status ; 

    CS_SegPtr pnxt ;
    CS_SegPtr pfillet ;
    CS_SegPtr pn = pStart ;

    while (pn)
    {
        pnxt = pn->next ; 

        status = 0 ; 
        pfillet = FilletSegments(pn, frad, searchfillet, &status) ;
        if (!pfillet && !(status & CS_FILLET_SEGMENTS_TANGENT) && bReduceRadMode)
        {   // Then attempt to refine fillet rad and continue
            bool bFilletFailed = true ; 
            double fradLast = frad ;
            double r = frad / divfactor ; 
            while (tcomp_NEQ(r, fradLast) && tcomp_NEZ(r / 10.0))
            {
                pfillet = FilletSegments(pn, r, searchfillet) ;
                if (pfillet)
                {
                    bFilletFailed = false ; 
                    break ; // did fillet
                }
                fradLast = r ; 
                r /= divfactor ; 
            }

            if (bFilletFailed) 
                nFilletFailureCount++ ; 
        }

        /*
        else if (!pfillet && searchfillet && !(status & CS_FILLET_SEGMENTS_TANGENT))
        {   // See if we can fillet this segment with the next one skipping 
            // the current segment, until we reach the last segment again.
            CS_Curve testcrv ; 
            testcrv.Append(pn->Copy()) ; 
            CS_SegPtr ps ; 

            if (Closed())
            {
                if (!pnxt)
                    ps = pStart ; 
                else
                    ps = Next(pnxt) ;
            }
            else
            {
                ps = pnxt->next ; 
            }

            while (ps && (ps != pn))
            {
                testcrv.Append(ps->Copy()) ; 
                CS_SegPtr pfs = testcrv.FilletSegments(testcrv.pStart, frad, 0, &status) ;
                if (pfs)
                {   // The fillet worked so we want to delete out the section of the 
                    // base curve and insert this fillet
                    // Here we simply insert the testcrv into the *this curve
                    // from pn to ps 

                    // 1) Delete from pn to ps
                    CS_SegPtr pins = pn->prev ; // save the insert point
                    CS_SegPtr pstop = ps->next ; 
                    while (pn != pstop)
                    {
                        CS_SegPtr pdel = pn; 
                        pn = pn->next ;
                        Delete(pdel) ; 
                    }

                    // Now insert the testcrv segments
                    pn = testcrv.pStart ; 
                    pstop = pn ; 
                    while (pn) 
                    {
                        pnxt = pn->next ; 
                        pstop = Insert(pins, pn, CS_NOENDPOINTADJUSTMENT) ; 
                        pn = pnxt ; 
                    }

                    pnxt = pstop ; 
                    break ; // Finished this fillet
                }

                testcrv.Delete(testcrv.pEnd) ; 

                if (Closed())
                    ps = Next(ps) ;
                else
                    ps = ps->next ; 
            }

        }
        */

        pn = pnxt ; 
    }

    return nFilletFailureCount ; 
}

///////////////////////////////////////////////////////////////////////////
// This is a rather large mess of code to do something as simple as 
// filleting two curve segemtns. See Notes Geom Algo's RR-Vol1 start on page 
// 61 for notes on what is happening here. Pg 67 is the start of where 
// all the ARC-ARC conditions are defined. 
///////////////////////////////////////////////////////////////////////////

CS_SegPtr CS_Curve::FilletSegments(CS_SegPtr psna, double frad, int searchfillet, int *status)
{
    CS_SegPtr psnb ; // the second node to fillet with

    if (tcomp_EQZ(frad))
    {
	CS_DEBUG(fprintf(fpDebugOut, "Zero radius, can't do fillet\n") ; )
	return NULL ; // can't fillet with 0 radius
    }

    if (nodecnt < 2)
    {
	CS_DEBUG(fprintf(fpDebugOut, "Less than 2 segments in the curve, can't fillet\n"); )
	return NULL ; // can't fillet a single segment
    }

    psnb = psna->next ;
    if (psnb == NULL)
    {	// Then we are at the end of the curve
	// Test if the curve is closed to see if we can even do the fillet
	if (Closed())
	{   // Then conceivably we can do the fillet
	    psnb = pStart ;
	}
	else
	{   // Can't fillet the last segment end point because it's not
	    // connected to anything
	    // TO DO - add setgeomerror(CANT_FILLET_UNCONNECTED_END_NODE)
	    return NULL ;
	}
    }

    ////////////////////////////////////////////////////////////////////////
    // LINE-LINE
    ////////////////////////////////////////////////////////////////////////
    // For now the two segments must be lines and their endpoints have to meet
    if ((psna->SegmentType() == CS_Segment::LINE_TYPE) &&
        (psnb->SegmentType() == CS_Segment::LINE_TYPE))
    {	// Then we can do this fillet maybe
	CS_LineSeg *pla = (CS_LineSeg *)psna ;
	CS_LineSeg *plb = (CS_LineSeg *)psnb ;

	CS_DEBUG(
	    fprintf(fpDebugOut, "Filleting line segments, rad=%.6lf:\n", frad) ;
	    pla->sp.Print(fpDebugOut) ; fprintf(fpDebugOut, " ") ; 
            pla->ep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ;
	    plb->sp.Print(fpDebugOut) ; fprintf(fpDebugOut, " ") ; 
            plb->ep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ;
	)

	CS_LineSeg lsa(pla->StartPoint(), pla->EndPoint()) ;
	CS_LineSeg lsb(plb->StartPoint(), plb->EndPoint()) ;

	if (lsa.ep != lsb.sp)
	{
	   CS_DEBUG(fprintf(fpDebugOut, "Error: end points don't match (A1)\n") ;)
	    return NULL ; // end points have to match to do the fillet
	}

	// The end points match so we are all set to do the fillet operation
	CS_VECTOR va(lsa.sp, lsa.ep) ;
	CS_VECTOR vb(lsb.sp, lsb.ep) ;
	CS_VECTOR vaofs, vbofs ;
	double zc = ZCross(va,vb) ;

	if (tcomp_EQZ(zc))
	{
	    CS_DEBUG(fprintf(fpDebugOut, "Error: collinear lines zc=0 (A2)\n") ;)
            if (status)
                *status = CS_FILLET_SEGMENTS_TANGENT ;
            return NULL ; 
	}

	if (zc < 0.0)
	{
	    vaofs = va.RightPerp() ;
	    vaofs = vaofs.Unit() * frad ;
	    vbofs = vb.RightPerp() ;
	    vbofs = vbofs.Unit() * frad ;
	}
	else
	{
	    vaofs = va.LeftPerp() ;
	    vaofs = vaofs.Unit() * frad ;
	    vbofs = vb.LeftPerp() ;
	    vbofs = vbofs.Unit() * frad ;
	}

	// Offset the two line segments
	lsa.Move(vaofs) ;
	lsb.Move(vbofs) ;

	CS_LINE linea(lsa) ;
	CS_LINE lineb(lsb) ;
	CS_POINT pntc ;
	int numisects ;

	numisects = linea.Intersect2D(lineb, pntc) ;
	if (numisects == 0)
	{   // Then something went really wrong since we already tested for
	    // the parallel-collinear condition so the lines have to
	    // intersect
	    CS_DEBUG(fprintf(fpDebugOut, "No intersect with offset segments\n") ;)
	    return NULL ;
	}

	if (!lsa.PointOnSegment(pntc) || !lsb.PointOnSegment(pntc))
	{
	    // This error means the rad was too large to perform the
	    // fillet since the intersect point went beyond the end
	    // points of one of the line segments
	    CS_DEBUG(fprintf(fpDebugOut, "Offset segs Isect point not on segments\n") ;)
	    return NULL ;
	}

	CS_POINT pntm = pntc - vaofs ;
	CS_POINT pntn = pntc - vbofs ;

	double alpha = mod2PI(vaofs.AngleXY() + RADIAN180) ;
	double beta = mod2PI(vbofs.AngleXY() + RADIAN180) ;
	double start_angle, end_angle, sweep ; // angles for the arc

	if (zc < 0.0)
	{
	    start_angle = beta ;
	    end_angle = alpha ;
	}
	else
	{
	    start_angle = alpha ;
	    end_angle = beta ;
	}

	// Only thing left is to calculate the sweep angle
	if (start_angle > end_angle)
	    sweep = RADIAN360 - start_angle + end_angle ;
	else
	    sweep = end_angle - start_angle ;

        // Define the arc as CCW 
	CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	pfarc->rad = frad ;
	pfarc->ctr = pntc ;
	pfarc->sa = NormalizeAngle(start_angle) ;
	pfarc->swp = fabs(sweep) ;
	if (zc < 0.0)
            pfarc->Reverse() ; // set it CW

	CS_DEBUG(
	    fprintf(fpDebugOut, "Creating fillet arc, ctr="); pntc.Print(fpDebugOut) ;
	    fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf dir=%s\n",
			    frad, pfarc->sa, sweep,
			    (pfarc->ArcDir() == CW) ? "CW" : "CCW") ;
	)

	// Finally we need to adjust the end points, arclength's and add
	// the arc to the CS_Curve
	CS_SegPtr pnewseg ;
	pnewseg = InsertAfter(psna, pfarc, 1) ;
	if (!pnewseg)
	    return NULL ;

	// Now adjust the lengths and end points of the two line segments
	// subtract the current lengths of the segments
	arclength -= pla->ArcLength() ;
	arclength -= plb->ArcLength() ;

	//  adjusting the end point  for segment A
	pla->ep = pntm ;
	
	// adjusting the start point for segment B
	plb->sp = pntn ;

	// Now add the new arclength's back on
	arclength +=  pla->ArcLength() ;
	arclength +=  plb->ArcLength() ;

	// We are done
	return pnewseg ;
    }
    ////////////////////////////////////////////////////////////////////////
    // LINE-ARC
    ////////////////////////////////////////////////////////////////////////
    // TO DO - delete segments A or B if either is completely consumed by
    //	       the fillet operation.
    else if ((psna->SegmentType() == CS_Segment::LINE_TYPE) &&
             (psnb->SegmentType() == CS_Segment::ARC_TYPE))
    {	// Line-Arc style fillet
	CS_LineSeg *psega = (CS_LineSeg *)psna ;
	CS_ArcSeg *psegb = (CS_ArcSeg *)psnb ;
	int nisects ;

	CS_VECTOR vta, vtb ;
	vta = psega->UTangent(1.0) ; // unit tangent vector
	vtb = psegb->UTangent(0.0) ; // returns unit tangent vector

	double zx = ZCross(vta, vtb) ; // z component of cross product

	CS_DEBUG
	(
	    fprintf(fpDebugOut, "Line-Arc tangent vectors A,B\n    ") ;
	    vta.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n    ") ; 
            vtb.Print(fpDebugOut) ;
	    fprintf(fpDebugOut, "Line-Arc zcross=%lf\n", zx) ;
	)

	if (tcomp_EQZ(zx))
	{
	    CS_DEBUG(fprintf(fpDebugOut, "Can't fillet, tangent endpoints\n")) ;
            if (status)
                *status = CS_FILLET_SEGMENTS_TANGENT ;
            return NULL ; 
	}

	if ((psegb->ArcDir() == CW) && (zx < 0))
	{   // Case1: CW and [(tl x ta).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // LINE-ARC, Case 1:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vta.RightPerp() * frad ;
	    CS_LineSeg lnpq(psega->sp + vpp, psega->ep + vpp) ;
	    CS_ArcSeg  arci = *psegb ;

	    arci.rad = psegb->rad - frad ;
	    if (arci.rad < 0)
		return NULL ; // can't do the fillet

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), lnpq.UPoint(uipa[1])) ;
		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psegb->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = ipnt - vpp ;
	    pntb = psegb->ctr + (vcf * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

            // adjusting the end point for segment A
            psega->ep = pnta ;

	    // Now adjust the sweep for the segment B arc
            double oldsang = psegb->sa ; 
            psegb->sa = vcf.AngleXY() ; 
            // Subtract the sweep portion required to give new arc
            // Note because the arc is CW (swp < 0) and arc_sweep returns
            // a value > 0 then by adding we are effectively 
            // subtracting from the current sweep
            psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if((psegb->ArcDir() == CCW) && (zx < 0))
	{   // Case2: CCW and [(tl x ta).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // LINE-ARC, Case 2:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vta.RightPerp() * frad ;
	    CS_LineSeg lnpq(psega->sp + vpp, psega->ep + vpp) ;
	    CS_ArcSeg  arci = *psegb ;

	    arci.rad = psegb->rad + frad ;

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psegb->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = ipnt - vpp ;
	    pntb = psegb->ctr + (vcf * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case2:  ctr="); ipnt.Print() ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment A
	    psega->ep = pnta ;

	    // Now adjust the sweep for the segment B arc
	    double oldsang = psegb->sa ; // save the old start angle
	    psegb->sa = vcf.AngleXY() ;
	    // Subtract the sweep portion of the arc that was removed by the
	    // fillet operation.
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if((psegb->ArcDir() == CCW) && (zx > 0))
	{   // Case3: CCW and [(tl x ta).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // LINE-ARC, Case 3:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vta.LeftPerp() * frad ;
	    CS_LineSeg lnpq(psega->sp + vpp, psega->ep + vpp) ;
	    CS_ArcSeg  arci = *psegb ;

	    arci.rad = psegb->rad - frad ;
	    if (arci.rad < 0)
		return NULL ; // can't do the fillet

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psegb->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = ipnt - vpp ;
	    pntb = psegb->ctr + (vcf * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case3:  ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment A
	    psega->ep = pnta ;

	    // Now adjust the sweep for the segment B arc
	    double oldsang = psegb->sa ; // save the old start angle
	    psegb->sa = vcf.AngleXY() ;
	    // Subtract the sweep portion of the arc that was removed by the
	    // fillet operation.
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if((psegb->ArcDir() == CW) && (zx > 0))
	{   // Case4: CW and [(tl x ta).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // LINE-ARC, Case 4:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vta.LeftPerp() * frad ;
	    CS_LineSeg lnpq(psega->sp + vpp, psega->ep + vpp) ;
	    CS_ArcSeg  arci = *psegb ;

	    arci.rad = psegb->rad + frad ;

	    double uipa[2], uipb[2] ;

	    CS_DEBUG
	    (
		fprintf(fpDebugOut, "Line-Arc Case 4 fillet\n") ;
		lnpq.Print(fpDebugOut) ;
		arci.Print(fpDebugOut) ;
	    )
	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
	    {
		CS_DEBUG(fprintf(fpDebugOut, "No intersects in line-arc case 4 fillet\n")) ;
		return NULL ; // can't do fillet, no intersections found
	    }

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psegb->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = ipnt - vpp ;
	    pntb = psegb->ctr + (vcf * psegb->rad) ;

	    CS_DEBUG
	    (
		fprintf(fpDebugOut, "Intersect points are (A,B)\n    ") ;
		pnta.Print(fpDebugOut) ; fprintf(fpDebugOut,"    \n") ; pntb.Print(fpDebugOut) ;
	    )

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut,"Creating fillet arc, LA-Case4:  ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf dir=%d\n",
				frad, pfarc->sa, pfarc->swp,
				(pfarc->ArcDir() == CW)) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment A
	    psega->ep = pnta ;

	    // Now adjust the sweep for the segment B arc
	    // fillet operation.
            double oldsang = psegb->sa ; 
            psegb->sa = vcf.AngleXY() ; 
            // Adding to a negative sweep thus reducing magnitude of included
            // angle
	    psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
    }
    ////////////////////////////////////////////////////////////////////////
    // ARC-LINE
    ////////////////////////////////////////////////////////////////////////
    // TO DO - delete segments A or B if either is completely consumed by
    //	       the fillet operation.
    else if ((psna->SegmentType() == CS_Segment::ARC_TYPE) &&
             (psnb->SegmentType() == CS_Segment::LINE_TYPE))
    {	// Arc-Line style fillet
	CS_ArcSeg *psega = (CS_ArcSeg *)psna ;
	CS_LineSeg *psegb = (CS_LineSeg *)psnb ;
	int nisects ;

	CS_VECTOR vta, vtb ;
	vta = psega->UTangent(1.0) ; // unit tangent vector
	vtb = psegb->UTangent(0.0) ; // returns unit tangent vector

	double zx = ZCross(vta, vtb) ; // z component of cross product

	if (tcomp_EQZ(zx))
        {
            if (status)
                *status = CS_FILLET_SEGMENTS_TANGENT ;
            return NULL ; 
        }

	if ((psega->ArcDir() == CW) && (zx < 0))
	{   // Case1: CW and [(ta x tl).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-LINE, Case 1:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vtb.RightPerp() * frad ;
	    CS_ArcSeg  arci = *psega ;
	    CS_LineSeg lnpq(psegb->sp + vpp, psegb->ep + vpp) ;

	    arci.rad = psega->rad - frad ;
	    if (arci.rad < 0)
		return NULL ; // can't do the fillet

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psegb->StartPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psegb->StartPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psega->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = psega->ctr + (vcf * psega->rad) ;
	    pntb = ipnt - vpp ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AL-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf, dir=%d\n",
				frad, pfarc->sa, pfarc->swp,
				(pfarc->ArcDir() == CW)) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment B
	    psegb->sp = pntb ;

	    // Now adjust the sweep for the segment A arc
	    psega->swp = -arc_sweep(psega->sa, vcf.AngleXY(), CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) && (zx < 0))
	{   // Case2: CCW and [(ta x tl).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-LINE, Case 2:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vtb.RightPerp() * frad ;
	    CS_ArcSeg  arci = *psega ;
	    CS_LineSeg lnpq(psegb->sp + vpp, psegb->ep + vpp) ;

	    arci.rad = psega->rad + frad ;

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psegb->StartPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psegb->StartPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psega->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = psega->ctr + (vcf * psega->rad) ;
	    pntb = ipnt - vpp ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AL-Case2: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

            // adjusting the end point for segment B
	    psegb->sp = pntb ;

	    // Now adjust the sweep for the segment A arc
	    psega->swp = arc_sweep(psega->sa, vcf.AngleXY(), CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) && (zx > 0))
	{   // Case3: CCW and [(ta x tl).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-LINE, Case 3:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vtb.LeftPerp() * frad ;
	    CS_ArcSeg  arci = *psega ;
	    CS_LineSeg lnpq(psegb->sp + vpp, psegb->ep + vpp) ;

	    arci.rad = psega->rad - frad ;
	    if (arci.rad <= 0)
		return NULL ;

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psegb->StartPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psegb->StartPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psega->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = psega->ctr + (vcf * psega->rad) ;
	    pntb = ipnt - vpp ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AL-Case3: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment B
	    psegb->sp = pntb ;

	    // Now adjust the sweep for the segment A arc
	    psega->swp = arc_sweep(psega->sa, vcf.AngleXY(), CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CW) && (zx > 0))
	{   // Case4: CW and [(ta x tl).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-LINE, Case 4:
	    ////////////////////////////////////////////////////////////////
	    CS_VECTOR vpp = vtb.LeftPerp() * frad ;
	    CS_ArcSeg  arci = *psega ;
	    CS_LineSeg lnpq(psegb->sp + vpp, psegb->ep + vpp) ;

	    arci.rad = psega->rad + frad ;

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = lnpq.Intersect2D(arci, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if (nisects == 0)
		return NULL ; // can't do fillet, no intersections found

	    CS_POINT ipnt ;
	    if (nisects > 1)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psegb->StartPoint(), lnpq.UPoint(uipa[0])) ;
		CS_VECTOR v2(psegb->StartPoint(), lnpq.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
		    ipnt = lnpq.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = lnpq.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = lnpq.UPoint(uipa[0]) ;
	    }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcf(psega->ctr, ipnt) ;

	    vcf = vcf.Unit() ;

	    pnta = psega->ctr + (vcf * psega->rad) ;
	    pntb = ipnt - vpp ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG
	    (
		fprintf(fpDebugOut, "Creating fillet arc, AL-Case4: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf, dir=%d\n",
				frad, pfarc->sa, pfarc->swp,
				(pfarc->ArcDir() == CW)) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    // adjusting the end point for segment B
	    psegb->sp = pntb ;

	    // Now adjust the sweep for the segment A arc
	    psega->swp = -arc_sweep(psega->sa, vcf.AngleXY(), CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
    }
    ////////////////////////////////////////////////////////////////////////
    // ARC-ARC
    ////////////////////////////////////////////////////////////////////////
    // TO DO - delete segments A or B if either is completely consumed by
    //	       the fillet operation.
    else if ((psna->SegmentType() == CS_Segment::ARC_TYPE) &&
             (psnb->SegmentType() == CS_Segment::ARC_TYPE))
    {	// Arc-Arc style fillet
	CS_ArcSeg *psega = (CS_ArcSeg *)psna ;
	CS_ArcSeg *psegb = (CS_ArcSeg *)psnb ;
	int nisects ;

	CS_VECTOR vta, vtb ;
	vta = psega->UTangent(1.0) ; // unit tangent vector
	vtb = psegb->UTangent(0.0) ; // returns unit tangent vector

	double zx = ZCross(vta, vtb) ; // z component of cross product

	CS_DEBUG
	(
	    fprintf(fpDebugOut, "Arc-Arc fillet, zx=%.5lf\n   ", zx) ;
	    vta.Print(fpDebugOut) ; fprintf(fpDebugOut, "   ") ;
	    vtb.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ;
	)


	if (tcomp_EQZ(zx))
	{
            if (status)
                *status = CS_FILLET_SEGMENTS_TANGENT ;
            return NULL ; 
	}

	if ((psega->ArcDir() == CW) && (psegb->ArcDir() == CCW) && (zx < 0))
	{   // Case1: CW->CCW and [(ta x tb).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 1:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad -= frad ;
	    arcb.rad += frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 1:\n")) ;

	    if (tcomp_LEQ(arca.rad,0))
	    {
		CS_DEBUG(fprintf(fpDebugOut, "AA-Case1: arca.rad=%.5lf\n", arca.rad)) ;
		return NULL ; // can't do fillet with inverted or NULL arc
	    }

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		CS_DEBUG(fprintf(fpDebugOut, "AA-Case1: numisects = %d\n",nisects)) ;
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
	    {
		CS_DEBUG(
		  fprintf(fpDebugOut, "AA-Case1: Error inserting new arc into curve\n")) ;
		return NULL ;
	    }

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = -arc_sweep(psega->sa, vcfa.AngleXY(), CW) ;

	    oldsang = psegb->sa ;
	    psegb->sa = vcfb.AngleXY() ;
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CW) && 
                 (psegb->ArcDir() == CW) &&
                 (zx < 0))
	{   // Case2: CW->CW and [(ta x tb).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 2:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad -= frad ;
	    arcb.rad -= frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 2:\n")) ;

	    if (tcomp_LEQ(arca.rad,0) || tcomp_LEQ(arcb.rad, 0))
		return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AA-Case2: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = -arc_sweep(psega->sa, vcfa.AngleXY(), CW) ;

            oldsang = psegb->sa ; 
            psegb->sa = vcfb.AngleXY() ;
            // Note: decreasing magnitude of sweep by adding to a negative
            // sweep value
	    psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ( (psega->ArcDir() == CW) &&
		  (psegb->ArcDir() == CW) && 
                  (zx > 0))
	{   // Case3: CW->CW and [(ta x tb).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 3:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad += frad ;
	    arcb.rad += frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 3:\n")) ;

	    // if (tcomp_LEQ(arca.rad,0) || tcomp_LEQ(arcb.rad, 0))
	    //	   return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections

            CS_DEBUG(
                fprintf(fpDebugOut, "sega endpoint = ") ; psega->EndPoint().Print(fpDebugOut) ; 
                fprintf(fpDebugOut, "#isects= %d\n", nisects) ; 
                fprintf(fpDebugOut, "Intersect points are\n") ; 
                arca.UPoint(uipa[0]).Print(fpDebugOut) ; fprintf(fpDebugOut, "\n") ; 
                if (nisects > 1)
                    arca.UPoint(uipa[1]).Print(fpDebugOut) ; 
            ) ; 

            
            if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point


		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

            if (tcomp_EQ(pfarc->swp, RADIAN360, 0.001))
            {   // We've likely got a near zero length fillet resulting
                // from an arc with an extremely large radius that is 
                // causing math problems, so ignore this fillet 
                delete pfarc ; 
                return 0 ; 
            }


	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AA-Case3: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = -arc_sweep(psega->sa, vcfa.AngleXY(), CW) ;

	    oldsang = psegb->sa ;
            psegb->sa = vcfb.AngleXY() ; 
	    psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CW) &&
		 (psegb->ArcDir() == CCW) && 
                 (zx > 0))
	{   // Case4: CW->CCW and [(ta x tb).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 4:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad += frad ;
	    arcb.rad -= frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 4:\n")) ;

	    if (tcomp_LEQ(arcb.rad, 0))
	    {
		CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc Case 4:, arcb.rad=%.6lf\n",
				arcb.rad)) ;
		return NULL ; // can't do fillet with inverted or NULL arc
	    }

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc Case 4: nisects=%d\n", nisects)) ;
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ;
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AA-Case4: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = -arc_sweep(psega->sa, vcfa.AngleXY(), CW) ;

	    oldsang = psegb->sa ;
	    psegb->sa = vcfb.AngleXY() ;
            // In this case the original segment B is CCW thus swp > 0
            // and we want to subtract from the existing value
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) &&
		 (psegb->ArcDir() == CW) && 
                 (zx < 0))
	{   // Case5: CCW->CW and [(ta x tb).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 5:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad += frad ;
	    arcb.rad -= frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 5:\n")) ;

	    if (tcomp_LEQ(arcb.rad, 0))
		return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ;
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }


	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

            double oldsang ; 
	    psega->swp = arc_sweep(psega->sa, vcfa.AngleXY(), CCW) ;

            oldsang = psegb->sa ; 
            psegb->sa = vcfb.AngleXY() ;
            // Reduce neg swp by adding 
	    psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) &&
		 (psegb->ArcDir() == CCW) && 
                 (zx > 0))
	{   // Case6: CCW->CCW and [(ta x tb).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 6:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad -= frad ;
	    arcb.rad -= frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 6:\n")) ;

	    if (tcomp_LEQ(arca.rad, 0.0) || tcomp_LEQ(arcb.rad, 0.0))
		return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = arc_sweep(psega->sa, vcfa.AngleXY(), CCW) ;

	    oldsang = psegb->sa ;
	    psegb->sa = vcfb.AngleXY() ;
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) &&
		 (psegb->ArcDir() == CCW) && 
                 (zx < 0))
	{   // Case7: CCW->CCW and [(ta x tb).z < 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 7:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad += frad ;
	    arcb.rad += frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 7:\n")) ;

	    // if (tcomp_LEQ(arca.rad, 0.0) || tcomp_LEQ(arcb.rad, 0.0))
	    //	   return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
            CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                // TO DO - check to make sure that this in fact the case.
                // See notes GEOM ALGO's RR-VOL 4 pg 79 for specific case values.
                

                return 0 ; 
            }


	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, LA-Case1: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut, " rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

	    double oldsang ;
	    psega->swp = arc_sweep(psega->sa, vcfa.AngleXY(), CCW) ;

	    oldsang = psegb->sa ;
	    psegb->sa = vcfb.AngleXY() ;
	    psegb->swp -= arc_sweep(oldsang, psegb->sa, CCW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
	else if ((psega->ArcDir() == CCW) &&
		 (psegb->ArcDir() == CW) && 
                 (zx > 0))
	{   // Case8: CCW->CW and [(ta x tb).z > 0]
	    ////////////////////////////////////////////////////////////////
	    // ARC-ARC, Case 8:
	    ////////////////////////////////////////////////////////////////
	    CS_ArcSeg  arca = *psega ;
	    CS_ArcSeg  arcb = *psegb ;

	    arca.rad -= frad ;
	    arcb.rad += frad ;

	    CS_DEBUG(fprintf(fpDebugOut, "Arc-Arc fillet operation, case 8:\n")) ;

	    // if (tcomp_LEQ(arca.rad, 0.0) || tcomp_LEQ(arcb.rad, 0.0))
	    //	   return NULL ; // can't do fillet with inverted or NULL arc

	    double uipa[2], uipb[2] ;

	    // Intersect the line segment with the arc segment
	    nisects = arca.Intersect2D(arcb, uipa, uipb) ;
	    // Now check to make sure the interesection points if any are
	    // on the curve segments and thus are valid intersections
	    if ((nisects < 1) || (nisects > 2))
	    {
		return NULL ; // can't do fillet, no intersections found
			      // or the segments overlay one another
	    }

            int used2ndisect = 0 ; 
	    CS_POINT ipnt ;
	    if (nisects == 2)
	    {	// Then we have to find the nearest intersect point
		CS_VECTOR v1(psega->EndPoint(), arca.UPoint(uipa[0])) ;
		CS_VECTOR v2(psega->EndPoint(), arca.UPoint(uipa[1])) ;

		if (v1.Mag() > v2.Mag())
		{   // Then uip1 is closer
                    used2ndisect = 1 ; 
		    ipnt = arca.UPoint(uipa[1]) ;
		}
		else
		{   // The first intersect point is the closest
		    ipnt = arca.UPoint(uipa[0]) ;
		}
	    }
	    else
	    {	// Then there is a single intersection point
		ipnt = arca.UPoint(uipa[0]) ;
	    }

            if ((!used2ndisect && tcomp_EQ(uipa[0], 1.0) && tcomp_EQZ(uipb[0])) || 
                (used2ndisect && tcomp_EQ(uipa[1], 1.0) && tcomp_EQZ(uipb[1]))
               )
            {   // The two segments offset by the fillet radius intersect at 
                // their respective end points thus they are no different than
                // the original input arcs, which means doing
                // a fillet is pointless, since the fillet will end up being 
                // basically zero in length. 
                return 0 ; 
            }

	    // Now we proceed to calculate remaining information for the
	    // filleting arc to be created and inserted into the curve.
	    CS_POINT pnta, pntb ;
	    CS_VECTOR vcfa(psega->ctr, ipnt) ;
	    CS_VECTOR vcfb(psegb->ctr, ipnt) ;

	    vcfa = vcfa.Unit() ;
	    vcfb = vcfb.Unit() ;

	    pnta = psega->ctr + (vcfa * psega->rad) ;
	    pntb = psegb->ctr + (vcfb * psegb->rad) ;

	    CS_ArcSeg *pfarc = new CS_ArcSeg ; // create the fillet arc
	    pfarc->rad = frad ;
	    pfarc->ctr = ipnt ;

	    pfarc->SetSPEP(pnta, pntb, CCW) ;

	    CS_DEBUG(
		fprintf(fpDebugOut, "Creating fillet arc, AA-Case8: ctr="); ipnt.Print(fpDebugOut) ;
		fprintf(fpDebugOut," rad=%.6lf, sa=%.6lf, swp=%.6lf\n",
				frad, pfarc->sa, pfarc->swp) ;
	    )

	    // Finally we need to adjust the end points, arclength's and add
	    // the arc to the CS_Curve
	    CS_SegPtr pnewseg ;
	    // sets arc length for this curve during insert operation
	    pnewseg = InsertAfter(psna, pfarc, 1) ;
	    if (!pnewseg)
		return NULL ;

	    // Now adjust the lengths and end points of the two line segments
	    // subtract the current lengths of the segments
	    arclength -= psega->ArcLength() ;
	    arclength -= psegb->ArcLength() ;

            double oldsang ; 
	    psega->swp = arc_sweep(psega->sa, vcfa.AngleXY(), CCW) ;

            oldsang = psegb->sa ; 
            psegb->sa = vcfb.AngleXY() ;
            // Adding to -ve swp to decrease it
	    psegb->swp += arc_sweep(oldsang, psegb->sa, CW) ;

	    // Now add the new arclength's back on
	    arclength +=  psega->ArcLength() ;
	    arclength +=  psegb->ArcLength() ;

	    // We are done
	    return pnewseg ;
	}
    }
 
    // TO DO - handle spline cases for filleting
    // else if (LINE && SPLINE) {}
    // else if (SPLINE && LINE) {}
    // else if (ARC && SPLINE) {}
    // else if (SPLINE && ARC)	{}
    // else if (SPLINE && SPLINE) {}
    return NULL ; // didn't create fillet
}


/*
// Returns true if a fillet can be created between the two curve segments
int CS_Curve::CanFillet(CS_SegPtr psa, CS_SegPtr psb)
{
    return 0 ;
}
*/


