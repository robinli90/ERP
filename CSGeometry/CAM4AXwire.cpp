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
// CAM4AXwire.cpp - routines to simplify generation of 4 axis wire paths

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_cadfuncs.h"
#include "cs_nmcurves.h"
#include "cs_camfuncs.h"


// Set to 0 to disable, do not undefine
#define DEBUG4AXIS              0
#define DEBUG4AXSYNCH           0


static void AdjustCurvePoint(CS_CrvPnt &cp)
{
    if (cp.u >= 1.0)
    {
        if (cp.s->pParent->Closed())
        {   
            cp.s = cp.s->pParent->Next(cp.s) ; 
            cp.u = 0 ; 
        }
        else
        {   // Simply force it to 1.0
            cp.u = 1.0 ; 
        }
    }
    else if (cp.u < 0.0)
    {
        cp.u = 0.0 ; 
    }
}


// See notes Geom Algo's RR Vol4 pg 186
static inline void CalcXYandUVPoints(CS_POINT &p1, CS_POINT &p2, 
                                     double z1, double z2, 
                                     double ZXY, double ZUV, 
                                     CS_POINT &pxy, CS_POINT &puv) 
{
    CS_POINT pA(p1) ; 
    pA.z = z1 ; 

    CS_VECTOR v12(p2.x - p1.x, p2.y - p1.y, z2 - z1) ;
    double zH = z2 - z1 ; 
    pxy = pA + (v12 * ((ZXY - z1) / zH)) ; 
    puv = pA + (v12 * ((ZUV - z1) / zH)) ; 
}

static inline double calcdeltau(CS_Curve &crv, double us, double ue, int synchlen)
{
    double du ; 
    if (synchlen == 2)
    {   // Special case 
        if (tcomp_EQ(us, ue))
        {
            if (crv.Closed())
                du = 1.0 ; 
            else
                du = 0.0 ; 
        }
        else if (us < ue)
        {
            du = ue - us ; 
        }
        else
        {
            du = 1.0 - us + ue ; 
        }
    }
    else
    {
        if (tcomp_EQ(us, ue))
        {
            du = 0.0 ; 
        }
        else if (us < ue)
        {
            du = ue - us ; 
        }
        else
        {
            du = 1.0 - us + ue ; 
        }
    }
    return du ; 
}

static inline double GetZHeight(CS_FastSegVector &fsv, double xdist)
{
    
    CS_SegPtr pseg = fsv.Find(xdist) ; 
    
    if (pseg->IsARC())
    {   // Then have to work out the arc angle
        CS_ArcSeg *pas = (CS_ArcSeg *)pseg ;
        
        // Now make sure the angle is within the sweep of the curve and if
        // not then relect across the line that goes flat through the 
        // center of the arc since we obviously have the reflected angle 
        // result. 
        double alpha = acos((xdist - pas->ctr.x) / pas->rad) ;
        
        if (!pas->AngleOnSweep(alpha))
        {   // Need to reflect the angle
            CS_VECTOR vref(1,0) ; 
            vref.Rotate(alpha) ; 
            vref.y = -vref.y ; // flip the y value
            alpha = vref.AngleXY() ; 
        }
        double y = pas->rad * sin(alpha) + pas->ctr.y ; 
        // v = pas->UTangent(pas->AngleU(alpha)) ; 
        return y ; 
    }
    else
    {
        // Else it's a line segment
        CS_LineSeg *pls = (CS_LineSeg *)pseg ;
        // using y-y1 = m(x-x1)
        double m = (pls->ep.y - pls->sp.y)/(pls->ep.x - pls->sp.x) ; 
        double y = m * (xdist - pls->sp.x) + pls->sp.y ; 
        // v = pls->UTangent(0.0) ; // in case need the v value in future
        return y ; 
    }
}



int CS_4AXWirePathGen(CS_Curve &p1crv, CS_Curve &z1crv,             
                      CS_Curve &p2crv, CS_Curve &z2crv,             
                      CS_Curve &xycrv, CS_Curve &uvcrv,
                      double ZXY, double ZUV, double stepsize,         
                      CS_CurveSyncDataVec &csvec)

{

    // Make sure we have synchronization lines at the start and end of the
    // both curves. 
    FILE *fp = 0 ; 

    if (DEBUG4AXIS)
    {
    
        fp = fopen("c:\\users\\4AX.log", "w") ;   
        fprintf(fp, "=========================================================\n") ; 
        fprintf(fp, "============== Start of Curve SYNCH  ====================\n\n") ; 
    
        fprintf(fp, "p1crv:\n") ; 
        p1crv.Print(0, fp) ; 
    
        fprintf(fp, "\nz1crv:\n") ; 
        z1crv.Print(0, fp) ; 
    
        fprintf(fp, "\np2crv:\n") ; 
        p2crv.Print(0, fp) ; 
    
        fprintf(fp, "\nz2crv:\n") ; 
        z2crv.Print(0, fp) ; 

    }
    
   
    if (csvec.size() == 0)
    {   // Then initialize the synch lines to the end points
        CS_CurveSyncData csd ;

        csd.cpa.s = p1crv.pStart;
        csd.cpa.u = 0.0 ; 
        csd.cpb.s = p2crv.pStart ;
        csd.cpb.u = 0.0 ; 
        csd.ua = 0.0 ; 
        csd.ub = 0.0 ; 
        csvec.push_back(csd) ; 

        csd.cpa.s = p1crv.pEnd ;
        csd.cpa.u = 1.0 ; 
        csd.cpb.s = p2crv.pEnd ;
        csd.cpb.u = 1.0 ; 
        csd.ua = 1.0 ; 
        csd.ub = 1.0 ; 
        csvec.push_back(csd) ; 
    }

    // CS_SegPtr *z1sega = z1crv.BuildSegArray() ; 
    // CS_SegPtr *z2sega = z2crv.BuildSegArray() ; 

    // These vectors are used to quickly map u coords on the picrv's back 
    // to an x distance along the zicrv's. The Z height curves are going
    // to be longer since the x length matches the picrv overall arclength
    // but the zicrv's also have varying Y coord data (and thus must be longer
    // except for the special case where the zicrv is flat where the picrv and
    // zicrv would have identical arclengths). 
    CS_FastSegVector fsv1, fsv2 ; 

    CS_X2SegRec xsr ;
    CS_SegPtr ps = z1crv.pStart ; 
    while (ps)
    {
        xsr.pseg = ps ; 
        xsr.x = ps->StartPoint().x ; 
        fsv1.vs.push_back(xsr) ; 
        ps = ps->next ; 
    }
    // Multiply the x coordinate for the end point by 2 so that it guarantees
    // an exit condition when comparing against the last segment. 
    xsr.pseg = z1crv.pEnd ; 
    xsr.x = z1crv.pEnd->EndPoint().x ; 
    fsv1.vs.push_back(xsr) ; 

    ps = z2crv.pStart ; 
    while (ps)
    {
        xsr.pseg = ps ; 
        xsr.x = ps->StartPoint().x ; 
        fsv2.vs.push_back(xsr) ; 
        ps = ps->next ; 
    }
    xsr.pseg = z2crv.pEnd ; 
    xsr.x = z2crv.pEnd->EndPoint().x ; 
    fsv2.vs.push_back(xsr) ; 

    // Finished initializing the fast lookup arrays

    xycrv.Reset() ; 
    uvcrv.Reset() ; 

    // The synchro lines should now be defined properly. 
    CS_PntCurveBuilder pcbXY, pcbUV ; // the output build curves
    CS_Curve pntCrvXY, pntCrvUV ; 
    pcbXY.pcrv = &pntCrvXY ; 
    pcbUV.pcrv = &pntCrvUV ; 

    double du1, du2 ; // crv 1 and 2 u steps values
    double u1, u2 ; 
    double u1s, u1e, u2s, u2e ; 
    double u1len, u2len ; 

    double z1, z2 ; 
    int nstep1, nstep2, nsteps ; 
    CS_POINT p1, p2 ; 
    CS_POINT pXY, pUV ; 

    // Initialize the first point that is being added. 
    p1 = csvec[0].cpa.Point() ; 
    p2 = csvec[0].cpb.Point() ; 
    z1 = GetZHeight(fsv1, csvec[0].ua * p1crv.arclength) ;
    z2 = GetZHeight(fsv2, csvec[0].ub * p2crv.arclength) ; 

    CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 
    
    pcbXY.AddPoint(pXY, csvec[0].cpa) ; 
    pcbUV.AddPoint(pUV, csvec[0].cpb) ; 

    double u1step = stepsize / p1crv.ArcLength() ; 
    double u2step = stepsize / p2crv.ArcLength() ; 

    double al1step, al2step ; 

    double u1pct, u2pct ; 
    double u1crv, u2crv ; 

    ///////////////////////////////////////////////////////////////////////////
    // not really needed as this stuff is automatically created in SynchCurves 
    // These two curve synch data records will be used for each section
    // CS_CurveSyncData *pcsdata[2] ; 
    // CS_CurveSyncData csd1, csd2 ; 
    // pcsdata[0] = &csd1 ; 
    // pcsdata[1] = &csd2 ; 
    ///////////////////////////////////////////////////////////////////////////

    CS_CrvPnt cp1, cp2 ; 
    CS_CrvPnt cpa, cpb ; 
    double du1seg, du2seg ; 
    double uc ; // temp u value


    if (DEBUG4AXIS)
    {
        for (unsigned int ii = 0 ; ii < csvec.size() ; ii++)
        {
            fprintf(fp, "%4d: ", ii) ; 
            CS_POINT p1 = csvec[ii].cpa.Point() ; 
            CS_POINT p2 = csvec[ii].cpb.Point() ; 
            p1.z = p2.z = 0 ; 
            double d = CS_Distance(p1, p2) ; 
            p1.Print(fp) ; p2.Print(fp) ; 
            fprintf(fp, "  %.10f\n", d) ; 
        }
    }

    unsigned int i ; 
    for (i=0; i < csvec.size() - 1; i++)
    {

        cp1 = csvec[i].cpa ;
        cp2 = csvec[i].cpb ;

        AdjustCurvePoint(cp1) ; 
        AdjustCurvePoint(cp2) ; 

        u1s = csvec[i].cpa.UCrv() ;
        u2s = csvec[i].cpb.UCrv() ;

        u1e = csvec[i+1].cpa.UCrv() ;
        u2e = csvec[i+1].cpb.UCrv() ;

        u1len = calcdeltau(p1crv, u1s, u1e, (int)csvec.size()) ;
        u2len = calcdeltau(p2crv, u2s, u2e, (int)csvec.size()) ;

        // Now match the steps exactly along the two segments
        nstep1 = (int)(u1len / u1step) ; 
        nstep2 = (int)(u2len / u2step) ; 
        if (nstep1 > nstep2)
            nsteps = nstep1 ;
        else 
            nsteps = nstep2 ; 

        nsteps += 1 ; 
        du1 = u1len / (double)nsteps ; 
        du2 = u2len / (double)nsteps ; 
        
        al1step = p1crv.arclength * du1 ; 
        al2step = p2crv.arclength * du2 ; 

        du1seg = CS_CrvULen2SegULen(du1, p1crv, cp1.s) ; 
        du2seg = CS_CrvULen2SegULen(du2, p2crv, cp2.s) ; 

        u1 = u1s + du1 ; 
        u2 = u2s + du2 ; 

        // The initial point will always have been processed when starting the loop

        if (DEBUG4AXIS)
        {
            fprintf(fp, "SYNCH_STEPS - %d\n", nsteps) ; 
        } 

        for (int j=1; j < nsteps - 1 ; j++)
        {
            // See note Geom Algo's RR-Vol4 page 188 for diagrams on what these
            // if's are testing and the cases they describe. 
            if (tcomp_GT(cp1.u + du1seg, 1.0))
            {   // Then we've crossed a segment end point so insert this 
                // point into the processing
                u1pct = (1.0 - cp1.u) / du1seg ; 

                if (tcomp_GT(cp2.u + du2seg, 1.0))
                {   // Then must deal with case 2, 3, or 4
                    u2pct = (1.0 - cp2.u) / du1seg ; 

                    if (tcomp_LT(u2pct, u1pct))
                    {   // CASE 2 
                        cpa.s = cp1.s ;
                        cpa.u = cp1.u + du1seg * u2pct ; 
                        cpb.s = p2crv.Next(cp2.s) ;
                        cpb.u = 0.0 ; 

                        u1crv = cpa.UCrv() ; 
                        u2crv = cpb.s->uo ; 
                        
                        p1 = cpa.Point() ; 
                        p2 = cpb.Point() ; 
                        z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ;
                        z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ;
                        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                        if (DEBUG4AXIS)
                        {
                            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                        } 

                        pcbXY.AddPoint(pXY, cpa) ; 
                        pcbUV.AddPoint(pUV, cpb) ; 

                        // Now do the second segment end point
                        
                        cpa.s = p1crv.Next(cp1.s) ;
                        cpa.u = 0.0 ; 

                        // The next two lines could skip over short segments since
                        // we are doing the math w.r.t. the overall curve arclength
                        // (And the skip over is not because of math precision, the 
                        // reason is that a very short segment might fit completely 
                        // within the small step that is being taken and thus it 
                        // would be skipped over) This problem could happen for 
                        // case 4 as well
                        uc = u2 + al2step * u1pct ; 
                        p2crv.CrvU2SegU(uc, cp2.s, cpb) ; 

                        u1crv = cpa.s->uo ; 
                        u2crv = cpb.UCrv() ; 
                        
                        p1 = cpa.Point() ; 
                        p2 = cpb.Point() ; 
                        z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                        z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                        if (DEBUG4AXIS)
                        {
                            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                        } 

                        pcbXY.AddPoint(pXY, cpa) ; 
                        pcbUV.AddPoint(pUV, cpb) ; 
                    }
                    else if (tcomp_EQ(u1pct, u2pct))
                    {   // CASE 3
                        cpa.s = p1crv.Next(cp1.s) ;
                        cpa.u = 0.0 ; 
                        cpb.s = p2crv.Next(cp2.s) ;
                        cpb.u = 0.0 ; 

                        u1crv = cpa.s->uo ;
                        u2crv = cpb.s->uo ; 
                        
                        p1 = cpa.Point() ; 
                        p2 = cpb.Point() ; 
                        z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                        z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                        if (DEBUG4AXIS)
                        {
                            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                        } 

                        pcbXY.AddPoint(pXY, cpa) ; 
                        pcbUV.AddPoint(pUV, cpb) ; 
                    }
                    else
                    {   // CASE 4
                        cpa.s = p1crv.Next(cp1.s) ;
                        cpa.u = 0.0 ; 
                        cpb.s = cp2.s ; 
                        cpb.u = cp2.u + du2seg * u1pct  ; 

                        u1crv = cpa.s->uo ; 
                        u2crv = cpb.UCrv() ; 
                        
                        p1 = cpa.Point() ; 
                        p2 = cpb.Point() ; 
                        z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                        z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                        if (DEBUG4AXIS)
                        {
                            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                        }

                        pcbXY.AddPoint(pXY, cpa) ; 
                        pcbUV.AddPoint(pUV, cpb) ; 

                        // Now do the second segment end point

                        uc = u1 + al1step * u2pct ; 
                        p1crv.CrvU2SegU(uc, cp1.s, cpa) ; 

                        cpb.s = p2crv.Next(cp2.s) ;
                        cpb.u = 0.0 ; 

                        u1crv = cpa.UCrv() ; 
                        u2crv = cpb.s->uo ; 
                        
                        p1 = cpa.Point() ; 
                        p2 = cpb.Point() ; 
                        z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                        z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                        if (DEBUG4AXIS)
                        {
                            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                        } 

                        pcbXY.AddPoint(pXY, cpa) ; 
                        pcbUV.AddPoint(pUV, cpb) ; 
                    }

                    // Advance cp2
                    cp2.s = p2crv.Next(cp2.s) ; 
                    p2crv.CrvU2SegU(u2, cp2.s, cp2) ; 
                    du2seg = CS_CrvULen2SegULen(du2, p2crv, cp2.s) ; 
                }
                else
                {   // CASE 1
                    cpa.s = p1crv.Next(cp1.s) ;
                    cpa.u = 0.0 ; 
                    cpb.s = cp2.s ; 
                    cpb.u = cp2.u + du2seg * u1pct ; 

                    u1crv = cpa.s->uo ; 
                    u2crv = cpb.UCrv() ; 
                    
                    p1 = cpa.Point() ; 
                    p2 = cpb.Point() ; 
                    z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                    z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                    CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                    if (DEBUG4AXIS)
                    {
                        p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                        pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                    } 

                    pcbXY.AddPoint(pXY, cpa) ; 
                    pcbUV.AddPoint(pUV, cpb) ; 
                }

                // Advance cp1
                cp1.s = p1crv.Next(cp1.s) ; 
                p1crv.CrvU2SegU(u1, cp1.s, cp1) ; 
                du1seg = CS_CrvULen2SegULen(du1, p1crv, cp1.s) ; 
            }
            // Now duplicate all the same logic to see if the second segment has
            // walked over an endpoint
            else if (tcomp_GT(cp2.u + du2seg, 1.0))
            {   // Then crossed the segment end point on 2nd curve
                // To get to here we are dealing with a case 1 situation 
                // for the reversed order of the two curves. Thus adding the 
                // equivalent of the first if's part case 2 first point added
                // This is so because it's already determined from the initial 
                // if clause that the cp1 segment is longer than the current step. 
                u2pct = (1.0 - cp2.u) / du2seg ; 

                cpa.s = cp1.s ;
                cpa.u = cp1.u + du1seg * u2pct ; 
                cpb.s = p2crv.Next(cp2.s) ;
                cpb.u = 0.0 ; 

                u1crv = cpa.UCrv() ; 
                u2crv = cpb.s->uo ; 
                
                p1 = cpa.Point() ; 
                p2 = cpb.Point() ; 
                z1 = GetZHeight(fsv1, u1crv * p1crv.arclength) ; 
                z2 = GetZHeight(fsv2, u2crv * p2crv.arclength) ; 
                CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

                if (DEBUG4AXIS)
                {
                    p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                    pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
                }

                pcbXY.AddPoint(pXY, cpa) ; 
                pcbUV.AddPoint(pUV, cpb) ; 

                // Advance cp2
                cp2.s = p2crv.Next(cp2.s) ; 
                p2crv.CrvU2SegU(u2, cp2.s, cp2) ; 
                du2seg = CS_CrvULen2SegULen(du2, p2crv, cp2.s) ; 
            }
            else
            {
                cp1.u += du1seg ; 
                cp2.u += du2seg ; 
            }

            // The cp1 and cp2 values have now been incremented
            // Now add the two end points 
            p1 = cp1.Point() ; 
            p2 = cp2.Point() ; 
            z1 = GetZHeight(fsv1, cp1.UCrv() * p1crv.arclength) ;
            z2 = GetZHeight(fsv2, cp2.UCrv() * p2crv.arclength) ;
            CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

            if (DEBUG4AXIS)
            {
                p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
                pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
            }
            pcbXY.AddPoint(pXY, cp1) ; 
            pcbUV.AddPoint(pUV, cp2) ; 
            
            u1 += du1 ; 
            u2 += du2 ; 
        }

        // Use the exact end points for the last step. 
        p1 = csvec[i+1].cpa.Point() ; 
        p2 = csvec[i+1].cpb.Point() ; 
        z1 = GetZHeight(fsv1, csvec[i+1].ua * p1crv.arclength) ;
        z2 = GetZHeight(fsv2, csvec[i+1].ub * p2crv.arclength) ;
        CalcXYandUVPoints(p1, p2, z1, z2, ZXY, ZUV, pXY, pUV) ; 

        if (DEBUG4AXIS)
        {
            p1.Print(fp); p2.Print(fp) ; fprintf(fp, "\n") ; 
            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
        }


        pcbXY.AddPoint(pXY, csvec[i+1].cpa) ; 
        pcbUV.AddPoint(pUV, csvec[i+1].cpb) ; 
        
        pcbXY.CompleteSegment() ; 
        pcbUV.CompleteSegment() ; 

        CS_Curve *pscrvxy = new CS_Curve ; 
        CS_Curve *pscrvuv = new CS_Curve ; 

        pcbXY.pcrv->Complete(-1) ; 
        pcbUV.pcrv->Complete(-1) ; 

        CS_CurveSynch(*(pcbXY.pcrv), *(pcbUV.pcrv), *pscrvxy, *pscrvuv, 0, 0) ; 

        xycrv.AddCurve(pscrvxy) ;
        uvcrv.AddCurve(pscrvuv) ;

        pcbXY.pcrv->Reset() ; 
        pcbUV.pcrv->Reset() ; 
    }

    if (DEBUG4AXIS)
        fclose(fp) ; 

    return 0 ; 
}


// See GEOM ALGO's Vol 4 pg 207 
static inline void FlatXYandUVPoints(CS_POINT &pspl, CS_POINT &pclr, 
                                     double zh, double zs, 
                                     double ZXY, double ZUV, 
                                     CS_POINT &pxy, CS_POINT &puv) 
{
    double k = CS_Distance2D(pspl, pclr) ; 
    double D = k * (zs - ZUV) / zh ; 
    double E = k * (ZXY - zs) / zh ; 

    CS_VECTOR vsc(pspl, pclr) ; 
    vsc.z = 0 ; 
    vsc = vsc.Unit() ; 
        
    pxy = pspl - vsc * E ;
    pxy.z = ZXY ; 

    puv = pspl + vsc * D ; 
    puv.z = ZUV ; 
}



// This version uses a flat clearance curve

// See Geom Algo's RR Vol4 pg 208 for an updated explanation of what is going
// on here
int CS_4AXWirePathAngGen(CS_Curve &splinecrv, CS_Curve &zsplinecrv, 
                         CS_Curve &clrcrv, double zoclr, double zdepclr,
                         CS_Curve &xycrv, CS_Curve &uvcrv,
                         double ZXY, double ZUV, double stepsize,         
                         CS_CurveSyncDataVec &csvec)

{

    // Make sure we have synchronization lines at the start and end of the
    // both curves. 

    FILE *fp  = 0 ;
    FILE *fps = 0 ; 

    if (DEBUG4AXIS)
    {
    
        fp = fopen("c:\\users\\4AX.log", "w") ;   
        fprintf(fp, "=========================================================\n") ; 
        fprintf(fp, "============== Start of Curve SYNCH  ====================\n\n") ; 
    
        fprintf(fp, "splinecrv:\n") ; 
        splinecrv.Print(0, fp) ; 
    
        fprintf(fp, "\nzsplinecrv:\n") ; 
        zsplinecrv.Print(0, fp) ; 
    
        fprintf(fp, "\nclrcrv:\n") ; 
        clrcrv.Print(0, fp) ; 
    }

    if (DEBUG4AXSYNCH) 
    {
        fps = fopen("c:\\users\\4AXsynch.log", "wt") ; 
    }
    
   
    if (csvec.size() == 0)
    {   // Then initialize the synch lines to the end points
        CS_CurveSyncData csd ;

        csd.cpa.s = splinecrv.pStart;
        csd.cpa.u = 0.0 ; 
        csd.cpb.s = clrcrv.pStart ;
        csd.cpb.u = 0.0 ; 
        csd.ua = 0.0 ; 
        csd.ub = 0.0 ; 
        csvec.push_back(csd) ; 

        csd.cpa.s = splinecrv.pEnd ;
        csd.cpa.u = 1.0 ; 
        csd.cpb.s = clrcrv.pEnd ;
        csd.cpb.u = 1.0 ; 
        csd.ua = 1.0 ; 
        csd.ub = 1.0 ; 
        csvec.push_back(csd) ; 
    }

    // CS_SegPtr *z1sega = z1crv.BuildSegArray() ; 
    // CS_SegPtr *z2sega = z2crv.BuildSegArray() ; 

    // These vectors are used to quickly map u coords on the picrv's back 
    // to an x distance along the zicrv's. The Z height curves are going
    // to be longer since the x length matches the picrv overall arclength
    // but the zicrv's also have varying Y coord data (and thus must be longer
    // except for the special case where the zicrv is flat where the picrv and
    // zicrv would have identical arclengths). 
    CS_FastSegVector fsv ; 

    CS_X2SegRec xsr ;
    CS_SegPtr ps = zsplinecrv.pStart ; 
    while (ps)
    {
        xsr.pseg = ps ; 
        xsr.x = ps->StartPoint().x ; 
        fsv.vs.push_back(xsr) ; 
        ps = ps->next ; 
    }
    
    // Multiply the x coordinate for the end point by 2 so that it guarantees
    // an exit condition when comparing against the last segment.
    xsr.pseg = zsplinecrv.pEnd ; 
    xsr.x = zsplinecrv.pEnd->EndPoint().x ; 
    fsv.vs.push_back(xsr) ; 

    // Finished initializing the fast lookup array
    xycrv.Reset() ; 
    uvcrv.Reset() ; 

    // The synchro lines should now be defined properly. 
    CS_PntCurveBuilder pcbXY, pcbUV ; // the output build curves
    CS_Curve pntCrvXY, pntCrvUV ;
    pcbXY.pcrv = &pntCrvXY ;
    pcbUV.pcrv = &pntCrvUV ;

    CAM4XEventRec evtrec ; 
    evtrec.Initialize(&splinecrv, &clrcrv) ;

    double zh, zs ; 
    CS_POINT p1, p2 ; 
    CS_POINT pXY, pUV ; 

    int synchlen = (int)csvec.size() ; 

    // Initialize the first point that is being added. 
    zh = zoclr - zdepclr ; // this is the z depth
    p1 = csvec[0].cpa.Point() ; 
    p2 = csvec[0].cpb.Point() ; 
    zs = GetZHeight(fsv, csvec[0].ua * splinecrv.arclength) ;

    FlatXYandUVPoints(p1, p2, zh, zs, ZXY, ZUV, pXY, pUV) ;
    
    pcbXY.AddPoint(pXY, csvec[0].cpa) ; 
    pcbUV.AddPoint(pUV, csvec[0].cpb) ; 



    ///////////////////////////////////////////////////////////////////////////
    // not really needed as this stuff is automatically created in SynchCurves 
    // These two curve synch data records will be used for each section
    // CS_CurveSyncData *pcsdata[2] ; 
    // CS_CurveSyncData csd1, csd2 ; 
    // pcsdata[0] = &csd1 ; 
    // pcsdata[1] = &csd2 ; 
    ///////////////////////////////////////////////////////////////////////////

    if (DEBUG4AXIS)
    {
        for (unsigned int ii = 0 ; ii < csvec.size() ; ii++)
        {
            fprintf(fp, "%4d: ", ii) ; 
            CS_POINT p1 = csvec[ii].cpa.Point() ; 
            CS_POINT p2 = csvec[ii].cpb.Point() ; 
            p1.z = p2.z = 0 ; 
            double d = CS_Distance(p1, p2) ; 
            p1.Print(fp) ; p2.Print(fp) ; 
            fprintf(fp, "  %.10f\n", d) ; 
        }
    }



    int i ; 
    for (i=0; i < synchlen - 1; i++)
    {
        if (i == 112)
        {
            int xxx = 1 ; 
            xxx++ ; 
        }

        // Initialize everything
        evtrec.InitializeSection(csvec, i, stepsize) ;

        // The initial point will always have been processed when starting the loop
        if (DEBUG4AXIS)
        {
            fprintf(fp, "SYNCH_STEPS - %d\n", evtrec.nsteps) ; 
        }

        while (evtrec.istep < evtrec.nsteps - 1)
        {
            // See note Geom Algo's RR-Vol4 page 188 for diagrams on what these
            // if's are testing and the cases they describe. Updated notes
            // are on page 208 and inside back cover
            evtrec.NextEvent() ; 
                        
            p1 = evtrec.cp1cur.Point() ; 
            p2 = evtrec.cp2cur.Point() ; 
            zs = GetZHeight(fsv, evtrec.cp1cur.UCrv() * splinecrv.arclength) ;
            FlatXYandUVPoints(p1, p2, zh, zs, ZXY, ZUV, pXY, pUV) ;

            if (DEBUG4AXIS)
            {
                fprintf(fp, "A - Dist=%10.6lf DistOut=%10.6lf  ", 
                        CS_Distance2D(p1, p2), CS_Distance2D(pXY, pUV)) ; 
                p1.Print(fp); p2.Print(fp) ; fprintf(fp, " OUT POINTS: ") ; 
                pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
            }

            pcbXY.AddPoint(pXY, evtrec.cp1cur) ; 
            pcbUV.AddPoint(pUV, evtrec.cp2cur) ; 

        }

        // Use the exact end points for the last step. 
        p1 = csvec[i+1].cpa.Point() ; 
        p2 = csvec[i+1].cpb.Point() ; 
        zs = GetZHeight(fsv, evtrec.u1e * splinecrv.arclength) ;
        FlatXYandUVPoints(p1, p2, zh, zs, ZXY, ZUV, pXY, pUV) ;

        if (DEBUG4AXIS)
        {
            fprintf(fp, "I - Dist=%10.6lf DistOut=%10.6lf  ", 
                    CS_Distance2D(p1, p2), CS_Distance2D(pXY, pUV)) ; 
            p1.Print(fp); p2.Print(fp) ; fprintf(fp, " OUT POINTS: ") ; 
            pXY.Print(fp); pUV.Print(fp) ; fprintf(fp, "\n") ; 
        }


        pcbXY.AddPoint(pXY, csvec[i+1].cpa) ; 
        pcbUV.AddPoint(pUV, csvec[i+1].cpb) ; 
        
        pcbXY.CompleteSegment() ; 
        pcbUV.CompleteSegment() ; 

        CS_Curve *pscrvxy = new CS_Curve ; 
        CS_Curve *pscrvuv = new CS_Curve ; 

        pcbXY.pcrv->Complete(-1) ; 
        pcbUV.pcrv->Complete(-1) ; 

        CS_CurveSynch(*(pcbXY.pcrv), *(pcbUV.pcrv), *pscrvxy, *pscrvuv, 0, 0) ; 

        /////////////////////////////
        if (DEBUG4AXSYNCH)
        {
            CS_SegPtr pss1, pss2 ; 
            pss1 = pscrvxy->pStart ; 
            pss2 = pscrvuv->pStart ; 
        
            fprintf(fps, "Sync seg %d\n", i) ; 
            fprintf(fps, "Dist=%10.6lf\n", CS_Distance(pss1->StartPoint(), pss2->StartPoint())) ; 
            fprintf(fps, "                ") ; pss1->Print(fps) ; fprintf(fps, "\n") ; 
            fprintf(fps, "                ") ; pss2->Print(fps) ; fprintf(fps, "\n") ; 

            while (pss1)
            {
                fprintf(fps, "Dist=%10.6lf\n", CS_Distance(pss1->StartPoint(), pss2->StartPoint())) ; 
                fprintf(fps, "                ") ; pss1->Print(fps) ; fprintf(fps, "\n") ; 
                fprintf(fps, "                ") ; pss2->Print(fps) ; fprintf(fps, "\n") ; 
                pss1 = pss1->next ; 
                pss2 = pss2->next ; 
            }
        }
        /////////////////////////////

        xycrv.AddCurve(pscrvxy) ;
        uvcrv.AddCurve(pscrvuv) ;

        pcbXY.pcrv->Reset() ; 
        pcbUV.pcrv->Reset() ; 
    }

    if (DEBUG4AXIS)
        fclose(fp) ; 

    if (DEBUG4AXSYNCH)
        fclose(fps) ; 

    return 0 ; 
}


void CAM4XEventRec::AdjustCurvePoint(CS_CrvPnt &cp)
{
    if (cp.u >= 1.0)
    {
        if (cp.s->pParent->Closed())
        {   
            cp.s = cp.s->pParent->Next(cp.s) ; 
            cp.u = 0 ; 
        }
        else
        {   // Simply force it to 1.0
            cp.u = 1.0 ; 
        }
    }
    else if (cp.u < 0.0)
    {
        cp.u = 0.0 ; 
    }
}
 
int CAM4XEventRec::Initialize(CS_Curve *pc1, CS_Curve *pc2)
{
    pcrv1 = pc1 ; 
    pcrv2 = pc2 ; 
    arc1len = pcrv1->ArcLength() ; 
    arc2len = pcrv2->ArcLength() ; 

    return 0 ; 
}


int CAM4XEventRec::InitializeSection(CS_CurveSyncDataVec &csvec, int i, double stepsize) 
{
    cp1start = csvec[i].cpa ;
    cp2start = csvec[i].cpb ;
    
    AdjustCurvePoint(cp1start) ; 
    AdjustCurvePoint(cp2start) ; 
    
    u1s = cp1start.UCrv() ;
    u2s = cp2start.UCrv() ;
    
    cp1end = csvec[i+1].cpa ;
    cp2end = csvec[i+1].cpb ;
    
    AdjustCurvePoint(cp1end) ; 
    AdjustCurvePoint(cp2end) ; 
    
    u1e = cp1end.UCrv() ;
    u2e = cp2end.UCrv() ;
    
    u1len = calcdeltau(*pcrv1, u1s, u1e, (int)csvec.size()) ;
    u2len = calcdeltau(*pcrv2, u2s, u2e, (int)csvec.size()) ;

    double u1step = stepsize / arc1len ; 
    double u2step = stepsize / arc2len ; 
    
    // Now match the steps exactly along the two segments
    int nstep1 = (int)(u1len / u1step) ; 
    int nstep2 = (int)(u2len / u2step) ; 
    if (nstep1 > nstep2)
        nsteps = nstep1 ;
    else 
        nsteps = nstep2 ; 
    
    nsteps += 1 ; 
    du1 = u1len / (double)nsteps ; 
    du2 = u2len / (double)nsteps ; 
    
    cp1cur = cp1start ; 
    cp2cur = cp2start ; 

    seg1arclen = cp1cur.s->ArcLength() ; 
    seg2arclen = cp2cur.s->ArcLength() ; 

    seg1ulen = seg1arclen / arc1len ; 
    seg2ulen = seg2arclen / arc2len ; 

    u1i = u1s ; 
    u2i = u2s ; 

    istep = 1 ; // start at first step position since the 0'th position
    // has already been initialized.

    return 0 ; 
}    


int CAM4XEventRec::JumpsToNextSeg(CS_CrvPnt &cp, double ui, double du)
{
    CS_SegPtr psnxt ; 
    psnxt = cp.s->pParent->Next(cp.s) ; 
    if (psnxt->uo < cp.s->uo)
    {   // Then we wrapped around
        if (ui + du > 1.0) 
            return 1 ; 
    }
    else
    {   // Next segment follows the current one logically
        if (tcomp_GEQ(ui + du, psnxt->uo))
            return 1 ; 
    }

    return 0 ; 
}


void CAM4XEventRec::NextSeg1()
{
    cp1cur.s = cp1cur.s->pParent->Next(cp1cur.s) ; 
    cp1cur.u = 0.0 ; 

    seg1arclen = cp1cur.s->ArcLength() ; 
    seg1ulen = seg1arclen / arc1len ; 
}

void CAM4XEventRec::NextSeg2()
{
    cp2cur.s = cp2cur.s->pParent->Next(cp2cur.s) ; 
    cp2cur.u = 0.0 ; 

    seg2arclen = cp2cur.s->ArcLength() ; 
    seg2ulen = seg2arclen / arc2len ; 
}


// The cases described here are listed on pg 207 of Geom Algo's RR Vol 4
void CAM4XEventRec::NextEvent()
{
    // The four possible distances for each of the four possible events
    // Set to max values so that not factored in if not set. 
    // Each distance must be in terms of a ratio of the total u len for the 
    // section so that a relative distance can be done properly. the 
    // r prefix stands for ratio distance
    double rdu1nxt = 2.0 ; // step to next segment
    double rdu2nxt = 2.0 ; 
    double rdu1step = 2.0 ; // step within current segment
    double rdu2step = 2.0 ; 

    int bC1StepOnSeg = 0 ; // set to 1 if the step is on the same segment
    int bC2StepOnSeg = 0 ; // set to 1 if the step is on the same segment

    // Now find the minimum step delta
    if (JumpsToNextSeg(cp1cur, u1i, du1))
    {   // Then the segment end point occurs before the step to the next point 
        rdu1nxt = (1.0 - cp1cur.u) * seg1ulen  / u1len ; 
    }
    else
    {   // We stay on the same segemtn
        rdu1step = du1 / u1len ;
        bC1StepOnSeg = 1 ;
    }

    // Do the same for the second curve
    if (JumpsToNextSeg(cp2cur, u2i, du2))
    {   // Then the segment end point occurs before the step to the next point 
        rdu2nxt = (1.0 - cp2cur.u) * seg2ulen  / u2len ; 
    }
    else
    {   // We stay on the same segemtn
        rdu2step = du2 / u2len ;
        bC2StepOnSeg = 1 ;
    }


    // Now see which case we have
    // Case 1, next step is on the current segments for both curves
    if (bC1StepOnSeg && bC2StepOnSeg)
    {   // Then we have a CASE 1 condition, don't have to test distances
        // Everything remains on the same current segments
        u1i += du1 ; 
        u2i += du2 ; 

        cp1cur.u = (u1i - cp1cur.s->uo) / seg1ulen ; 
        cp2cur.u = (u2i - cp2cur.s->uo) / seg2ulen ; 

        istep += 1 ; // this completes a delta step 
    }
    else if (!bC1StepOnSeg)
    {   // Then we could have case 2, 3 or 4
        // rdu1nxt is set here have to see which one is less
        if (!bC2StepOnSeg)
        {   // Then test between case 2 or 3 which ever is less
            if (tcomp_LT(rdu1nxt, rdu2nxt))
            {   // Moved to 1st segment end point first
                // Must convert the ratio distance to segment 1's end point
                // to the matching point on segment 2. 
                double udist2 = (rdu1nxt * u2len) ; 
                double usegdist2 = udist2 * u2len / seg2ulen ; 

                NextSeg1() ; 

                cp2cur.u = cp2cur.u + usegdist2 ; 

                // Still on the current step since haven't reached target 
                // distances yet. 
            }
            else if (tcomp_EQ(rdu1nxt, rdu2nxt))
            {   // This is a case 4 situation 
                // Hit segment end points on both curves
                NextSeg1() ; 
                NextSeg2() ; 

                // In this situation we may have hit the u1i and u2i points
                if (tcomp_EQ(cp1cur.s->uo, u1i) && tcomp_EQ(cp2cur.s->uo, u2i))
                {
                    u1i += du1 ; 
                    u2i += du2 ; 
                    istep += 1 ; 
                }
            }
        }
        else
        {   // bC2StepOnSeg is true 
            double udist2 = (rdu1nxt * u2len) ; 
            double usegdist2 = udist2 * u2len / seg2ulen ; 

            NextSeg1() ; 
            // Increment position on the curve 2 segment
            cp2cur.u = cp2cur.u + usegdist2 ; 
        }
    }
    else
    {   // bC1StepOnSeg && !bC2StepOnSeg
        // Which means we have a CASE 3 condition
        double udist1 = (rdu2nxt * u1len) ; 
        double usegdist1 = udist1 * u1len / seg1ulen ; 

        NextSeg2() ; 
        // Increment position on the curve 1 segment
        cp1cur.u = cp1cur.u + usegdist1 ; 
    }
}


