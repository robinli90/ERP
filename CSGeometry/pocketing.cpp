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
// pocketing.cpp

#pragma warning( disable : 4786 )

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
#include "cs_chain.h"
#include "cs_pocketing.h"


CS_Pocketing::CS_Pocketing()
{
    maxDecentDepth = 100000 ; 
    maxdepth = 0 ; 
    mode = 0 ; 
    toolrad = 0 ;        // radius of tool
    stepPercentage = 0 ; // step for each cut pass
    zrapid = 0 ;         // non cutting sections at this height
    zcut = 0 ;           // cutting sections at this depth

    topnode = 0 ; 
    pBndCurve = 0 ; 
    pIslandCurveSet = 0 ;  
}


CS_Pocketing::~CS_Pocketing()
{
    DeleteTree(topnode) ;
    delete topnode ; 
}


void CS_Pocketing::DeleteTree(CS_TPTNode *pnode)
{
    if (!pnode)
        return ; 
    if (pnode->nOffsets)
    {
        for (int i=0; i < pnode->nOffsets; i++)
            DeleteTree(&pnode->offsnodes[i]) ; 
        delete[] pnode->offsnodes ;
    }
}

// The input is defined by the curves in the boundaries. The boundary 
// curve defines the outside limit is offset in towards the center.
// The islands curveset define those island boundaries which are offset
// out and must be avoided when pocketing the outside boundary.
// The resultant tool path is returned as a single connected curve. 
// If uncut areas are required, then call the individual routines 
// which build the toolpath separately so that intermediate data 
// can be saved (uncut curves etc...)

void CS_Pocketing::ContourPocket(CS_Curve *pbndcrv,
                                 CS_CurveSet *islands, 
                                 CS_Curve *toolpathcrv)
{
    // Want to create the tree as we offset the various curves
    CS_Curve *pcrv, *pc, *pci ; 

    // Make sure the curves are oriented in the proper direction
    pIslandCurveSet = islands ;
    pIslandCurveSet->InitIterator() ; 
    while (pcrv = pIslandCurveSet->NextCurve())
    {
        pc = new CS_Curve ; 
        pc->CopyCurve(*pcrv) ; 
        if (!pc->Closed())
        {
            CS_LineSeg *pls = new CS_LineSeg(pc->EndPoint(), pc->StartPoint()) ;
            pc->Append(pls) ; 
        }
        pc->Complete(CCW) ; 
        double tol = COMPARETOLERANCE * 5.0 ;
        pc->OffsetSlow(toolrad, islandSet, &tol) ;
        // pc->Offset(toolrad, islandSet) ;
        delete pc ; 
    }

    islandSet.InitIterator() ; 
    while (pci = islandSet.NextCurve())
    {   // Orient all the island curves CW so that the chaining 
        // functions work properly. 
        pci->statflags &= ~CS_ISLANDDELETED ; // clear this bit
        pci->ConnectEndPoints() ; 
        pci->Complete(CW) ; 
    }

    pBndCurve = pbndcrv ; // save this pointer
    topnode = new CS_TPTNode ; 
    topnode->pcrv = new CS_Curve ; 
    topnode->pcrv->CopyCurve(*pbndcrv) ; 
    topnode->pcrv->Complete(CCW) ; 
    topnode->depth = 0 ; 

    // Build the tree
    OffsetNode(topnode) ; 


    // Test mode - generate all the curve segments in the single output
    // curve 
    LoopsToCurves(*toolpathcrv) ; 
}



// The islandSet is modified as this function is called,
// when an island curve is intersected during an offset 
// and becomes part of the offset chain, it is remoived
// from the island set since it now is part of the offset
// node tree. This routine calls itself recursively until 
// the offset results in a NULL result. 
// This is a recursive function. The islandSet is shared 
// since it is passed by reference, thus make sure no
// pointers are maintained through recursive calls. Modify
// island set and clean it up completely before the next
// recursive call.
int CS_Pocketing::OffsetNode(CS_TPTNode *pnode)
{
    // Offset the boundary curve, intersect it with the 
    // islands, and any island curves that are consumed in the 
    // processed are deleted from the island set. All complete
    // curves generated are added to the offsnodes array wihin
    // pnode.

    // DEBUG 
    if (pnode->depth > maxDecentDepth)
        return 0 ; 

    if (maxdepth < pnode->depth)
        maxdepth = pnode->depth ; 

    CS_CurveSet ofscrvset ;
    pnode->pwrkcrv = new CS_Curve ; 
    pnode->pwrkcrv->CopyCurve(*(pnode->pcrv)) ; 
    
    double tol = COMPARETOLERANCE * 5.0 ; 
    pnode->pwrkcrv->OffsetSlow(-toolrad, ofscrvset, &tol) ;
    // pnode->pwrkcrv->Offset(-toolrad, ofscrvset) ;

    if (ofscrvset.Count() == 0)
    {
        delete pnode->pwrkcrv ; 
        pnode->pwrkcrv = 0 ; 
        return 0 ; // done this branch
    }

    // The offset curves are transferred to one of two lists
    // depending on whether or not they intersected with any 
    // of the island curves.
    CS_CurveVec isectcrvnodeList ; 
    CS_CurveVec newNodeCrvList ; 
    CS_CurveVec islandISectCrvList ; 

    CS_Curve *pcrv, *poffscrv ; 

    CS_IRECList allIntersects ; 
    int i ; 
    ofscrvset.InitIterator() ; 
    while (poffscrv = ofscrvset.RemoveNextCurve())
    {
        if (!poffscrv->Closed())
            delete poffscrv ;
        else
        {
            poffscrv->ConnectEndPoints() ;
            poffscrv->Complete(CCW) ;
            // Intersect it with each of the island curves
            bool bOffsetDidIntersect = false ;
            islandSet.InitIterator() ;
            while (pcrv = islandSet.NextCurve())
            {
                CS_IRECList islist ;
                poffscrv->Intersect2D(pcrv, &islist) ;
                if (islist.size() > 1)
                {   // Then we want to include the island in the
                    // processing of the chaining. If the count is 1
                    // then we had a tangent intersection of an arc
                    // at a single point in which case we don't want
                    // to process the island curve at all.
                    bOffsetDidIntersect = true ;
                    pcrv->statflags |= CS_ISLANDDELETED ; 
                    allIntersects.splice(allIntersects.end(), islist) ; 
                    islandISectCrvList.push_back(pcrv) ; 
                }
            }
            if (!bOffsetDidIntersect)
                newNodeCrvList.push_back(poffscrv) ; 
            else
                isectcrvnodeList.push_back(poffscrv) ; 
        }
    }

    if ((newNodeCrvList.size() == 0) && (isectcrvnodeList.size() == 0))
    {   
        return 0 ; 
    }

    // Chain the various island loops together with the offset loops

    CS_Chain chn ; 
    chn.AddIntersectDataToCurves(allIntersects) ;
    

    CS_CurveVecItr icv ; 
    for (icv = isectcrvnodeList.begin() ; icv != isectcrvnodeList.end(); icv++)
        chn.SetFwdRevPointers(*icv) ; 

    for (icv = islandISectCrvList.begin() ; icv != islandISectCrvList.end(); icv++)
        chn.SetFwdRevPointers(*icv) ; 

    // Create the chains
    CS_CurveSet chainLoops ; 

    for (icv = isectcrvnodeList.begin() ; icv != isectcrvnodeList.end(); icv++)
        chn.ChainAllLoops((*icv)->pcnmap, chainLoops, CS_Chain::LEFT | CS_Chain::FORWARDONLY) ; 

    // Create child nodes as required
    if (chainLoops.Count() > 0)  
    {
        chainLoops.InitIterator() ; 
        while (pcrv = chainLoops.RemoveNextCurve())
        {
            newNodeCrvList.push_back(pcrv) ; 
        }
    }


    if (newNodeCrvList.size() > 0)  
    {
        pnode->nOffsets = (int)newNodeCrvList.size() ;
        pnode->offsnodes = new CS_TPTNode[pnode->nOffsets] ; 
        
        i = 0 ; 
        for (icv = newNodeCrvList.begin(); icv != newNodeCrvList.end(); icv++)
        {
            pnode->offsnodes[i].pcrv = *icv ; 
            pnode->offsnodes[i].depth = pnode->depth + 1 ; 
            i++ ; 
        }
    }

    // Delete the island curves that have been intersected and used 
    // in the loop chains
    for (icv = islandISectCrvList.begin() ; icv != islandISectCrvList.end(); icv++)
        islandSet.DeleteCurve(*icv) ; 

    if (pnode->nOffsets > 1)
        i += 1 ; 

    for (i=0; i < pnode->nOffsets; i++)
        OffsetNode(&pnode->offsnodes[i]) ;

    return 0 ;
}



int CS_Pocketing::LoopsToCurves(CS_Curve &crv) 
{
    crv.Reset() ; 
    pOutputCurve = &crv ; 
    AddNodeToOutputCurve(topnode) ; 
    return 0 ;
}


int CS_Pocketing::AddNodeToOutputCurve(CS_TPTNode *pnode)
{
    for (int i=0; i < pnode->nOffsets; i++)
        AddNodeToOutputCurve(&pnode->offsnodes[i]) ; 
    CS_Curve *pc = new CS_Curve ; 
    pc->CopyCurve(*pnode->pcrv) ; 
    pOutputCurve->AddCurve(pc, CS_NOENDPOINTADJUSTMENT) ; 
    return 0 ; 
}


