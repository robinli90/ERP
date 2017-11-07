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
// outerbounds.cpp


#pragma warning( disable : 4786 )
// #pragma warning( disable : 4800 )

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_chain.h"
#include "cs_geomalgos.h"


// Note the function CS_CreateIntersectionSet(...) is almost identical to this one
int CS_CreateOuterBoundaries(CS_CurveSet &inset, CS_CurveSet &outset)
{
    // To do this we must first make sure that all the curves form 
    // closed loops. Each loop is then oriented CCW so that a chain 
    // right will follow the periphery of the curve set.

    CS_CurvePtr pcrv ; 
    inset.InitIterator() ; 
    while (pcrv = inset.NextCurve())
        pcrv->Complete() ; 

    // Set up for chaining all the curves into outside loops. 
    CS_IRECList irlist ; 
    unsigned int i, j  ; 
    for (i=0; i < inset.crvlist.size() - 1; i++)
    {
        CS_IRECList irlcrv ; 
        for (j=i+1; j < inset.crvlist.size(); j++)
        {
            inset.crvlist[i]->Intersect2D(inset.crvlist[j], &irlcrv) ; 
        }
        CS_SortIntersectSetByUValue(irlcrv) ; 
        CS_DeleteCommonIntersections(irlcrv) ; 
        irlist.splice(irlist.end(), irlcrv) ; 
    }

    CS_Chain chn ;
    chn.AddIntersectDataToCurves(irlist) ;

    inset.InitIterator() ;
    while (pcrv = inset.NextCurve())
        chn.SetFwdRevPointers(pcrv) ;
    

    inset.InitIterator() ;
    while (pcrv = inset.NextCurve())
        chn.ChainAllLoops(pcrv->pcnmap, outset, CS_Chain::RIGHT) ;

    // Now delete all curves that are inside other curves
    CS_POINT insidePnt ; 
    CS_CurveVecItr i1, i2 ; 
    for (i1=outset.crvlist.begin() ; i1 != outset.crvlist.end(); i1++)
    {
        i2=outset.crvlist.begin() ; 
        while (i2 != outset.crvlist.end())
        {
            if (*i1 == *i2)
            {
                i2++ ; 
            }
            else
            {
                CS_GetPointInside(*i2, insidePnt) ;
                if ((*i1)->PointInside(insidePnt))
                {   // Then we want to delete the j'th curve from the list
                    CS_CurveVecItr iv ; 
                    iv = i2 ;
                    i2++ ; 
                    outset.DeleteCurve(iv) ; 
                }
                else
                {
                    i2++ ; 
                }
            }
        }
    }


    return 0 ;
}




// Linker and Compiler error testing see chaining.cpp

int __cdecl CompChainSeg(const void *a, const void *b) ;
CS_ChainSegment *RemoveFromList(CS_ChainSegment* &pfirst, CS_ChainSegment* pdel) ;

int CS_ChainUniqueSegments(CS_Segment **pIN, int nIN, CS_CurveSet &crvset, double *tol)
{
    int i ;

    if (nIN <= 0)
        return 0 ; 

    // Intersect all the segments together. The first step is to sort all the 
    // segments based on their rectangles

    CS_ChainSegment *pfirst, *plast, *pnxt ; 
    CS_ChainSegment *pchnseg = new CS_ChainSegment[nIN+4] ;

    for (i=0; i < nIN; i++)
    {
        pchnseg[i].pseg = pIN[i] ;
        pchnseg[i].status = 0 ;
        pchnseg[i].bndbox = pIN[i]->BoundingRect() ; 
        pchnseg[i].bndbox.Expand(0.01) ; 
    }

    // Now sort the segments based on their left rect values.
    qsort(pchnseg, nIN, sizeof(CS_ChainSegment), CompChainSeg) ;


    // Connect up the list pointers
    for (i=0; i < nIN; i++)
    {
        pchnseg[i].next = &pchnseg[i+1] ;
        pchnseg[i+1].prev = &pchnseg[i] ;
    }

    // Only have to assign and clean up the first and last pointers
    pfirst = &pchnseg[0] ;
    plast = &pchnseg[nIN-1] ; 
    pfirst->prev = 0 ; 
    plast->next = 0 ; 

    // Chain simply connected segments together and filter out overlapping
    // segments.
    CS_SegPtr pseg ; 
    CS_IREC *pirec ; 
    int resmask ; 
    CS_Curve *pcrv ; 

    while (pfirst)
    {
        pcrv = new CS_Curve ; 
        pcrv->Append(pfirst->pseg->Copy()) ; 
        
        // Delete the first node from the list since it has been used
        pnxt = pfirst ; 
        pnxt = RemoveFromList(pfirst, pnxt) ; 
        
        bool bConnectedNewSegment = true ; 

        while (bConnectedNewSegment)
        {
            bConnectedNewSegment = false ;
            pnxt = pfirst ;
            while (pnxt)
            {
                if (0 != (resmask = SegmentsConnected(pcrv->pStart, pnxt->pseg, tol)))
                {   
                    bool overlapped = false ;

                    if (pnxt->pseg->SegmentType() == pcrv->pStart->SegmentType())
                    {   // Check if they overlap
                        CS_IRECList isset ;
                        CS_IRECListItr iri ;
                        pnxt->pseg->Intersect2D(pcrv->pStart, &isset) ;
                        for (iri = isset.begin(); iri != isset.end(); iri++)
                        {
                            pirec = iri->pir ; 
                            if (pirec->statinfo & CS_IREC::OVERLAP)
                            {   // Then don't want to append this record
                                overlapped = true ; 
                                break ;
                            }
                        }
                    }

                    //////////////////////////////////////////////////////////
                    // TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO 
                    // Have to check to see if the pnxt overlap record covers
                    // the [0,1] range. If it doesn't then we have to trim the 
                    // segment out that doesn't overlap and append it to the 
                    // end of the list of segments to test against
                    //////////////////////////////////////////////////////////


                    // Note: the logic below never reorients the segments in 
                    // the pcrv. 

                    int bProcessed = false ; 
                    if (!overlapped)
                    {   
                        if (resmask == CS_CONNECT_ALL)
                        {   // Then both end points are connected
                            // Should only get here if there are two segments which form
                            // a loop which means one of the segments 
                            assert(pcrv->nodecnt == 1) ; 

                            // THIS IS WRONG - the only way all end points can be connected
                            // is if the curve is a complete circle and the segment to be
                            // added is a complete circle, in which case we have two 
                            // overlapping circles and thus one of them should be discarded

                            // Test this by creating two overlapping circles and see if 
                            // this logic is entered. Note for this to work, complete 
                            // circles have to be normalized so that they start at 0 
                            // degrees, otherwise the start points won't overlap and 
                            // this condition will not be trapped. 


                            if (pcrv->pStart->StartPoint() == pnxt->pseg->StartPoint())
                            {   // Then reverse the second curve
                                pseg = pnxt->pseg->Copy() ; 
                                pseg->Reverse() ; 
                                pcrv->Insert(pcrv->pStart, pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            }
                            else
                            {   // Add it to the end
                                pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                            }
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_START) &&
                            (resmask & CS_CONNECT_B_START))
                        {   // reverse B and insert before A
                            pseg = pnxt->pseg->Copy() ; 
                            pseg->Reverse() ; 
                            pcrv->Insert(pcrv->pStart, pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_START) &&
                                 (resmask & CS_CONNECT_B_END))
                        {
                            pcrv->Insert(pcrv->pStart, pnxt->pseg->Copy(), 
                                                    CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if (pcrv->nodecnt == 1) 
                        {
                            if ((resmask & CS_CONNECT_A_END) &&
                                (resmask & CS_CONNECT_B_END))
                            {
                                pseg = pnxt->pseg->Copy() ; 
                                pseg->Reverse() ; 
                                pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                                bProcessed = true ; 
                                bConnectedNewSegment = true ; 
                            }
                            else if ((resmask & CS_CONNECT_A_END) &&
                                     (resmask & CS_CONNECT_B_START))
                            {
                                pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                                bProcessed = true ; 
                                bConnectedNewSegment = true ; 
                            }
                        }
                        // else (resmask & CS_CONNECT_A_END) must hold
                        // In this case simply want to skip the segment and 
                        // continue processing
                    }
                    
                    // delete pnxt since if it has been processed
                    if (bProcessed) 
                    {
                        pnxt = RemoveFromList(pfirst, pnxt) ; 
                        continue ; 
                    }
                    else 
                    {
                        int x = 0 ; 
                        x += 1 ; 
                    }
                }
                else if (0 != (resmask = SegmentsConnected(pcrv->pEnd, pnxt->pseg, tol)))
                {
                    assert(pcrv->nodecnt > 1) ;

                    bool overlapped = false ; 

                    if (pnxt->pseg->SegmentType() == pcrv->pStart->SegmentType())
                    {   // Check if they overlap
                        CS_IRECList isset ; 
                        CS_IRECListItr iri ;
                        pnxt->pseg->Intersect2D(pcrv->pEnd, &isset) ; 
                        for (iri = isset.begin(); iri != isset.end(); iri++)
                        {
                            pirec = iri->pir ; 
                            if (pirec->statinfo & CS_IREC::OVERLAP)
                            {   // Then don't want to append this record
                                overlapped = true ; 
                                break ;
                            }
                        }
                    }

                    //////////////////////////////////////////////////////////
                    // TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO TO DO 
                    // Have to check to see if the pnxt overlap record covers
                    // the [0,1] range. If it doesn't then we have to trim the 
                    // segment out that doesn't overlap and append it to the 
                    // end of the list of segments to test against
                    //////////////////////////////////////////////////////////


                    // Note: the logic below never reorients the segments in 
                    // the pcrv. 

                    int bProcessed = false ; 
                    if (!overlapped)
                    {   
                        if ((resmask & CS_CONNECT_A_END) &&
                            (resmask & CS_CONNECT_B_END))
                        {   // reverse B and append to curve
                            pseg = pnxt->pseg->Copy() ; 
                            pseg->Reverse() ; 
                            pcrv->Append(pseg, CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        else if ((resmask & CS_CONNECT_A_END) &&
                                 (resmask & CS_CONNECT_B_START))
                        {
                            pcrv->Append(pnxt->pseg->Copy(), CS_NOENDPOINTADJUSTMENT) ; 
                            bProcessed = true ; 
                            bConnectedNewSegment = true ; 
                        }
                        // else (resmask & CS_CONNECT_A_START) must hold
                        // In this case simply want to skip the segment and 
                        // continue processing, since if the nodecnt==1 and this
                        // condition occured it would have been trapped in the
                        // first if statement above. 
                    }
                    
                    // delete pnxt since if it has been processed
                    if (bProcessed) 
                    {
                        pnxt = RemoveFromList(pfirst, pnxt) ; 
                        continue ; 
                    }
                    else 
                    {
                        int x = 0 ; 
                        x += 1 ; 
                    }
                }
                pnxt = pnxt->next ; 
            }
        } 
        crvset.AddCurve(pcrv) ; 
    }


    // Now see if any of the crvset curves can be connected together. 

    double cmptol = COMPARETOLERANCE ; 
    if (tol)
        cmptol = *tol ; 

    CS_CurveVecItr icset = crvset.crvlist.begin() ;  
    // TO DO - see if we can optimize this instead of looping through over and
    // over again. 
    bool connectedSomething ; 
    do {
        connectedSomething = false ; 

        while (icset != crvset.crvlist.end())
        {
            CS_Curve *pc = *icset ; 
            if (pc->Closed(tol))
            {
                icset++ ; 
                continue ; // skip the closed curves
            }

            CS_POINT sp = pc->StartPoint() ; 
            CS_POINT ep = pc->EndPoint() ; 

            CS_CurveVecItr ics2 = icset ;  
            ics2++ ; // move to next record
            
            bool nextRec = true ; 
            while (ics2 != crvset.crvlist.end())
            {
                CS_Curve *pc2 = *ics2 ; 
                CS_POINT sp2, ep2 ; 
                sp2 = pc2->StartPoint() ; 
                ep2 = pc2->EndPoint() ; 

                // note if any of these if conditions matches then we want to 
                // reprocess the current curve since it may conntect up to something else
                // which is why we set nextRec to false. 
                if (tcomp_PointsEQ(sp.p, sp2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc2->Reverse() ; 
                    pc->InsertCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(sp.p, ep2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc->InsertCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(ep.p, sp2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc->AddCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }
                else if (tcomp_PointsEQ(ep.p, ep2.p, cmptol))
                {   // Then join up the curves. 
                    // First reverse the 2nd curve so that it goes in the right direction
                    pc2->Reverse() ; 
                    pc->AddCurve(pc2) ; 
                    crvset.crvlist.erase(ics2) ; 
                    nextRec = false ; 
                    connectedSomething = true ; 
                    break ; 
                }

                ics2++ ; 
            }

            if (nextRec)
                icset++ ; 
        }
    } while (connectedSomething) ; 

    delete[] pchnseg ;
    return 0 ; 
}


