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
// crvboolean.cpp - Boolean operations on curves of intersection, union and 
//      difference. Thus we can due three operations on two curves
//      AxB (intersection), A+B (union), or A-B (difference)

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
#include "cs_chain.h"

#include "cs_offset.h"
#include "cs_offsoval.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)                
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif


void CS_Curve::ClearChaining() 
{
    if (pcnmap)
    {
        delete pcnmap ; 
        pcnmap = 0 ; 
    }
}

// CS_Curve function call entry points for the boolean operations
int CS_Curve::Union(CS_Curve *pcrvB, CS_CurveSet &resultSet) 
{
    Bool2D b2d ; 
    return b2d.Union(this, pcrvB, &resultSet) ; 
}

int CS_Curve::Intersection(CS_Curve *pcrvB, CS_CurveSet &resultSet) 
{
    Bool2D b2d ; 
    return b2d.Intersect(this, pcrvB, &resultSet) ; 
}

int CS_Curve::Difference(CS_Curve *pcrvB, CS_CurveSet &resultSet) 
{
    Bool2D b2d ; 
    return b2d.Difference(this, pcrvB, &resultSet) ; 
}


// generic routine to intersect and generate events for two arbitrary curves
// Note: the curves passed in don't have to be closed or even continuous
// since all the routine does is put all the curve segments into a list
// and then intersect each against one another

// TO DO - make this generic so it can run on a single curve (self 
// intersections) as well as multpile curves or random curve
// segments. Have to make sure that the pca, and pcb pointers will
// make sense in this mode.

int IntersectCurves(CS_Curve *pcrva, CS_Curve *pcrvb, 
                    UEventList &ela, UEventList &elb)
{
    CCISNode *pisn = new CCISNode[pcrva->nodecnt + pcrvb->nodecnt + 2] ; 
    if (!pisn)
        return -1 ; // memory error


    ///////////////////////////////////////////
    ///////////////////////////////////////////
    // Fill node data and set rectangle values
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    int i, j; 
    int segcount ; 
    CS_SegPtr pn ; 
    int crvnum = 0 ; 

    i = 0 ; // intersect node counter
    segcount = 0 ; 
    pn = pcrva->pStart ; 
    while (pn)
    {
        pisn[i].psn = pn ; 
        pisn[i].rect = pn->BoundingRect() ;
        pisn[i].rect.Expand(0.01) ; 
        pisn[i].pcrv = pcrva ; 
        pisn[i].count = segcount++ ; 
        pisn[i].crvnum = crvnum ; 
        pn = pn->next ; 
        i++ ; 
    }

    // Add in the B curve data
    crvnum++ ; 
    segcount = 0 ; 
    pn = pcrvb->pStart ; 
    while (pn)
    {
        pisn[i].psn = pn ; 
        pisn[i].rect = pn->BoundingRect() ;
        pisn[i].rect.Expand(0.01) ; 
        pisn[i].pcrv = pcrvb ; 
        pisn[i].count = segcount++ ; 
        pisn[i].crvnum = crvnum ; 
        pn = pn->next ; 
        i++ ; 
    }

    int nodecnt = i ;

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
    UEvent *pevent ; 
    int evtype ; // temporary event type used in overlap processing

    // Speed wise we could optimize things here since we're doing alot
    // of testing for a curve against itself (yes we ignore this but 
    // still have to loop through them all). Could set things up 
    // better making use of the fact that the two curves do not 
    // intersect themselves. Perhaps some type of p-tree structure
    // would speed processing.

    i = 0 ; 
    for (i=0; i < nodecnt; i++)
    {
        // We want the segments as defined in the event data structures
        // to be ordered such that the segment with the lesser Uo value 
        // occurs first.

        for (j=i+1;(j < nodecnt) && (pisn[i].rect.r > pisn[j].rect.l);j++)
        {
            if (pisn[i].pcrv == pisn[j].pcrv)
                continue ; // don't test segments on same curve

            // Check if these segments intersect
            CS_IRECList isset ; 
            nisects = pisn[i].psn->Intersect2D(pisn[j].psn, &isset);

            CS_IRECListItr iri ; 
            for(iri = isset.begin(); iri != isset.end(); iri++)
            {
                if (iri->pir->statinfo & CS_IREC::POINT)
                {
                    if (pisn[i].pcrv == pcrva)
                    {
                        pevent = ela.BoolIXEvent(pisn, i, j, 
                                                    iri->pir->cpp[0].u, iri->pir->cps[0].u) ; 
                        elb.AppendSecondary(UEVENT_INTERSECTION, pevent) ;
                    }
                    else
                    {   // Then j references the a curve segment
                        pevent = ela.BoolIXEvent(pisn, j, i, 
                                                    iri->pir->cps[0].u, iri->pir->cpp[0].u) ; 
                        elb.AppendSecondary(UEVENT_INTERSECTION, pevent) ;
                    }
                }
                else if (iri->pir->statinfo & CS_IREC::OVERLAP)
                {
                    // Do the first point
                    evtype = -1 ; // uninitialized state
                    if (pisn[i].pcrv == pcrva)
                    {
                        pevent = ela.BoolOVLPEvent(pisn, i, j, 
                                                    iri->pir->cpp[0].u, iri->pir->cps[0].u, 
                                                        &evtype) ;
                        if (evtype & UEVENT_OVERLAPBREVERSE)
                        {   // flip the startpoint bit
                            evtype ^= UEVENT_STARTPOINT ; 
                        }
                        elb.AppendSecondary(evtype, pevent) ; 
                    }
                    else
                    {
                        pevent = ela.BoolOVLPEvent(pisn, j, i, 
                                                    iri->pir->cps[0].u, iri->pir->cpp[0].u, 
                                                        &evtype) ;
                        if (evtype & UEVENT_OVERLAPBREVERSE)
                        {   // flip the startpoint bit
                            evtype ^= UEVENT_STARTPOINT ; 
                        }
                        elb.AppendSecondary(evtype, pevent) ; 
                    }

                    // Now we deal with the second point. Note the evtype
                    // variable will already hold the proper value for the
                    // reverse condition, so we don't really want to redo
                    // the reverse logic. The startpoint is correctly set
                    // based on the fact that evtype != -1 on entry 
                    // (which causes the startpoint to be cleared)
                    
                    if (pisn[i].pcrv == pcrva)
                    {
                        pevent = ela.BoolOVLPEvent(pisn, i, j, 
                                                   iri->pir->cpp[1].u, iri->pir->cps[1].u, 
                                                   &evtype) ;
                        if (evtype & UEVENT_OVERLAPBREVERSE)
                        {   // flip the startpoint bit
                            evtype ^= UEVENT_STARTPOINT ; 
                        }
                        elb.AppendSecondary(evtype, pevent) ; 
                    }
                    else
                    {
                        pevent = ela.BoolOVLPEvent(pisn, j, i, 
                                                   iri->pir->cps[1].u, iri->pir->cpp[1].u, 
                                                   &evtype) ;
                        if (evtype & UEVENT_OVERLAPBREVERSE)
                        {   // flip the startpoint bit
                            evtype ^= UEVENT_STARTPOINT ; 
                        }
                        elb.AppendSecondary(evtype, pevent) ; 
                    }
                }
                // else an error occured
            }
        }
    }

    delete[] pisn ; // don't need the bounding rectangles anymore 

    // Have now built the two event lists and they are ready for the next step

    return 0 ; 
}






