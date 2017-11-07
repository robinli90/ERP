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
// boolevents.cpp - extensions to the UEventList class used for 
// boolean operations with curves


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

#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif


UEvent *UEventList::BoolIXEvent(CCISNode *pisn, int i, int j, 
                                double &uvi, double &uvj)
{
    UEvent uevent ; 
    int eventtype ; 
    int counti, countj ;
    double uli, ulj ; // ulengths
    double usegi, usegj ; 
    double ucrvi, ucrvj ; 
    CS_SegPtr psni = pisn[i].psn ;
    CS_SegPtr psnj = pisn[j].psn ;

    uevent.pnt = psni->UPoint(uvi) ;

    uli = pisn[i].pcrv->SegmentULength(psni) ;
    ulj = pisn[j].pcrv->SegmentULength(psnj) ;

    usegi = uvi ; 
    usegj = uvj ; 

    ucrvi = psni->uo + usegi * uli ; 
    ucrvj = psnj->uo + usegj * ulj ; 

    counti = pisn[i].count ; 
    countj = pisn[j].count ; 

    // If one event occurs at the overall Curve u=1.0 point
    // and the overall base curved forms a closed loop, 
    // then we have to map the u=1.0 event to the start of the 
    // curve at u=0.0, and proceed after that

    // Note: unlike the offset case both events could be endpoints
    // so we have to test shifting both of them.

    // This could cause problems where we tolerance shift the end point
    // without actually changing the event point. May have to do some
    // extra testing around all the IsEndPoint tests


    if (IsEndPoint(pisn[i].pcrv, psni, usegi))
    {   // Then remap i event to 0.0
        // psni must point to last segment in the curve so 
        // jump to start segment, and adjust the associated
        // variables for the new segment
        psni = pisn[i].pcrv->pStart ; 
        // usegi must also be equal to 1.0 since this has to 
        // be the end point of the segment, so we are remapping
        // this to 0.0 as well
        usegi = 0.0 ; 
        ucrvi = 0.0 ;
        counti = 0 ; 
    }
    
    if (IsEndPoint(pisn[j].pcrv, psnj, usegj))
    {   // remap the j event to 0.0
        psnj = pisn[j].pcrv->pStart ;
        usegj = 0.0 ; 
        ucrvj = 0.0 ;
        countj = 0 ; 
    }
      
    // Do not have to test uo order because they're on different curves
    
    uevent.psna = psni ;
    uevent.psnb = psnj ;
    uevent.pca = pisn[i].pcrv ; 
    uevent.pcb = pisn[j].pcrv ; 
    uevent.u1 = usegi ; 
    uevent.u2 = usegj ; 
    uevent.cnta = counti ; 
    uevent.cntb = countj ; 
    // To calculate the overall U values we need the
    // relative U length for each segment
    uevent.ua = ucrvi ; 
    uevent.ub = ucrvj ; 
    
    // Only need set the one bit in this case
    eventtype = UEVENT_INTERSECTION ;
    return AppendPrimary(eventtype, uevent) ; 
}


UEvent *UEventList::BoolOVLPEvent(CCISNode *pisn, int i, int j, 
                                  double &uvi, double &uvj, int *evtype)
{
    UEvent uevent ; 
    int counti, countj ; 
    double uli, ulj ; // ulengths
    double usegi, usegj ; 
    double ucrvi, ucrvj ; 
    CS_SegPtr psni ;
    CS_SegPtr psnj ; // need to save these
    // Parameters specific to the overlapped case
    CS_VECTOR vi, vj ; 
    int reversed ;
    int isStartpoint ; 
    double theta ; 

    /////////////////////////////////////////////////////////////////////////
    // For overlaps we create 2 records, one at the start of the overlap
    // and the other at the end, thus we may end up effectively splitting an
    // overlap across two segments if we have to move one of the points 
    // to the start of the overall curve. This won't affect processing
    // later on since the CopySection() routine deals with sections that
    // span the end-start boundary of the curve. (Or in other words
    // a call such as CopySection(ua, ub) where ua > ub is valid)

    // Save these pointer values
    psni = pisn[i].psn ;  
    psnj = pisn[j].psn ;  

    //////////////////////////////////////////////////////////////
    // Need the direction information from the original curves
    // Must do this step first since it affects everything.
    // Note: this will work for arcs as well since the arcs
    // overlap and the points are common
    

    if (*evtype == -1)
    {   // Then we have to calculate the reversed condition
        isStartpoint = true ; 
        vi = psni->UTangent(uvi) ; 
        vj = psnj->UTangent(uvj) ; 
        theta = vi.Angle(vj) ; 
        reversed = false ; 
        if (theta > RADIAN90 || theta < -RADIAN90)
        {
            reversed = true ;
        }
    }
    else
    {   // Simply get the reverse state (which was calculated previously)
        reversed = *evtype & UEVENT_OVERLAPBREVERSE ;
        isStartpoint = false ; 
    }


    uli = pisn[i].pcrv->SegmentULength(psni) ; 
    ulj = pisn[j].pcrv->SegmentULength(psnj) ; 

    //////////////////////////////////////
    //////////////////////////////////////
    // 1st overlap intersection point
    //////////////////////////////////////
    //////////////////////////////////////
    usegi = uvi ; 
    usegj = uvj ; 
    ucrvi = psni->uo + usegi * uli ; 
    ucrvj = psnj->uo + usegj * ulj ; 
    counti = pisn[i].count ; 
    countj = pisn[j].count ; 

    uevent.pnt = psni->UPoint(usegi) ; 

    // now test remapping of 1st intersection point
    if (IsEndPoint(pisn[i].pcrv, psni, usegi))
    {   // Then remap i event to 0.0
        // psni must point to last segment in the curve so 
        // jump to start segment, and adjust the associated
        // variables for the new segment
        psni = pisn[i].pcrv->pStart ; 
        // usegi must also be equal to 1.0 since this has to 
        // be the end point of the segment, so we are remapping
        // this to 0.0 as well
        usegi = 0.0 ; 
        ucrvi = 0.0 ;
        counti = 0 ; 
    }

    // Same for other point
    if (IsEndPoint(pisn[j].pcrv, psnj, usegj))
    {   // remap the j event to 0.0
        psnj = pisn[j].pcrv->pStart ;
        usegj = 0.0 ; 
        ucrvj = 0.0 ;
        countj = 0 ; 
    }
      

    // TO DO - redo the boolean stuff with the new chaining structure 

    // If we swap records for Overlaps, then we have to check the 
    // OVERLAPBREVERSE bit and adjust the STARTPOINT values for 
    // each of the events created. Must also take into consideration
    // the fact that the overlap uvi and uvj values are ordered.
    // Thus uvi[0] < uvi[1] will always hold but, uvj[0] > uvj[1] 
    // will be true if the curves are reversed.

    uevent.psna = psni ;
    uevent.psnb = psnj ;
    uevent.pca = pisn[i].pcrv ; 
    uevent.pcb = pisn[j].pcrv ; 
    uevent.u1 = usegi ; 
    uevent.u2 = usegj ; 
    uevent.cnta = counti ;
    uevent.cntb = countj ;
    // To calculate the overall U values we need the
    // relative U length for each segment
    uevent.ua = ucrvi ; 
    uevent.ub = ucrvj ; 

    *evtype = UEVENT_OVERLAP ; // this has to be set
    
    if (isStartpoint)
        *evtype |= UEVENT_STARTPOINT ;

    if (reversed)
        *evtype |= UEVENT_OVERLAPBREVERSE ; // mask in reversed condition

    UEvent *pevent ; 
    pevent = AppendPrimary(*evtype, uevent) ; 

    return pevent ; 

}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Boolean Index Processing
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// This is the final stage in the processing of an offset. Once this 
// stage is complete all that remains is to build the final curves
// based on those curves which have matching index counts.

BooleanIndexing::BooleanIndexing()
{
    indexCount = 0 ; // current index count
    minidxCount = 0 ; // minimum count value during processing
    bInOverlap = 0 ; // inside overlap section indicator
    esetLength = 0 ; 
    pidxrecs = 0 ; 
    irecLen = 0 ; // number of index record entries defined
    pevlst = 0 ; 
    lastIndexCount = 0 ; 
}


BooleanIndexing::~BooleanIndexing()
{
    if (pidxrecs)
        delete[] pidxrecs ; 
}


int BooleanIndexing::Initialize(UEventList *plst)
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


int BooleanIndexing::DoIndexCount(int i)
{
    int retstat ; 
    int einfo = pevlst->plist[i].einfo ;
    int stat = pevlst->plist[i].pevent->status ;
    int prevIndexCount = indexCount ; 

    indexDelta = 0 ; 
    retstat = 0 ; 

    if (stat & UEVENT_CROSSOVER)
    {   // If it's not a crossover then don't do anything
        if (einfo & UEVENT_PRIMARYRECORD)
        {   // Normal forward direction processing
            if (stat & UEVENT_LEFT)
                indexCount++ ; 
            else
                indexCount-- ; 
        }   
        else
        {   // Have to reverse the sense of what's happening
            if (stat & UEVENT_RIGHT)
                indexCount++ ; 
            else
                indexCount-- ; 
        }

        // Save minimum index count value
        if (indexCount < minidxCount)
            minidxCount = indexCount ; 
    
        // Set all the index tracking management variables
        if (firstActiveIDX == -1)
            firstActiveIDX = i ; 
        lastActiveIDX = i ;

        indexDelta = indexCount - prevIndexCount ;
        
        retstat = stat & 
            (UEVENT_CROSSOVER | UEVENT_LEFT | UEVENT_RIGHT) ;
    }
    else
    {   // This is an overlap touch off condition. In this situation
        // the index count will not change
        if (firstActiveIDX == -1)
            firstActiveIDX = i ; 
        lastActiveIDX = i ;
        retstat = stat & (UEVENT_LEFT | UEVENT_RIGHT) ;
    }

    return retstat ; // return state of this event
}




int BooleanIndexing::CalcIndexes()
{
    int es ; // current event set
    int esexit ; 
    int esEnd ; // used as a work variable, marks end of event set
    int stat ;  // work var 

    // Loop through each event set, note we are starting with the first
    // event since we are always looking at two events to define an
    // index curve section (which exists between two separate events

    // initialize the first index record and then proceed with normal 
    // processing. The first record is really a special case because
    // we havent had to do any index counting yet
    
    // From the first event set we have to extract the overlap  
    // conditions 

    status = 0 ; // initialize the state information 
    
    // Reset index count variables
    indexCount = 0 ; 
    minidxCount = 0 ; // min should be negative or 0 when finished
    lastIndexCount = 0 ; 
    bInOverlap = 0 ;
    overallActiveStat = 0 ; 


    if (esetLength == 0)
        return 0 ; // nothing to do
    
    stat = 0 ; 
    prevActiveEventIDX = 0 ; 

    // Perform the main scan processing loop. We want to move ahead to the
    // next valid Xover style intersection, maintaining various status 
    // information along the way. Each time we move to a new event set
    // boundary has to be recorded as to the curve information of the 
    // last X over event. All we need to store at each node is the curves
    // overall u value, and the segment node that the u value occurs on.
    // Also need the index count for that section, as well as any overlap
    // regions contained in the section. 
    
   
    // Pointers used to save where the first and last cross over events 
    // occured so we can select the correct one later on.

    // We want to process the first active event set twice. Thus 
    // we have to find the first active event set, and start at 
    // that event set for processing. Then we keep a count of 
    // how many times that node (eventSet[]) has been processed
    // and after dealing with it the second time, we exit.

    int firstActiveESet ; 
    int bOverlapSection ; 

    firstActiveESet = FindFirstActiveESet() ; 
    if (firstActiveESet == -1)
    {   // Then there are no active event sets
        return 0 ; // nothing to do 
    }
 
    prevActiveESet = firstActiveESet ; 
    prevActiveEventIDX = lastActiveIDX ;
    esexit = firstActiveESet ; // so that we don't immediately exit the loop
    prevActiveESet = firstActiveESet ;
    bOverlapSection = 0 ; 
    es = 0 ; 

    do 
    {
        es = IncEventSet(es) ;
        esEnd = pevlst->eventSets[es+1] ;
        if (esEnd == -1)
            esEnd = pevlst->listlen ;

        int bActiveStat = 0 ; // Set if an X over or overlap event is logged
        // which means we want to create a new entry in the  

        indexDelta = 0; 
        firstActiveIDX = lastActiveIDX = -1 ; // initialized as invalid

        if (bInOverlap)
            bOverlapSection = 1 ; 

        // We want to label the overlap crossovers as we leave the overlap 
        // section. Also overlap sections need to be included in the event 
        // set

        // eventSets[] define the index start point for each event set
        // esEnd is the index of the start of the next event set (or the
        // end of the array)

        // Loop through the event set
        for (int i=pevlst->eventSets[es]; i < esEnd; i++)
        {
            if (pevlst->plist[i].einfo & UEVENT_DELETED)
                continue ; // skip the event

            // Main processing occurs here
            // Want to remember if a crossover occurs
            if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                (pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap start point
                bInOverlap = 1 ;
                bActiveStat |= DoIndexCount(i) ;
                // Only index count overlap crossovers on exit
            }
            else if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) &&
                     !(pevlst->plist[i].einfo & UEVENT_STARTPOINT))
            {   // Overlap end point
                bInOverlap = 0 ;
                bActiveStat |= DoIndexCount(i) ;
            }
            else if (pevlst->plist[i].einfo & UEVENT_INTERSECTION)
            {   // Intersection so do index counting processing logic
                bActiveStat |= DoIndexCount(i) ;
            }
        } // end for

        //////////////////////////////////////////////////////////
        // Here's where we create the actual index record entries
        //////////////////////////////////////////////////////////
        // The prevActiveESet != eset0 condition is to ensure that we 
        // have at least one active set defined previously
        if (bActiveStat)
        {   // Then one or more crossovers occured within the current
            // event set so we want to create a new index record entry
            // Need the event set start and end indexes so that we can
            // set the various index record values
            overallActiveStat |= bActiveStat ; 
            // Step 1: work out which specific U event record we want to 
            // be the defining event for this record set.
            int ievent ; // array offset to the event
            if (indexDelta > 0)
            {
                ievent = firstActiveIDX ;
            }
            else
            {
                ievent = lastActiveIDX ;
            }

            pidxrecs[irecLen].esfromIDX = pevlst->eventSets[prevActiveESet];
            pidxrecs[irecLen].estoIDX = pevlst->eventSets[es] ; 
            pidxrecs[irecLen].idxCount = lastIndexCount ; 
            pidxrecs[irecLen].status = bActiveStat ;
            
            if (bOverlapSection)
                pidxrecs[irecLen].status |= UEVENT_OVERLAP ; 
            
            // want to remember all the conditions that existed while 
            // calculating the indexes
            overallActiveStat |= pidxrecs[irecLen].status ;


            pidxrecs[irecLen].ifromEvent = prevActiveEventIDX ;
            pidxrecs[irecLen].itoEvent = ievent ;
            
            pevlst->plist[prevActiveEventIDX].irsIDX = irecLen ; 
            pevlst->plist[ievent].ireIDX = irecLen ; 

            if (pevlst->plist[prevActiveEventIDX].einfo & UEVENT_PRIMARYRECORD)
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[prevActiveEventIDX].pevent->psna ; 

                pidxrecs[irecLen].uss =  
                    pevlst->plist[prevActiveEventIDX].pevent->u1 ; 

                // The start and end points will always be on the same
                // curve so we don't need to duplicate this in the end
                // point setting section that follows
                pidxrecs[irecLen].pcrv = 
                    pevlst->plist[prevActiveEventIDX].pevent->pca ; 
            }
            else
            {
                pidxrecs[irecLen].pss = 
                    pevlst->plist[prevActiveEventIDX].pevent->psnb ; 

                pidxrecs[irecLen].uss = 
                    pevlst->plist[prevActiveEventIDX].pevent->u2 ; 

                pidxrecs[irecLen].pcrv = 
                    pevlst->plist[prevActiveEventIDX].pevent->pcb ; 
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

            pidxrecs[irecLen].us =  pevlst->plist[prevActiveEventIDX].u ; 
            pidxrecs[irecLen].ue =  pevlst->plist[ievent].u ; 

            // Increment the Index record set count length
            irecLen++ ; 

            // Save all the needed parameters for the next iteration
            lastIndexCount = indexCount ; 
            prevActiveESet = es ; 
            prevActiveEventIDX = ievent ; 

            if (!bInOverlap)
                bOverlapSection = 0 ; 
        }

        if (bInOverlap)
            bOverlapSection = 1 ; 

    } while (es != esexit) ; 

    // Could do a test here to make sure that indexCount matches the index
    // count of the next segment, which should hold true for closed curves
    // If this is not the case, then the logic used to perform the index
    // counting will likely have to be modified. Since we start at an
    // index count of 0, (indexCount==0) should be valid at this point

    return 0 ; // success
}


void BooleanIndexing::NormalizeIndexes()
{
    // We want to adjust all indexes so that the minimum starts at 0
    // say min=-2  (-2- (-2) = 0)   (2 - -2 = 4 etc... )
    // say min=1   (1-1 = 0 2-1 = 1 ...)
    if (minidxCount == 0)
        return ; // don't have to do anything

    for (int i=0; i < irecLen; i++)
        pidxrecs[i].idxCount -= minidxCount ;
    minidxCount = 0 ; 
}

int BooleanIndexing::IncEventSet(int e)
{
    e += 1 ; 
    if (e >= esetLength) 
        e = 0 ; // then wrap back 
    return e ; 
}


int BooleanIndexing::FindFirstActiveESet()
{
    int es, esEnd ; 

    es = 0 ; 
    for (es = 0; es < esetLength ; es++)
    {
        esEnd = pevlst->eventSets[es+1] ;
        if (esEnd == -1)
            esEnd = pevlst->listlen ;

        int bActiveStat = 0 ; // Set if an X over or overlap event is logged
        // which means we want to create a new entry in the  

        bInOverlap = 0 ; 
        indexDelta = 0; 
        firstActiveIDX = lastActiveIDX = -1 ; // initialized as invalid

        // We want to label the overlap crossovers as we leave the overlap 
        // section. Also overlap sections need to be included in the event 
        // set

        // eventSets[] define the index start point for each event set
        // esEnd is the index of the start of the next event set (or the
        // end of the array)

        // Loop through the event set
        for (int i=pevlst->eventSets[es]; i < esEnd; i++)
        {
            if (pevlst->plist[i].einfo & UEVENT_DELETED)
                continue ; // skip the event

            if ((pevlst->plist[i].einfo & UEVENT_OVERLAP) ||
                (pevlst->plist[i].einfo & UEVENT_INTERSECTION)) 
            {   // This is an active event and thus we must be in 
                // an active event set. 
                
                if (pevlst->plist[i].einfo & UEVENT_OVERLAP)
                {
                    if (pevlst->plist[i].einfo & UEVENT_STARTPOINT)
                        bInOverlap = 1 ; 
                    else
                        bInOverlap = 0 ; 
                }
                lastActiveIDX = i ; 
                return es ; 
            }
        } // end for
    }
    return -1 ; // no active event set found
}

void BooleanIndexing::Dump(FILE *fp)
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
        fprintf(fp,"%3d ", i) ; 
        pidxrecs[i].pss->UPoint(pidxrecs[i].uss).Print(fp) ; 
        fprintf(fp, " => ") ; 
        pidxrecs[i].pse->UPoint(pidxrecs[i].use).Print(fp) ; 
        fprintf(fp, "\n") ; 
    }

    fprintf(fp, "\n") ; 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
    