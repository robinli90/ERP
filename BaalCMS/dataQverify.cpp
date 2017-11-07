// dataQverify.cpp

#include "stdafx.h"
#include <conio.h>
#include <list>
#include <CSStdlibs/cslib.h>

#include <libCMS/CMSBOMRTE.h>
// #include "SQLDatabase.h"
// #include "SQLRecordset.h"

#include "BaalV2.h"

#ifdef _DEBUG
#define CHECK_DELAY     10 
#define EVENT_TIMEOUT   900
#else
#define CHECK_DELAY     10 
#define EVENT_TIMEOUT   600
#endif

#define SET_PROCESSING_COMPLETE     0x01

//! When checking the event times this is an allowance window in seconds
#define TIMECHECK_ALLOWANCE     100
#define MAX_EVENTS_IN_SET       7
//! If in queue for 1800 seconds then abort. 
#define MAXQUEUEWAIT            1800

int ProcessSetEvent(CMSEventSet &evtset) ;

void CMSEventSet::NextEvent() 
{
    // We need to space out the firing of sequential events in the
    // set so save the time that the previous event was sent so that 
    // we don't get two event right on top of one another. 
    if (eidx < nEVs - 1) 
    {   // There are more events in this set
        ev[eidx+1].timeLastSend = ev[eidx].timeLastSend - (CHECK_DELAY / 2) ; 
    }
    eidx++ ; // move to the next event in the set. 
    retry = 0 ; // reset the retry counter to start the next event
}

void DoDataQVerification()
{
    time_t tnow ; 
    time(&tnow) ;
    gCMSparms.lastCheckTime = tnow ; 

    // EDataMapItr ied = gCMSparms.pevp->evdmap.begin();
    CMSResourceMapItr irm = gCMSparms.pevp->evresmap.begin();
    while( irm != gCMSparms.pevp->evresmap.end() ) 
    {
        CMSEventSet *pevset = 0 ; 
        CMSEventSetListItr iel = irm->second.evlist.begin() ;
        CMSResourceMapItr inext = irm ;
        inext++ ; 
        if (ProcessSetEvent(*iel) == SET_PROCESSING_COMPLETE)
        {   // Delete it from the list, and also check to see if this is the last 
            // node in the eventlist in which case we delete the resource from 
            // the map as well so that the memory doesn't get consumed with dead
            // resources. We end up adding resources back all the time but it 
            // simplifies data management somewhat. 
            irm->second.evlist.pop_front() ; 
            if (irm->second.evlist.begin() == irm->second.evlist.end())
                gCMSparms.pevp->evresmap.erase(irm) ; 
        }
        irm = inext ; 
    }
}

void AbortEvent(int evtnum, EventData evt) 
{
    char msg[2048] ; 
    sprintf(msg, "ERROR max retries or timeout exceeded for jobnum#=%s seq#=%s, event=%d", 
                    evt.jobnum, evt.seqnum, evtnum) ; 
    Log2Error(msg, gParms.bNoEcho) ;
    evt.eventData[350] = 0 ; 
    LogError("********************************\r\nERROR: aborting send on ->\r\n") ; 
    LogError(evt.eventData) ; 
    LogError("********************************\r\n") ; 
}

int ProcessSetEvent(CMSEventSet &es)
{
    // Here we can loop through until we find an event that we are waiting on 
    // or we actually send a new event. At most we will loop twice. 
    int loopCount = 0 ;
    time_t tnow ; 

    while ((loopCount < MAX_EVENTS_IN_SET) && (es.eidx < es.nEVs))
    {
        int evtnum = atoi(es.ev[es.eidx].eventCode) ; 
        time(&tnow) ; 
        
        if (es.ev[es.eidx].sendcount >= EVMAX_RETRIES)
        {   // Then we should give up and delete the remainder of the set since we 
            // are simply not going to be able to reliably process this event
            AbortEvent(evtnum, es.ev[es.eidx]) ; 
            return SET_PROCESSING_COMPLETE ; // delete this event set. 
        }

        int deltaT = 0 ; 
        deltaT = (int)(tnow - es.ev[es.eidx].timeLastSend) ; 

        if (evtnum == 10000 || evtnum == 10001)
        {
            int runmode = 0 ; 
            runmode = gParms.evp.ActiveBatchShift(&es.ev[es.eidx]) ; 
            if (runmode == RUNMODE_ACTIVE)
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if (deltaT > CHECK_DELAY)
            {   // Attempt to send it 
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                if (evtnum == 10000)
                    es.ev[es.eidx].Set10000() ; // Set mode to RUN
                else 
                    es.ev[es.eidx].Set10001() ; // Set mode to SHIFT OUT AND CONTINUE RUN
                CMS_SendEventToQ(es.ev[es.eidx]) ; 
                es.ev[es.eidx].sendcount++ ; 
                es.ev[es.eidx].timeLastSend = tnow ; 

                char tmpstr[512] ; 
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount, 
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum, 
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ; 
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; // skip completely
            }
        }
        else if (evtnum == 10100)
        {
            // For this event we cannot ouput the 10151 unless the 10001 or the 10000 
            // has been output. Check to see if there is a ActiveBatchShift() and if not 
            // then check to see if we have a 1000x's queued up here waiting to go. 
            // If there is the wait for that to clear before attempting to process 
            // the 10151 event. 
            // 

            // There is no good way to test for this event, and it is not critical
            // so simply push it through the system without testing. TODO - enhance
            // this to verify the data, would have to work off of Q4ENT# and 
            // the date/time potentially. 
            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get10100Status(es.ev[es.eidx], evtTime) ;
            if ((stat & EVENT_10100) && (evtTime > (es.processTime - 1200000)))
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if (deltaT > CHECK_DELAY)
            {   // Attempt to send it 

                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ;
                es.ev[es.eidx].Set10100() ; // Set mode to DOWN
                CMS_SendEventToQ(es.ev[es.eidx]) ;
                es.ev[es.eidx].sendcount++ ; 
                es.ev[es.eidx].timeLastSend = tnow ; 

                char tmpstr[512] ; 
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount, 
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum, 
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ; 
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        else if (evtnum == 10151)
        {
            // For this event we cannot ouput the 10151 unless the 10001 or the 10000 
            // has been output. Check to see if there is a ActiveBatchShift() and if not 
            // then check to see if we have a 1000x's queued up here waiting to go. 
            // If there is the wait for that to clear before attempting to process 
            // the 10151 event. 
            // 
            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get10151Status(es.ev[es.eidx], evtTime) ;
            if ((stat & EVENT_10151) && (evtTime > (es.processTime - 1200000)))
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if (deltaT > CHECK_DELAY)
            {   // Attempt to send it 
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                es.ev[es.eidx].Set10151() ; // Set mode to RUN
                gParms.evp.TestAndSet10151Time(es.ev[es.eidx]) ;
                CMS_SendEventToQ(es.ev[es.eidx]) ; 
                es.ev[es.eidx].sendcount++ ; 
                es.ev[es.eidx].timeLastSend = tnow ; 

                char tmpstr[512] ;
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount, 
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum, 
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ; 
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        else if (evtnum == 20000)
        {
            // For this event we cannot ouput the 20000 unless the 10151
            // has been output. If we get to here it means that the 10151 
            // was read back and now exists within the database so now we
            // try and output the 20000 event 
            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get20000Status(es.ev[es.eidx], evtTime) ; 
            if ((stat & EVENT_20000) && (evtTime > (es.processTime - TIMECHECK_ALLOWANCE)))
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if ((deltaT > CHECK_DELAY) && (stat & EVENT_10151))
            {   // Attempt to send it 
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                es.ev[es.eidx].Set20000() ; 
                CMS_SendEventToQ(es.ev[es.eidx]) ; 
                es.ev[es.eidx].sendcount++ ; 
                es.ev[es.eidx].timeLastSend = tnow ; 

                char tmpstr[512] ; 
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount, 
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum, 
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ; 
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        else if (evtnum == 20009)
        {
            // For this event there is no output to the SFTX table so we can't do any
            // testing (for now, TODO find out where the 20009 is stored so that we 
            // can check for it). For now only output this event once. 
            // Attempt to send it 

            // Dec 15, 2009 - well it appears that 20009 is actually output to the SFTX, 
            // it is just that Solarsoft is rather particular about what it will accept
            // before recording this event to the SFTX table. 

            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get20009Status(es.ev[es.eidx], evtTime) ; 
            if ((stat & EVENT_20009) && (evtTime > (es.processTime - TIMECHECK_ALLOWANCE)))
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if (deltaT > CHECK_DELAY)
            {
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                es.ev[es.eidx].Set20009() ;
                CMS_SendEventToQ(es.ev[es.eidx]) ;
                es.ev[es.eidx].sendcount++ ;
                es.ev[es.eidx].timeLastSend = tnow ;

                char tmpstr[512] ;
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount,
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum,
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ;
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        else if (evtnum == 30000)
        {
            // For this event there is no output to the SFTX table so we can't do any
            // testing (for now, TODO find out where the 20009 is stored so that we 
            // can check for it). For now only output this event once. 
            // Attempt to send it 

            // Dec 15, 2009 - well it appears that 20009 is actually output to the SFTX, 
            // it is just that Solarsoft is rather particular about what it will accept
            // before recording this event to the SFTX table. 

            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get30000Status(es.ev[es.eidx], evtTime) ; 
            if (stat & EVENT_30000)  // can't use time in this case
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > MAXQUEUEWAIT)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if (deltaT > CHECK_DELAY)
            {
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                es.ev[es.eidx].Set30000() ;
                CMS_SendEventToQ(es.ev[es.eidx]) ;
                es.ev[es.eidx].sendcount++ ;
                es.ev[es.eidx].timeLastSend = tnow ;

                char tmpstr[512] ;
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount,
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum,
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ;
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        else if (evtnum == 40005)
        {
            // For this event we cannot ouput the 20000 unless the 10151
            // has been output. If we get to here it means that the 10151 
            // was read back and now exists within the database so now we
            // try and output the 20000 event 
            time_t evtTime = 0 ; 
            int stat = gParms.evp.Get40005Status(es.ev[es.eidx], evtTime) ; 
            // Allow 1,200,000 seconds (about 2 weeks) backwards in time on the 40005
            // since we only ever want to track one of these, and they can conceivably 
            // go back in time. 
            if ((stat & EVENT_40005) && (evtTime > (es.processTime - 1200000)))
            {   // Then it's done
                es.NextEvent() ; 
            }
            else if (deltaT > EVENT_TIMEOUT && es.ev[es.eidx].timeLastSend > 1000)
            {
                AbortEvent(evtnum, es.ev[es.eidx]) ; 
                return SET_PROCESSING_COMPLETE ; // delete this event set. 
            }
            else if ((deltaT > CHECK_DELAY) && (stat & EVENT_10151))
            {   // Attempt to send it 
                es.ev[es.eidx].SetBaseFields(gCMSparms.dbname, gParms.evp.idseed) ; 
                es.ev[es.eidx].Set40005() ; 
                CMS_SendEventToQ(es.ev[es.eidx]) ; 
                es.ev[es.eidx].sendcount++ ; 
                es.ev[es.eidx].timeLastSend = tnow ; 

                char tmpstr[512] ; 
                sprintf(tmpstr, " EVT=%d, sendcount=%d, JOB#=%s, SEQ#=%s, DEPT=%s RES=%s", 
                                evtnum, es.ev[es.eidx].sendcount, 
                                es.ev[es.eidx].jobnum, es.ev[es.eidx].seqnum, 
                                es.ev[es.eidx].deptCode, es.ev[es.eidx].resCode) ; 
                Log2Error(tmpstr, gParms.bNoEcho) ;
                break ; 
            }
            else
            {
                break ; 
            }
        }
        loopCount++ ; 
    }

    if (es.eidx >= es.nEVs)
        return SET_PROCESSING_COMPLETE ; 

    return 0 ; 
}
