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
// machoffset.cpp - machining style offset (Minkowski Sum) 

// This offset is based on several papers that have been published in the public 
// domain, with some minor modifications to correct errors in those papers.
// See:  'An Algorithm for Generating NC Tool Paths for Arbitrarily
//          Shaped Pockets and Islands',  Allan Hansen, Farhad Arbab,
//       ACM Transactions on Graphics, Vol 11, No. 2, April 1992, Pgs 152-182
// There were several other papers that detailed similar methods but this 
// one defined the details fairly clearly.
// 


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

#include "cs_offset.h"
#include "cs_offsoval.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)                  
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// This is a full machining style offset. The first step is to call Offset2()
// Then the extra steps required to delete the various curve sections based
// on intersection points is performed. The final result is a set of offset
// curves. If the offset results in a fully inside-out shape then the result
// set is NULL. More than one curve can be in the result set since when 
// offsetting shape sections inwards, loop sections can be cut of through
// self intersections. More specifically, offsetting a concave shape can 
// result in multiple closed curves. Offsetting a simple convex closed curve
// can only result in one shape (Convex simple means a curve where if at 
// any point along the curve, no line segment can be drawn to any other point
// on the curve which intersects the curve at a third point. Obviously the 
// 2 points have to be on different line segments as well, since two points
// on the same line segment pass through infinitely many points along the 
// space between the two points.)
// 
// This routine works in several stages.
//  1) Start by calling Offset2() 
//  2) Create bounding box for all resultant segments and sort by left x
//  3) Create intersection set of all curve self intersections, and make
//     use of the bounding box information to optimize intersection 
//     calculation.
//  4) Split the segments at all intersection points. keeping track of 
//     those start/end point pairs that sit on a self intersect point.
//  5) Walk along and by keeping track of which crossovers at each 
//     intersection, determine which curve segments to keep and which
//     ones to discard. 
//  6) Generate the final set of curves by chaining left those curves
//     that were marked as keepers.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int OfsISNodeComp(const void *a, const void *b)
{
    CCISNode *pa, *pb ; 
    pa = (CCISNode *)a ; 
    pb = (CCISNode *)b ; 
    if (pa->rect.l < pb->rect.l)
        return -1 ; 
    else if(pa->rect.l == pb->rect.l)
        return 0 ; 
    return 1 ; 
}

// returns error code on failure
// returns a pointer to an array of CS_Curves that are the result of the offset
// Note: this is required since the offset operation can result in multiple
// closed curves being generated. The CS_Curve array returned as well as each
// curve in the list must be freed on exit. This can be done with a call to
// FreeCurveList(), the number of curves is passed back in count
// The int return code signals any errors that occur, 0=success
// Warning, the original curve is modified through an Offset2() call
int CS_Curve::Offset(double delta, CS_CurveSet &curveset, int offsetmode)
{
    int i, j ; 
    CS_SegPtr pn ; 

    statflags &= ~CS_FORCEOPENOFS ; 
    statflags |= (offsetmode & CS_FORCEOPENOFS) ; 
    
    if (tcomp_EQZ(delta))
    {
        CS_Curve *pcrv = new CS_Curve ; 
        pcrv->CopyCurve(*this) ; 
        curveset.AddCurve(pcrv) ; 
        return 0 ; 
    }
    // Initial setup and raw offset 
    if (!(statflags & CS_FORCEOPENOFS))
        SetDirection(CCW) ; 

    Offset2(delta) ; // this offsets and inserts inverted arcs
    if (!pStart)
        return 1 ; // curve disappeared, nothing to do
    Finalize() ; // validate all u parms and closed condition
    Closed() ; // make sure the CLOSEDCURVE status bit is set correctly
    if (statflags & CS_FORCEOPENOFS)
        statflags &= ~CS_CLOSEDCURVE ;

    // fprintf(fpDebugOut, "Offset of %f\n", delta) ; 
    
    /*
    ////////////////////////////////
    // Output raw offset curve
    CS_Curve *pc = new CS_Curve ; 
    pc->CopyCurve(*this) ; 
    curveset.AddCurve(pc) ; 
    return 0 ; // success
    // end raw output
    ////////////////////////////////
    */

    CCISNode *pisn = new CCISNode[nodecnt+1] ; 
    if (!pisn)
        return -1 ; // memory error

    ///////////////////////////////////////////
    ///////////////////////////////////////////
    // Fill node data and set rectangle values
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    pn = pStart ; 
    i = 0 ; 
    while (pn)
    {
        pisn[i].psn = pn ; 
        pisn[i].rect = pn->BoundingRect() ;
        pisn[i].rect.Expand(0.01) ; 
        pisn[i].count = i ; 
        pisn[i].pcrv = this ; 
        pn = pn->next ; 
        i++ ; 
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////
    // Sort the nodes by the rect.left value
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    qsort(pisn, nodecnt, sizeof(CCISNode), OfsISNodeComp) ;

    //////////////////////////////////////////////
    //////////////////////////////////////////////
    // Perform the self intersection on the curve
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    // Here we build the initial event list. Once done a postprocessing
    // step is performed whereby the event list is cleaned up and sorted
    int nisects ; 

    UEventList evlst ; 

    // TO DO - see if we can clean up the logic here since the test ui<uj 
    // creates a whole pile of if statements with basically redundant 
    // code. Simple solution is to create an EventReverse() call but
    // this would slow the code down drastically, need a better solution
    // We have to have the segment nodes within the events ordered so 
    // that later on we can eliminate secondary intersection events 
    // without testing a large number of cases. Have the segments ordered
    // within the event reduces the number of comparisons by a factor of 
    // four.

    CS_IRECListItr iri ; 
    i = 0 ; 
    double compTolValue = COMPARETOLERANCE * 10.0 ; 
    for (i=0; i < nodecnt; i++)
    {
        // We want the segments as defined in the event data structures
        // to be ordered such that the segment with the lesser Uo value 
        // occurs first.
        
        for (j=i+1; (j<nodecnt) && (pisn[i].rect.r > pisn[j].rect.l); j++)
        {
            CS_IRECList isset ; 
            nisects = pisn[i].psn->Intersect2D(pisn[j].psn, &isset);

            
            for (iri = isset.begin(); iri != isset.end(); iri++)
            {   // Work through all the intersections
                if (iri->pir->statinfo & CS_IREC::POINT)
                {
                    CS_CrvPnt cp1, cp2 ; 
                    cp1.s = pisn[i].psn ;
                    cp1.u = iri->pir->cpp[0].u ;
                    cp2.s = pisn[j].psn ;
                    cp2.u = iri->pir->cps[0].u ; 
                    if (!SequentialSegments(&cp1, &cp2, &compTolValue))
                    {   // Then add this intersection to the event list
                        double uvp[2], uvs[2] ; 
                        uvp[0] = iri->pir->cpp[0].u ; 
                        uvp[1] = iri->pir->cpp[1].u ; 
                        uvs[0] = iri->pir->cps[0].u ; 
                        uvs[1] = iri->pir->cps[1].u ; 
                        evlst.OffsetIXEvent(pisn, i, j, uvp, uvs) ;
                    }
                }
                else if(iri->pir->statinfo & CS_IREC::OVERLAP)
                {
                    double uvp[2], uvs[2] ; 
                    uvp[0] = iri->pir->cpp[0].u ; 
                    uvp[1] = iri->pir->cpp[1].u ; 
                    uvs[0] = iri->pir->cps[0].u ; 
                    uvs[1] = iri->pir->cps[1].u ; 

                    evlst.OffsetOVLPEvent(pisn, i, j, uvp, uvs);
                }
                else
                {   // Error abort
                }
            }
        }

        // Must test for and store the inverted arc condition as well
        if (pisn[i].psn->info & CRV_ARCCONVEX)
        {   // Here we create two events, inverted arc start and 
            // inverted arc end
            evlst.OffsetInvArcEvent(pisn, i) ; 
        }
    }

    delete[] pisn ; // don't need the bounding rectangles anymore 

    ///////////////////////////////
    ///////////////////////////////
    // Post-process the event list
    ///////////////////////////////
    ///////////////////////////////
    
    evlst.SortList() ; 
    CS_DEBUG(evlst.DumpList()) ; 
    evlst.MergeOverlaps() ;
    evlst.LabelCrossovers() ; 
    CS_DEBUG(evlst.DumpList()) ; 

    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    // Perform index counting and build final curves
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    // First allocate space for the index records which will match the
    // number of valid set

    // First handle the special case of no events
    // TO DO : test changing listlen to numSets
    if (evlst.listlen < 2 || evlst.eventSets[0] == -1)
    {   // then there are no events defined so we simply grab the entire 
        // offset curve as the final result
        CS_Curve *pc = new CS_Curve ; 
        pc->CopyCurve(*this) ; 
        curveset.AddCurve(pc) ; 
        return 0 ; // success
    }
    
    ////////////////////////////////////
    // Otherwise we have more work to do
    ////////////////////////////////////
    OffsetIndexing oi ; // class to maintain indexing information
    oi.sideINC = (delta > 0.0) ? 1 : -1 ;
    oi.Initialize(&evlst) ;     // Initialize and allocate memory
    // Create the list of index records
    oi.CalcIndexes(statflags & CS_CLOSEDCURVE) ; 
    CS_DEBUG(oi.Dump();) ; 

    
    ////////////////////////////////////////////////////
    // Extract list of final curves using the minimum 
    // index count value generated
    ////////////////////////////////////////////////////

    oi.BuildCurves(this, curveset) ; 

    Closed() ; // make sure the CLOSEDCURVE status bit is set correctly
    // fprintf(fpDebugOut, "\n ==== Offset Done === \n") ; 

    return 0 ; // success
}



// Note only call this if the intent is to de-allocate and free
// the memory for all the curves in the array as well as the 
// array itself. If the curves are used elsewhere and will be
// deleted elsewhere, then do not call this function. All that
// is required is to de-allocate the curve pointer array
// with the call  'delete[] pcrvs' ;
void CS_FreeCurves(CS_Curve **pcrvs, int count)
{
    int i ;
    if (count)
    {
        if (pcrvs)
        {
            for (i = 0; i < count; i++)
                delete pcrvs[i++] ; 
            delete[] pcrvs ;
        }
    }
    else
    {
        if (pcrvs)
        {
            i = 0 ; 
            while (pcrvs[i])
                delete pcrvs[i++] ; 

            delete[] pcrvs ;
        }
    }
}


// This is code that was used to connect CS_CurveChain type data together 
// regardless of the order of the curves in the set. Each curve must be
// oriented in the proper direction though before it will be connected
// with another curve. Curves that occur later in the list but come
// before the current curve section are inserted in the front, and 
// replace that curve definition. Curves that are appended are simply
// deleted (The CS_Curve memory used) after being appended to the current
// curve
    

    ///////////////////////////////////////////////////////////////////////
    // Now we have to connect together the various curve sets as the final 
    // step since independent curve sets may have been created
    ///////////////////////////////////////////////////////////////////////
    /*
    CS_ListNode *plistnxt ; 
    plistn = activelist.pFirst ;
    CS_CurveChain *psettest ;
    CS_ListNode *plntmp ;
    
    plistn = activelist.pFirst ; 

    while (plistn)
    {
        psettest = *(activelist.GetData(plistn)) ;
        plistnxt = plistn->next ; 
        bCurveAdded = false ; 
        while (plistnxt) 
        {   // Check each curve in the list for front and back appendability
            pcrvset = *(activelist.GetData(plistnxt)) ;
            if (psettest->ep == pcrvset->sp)
            {   // then append this curve to the end
                // And delete it from the list
                psettest->pcrv->AddCurve(pcrvset->pcrv) ; 
                psettest->ep = pcrvset->ep ; 
                psettest->status |= (pcrvset->status & REC_CONTAINSINVERTARC) ; 

                // Delete the current node since it's been merged
                pcrvset->pcrv = 0 ; // so desctructor doesn't try to delete it
                delete pcrvset ; 
                plntmp = plistnxt->next ; 
                activelist.Delete(plistnxt) ; 
                plistnxt = plntmp ; 

                // Now check if we've closed this curve
                if (psettest->sp == psettest->ep)
                {   // Then we've closed the curve so transfer it to the 
                    // final curve list
                    finallist.Append(psettest) ; 
                    // We're breaking out of the loop so it is okay to delete 
                    // this node from the list
                    plntmp = plistn->next ; 
                    activelist.Delete(plistn) ; 
                    plistn = plntmp ; 
                    bCurveAdded = true ; 
                    break ; // break out of the inner loop
                }
                // mark that we've connected two curves
                // So that we do not increment the next pointer
                // Note even when entering the if we want to set this condition
                // since we have to move plistn ahead in this situation
                bCurveAdded = true ; 
            }
            else if (pcrvset->ep == psettest->sp)
            {   // Want to add S->E in proper order
                pcrvset->pcrv->AddCurve(psettest->pcrv) ; 
                pcrvset->ep = psettest->ep ; 
                pcrvset->status |= (psettest->status & REC_CONTAINSINVERTARC) ; 

                // Delete the curveset that was merged
                psettest->pcrv = 0 ; // so desctructor doesn't try to delete it
                delete psettest ; 

                // Now move the current Curveset to the Base position
                // and delete the current node
                *((CS_CurveChain **)plistn->pdata) = pcrvset ; 
                // Change the pointer since this is the new current set
                psettest = pcrvset ; 
                
                // Delete the unused node now
                plntmp = plistnxt->next ; 
                activelist.Delete(plistnxt) ; 
                plistnxt = plntmp ; 

                // Now check if we've closed this curve
                if (psettest->sp == psettest->ep)
                {   // Then we've closed the curve so transfer it to the 
                    // final curve list
                    finallist.Append(psettest) ; 
                    // We're breaking out of the loop so it is okay to delete 
                    // this node from the list
                    CS_ListNode *plntmp = plistn->next ; 
                    activelist.Delete(plistn) ; 
                    plistn = plntmp ; 
                    bCurveAdded = true ; 
                    break ; // break out of the inner loop
                }
                // mark that we've connected two curves
                // So that we do not increment the next pointer
                // Note even when entering the if we want to set this condition
                // since we have to move plistn ahead in this situation
                bCurveAdded = true ; 
            }
            else
            {
                plistnxt = plistnxt->next ; 
            }
        }

        // If we added a curve then we have to rescan the list
        if (!bCurveAdded)
            plistn = plistn->next ; 
    }

    */

