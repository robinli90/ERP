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
// boolSetDiff.cpp


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
#define CS_DEBUG(a)     a
#else
#define CS_DEBUG(a)
#endif


int CS_CurveSetDiff(CS_Curve &crvA, CS_CurveSet &csB, CS_CurveSet &diffSet, CS_CurveSet &holes) 
{
    crvA.Complete(CCW) ; 

    CS_Curve *pcrv ; 

    // Any B's that don't intersect with A are saved for hole testing at the end. 
    CS_CurveVec holetestVec ; 

    // Make use of chaining
    CS_IRECList ichainset ; 

    int nisects ; 
    csB.InitIterator() ; 
    while (pcrv = csB.NextCurve())
    {
        CS_IRECList isset ; 
        pcrv->Complete(CW) ; 
        nisects = crvA.Intersect2D(pcrv, &isset) ; 

        if (isset.size() == 0)
        {
            holetestVec.push_back(pcrv) ; 
        }
        else
        {   // Keep building the intersection set. 
            CS_AppendIRECList(ichainset, isset) ; 
        }
    }

    // Otherwise we've intersected at 2 or more points, thus it is 
    // possible to walk around the outside of the shape to create the 
    // union of the two parts. 

    int ret = 0 ; 

    if (ichainset.size())
    {
        CS_Chain chn ; 
        chn.chntol = 0.001 ; 
        chn.AddIntersectDataToCurves(ichainset) ; 
        chn.SetFwdRevPointers(&crvA) ; 
        csB.InitIterator() ; 
        while (pcrv = csB.NextCurve())
            chn.SetFwdRevPointers(pcrv) ; 

        // Now chain all loops, always go left, and go in the forward direction only. 

        // Used for debug, look at the chain map for the A curve
        // CS_ChnNode *chnnd[32] ; 
        // int kk = 0 ; 
        // CS_ChnNodeMapItr  icm = crvA.pcnmap->begin() ; 
        // while (icm != crvA.pcnmap->end())
        // {
        //     chnnd[kk++] = &(icm->second) ; 
        //     icm++ ; 
        // }

        ret = chn.ChainAllLoops(crvA.pcnmap, diffSet, 
                        CS_Chain::LEFT | CS_Chain::FORWARDONLY | CS_Chain::WALKONCE) ;
    }
    else
    {   // There were no intersections, this means all the csB curves are either inside
        // the A curve, or completely outside the A curve. Either way, the A curve is 
        // going to be part of the solution set. 
        diffSet.AddCurve(crvA.CopyCurve()) ; 
    }

    for (int i=0; i < (int)holetestVec.size(); i++)
    {
        diffSet.InitIterator() ; 
        while (pcrv = diffSet.NextCurve())
        {
            if (pcrv->Inside(holetestVec[i]->StartPoint()))
            {
                CS_Curve *phc = holetestVec[i]->CopyCurve() ; 
                phc->pUserData = pcrv ; 
                holes.AddCurve(phc) ;
                break ; // the hole could only be inside one curve so exit
            }
        }
    }

    return ret ; 
}


// copied from CS_FindLeftChain(...) where we add the logic to not 
// follow inside sections. Plus we are only considering foward direction here, 
// and walk once is implied automatically as well. 
int BoolDiffChainCallback(CS_ChainSTKListItr &istk, int mode)
{
    istk->pcrTO = 0 ; 
    istk->direction = 0 ;
    // Looking for largest angle.
    double angpick = -RADIAN360 ; 
    CS_ChainRECListItr icrl ;
    for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
    {
        CS_ChainREC *pcr = *icrl ;         
        if ((pcr->fwdwalkcount == 0) && !pcr->bIsInside && 
                !pcr->FWDAvoid() && tcomp_GT(pcr->fwdang, angpick, istk->pChain->angtol))
        {
            angpick = pcr->fwdang ;
            istk->pcrTO = pcr ; 
            istk->direction = CS_FORWARD ; 
        }
    }

    if (istk->pcrTO == 0)
    {   // Slack off the requirements
        for (icrl = istk->creclist.begin(); icrl != istk->creclist.end(); icrl++)
        {
            CS_ChainREC *pcr = *icrl ;         
            if ((pcr->fwdwalkcount == 0) && !pcr->bIsInside && 
                 !pcr->FWDBlocked() && tcomp_GT(pcr->fwdang, angpick, istk->pChain->angtol))
            {
                angpick = pcr->fwdang ;
                istk->pcrTO = pcr ; 
                istk->direction = CS_FORWARD ; 
            }
        }
    }

    if (istk->pcrTO == 0)
        return CS_Chain::CUSTOMABORT ; 

    return 0 ; 
}



int CS_CurveSetDiff2(CS_Curve &crvA, CS_CurveSet &csB, CS_CurveSet &diffSet, CS_CurveSet &holes) 
{
    crvA.Complete(CCW) ; 

    // First merge all the subtraction curves into largest possible blocks
    CS_CurveSet subset, holeSet ; 
    CS_UnionCurveSet(csB, subset, holeSet) ; 
    // ignore holes for now TODO: add the holes back in later as required
    // To do this loop through holeSet and if inside crvA then add it to the 
    // diffset since this something that shouldn't have been subtracted out. 

    CS_Curve *pcrv ; 

    // Any B's that don't intersect with A are saved for hole testing at the end. 
    CS_CurveVec holetestVec ; 

    CS_CurveVec subtractSet ; 
    // Make use of chaining
    CS_IRECList ichainset ; 

    int nisects ; 
    subset.InitIterator() ; 
    while (pcrv = subset.NextCurve())
    {
        CS_IRECList isset ;
        pcrv->Complete(CW) ;
        nisects = crvA.Intersect2D(pcrv, &isset) ;

        if (isset.size() == 0)
        {
            holetestVec.push_back(pcrv) ;
        }
        else
        {   // Keep building the intersection set. 
            CS_AppendIRECList(ichainset, isset) ; 
            subtractSet.push_back(pcrv) ; // remember for later
        }
        // Initialize since we need it later 
        pcrv->SetBoundingRect() ; 
    }

    // Otherwise we've intersected at 2 or more points, thus it is 
    // possible to walk around the outside of the shape to create the 
    // union of the two parts. 

    int ret = 0 ; 

    if (ichainset.size())
    {
        CS_Chain chn ; 
        chn.chntol = 0.001 ; 
        chn.chnmode |= CS_Chain::ALLOWREVERSALS ; // THIS IS IMPORTANT.

        chn.AddIntersectDataToCurves(ichainset) ; 
        chn.SetFwdRevPointers(&crvA) ; 
        subset.InitIterator() ; 
        while (pcrv = subset.NextCurve())
            chn.SetFwdRevPointers(pcrv) ;
        chn.cbfunc = BoolDiffChainCallback ; 

        /////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////
        // Set up the is inside data for the primary curve. 
        /////////////////////////////////////////////////////////////////////
        CS_ChnNodeMapItr icn ; 
        for (icn = crvA.pcnmap->begin(); icn != crvA.pcnmap->end(); icn++)
        {
            CS_ChainREC *pcr = icn->second.pcr ; 
            double ua = pcr->ucrv ; 
            double ub ; 
            CS_ChainREC *pcrnext = CS_NextChainRECNode(pcr, CS_FORWARD) ; 
            if (!pcrnext)
            {   // This is an error, show flag user, simply use ua as ub value
                ub = ua ; 
            }
            else
            {   // We have the next point in the chain. 
                ub = pcrnext->ucrv ; 
            
            }
            CS_Curve *pc = pcr->crvpnt.s->pParent ; 
            pcr->pntFwdMid = pc->UPoint(pc->UMid(ua, ub)) ; 
            pcr->bIsInside = false ; 
            pcr->statPntFwd = 0 ; 

            // TODO - may need to filter out the ON condition and leave as false
            // if ON but not INSIDE. 
            for (int i=0; i < (int)subtractSet.size(); i++)
            {
                pcrv = subtractSet[i] ; 
                if (pcrv->Inside(pcr->pntFwdMid, 0, 1))
                {
                    pcr->bIsInside = true ; 
                    break ; 
                }
            }
        }

        /////////////////////////////////////////////////////////////////////
        // Set up the is inside data for the subtraction set curves. Even though
        // subtraction curves may be inside other shapes, in this context it is 
        // OK to follow these sections. Only inside sections on the primary 
        // curve cannot be followed. 
        for (int i=0; i < (int)subtractSet.size(); i++)
        {
            pcrv = subtractSet[i] ;
            if (pcrv->pcnmap)
            {
                for (icn = pcrv->pcnmap->begin(); icn != pcrv->pcnmap->end(); icn++)
                    icn->second.pcr->bIsInside = false ; 
            }
        }



        // Done bIsInside setup 
        /////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////

        // Now chain all loops, always go left, and go in the forward direction only. 

        // Used for debug, look at the chain map for the A curve
        // CS_ChnNode *chnnd[32] ; 
        // int kk = 0 ; 
        // CS_ChnNodeMapItr  icm = crvA.pcnmap->begin() ; 
        // while (icm != crvA.pcnmap->end())
        // {
        //     chnnd[kk++] = &(icm->second) ; 
        //     icm++ ; 
        // }

        CS_CurveSet tmpDiffSet ;
        ret = chn.ChainAllLoops(crvA.pcnmap, tmpDiffSet, 
                    CS_Chain::CUSTOM | CS_Chain::FORWARDONLY | 
                    CS_Chain::WALKONCE | CS_Chain::STARTOUTSIDE) ;

        // NOTE: FORWARDONLY and WALKONCE are not needed since the custom callback
        // performs those function automatically. 

        // Go through and verify that the diffset curves are valid
        tmpDiffSet.InitIterator() ; 
        while (pcrv = tmpDiffSet.RemoveNextCurve())
        {
            double A = pcrv->Area() ; 
            if (A > 0)
                diffSet.AddCurve(pcrv) ; 
            else 
                delete pcrv ; // throw it out. 
        }

    }
    else
    {   // There were no intersections, this means all the subset curves are either inside
        // the A curve, or completely outside the A curve. Either way, the A curve is 
        // going to be part of the solution set, except for the case where the csB curves
        // completely contain crvA. 
        bool crvAInsideSubSet = false ; 
        subset.InitIterator() ; 
        while (pcrv = subset.NextCurve())
        {
            if (pcrv->Inside(crvA.StartPoint()) && 
                pcrv->Inside(crvA.MidPoint()))
            {
                crvAInsideSubSet = true ; 
                break ; 
            }
        }
        
        if (!crvAInsideSubSet)
            diffSet.AddCurve(crvA.CopyCurve()) ; 
    }

    for (int i=0; i < (int)holetestVec.size(); i++)
    {
        diffSet.InitIterator() ; 
        while (pcrv = diffSet.NextCurve())
        {
            if (pcrv->Inside(holetestVec[i]->StartPoint()))
            {
                CS_Curve *phc = holetestVec[i]->CopyCurve() ; 
                phc->pUserData = pcrv ; 
                holes.AddCurve(phc) ;
                break ; // the hole could only be inside one curve so exit
            }
        }
    }

    return ret ; 
}
