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
// varofsNM.cpp - do a variable offset with a brute force numerical method
//              style algorithm. No optimization occurs here and the 
//              result is a raw offset which must be cleaned up further
//              for a proper offset curve. 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"

#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#include "cs_offset.h"
#include "cs_offsoval.h"

#include "cs_chain.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)     a ; 
#else
#define CS_DEBUG(a)
#endif

#define DEBUGVAR(a)     a ; 

#ifndef min
#define min(a,b)   (a < b) ? (a) : (b)
#endif 

#ifndef max
#define max(a,b)   (a > b) ? (a) : (b)
#endif 

static double deltau(double dofs[][2], int n, double u, int closed)
{
    // \todo optimize this using a binary search tye technique to minimize 
    // the number of comparisons.
    int i = 0 ; 
    while (i < n)
    {   // Find which section this u falls into
        if (u <= dofs[i][0])
            break ; 
        i++ ; 
    }

    double ul ; // u length of the section
    double ur ; // u relative to the [i-1,i] section
    double k0 ; // offset value at start of section
    double k1 ; // offset value at end of section

    if (i == 0)
    {   // Somewhere in the first section
        if (!closed)
        {   // Then the start section is flat, so simply return the
            // the flat offset value at the start of the curve
            return dofs[0][1] ;
        }
        else
        {
            ul = (1.0 - dofs[n-1][0]) + dofs[0][0] ; 
            ur = 1.0 - dofs[n-1][0] + u ; 
            k0 = dofs[n-1][1] ;
            k1 = dofs[0][1] ; 
            if (tcomp_EQZ(ul))
                return k0 ; 
            return k0 + (k1 - k0) * (ur / ul) ;
        }
    }
    else if (i >= n)
    {   // Somewhere in the last section
        if (!closed)
        {   // Then the last section is flat, so simply return the
            // the flat offset value at the end of the curve
            return dofs[n-1][1] ;
        }
        else
        {
            ul = (1.0 - dofs[n-1][0]) + dofs[0][0] ; 
            ur = u - dofs[n-1][0] ; 
            k0 = dofs[n-1][1] ;
            k1 = dofs[0][1] ; 
            if (tcomp_EQZ(ul))
                return k0 ; 
            return k0 + (k1 - k0) * (ur / ul) ;
        }
    }

    // else
    // Somewhere on an inner section
    ul = dofs[i][0] - dofs[i-1][0] ; 
    ur = u - dofs[i-1][0] ; 
    k0 = dofs[i-1][1] ;
    k1 = dofs[i][1] ; 
    if (tcomp_EQZ(ul))
        return k0 ; 
    return k0 + (k1 - k0) * (ur / ul) ;
}


//! Incorporate the point p into the arc. p should be close to one of the end 
//! points of the arc for this to work reliably. The point p must not be 
//! within the sweep of the arc otherwise the arc will end up being 
//! reduced in size (See notes Geom Algos RR.Vol-4 pg 130-131)
static int IncludeArcPoint(CS_ARC &arc, double pointangle)
{
    double alpha = arc.UAngle(0.5) ; 
    double beta =  mod2PI(alpha + RADIAN180) ; 
    double omega = (RADIAN360 - fabs(arc.swp)) / 2.0 ; 

    CS_ARC arcbsa, arcbea ; 
    if (arc.swp < 0)
    {
        arcbsa.sa = arc.sa ; 
        arcbsa.swp = omega ; 
        arcbea.sa = beta ; 
        arcbea.swp = omega ; 
    }
    else
    {
        arcbsa.sa = beta ; 
        arcbsa.swp = omega ; 
        arcbea.sa = arc.sa + arc.swp ; 
        arcbea.swp = omega ; 
    }

    if (arcbsa.AngleOnSweep(pointangle))
    {   // Then move the start angle
        if (arc.swp < 0)
            arc.swp -= arc_sweep(pointangle, arc.sa, CW) ; 
        else
            arc.swp += arc_sweep(pointangle, arc.sa, CCW) ; 

        arc.sa = pointangle ; 
    }
    else
    {   // Move the end angle 
        if (arc.swp < 0)
            arc.swp -= arc_sweep(arc.sa + arc.swp, pointangle, CW) ; 
        else
            arc.swp += arc_sweep(arc.sa + arc.swp, pointangle, CCW) ; 
    }

    return 0 ; 
}


enum {
    NOMODE   = 0, 
    ARCMODE  = 1,
    LINEMODE = 2
} ;


static inline void ProcessPoint(CS_Curve &crv, 
                                CS_CrvPnt &cp, 
                                double dofs[][2], 
                                int &ndofs, 
                                double &u, 
                                int &closed, 
                                CS_POINT pl[], 
                                CS_CrvPnt acp[],
                                int &np, 
                                int &mode, 
                                CS_LineSeg &line, 
                                CS_ArcSeg &arc, 
                                CS_Curve &rescrv)

{
    CS_POINT tp ;
    CS_VECTOR vtan, vp ; 
    double dk, ut ;

    dk = deltau(dofs, ndofs, u, closed) ; 
    // vtan = crv.UTangent(u) ; 
    vtan = cp.s->UTangent(cp.u) ; 
    vp = vtan.RightPerp() ; 
    // tp = crv.UPoint(u) + (vp * dk) ; 
    tp = cp.s->UPoint(cp.u) + (vp * dk) ; 
   
    if (mode == LINEMODE)
    {   
        if (line.PointOnLine(tp, &ut))
        {   // Then want to absorb this point into the line
            if (ut < 0.0)
            {
                acp[0] = cp ; 
                line.sp = tp ; 
            }
            else if (ut > 1.0)
            {
                acp[1] = cp ; 
                line.ep = tp ;
            }
        }
        else 
        {   // The point is not on the line so add the current line
            // segment to the curve being built and then reset for 
            // the next point
            CS_LineSeg *pls = new CS_LineSeg(line) ;
            pls->cp = acp[0] ;
            rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
            
            mode = NOMODE ;
            acp[0] = acp[1] ;
            acp[1] = cp ; 
            pl[0] = line.ep ; 
            pl[1] = tp ; 
            np = 2 ; 
        }
    }
    else if (mode == ARCMODE)
    {   // Test if the point is on the circle defined by the arc
        CS_VECTOR vctr(arc.ctr, tp) ;
        if (tcomp_EQ(vctr.Mag(), arc.rad))
        {   // Have to absorb this point into the arc, to do this want
            // to get a u coordinate for the point relative to the existing
            // arc and then adjust the start angle and sweep based on 
            // where this point falls. 
            if (!arc.PointOnArc(tp, &ut))
            {   // Then have to figure out which end to extend
                double pointang = vctr.AngleXY() ;
                IncludeArcPoint(arc, pointang) ;
                acp[1] = cp ; 
            }
        }
        else
        {   // The point defines a new arc or line so save the current
            // arc and reset for next curve segment
            CS_ArcSeg *pas = new CS_ArcSeg(arc) ;
            pas->cp = acp[0] ;
            rescrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ; 

            mode = NOMODE ;
            acp[0] = acp[1] ;
            acp[1] = cp ; 
            pl[0] = arc.EndPoint() ; 
            pl[1] = tp ; 
            np = 2 ; 
        }
    }
    else
    {   // No mode currently active so see what type of curve we 
        // are building and set the state accordingly.
        if (np < 2)
        {   // Simply add the point to the list
            if (np == 0)
                acp[0] = cp ; 
            else
                acp[1] = cp ; 
            pl[np++] = tp ; 
        }
        else
        {   // This is the third point
            // no should be 2 at this point so grab the last two points
            // plus the current point and figure out what mode to set. 
            if (CS_Collinear(pl[0], pl[1], tp))
            {   // Then create a line
                acp[1] = cp ; 
                line.sp = pl[0] ; 
                line.ep = tp ; 
                np = 2 ; 
                mode = LINEMODE ; 
            }
            else
            {
                arc.Arc3Points(pl[0], pl[1], tp) ;
                if (fabs(arc.swp) > RADIAN45)
                {
                    CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
                    pls->cp = acp[0] ;
                    rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;

                    mode = NOMODE ; 
                    acp[0] = acp[1] ; 
                    acp[1] = cp ; 
                    pl[0] = pl[1] ; 
                    pl[1] = tp ; 
                    np = 2 ; 
                }
                else
                {
                    acp[1] = cp ; 
                    np = 2 ; 
                    mode = ARCMODE ; 
                }
            }
        }
    }
}


static int compdbl(const void *a, const void *b)
{
    if (*(double *)a < *(double *)b)
        return -1 ; 
    else if (*(double *)a > *(double *)b)
        return 1 ; 
    return 0 ; 
}


int VarOfsNM(CS_Curve &crv, double dofs[][2], int ndofs, double filletrad, int segsteps, CS_Curve &rescrv)
{
    CS_Curve tprcrv ; 

    if (tcomp_NEZ(filletrad))
        crv.Fillet(filletrad) ; 
    crv.Complete() ; 

    // Process each segment of the curve separately, so that short segments
    // are processed with as much (greater) precision as long segments. 

    CS_LineSeg line ;   // temporary line segment being built
    CS_ArcSeg  arc ;    // temporary arc segment being built
    CS_VECTOR vtan, vp ; 
    CS_POINT pl[4] ; // processed points list
    
    // matching curve points to the start and end of current build segment
    CS_CrvPnt acp[2] ; 

    CS_POINT tp ;    // next test point
    int np = 0 ;     // number of current points
    int mode = NOMODE ; 
    double u, uo, uf, ul, du ; 
    int closed = crv.Closed() ; 
          
    CS_CrvPnt cp ; // current process point on main curve
    CS_SegPtr pseg ; 
    int i ; 
    // int segsteps = 15 ; 

    pseg = crv.pStart ; 

    while (pseg)
    {
        uo = pseg->uo ; 
        if (pseg->next)
            uf = pseg->next->uo  ; 
        else 
            uf = 1.0 ; 

        ul = uf - uo ; 
        du = ul / (double)segsteps ; 

        for (i=0, u=uo; i < segsteps ; i++, u+=du)
        {
            cp.s = pseg ; 
            // Now need the u value of the segment
            cp.u = fabs(u - uo) / ul ; 
            ProcessPoint(crv, cp, dofs, ndofs, u, closed, pl, acp, np, mode, line, arc, tprcrv) ;
        }
        pseg = pseg->next ;
    }

    u = 1.0 ; 
    cp.s = crv.pEnd ; 
    cp.u = 1.0 ; 
    ProcessPoint(crv, cp, dofs, ndofs, u, closed, pl, acp, np, mode, line, arc, tprcrv) ;

    if (mode == LINEMODE)
    {
        CS_LineSeg *pls = new CS_LineSeg(line) ; 
        pls->cp = acp[0] ;  
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (mode == ARCMODE)
    {
        CS_ArcSeg *pas = new CS_ArcSeg(arc) ; 
        pas->cp = acp[0] ;  
        tprcrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (np > 1)
    {   // In no mode, so take the last two points and add the line
        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
        pls->cp = acp[0] ; 
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }

    
    ///////////////////////////// DEBUG /////////////////////////////////
    DEBUGVAR(fprintf(fpDebugOut, "Raw taper curve has %d nodes\n", tprcrv.nodecnt)) ; 


    CS_IRECList irlist ; 
    tprcrv.SelfIntersect(-1, irlist) ; 
    if (irlist.size() == 0)
    {   // Then just copy the result curve, no need to do any chaining
        DEBUGVAR(fprintf(fpDebugOut, "No self intersections\n")) ; 
        rescrv.CopyCurve(tprcrv) ; 
    }
    else
    {
        DEBUGVAR(fprintf(fpDebugOut, "There were %d self intersections\n", irlist.size())) ; 

        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
        // Split the curve up at each intersection point         //
        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
        // Put all the intersections in a list sorted by u value 
        double *d1, *d2 ; // d1 is first list and d2 is final list
        int n1, n2 ; 

        d1 = new double[irlist.size() * 2 + 2] ; 
        d2 = new double[irlist.size() * 2 + 2] ; 

        n1 = 0 ; 
        CS_IRECListItr iri ;
        for (iri = irlist.begin(); iri != irlist.end(); iri++)
        {
            CS_IREC *pir = iri->pir ; 
            d1[n1++] = pir->UP0() ; 
            d1[n1++] = pir->US0() ; 
        }

        qsort(d1, n1, sizeof(double), compdbl);

        CS_CurvePtr pcrv ; 
        CS_CurveSet sectionset ; 

        // Build the final list
        i = 0 ; 
        n2 = 0 ; 
        d2[n2++] = 0.0 ; 
        if (tcomp_EQZ(d1[0]))
            i++ ; 
        
        while (i < n1)
        {
            if (tcomp_NEQ(d1[i], d2[n2-1]))
                d2[n2++] = d1[i] ; 
            i++ ; 
        }

        if (tcomp_NEQ(d2[n2-1], 1.0))
            d2[n2++] = 1.0 ; 

        for (i=0; i < n2-1; i++)
        {   // Then add the start section to the curve. 
            DEBUGVAR(fprintf(fpDebugOut, "Adding chain section [%.6f,%.6f]\n", d2[i], d2[i+1])) ; 
            pcrv = tprcrv.CopySection(d2[i], d2[i+1]) ; 
            sectionset.AddCurve(pcrv) ; 
        }

        delete[] d2 ; 
        delete[] d1 ; 

        // Now intersect all the curves in the sectionset together
        // so that they can be chained
        CS_IRECList irlchn ; 
        CS_CurveVecItr ica, icb ; 
        ica = sectionset.crvlist.begin() ; 
        while (ica != sectionset.crvlist.end())
        {
            (*ica)->Complete() ; 
            icb = ica ;
            icb++ ; 
            while (icb != sectionset.crvlist.end())
            {
                (*ica)->Intersect2D(*icb, &irlchn) ; 
                icb++ ; 
            }
            ica++ ; 
        }

        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
        // Now chain right or left depending on the offset side. //
        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
    
        DEBUGVAR(fprintf(fpDebugOut, "There were %d chaining intersections\n", irlchn.size())) ; 

        int chnmode ;
        if (dofs[0][1] < 0)
            chnmode = CS_Chain::LEFT | CS_Chain::OPENCURVES | CS_Chain::WALKONCE ; 
        else
            chnmode = CS_Chain::RIGHT | CS_Chain::OPENCURVES | CS_Chain::WALKONCE ; 

        CS_Chain chn ; 
        chn.chntol = 0.025 ;
        chn.AddIntersectDataToCurves(irlchn) ;

        CS_CurvePtr firstcrv, lastcrv ; 
        firstcrv = *(sectionset.crvlist.begin()) ; 
        lastcrv = sectionset.crvlist.back() ; 

        if (!crv.Closed())
        {
            chn.AddChainRECToCurve(firstcrv, 0.0, chn.chntol) ;
            if (firstcrv != lastcrv) 
                chn.AddChainRECToCurve(lastcrv, 1.0, chn.chntol) ;
        }

        sectionset.InitIterator() ; 
        while (pcrv = sectionset.NextCurve())
        {
            chn.SetFwdRevPointers(pcrv) ; 
            lastcrv = pcrv ; 
        }
        
        CS_ChnNodeMapItr icn ; 
        icn = firstcrv->pcnmap->begin() ;
        CS_ChainREC *pstartrec = icn->second.pcr ; 

        DEBUGVAR(fprintf(fpDebugOut, "About to chain loop\n")) ; 
        DEBUGVAR (
            {
                i = 0 ; 
                sectionset.InitIterator() ; 
                while (pcrv = sectionset.NextCurve())
                {
                    fprintf(fpDebugOut, "==========================================================\n") ;
                    fprintf(fpDebugOut, "Curve # %d\n", i++) ;
                    pcrv->PrintCurve(1, fpDebugOut) ; 
                    for (icn = pcrv->pcnmap->begin(); icn != pcrv->pcnmap->end() ; icn++)
                    {
                        fprintf(fpDebugOut, "ChnNode: %.6f\n", icn->first.d) ;
                    }
                }
            }
        )

        chn.ChainLoop(pstartrec, CS_FORWARD, chnmode | CS_Chain::FORWARDONLY) ; 

        DEBUGVAR(fprintf(fpDebugOut, "Chain has %d sections to it\n", chn.chnreclist.size())) ; 

        pcrv = chn.BuildChainCurve() ; 

        if (pcrv)
            rescrv.CopyCurve(*pcrv) ; 
    }

    return 0 ;
}


static inline void ProcessPointC(CS_Curve &crv, 
                                 CS_RECT *rec, 
                                 CS_CrvPnt &cp, 
                                 double dofs[][2], 
                                 int &ndofs, 
                                 double &u, 
                                 int &closed, 
                                 CS_POINT pl[], 
                                 CS_CrvPnt acp[],
                                 int &np, 
                                 int &mode, 
                                 CS_LineSeg &line, 
                                 CS_ArcSeg &arc, 
                                 CS_Curve &rescrv)

{
    CS_POINT tp, crvpnt ;
    CS_VECTOR vtan, vp ; 
    double dk, ut ;

    CS_ArcSeg circ ; 
    CS_CIRCLE cir ; 

    dk = deltau(dofs, ndofs, u, closed) ; 
    // vtan = crv.UTangent(u) ; 
    vtan = cp.s->UTangent(cp.u) ; 
    vp = vtan.RightPerp() ; 
    crvpnt = cp.Point() ; 
    
    circ.ctr = crvpnt + (vp * dk) ; 
    circ.rad = dk ; 
    circ.swp = RADIAN360 ; 
    circ.sa  = 0 ; 
    cir.ctr = circ.ctr ; 
    cir.rad = circ.rad ; 

    CS_RECT cbndrect ; 
    cbndrect = circ.BoundingRect() ; 

    bool failed = false ; 
    int i = 0 ; 
    double uva[2], uvb[2] ; 
    int nisects ; 
    CS_SegPtr pseg = crv.pStart ; 

    while (pseg && !failed)
    {
        if (rec[i++].Overlaps(cbndrect))
        {
            if (pseg->IsLINE())
            {
                CS_LineSeg *pls = (CS_LineSeg*)pseg ; 
                nisects = pls->Intersect2D(circ, uva, uvb) ;
                if (nisects > 0)
                {
                    CS_POINT p = pls->UPoint(uva[0]) ; 
                    if (p != crvpnt)
                    {
                        failed = true ; 
                        break ; 
                    }
                }

                if (nisects > 1)
                {
                    CS_POINT p = pls->UPoint(uva[1]) ; 
                    if (p != crvpnt)
                    {
                        failed = true ; 
                        break ; 
                    }
                }
            }
            else
            {
                CS_ArcSeg *pas = (CS_ArcSeg*)pseg ; 
                if (!cir.InsideOrOn(CS_CIRCLE(*pas)))
                {
                    nisects = pas->Intersect2D(circ, uva, uvb) ; 
                    if (nisects > 0)
                    {
                        CS_POINT p = pas->UPoint(uva[0]) ; 
                        if (p != crvpnt)
                        {
                            failed = true ; 
                            break ; 
                        }
                    }

                    if (nisects > 1)
                    {
                        CS_POINT p = pas->UPoint(uva[1]) ; 
                        if (p != crvpnt)
                        {
                            failed = true ; 
                            break ; 
                        }
                    }
                }
            }
        }
        pseg = pseg->next ; 
    }
   
    if (!failed)
    {   // Then use the point
        tp = circ.ctr ; 
        if (mode == LINEMODE)
        {   
            if (line.PointOnLine(tp, &ut))
            {   // Then want to absorb this point into the line
                if (ut < 0.0)
                {
                    acp[0] = cp ; 
                    line.sp = tp ; 
                }
                else if (ut > 1.0)
                {
                    acp[1] = cp ; 
                    line.ep = tp ;
                }
            }
            else 
            {   // The point is not on the line so add the current line
                // segment to the curve being built and then reset for 
                // the next point
                CS_LineSeg *pls = new CS_LineSeg(line) ;
                pls->cp = acp[0] ;
                rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
            
                mode = NOMODE ;
                acp[0] = acp[1] ;
                acp[1] = cp ; 
                pl[0] = line.ep ; 
                pl[1] = tp ; 
                np = 2 ; 
            }
        }
        else if (mode == ARCMODE)
        {   // Test if the point is on the circle defined by the arc
            CS_VECTOR vctr(arc.ctr, tp) ;
            if (tcomp_EQ(vctr.Mag(), arc.rad))
            {   // Have to absorb this point into the arc, to do this want
                // to get a u coordinate for the point relative to the existing
                // arc and then adjust the start angle and sweep based on 
                // where this point falls. 
                if (!arc.PointOnArc(tp, &ut))
                {   // Then have to figure out which end to extend
                    double pointang = vctr.AngleXY() ;
                    IncludeArcPoint(arc, pointang) ;
                    acp[1] = cp ; 
                }
                else
                {   // Do nothing since point is on the arc already
                    int x = 0 ; 
                    x++ ; 
                }
            }
            else
            {   // The point defines a new arc or line so save the current
                // arc and reset for next curve segment
                CS_ArcSeg *pas = new CS_ArcSeg(arc) ;
                pas->cp = acp[0] ;
                rescrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ; 

                mode = NOMODE ;
                acp[0] = acp[1] ;
                acp[1] = cp ; 
                pl[0] = arc.EndPoint() ; 
                pl[1] = tp ; 
                np = 2 ; 
            }
        }
        else
        {   // No mode currently active so see what type of curve we 
            // are building and set the state accordingly.
            if (np < 2)
            {   // Simply add the point to the list
                if (np == 0)
                    acp[0] = cp ; 
                else
                    acp[1] = cp ; 
                pl[np++] = tp ; 
            }
            else
            {   // This is the third point
                // no should be 2 at this point so grab the last two points
                // plus the current point and figure out what mode to set. 
                if (CS_Collinear(pl[0], pl[1], tp))
                {   // Then create a line
                    acp[1] = cp ; 
                    line.sp = pl[0] ; 
                    line.ep = tp ; 
                    np = 2 ; 
                    mode = LINEMODE ; 
                }
                else
                {
                    arc.Arc3Points(pl[0], pl[1], tp) ;
                    if (fabs(arc.swp) > RADIAN45)
                    {
                        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
                        pls->cp = acp[0] ;
                        rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;

                        mode = NOMODE ; 
                        acp[0] = acp[1] ; 
                        acp[1] = cp ; 
                        pl[0] = pl[1] ; 
                        pl[1] = tp ; 
                        np = 2 ; 
                    }
                    else
                    {
                        acp[1] = cp ; 
                        np = 2 ; 
                        mode = ARCMODE ; 
                    }
                }
            }
        }
    }
}



// Circle method
int VarOfsNMC(CS_Curve &crv, double dofs[][2], int ndofs, double filletrad, int segsteps, CS_Curve &rescrv)
{
    CS_Curve tprcrv ; 

    if (tcomp_NEZ(filletrad))
        crv.Fillet(filletrad) ; 
    crv.Complete() ; 

    // Process each segment of the curve separately, so that short segments
    // are processed with as much (greater) precision as long segments. 

    CS_LineSeg line ;   // temporary line segment being built
    CS_ArcSeg  arc ;    // temporary arc segment being built
    CS_VECTOR vtan, vp ; 
    CS_POINT pl[4] ; // processed points list
    
    // matching curve points to the start and end of current build segment
    CS_CrvPnt acp[2] ; 

    CS_POINT tp ;    // next test point
    int np = 0 ;     // number of current points
    int mode = NOMODE ; 
    double u, uo, uf, ul, du ; 
    int closed = crv.Closed() ; 
          
    CS_CrvPnt cp ; // current process point on main curve
    CS_SegPtr pseg ; 
    int i ; 

    // int segsteps = 15 ; 

    pseg = crv.pStart ; 
    // initialize a set of bounding rectangles
    CS_RECT *prect = new CS_RECT[crv.nodecnt] ; 
    i = 0 ; 
    while (pseg)
    {
        prect[i] = pseg->BoundingRect() ; 
        prect[i].Expand(0.01) ; // make 1% bigger
        pseg = pseg->next ;    
        i++ ; 
    }

    pseg = crv.pStart ; 
    while (pseg)
    {
        uo = pseg->uo ; 
        if (pseg->next)
            uf = pseg->next->uo  ; 
        else 
            uf = 1.0 ; 

        ul = uf - uo ; 
        du = ul / (double)segsteps ; 

        for (i=0, u=uo; i < segsteps ; i++, u+=du)
        {
            cp.s = pseg ; 
            cp.u = fabs(u - uo) / ul ; 
            ProcessPointC(crv, prect, cp, dofs, ndofs, u, closed, pl, acp, np, mode, line, arc, tprcrv) ;
        }
        pseg = pseg->next ;
    }

    u = 1.0 ; 
    cp.s = crv.pEnd ; 
    cp.u = 1.0 ; 
    ProcessPointC(crv, prect, cp, dofs, ndofs, u, closed, pl, acp, np, mode, line, arc, tprcrv) ;

    if (mode == LINEMODE)
    {
        CS_LineSeg *pls = new CS_LineSeg(line) ; 
        pls->cp = acp[0] ;  
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (mode == ARCMODE)
    {
        CS_ArcSeg *pas = new CS_ArcSeg(arc) ; 
        pas->cp = acp[0] ;  
        tprcrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (np > 1)
    {   // In no mode, so take the last two points and add the line
        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
        pls->cp = acp[0] ; 
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }

    delete[] prect ; // done with the bounding rectangles
    
    ///////////////////////////// DEBUG /////////////////////////////////
    DEBUGVAR(fprintf(fpDebugOut, "Raw taper curve has %d nodes\n", tprcrv.nodecnt)) ; 
    rescrv.CopyCurve(tprcrv) ; 
    return 0 ;
}


static inline void ProcessPointCp(CS_Curve &crv, 
                                  CS_RECT *rec, 
                                  CS_CrvPnt &cp, 
                                  double &dk, 
                                  CS_POINT pl[], 
                                  CS_CrvPnt acp[],
                                  int &np, 
                                  int &mode, 
                                  CS_LineSeg &line, 
                                  CS_ArcSeg &arc, 
                                  CS_Curve &rescrv)

{
    CS_POINT tp, crvpnt ;
    CS_VECTOR vtan, vp ; 
    double ut ;

    CS_ArcSeg circ ; 
    CS_CIRCLE cir ; 

    // vtan = crv.UTangent(u) ;
    vtan = cp.s->UTangent(cp.u) ; 
    vp = vtan.RightPerp() ; 
    crvpnt = cp.Point() ; 
    
    circ.ctr = crvpnt + (vp * dk) ; 
    circ.rad = dk ; 
    circ.swp = RADIAN360 ; 
    circ.sa  = 0 ; 
    cir.ctr = circ.ctr ; 
    cir.rad = circ.rad ; 

    CS_RECT cbndrect ; 
    cbndrect = circ.BoundingRect() ; 

    bool failed = false ; 
    int i = 0 ; 
    double uva[2], uvb[2] ; 
    int nisects ; 
    CS_SegPtr pseg = crv.pStart ; 

    while (pseg && !failed)
    {
        if (rec[i++].Overlaps(cbndrect))
        {
            if (pseg->IsLINE())
            {
                CS_LineSeg *pls = (CS_LineSeg*)pseg ; 
                nisects = pls->Intersect2D(circ, uva, uvb) ;
                if (nisects > 0)
                {
                    CS_POINT p = pls->UPoint(uva[0]) ; 
                    if (p != crvpnt)
                    {
                        failed = true ; 
                        break ; 
                    }
                }

                if (nisects > 1)
                {
                    CS_POINT p = pls->UPoint(uva[1]) ; 
                    if (p != crvpnt)
                    {
                        failed = true ; 
                        break ; 
                    }
                }
            }
            else
            {
                CS_ArcSeg *pas = (CS_ArcSeg*)pseg ; 
                if (!cir.InsideOrOn(CS_CIRCLE(*pas)))
                {
                    nisects = pas->Intersect2D(circ, uva, uvb) ; 
                    if (nisects > 0)
                    {
                        CS_POINT p = pas->UPoint(uva[0]) ; 
                        if (p != crvpnt)
                        {
                            failed = true ; 
                            break ; 
                        }
                    }

                    if (nisects > 1)
                    {
                        CS_POINT p = pas->UPoint(uva[1]) ; 
                        if (p != crvpnt)
                        {
                            failed = true ; 
                            break ; 
                        }
                    }
                }
            }
        }
        pseg = pseg->next ; 
    }
   
    if (!failed)
    {   // Then use the point
        tp = circ.ctr ; 
        if (mode == LINEMODE)
        {   
            if (line.PointOnLine(tp, &ut))
            {   // Then want to absorb this point into the line
                if (ut < 0.0)
                {
                    acp[0] = cp ; 
                    line.sp = tp ; 
                }
                else if (ut > 1.0)
                {
                    acp[1] = cp ; 
                    line.ep = tp ;
                }
            }
            else 
            {   // The point is not on the line so add the current line
                // segment to the curve being built and then reset for 
                // the next point
                CS_LineSeg *pls = new CS_LineSeg(line) ;
                pls->cp = acp[0] ;
                rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
            
                mode = NOMODE ;
                acp[0] = acp[1] ;
                acp[1] = cp ; 
                pl[0] = line.ep ; 
                pl[1] = tp ; 
                np = 2 ; 
            }
        }
        else if (mode == ARCMODE)
        {   // Test if the point is on the circle defined by the arc
            CS_VECTOR vctr(arc.ctr, tp) ;
            if (tcomp_EQ(vctr.Mag(), arc.rad))
            {   // Have to absorb this point into the arc, to do this want
                // to get a u coordinate for the point relative to the existing
                // arc and then adjust the start angle and sweep based on 
                // where this point falls. 
                if (!arc.PointOnArc(tp, &ut))
                {   // Then have to figure out which end to extend
                    double pointang = vctr.AngleXY() ;
                    IncludeArcPoint(arc, pointang) ;
                    acp[1] = cp ; 
                }
                else
                {   // Do nothing since point is on the arc already
                    int x = 0 ; 
                    x++ ; 
                }
            }
            else
            {   // The point defines a new arc or line so save the current
                // arc and reset for next curve segment
                CS_ArcSeg *pas = new CS_ArcSeg(arc) ;
                pas->cp = acp[0] ;
                rescrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ; 

                mode = NOMODE ;
                acp[0] = acp[1] ;
                acp[1] = cp ; 
                pl[0] = arc.EndPoint() ; 
                pl[1] = tp ; 
                np = 2 ; 
            }
        }
        else
        {   // No mode currently active so see what type of curve we 
            // are building and set the state accordingly.
            if (np < 2)
            {   // Simply add the point to the list
                if (np == 0)
                    acp[0] = cp ; 
                else
                    acp[1] = cp ; 
                pl[np++] = tp ; 
            }
            else
            {   // This is the third point
                // no should be 2 at this point so grab the last two points
                // plus the current point and figure out what mode to set. 
                if (CS_Collinear(pl[0], pl[1], tp))
                {   // Then create a line
                    acp[1] = cp ; 
                    line.sp = pl[0] ; 
                    line.ep = tp ; 
                    np = 2 ; 
                    mode = LINEMODE ; 
                }
                else
                {
                    arc.Arc3Points(pl[0], pl[1], tp) ;
                    if (fabs(arc.swp) > RADIAN45)
                    {
                        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
                        pls->cp = acp[0] ;
                        rescrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;

                        mode = NOMODE ; 
                        acp[0] = acp[1] ; 
                        acp[1] = cp ; 
                        pl[0] = pl[1] ; 
                        pl[1] = tp ; 
                        np = 2 ; 
                    }
                    else
                    {
                        acp[1] = cp ; 
                        np = 2 ; 
                        mode = ARCMODE ; 
                    }
                }
            }
        }
    }
}



// Circle method, with direct incremental steps pre-defined. In this version 
// testing is done to make sure that the exact end point of each inner segment 
// is also included in the testing for offsetting. The u increment along the 
// base curve crv is determined by the input data array. Make sure the dofs
// array has extra duplicate entries tacked on to the end beyond the ndofs 
// count value
int VarOfsNMCp(CS_Curve &crv, double dofs[][2], int ndofs, CS_Curve &rescrv)
{
    CS_Curve tprcrv ; 

    crv.Complete(NODIR) ; // make sure the input curve is up to date. 

    CS_LineSeg line ;   // temporary line segment being built
    CS_ArcSeg  arc ;    // temporary arc segment being built
    CS_VECTOR vtan, vp ; 
    CS_POINT pl[4] ; // processed points list
    
    // matching curve points to the start and end of current build segment
    CS_CrvPnt acp[2] ; 

    CS_POINT tp ;    // next test point
    int np = 0 ;     // number of current points
    int mode = NOMODE ; 
    double u, uo, uf, ul ; 
          
    CS_CrvPnt cp ; // current process point on main curve
    CS_SegPtr pseg ; 
    int i ; 

    // int segsteps = 15 ; 

    pseg = crv.pStart ; 
    // initialize a set of bounding rectangles
    CS_RECT *prect = new CS_RECT[crv.nodecnt] ; 
    i = 0 ; 
    while (pseg)
    {
        prect[i] = pseg->BoundingRect() ; 
        prect[i].Expand(0.01) ; // make 1% bigger
        pseg = pseg->next ;    
        i++ ; 
    }

    i = 0 ; 
    pseg = crv.pStart ; 
    while (pseg)
    {
        uo = pseg->uo ; 
        if (pseg->next)
            uf = pseg->next->uo  ; 
        else 
            uf = 1.0 ; 

        ul = uf - uo ; 

        while (dofs[i][0] < uf)
        {
            cp.s = pseg ; 
            cp.u = fabs(dofs[i][0] - uo) / ul ; 
            ProcessPointCp(crv, prect, cp, dofs[i][1], pl, acp, np, 
                                    mode, line, arc, tprcrv) ;
            i++ ; 
        }

        
        // We've just walked off the end of the segment so make sure that the
        // last point processed was the exact end of the segment and if not 
        // then include that point in the processing. 
        if (pseg->next && tcomp_NEQ(cp.u, 1.0))
        {   // Must include the segment end point
            double uc, dx, dy, ofs ;
            cp.s = pseg ; 
            cp.u = 1.0 ; 
            // Now want the curve u 
            uc = crv.SegU2CrvU(cp.s, cp.u) ; 
            // Now find the two offsets that enclose the curve u coordinate
            if (tcomp_LEQ(dofs[i][0], uc) && tcomp_LEQ(uc, dofs[i+1][0]))
            {   // Want the record forwards, this should only occur if we land 
                // exactly on the end of the segment since the while loop above
                // that processes the points should ensure the 
                dx = uc - dofs[i][0] ;
                dy = dofs[i+1][1] - dofs[i][1] ; 
                ofs = dofs[i][1] + dy * dx ; 
            }   
            if (tcomp_LEQ(dofs[i-1][0], uc) && tcomp_LEQ(uc, dofs[i][0]))
            {   // Want the record backwards, this should be the case 
                // almost every time. 
                dx = uc - dofs[i-1][0] ;
                dy = dofs[i][1] - dofs[i-1][1] ; 
                ofs = dofs[i-1][1] + dy * dx ; 
            }
            else
            {   // Something is wrong since we should be almost exactly synched
                // to the line at this point due to while exit condition, 
                // probably have bad dofs[] data array
                if (i > 0)
                    ofs = dofs[i-1][1] ; 
                else
                    ofs = dofs[0][1] ; 
            }
            ProcessPointCp(crv, prect, cp, ofs, pl, acp, np, 
                                    mode, line, arc, tprcrv) ;
        }

        pseg = pseg->next ;
    }

    u = 1.0 ;
    cp.s = crv.pEnd ; 
    cp.u = 1.0 ; 
    ProcessPointCp(crv, prect, cp, dofs[ndofs-1][1], pl, acp, np, 
                            mode, line, arc, tprcrv) ;

    if (mode == LINEMODE)
    {
        CS_LineSeg *pls = new CS_LineSeg(line) ; 
        pls->cp = acp[0] ;  
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (mode == ARCMODE)
    {
        CS_ArcSeg *pas = new CS_ArcSeg(arc) ; 
        pas->cp = acp[0] ;  
        tprcrv.Append(pas, CS_NOENDPOINTADJUSTMENT) ;
    }
    else if (np > 1)
    {   // In no mode, so take the last two points and add the line
        CS_LineSeg *pls = new CS_LineSeg(pl[0], pl[1]) ;
        pls->cp = acp[0] ; 
        tprcrv.Append(pls, CS_NOENDPOINTADJUSTMENT) ;
    }

    delete[] prect ; // done with the bounding rectangles
    
    ///////////////////////////// DEBUG /////////////////////////////////
    DEBUGVAR(fprintf(fpDebugOut, "Raw taper crv nodecnt=%d\n", tprcrv.nodecnt)) ;
    rescrv.CopyCurve(tprcrv) ; 
    return 0 ;
}