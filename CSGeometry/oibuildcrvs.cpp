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
// ofsevents.cpp
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


int OffsetIndexing::BuildCurves(CS_Curve *pcrv, CS_CurveSet &curveset)
{

    // fprintf(fpDebugOut, "\nCurveSections\n") ; 
    if (irecLen == 0)
    {   // Then we are basically done at this point
        if (!(overallEventStat & UEVENT_INVERTARC))
        {   // Then the curve had no inverse arc in it, and thus 
            // only contained touch off type events. This means that
            // we simply output the entire curve as is
            // 
            CS_Curve *pc = new CS_Curve ; 
            pc->CopyCurve(*pcrv) ; 
            curveset.AddCurve(pc) ; 
        }
        // else if oi.bInvertArc is true, then there were no intersections
        // but the curve did contain an inverted arc so we want to discard 
        // the entire curve
        return 0 ; // success
    }

    int ret = 0 ; 
    if (pcrv->statflags & CS_CLOSEDCURVE)
    {
        ret = BuildCurvesClosed(pcrv, curveset) ; 
    }
    else
    {
        ret = BuildCurvesOpen(pcrv, curveset) ; 
    }

    return ret ; 
}



int OffsetIndexing::BuildCurvesClosed(CS_Curve *pcrv, CS_CurveSet &curveset)
{
    int i ; 
    CS_List<CS_CurveChain *> activelist ; // curves that are being built
    CS_List<CS_CurveChain *> finallist ;  // final curves
    CS_POINT crvsp, crvep ;
    CS_ListNode *plistn; 
    CS_CurveChain *pcrvchn ; 
    bool bCurveAdded ;

    try 
    { 
        for (i=0;  i < irecLen; i++)
        {
            if ((pidxrecs[i].idxCount == minidxCount) && 
                !(pidxrecs[i].status & REC_CONTAINSINVERTARC))
            {   // Then this is a keeper. First extract it out and 
                // create a CS_Curve based on the us,ue parameters
                // Then see if it can be connected to the back of any 
                // other curves and add it to the active list or create
                // a new active list entry
                // Note we put the this pointer in so that it will be
                // easier to change the logic later when we create an new
                // offset curve and don't modify the original 

                CS_Curve *pc = pcrv->CopySection(pidxrecs[i].pss, 
                                                 pidxrecs[i].pse, 
                                                 pidxrecs[i].uss, 
                                                 pidxrecs[i].use, 
                                                 SEGMENTBASED_UVALUES) ;  
                if (!pc)
                {   // Error extracting the curve section
                    throw 2 ; // error condition
                }
        
                // See if we can append this to on of the existing sets
            
                crvsp = pc->StartPoint() ; 
                crvep = pc->EndPoint() ; 

                CS_DEBUG(fprintf(fpDebugOut, "us=%14.12f ue=%14.12f\n", 
                        pidxrecs[i].us, pidxrecs[i].ue) ;) ;  
                CS_DEBUG(crvsp.Print(fpDebugOut) ; fprintf(fpDebugOut, " => ") ; ) ; 
                CS_DEBUG(crvep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n\n") ; ) ; 
            
                bCurveAdded = false ; 

                // We only test the last node here since if it can't connect 
                // to the last node then there is considerable overhead in 
                // connecting the curves up properly, which is done as a 
                // final step.
                plistn = activelist.pLast ;
                if (plistn)
                {
                    pcrvchn = *(activelist.GetData(plistn)) ;
                    if (pcrvchn->ep == crvsp)
                    {   // then append this curve 
                        pcrvchn->pcrv->AddCurve(pc, CS_ADJUST_STARTPOINT) ; 
                        pcrvchn->ep = crvep ; 
                        bCurveAdded = true ; 
                        // Now check if we've closed this curve
                        if (pcrvchn->sp == pcrvchn->ep)
                        {   // Then we've closed the curve so transfer it to the 
                            // final curve list
                            finallist.Append(pcrvchn) ; 
                            // We're breaking out of the loop so it is okay to delete 
                            // this node from the list
                            activelist.Delete(plistn) ; 
                        }
                    }
                }

                if (!bCurveAdded)
                {   // Then add the curve to the active list
                    pcrvchn = new CS_CurveChain ; 
                    pcrvchn->pcrv = pc ; 
                    pcrvchn->sp = crvsp ; 
                    pcrvchn->ep = crvep ; 

                    if (crvsp == crvep)
                        finallist.Append(pcrvchn) ; 
                    else
                        activelist.Append(pcrvchn) ; 
                }
            }
            // else we don't want to use this part of the curve so ignore it
        }
    } 
    catch (int err)
    {
        // Error - delete the curve memory that won't get de-allocated
        sprintf(szGeomErrString, "Caught err %d in Index offsetting", err) ; 

        plistn = activelist.pFirst ; 
        while (plistn)
        {
            pcrvchn = *(activelist.GetData(plistn)) ; 
            delete pcrvchn ; 
            plistn = plistn->next ; 
        }
        
        plistn = finallist.pFirst ; 
        while (plistn)
        {
            pcrvchn = *(finallist.GetData(plistn)) ; 
            delete pcrvchn ; 
            plistn = plistn->next ; 
        }
        
        return err ; 
    }


    // Now we want to create an array with all the newly created
    // CS_Curve pointers

    CS_DEBUG(fprintf(fpDebugOut, "\nFinalist count=%d\nActivelist Count= %d\n",
                finallist.len, activelist.len) ; ) ; 

    i = 0 ; 

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // Release Code Logic here
    ////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    // fprintf(fpDebugOut, "\n *** FinalList *** \n") ; 

    plistn = finallist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(finallist.GetData(plistn)) ; 

        // TO DO This if is redundant now, remove once debugging is complete
        if (!(pcrvchn->status & REC_CONTAINSINVERTARC))
        {   // Save the curve to the output list
            curveset.AddCurve(pcrvchn->pcrv) ; 
            pcrvchn->pcrv = 0 ; // do not de-allocate this one
        }
        
        delete pcrvchn ; 
        // Don't have to set the pointer in the list to null since it is 
        // never used again
        
        plistn = plistn->next ; 
    }

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // End Release Code Logic here
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    /*
    */

    /*
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // Test code logic here
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////

    plistn = activelist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(activelist.GetData(plistn)) ; 
        curveset.AddCurve(pcrvchn->pcrv) ; 
        pcrvchn->pcrv = 0 ; // do not de-allocate this one
        plistn = plistn->next ; 
    }

    plistn = finallist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(finallist.GetData(plistn)) ; 
        curveset.AddCurve(pcrvchn->pcrv) ; 
        pcrvchn->pcrv = 0 ; // do not de-allocate this one
        plistn = plistn->next ; 
    }
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // END TEST CODE
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    */

    return 0 ; 
}


#define NEGINITVAL          -10
int OffsetIndexing::BuildCurvesOpen(CS_Curve *pcrv, CS_CurveSet &curveset)
{
    int i ; 
    CS_List<CS_CurveChain *> activelist ; // curves that are being built
    CS_List<CS_CurveChain *> finallist ;  // final curves
    CS_POINT crvsp, crvep ;
    CS_ListNode *plistn; 
    CS_CurveChain *pcrvchn ; 
    bool bCurveAdded ;

    try 
    { 
        // We have to treat the first and last index record sections as
        // special cases when dealing with open offset curves
        CS_Curve *pc ;
        int ifirst, ilast ; 

        // Note: ifirst and ilast have to refer to entries in the active 
        // list. If a curve is closed and transferred to the final list
        // then we no longer want those sections of the curve considered for 
        // the active list testing. In fact if an index section at the 
        // start or end gets transferred to the final list, then we no 
        // longer have to do final processing on that section (can
        // skip part B and/or C respectively). Note that there will only
        // be 1 active list curve, So we can test directly against this
        // curve whether or not we should be adding things. If the active
        // list is NULL then there is the possibility of adding the two
        // special case sections regardless. 

        ifirst = ilast = NEGINITVAL ; // must init to less than -2

        // See RR-Vol2 pg 142 for details, should also refer backwards several
        // pages to see how we arrived at this method.

        // Part A, Build the basic final and active curve lists
        for (i=0;  i < irecLen ; i++)
        {
            if ((pidxrecs[i].idxCount == minidxCount) && 
                !(pidxrecs[i].status & REC_CONTAINSINVERTARC))
            {   // Then this is a keeper. First extract it out and 
                // create a CS_Curve based on the us,ue parameters
                // Then see if it can be connected to the back of any 
                // other curves and add it to the active list or create
                // a new active list entry
                // Note we put the this pointer in so that it will be
                // easier to change the logic later when we create an new
                // offset curve and don't modify the original 

                if (ifirst == NEGINITVAL)
                    ifirst = i ; 
                ilast = i ; 

                CS_Curve *pc = pcrv->CopySection(pidxrecs[i].pss, 
                                               pidxrecs[i].pse, 
                                               pidxrecs[i].uss, 
                                               pidxrecs[i].use, 
                                               SEGMENTBASED_UVALUES) ;  
                if (!pc)
                {   // Error extracting the curve section
                    throw 2 ; // error condition
                }
        
                // See if we can append this to on of the existing sets
            
                crvsp = pc->StartPoint() ; 
                crvep = pc->EndPoint() ; 

                CS_DEBUG(fprintf(fpDebugOut, "us=%14.12f ue=%14.12f\n", 
                        pidxrecs[i].us, pidxrecs[i].ue) ;) ;  
                CS_DEBUG(crvsp.Print(fpDebugOut) ; fprintf(fpDebugOut, " => ") ; ) ; 
                CS_DEBUG(crvep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n\n") ; ) ; 
            
                bCurveAdded = false ; 

                // We only test the last node here since if it can't connect 
                // to the last node then there is considerable overhead in 
                // connecting the curves up properly, which is done as a 
                // final step.
                plistn = activelist.pLast ;
                if (plistn)
                {
                    pcrvchn = *(activelist.GetData(plistn)) ;
                    if (pcrvchn->ep == crvsp)
                    {   // then append this curve 
                        pcrvchn->pcrv->AddCurve(pc, CS_ADJUST_STARTPOINT) ; 
                        pcrvchn->ep = crvep ; 
                        bCurveAdded = true ; 
                        // Now check if we've closed this curve
                        if (pcrvchn->sp == pcrvchn->ep)
                        {   // Then we've closed the curve so transfer it to the 
                            // final curve list
                            finallist.Append(pcrvchn) ; 
                            // We're breaking out of the loop so it is okay to delete 
                            // this node from the list
                            activelist.Delete(plistn) ; 
                        }
                    }
                }

                if (!bCurveAdded)
                {   // Then add the curve to the active list
                    pcrvchn = new CS_CurveChain ; 
                    pcrvchn->pcrv = pc ; 
                    pcrvchn->sp = crvsp ; 
                    pcrvchn->ep = crvep ; 

                    if (crvsp == crvep)
                        finallist.Append(pcrvchn) ; 
                    else
                        activelist.Append(pcrvchn) ; 
                }
            }
            // else we don't want to use this part of the curve so ignore it
        }


        // Part B
        for (i=ifirst-1; i >= 0; i--)
        {
            if (pidxrecs[i].idxCount == minidxCount)
            {   // Then we might want to add this section
                CS_SegPtr psegn ; 
                double useg ;
                int x, y ;
                
                x = pidxrecs[i].idxae ;
                y = pidxrecs[i].itoEvent ;

                if (!pevlst->EquivalentEvents(x, y))
                {   // Then it doesn't end in an inverse arc section so we
                    // want to stuff the trailing end of this section to
                    // the front of the active list curve and then exit
                    psegn = pevlst->plist[x].pevent->psna ;
                    useg = pevlst->plist[x].pevent->u1 ;

                    pc = pcrv->CopySection(psegn, pidxrecs[i].pse,
                                           useg, pidxrecs[i].use,
                                           SEGMENTBASED_UVALUES) ;  
                    // Now stuff this into the start of the active curve
                    // list if possible
                    if (pc)
                    {
                        crvsp = pc->StartPoint() ; 
                        crvep = pc->EndPoint() ; 

                        CS_DEBUG(fprintf(fpDebugOut, "us=%14.12f ue=%14.12f\n", 
                                pidxrecs[i].us, pidxrecs[i].ue) ;) ;  
                        CS_DEBUG(crvsp.Print(fpDebugOut) ; fprintf(fpDebugOut, " => ") ; ) ; 
                        CS_DEBUG(crvep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n\n") ; ) ; 
        
                        // We only test the last node here since if it can't connect 
                        // to the last node then there is considerable overhead in 
                        // connecting the curves up properly, which is done as a 
                        // final step.
                        plistn = activelist.pFirst ;
                        if (plistn)
                        {
                            pcrvchn = *(activelist.GetData(plistn)) ;
                            if (pcrvchn->sp == crvep)
                            {   // then prepend this curve 
                                pc->AddCurve(pcrvchn->pcrv, CS_ADJUST_STARTPOINT) ; 
                                pcrvchn->pcrv = pc ; 
                                pc = 0 ; 
                                pcrvchn->sp = crvsp ; 
                                // Now check if we've closed this curve
                                if (pcrvchn->sp == pcrvchn->ep)
                                {   // Then we've closed the curve so transfer it to the 
                                    // final curve list
                                    finallist.Append(pcrvchn) ; 
                                    // We're breaking out of the loop so it is okay to delete 
                                    // this node from the list
                                    activelist.Delete(plistn) ; 
                                }
                                break ; 
                            }
                            else
                            {
                                delete pc ; 
                            }
                        }
                        else
                        {   // Then add the curve to the active list
                            pcrvchn = new CS_CurveChain ; 
                            pcrvchn->pcrv = pc ; 
                            pcrvchn->sp = crvsp ; 
                            pcrvchn->ep = crvep ; 

                            if (crvsp == crvep)
                                finallist.Append(pcrvchn) ; 
                            else
                                activelist.Append(pcrvchn) ; 

                            break ; 
                        }
                    }
                }
            }
        }



        // Part C
        for (i=ilast+1; (ilast >= 0) && (i < irecLen); i++)
        {
            if (pidxrecs[i].idxCount == minidxCount)
            {   // Then we might want to add this section
                CS_SegPtr psegn ; 
                double useg ;
                int x, y ;
                
                x = pidxrecs[i].idxas ;
                y = pidxrecs[i].ifromEvent ;

                if (!pevlst->EquivalentEvents(x, y))
                {   // Then it doesn't start in an inverse arc section so we
                    // want to add this to the end of the active curve if possible
                    // (if we add it then we also exit)
                    psegn = pevlst->plist[x].pevent->psna ;
                    useg = pevlst->plist[x].pevent->u1 ;

                    pc = pcrv->CopySection(pidxrecs[i].pss, psegn, 
                                           pidxrecs[i].uss, useg, 
                                           SEGMENTBASED_UVALUES) ;  
                    // Now stuff this into the start of the active curve
                    // list if possible
                    if (pc)
                    {
                        crvsp = pc->StartPoint() ; 
                        crvep = pc->EndPoint() ; 

                        CS_DEBUG(fprintf(fpDebugOut, "us=%14.12f ue=%14.12f\n", 
                                pidxrecs[i].us, pidxrecs[i].ue) ;) ;  
                        CS_DEBUG(crvsp.Print(fpDebugOut) ; fprintf(fpDebugOut, " => ") ; ) ; 
                        CS_DEBUG(crvep.Print(fpDebugOut) ; fprintf(fpDebugOut, "\n\n") ; ) ; 

                        // We only test the last node here since if it can't connect 
                        // to the last node then there is considerable overhead in 
                        // connecting the curves up properly, which is done as a 
                        // final step.
                        plistn = activelist.pFirst ;
                        if (plistn)
                        {
                            pcrvchn = *(activelist.GetData(plistn)) ;
                            if (pcrvchn->ep == crvsp)
                            {   // then prepend this curve 
                                pcrvchn->pcrv->AddCurve(pc, CS_ADJUST_STARTPOINT) ; 
                                pc = 0 ; 
                                pcrvchn->ep = crvep ; 
                                // Now check if we've closed this curve
                                if (pcrvchn->sp == pcrvchn->ep)
                                {   // Then we've closed the curve so transfer it to the 
                                    // final curve list
                                    finallist.Append(pcrvchn) ; 
                                    // We're breaking out of the loop so it is okay to delete 
                                    // this node from the list
                                    activelist.Delete(plistn) ; 
                                }
                                break ; 
                            }
                            else
                            {
                                delete pc ; 
                            }
                        }
                        else
                        {   // Only add the curve if the active list is empty
                            // Then add the curve to the active list
                            pcrvchn = new CS_CurveChain ; 
                            pcrvchn->pcrv = pc ; 
                            pcrvchn->sp = crvsp ; 
                            pcrvchn->ep = crvep ; 

                            if (crvsp == crvep)
                                finallist.Append(pcrvchn) ; 
                            else
                                activelist.Append(pcrvchn) ; 
                         
                            break ; 
                        }
                    }
                }
            }
        }
    } 
    catch (int err)
    {
        // Error - delete the curve memory that won't get de-allocated
        sprintf(szGeomErrString, "Caught err %d in Index offsetting", err) ; 

        plistn = activelist.pFirst ; 
        while (plistn)
        {
            pcrvchn = *(activelist.GetData(plistn)) ; 
            delete pcrvchn ; 
            plistn = plistn->next ; 
        }
        
        plistn = finallist.pFirst ; 
        while (plistn)
        {
            pcrvchn = *(finallist.GetData(plistn)) ; 
            delete pcrvchn ; 
            plistn = plistn->next ; 
        }
        
        return err ; 
    }


    // Now we want to create an array with all the newly created
    // CS_Curve pointers

    CS_DEBUG(fprintf(fpDebugOut, "\nFinalist count=%d\nActivelist Count= %d\n",
                finallist.len, activelist.len) ; ) ; 

    i = 0 ; 

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // Release Code Logic here
    ////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    // fprintf(fpDebugOut, "\n *** ActiveList *** \n") ; 

    // Since the input curve was open then we also have to include 
    // curves that are in the active list to the final output set
    plistn = activelist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(activelist.GetData(plistn)) ; 

        if (!(pcrvchn->status & REC_CONTAINSINVERTARC))
        {   // Save the curve to the output list
            curveset.AddCurve(pcrvchn->pcrv) ; 
            pcrvchn->pcrv = 0 ; // do not de-allocate this one
        }
    
        delete pcrvchn ; 

        // Don't have to set the pointer in the list to null since it is
        // never used again
        plistn = plistn->next ; 
    }
    

    // fprintf(fpDebugOut, "\n *** FinalList *** \n") ; 

    plistn = finallist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(finallist.GetData(plistn)) ; 

        if (!(pcrvchn->status & REC_CONTAINSINVERTARC))
        {   // Save the curve to the output list
            curveset.AddCurve(pcrvchn->pcrv) ; 
            pcrvchn->pcrv = 0 ; // do not de-allocate this one
        }
        
        delete pcrvchn ; 
        // Don't have to set the pointer in the list to null since it is 
        // never used again
        
        plistn = plistn->next ; 
    }

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // End Release Code Logic here
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    /*
    */

    /*
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // Test code logic here
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////

    plistn = activelist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(activelist.GetData(plistn)) ; 
        curveset.AddCurve(pcrvchn->pcrv) ; 
        pcrvchn->pcrv = 0 ; // do not de-allocate this one
        plistn = plistn->next ; 
    }

    plistn = finallist.pFirst ; 
    while (plistn)
    {
        pcrvchn = *(finallist.GetData(plistn)) ; 
        curveset.AddCurve(pcrvchn->pcrv) ; 
        pcrvchn->pcrv = 0 ; // do not de-allocate this one
        plistn = plistn->next ; 
    }
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    // END TEST CODE
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    */

    return 0 ; 
}