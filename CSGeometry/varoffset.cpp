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
// varoffset.cpp - smoothly offset curve by varying amounts based on an
//              input array that defines the offset distance at different 
//              key points along the curve. 

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

#ifdef	CSDEBUG
#define CS_DEBUG(a)     a ; 
#else
#define CS_DEBUG(a)
#endif

#ifndef min
#define min(a,b)   (a < b) ? (a) : (b)
#endif 

#ifndef max
#define max(a,b)   (a > b) ? (a) : (b)
#endif 


// structure used internally to build out the curve points
struct PointCurveData
{
    // Input parameters

    //! the base curve
    CS_Curve *pbasecrv ; 

    //! maximum delta value
    double dmax ; 

    //! minimum delta value
    double dmin ; 

    //! array of offset curve sets.
    CS_CurveSet *cvs ; 

    //! number of offset curves (length of above array)
    int nofs ;  

    //! u value at start of section
    double us ; 

    //! u value at end of section
    double ue ; 

    //! delta u value for walking along the curve
    double ud ; 

    //! delta at start of the section
    double ds ; 

    //! delta at end of the section
    double de ; 

    //! tolerance determines number of offset curves
    double ofstol ; 

    //! linear tolerance factor
    double lintol ; 

    //! arc tolerance factor
    double arctol ; 

    // Output parameters

    //! array of generated points
    CS_PointVec pv ; 

    PointCurveData() ; 
    ~PointCurveData() ; 

    void OffsetSection() ; 
} ;


PointCurveData::PointCurveData()
{
    cvs = 0 ; 
    nofs = 0 ; 
}

PointCurveData::~PointCurveData()
{
    if (cvs)
        delete[] cvs ; 
}


void PointCurveData::OffsetSection()
{
    CS_Curve *pcrv ; 
    CS_POINT basepnt ; // current point on the base curve
    CS_POINT pnt, nearpnt ; // test point and the nearest point

    ud = (ue - us) * ofstol ;

    double ui ; // current position on the curve
    for (ui = us; tcomp_LT(ui, ue) ; ui += ud)
    {
        // Must map this ui to the offset curve. Based on the ds and de values
        // there will be a range of curves that we are looking at. Take the 
        double ur = (ui - us) / (ue - us) ; 
        double delta = ds + (de - ds) * ur ; 
        int n = RoundDouble(delta / (dmax - dmin) * (double)nofs) ; 
        // Make sure n is within range
        if (n < 0) 
            n = 0 ; 
        else if (n >= nofs) 
            n = nofs - 1 ; 

        // Find the closest point to the point on the base curve
        basepnt = pbasecrv->UPoint(ui) ; 
        
        double unear ; 
        double neardist = 9.9e200 ; // set large

        cvs[n].InitIterator() ; 
        while (pcrv = cvs[n].NextCurve())
        {
            pcrv->PointOnCurve(basepnt, &unear, &pnt) ; 
            double dist = CS_Distance(basepnt, pnt) ;
            if (dist < neardist)
            {
                neardist = dist ; 
                nearpnt = pnt ; 
            }
        }
        pv.push_back(nearpnt) ; 
    }
}



int CS_VarOffset(CS_Curve &crv, CS_VarOfsDataVect &ov, CS_CurveSet &crvset, 
                 double ofstol, double lintol, double arctol) 
{
    if (ov.size() < 1)
    {   // nothing to do, signal error
        return 1 ; 
    }
    else if (ov.size() == 1)
    {   // Then do a single offset
        crv.OffsetSlow(ov[0].delta, crvset) ; 
        return 0 ; 
    }

    // Proceed normally
    int i ; 
    double dmin, dmax ; // offset minimum and maximum values
    dmin = dmax = ov[0].delta ;

    for (i=1; i < (int)ov.size(); i++)
    {
        dmin = min( dmin, ov[i].delta ) ; 
        dmax = max( dmax, ov[i].delta ) ; 
    }

    // Work out the incremental delta offset value, for the set of approximation
    // offset curves
    PointCurveData pcd ; // stores all intermediate processing values

    // set the main variables
    pcd.pbasecrv = &crv ; 
    pcd.dmin = dmin ; 
    pcd.dmax = dmax ; 
    pcd.nofs = (int)(1.0 / ofstol) ; 
    pcd.lintol = lintol ; 
    pcd.arctol = arctol ; 
    pcd.ofstol = ofstol ; 

    double dinc = (dmax - dmin) * ofstol ; 
    double d ; // actual current offset delta

    // Generate the set of offset curves used to approximate the variable curve
    crv.Complete() ; // set uo, cnt, and parent pointers
    pcd.cvs = new CS_CurveSet[pcd.nofs] ; 
    
    // Here we start from the largest offset distance and work out way down to
    // the smallest distance. Since curves are oriented CCW and -ve offsets
    // are towards the inside of the shape, this means that the first offset
    // group will generate the curves that contain all the remaining shapes,
    // thus the first set of offset curves generated will represent the top
    // nodes in the tree that is generated in the next step. Under normal
    // conditions there will only be a single offset curve generated initially.
    for (i=0, d=dmax; i < (int)pcd.nofs; i++, d -= dinc)
    {   // Offset each curve
        crv.OffsetSlow(d, pcd.cvs[i]) ; 
    }


    // Final step is to piece together the resultant curve using points
    // mapped from the original curve to one of the offset curves based 
    // on the offset distance. The index into the cvs array is based upon
    // the offset distance at that point along the base curve. This 
    // offset distance is extracted from the CS_VarOfsDataVect parameter
    // that is passed into the routine. 

    // The main outer loop walks through the CS_VarOfsDataVect data 
    // extracting the either the fixed offset of the offset gradient
    // at each key point. Then an inner loop walks along the curve 
    // for each offset distance section, varying the delta as required
    // along the way. As each point is generated it is added to the end 
    // of approximation points where the resultant curve is approximated
    // as the points are added. Both line and arc segments are 
    // approximated as each point is added. The point to curve builder
    // routine automatically switches from line to arc mode as required
    // in order to minimize the amount of data while simultaneously 
    // meeting the curve tolerance parameters passed into this function.

    // If the line is closed then the section that covers the 1->0 
    // end-start crossover point on the curve is done last. Thus 
    // we begin on the {ov[0],ov[1]} section of the curve

    // See notes Geom Vol4, pg 41
    CS_Curve *pcrv ; 
    CS_POINT basepnt  ; 
    CS_POINT nearpnt, pnt ; 

    int nove = (int)ov.size() - 1 ; 

    // Work out the detail of the start of the curve (initial section)
    // Two different modes, one for closed curves and the other for open curves
    if (tcomp_NEZ(ov[0].u))
    {
        if (crv.Closed()) 
        {   // Then have to work out the start section based on a taper from 
            // the trailing section of the curve. 
            if (tcomp_EQ(ov[nove].u, 1.0))
            {   // Then the last point is the end of the curve so everyhing is
                // simple
                pcd.us = 0 ; 
                pcd.ue = ov[0].u ; 
                pcd.ds = ov[nove].delta ; 
                pcd.de = ov[0].delta ; 
            }
            else
            {   // Have to do it the hard way
                pcd.us = 0.0 ; 
                pcd.ue = ov[0].u ; 
                
                // We need the relative u distance to the start point of the curve
                // from the last section of the curve
                double uro = (1.0 - ov[nove].u) / (1.0 - ov[nove].u + ov[0].u) ; 
                pcd.ds = ov[nove].delta + (ov[0].delta - ov[nove].delta) * uro ;
                pcd.de = ov[0].delta ; 
            }
            pcd.OffsetSection() ; 
        }
        else 
        {   // Then we have to deal with the open ended curve situation
            pcd.us = 0 ; 
            pcd.ue = ov[0].u ; 
            pcd.ds = ov[0].delta ; 
            pcd.de = ov[0].delta ; 

            pcd.OffsetSection() ; 
        }
    }
    // Else - when ov[0].u value is 0 then we don't have to do anything here
    // since the first time through the main loop below the first section will 
    // be calculated. 


    for (i=0; i < (int)ov.size() - 1; i++)
    {
        pcd.us = ov[i].u ; 
        pcd.ue = ov[i+1].u ; 
        pcd.ds = ov[i].delta ; 
        pcd.de = ov[i+1].delta ; 

        pcd.OffsetSection() ; 
    }

    // Must now do the last section 

    // Work out the detail of the start of the curve (initial section)
    // Two different modes, one for closed curves and the other for open curves
    if (tcomp_NEQ(ov[nove].u, 1.0))
    {
        if (crv.Closed()) 
        {   // Then have to work out the end section based on a taper from 
            // the trailing section of the curve through to the start section. 
            if (tcomp_EQZ(ov[0].u))
            {   // Then the last point is the end of the curve so everyhing is
                // simple
                pcd.us = ov[nove].u ; 
                pcd.ue = 1.0 ; 
                pcd.ds = ov[nove].delta ; 
                pcd.de = ov[0].delta ; 
            }
            else
            {   // Have to do it the hard way
                pcd.us = ov[nove].u ; 
                pcd.ue = 1.0 ; 
                
                // We need the relative u distance to the start point of the curve
                // from the last section of the curve

                // we're calculating uro identically here as we did in the 
                // start section case
                double uro = (1.0 - ov[nove].u) / (1.0 - ov[nove].u + ov[0].u) ; 
                pcd.ds = ov[nove].delta ;
                pcd.de = ov[nove].delta + (ov[0].delta - ov[nove].delta) * uro ; 
            }
            pcd.OffsetSection() ; 
        }
        else 
        {   // Then we have to dealt with the open ended curve situation
            pcd.us = ov[nove].u; 
            pcd.ue = 1.0 ; 
            pcd.ds = ov[nove].delta ; 
            pcd.de = ov[nove].delta ; 

            pcd.OffsetSection() ; 
        }
    }
    // Else - when ov[0].u value is 0 then we don't have to do anything here
    // since the first time through the main loop below the first section will 
    // be calculated. 


    // -------------------------------------------------------------------- //
    // -------------------------------------------------------------------- //
    // ------ Curve approximation complete - next build resultant curve --- //
    // -------------------------------------------------------------------- //
    // -------------------------------------------------------------------- //


    // ----------------------------------------------------------------------
    /* TEST CODE */
    int npnts = (int)pcd.pv.size() ; 
    if (npnts > 3)
    {
        CS_LineSeg *pls ; 
        pcrv = new CS_Curve ; 
        for (i=0; i < (npnts - 1); i++)
        {
            pls = new CS_LineSeg(pcd.pv[i], pcd.pv[i+1]) ; 
            pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ; 
        }

        if (crv.Closed())
        {
            pls = new CS_LineSeg(pcd.pv[npnts-1], pcd.pv[0]) ; 
            pcrv->Append(pls, CS_NOENDPOINTADJUSTMENT) ; 
        }
        crvset.AddCurve(pcrv) ; 
    }
    else
        return 2 ;  // error no points generated
    /* END TEST CODE */
    // ----------------------------------------------------------------------

    /////////////////////
    // Production code //
    /////////////////////

    // This is where we do the line and arc approximation based on the 
    // point set generated. TO DO - do the approximation on the fly.

    return 0 ; 
}