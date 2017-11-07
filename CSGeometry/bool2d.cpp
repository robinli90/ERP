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
// bool2d.cpp - 2D boolean operations class


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

#ifdef	CSDEBUG
#define CS_DEBUG(a)                   
#else
#define CS_DEBUG(a)
#endif

CS_Curve *BoolConnectCurve(IndexRecord **pidxrecs, int irecLen) ;
static void UnionTagHoles(CS_CurveSet &crvset) ;


Bool2D::Bool2D()
{
    error = 0 ; 
}


Bool2D::~Bool2D()
{
}


int Bool2D::Setup(CS_Curve *pcrva, CS_Curve *pcrvb)
{
    if (!pcrva->pStart)
        return 1 ; // no curve defined, nothing to do

    if (!pcrva->Closed() || !pcrvb->Closed())
        return 2 ; // cannot union curves if they are not both closed

    // Initial setup 
    pcrva->SetDirection(CCW) ; 
    pcrva->Finalize() ; // validate all u parms and closed condition
    
    pcrvb->SetDirection(CCW) ; 
    pcrvb->Finalize() ; // validate all u parms and closed condition

    /*
    ////////////////////////////////
    // Output raw offset curve
    *prescrvs = new CS_Curve*[2] ; 
    CS_Curve *pc = new CS_Curve ; 
    pc->CopyCurve(*this) ; 
    (*prescrvs)[0] = pc ; 
    *rescount = 1 ; 
    return 0 ; // success
    // end raw output
    ////////////////////////////////
    */

    if (IntersectCurves(pcrva, pcrvb, evlstA, evlstB))
        return 3 ; // intersection event error


    // Now do all the required index counting processing including the 
    // intersection event Merging (just as is done in the Offset routine)


    ////////////////////////////////
    ////////////////////////////////
    // Post-process the event lists
    ////////////////////////////////
    ////////////////////////////////

    // CS_DEBUG(evlst.DumpList()) ; 
    // These work the same way the offset routine does
    evlstA.SortList() ; 
    evlstA.MergeOverlaps() ;
    evlstA.LabelCrossovers() ; 

    evlstB.SortList() ; 
    evlstB.MergeOverlaps() ;
    evlstB.LabelCrossovers() ; 
    
    CS_DEBUG(fprintf(fpDebugOut,"After xover\n   A\n") ; ) ; 
    CS_DEBUG(evlstA.DumpList() ; ) ;
    CS_DEBUG(fprintf(fpDebugOut,"   B\n") ; ) ;
    CS_DEBUG(evlstB.DumpList() ; ) ;

    bia.pcrv = pcrva ;
    bia.Initialize(&evlstA) ;     // Initialize and allocate memory
    bia.CalcIndexes() ; // create the list of index records
    bia.NormalizeIndexes() ;

    bib.pcrv = pcrvb ;
    bib.Initialize(&evlstB) ;     // Initialize and allocate memory
    bib.CalcIndexes() ; // create the list of index records
    bib.NormalizeIndexes() ;

    return 0 ;
}


int Bool2D::Union(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) 
{
    int err ; 
    // Save the result set pointer
    if (!pcrva || !pcrvb || !presultSet)
        return -1 ; // something missing
    presSet = presultSet; 

    // The setup routine performs the curve intersection and creates all 
    // the necessary event set data. After the events are generated
    // and preprocessed, index records are then created for the two
    // curves, labelling crossovers and overlaps.
    if ((err = Setup(pcrva, pcrvb)) != 0)
    {
        sprintf(szGeomErrString, 
            "Setup error %d occured in Bool2D::Union()\n", err) ; 
        return err ; 
    }

    // With the index records created, we can now connect the Index 
    // records together to form the final output curves
    return UnionConnect() ; 
}

int Bool2D::Intersect(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) 
{
    int err ; 
    // Save the result set pointer
    if (!pcrva || !pcrvb || !presultSet)
        return -1 ; // something missing
    presSet = presultSet; 

    if ((err = Setup(pcrva, pcrvb)) != 0)
    {
        sprintf(szGeomErrString, 
            "Setup error %d occured in Bool2D::Intersect()\n", err) ; 
        return err ; 
    }

    return IntersectConnect() ; 
}

int Bool2D::Difference(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) 
{
    int err ; 
    // Save the result set pointer
    if (!pcrva || !pcrvb || !presultSet)
        return -1 ; // something missing
    presSet = presultSet; 

    if ((err = Setup(pcrva, pcrvb)) != 0)
    {
        sprintf(szGeomErrString, 
            "Setup error %d occured in Bool2D::Intersect()\n", err) ; 
        return err ; 
    }

    return DifferenceConnect() ; 
}


///////////////////////////////////////////////////////////////////////
// Returns the union of the two index record sets. If the two curves
// are disjoint, then copies of both curves are returned in the 
// CS_CurveSet crvset. If one curve completely contains the other, then
// a copy of the curve is returned as the result in crvset. Otherwise
// the two curves are combined to form the final union curve set 
// created by following the overall outside curve, as well as any 
// holes that are generated by the process. 
int Bool2D::UnionConnect() 
{
    // Now do final index analysis to generate the A+B (union) curve
    // Here we must also check for the various special cases that can
    // occur, specifically if A is inside B or B is inside A. This can
    // also be the case even if they touch one another.
    
    CS_Curve *pcrv ; // tmp work var

    if (evlstA.listlen == 0)
    {   // Then there were no events and thus the curves do not contact
        // each other at all. Check to see if one curve is inside the 
        if (bia.pcrv->PointInside(bib.pcrv->StartPoint()))
        {   // Then B is entirely inside A, result is A
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        if (bib.pcrv->PointInside(bia.pcrv->StartPoint()))
        {   // Then A is entirely inside B, result is B
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bib.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        // Disjoint curves
        pcrv = new CS_Curve ; 
        pcrv->CopyCurve(*bia.pcrv) ; 
        presSet->AddCurve(pcrv) ; 
        
        pcrv = new CS_Curve ; 
        pcrv->CopyCurve(*bib.pcrv) ; 
        presSet->AddCurve(pcrv) ; 

        return 0 ; 
    }


    // The two curves touch one another somehow. 

    if (bia.irecLen == 0 || !(bia.overallActiveStat & UEVENT_CROSSOVER))
    {   // Then the two curves touch one another at one or more points. 
        // Using the status info we can determine which curve is inside 
        // the other. If B touches off of A on the left, then A is the 
        // result otherwise B is the result
        if (bia.overallActiveStat & UEVENT_LEFT)
        {
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        if (bia.overallActiveStat & UEVENT_RIGHT)
        {
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bib.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }


        // If we get to here then an error has occured, since the curves
        // did touch one another yet we got no left or right status
        // bit set.
        return 1 ;
    }


    //////////////////////////////////////////////////////////////
    // Main Logic Processing Control Switches
    //////////////////////////////////////////////////////////////
    // initialize scanmode for standard difference processing
    int iret = 0; 
    aindex = 0 ; 
    bindex = 0 ; 
    breversed = 0 ; 

    iret = BoolConnect("Union") ; 
    
    // Now tag the holes if any
    UnionTagHoles(*presSet) ; 

    return iret ; 
}

int Bool2D::IntersectConnect() 
{
    // Now do final index analysis to generate the A.B (intersect) curves
    // Here we must also check for the various special cases that can
    // occur, specifically if A is inside B or B is inside A. This can
    // also be the case even if they touch one another.
    
    CS_Curve *pcrv ; // tmp work var

    if (evlstA.listlen == 0)
    {   // Then there were no events and thus the curves do not contact
        // each other at all. Check to see if one curve is inside the 

        // The two following ifs are the reverse of the Union operation
        if (bia.pcrv->PointInside(bib.pcrv->StartPoint()))
        {   // Then B is entirely inside A, result is B
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bib.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        if (bib.pcrv->PointInside(bia.pcrv->StartPoint()))
        {   // Then A is entirely inside B, result is A
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        // Disjoint curves, no result
        return 0 ; 
    }


    // The two curves touch one another somehow. 

    if (bia.irecLen == 0 || !(bia.overallActiveStat & UEVENT_CROSSOVER))
    {   // Then the two curves touch one another at one or more points. 
        // Using the status info we can determine which curve is inside 
        // the other. If B touches off of A on the left, then B is 
        // inside of A and thus B is the result. If B is to the 
        // right of A then, then A is the result since it is inside.
        if (bia.overallActiveStat & UEVENT_LEFT)
        {
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bib.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        if (bia.overallActiveStat & UEVENT_RIGHT)
        {
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        // If we get to here then an error has occured, since the curves
        // did touch one another yet we got no left or right status
        // bit set.
        return 1 ;
    }

    //////////////////////////////////////////////////////////////
    // Main Logic Processing Control Switches
    //////////////////////////////////////////////////////////////
    // initialize scanmode for standard difference processing
    aindex = 1 ; 
    bindex = 1 ; 
    breversed = 0 ; 

    return BoolConnect("Intersection") ; 
}


int Bool2D::DifferenceConnect() 
{
    // Now do final index analysis to generate the A.B (intersect) curves
    // Here we must also check for the various special cases that can
    // occur, specifically if A is inside B or B is inside A. This can
    // also be the case even if they touch one another.

    CS_Curve *pcrv ; // tmp work var

    if (bia.pevlst->listlen == 0)
    {   // Then there were no events and thus the curves do not contact
        // each other at all. Check to see if one curve is inside the 

        // The two following ifs are the reverse of the Union operation
        if (bia.pcrv->PointInside(bib.pcrv->StartPoint()))
        {   // Then B is entirely inside A, result is A and B=hole
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bib.pcrv) ; 
            pcrv->statflags |= CS_HOLECURVE ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        if (!bib.pcrv->PointInside(bia.pcrv->StartPoint()))
        {   // Then the curves are disjoint so result is A
            pcrv = new CS_Curve ; 
            pcrv->CopyCurve(*bia.pcrv) ; 
            presSet->AddCurve(pcrv) ; 
            return 0 ; 
        }

        // Else A is entirely inside B, result is null
        return 0 ; 
    }


    //////////////////////////////////////////////////////////////
    // Main Logic Processing Control Switches
    //////////////////////////////////////////////////////////////
    // initialize scanmode for standard difference processing
    aindex = 0 ; 
    bindex = 1 ; 
    breversed = 1; 

    // The two curves touch one another somehow. 
    if (!(bia.overallActiveStat & UEVENT_CROSSOVER))
    {   // Then the two curves touch one another at one or more points, 
        // but they never cross over each other.
        // Using the status info we can determine which curve is inside 
        // the other. If B touches off of A on the left, then B is 
        // inside of A, which represents a special case where the 
        // scanMode is set to 1. 
        if (bia.overallActiveStat & UEVENT_LEFT)
        {
            // For this special case we scan A0/B0,V 
            bindex = 0 ; // clear this
        }

        // Otherwise we have a null result
        if (bia.overallActiveStat & UEVENT_RIGHT)
        {
            return 0 ; 
        }
    }

    return BoolConnect("Difference") ; 
}


int Bool2D::BoolConnect(char *connectType) 
{
    // We have at least an index record and an intersection which 
    // means we must walk along and follow the various curve segments. To do
    // the walk around we follow a curve prioriterization scheme. At each
    // intersection (or event set node) we must scan the event set to
    // find all the adjacent index records and then decide which index
    // record to follow (and thus connect) to continue building the 
    // final output curve. The prioriterization is defined by the 
    // aindex, bindex, and breversed variables. These variables must be
    // set correctly before this routine is called.

    int pirLen ; 
    IndexRecord **pir ;
    
    pir = new IndexRecord*[bia.irecLen + bib.irecLen + 2] ; 

    int irap ; // the number of A index records processed
    int irbp ; // the number of B index records processed
    int i ; 

    int nxtaidx, startaidx ; 
    int bCompletedCurve ; 

    irap = 0 ; 
    irbp = 0 ; 

    // Find the first 1 index count section on the A curve
    for (i=0; i < bia.irecLen ; i++)
    {
        if ((bia.pidxrecs[i].idxCount == aindex) && 
           !(bia.pidxrecs[i].status & UEVENT_OVERLAP))
            break ; 
        // want to ignore non 1 index records (if they are not 
        // overlap records)
        if (!(bia.pidxrecs[i].status & UEVENT_OVERLAP))
        {
            bia.pidxrecs[i].status |= UEVENT_DELETED ; 
            irap++ ; 
        }
    }
    startaidx = i ; 

    // thus starting on the first active section of the A curve with minimum
    // count value. 

    try
    {
        while (irap < bia.irecLen)
        {   // initialize and create a curve
            OnA = 1 ; 
            nxtaidx = iridx = startaidx ; 
            // Use the same space in the pir[] arrary
            pirLen = 0 ; 
            pir[pirLen++] = &bia.pidxrecs[iridx] ;
            bia.pidxrecs[iridx].status |= UEVENT_DELETED ; 
            irap++ ; // we have effectively taken 1 IR record out
            startpnt = pir[0]->pss->UPoint(pir[0]->uss) ; 

            bCompletedCurve = 0 ; 

            while (!bCompletedCurve)
            {
                GetNextIRSection() ;
                if (error)
                    throw error ; // something went wrong

                if (OnA)
                {
                    pir[pirLen] = &bia.pidxrecs[iridx] ;
                    bia.pidxrecs[iridx].status |= UEVENT_DELETED ; 
                    irap++ ; // we have effectively taken 1 IR record out
                }
                else
                {
                    pir[pirLen] = &bib.pidxrecs[iridx] ;
                    bib.pidxrecs[iridx].status |= UEVENT_DELETED ; 
                    irbp++ ; // we have effectively taken 1 IR record out
                }

                if (startpnt == endpnt)
                    bCompletedCurve = 1 ; // done

                pirLen++ ; 
            } 


            if (bCompletedCurve)
            {   
                // Now simply walk the list of IndexRecords and 
                // add the curve sections together
                CS_Curve *prescrv ; 
                prescrv = BoolConnectCurve(pir, pirLen) ; 

                if (prescrv)
                    presSet->AddCurve(prescrv) ; 
            }
            else
            {   // Then something went wrong in the processing
                break ; // nothing else to do 
            }


            // Now find next A section to process if any
            int prevnxtaidx = nxtaidx ; 
            nxtaidx = ModuloInc(nxtaidx, bia.irecLen) ; 
            i = nxtaidx ; 
            while (i != prevnxtaidx)  // (ie we've looped around) 
            {
                if (!(bia.pidxrecs[i].status & UEVENT_DELETED))
                {   // Then it hasn't been processed so need to check it
                    if ((bia.pidxrecs[i].idxCount == aindex) && 
                        !(bia.pidxrecs[i].status & UEVENT_OVERLAP))
                        break ; 
                    // want to ignore non-0 index records (if they are not 
                    // overlap records)
                    if (!(bia.pidxrecs[i].status & UEVENT_OVERLAP))
                    {   // Skip index=1 records
                        bia.pidxrecs[i].status |= UEVENT_DELETED ; 
                        irap++ ; 
                    }
                }
                i = ModuloInc(i, bia.irecLen) ; 
            }
            startaidx = i ; 
        
            if (startaidx == prevnxtaidx)
                break ; // something went wrong or nothing left to do

        }
    }
    catch (int err) 
    {
        sprintf(szGeomErrString, 
            "Error %d occured in Bool2D::%s\n", err, connectType) ; 
    }

    delete[] pir ; 

    return error ; 
}

// Returns true if an adjacent curve is found. If an adjacent curve is
// found then the OnA and iridx is updated. 
// scanMode = 0, process normally for difference operation of 
// {A0/B1, X} , if scanMode == 1 then {A0/B0, X}

// returns the endpoint of the active section that is being returned as 
// the next section to be processed
// returns TRUE if it finds something, else it returns FALSE
void Bool2D::GetNextIRSection() 
{
    // Must search for the next index record set that should be 
    // followed based on the priority rules for traversing union sets.
    // Also must take into account the process of reverse referencing 
    // to just those index records that we can follow through the 
    // backward index records in UEvent, and UEventRecord

    //  is the simplest since we are alternating back and forth
    // from A to B until we end up back where we started

    // intersect if similar to union in the with the only difference 
    // being that the 1 index records are followed and the 0 index
    // records are ignored. Overlap records are followed using the 
    // exact same rule as for the union operation.

    // For two curves the maximum number of adjacent curves is 3 which
    // occurs at an intersection.
    
    IndexRecord *pirec ; 
    UEventRecord *puerec, *pueback ; 
    int nxtaidx ; 
    int nxtbidx ; // complementary event list index (reverse lookup)
    int elidx ;
    int esidx ; // event set start idx

    if (OnA)
    {
        // Take a look at the secondary events first since we must be
        // switching sides at an event (or following an overlap event
        // which is effectively the same thing)
        
        // For intersect processing all the IndexRecords will be connecting
        // to the end point (just like the union case)
        nxtaidx = ModuloInc(iridx, bia.irecLen) ; 
        if (bia.pidxrecs[nxtaidx].status & UEVENT_OVERLAP)
        {   // We have to do the overlap testing logic
            // From an overlap we could end up following either 
            // the A or B section, whichever has the matching index 
            // count going in the proper direction. If we are going
            // backwards then we must look at the ireIDX instead of 
            // the irsIDX. If no valid index follows then an error
            // has occured since two overlaps cannot follow one
            // another

            /////////////////////////////////////////////////
            // Man is this convoluted (See RR-Vol2 pg 163) //
            /////////////////////////////////////////////////

            // First check the B section since normally we would be switching
            // back and forth between A and B sections
            
            // First get the UEventRecord in the A list
            elidx = bia.pidxrecs[iridx].estoIDX ;
            puerec = &evlstA.plist[elidx] ; 

            // then do reverse lookup through the UEvent defined within 
            // the UEventRecord
            pueback = &(evlstB.plist[puerec->pevent->scndIDX]) ;
            esidx = evlstB.eventSets[pueback->setCount] ;

            if (!breversed)
            {   // Going forward normally
                nxtbidx = evlstB.plist[esidx].irsIDX ;
            }
            else
            {   // Grab the end since we're going backwards on B
                nxtbidx = evlstB.plist[esidx].ireIDX ;
            }

            if (bib.pidxrecs[nxtbidx].idxCount == bindex)
            {
                iridx = nxtbidx ; 
                OnA = 0 ; 
                pirec = &bib.pidxrecs[iridx] ; 
                if (!breversed)
                {
                    endpnt = pirec->pse->UPoint(pirec->use) ;
                }
                else
                {
                    endpnt = pirec->pss->UPoint(pirec->uss) ;
                    pirec->status |= UEVENT_REVERSED ; 
                }
            }
            else
            {   // Then one way or another we will continue on the 
                // A section, whether it be an overlap or not
                // Note we could test the value of the A section
                // index and if it didn't match aindex then signal
                // an error - left as future extension if required
                iridx = nxtaidx ; 
                pirec = &bia.pidxrecs[iridx] ; 
                endpnt = pirec->pse->UPoint(pirec->use) ;
            }
        }
        else
        {   // Process normally
            // elidx = bia.pidxrecs[iridx].itoEvent ;
            
            elidx = bia.pidxrecs[iridx].estoIDX ;
            puerec = &evlstA.plist[elidx] ; 
            // We only have to worry about going in the foward direction 
            // in the secondary curve
            pueback = &(evlstB.plist[puerec->pevent->scndIDX]) ;
            esidx = evlstB.eventSets[pueback->setCount] ;

            OnA = 0 ; // toggle this

            if (!breversed)
            {
                iridx = evlstB.plist[esidx].irsIDX ;
                pirec = &bib.pidxrecs[iridx] ; 
                endpnt = pirec->pse->UPoint(pirec->use) ;
            }
            else
            {
                iridx = evlstB.plist[esidx].ireIDX ;
                pirec = &bib.pidxrecs[iridx] ; 
                pirec->status |= UEVENT_REVERSED ; 
                endpnt = pirec->pss->UPoint(pirec->uss) ;
            }
        }
    }
    else
    {
        // If not OnA then processing is almost identical to the OnA
        // processing except we reverse the A's and B's in most places
        // as well as deal with slightly differenct direction 
        // situations as well
        if (!breversed)
        {
            nxtbidx = ModuloInc(iridx, bib.irecLen) ; 
        }
        else
        {   // we have to count backwards
            nxtbidx = iridx - 1 ; 
            if (nxtbidx < 0)
                nxtbidx = bib.irecLen - 1 ; 
        }
        
        if (bib.pidxrecs[nxtbidx].status & UEVENT_OVERLAP)
        {   // We have to do the overlap testing logic
            // From an overlap we could end up following either 
            // the A or B section, whichever has the matching index 
            // count going in the proper direction. If we are going
            // backwards then we must look at the ireIDX instead of 
            // the irsIDX. If no valid index follows then an error
            // has occured since two overlaps cannot follow one
            // another

            /////////////////////////////////////////////////
            // Man is this convoluted (See RR-Vol2 pg 163) //
            /////////////////////////////////////////////////

            // First check the A section since normally we would be switching
            // back and forth between A and B sections
            if (breversed)
                elidx = bib.pidxrecs[iridx].esfromIDX ;
            else
                elidx = bib.pidxrecs[iridx].estoIDX ;

            puerec = &evlstB.plist[elidx] ; 

            // then do reverse lookup through the UEvent defined within 
            // the UEventRecord
            pueback = &(evlstA.plist[puerec->pevent->primIDX]) ;
            esidx = evlstA.eventSets[pueback->setCount] ;

            nxtaidx = evlstA.plist[esidx].irsIDX ;

            if (bia.pidxrecs[nxtaidx].idxCount == aindex)
            {   // This is the one we want to follow
                iridx = nxtaidx ; 
                OnA = 1 ; 
                pirec = &bia.pidxrecs[iridx] ; 
                endpnt = pirec->pse->UPoint(pirec->use) ;
            }
            else
            {   // Then one way or another we will continue on the 
                // B section, whether it be an overlap or not
                // Note we could test the value of the B section
                // index and if it didn't match bndex then signal
                // an error - left as future extension if required
                iridx = nxtbidx ; 
                pirec = &bib.pidxrecs[iridx] ; 
                if (!breversed)
                {
                    endpnt = pirec->pse->UPoint(pirec->use) ;
                }
                else
                {
                    endpnt = pirec->pss->UPoint(pirec->uss) ;
                    pirec->status |= UEVENT_REVERSED ; 
                }
            }
        }
        else
        {   // Process normally
            // elidx = bia.pidxrecs[iridx].itoEvent ;
            if (breversed)
                elidx = bib.pidxrecs[iridx].esfromIDX ;
            else
                elidx = bib.pidxrecs[iridx].estoIDX ;

            puerec = &evlstB.plist[elidx] ; 
            // We only have to worry about going in the foward direction 
            // in the secondary curve
            pueback = &(evlstA.plist[puerec->pevent->primIDX]) ;
            esidx = evlstA.eventSets[pueback->setCount] ;
            iridx = evlstA.plist[esidx].irsIDX ;
            pirec = &bia.pidxrecs[iridx] ; 
            endpnt = pirec->pse->UPoint(pirec->use) ;
            OnA = 1 ; // toggle this
        }
    }
}



CS_Curve *BoolConnectCurve(IndexRecord **pidxrecs, int irecLen) 
{
    int i ; 
    CS_POINT crvsp, crvep ;
    CS_Curve *prescrv = new CS_Curve ; 

    try 
    { 
        for (i=0;  i < irecLen; i++)
        {
            // First extract it out and 
            // create a CS_Curve based on the us,ue parameters
            // Then see if it can be connected to the back of any 
            // other curves and add it to the active list or create
            // a new active list entry
            // Note we put the this pointer in so that it will be
            // easier to change the logic later when we create an new
            // offset curve and don't modify the original 

            // With the union operation all the curve sections are traversed
            // in a counter clockwise manner so we don't have to worry about
            // reversing the direction of any of the curve sections
            CS_Curve *pc = pidxrecs[i]->pcrv->CopySection(pidxrecs[i]->pss, 
                                                        pidxrecs[i]->pse, 
                                                        pidxrecs[i]->uss, 
                                                        pidxrecs[i]->use, 
                                                        SEGMENTBASED_UVALUES) ;  

            
            if (!pc)
            {   // Error extracting the curve section
                throw 2 ; // error condition
            }

            if (pidxrecs[i]->status & UEVENT_REVERSED)
            {   // Then reverse this curve section
                pc->Reverse() ; 
            }

    
            // See if we can append this to on of the existing sets
        
            crvsp = pc->StartPoint() ; 
            crvep = pc->EndPoint() ; 

            CS_DEBUG(fprintf(fpDebugOut,"us=%14.12f ue=%14.12f\n", 
                    pidxrecs[i].us, pidxrecs[i].ue) ;) ;  
            CS_DEBUG(crvsp.Print(fpDebugOut) ; fprintf(fpDebugOut," => ") ; ) ; 
            CS_DEBUG(crvep.Print(fpDebugOut) ; fprintf(fpDebugOut,"\n\n") ; ) ; 
        
            // We only test the last node here since if it can't connect 
            // to the last node then there is considerable overhead in 
            // connecting the curves up properly, which is done as a 
            // final step.
            if ((prescrv->nodecnt > 0) && (prescrv->EndPoint() != crvsp))
            {
                fprintf(fpDebugOut,"Build curve end doesn't match start point," 
                       " build end ==>\n") ; 
                prescrv->EndPoint().Print(fpDebugOut) ; fprintf(fpDebugOut, "\n\n") ;
            }

            prescrv->AddCurve(pc, CS_ADJUST_STARTPOINT) ; 
        }
    } 
    catch (int err)
    {
        sprintf(szGeomErrString, 
            "Error copying curve section in BoolConnectCurve(), %d\n",err) ;
        delete prescrv ; 
        return 0 ; 
    }

    if (prescrv->nodecnt == 0)
    {
        delete prescrv ; 
        prescrv = 0 ; 
    }

    return prescrv ; 
}


// Used by the Union function to find all curves that are inside the main
// union curve. Inside curves are labelled as holes.
static void UnionTagHoles(CS_CurveSet &crvset)
{
    // To perform this operation efficiently we need to find the one oustide
    // containment curve, if there is one. Start with the first curve and
    // test if it is inside the next. If not then test the reverse, as soon
    // a curve is found that contains another one, we are finished, since 
    // these can only be one container curve. All the rest will be holes

    CS_CurveVecItr poutside ; // last container curve pointer
    CS_CurveVecItr pnxt, pfirst ;   // next test node
    CS_Curve *ca, *cb ; // two test curves

    pfirst = poutside = crvset.crvlist.begin() ; 
    pnxt = pfirst + 1 ; 
    while (pnxt != crvset.crvlist.end())
    {   
        ca = *pfirst ; 
        cb = *pnxt ; 

        if (ca->PointInside(cb->StartPoint()))
        {   // Then the last curve tested is inside the current
            // curve so this becomes the outside curve
            // This means ca is the container curve which is from 
            // poutside so we're done
            poutside = pfirst ; 
            break ; 
        }
        else if (cb->PointInside(ca->StartPoint()))
        {   // Then cb is the container curve which means we are done
            poutside = pnxt ; 
            break ; 
        }
        pnxt++ ;
    }

    if (poutside != pfirst)
    {
        // Then swap the curve pointers
        ca = *poutside ;
        *poutside= *pfirst;
        *pfirst = ca ;
    }

    // Now mark all curves except the first one as holes
    pnxt = pfirst + 1 ; 
    while (pnxt != crvset.crvlist.end())
    {
        (*pnxt)->statflags |= CS_HOLECURVE ; 
        pnxt++ ; 
    }
}


