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
// intersectionSet.cpp - take the input set of curves and output a set of 
//              intersected curves. For input curves that don't intersect
//              with anything, these are simply fed back as part of the 
//              non-intersected intersection set
// 


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

#include "cs_offset.h"

#include "cs_chain.h"
#include "cs_geomalgos.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)                 a
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif

// Note the function CS_CreateOuterBoundaries(...) is almost identical to this one
int CS_CreateIntersectionSet(CS_CurveSet &inputSet, 
                             CS_CurveSet &intersectedSet, 
                             CS_CurveSet &nonIntersectedSet,
                             double *chaintol, double *revangtol) 
{
    inputSet.InitIterator() ; 
    // Must orient all the curves CCW to ensure the logic works out correctly
    // based on the chaining rules that are applied.

    intersectedSet.clear() ; 
    nonIntersectedSet.clear() ; 

    CS_Curve *pcrv ; 
    while (pcrv = inputSet.NextCurve())
    {   // Make sure the parent pointers are set and that the curves are clockwise
        pcrv->Complete(CCW) ; 
    }

    // Get outer loops from the shpofs curve set. 
    // Because the layer 21 shapes are oriented CW, the outer loops will be 
    // defined by doing a LEFT most chaining operation. This will feed back
    // the overall outer curve as well as any inner loops. 
    CS_IRECList ichnset ; 
    CS_CurveVecItr ic1, ic2 ; 
    for (ic1 = inputSet.crvlist.begin(); ic1 != inputSet.crvlist.end(); ic1++)
    {
        ic2 = ic1 ; 
        ic2++ ; 

        CS_IRECList ilst ; 
        while (ic2 != inputSet.crvlist.end())
        {
            (*ic1)->Intersect2D(*ic2, &ilst) ; 
            ic2++ ; 
        }
        CS_SortIntersectSetByUValue(ilst) ; 
        double tol=0.00001 ; 
        CS_DeleteCommonIntersections(ilst, &tol) ; 
        ichnset.splice(ichnset.end(), ilst) ; 

    }

    // Doing a delete common here may cause problems since the common intersections
    // would actually be from different curves so in the overall logic we should
    // be able to navigate safely from node to node even with these interesections
    // included in the curve pcnmap (chain map) structure. 
    // CS_DeleteCommonIntersections(ichnset) ; 

    CS_CurveSet outerloops ; 

    CS_Chain chn ;
    if (chaintol)
        chn.chntol = *chaintol ;
    if (revangtol)
        chn.revangtol = *revangtol ; 

    chn.AddIntersectDataToCurves(ichnset) ; 

    CS_CurveVecItr pcn = inputSet.crvlist.begin() ; 
    while (pcn != inputSet.crvlist.end())
    {
        pcrv = *pcn ; 
        if (pcrv->pcnmap)
        {   // Then check the next curve
            chn.SetFwdRevPointers(pcrv) ; 
            pcn++ ; 
        }
        else
        {   // No intersections with this curve, thus must delete it 
            // from processing for chaining but keep it as part of the 
            // final outer loop set. 
            nonIntersectedSet.AddCurve(pcrv) ; 
            pcn = inputSet.crvlist.erase(pcn) ; 
        }
    }

    int n = 0 ; 
    pcn = inputSet.crvlist.begin() ; 
    while (pcn != inputSet.crvlist.end())
    {
        chn.ChainAllLoops((*pcn)->pcnmap, intersectedSet, 
                CS_Chain::RIGHT | CS_Chain::FORWARDONLY | CS_Chain::WALKONCE) ; 
        pcn++ ; 
    }

    intersectedSet.InitIterator() ;
    while (pcrv = intersectedSet.NextCurve())
    {
        pcrv->Complete(CCW) ; 
        n++ ; 
    }

    // Must now filter out duplicate overlapped sets of chained curves






    return n ; // the number of newly created chained curves (intersectino curves)
}
