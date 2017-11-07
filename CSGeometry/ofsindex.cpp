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
// ofsindex.cpp - does offset index counting
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
#include "cs_offsoval.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)                
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Offset Index Processing
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// This is the final stage in the processing of an offset. Once this 
// stage is complete all that remains is to build the final curves
// based on those curves which have matching index counts.

OffsetIndexing::OffsetIndexing()
{
    sideINC = 0 ;    // indicates an inside(-1) or outside(+1) offset
    indexCount = 0 ; // current index count
    minidxCount = 0 ; // minimum count value during processing
    bInvertArc = 0 ; // invert arc active indicator
    bInOverlap = 0 ; // inside overlap section indicator
    esetLength = 0 ; 
    pidxrecs = 0 ; 
    irecLen = 0 ; // number of index record entries defined
    pevlst = 0 ; 
    lastIndexCount = 0 ; 
    bInvertArcSection = 0 ; 
}


OffsetIndexing::~OffsetIndexing()
{
    if (pidxrecs)
        delete[] pidxrecs ; 
}


int OffsetIndexing::Initialize(UEventList *plst)
{
    pevlst = plst ; 
    esetLength = pevlst->numSets ; 

    // Allocate max possible space
    pidxrecs = new IndexRecord[pevlst->listlen + 5] ; 
    if (!pidxrecs)
        return -1 ; // memory error

    memset(pidxrecs, 0, sizeof(IndexRecord) * (pevlst->listlen + 5)) ; 
    return 0 ; // success
}


int OffsetIndexing::DoIndexCount(int i)
{
    int einfo = pevlst->plist[i].einfo ;
    int status = pevlst->plist[i].pevent->status ;
    int prevIndexCount = indexCount ; 

    indexDelta = 0 ; 

    if (status & UEVENT_CROSSOVER)
    {   // If it's not a crossover then don't do anything
        if (einfo & UEVENT_PRIMARYRECORD)
        {   // Normal forward direction processing
            if (status & UEVENT_RIGHT)
                indexCount -= sideINC ; 
            else
                indexCount += sideINC ; 
        }   
        else
        {   // Have to reverse the sense of what's happening
            if (status & UEVENT_LEFT)
                indexCount -= sideINC ; 
            else
                indexCount += sideINC ; 
        }

        // Save minimum index count value
        if (indexCount < minidxCount)
            minidxCount = indexCount ; 
    
        // Set all the index tracking management variables
        if (firstXOverIDX == -1)
            firstXOverIDX = i ; 
        lastXOverIDX = i ;

        indexDelta = indexCount - prevIndexCount ;

        return 1 ; // return true since it was a crossover
    }


    return 0 ; 
}




int OffsetIndexing::CalcIndexes(int closed)
{
    if (closed)
        return CalcIndexesClosed() ; 
    else
        return CalcIndexesOpen() ; 
}

int OffsetIndexing::CalcIndexesClosed()
{
    int es ; // current event set
    int eset0 ; 
    int esEnd ; // used as a work variable, marks end of event set
    int stat ;  // work var 

    // Loop through each event set, note we are starting with the first
    // event since we are always looking at two events to define an
    // index curve section (which exists between two separate events

    // initialize the first index record and then proceed with normal 
    // processing. The first record is really a special case because
    // we havent had to do any index counting yet
    
    // From the first event set we have to extract the overlap and 
    // inverse arc conditions but can ignore the effects of intersections
    
    ////////////////////////////////////////////////////////////
    // Step 1. - Find first event set with a valid crossover
    ////////////////////////////////////////////////////////////

    eset0 = 0 ; 
    stat = 0 ; 
    prevXOverEventIDX = 0 ; 
    overallEventStat = 0 ; 

    // Have to check if we are skipping completely deleted sets (overlap
    // sections) since we need to know if we are inside an overlap section)
    bInOverlap = 0 ;
    bInvertArc = 0 ; 
    if (pevlst->eventSets[0] > 0)
    {   // Then the first event set starts after the first entry in the 
        // list which means we have a completely deleted event set. This 
        // means that we are potentially in an overlap section (Actually 
        // I think this means we must be in an overlap section, but will 
        // have to test this in the future - for now we will assume that
        // this is the case. If this turns out not to be the case then
        // we will have to scan through the list of deleted events to 
        // decide how to correctly set the bInOverlap bit) 
            
        bInOverlap = 1 ; 
        
        // Possible code that we might want to keep for future use
        // Scan for overlap stat records
        // for (i=0; i < pevlst->eventSets[0] ; i++)
        // {
        //     if (pevlst->plist[i].einfo & UEVENT_OVERLAP)
        //     {
        //        if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
        //             bInOverlap = 1 ; 
        //         else 
        //             bInOverlap = 0 ; 
        //     }
        // }
    }

    // We don't want to start any index counting while inside 
    // an overlap section since this means we would have to search
    // both forwards and backwards to determine how to initialize the
    // bOverlapCountedOnEntry status bit
    while (eset0 < esetLength || bInOverlap)
    {
        stat = GetSetStatus(eset0) ; 
        if ((stat & UEVENT_CROSSOVER) && !bInOverlap) 
            break ; 
        eset0++ ; 
    }

    // Perform the main scan processing loop. We want to move ahead to the
    // next valid Xover style intersection, maintaining various status 
    // information along the way. Each time we move to a new event set
    // boundary has to be recorded as to the curve information of the 
    // last X over event. All we need to store at each node is the curves
    // overall u value, and the segment node that the u value occurs on.
    // Also need the index count for that section, as well as any overlap
    // regions contained in the section. 
    
    // eset0 is now the starting event set. We want to continue looping 
    // until this event set is reached again. (this will likely involve
    // looping past the end and back to the start of the list)

    
    // Pointers used to save where the first and last cross over events 
    // occured so we can select the correct one later on.

    int bOverlapCountedOnEntry = 0 ; 
    
    if (bInvertArc)
        bInvertArcSection = 1 ; 
    else
        bInvertArcSection = 0 ; 

    if (eset0 == esetLength)
    {   // Then we didn't find any crossovers so thus we are either keeping
        // the entire curve or discarding it which will be decided later
        return 0 ; 
    }

    // Reset index count variables
    indexCount = 0 ; 
    minidxCount = 0 ; // min should be negative or 0 when finished
    lastIndexCount = 0 ; 

    // Save the current crossover set location
    prevXOverESet = eset0 ; 

    // Start at the first crossover set, since we skip ahead one immediately
    // on entry to the loop. Thus we have all the parameters set for the 
    // first event that we need to set values for the second
    es = eset0 ; 

    do 
    {   // Note we do want to increment the counter immediately
        // on entry to the loop the first time since we want to 
        // skip the first crossover event
        
        // Increment the main loop counter        
        es = IncEventSet(es) ;

        esEnd = pevlst->eventSets[es+1] ;
        if (esEnd == -1)
            esEnd = pevlst->listlen ;

        // Loop through the event set
        int bXOver = 0 ; // Set if an X over event is logged
        // which means we want to create a new entry in the 
        indexDelta = 0; 
        firstXOverIDX = lastXOverIDX = -1 ; // initialized as invalid

        for (int i=pevlst->eventSets[es]; i < esEnd; i++)
        {
            if (pevlst->plist[i].einfo & UEVENT_DELETED)
                continue ; // skip the event

            // Main processing occurs here
            // Want to remember if a crossover occurs
            if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                (pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap start point
                overallEventStat |= UEVENT_OVERLAP ;
                bInOverlap = 1 ;
                if (bInvertArcSection)
                {   // Only index count overlap crossovers when invert
                    // arcs are active at the end of an overlap section
                    bXOver |= DoIndexCount(i) ;
                    bOverlapCountedOnEntry = 1 ; 
                }
            }
            else if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                     !(pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap end point
                bInOverlap = 0 ;
                if (!bOverlapCountedOnEntry)
                {   // Then index count on the exit
                    bXOver |= DoIndexCount(i) ;
                }
                bOverlapCountedOnEntry = 0 ; 
            }
            else if (pevlst->plist[i].einfo & UEVENT_INTERSECTION)
            {   // Intersection so do index counting processing logic
                overallEventStat |= UEVENT_INTERSECTION ;
                bXOver |= DoIndexCount(i) ;
            }
            else if (pevlst->plist[i].einfo & UEVENT_INVERTARC)
            {
                overallEventStat |= UEVENT_INVERTARC ;
                if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
                {
                    bInvertArcSection = 1 ; 
                    bInvertArc = 1 ; 
                }
                else
                    bInvertArc = 0 ; 
            }
        } // end for

        //////////////////////////////////////////////////////////
        // Here's where we create the actual index record entries
        //////////////////////////////////////////////////////////
        if (bXOver)
        {   // Then one or more crossovers occured within the current
            // event set so we want to create a new index record entry
            // Need the event set start and end indexes so that we can
            // set the various index record values
            
            // Step 1: work out which specific U event record we want to 
            // be the defining event for this record set.
            int ievent ; // array offset to the event
            if (indexDelta > 0)
            {
                ievent = firstXOverIDX ;
            }
            else
            {
                ievent = lastXOverIDX ;
            }

            pidxrecs[irecLen].esfromIDX = pevlst->eventSets[prevXOverESet];
            pidxrecs[irecLen].estoIDX = pevlst->eventSets[es] ; 
            pidxrecs[irecLen].idxCount = lastIndexCount ; 

            pidxrecs[irecLen].ifromEvent = prevXOverEventIDX ;
            pidxrecs[irecLen].itoEvent = ievent ;

            if (pevlst->plist[prevXOverEventIDX].einfo & UEVENT_PRIMARYRECORD)
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[prevXOverEventIDX].pevent->psna ; 

                pidxrecs[irecLen].uss =  
                    pevlst->plist[prevXOverEventIDX].pevent->u1 ; 
            }
            else
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[prevXOverEventIDX].pevent->psnb ; 

                pidxrecs[irecLen].uss = 
                    pevlst->plist[prevXOverEventIDX].pevent->u2 ; 
            }
    
            if (pevlst->plist[ievent].einfo & UEVENT_PRIMARYRECORD)
            {
                pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psna ; 
                pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u1 ; 
            }
            else
            {
                pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psnb ; 
                pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u2 ; 
            }
    
            pidxrecs[irecLen].us =  pevlst->plist[prevXOverEventIDX].u ; 
            pidxrecs[irecLen].ue =  pevlst->plist[ievent].u ; 

            // Save inverse arc condition
            if (bInvertArcSection || bInvertArc)
                pidxrecs[irecLen].status |= REC_CONTAINSINVERTARC ;

            // Increment the Index record set count length
            irecLen++ ; 

            // Save all the needed parameters for the next iteration
            lastIndexCount = indexCount ;
            if (!bInvertArc)
                bInvertArcSection = 0 ;
            prevXOverESet = es ; 
            prevXOverEventIDX = ievent ; 
        }
    } while (es != eset0) ; 

    // Could do a test here to make sure that indexCount matches the index
    // count of the next segment, which should hold true for closed curves
    // If this is not the case, then the logic used to perform the index
    // counting will likely have to be modified. Since we start at an
    // index count of 0, (indexCount==0) should be valid at this point

    return 0 ; // success
}



int OffsetIndexing::CalcIndexesOpen()
{
    int es ; // current event set
    int esEnd ; // used as a work variable, marks end of event set
    int stat ;  // work var 

    // Loop through each event set, note we are starting with the first
    // event since we are always looking at two events to define an
    // index curve section (which exists between two separate events

    // initialize the first index record and then proceed with normal 
    // processing. The first record is really a special case because
    // we havent had to do any index counting yet
    
    // From the first event set we have to extract the overlap and 
    // inverse arc conditions but can ignore the effects of intersections



    //////////////////////////////////////////////////////////////
    // Oct 1, 2001 - Special Case: two small arcs at the end of 
    // a line which is offset, causing both end arcs to invert. 
    // Then all that is generated are two invers arc events at 
    // either end of the curve. This can occur even of multiple
    // sections in the middle, if non-inverse arcs get inserted
    // at the middle sections, and inverse arcs at the ends. 
    // So, to deal with this. Check if there are exactly 4 inverse 
    // arc events and then keep the section in between the two 
    // of them.
    ///////////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////////
    // Step 1. - Find first event set with a valid crossover
    ////////////////////////////////////////////////////////////

    stat = 0 ; 
    overallEventStat = 0 ; 

    // Have to check if we are skipping completely deleted sets (overlap
    // sections) since we need to know if we are inside an overlap section)
    bInvertArcSection = 0 ; 
    bInOverlap = 0 ;
    bInvertArc = 0 ; 
    if (pevlst->eventSets[0] > 0)
    {   // Then the first event set starts after the first entry in the 
        // list which means we have a completely deleted event set. This 
        // means that we are potentially in an overlap section (Actually 
        // I think this means we must be in an overlap section, but will 
        // have to test this in the future - for now we will assume that
        // this is the case. If this turns out not to be the case then
        // we will have to scan through the list of deleted events to 
        // decide how to correctly set the bInOverlap bit) 
            
        bInOverlap = 1 ; 
    }

    int bOverlapCountedOnEntry = 0 ; 

    if (esetLength < 2)
    {   // Not possible to do index counting in this situation, so we 
        // either keep the entire curve or dump it
        return 0 ; 
    }

    if (esetLength == 2)
    {   // Check if they are inverse arc events, in which case the entire
        // curve has effectively inverted and we're dumping everything
        if (pevlst->plist[0].einfo & UEVENT_INVERTARC)
        {   // Then they are both invert arc events since they must 
            // occur in pairs.
            return 0 ; 
        }
    }

    if (esetLength == 4)
    {
        if (pevlst->plist[0].einfo & UEVENT_INVERTARC &&
            pevlst->plist[1].einfo & UEVENT_INVERTARC &&
            pevlst->plist[2].einfo & UEVENT_INVERTARC &&
            pevlst->plist[3].einfo & UEVENT_INVERTARC)
        {   // Then they are both invert arc events since they must 
            // occur in pairs.

            pidxrecs[irecLen].esfromIDX = 1;
            pidxrecs[irecLen].estoIDX = 2 ; 
            pidxrecs[irecLen].idxCount = 0 ; 

            pidxrecs[irecLen].ifromEvent = 1 ;
            pidxrecs[irecLen].itoEvent = 2 ;

            if (pevlst->plist[1].einfo & UEVENT_PRIMARYRECORD)
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[1].pevent->psna ; 

                pidxrecs[irecLen].uss =  
                    pevlst->plist[1].pevent->u1 ; 
            }
            else
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[1].pevent->psnb ; 

                pidxrecs[irecLen].uss = 
                    pevlst->plist[1].pevent->u2 ; 
            }

            if (pevlst->plist[2].einfo & UEVENT_PRIMARYRECORD)
            {
                pidxrecs[irecLen].pse = pevlst->plist[2].pevent->psna ; 
                pidxrecs[irecLen].use =  pevlst->plist[2].pevent->u1 ; 
            }
            else
            {
                pidxrecs[irecLen].pse = pevlst->plist[2].pevent->psnb ; 
                pidxrecs[irecLen].use =  pevlst->plist[2].pevent->u2 ; 
            }

            pidxrecs[irecLen].us =  pevlst->plist[1].u ; 
            pidxrecs[irecLen].ue =  pevlst->plist[2].u ; 

            // Save inverse arc condition
            // if (bInvertArcSection || bInvertArc)
            //     pidxrecs[irecLen].status |= REC_CONTAINSINVERTARC ;

            pidxrecs[irecLen].idxas = 1 ; 
            pidxrecs[irecLen].idxae = 2 ; 

            // Increment the Index record set count length
            irecLen++ ; 
            return 0 ; 
        }
    }

    CS_Curve *pcrv ; // temp var

    // Reset index count variables
    indexCount = 0 ; 
    minidxCount = 0 ; // min should be negative or 0 when finished
    lastIndexCount = 0 ; 

    // Init prevXover to NULL 
    prevXOverESet = -1 ; 
    prevXOverEventIDX = -1 ; 

    int ievent ; // array offset to the event

    // Start at the first crossover set, since we skip ahead one immediately
    // on entry to the loop. Thus we have all the parameters set for the 
    // first event that we need to set values for the second

    int idxas, idxae ; // idx offset to inverse arc start and ends along 
    // a curve section (in between crossovers) within the eventlist array

    idxas = -1 ; 
    idxae = -1 ; 

    for (es = 0; es < esetLength; es++) 
    {   // Note we do want to increment the counter immediately
        // on entry to the loop the first time since we want to 
        // skip the first crossover event
        
        // Loop through the event set
        int bXOver = 0 ; // Set if an X over event is logged
        // which means we want to create a new entry in the 
        indexDelta = 0; 
        firstXOverIDX = lastXOverIDX = -1 ; // initialized as invalid

        esEnd = pevlst->eventSets[es+1] ;
        if (esEnd == -1)
            esEnd = pevlst->listlen ;

        for (int i=pevlst->eventSets[es]; i < esEnd; i++)
        {
            if (pevlst->plist[i].einfo & UEVENT_DELETED)
                continue ; // skip the event

            // Main processing occurs here
            // Want to remember if a crossover occurs
            if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                (pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap start point
                overallEventStat |= UEVENT_OVERLAP ;
                bInOverlap = 1 ;
                if (bInvertArcSection)
                {   // Only index count overlap crossovers when invert
                    // arcs are active at the end of an overlap section
                    bXOver |= DoIndexCount(i) ;
                    bOverlapCountedOnEntry = 1 ; 
                }
            }
            else if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                     !(pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap end point
                bInOverlap = 0 ;
                if (!bOverlapCountedOnEntry)
                {   // Then index count on the exit
                    bXOver |= DoIndexCount(i) ;
                }
                bOverlapCountedOnEntry = 0 ; 
            }
            else if (pevlst->plist[i].einfo & UEVENT_INTERSECTION)
            {   // Intersection so do index counting processing logic
                overallEventStat |= UEVENT_INTERSECTION ;
                bXOver |= DoIndexCount(i) ;
            }
            else if (pevlst->plist[i].einfo & UEVENT_INVERTARC)
            {
                overallEventStat |= UEVENT_INVERTARC ;
                if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
                {
                    // Only want the first inverse arc event
                    if (idxas == -1)
                        idxas = i ; 
                    bInvertArcSection = 1 ; 
                    bInvertArc = 1 ; 
                }
                else
                {   // Want last inverse arc event so always set it
                    idxae = i ; 
                    bInvertArc = 0 ; 
                }
            }
        }  // end for

        //////////////////////////////////////////////////////////
        // Here's where we create the actual index record entries
        //////////////////////////////////////////////////////////
        if (bXOver)
        {   // Then one or more crossovers occured within the current
            // event set so we want to create a new index record entry
            // Need the event set start and end indexes so that we can
            // set the various index record values

            // Step 1: work out which specific U event record we want to 
            // be the defining event for this record set.
            if (indexDelta > 0)
            {
                ievent = firstXOverIDX ;
            }
            else
            {
                ievent = lastXOverIDX ;
            }

            if (prevXOverESet == -1)
            {   
                // 1st Record being added

                // Then there is no previous event so we must define 
                // parameters for the section at the start of the curve
                pidxrecs[irecLen].esfromIDX = -1;
                pidxrecs[irecLen].estoIDX = pevlst->eventSets[es] ; 
                pidxrecs[irecLen].idxCount = lastIndexCount ; 

                pidxrecs[irecLen].ifromEvent = prevXOverEventIDX ;
                pidxrecs[irecLen].itoEvent = ievent ;

                // Starts at the start of the curve
                pcrv = pevlst->plist[ievent].pevent->pca ;  
                pidxrecs[irecLen].pss = pcrv->pStart ; 
                pidxrecs[irecLen].uss = 0.0 ;
    
                if (pevlst->plist[ievent].einfo & UEVENT_PRIMARYRECORD)
                {
                    pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psna ; 
                    pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u1 ; 
                }
                else
                {
                    pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psnb ; 
                    pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u2 ; 
                }
    
                pidxrecs[irecLen].us =  0.0 ; 
                pidxrecs[irecLen].ue =  pevlst->plist[ievent].u ; 

                // Save inverse arc condition
                if (bInvertArcSection || bInvertArc)
                    pidxrecs[irecLen].status |= REC_CONTAINSINVERTARC ;

                pidxrecs[irecLen].idxas = idxas ; 
                pidxrecs[irecLen].idxae = idxae ; 

                // Increment the Index record set count length
                irecLen++ ; 

                // Save all the needed parameters for the next iteration
                lastIndexCount = indexCount ; 
                if (!bInvertArc)
                    bInvertArcSection = 0 ;
                prevXOverESet = es ; 
                prevXOverEventIDX = ievent ; 
            }
            else
            {
                pidxrecs[irecLen].esfromIDX = pevlst->eventSets[prevXOverESet];
                pidxrecs[irecLen].estoIDX = pevlst->eventSets[es] ; 
                pidxrecs[irecLen].idxCount = lastIndexCount ; 

                pidxrecs[irecLen].ifromEvent = prevXOverEventIDX ;
                pidxrecs[irecLen].itoEvent = ievent ;

                if (pevlst->plist[prevXOverEventIDX].einfo & UEVENT_PRIMARYRECORD)
                {
                    pidxrecs[irecLen].pss = 
                        pevlst->plist[prevXOverEventIDX].pevent->psna ; 

                    pidxrecs[irecLen].uss =  
                        pevlst->plist[prevXOverEventIDX].pevent->u1 ; 
                }
                else
                {
                    pidxrecs[irecLen].pss = 
                        pevlst->plist[prevXOverEventIDX].pevent->psnb ; 

                    pidxrecs[irecLen].uss = 
                        pevlst->plist[prevXOverEventIDX].pevent->u2 ; 
                }
    
                if (pevlst->plist[ievent].einfo & UEVENT_PRIMARYRECORD)
                {
                    pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psna ; 
                    pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u1 ; 
                }
                else
                {
                    pidxrecs[irecLen].pse = pevlst->plist[ievent].pevent->psnb ; 
                    pidxrecs[irecLen].use =  pevlst->plist[ievent].pevent->u2 ; 
                }
    
                pidxrecs[irecLen].us =  pevlst->plist[prevXOverEventIDX].u ; 
                pidxrecs[irecLen].ue =  pevlst->plist[ievent].u ; 

                // Save inverse arc condition
                if (bInvertArcSection || bInvertArc)
                    pidxrecs[irecLen].status |= REC_CONTAINSINVERTARC ;

                pidxrecs[irecLen].idxas = idxas ; 
                pidxrecs[irecLen].idxae = idxae ; 

                // Increment the Index record set count length
                irecLen++ ; 

                // Save all the needed parameters for the next iteration
                lastIndexCount = indexCount ;
                if (!bInvertArc)
                    bInvertArcSection = 0 ;
                prevXOverESet = es ;
                prevXOverEventIDX = ievent ;
            }

            if (!bInvertArc)
                idxas = -1 ; 
        }
    } 

    if (prevXOverESet == -1)
    {   // Then no crossover events occurred
        return 0 ; 
    }

    // Finally we have to add the section off the end
    // The index count for this section will be the current index count
    // Set ievent to the last event in the list
    ievent = pevlst->listlen - 1 ; 

    pidxrecs[irecLen].esfromIDX = pevlst->eventSets[prevXOverESet];
    pidxrecs[irecLen].estoIDX = pevlst->eventSets[es] ; 
    pidxrecs[irecLen].idxCount = indexCount ; 

    pidxrecs[irecLen].ifromEvent = prevXOverEventIDX ;
    pidxrecs[irecLen].itoEvent = ievent ;

    if (pevlst->plist[prevXOverEventIDX].einfo & UEVENT_PRIMARYRECORD)
    {
        pidxrecs[irecLen].pss = 
            pevlst->plist[prevXOverEventIDX].pevent->psna ; 

        pidxrecs[irecLen].uss =  
            pevlst->plist[prevXOverEventIDX].pevent->u1 ; 
    }
    else
    {
        pidxrecs[irecLen].pss = 
            pevlst->plist[prevXOverEventIDX].pevent->psnb ; 

        pidxrecs[irecLen].uss = 
            pevlst->plist[prevXOverEventIDX].pevent->u2 ; 
    }
    
    pcrv = pevlst->plist[ievent].pevent->pca ;  

    pidxrecs[irecLen].pse = pcrv->pEnd ;
    pidxrecs[irecLen].use = 1.0 ; 

    pidxrecs[irecLen].us =  pevlst->plist[prevXOverEventIDX].u ; 
    pidxrecs[irecLen].ue =  1.0 ; 

    pidxrecs[irecLen].idxas = idxas ; 
    pidxrecs[irecLen].idxae = idxae ; 

    // Save inverse arc condition
    if (bInvertArcSection || bInvertArc)
        pidxrecs[irecLen].status |= REC_CONTAINSINVERTARC ;

    // Increment the Index record set count length
    irecLen++ ; 

    // Could do a test here to make sure that indexCount matches the index
    // count of the next segment, which should hold true for closed curves
    // If this is not the case, then the logic used to perform the index
    // counting will likely have to be modified. Since we start at an
    // index count of 0, (indexCount==0) should be valid at this point

    return 0 ; // success
}


int OffsetIndexing::IncEventSet(int e)
{
    e += 1 ; 
    if (e >= esetLength) 
        e = 0 ; // then wrap back 
    return e ; 
}


////////////////////////////////////////////////////////////
// Get the status of the specified event set
// sets status bit depending on conditions in the set
// Events set are Inv Arc Start, Overlap Start, and Intersection
// Possible flags set on return are:
//      UEVENT_INVERTARC
//      UEVENT_OVERLAP
//      UEVENT_INTERSECTION
int OffsetIndexing::GetSetStatus(int esidx)
{
    int i ; // loop counter into the event list
    int setcount ; // value of the setcount for the event set
    setcount = pevlst->eventSets[esidx]; 

    i = pevlst->eventSets[esidx]; // set start index for this event set
    setcount = pevlst->plist[i].setCount ; 

    int status = 0 ; 
    indexDelta = 0 ; 
    firstXOverIDX = lastXOverIDX = -1 ; 

    while ((i < pevlst->listlen) && (pevlst->plist[i].setCount == setcount))
    {
        // Inverted arc events cannot be deleted
        // thus we don't have to test for the UEVENT_DELETED condition
        if (pevlst->plist[i].einfo & UEVENT_INVERTARC)
        {
            overallEventStat |= UEVENT_INVERTARC ;
            if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
                bInvertArc = 1 ; 
            else
                bInvertArc = 0 ; 
        }

        if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) && 
            !(pevlst->plist[i].einfo & UEVENT_DELETED))
        {
            overallEventStat |= UEVENT_OVERLAP ;
            if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
                bInOverlap = 1 ;  
            else
                bInOverlap = 0 ; 
        }

        // A valid crossover is the main stop condition
        if (!(pevlst->plist[i].einfo & UEVENT_DELETED) &&
             (pevlst->plist[i].einfo & UEVENT_CROSSOVER))
        {
             overallEventStat |= UEVENT_CROSSOVER ;
             status |= UEVENT_CROSSOVER ;
             
             if (firstXOverIDX == -1)
                 firstXOverIDX = i ; 
             
             lastXOverIDX = i ; 

             DoIndexCount(i) ; 
        }

        i++ ;
    }


    if (indexDelta > 0)
        prevXOverEventIDX = firstXOverIDX ;
    else
        prevXOverEventIDX = lastXOverIDX ;

    minidxCount = 0 ; 
    indexCount = 0 ; 

    return status ; 
}

void OffsetIndexing::Dump(FILE *fp)
{
    int i ; 
    if (!fp)
        fp = fpDebugOut ; 
    for (i=0; i < irecLen; i++)
    {
        fprintf(fp, "IDX=%4d  %14.12f  %14.12f %3d %3d\n", 
            pidxrecs[i].idxCount, pidxrecs[i].us, pidxrecs[i].ue, 
            pidxrecs[i].esfromIDX, pidxrecs[i].estoIDX) ;
    }

    for (i=0; i < irecLen; i++)
    {
        fprintf(fp, "%3d ", i) ; 
        pidxrecs[i].pss->UPoint(pidxrecs[i].uss).Print(fp) ; fprintf(fp, " => ") ; 
        pidxrecs[i].pse->UPoint(pidxrecs[i].use).Print(fp) ; fprintf(fp, "\n") ; 
    }

    fprintf(fp, "\n") ; 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
