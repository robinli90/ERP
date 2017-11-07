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
// boolSetUnion.cpp

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <search.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"
#include "cs_booleans.h"
#include "cs_chain.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)     
#define CS_DEBUGU(a)    a 
#else
#define CS_DEBUG(a)
#define CS_DEBUGU(a)     
#endif



/*!
    This callback is specifically for the union operation of two curves. 
    If is used in CS_UnionCurves(...) below

    This test callback will only work when attempting to boolean two 
    curves together. To work on multiple curves at once the logic would
    have to be updated to search for the right most angle in other 
    curves in addition to the midpoint outside testing. 
 */
int BoolDirTestCallback(CS_ChainSTKListItr &istk, int mode) 
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;

    CS_ChainREC *pcrLastStep = istk->pChain->pcrFROM ; 
    CS_Curve *pLC = pcrLastStep->crvpnt.s->pParent ; // last curve section

    // The boolean union operation is looking to chain sections that are 
    // outside of the other curve. Typically we will alternate between one 
    // curve and the other but on overlp sections this may not be the case. 
    // Plus we always want to follow the forward direction (all curves must 
    // be oriented in the same direction for this to work). At the end there
    // will be curves in various directions. Those oriented in the same 
    // direction as the input curves are the outside union profiles. Those
    // going in the reverse direction to the input curves are holes within 
    // the overall union. 
    // If the next section on the next curve is not outside, then simply stay 
    // on the current curve. 




    /*
        Need a chain right rule if nothing is found in the main loop. In other words, 
        if it isn't possible to switch to a different outside curve from the current
        curve that we came from, then must determine which curve represents the 
        rightmost angle from where we are and follow that path, whether that is
        an inside point or not. Should also have another flag added to bIsInside
        called bIsOn. The bIsInside flag should only be set if bIsOn is not true for
        the curve being tested against. This will exactly filter out overlap curve
        situations. 

        NOTE: bIsOn was replaced with statPntFwd to handle more conditions. The
        rules ended up getting even more complex since the bIsOn condition must
        also be associated with a forward or reverse overlap intersection 
        condition and different actions taken depending on which is the case. 
     */
    

    CS_ChainRECListItr icrl ;
    CS_ChainREC *pcrSame = 0 ; // next node on same curve. 
    double angpick = RADIAN360 ; 

    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        CS_Curve *pCC = pcr->crvpnt.s->pParent ; 

        if (pCC == pLC)
        {
            pcrSame = pcr ; 
            continue ; // skip the current curve for now. 
        }

        if (!pcr->bIsInside && (pcr->fwdwalkcount == 0) &&
            !(pcr->statPntFwd & CS_ChainREC::PNTFWD_ONREV) && 
            !pcr->FWDAvoid() && tcomp_LT(pcr->fwdang, angpick, istk->pChain->angtol))
        {   // Then set this direction for now
            angpick = pcr->fwdang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }
    }

    if (!istk->pcrTO)
    {   // Then no path was found. This occured in the past before the statPntFwd logic
        // was added when there is an overlap section and the same curve could be 
        // followed to the next node. With the statPntFwd logic however, this should not
        // occur. I'm guessing it may be possible that in rare cases when we are 
        // "almost" folding back on ourselves that the FWDAvoid rule could have 
        // blocked the proper path, in which case we back off the rules to allow the 
        // near reversal direction

        if (!pcrSame->bIsInside && pcrSame->fwdwalkcount == 0)
        {
            istk->pcrTO = pcrSame ; 
            istk->direction = CS_FORWARD ; 
        }
        else
        {   // No next section found yet

            // TODO - may need to do another loop through here without the FWDAvoid()
            // condition in the if statement, if the above logic fails to set 
            // a next node. 

            int xx = 0 ; 
            xx++ ; 
        }
    }

    return 0 ; 
}


//! Version 2 of the call back test using the interior/exterior logic. 
/*!
    The statPntFwd flag PNTFWD_INSIDE is set when a segment is completely inside 
    one of the other curves. Refer to notes GEOM ALGO'S RR - Vol5 Pg 73
 */
int BoolDirTestCallback_V2(CS_ChainSTKListItr &istk, int mode) 
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;

    CS_ChainREC *pcrLastStep = istk->pChain->pcrFROM ; 
    CS_Curve *pLC = pcrLastStep->crvpnt.s->pParent ; // last curve section

    // The boolean union operation is looking to chain sections that are 
    // outside of the other curve. Typically we will alternate between one 
    // curve and the other but on overlp sections this may not be the case. 
    // Plus we always want to follow the forward direction (all curves must 
    // be oriented in the same direction for this to work). At the end there
    // will be curves in various directions. Those oriented in the same 
    // direction as the input curves are the outside union profiles. Those
    // going in the reverse direction to the input curves are holes within 
    // the overall union. 
    // If the next section on the next curve is not outside, then simply stay 
    // on the current curve. 




    /*
        Need a chain right rule if nothing is found in the main loop. In other words, 
        if it isn't possible to switch to a different outside curve from the current
        curve that we came from, then must determine which curve represents the 
        rightmost angle from where we are and follow that path, whether that is
        an inside point or not. Should also have another flag added to bIsInside
        called bIsOn. The bIsInside flag should only be set if bIsOn is not true for
        the curve being tested against. This will exactly filter out overlap curve
        situations. 

        NOTE: bIsOn was replaced with statPntFwd to handle more conditions. The
        rules ended up getting even more complex since the bIsOn condition must
        also be associated with a forward or reverse overlap intersection 
        condition and different actions taken depending on which is the case. 
     */
    

    CS_ChainRECListItr icrl ;
    CS_ChainREC *pcrSame = 0 ; // next node on same curve. 
    double angpick = RADIAN360 ; 

    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        CS_Curve *pCC = pcr->crvpnt.s->pParent ; 

        if (pCC == pLC)
        {
            pcrSame = pcr ; 
            continue ; // skip the current curve for now. 
        }

        if (!pcr->bIsInside && (pcr->fwdwalkcount == 0) &&
            tcomp_LT(pcr->fwdang, angpick, istk->pChain->angtol))
        {   // Then set this direction for now
            angpick = pcr->fwdang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }
    }

    if (!istk->pcrTO)
    {   // Then no path was found. This occured in the past before the statPntFwd logic
        // was added when there is an overlap section and the same curve could be 
        // followed to the next node. With the statPntFwd logic however, this should not
        // occur. I'm guessing it may be possible that in rare cases when we are 
        // "almost" folding back on ourselves that the FWDAvoid rule could have 
        // blocked the proper path, in which case we back off the rules to allow the 
        // near reversal direction

        if (!pcrSame->bIsInside && pcrSame->fwdwalkcount == 0)
        {
            istk->pcrTO = pcrSame ; 
            istk->direction = CS_FORWARD ; 
        }
        else
        {   // No next section found yet

            /*! 
                In this case something went wrong, either we started off on a section
                that wasn't really on the outside of all the other curves, or a direction
                selection failed to go the right way. From here we can:

                    1. Continue on the same section effectively ignoring the error
                    2. Return nothing, thus aborting the chaining 
                    3. Try to figure out what went wrong and adjust the decision rule
             */
            
            // TODO - may need to do another loop through here without the FWDAvoid()
            // condition in the if statement, if the above logic fails to set 
            // a next node. 

            int xx = 0 ; 
            xx++ ; 
        }
    }

    return 0 ; 
}




int CS_UnionCurveSet(CS_CurveSet &inset, CS_CurveSet &outset, CS_CurveSet &holeset, double *epstol)
{
    CS_Curve *pc ; 

    // ============================================================
    // ============= Initialize the input curve set ===============
    FILE *fp1 = 0 ; 
    if (chainDebugSaveCurves)                                    
        fp1 = fopen("c:\\tmp\\crvdat.txt", "wt") ;   

    inset.InitIterator() ; 
    while (pc = inset.NextCurve())
    {
        if (chainDebugSaveCurves)                                    
            pc->WriteCurveToFile(fp1) ; 
        pc->Complete(CCW) ; 
        pc->ClearChaining() ; 
        pc->SetBoundingRect() ; 
    }

    if (chainDebugSaveCurves)                                    
        fclose(fp1) ; 
    
    // ============================================================
    // ============= Intersect all the curves together ============

    // TODO - optimize this with a plane sweep vertex algorithm
    CS_IRECList ichainset ; 
    int i, j ; 
    for (i=0; i < (int)inset.size() - 1; i++) 
    {
        for (j=i+1; j < (int)inset.size(); j++)
            inset.crvlist[i]->Intersect2D(inset.crvlist[j], &ichainset) ; 
    }

    if (ichainset.size() <= 1)
    {   // ========================================================
        // None of the curves intersect each other (or two curves
        // touch at a single point which is ignored). Test if any 
        // of the curves are inside other curves. and return the 
        // set of all containing curves, with inner curves removed, 
        int cssize = (int)ichainset.size() ; 

        BoolCrvLst bcl ; 
        int cc = 0 ;
        inset.InitIterator() ; 
        while (pc = inset.NextCurve()) 
        {
            pc->XYarclength = 0 ; 
            bcl.AddNode(pc) ; 
        }


        BoolCurveNode *pi, *pj ; 
        pi = bcl.pStart ; 
        while (pi)
        {
            pj = pi->next ; 
            while (pj)
            {
                if (pi->pcrv->Inside(pj->pcrv->StartPoint()))
                {
                    pj = bcl.DelNode(pj, true) ; // true=keepCurve and just delete node 
                }
                else if (pj->pcrv->Inside(pi->pcrv->StartPoint()))
                {   
                    pi = bcl.DelNode(pi, true) ; // true=keepCurve and just delete node 
                    if (pi == pj)
                        pj = pj->next ; 
                }
                else
                {
                    pj = pj->next ; 
                }
            }

            pi = pi->next ; 
        }

        // All remaining curves are outer curves
        pi = bcl.pStart ; 
        while (pi)
        {
            outset.AddCurve(pi->pcrv->CopyCurve()) ;
            pi = pi->next ; 
        }
        return 0 ; // done
    }

    // Otherwise we've intersected at 2 or more points, thus it is 
    // possible to walk around the outside of the shape to create the 
    // union of the two parts. 

    // =================================================================
    //              CHAINING SETUP AND INITIALIZATION
    // =================================================================
    CS_Chain chn ; 
    chn.prcmode = CS_Chain::PRCMODE_EXACT ; 

    if (epstol)
        chn.chntol = *epstol ; 
    else
        chn.chntol = 0.001 ; 
    chn.AddIntersectDataToCurves(ichainset) ;

    // For all curves that do not have chain maps defined at this point
    // see if they are completely inside other curves and eliminate them
    // from consideration, otherwise save them to the output curve set. 
    // All curves that do have chaining data associated with them get 
    // added to the chncrvs vector so that they can be quickly iterated
    // through during processing later on. 
    for (i=0; i < (int)inset.size(); i++) 
    {
        if (inset.crvlist[i]->pcnmap == 0)
        {   // Need to see if this is inside any other curves
            CS_POINT sp = inset.crvlist[i]->StartPoint() ;
            bool isInside = false ; 

            for (j=0; j < (int)inset.size(); j++)
            {
                if (i == j)
                    continue ; 
                if (inset.crvlist[j]->Inside(sp))
                {
                    isInside = true ; 
                    break ; 
                }
            }

            if (!isInside)
            {   // Then save this curve as part of the output set 
                outset.AddCurve(inset.crvlist[i]->CopyCurve()) ; 
            }
        }
        else
        {   // Else include this as part of the chaining set curves
            // to be considered during processing. 
            chn.chncrvs.push_back(inset.crvlist[i]) ;
        }
    }

    // The final step 

    inset.InitIterator() ; 
    while (pc = inset.NextCurve())
        chn.SetFwdRevPointers(pc) ; 
    chn.SetAllFwdMidPoints() ; 
    chn.chnmode |= CS_Chain::ALLOWREVERSALS ;
    // chn.cbfunc = BoolDirTestCallback ; 
    chn.cbfunc = BoolDirTestCallback_V2 ; 

    // =================================================================
    //              DONE SETUP AND INITIALIZATION
    // =================================================================


    // Ideally we want to start on a section on one shape that is outside
    // of the other so that the first complete walk around gives us the final
    // result. To do this we find a chain section where the midpoint is outside
    // of the other curve. 
    // The chainnode map pcnmap attached to the curve is sorted by U value 
    // of the intersection points. Thus this can be used to figure out what
    // section is on the outside
    
    // ================================================================
    // Everything is now setup to run. From here we want to walk forward
    // and ChainLoop all sections that are outside of all other curves. 
    // Finding pntFwdMid points that are outside all the other sections
    // is an O(N^2) operation worst case since we have to test against 
    // every  other curve each time. This can be optimized somewhat by
    // skipping sections that have a forward walkcount > 0. 

    // Work through all the stack lists until we've walked all the outside 
    // chainrec sections. 
    CS_ChainSTKListItr ics ; 
    int chainingMode = CS_Chain::CUSTOM | CS_Chain::FORWARDONLY | CS_Chain::WALKONCE ;

    for (ics = chn.stklst.begin() ; ics != chn.stklst.end(); ics++)
    {   // Work through each ChainREC in this stack
        CS_ChainRECListItr icr ; 
        for (icr = ics->creclist.begin(); icr != ics->creclist.end(); icr++)
        {  
            CS_ChainREC *pcr = *icr ;
            if (!pcr->bIsInside && pcr->fwdwalkcount == 0)
                
                // Removed Oct 9, 2010
                //  && !(pcr->statPntFwd & CS_ChainREC::PNTFWD_ONREV)) 

                // This used to be part of the rule but was removed, See Geom Algos 5 Pg 69
                // && !(pcr->origstatus & CS_ChainREC::OVRLAPSTART))
            {   // Then create chain from here
                int chainret = chn.ChainLoop(pcr, CS_FORWARD, chainingMode) ;  

                if (chainret == 1)
                {   // Then the union operation worked normally
                    chn.BuildChainCurve() ;
                    if (chn.pchncrv)
                    {   // Then something was generated. 
                        if (chn.pchncrv->nodecnt > 1 && chn.pchncrv->Closed())
                        {   // Then this is a valid chained region
                            double area = chn.pchncrv->Area() ; 
                            if (area > 0) 
                            {   // This is the final result curve that we want
                                if (chainDebugSaveCurves)                                    
                                {                                                            
                                    FILE *fp1 = fopen("c:\\tmp\\crvdat.txt", "at") ;   
                                    chn.pchncrv->WriteCurveToFile(fp1) ; 
                                    fclose(fp1) ; 
                                }

                                outset.AddCurve(chn.pchncrv) ; 
                                chn.pchncrv = 0 ;  // so that it isn't de-alloced later
                            }
                            else if (area < 0) 
                            {   // area is less than zero meaning this is a hole
                                // If there is a curve and it has only one node, then 
                                // something went wrong, so delete it and signal error
                                if (chainDebugSaveCurves)                                    
                                {                                                            
                                    FILE *fp1 = fopen("c:\\tmp\\crvdat.txt", "at") ;   
                                    chn.pchncrv->WriteCurveToFile(fp1) ; 
                                    fclose(fp1) ; 
                                }

                                holeset.AddCurve(chn.pchncrv) ;
                                chn.pchncrv = 0 ;  // so that it isn't de-alloced later
                            }
                            else
                            {
                                if (chainDebugSaveCurves)                                    
                                {                                                            
                                    FILE *fp1 = fopen("c:\\tmp\\crvdat.txt", "at") ;   
                                    chn.pchncrv->WriteCurveToFile(fp1) ; 
                                    fclose(fp1) ; 
                                }

                                delete chn.pchncrv ; 
                                chn.pchncrv = 0 ;  // reset so a second delete isn't attempted
                            }
                        }
                        else
                        {   // Something wrong with the curve. This should be flagged
                            // as an error condition. 
                            delete chn.pchncrv ; 
                            chn.pchncrv = 0 ;  // reset so a second delete isn't attempted
                        }
                    }
                }
                //  else if (chainret == 2)  // then aborted the chaining
            }
        }
    }

    return (int)outset.size() ; 
}


/*
// See GEOM ALGO's RR-Vol5 Pg 42.
int CS_UnionCurveSet(CS_CurveSet &inset, CS_CurveSet &outset, CS_CurveSet &holeset)
{
    // First create a linked list out of the input set. 
    CS_Curve *pcrv ; 
    inset.InitIterator() ; 

    BoolCrvLst bcl ; 
    int cc = 0 ;
    CS_DEBUGU(
        FILE *fpu = fopen("C:\\tmp\\inputcrv.txt", "wt") ; 
    ) ; 

    while (pcrv = inset.NextCurve()) 
    {
        pcrv->XYarclength = 0 ; 
        bcl.AddNode(pcrv) ; 

        CS_DEBUGU(
            pcrv->WriteCurveToFile(fpu) ; 
            fflush(fpu) ; 
        ) ; 
    }

    CS_DEBUGU(
        fclose(fpu) ; 
    ) ; 


    BoolCurveNode *pi, *pj ; 
    pi = bcl.pStart ; 

    CS_Curve *puc ; // temp union work curve. 
    
    // We have to keep looping through the entire set until no curve merges
    // take place (meaning nothing intersects with anything else anymore. 

    bool mergedCurves = false ; 
    while (pi)
    {
        pj = pi->next ; 
        while (pj)
        {
            int ret = CS_UnionCurves(pi->pcrv, pj->pcrv, &puc) ; 
            if (ret & 0x07)
            {   // Then we intersected something, so overwrite pi and delete pj
                puc->XYarclength = -1 ; // must de-allocate later
                if (tcomp_EQ(pi->pcrv->XYarclength, -1.0))
                    delete pi->pcrv ;
                pi->pcrv = puc ; 
                pi->pcrv->ClearChaining() ; // reset for next union operation
                pj = bcl.DelNode(pj, true) ; // true=keepCurve
                
                mergedCurves = true ; // we did something
            }
            else
            {   // Nothing happened with pj so just keep testing
                pi->pcrv->ClearChaining() ; 
                pj->pcrv->ClearChaining() ; 
                pj = pj->next ; 
            }
        }

        pi = pi->next ; 
        if (!pi && mergedCurves)
        {   // Then we need to start over again just to make sure that 
            // everything has been connected together. 
            pi = bcl.pStart ; 
            mergedCurves = false ; // reset for the next run through the set. 
        }
    }

    // The final result set can now be saved in the outset. 

    CS_DEBUGU(
        fpu = fopen("C:\\tmp\\outputcrv.txt", "wt") ; 
    ) ; 

    pi = bcl.pStart ; 
    while (pi)
    {
        outset.AddCurve(pi->pcrv->CopyCurve()) ; 
        if (tcomp_EQ(pi->pcrv->XYarclength, -1.0))
            delete pi->pcrv ;
        pi = pi->next ; 
    }

    CS_DEBUGU(
        outset.InitIterator() ; 
        cc = 0 ;
        while (pcrv = outset.NextCurve())
        {
            pcrv->WriteCurveToFile(fpu) ; 
            fflush(fpu) ; 
        }
    ) ; 


    CS_DEBUGU(
        fclose(fpu) ; 
    ) ; 

    return 0 ; 
}
*/

// WARNING ; USE THE CS_UnionCurveSets(...) version which is much more reliable. 
int CS_UnionCurves(CS_Curve *pca, CS_Curve *pcb, CS_Curve **pcu, CS_CurveSet &holeSet)
{
    pca->Complete(CCW) ; 
    pcb->Complete(CCW) ; 

    if (chainDebugSaveCurves)                                    
    {                                                            
        FILE *fp1 = fopen("c:\\tmp\\crvdat.txt", "wt") ;   
        pca->WriteCurveToFile(fp1) ; 
        pcb->WriteCurveToFile(fp1) ; 
        fclose(fp1) ; 
    }


    // Make use of chaining
    CS_IRECList ichainset ; 
    int nisects = pca->Intersect2D(pcb, &ichainset) ; 

    if (ichainset.size() == 0)
    {   // Test if one inside the other
        if (pca->Inside(pcb->pStart->StartPoint()))
        {
            *pcu = pca->CopyCurve() ; 
            return 0x02 ; 
        }

        if (pcb->Inside(pca->pStart->StartPoint()))
        {
            *pcu = pcb->CopyCurve() ; 
            return 0x04 ; 
        }
        
        // no intersection at all 
        return 0 ; 
    }
    else if (ichainset.size() == 1)
    {   // Then the curves touch at a point perhaps tangent arcs or
        // at a corner. This means that they don't really intersect
        return 0x08 ; 
    }
    else
    {   // Must test for the special case where the two curves completely 
        // overlap one another and thus have multiple overlap intersections
        // but are effectively identical. 
        // For this to be true, all intersects must be overlap types. 
        CS_IRECListItr iri = ichainset.begin() ; 
        bool foundSingleIntersect = false ; 
        while (iri != ichainset.end())
        {
            CS_INODE *pin = &(*iri) ; 
            if (!pin->Overlap())
            {
                foundSingleIntersect = true ; 
                break ; 
            }
            iri++ ; 
        }

        if (!foundSingleIntersect)
        {   // Then all intersections are overlap type and the curves are 
            // identical, so simply return the A curve
            *pcu = pca->CopyCurve() ; 
            return 0x06 ; 
        }
    }

    // Otherwise we've intersected at 2 or more points, thus it is 
    // possible to walk around the outside of the shape to create the 
    // union of the two parts. 

    CS_Chain chn ; 
    chn.chntol = 0.001 ; 
    chn.AddIntersectDataToCurves(ichainset) ; 
    chn.SetFwdRevPointers(pca) ; 
    chn.SetFwdRevPointers(pcb) ; 
    chn.SetAllFwdMidPoints() ; 
    chn.chnmode |= CS_Chain::ALLOWREVERSALS ;
    chn.prcmode = CS_Chain::PRCMODE_EXACT ; 
    chn.cbfunc = BoolDirTestCallback ; 

    // Ideally we want to start on a section on one shape that is outside
    // of the other so that the first complete walk around gives us the final
    // result. To do this we find a chain section where the midpoint is outside
    // of the other curve. 
    // The chainnode map pcnmap attached to the curve is sorted by U value 
    // of the intersection points. Thus this can be used to figure out what
    // section is on the outside
    
    CS_ChnNodeMapItr icstart ;
    // icS->icT are the from-to pairs used to find a valid starting section. 
    // These pairs are walked around all sections of the A curve. 
    // The valid starting section has to be a non-overlap section that is outside
    // of the other curve (midpoint not contained/inside in other curve)
    CS_ChnNodeMapItr icS = pca->pcnmap->begin() ; 
    CS_ChnNodeMapItr icT = icS ; 
    icT++ ; 

    if (icT == pca->pcnmap->end())
        return 0 ; // something went wrong, curves only touched at a single point

    // ==============================================================
    // Everything is now setup. Next find a section of curve that is 
    // outside of the other curve and also doesn't overlap the other 
    // curve. The only time this condition will not exist is when the 
    // two curves overlap completely, and that has been filtered out
    // before we get to here. So if we can't find an exterior starting
    // section at this point, then something went wrong and no result 
    // we be returned. 
    // ==============================================================
    // Find the proper starting section

    // All sections that are outside the other curve need to be walked
    // once for chaining in order to extract the outside curve as 
    // well as all the possible inner hole curves that may result. 
    // A hole is determined by it's orientation being reversed from 
    // the input curves which are CCW. Thus CW result curves must be
    // holes. 

    bool bFoundStart = false ; 
    while (icS != pca->pcnmap->end())
    {   // Take the midpoint of the section for testing the start node
        double u = pca->UMid(icS->second.ucrv, icT->second.ucrv) ; 
        CS_POINT tstpnt = pca->UPoint(u) ; 
        if (!(icS->second.pcr->origstatus & CS_ChainREC::OVRLAPSTART) 
                        && !pcb->Inside(icS->second.pcr->pntFwdMid))
        {   // Then we want to start from the icT record node since the next
            // step in the forward direction from b will be outside of the 
            // other curve. 
            icstart = icS ; 
            bFoundStart = true ; 
            break ; 
        }

        icS++ ; 
        icT++ ; 
        if (icT == pca->pcnmap->end() && pca->Closed())
            icT = pca->pcnmap->begin() ; // wrap around for the B only. 
    }

    if (!bFoundStart)
        return 0 ; // should never get here. TODO - log warning or error. 
        
    int chainret = chn.ChainLoop(icstart->second.pcr, CS_FORWARD, 
                        CS_Chain::CUSTOM | 
                        CS_Chain::FORWARDONLY | 
                        CS_Chain::WALKONCE) ;

    if (chainret == 1)
    {   // Then the union operation worked normally
        chn.BuildChainCurve() ;
    }
    else if (chainret == 2)
    {   // Aborted the chaining

    }

    if (chn.pchncrv && chn.pchncrv->nodecnt > 1)
    {   // This is the final result curve that we want
        *pcu = chn.pchncrv ; 

        if (chainDebugSaveCurves)                                    
        {                                                            
            FILE *fp1 = fopen("c:\\tmp\\crvdat.txt", "at") ;   
            chn.pchncrv->WriteCurveToFile(fp1) ; 
            fclose(fp1) ; 
        }

        return 0x01 ; 
    }
    else if (chn.pchncrv)
    {   // If there is a curve and it has only one node, then 
        // something went wrong, so delete it and signal error
        delete chn.pchncrv ;
    }

    return 0 ; 
}



















