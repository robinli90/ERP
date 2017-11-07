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
// fitcircle.cpp - routines to find largest fitting circles within a shape

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
#include "cs_fitcircle.h"


static inline int SegInsideCirc(CS_ArcSeg *paseg, CS_Segment *pseg)
{
    // paseg is the circle
    if (pseg->IsLINE())
    {
        CS_LineSeg *ps = (CS_LineSeg *)pseg ; 
        if (    tcomp_LEQ(CS_Distance2D(paseg->ctr, ps->sp), paseg->rad) 
            &&  tcomp_LEQ(CS_Distance2D(paseg->ctr, ps->ep), paseg->rad))
        {
            return 1 ; 
        }
        return 0 ; 
    }
    else if (pseg->IsARC())
    {
        double uva[2], uvb[2] ; 
        CS_ArcSeg *ps = (CS_ArcSeg *)pseg ; 
        int nisects = paseg->Intersect2D(*ps, uva, uvb) ;
        if (nisects > 0)
            return 0 ; // can't be inside it it intersects

        if (tcomp_LT(CS_Distance2D(paseg->ctr, ps->StartPoint()), paseg->rad)) 
            return 1 ; 
        return 0 ; 
    }

    return 0 ; // something went wrong if we get to here. 
}

// Returns number of tangent intersections, extracts the tangent intesection at the 
// u point. A negative return value indicates that tangency errors occured, thus 
// must take the absolute value of the returned value. passeg points to an arc
// definition of a complete circle
static inline int IntersectCrvAndCirc(CS_FitCircleToCurve &fcd, CS_ArcSeg *paseg, CS_POINTList *pntlst=0) 
{
    CS_RECT arcrect ; 
    arcrect = paseg->BoundingRect() ; 

    CS_IRECList irl ; 
    CS_CIRCLE testcir(*paseg) ;

    fcd.nisects = 0 ; 
    fcd.ntangent = 0 ; 
    fcd.tanerr = 0 ; 
    fcd.bFoundContainedSegment = 0 ;

    int i = 0 ; 
    CS_SegPtr pseg = fcd.pcrv->pStart ; 
    while (pseg)
    {
        if (SegInsideCirc(paseg, pseg))
        {
            fcd.bFoundContainedSegment = 1 ; 
            fcd.pcontainedseg = pseg ; 
            return -1 ; // don't have to look any further since this circle cannot fit 
        }
        else if (arcrect.Overlaps(fcd.crvrect[i++]))
            pseg->Intersect2D(paseg, &irl) ; 
        
        pseg = pseg->next ; 
    }
    

    if (pntlst)
        pntlst->clear() ; 

    CS_IRECListItr iri ; 
    iri = irl.begin() ;
    while(iri != irl.end())
    {
        if (pntlst)
            pntlst->push_back(iri->pir->ipnt[0]) ; 

        if (iri->pir->statinfo & CS_IREC::TANGENT)
        {   // This is a tangent intersection
            if (iri->pir->ipnt[0] != fcd.upnt)
            {
                fcd.bLastWasTangent = 1 ; 
                fcd.lasttanipnt = iri->pir->ipnt[0] ; 
                fcd.lasttanirad = paseg->rad ; 
                fcd.ntangent++ ; 
                iri++ ; 
            }
            else 
            {   // This is the base tangent point, so delete this record
                // effectively ignoring it in the processing
                CS_IRECListItr idel = iri ; 
                iri++ ; 
                irl.erase(idel) ; 
            }
        }
        else if (iri->pir->ipnt[0] == fcd.upnt)
        {   // Should be a tangent intersection but ignore it
            fcd.tanerr++ ; 
            iri++ ; 
        }
        else
        {
            fcd.bLastWasTangent = 0 ; 
            fcd.lastipnt = iri->pir->ipnt[0] ; 
            fcd.lastirad = paseg->rad ; 
            fcd.nisects++ ; 
            iri++ ; 
        }
    }

    return (int)irl.size() ; 
}


//  Returns 0=no intersect at radius r
// \todo Optimize the intersection routines to take advantage of circle instead 
// of converting to a 360 degree arc
/* 
    Start at the largest radius then move backwards in halving steps until 
    no intersections are found. If there is no intersections at maxrad then
    when backing off we must first get multiple intersections at some point, 
    which will define the upper limit of the search range. Then keep backing 
    off by half until there are no intersections. The search then becomes 
    an iterative half step walk between the very last multi intersect found
    and the no intersection radius. 
 */

// NOTE  NOT USED, NOT IMPLEMENTED, NOT COMPLETED, AND NOT TESTED
static int FindFitCircle(CS_FitCircleToCurve &fcd, double &maxrad)
{
    CS_ArcSeg aseg ; 

    bool foundMax = false ; 
    bool foundMin = false ;
    double rmax, rmin ; 
    double r = maxrad ; 
    double lastr = r ; 
    while (fcd.iters < fcd.maxiters && !fcd.done)
    {
        aseg.ctr = fcd.upnt + (fcd.vctr * r) ; 
        aseg.sa = 0 ; 
        aseg.swp = RADIAN360 ; 
        aseg.rad = r ;

        CS_IRECList irl ; 
        fcd.nisects = 0 ; 
        fcd.ntangent = 0 ; 
        fcd.tanerr = 0 ;
        fcd.bLastWasTangent = 0 ; 

        // Intersect the circle (full 360deg arc) with the curve
        IntersectCrvAndCirc(fcd, &aseg) ;

        // The first thing needed is to find the max starting point
        if (!foundMax)
        {
            if (fcd.nisects > 0)
            {
                foundMax = true ; 
                rmax = r ; 
            }
            else
            {
            }
        }
        else if (!foundMin)
        {   // Already have the max point, want to reduce to the min point
            if (fcd.nisects == 0)
            {
                if (fcd.ntangent == 1)
                {   // Then we're done
                }
            }
            else 
            {
                foundMin = true ; 
                rmin = r ; 
            }
        }
        else
        {   // Have found the min point so currently in the binary
            // search refine mode. In this mode the max and min values
            // are moved closer together until the radius no longer 
            // changes or the max number of iterations is reached
        }

        fcd.iters++ ;
        if (tcomp_EQ(lastr, r)) 
            break ; 
        lastr = r ; 
    }

    return 0 ; 
}

/*
// TO DO separate the CS_FitCircleToCurve data so that it can be initialized before
// calling this function and passed in as a parameter.  
int CS_FitCircle(CS_Curve &crv, double &u, CS_CIRCLE &retcirc, int side)
{
    int retcode = 0 ; 
    crv.Complete() ; 

    // Filter out the case when the input curve is a circle
    if (crv.nodecnt == 1 && crv.pStart->SegmentType() == CS_Segment::ARC_TYPE && 
        crv.Closed())
    {
        int direction = CW ;
        if (crv.Area() > 0)
            direction = CCW ;
        if ((side == CS_LEFTSIDE && direction == CCW) ||
            (side == CS_RIGHTSIDE && direction == CW))
        {   // The curve is a single circle
            CS_ArcSeg *pas = (CS_ArcSeg *)crv.pStart ;
            retcirc.ctr = pas->ctr ;
            retcirc.rad = pas->rad ;
            retcode = CS_FOUND ; 
        }
        else
        {
            retcode = CS_INFINITE ; 
        }
    }
    else
    {
        CS_FitCircleToCurve fcd ;

        crv.SetBoundingRect() ; 

        fcd.crvrect = new CS_RECT[crv.nodecnt+1] ;
        fcd.pcrv = &crv ;
        fcd.done = 0 ;
        fcd.iters = 0 ;
        fcd.maxiters = 40 ;
        fcd.upnt = crv.UPoint(u) ;
        fcd.vtan = crv.UTangent(u) ; // get unit tangent vector
        fcd.vctr  ;

        fcd.u = u ;

        CS_POINT botleft(crv.bndrect.l, crv.bndrect.b, 0) ; 
        CS_POINT topright(crv.bndrect.r, crv.bndrect.t, 0) ; 

        fcd.maxrad = CS_Distance(botleft, topright) / 2.0 ; 
        fcd.finalrad = 0 ; // final resultant radius
    
        fcd.bLastWasTangent = 0 ; 

        fcd.tanerr = 0 ; // number of intersects at upnt that weren't reported as tangent
        fcd.nisects = 0 ; // number of non-tangent intersects
        fcd.ntangent = 0 ; // number of tangent intersects
        fcd.done = 0 ; 

        fcd.lastirad = 0 ; 
        fcd.lasttanirad = 0 ; 

        if (side == CS_LEFTSIDE)
            fcd.vctr = fcd.vtan.LeftPerp() ;
        else
            fcd.vctr = fcd.vtan.RightPerp() ;

        // Find the first intersection with the shape when projecting a ray 
        // in the direction of the vctr vector
        CS_LineSeg ls ;
        ls.uo = 0 ;
        ls.pParent = 0 ;
        ls.sp = fcd.upnt ;
        ls.ep = ls.sp + (fcd.vctr * fcd.maxrad * 3.0) ;

        CS_IRECList lnirl ;
        CS_IRECListItr iri ;
        fcd.pcrv->Intersect2D(&ls, &lnirl) ;

        //////////////////////////////////////
        // Filter out any upnt intersections
        CS_SortIntersectSetByUValue(lnirl, 1) ;

        iri = lnirl.begin(); 
        while (iri != lnirl.end())
        {
            CS_IREC *pir = iri->pir ; 
            if (tcomp_EQZ(pir->US0()))
            {
                CS_IRECListItr idel ; 
                idel = iri ; 
                iri++ ; 
                lnirl.erase(idel) ; 
            }
            else
            {
                iri++ ;
            }
        }

        ///////////////////
        // Begin processing
        ///////////////////

        double r, rmax, rmin ; 

        int i = 0 ;
        CS_SegPtr pseg = crv.pStart ;
        while (pseg)
        {
            fcd.crvrect[i] = pseg->BoundingRect() ;
            fcd.crvrect[i].Expand(0.01) ; 
            i++ ; 
            pseg = pseg->next ;
        }

        CS_ArcSeg aseg ;
        int retval ;

        if (lnirl.size() == 0)
        {   // Then there was no intersection which means the circle
            // could end up being infinite or zero. Start at max rad
            // and work backwards until the first 0 intersect is found.
            // If the initial

            rmin = 0 ; 
            rmax = ls.ArcLength() * 2.0 ;
            r = rmax / 2.0 ; 

            bool foundisect = false ; // set true when first intersection is found
            bool foundopen  = false ; // set true when first no intersections are found
            do {
                aseg.ctr = fcd.upnt + (fcd.vctr * r) ;
                aseg.rad = r ;
                aseg.sa = 0.0 ;
                aseg.swp = RADIAN360 ;

                retval = IntersectCrvAndCirc(fcd, &aseg) ;

                if (fcd.nisects == 0)
                {
                    if (fcd.ntangent > 0)
                    {   // This is our master override stop condition
                        retcirc.rad = r ; 
                        retcirc.ctr = fcd.upnt + (fcd.vctr * r) ; 
                        retcode = CS_FOUND ; 
                        break ; 
                    }

                    foundopen = true ; 
                    if (!foundisect)
                    {
                        if (tcomp_EQZ(r))
                        {
                            retcode = CS_INFINITE ; 
                            break ; // no large intersecting circle found
                        }

                        // Else shrink the test circle
                        rmax = r ; 
                    }
                    else
                    {   // Increase size of test circle
                        rmin = r ; 
                    }
                }
                else
                {
                    foundisect = true ;
                    if (!foundopen)
                    {   // Then keep reducing
                        rmax = r ; 
                    }
                    else
                    {   // increase in size
                        rmin = r ; 
                    }
                }

                r = (rmax + rmin) / 2.0 ; 
                fcd.iters++ ; 
            } while (fcd.iters < fcd.maxiters && tcomp_NEZ(r)) ;

            if (!(retcode & CS_FOUND) && fcd.iters >= fcd.maxiters && foundisect)
            {
                retcirc.rad = r ; 
                retcirc.ctr = fcd.upnt + (fcd.vctr * r) ; 
                retcode = CS_OUTOFTOL | CS_FOUND ; 
            }
        }
        else
        {
            iri = lnirl.begin() ; 
            CS_IREC *pir = iri->pir ; 

            rmin = 0.0 ; 
            rmax = CS_Distance(fcd.upnt, pir->ipnt[0]) / 2.0 ; 

            aseg.ctr = fcd.upnt + (fcd.vctr * rmax) ;
            aseg.rad = rmax ;
            aseg.sa = 0.0 ;
            aseg.swp = RADIAN360 ;

            retval = IntersectCrvAndCirc(fcd, &aseg) ;

            if (fcd.nisects == 0)
            {  
                if (fcd.ntangent == 0)
                {   // \todo fill this in later
                    // Must do special decreasing mode scan
                    rmin = 0.0 ; 
                    r = rmax ; 
                    retcode |= CS_NOTFOUND ; // change this later
                }
                else
                {   // Only got a tangent intersection so done
                    retcirc.rad = fcd.lasttanirad ; 
                    retcirc.ctr = fcd.upnt + (fcd.vctr * fcd.lasttanirad) ; 
                    retcode = CS_FOUND ; 
                }
            }
            else 
            {   // Normal processing

                // upnt + (vctr * radius) gives center of the circle
                crv.SetBoundingRect() ;
    
                // Want to quickly search for the first secondary tangent intersection 
                do {
                    r = (rmax + rmin) / 2.0 ; 
                    aseg.ctr = fcd.upnt + (fcd.vctr * r) ;
                    aseg.rad = r ;
                    aseg.sa = 0.0 ;
                    aseg.swp = RADIAN360 ;

                    retval = IntersectCrvAndCirc(fcd, &aseg) ;

                    if (fcd.nisects == 0 && fcd.ntangent != 0)
                    {   // Only found tangent intersections so we're done. 
                        retcirc.rad = fcd.lasttanirad ; 
                        retcirc.ctr = fcd.upnt + (fcd.vctr * fcd.lasttanirad) ; 
                        retcode = CS_FOUND ; 
                        break ; 
                    }
                    else if (fcd.nisects == 0)
                    {   // Then we want to move rmin towards rmax
                        rmin = r ; 
                    }
                    else 
                    {
                        rmax = r ; 
                    }
                    fcd.iters++ ; 
                } while (fcd.iters < fcd.maxiters) ; 

                if (!(retcode & CS_FOUND) && fcd.iters >= fcd.maxiters)
                {
                    if (tcomp_NEZ(r))
                    {
                        retcirc.rad = r ; 
                        retcirc.ctr = fcd.upnt + (fcd.vctr * r) ; 
                        retcode = CS_FOUND ; 
                    }
                }
            }
        }

        delete[] fcd.crvrect ;
    }

    return retcode ; 
}

  */



CS_FitCircleToCurve::CS_FitCircleToCurve()
{
    pcrv = 0 ; 
    crvrect = 0 ; 

    InitRun() ; 
}

CS_FitCircleToCurve::~CS_FitCircleToCurve()
{
}



void CS_FitCircleToCurve::InitSegRects(CS_Curve *pc) 
{
    pcrv = pc ; 
    pcrv->Complete(NODIR) ; 
    crvrect = new CS_RECT[pcrv->nodecnt+1] ;

    int i = 0 ;
    maxrad = 0.0 ; 

    CS_SegPtr pseg = pcrv->pStart ;

    if (pseg)
    {
        crvrect[i] = pseg->BoundingRect() ; 
        pcrv->bndrect = crvrect[i] ; // init the bounding rect for the curve
        crvrect[i].Expand(0.01) ; 
        i++ ; 
    }
    else
    {
        return ; // nothing left to do
    }

    pseg = pseg->next ; // process rest of the segments

    while (pseg)
    {
        crvrect[i] = pseg->BoundingRect() ;
        pcrv->bndrect.Union(crvrect[i]) ; 
        crvrect[i].Expand(0.01) ; 
        i++ ; 
        pseg = pseg->next ;
    }

    cbrect = pcrv->bndrect ; 
    maxrad = CS_Distance(pcrv->bndrect.BLPoint(), pcrv->bndrect.TRPoint()) / 2.0 ; 
}


void CS_FitCircleToCurve::InitRun()
{
    done = 0 ;
    iters = 0 ;
    maxiters = 40 ;
    vctr  ;

    finalrad = 0 ; // final resultant radius
    bLastWasTangent = 0 ; 

    tanerr = 0 ; // number of intersects at upnt that weren't reported as tangent
    nisects = 0 ; // number of non-tangent intersects
    ntangent = 0 ; // number of tangent intersects
    done = 0 ; 

    lastirad = 0 ; 
    lasttanirad = 0 ; 
}

void CS_FitCircleToCurve::InitRun(double ucrv, int side)
{
    InitRun() ; 

    u = ucrv ;
    upnt = pcrv->UPoint(u) ;
    vtan = pcrv->UTangent(u) ; // get unit tangent vector

    if (side == CS_LEFTSIDE)
        vctr = vtan.LeftPerp() ;
    else
        vctr = vtan.RightPerp() ;
}


void CS_FitCircleToCurve::InitRun(double ucrv, CS_VECTOR &vsearch)
{
    InitRun() ; 

    u = ucrv ;
    upnt = pcrv->UPoint(u) ;
    vtan = pcrv->UTangent(u) ; // get unit tangent vector
    
    vctr = vsearch ; 
}



int CS_FitCircleToCurve::FitCircle(double &uval,       // point on curve to fit circle
                                   CS_CIRCLE &retcirc, // the resultant circle
                                   int side,           // side to grow circle on
                                   double radtol)      // default=-1.0 means don't use
{
    int retcode = 0 ; 

    // Filter out the case when the input curve is a circle
    if (pcrv->nodecnt == 1 && pcrv->pStart->IsARC() && pcrv->Closed())
    {
        int direction = CW ;
        if (pcrv->Area() > 0)
            direction = CCW ;
        if ((side == CS_LEFTSIDE && direction == CCW) ||
            (side == CS_RIGHTSIDE && direction == CW))
        {   // The curve is a single circle
            CS_ArcSeg *pas = (CS_ArcSeg *)pcrv->pStart ;
            retcirc.ctr = pas->ctr ;
            retcirc.rad = pas->rad ;
            retcode = CS_FOUND ; 
        }
        else
        {
            retcode = CS_INFINITE ; 
        }
    }
    else
    {
        InitRun(uval, side) ; 
        retcode = DoFit(uval, retcirc, radtol) ;  
    }

    return retcode ; 
}


int CS_FitCircleToCurve::FitLimitCircle(double &uval, 
                                        double limitRad, 
                                        CS_CIRCLE &retcirc, 
                                        int side, 
                                        double radtol)
{
    int retcode = 0 ; 

    // Filter out the case when the input curve is a circle
    if (pcrv->nodecnt == 1 && pcrv->pStart->IsARC() && pcrv->Closed())
    {
        int direction = CW ;
        if (pcrv->Area() > 0)
            direction = CCW ;
        if ((side == CS_LEFTSIDE && direction == CCW) ||
            (side == CS_RIGHTSIDE && direction == CW))
        {   // The curve is a single circle
            CS_ArcSeg *pas = (CS_ArcSeg *)pcrv->pStart ;
            retcirc.ctr = pas->ctr ;
            retcirc.rad = pas->rad ;
            retcode = CS_FOUND ; 

            if (retcirc.rad > limitRad)
            {   // Then shrink it down to the limit
                CS_POINT crvpnt = pcrv->UPoint(uval) ;
                CS_VECTOR vcc(crvpnt, retcirc.ctr) ; 
                vcc = vcc.Unit() ; 
                retcirc.ctr = crvpnt + vcc * limitRad ; 
                retcirc.rad = limitRad ; 
                retcode |= CS_FOUNDLIMIT ; 
            }
        }
        else
        {   // Circle to be fit is outside the arc. 
            CS_ArcSeg *pas = (CS_ArcSeg *)pcrv->pStart ;
            CS_POINT crvpnt = pcrv->UPoint(uval) ;
            CS_VECTOR vcc(pas->ctr, crvpnt) ; 
            vcc = vcc.Unit() ; 
            retcirc.ctr = crvpnt + vcc * limitRad ; 
            retcirc.rad = limitRad ; 
            retcode = CS_FOUNDLIMIT | CS_FOUND  ; 
        }
    }
    else
    {
        InitRun(uval, side) ; 
        retcode = DoFit(uval, retcirc, radtol, &limitRad) ;  
    }

    return retcode ; 
}


int CS_FitCircleToCurve::FitCircle(double &uval,       // point on curve to fit circle
                                   CS_VECTOR &vsearch, // direction of centerline for circle
                                   CS_CIRCLE &retcirc, // the resultant circle
                                   double radtol)      // default=-1.0 means don't use
{
    int retcode = 0 ; 

    // Filter out the case when the input curve is a circle
    if (pcrv->nodecnt == 1 && pcrv->pStart->IsARC() && pcrv->Closed())
    {
        int direction = CW ;
        if (pcrv->Area() > 0)
            direction = CCW ;
        // The curve is a single circle
        CS_ArcSeg *pas = (CS_ArcSeg *)pcrv->pStart ;
        CS_POINT p = pas->UPoint(uval) ; 
        CS_VECTOR vcp(pas->ctr, p) ; 
        vcp.z = 0 ; 
        vctr = vsearch ; 
        vctr.z = 0 ; 
        double dp = CS_DotProduct(vcp, vctr) ; 
        if (tcomp_EQZ(ZCross(vcp, vctr)))
        {
            if (dp > 0)
            {   // Searching outside the circle 
                retcode = CS_INFINITE ; 
            }
            else
            {   // Searching inside circle so the result simply matches
                // the circle that defines the curve. 
                retcirc.ctr = pas->ctr ;
                retcirc.rad = pas->rad ;
                retcode = CS_FOUND ; 
            }
        }
        else
        {
            if (dp > 0)
            {   // Searching outside the circle 
                retcode = CS_INFINITE ; 
            }
            else
            {   // Searching inside circle but the result is zero 
                retcode = CS_NOTFOUND ; 
            }
        }
        
        return retcode ; 
    }
    else
    {
        InitRun(uval, vsearch) ; 
        retcode = DoFit(uval, retcirc, radtol) ;
    }

    return retcode ; 
}


int CS_FitCircleToCurve::DoFit(double &uval,       // point on curve to fit circle
                               CS_CIRCLE &retcirc, // the resultant circle
                               double radtol, 
                               double *pLimitRad)
{
    int retcode = 0 ; 

    // Find the first intersection with the shape when projecting a ray 
    // in the direction of the vctr vector
    CS_LineSeg ls ;
    ls.uo = 0 ;
    ls.pParent = 0 ;
    ls.sp = upnt ;
    ls.ep = ls.sp + (vctr * maxrad * 3.0) ;

    pntlst.clear() ; 

    CS_IRECList lnirl ;
    CS_IRECListItr iri ;
    pcrv->Intersect2D(&ls, &lnirl) ;

    //////////////////////////////////////
    // Filter out any upnt intersections
    CS_SortIntersectSetByUValue(lnirl, 1) ;

    iri = lnirl.begin(); 
    while (iri != lnirl.end())
    {
        CS_IREC *pir = iri->pir ; 
        pntlst.push_back(pir->ipnt[0]) ; 
        // if (tcomp_EQ(pir->US0(), uval))
        if (tcomp_EQ(pir->UP0(), uval))
        {
            CS_IRECListItr idel ; 
            idel = iri ; 
            iri++ ; 
            lnirl.erase(idel) ; 
        }
        else
        {
            iri++ ;
        }
    }

    ///////////////////
    // Begin processing
    ///////////////////

    double r, rmax, rmin ; 

    int i = pcrv->nodecnt ;
    CS_ArcSeg aseg ;
    int retval ;

    if (lnirl.size() == 0)
    {   // Then there was no intersection which means the circle
        // could end up being infinite or zero. Start at max rad
        // and work backwards until the first 0 intersect is found.
        // If the initial

        rmin = 0 ; 
        rmax = ls.ArcLength() * 2.0 ;
        r = rmax / 2.0 ; 

        bool foundisect = false ; // set true when first intersection is found
        bool foundopen  = false ; // set true when first no intersections are found
        if (radtol > 0)
        {
            do {
                aseg.ctr = upnt + (vctr * r) ;
                aseg.rad = r ;
                aseg.sa = 0.0 ;
                aseg.swp = RADIAN360 ;

                retval = IntersectCrvAndCirc(*this, &aseg, &pntlst) ;

                if (nisects == 0)
                {
                    if (ntangent > 0)
                    {   // This is our master override stop condition
                        retcirc.rad = r ; 
                        retcirc.ctr = upnt + (vctr * r) ; 
                        retcode = CS_FOUND ; 
                        break ; 
                    }

                    foundopen = true ; 
                    if (!foundisect)
                    {
                        if (tcomp_EQZ(r))
                        {
                            retcode = CS_INFINITE ; 
                            break ; // no large intersecting circle found
                        }

                        // Else shrink the test circle
                        rmax = r ; 
                    }
                    else
                    {   // Increase size of test circle
                        rmin = r ; 
                    }
                }
                else
                {
                    foundisect = true ;
                    if (!foundopen)
                    {   // Then keep reducing
                        rmax = r ; 
                    }
                    else
                    {   // increase in size
                        rmin = r ; 
                    }
                }

                r = (rmax + rmin) / 2.0 ; 
                iters++ ; 
            } while (iters < maxiters && tcomp_NEZ(r) && tcomp_NEQ(rmin, rmax, radtol)) ;
        }
        else
        {
            do {
                aseg.ctr = upnt + (vctr * r) ;
                aseg.rad = r ;
                aseg.sa = 0.0 ;
                aseg.swp = RADIAN360 ;

                retval = IntersectCrvAndCirc(*this, &aseg, &pntlst) ;

                if (nisects == 0)
                {
                    if (ntangent > 0)
                    {   // This is our master override stop condition
                        retcirc.rad = r ; 
                        retcirc.ctr = upnt + (vctr * r) ; 
                        retcode = CS_FOUND ; 
                        break ; 
                    }

                    foundopen = true ; 
                    if (!foundisect)
                    {
                        if (tcomp_EQZ(r))
                        {
                            retcode = CS_INFINITE ; 
                            break ; // no large intersecting circle found
                        }

                        // Else shrink the test circle
                        rmax = r ; 
                    }
                    else
                    {   // Increase size of test circle
                        rmin = r ; 
                    }
                }
                else
                {
                    foundisect = true ;
                    if (!foundopen)
                    {   // Then keep reducing
                        rmax = r ; 
                    }
                    else
                    {   // increase in size
                        rmin = r ; 
                    }
                }

                r = (rmax + rmin) / 2.0 ; 
                iters++ ; 
            } while (iters < maxiters && tcomp_NEZ(r)) ;
        }

        if (!(retcode & CS_FOUND) && iters >= maxiters && foundisect)
        {
            retcirc.rad = r ; 
            retcirc.ctr = upnt + (vctr * r) ; 
            retcode = CS_OUTOFTOL | CS_FOUND | CS_MAXITERS ; 
        }
    }
    else
    {
        iri = lnirl.begin() ; 
        CS_IREC *pir = iri->pir ; 

        rmin = 0.0 ; 
        rmax = CS_Distance(upnt, pir->ipnt[0]) / 2.0 ; 

        aseg.ctr = upnt + (vctr * rmax) ;
        aseg.rad = rmax ;
        aseg.sa = 0.0 ;
        aseg.swp = RADIAN360 ;

        retval = IntersectCrvAndCirc(*this, &aseg, &pntlst) ;

        // Remember that nisects is the number of non-tangent intersections
        // and ntangent is the number of tangent only style intersections. 
        if (!bFoundContainedSegment && nisects == 0)
        {  
            if (ntangent == 0)
            {   // \todo look into this logic and verify validity
                // Might have to do special decreasing mode scan

                // For now, just assume that the far side of the circle
                // was just barely touching the other side of the shape
                // and the limiting radius prevented the circle from 
                // detecting an intersection with the other side. Thus
                // the current point is probably valid

                // rmin = 0.0 ; 
                // r = rmax ; 
                // retcode |= CS_NOTFOUND ; // change this later

                retcirc.rad = rmax ; 
                retcirc.ctr = upnt + (vctr * rmax) ; 
                retcode = CS_FOUND ; 
            }
            else  
            {   // Only got a tangent intersection so done
                retcirc.rad = lasttanirad ; 
                retcirc.ctr = upnt + (vctr * lasttanirad) ; 
                retcode = CS_FOUND ; 
            }
        }
        else  
        {   // Normal processing
            // upnt + (vctr * radius) gives center of the circle
            // Want to quickly search for the first secondary tangent intersection 

            if (bFoundContainedSegment)
            {   // Then have to drop rmax to the nearest point on the segment
                // Want the closest point on the segment to upnt
                CS_POINT npnt ; 
                double un ; 
                pcontainedseg->PointOnSegment(upnt, &un, &npnt) ; 

                if (upnt != npnt)
                    rmax = CS_Distance2D(upnt, npnt) ; 
            }

            do {
                r = (rmax + rmin) / 2.0 ; 
                aseg.ctr = upnt + (vctr * r) ;
                aseg.rad = r ;
                aseg.sa = 0.0 ;
                aseg.swp = RADIAN360 ;

                retval = IntersectCrvAndCirc(*this, &aseg, &pntlst) ;

                if (bFoundContainedSegment)
                {
                    CS_POINT npnt ; 
                    double un ; 
                    pcontainedseg->PointOnSegment(upnt, &un, &npnt) ; 

                    if (upnt != npnt)
                    {
                        double rtest = CS_Distance2D(upnt, npnt) ; 
                        if (rmax > rtest)
                            rmax = rtest ; 
                        else
                            rmax = r ; // divide by 2
                    }
                }
                else if (nisects == 0 && ntangent != 0)
                {   // Only found tangent intersections so we're done. 
                    retcirc.rad = lasttanirad ; 
                    retcirc.ctr = upnt + (vctr * lasttanirad) ; 
                    retcode = CS_FOUND ; 
                    break ; 
                }
                else if (nisects == 0)
                {   // Then we want to move rmin towards rmax
                    rmin = r ; 
                }
                else 
                {
                    rmax = r ; 
                }
                iters++ ; 
            } while (iters < maxiters) ; 

            if (!(retcode & CS_FOUND) && iters >= maxiters)
            {
                if (tcomp_NEZ(r))
                {
                    retcirc.rad = r ; 
                    retcirc.ctr = upnt + (vctr * r) ; 
                    retcode = CS_FOUND | CS_MAXITERS; 
                }
                else
                {
                    retcode = CS_MAXITERS ; 
                }
            }
        }
    }

    // TODO - optimize to reduce wasted testing 
    if (pLimitRad && (retcode & CS_FOUND || retcode & CS_INFINITE))
    {
        if (retcirc.rad > *pLimitRad)
        {
            retcirc.ctr = upnt + vctr * (*pLimitRad) ; 
            retcirc.rad = *pLimitRad ; 
            retcode |= CS_FOUNDLIMIT ; 
        }
    }

    return retcode ; 
}





int CS_FitCircleToCurve::FitCircle(CS_POINT &fitpnt,   // point to fit around
                                   double &retrad,     // the resultant circle radius
                                   double radtol)      // default=-1.0 means don't use
{
    int retcode = 0 ; 

    retrad = 0.0 ; 

    // Filter out the case when the input curve is a circle
    if (pcrv->nodecnt == 1 && pcrv->pStart->IsARC() && pcrv->Closed())
    {
        CS_ArcSeg *pas = (CS_ArcSeg *)pcrv->pStart ;
        if (pas->ctr == fitpnt)
        {
            retrad = pas->rad ; 
            return CS_FOUND ; 
        }
    }

    // Line segment to work out initial starting distance

    double r, rmax, rmin ; 
    if (!cbrect.Inside(fitpnt))
    {
        rmax = CS_Distance(cbrect.BRPoint(), cbrect.TLPoint()) ; 
        rmin = 0.0 ; 
    }
    else
    {
        double diag = CS_Distance(cbrect.BRPoint(), cbrect.TLPoint()) ; 
        double dctr = CS_Distance(fitpnt, cbrect.Center()) ; 
        rmax = dctr + diag ; 
        rmin = dctr - diag ; 
        if (rmin < 0.0)
            rmin = 0.0 ; 
    }

    CS_LineSeg ls ;
    ls.uo = 0 ;
    ls.pParent = 0 ;
    ls.sp = fitpnt ;

    CS_IRECList lnirl ;
    CS_IRECListItr iri ;

    CS_VECTOR vln(fitpnt, pcrv->StartPoint()) ; 
    ls.ep = fitpnt + vln * (rmax * 2.0) ; 
    pcrv->Intersect2D(&ls, &lnirl) ;

    //////////////////////////////////////
    // Filter out any upnt intersections
    CS_SortIntersectSetByUValue(lnirl, 1) ;

    // Re-adjust the rmax and min values
    if (lnirl.size() == 0)
    {   // Then failed to even find the startpoint intersection which 
        // should never happen. Traps this condition though
        rmax = CS_Distance(fitpnt, pcrv->StartPoint()) ; 
        if (rmin > rmax) 
        {   // Then return rmax as the result
            retrad = rmax ; 
            return 0 ; 
        }
        
        // assert(false) ; // want to enable assert during debugging. 
    }
    else
    {
        iri = lnirl.begin() ; 
        CS_IREC *pir = iri->pir ; 
        rmax = CS_Distance(fitpnt, pir->ipnt[0]) ; 
        if (rmin > rmax) 
        {   // Then return rmax as the result
            retrad = rmax ; 
            return 0 ; 
        }
    }

    ///////////////////
    // Begin processing
    ///////////////////

    // Want to search from rmax and back off down to rmin since we definitely 
    // have an intersection at rmax (since there will always be at least one
    
    InitRun() ; 

    CS_ArcSeg aseg ; 
    int retval = 0 ;

    // Normal processing
    // upnt + (vctr * radius) gives center of the circle
    // Want to quickly search for the first secondary tangent intersection 
    do {
        r = (rmax + rmin) / 2.0 ; 
        aseg.ctr = fitpnt + (vctr * r) ;
        aseg.rad = r ;
        aseg.sa = 0.0 ;
        aseg.swp = RADIAN360 ;

        retval = IntersectCrvAndCirc(*this, &aseg, &pntlst) ;

        if (bFoundContainedSegment)
        {
            CS_POINT npnt ; 
            double un ; 
            pcontainedseg->PointOnSegment(fitpnt, &un, &npnt) ; 

            if (fitpnt != npnt)
            {
                double rtest = CS_Distance2D(fitpnt, npnt) ; 
                if (rmax > rtest)
                    rmax = rtest ; 
                else
                    rmax = r ; // divide by 2
            }
        }
        else if (nisects == 0 && ntangent != 0)
        {   // Only found tangent intersections so we're done. 
            retrad = lasttanirad ; 
            retcode = CS_FOUND ; 
            break ; 
        }
        else if (nisects == 0)
        {   // Then we want to move rmin towards rmax
            rmin = r ; 
        }
        else 
        {   // move rmax towards rmin
            rmax = r ; 
        }
        iters++ ; 
    } while (iters < maxiters) ; 

    if (!(retcode & CS_FOUND) && iters >= maxiters)
    {
        if (tcomp_NEZ(r))
        {
            retrad = r ; 
            retcode = CS_FOUND | CS_MAXITERS ; 
        }
    }

    return retcode ; 
}




int CS_FitCircle(CS_Curve &crv, double &u, CS_CIRCLE &retcirc, int side)
{
    int retcode = 0 ; 
    crv.Complete(NODIR) ; 

    // Filter out the case when the input curve is a circle
    if (crv.nodecnt == 1 && crv.pStart->SegmentType() == CS_Segment::ARC_TYPE && 
        crv.Closed())
    {
        int direction = CW ;
        if (crv.Area() > 0)
            direction = CCW ;
        if ((side == CS_LEFTSIDE && direction == CCW) ||
            (side == CS_RIGHTSIDE && direction == CW))
        {   // The curve is a single circle
            CS_ArcSeg *pas = (CS_ArcSeg *)crv.pStart ;
            retcirc.ctr = pas->ctr ;
            retcirc.rad = pas->rad ;
            retcode = CS_FOUND ; 
        }
        else
        {
            retcode = CS_INFINITE ; 
        }
    }
    else
    {
        CS_FitCircleToCurve fcd ;

        fcd.InitSegRects(&crv) ; 
        retcode = fcd.FitCircle(u, retcirc, side) ; 
    }

    return retcode ; 
}


int CS_FitCircle(CS_Curve &crv, CS_POINT &pnt, double &retrad)
{
    if (crv.nodecnt == 0 || tcomp_EQZ(crv.ArcLength()))
        return 0x0001 ; // error, nothing to do

    int errcode = 0 ; 

    crv.SetBoundingRect() ; 

    CS_POINT maxpnt ; 
    double rmin, rmax, dist ; 

    rmin = 0.0 ; 
    rmax = 0.0 ; 
    
    if ((dist = CS_Distance(pnt, crv.bndrect.TLPoint())) > rmax)
    {
        rmax = dist ; 
        maxpnt = crv.bndrect.TLPoint() ; 
    }
    
    if ((dist = CS_Distance(pnt, crv.bndrect.TRPoint())) > rmax)
    {
        rmax = dist ; 
        maxpnt = crv.bndrect.TRPoint() ; 
    }
    
    if ((dist = CS_Distance(pnt, crv.bndrect.BLPoint())) > rmax)
    {
        rmax = dist ; 
        maxpnt = crv.bndrect.BLPoint() ; 
    }

    if ((dist = CS_Distance(pnt, crv.bndrect.BRPoint())) > rmax)
    {
        rmax = dist ; 
        maxpnt = crv.bndrect.BRPoint() ; 
    }


    // TO DO - complete the code here

    return errcode ; 
}

int CS_FitMaxCircleAlongCurve(CS_FitCircleToCurve &fc, double ua, double ub, CS_CIRCLE &retcirc, int side) 
{
    //  Sample code to simple search along a side of a shape over a certain region

    // Define the limits of the search
    // Take 50 steps to find the largest circle
    double ustep = fc.pcrv->ULength(ua, ub) / 10.0 ; 

    // ua and ub are the search region limits
    int i ; 
    double u, umax ; 
    CS_CIRCLE c, cmax ; 

    umax = -1.0 ; 
    cmax.rad = 0 ; 

    u = ua ; 
    for (i=0; i < 10; i++, u += ustep)
    {
        u = fc.pcrv->UNorm(u) ; 
        fc.FitCircle(u, c, side) ; 
        if (c.rad > cmax.rad)
        {
            umax = u ;
            cmax = c ; 
        }
    }

    // Now refine things around the max circle
    int nsteps = 25 ; 
    ua = fc.pcrv->UNorm(umax - ustep * 1.1) ; 
    ub = fc.pcrv->UNorm(umax + ustep * 1.1) ; 
    ustep = fc.pcrv->ULength(ua, ub) / nsteps ; 

    u = ua ; 
    for (i=0; i < nsteps; i++, u += ustep)
    {
        u = fc.pcrv->UNorm(u) ; 
        fc.FitCircle(u, c, side) ; 
        if (c.rad > cmax.rad)
        {
            umax = u ;
            cmax = c ; 
        }
    }

    
    // Close enough at this point since we should be 0.009mm within the location 
    // of where the largest circle would fit inside the curve
    retcirc = cmax ; 

    return 0 ; 
}
//! Search around the shape to fit circle
int CS_FitMaxCircle(CS_Curve &crv, CS_POINT &pnt, CS_CIRCLE &retcirc, double *eps) 
{
    crv.SetBoundingRect() ; 
    double maxrad = CS_Distance(crv.bndrect.TLPoint(), crv.bndrect.BRPoint()) ; 

    // Start with the closest point on the shape
    int retcode = 0 ; 
    double u ;
    CS_POINT p ;
    CS_CrvPnt cp ;
    crv.PointOnCurve(pnt, &u, &p, &cp.s, &cp.u) ;

    CS_VECTOR vsearch ; 
    CS_VECTOR vf, vb ; 

    vf = crv.TanVectorForwards(cp.s, cp.u) ; 
    vb = crv.TanVectorBackwards(cp.s, cp.u) ; 
    vb.Reverse() ; 

    double sa = vf.AngleXY() ; 
    double ea = vb.AngleXY() ; 

    // vc defines the line direction that the initial center of the center
    // will fall on. 
    CS_VECTOR vc(p, pnt) ;

    // ua and ub are the search region limits
    double a, amax ; 
    CS_CIRCLE c, cmax ; 

    amax = sa ; 
    cmax.rad = 0 ; 

    CS_FitCircleToCurve fc  ; 
    fc.InitSegRects(&crv) ;
    for (a = sa ; tcomp_NEQ(a, ea, DEGREEStoRADIANS * 2.5); a = mod2PI(a + DEGREEStoRADIANS * 1.0))
    {
        vsearch.x = 1 ; 
        vsearch.y = 0 ; 
        vsearch.z = 0 ; 
        vsearch.Rotate(a) ; 

        fc.FitCircle(u, vsearch, c) ; 
        if (c.rad > cmax.rad)
        {
            amax = a ;
            cmax = c ; 
        }
    }

    // Now search around the contact points +/- 1mm in each direction
    CS_POINTList pntlst ; 
    CS_POINTListItr pli ; 
    for (pli = fc.pntlst.begin(); pli != fc.pntlst.end(); pli++)
        pntlst.push_back(*pli) ; 

    // Now refine things around the max angle
    sa = mod2PI(amax - DEGREEStoRADIANS * 1.0) ; 
    ea = mod2PI(amax + DEGREEStoRADIANS * 1.0) ; 
    for (a = sa ; tcomp_NEQ(a, ea, DEGREEStoRADIANS * 0.2); a = mod2PI(a + DEGREEStoRADIANS * 0.1))
    {
        vsearch.x = 1 ; 
        vsearch.y = 0 ; 
        vsearch.z = 0 ; 
        vsearch.Rotate(a) ; 

        fc.FitCircle(u, vsearch, c) ; 
        if (c.rad > cmax.rad)
        {
            amax = a ;
            cmax = c ; 
        }
    }

    // Expand the circle and intersect it with the shape

    CS_IRECList irlist ; 
    CS_IRECListItr iri ; 

    CS_ArcSeg aseg(cmax.ctr, 0, RADIAN360, cmax.rad + 0.1) ; 
    crv.Intersect2D(&aseg, &irlist) ; 

    // Now refine things further by searching around the contact points. 
    double du, ua, ub ; 
    for (iri = irlist.begin(); iri != irlist.end(); iri++)
    {
        u = iri->pir->UP0() ; 
        if (eps)
            du = crv.ArcLengthToDeltaU(*eps) ; 
        else
            du = 0.01 ; 

        ua = crv.UNorm(u - du) ; 
        ub = crv.UNorm(u + du) ; 
        CS_FitMaxCircleAlongCurve(fc, ua, ub, c, CS_LEFTSIDE) ; 
        if (c.rad > cmax.rad)
            cmax = c ; 
    }


    
    retcirc = cmax ; 

    return retcode ; 
}


int CS_FindMaxCircleInShape(CS_Curve &shp, double ustep, CS_CIRCLE &retcirc)
{
    int retcode = 0 ; 
    if (!shp.Closed())
        return CS_NOTCLOSED ; 

    // Filter out the case when the input curve is a circle
    if (shp.nodecnt == 1 && shp.pStart->SegmentType() == CS_Segment::ARC_TYPE)
    {
        CS_ArcSeg *pas = (CS_ArcSeg *)shp.pStart ;
        if (pas->swp < 0)
        {
            retcode = CS_INFINITE ; 
        }
        else
        {
            retcirc.ctr = pas->ctr ;
            retcirc.rad = pas->rad ;
            retcode = CS_FOUND ; 
        }
    }
    else
    {

        CS_FitCircleToCurve fcd ;

        fcd.InitSegRects(&shp) ; 
        
        double u ;
        CS_CIRCLE circmax ; 
        for (u=0.0 ; u < 1.0 ; u += ustep) 
        {
            CS_CIRCLE circ ; 
            int ret = fcd.FitCircle(u, circ, CS_LEFTSIDE) ; 
            if (ret & CS_FOUND && !(ret & CS_MAXITERS))
            {
                if (circmax.rad < circ.rad)
                    circmax = circ ; 
            }
        }

        if (tcomp_NEZ(circmax.rad))
        {
            retcode = CS_FOUND ;
            retcirc = circmax ; 
        }
    }

    return retcode ; 
}

