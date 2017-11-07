// CompTable.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <libCMS/CMSBOMRTE.h>
#include "CompTable.h"

int stat(const char *path, struct stat *buf); 

RunParms::RunParms()
{
	
    plantMode = PLANT_EXCO ; 
    odbcName[0] = 0 ; 
    user[0] = 0 ; 
    pwd[0] = 0 ; 
    logfile[0] = 0 ; 
    taskdir[0] = 0 ; 
    taskarchive[0] = 0 ;
    bNoEcho = false ; 
    bVerification = false ; 
    bTrackAfterShipped = false ; 
    cfgfile[0] = 0 ; 
    sqllogname[0] = 0 ; 

    bVerifySolarsoft = false ; 
    bUseRoutingResource = 0 ; 

    soMaxCount = 0 ; 
    nLastMax = 0 ; 
    nLastPrefix = 0 ; 

    moveToDir[0] = 0 ; 

    memset(&isys, 0, sizeof(cwbCO_SysHandle)) ; 
    memset(&qhandle, 0, sizeof(cwbDQ_QueueHandle)) ; 
}
CMSConnectionParms gCMSparms ;
RunParms gParms ; 
CMSBOMRTE cmsdata ;

int _tmain(int argc, _TCHAR* argv[])
{

	printf("Program is running Compare Table between SolarSoft and Decade it will be closed when it's done...\r") ;

	strcpy(gParms.odbcName, "decade");
	strcpy(gParms.user, "jamie");
	strcpy(gParms.pwd, "jamie");

	strcpy(gParms.CMSIP, "10.0.0.35");
    strcpy(gParms.CMSDBName, "CMSDAT") ; 
    strcpy(gParms.CMSodbc, "cms1") ; 
    strcpy(gParms.CMSDBusr, "RROSSETTI") ; 
    strcpy(gParms.CMSDBpwd, "RROSSETTI") ; 
    strcpy(gParms.CMSQpwd, "RROSSETTI") ; 
    strcpy(gParms.CMSQusr, "RROSSETTI") ; 
    strcpy(gParms.CMSInQ, "SF223DQI") ; 
    strcpy(gParms.CMSOutQ, "SF223DQO") ; 
    strcpy(gParms.CMSPlant, "001") ; 


	gCMSparms.pevp = &gParms.evp ; 
	CCMSDatabase m_sql ;
	CCMSDatabase m_db ;
	try {
        m_sql.OpenEx(gParms.odbcName, gParms.user, gParms.pwd) ;
    }
    catch (...)
    {
        printf("Error connecting to Decade database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }
	try {
        m_db.OpenEx(gParms.CMSodbc, gParms.CMSDBusr, gParms.CMSDBpwd) ;
    }
    catch (...)
    {
        printf("Error connecting to SolarSoft database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }
	gCMSparms.status = 0 ; 
	
    strcpy(gCMSparms.ibmhost, gParms.CMSIP) ; 
    strcpy(gCMSparms.dbname,  gParms.CMSDBName) ; 
    strcpy(gCMSparms.odbc,    gParms.CMSodbc) ; 
    strcpy(gCMSparms.dbusr,   gParms.CMSDBusr) ; 
    strcpy(gCMSparms.dbpwd,   gParms.CMSDBpwd) ; 
    strcpy(gCMSparms.DQpwd,   gParms.CMSQpwd) ; 
    strcpy(gCMSparms.DQusr,   gParms.CMSQusr) ; 
    strcpy(gCMSparms.inputQ,  gParms.CMSInQ) ; 
    strcpy(gCMSparms.outputQ, gParms.CMSOutQ) ; 
    strcpy(gCMSparms.plantID, gParms.CMSPlant) ; 

    if (gCMSparms.ibmhost[0] == 0 || gCMSparms.odbc[0] == 0)
        gCMSparms.status = 0x80000000 ; 
        
    if (!gParms.evp.bBatchMode && !(gCMSparms.status & 0x80000000))
    {
        if (IBM_OpenDataQ(gParms.isys, gParms.qhandle, gCMSparms.inputQ))
        {
            char *pmsg =
                    "ERROR: error opening a data queue connection to the iSeries,\n"
                    "   check your config file parameter settings for the IBM iSeries\n"
                    "   data Q and try running the program again. The decade processing\n"
                    "   will still process normally even with this error.\n" ; 
        }
    }



    strcpy(gParms.evp.m_db.odbcName, gParms.CMSodbc) ; 
    strcpy(gParms.evp.m_db.userName, gParms.CMSDBusr) ; 
    strcpy(gParms.evp.m_db.password, gParms.CMSDBpwd) ; 
    strcpy(gParms.evp.m_db.dbname,   gParms.CMSDBName) ; 
    strcpy(gParms.evp.plantID,       gParms.CMSPlant) ; 

	strcpy(cmsdata.m_db.odbcName, gCMSparms.odbc) ; 
    strcpy(cmsdata.m_db.userName, gCMSparms.dbusr) ; 
    strcpy(cmsdata.m_db.password, gCMSparms.dbpwd) ; 


    if (!gParms.evp.OpenDatabase())
    {
        printf ("Error opening connection to CMS database, check IBM parameters and ODBC setup\n") ; 
        return -1 ; // error out. 
    }
	//ReProcessErrorArc();
	//BatchUpdChk();
	CadCompare();
    gParms.evp.LoadMaps(gParms.evp.plantID) ; 

	//select past 10 days information from decade
	csString sonumdec(64) ;
    csString empnumdec(64)   ; 
    csString prtcodedec(16)   ;
	csString subcodedec(16)	;
	csString stationdec(16)	;
    csString tasktimedec(64)  ;
	csString taskdec(16)	;
	csString prtcodealldec(64);
	csString plant(64);
	csString sonum(64) ;
    csString empnum(64)   ; 
    csString prtcode(16)   ;
	csString station(16)	;
    csString tasktime(64)  ;
	csString task(16)	;
    csString rtype(16)   ;
    csString arc(16) ; 
    csString N1(32) ; 
    csString N2(32) ; 
    csString R1(64) ; 
    csString R2(64) ; 
    csString S1(128) ; 
    csString S2(128) ; 
	int Count = -1;
	int CountCheck = -1;
	//TIME FUNCTION
			char datestr[64] ;
			char datestrnow[64];
			csString time;
			CDateTime dtime ; 
			dtime.SetNow() ; 
			dtime.FormatDateTimeSecs(datestrnow, 0) ;

			int DayTemp = dtime.m_nDay;
			int MonthTemp = dtime.m_nMonth;
			if(DayTemp-10>0)
			{
				DayTemp = DayTemp - 10;
				dtime.m_nDay = DayTemp;
			}
			else if(DayTemp -10 <=0 )
			{
				DayTemp = 28+(DayTemp -10);
				int tempMonth = MonthTemp -1;
				if(tempMonth -1 >0)
				{
					dtime.m_nDay = DayTemp;
					dtime.m_nMonth = tempMonth;
				}
				else if(tempMonth -1 == 0)
				{
					dtime.m_nDay = DayTemp;
					MonthTemp = 12;
				}
			}
	
			dtime.FormatDateTimeSecs(datestr, 0) ;
			datestr;
			
	char qrydecade[256];
	try
	{
		sprintf(qrydecade, "select ordernumber, employeenumber, task, part, subpart, station, tasktime from d_task WHERE tasktime > '%s' order by tasktime", 
					datestr) ; 

		CSQLRecordset rsu(m_sql) ;
        rsu << qrydecade ; 
        rsu.SQLExec();
		while (rsu.SQLFetch())
		{
			int fldnum = 1;
			sonumdec.len       = CS_strmaxcat(sonumdec.str    , rsu.SQLGetData(fldnum++).c_str(), 60) ; 
            empnumdec.len      = CS_strmaxcat(empnumdec.str   , rsu.SQLGetData(fldnum++).c_str(), 60) ;
			taskdec.len        =  CS_strmaxcat(taskdec.str     , rsu.SQLGetData(fldnum++).c_str(), 14) ;  
            prtcodedec.len     = CS_strmaxcat(prtcodedec.str  , rsu.SQLGetData(fldnum++).c_str(), 14) ;  
			subcodedec.len     = CS_strmaxcat(subcodedec.str  , rsu.SQLGetData(fldnum++).c_str(), 14) ;  
			stationdec.len     = CS_strmaxcat(stationdec.str  , rsu.SQLGetData(fldnum++).c_str(), 14) ;  
            tasktimedec.len    = CS_strmaxcat(tasktimedec.str , rsu.SQLGetData(fldnum++).c_str(), 60) ; 
         
			sonumdec.Trim() ;
            empnumdec.Trim() ;
            prtcodedec.Trim() ;
			subcodedec.Trim() ;
            taskdec.Trim() ;
            tasktimedec.Trim() ;
            stationdec.Trim() ;
			prtcodealldec = prtcodedec+subcodedec;
			prtcodealldec.Trim();
			//if(sonumdec!="234579")
				//continue;

			//if(taskdec != "IS")
				//continue;
			//Check if SONUM is in EXCOTASK first
			char qrysolarC[256];
			try
			{
				sprintf(qrysolarC, "select count (*) from %s.EXCOTASK where plant = '%s' and sonum = '%s'", 
					gCMSparms.dbname, gCMSparms.plantID, sonumdec) ; 
				CSQLRecordset rssc(m_db) ;
				rssc << qrysolarC ; 
				rssc.SQLExec();
				while(rssc.SQLFetch())
				{
					Count = atoi(rssc.SQLGetData(1).c_str()) ; 
				}
			}
			catch (CSQLException* e)
			{
				char msg[4096] ; 
				_snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
				msg[4000] = 0 ; 
				msg[4001] = 0 ; 
				LogError(msg) ; 
				e->Delete();
			}
			
			if(Count <=0)
				continue;


			//Check if the task is already in SolarSoft
			char qrySolarCheck[1024];
			try
			{
				sprintf(qrySolarCheck, "select count (*) from %s.EXCOTASK where plant = '%s' and sonum = '%s' and empnum = '%s' and prtcode = '%s'"
						"and task = '%s' and station = '%s' and tasktime = '%s'", 
						gCMSparms.dbname, gCMSparms.plantID, sonumdec.c_str(),empnumdec.c_str(),prtcodealldec.c_str(),taskdec.c_str(),stationdec.c_str(),tasktimedec.c_str()) ; 
				

				CSQLRecordset rssch(m_db) ;
				rssch << qrySolarCheck ; 
				rssch.SQLExec();
				while(rssch.SQLFetch())
				{
					CountCheck = atoi(rssch.SQLGetData(1).c_str()) ; 
				}
			}
			catch (CSQLException* e)
			{
				char msg[4096] ; 
				_snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
				msg[4000] = 0 ; 
				msg[4001] = 0 ; 
				LogError(msg) ; 
				e->Delete();

				//gParms.evp.m_db.Reconnect() ; 

			}
			if(CountCheck > 0)
				continue;


			//Insert record from Decade to SolarSoft
			char qrySolarI[256];
			char qrySolarI2[256];
			try
			{
				 sprintf(qrySolarI, "INSERT INTO %s.EXCOTASK(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,RTYPE,ARC)"
                            " VALUES('%s','%s','%s','%s','%s','%s','%s','EVT','N')", 
						    gCMSparms.dbname, gCMSparms.plantID, sonumdec.c_str(),empnumdec.c_str(),taskdec.c_str(), prtcodealldec.c_str(),stationdec.c_str(),tasktimedec.c_str()) ; 

				CSQLRecordset rssI(m_db) ;
				rssI << qrySolarI ; 
				rssI.SQLExec();
				
				try
				{
					sprintf(qrySolarI2, "INSERT INTO %s.EXCOTASKOTHERINFOR(PLANT,SONUM,EMPNUM,TASK,PRTCODE,STATION,TASKTIME,RTYPE,ARC,INSERTDEC)"
                            " VALUES('%s','%s','%s','%s','%s','%s','%s','EVT','N','%s')", 
						    gCMSparms.dbname, gCMSparms.plantID, sonumdec.c_str(),empnumdec.c_str(),taskdec.c_str(), prtcodealldec.c_str(),stationdec.c_str(),tasktimedec.c_str(),datestrnow) ; 

					CSQLRecordset rssI2(m_db) ;
					rssI2 << qrySolarI2 ; 
					rssI2.SQLExec();


				}
				catch (CSQLException* e)
				{
					char msg[4096] ; 
					_snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
							e->m_nRetCode, e->m_strError.c_str());
					msg[4000] = 0 ; 
					msg[4001] = 0 ; 
					LogError(msg) ; 
					e->Delete();

					//gParms.evp.m_db.Reconnect() ; 
				}

			}
			catch (CSQLException* e)
			{
				char msg[4096] ; 
				_snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
				msg[4000] = 0 ; 
				msg[4001] = 0 ; 
				LogError(msg) ; 
				e->Delete();

				//gParms.evp.m_db.Reconnect() ; 

			}

		}



	}
	catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                        e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();

        //gParms.evp.m_db.Reconnect() ; 

    }
	

	//BatchUpdChk();
	//ReProcessErrorArc();
	



	return 0;
}

void ReProcessErrorArc()
{
	printf("Program is running ReProcess Error Arc it will be closed when it's done...\r") ;
//	int ProgressCount;
	CCMSDatabase m_db1 ;
	try {
        m_db1.OpenEx(gParms.CMSodbc, gParms.CMSDBusr, gParms.CMSDBpwd) ;
    }
    catch (...)
    {
        printf("Error connecting to SolarSoft database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }
	csString sonum(64) ;
    csString empnum(64)   ; 
    csString prtcode(16)   ;
    csString task(16)   ;
    csString tasktime(64)  ;
    csString station(64) ;
    csString rtype(16)   ;
    csString arc(16) ; 
    csString N1(32) ; 
    csString N2(32) ; 
    csString R1(64) ; 
    csString R2(64) ; 
    csString S1(128) ; 
    csString S2(128) ; 
	char qry[512];
	_snprintf(qry, 0x3FF0,
        "SELECT CTIME FROM %s.EXCOTASK WHERE ARC='N' ORDER BY CTIME FETCH FIRST 1 ROWS ONLY", 
            gCMSparms.dbname, gCMSparms.plantID) ; 

    CDateTime firsttime ; 
    int foundFirstTime = 0 ;
    csString firstTimeStr ; 

    try {
        CSQLRecordset rs(m_db1) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            CDateTime dtnow ; 
            dtnow.SetNow() ; 

            firstTimeStr = rs.SQLGetData(1).c_str() ;

            SQL_ConvertTime(firstTimeStr.c_str(), firsttime) ;

            if (abs(dtnow.m_nYear - firsttime.m_nYear) <= 1)
                foundFirstTime = 1 ; 
        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d getting first 'N' type EXCOTASK record:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }


    if (!foundFirstTime)
    {
       // AfxMessageBox("ERROR Loading task data\r\n No 'N' record found.\r\n   ABORTING...", MB_OK) ; 
        exit(0) ; 
    }

	sprintf(qry,
        "SELECT SONUM,EMPNUM,PRTCODE,TASK,TASKTIME,STATION,RTYPE,ARC,N1,N2,R1,R2,S1,S2 FROM"
        " %s.EXCOTASK WHERE ARC IN('N','A','I','Y','S','T') AND PLANT='%s'"
        " AND CTIME >= '%s' ORDER BY TASKTIME", 
            gCMSparms.dbname, gCMSparms.plantID, firstTimeStr.c_str()) ; 

	
    int taskcount = 0 ; 
    int skippedcount = 0 ;
    int firstN = 0 ; 

    try
    {
        CSQLRecordset rs(m_db1) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            int fldnum = 1 ; 

            sonum.len       = CS_strmaxcat(sonum.str    , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            empnum.len      = CS_strmaxcat(empnum.str   , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            prtcode.len     = CS_strmaxcat(prtcode.str  , rs.SQLGetData(fldnum++).c_str(), 14) ;  
            task.len        = CS_strmaxcat(task.str     , rs.SQLGetData(fldnum++).c_str(), 14) ;  
            tasktime.len    = CS_strmaxcat(tasktime.str , rs.SQLGetData(fldnum++).c_str(), 60) ; 
            station.len     = CS_strmaxcat(station.str  , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            rtype.len       = CS_strmaxcat(rtype.str    , rs.SQLGetData(fldnum++).c_str(), 8) ;  
            arc.len         = CS_strmaxcat(arc.str      , rs.SQLGetData(fldnum++).c_str(), 8) ;  
            N1.len          = CS_strmaxcat(N1.str       , rs.SQLGetData(fldnum++).c_str(), 16) ;  
            N2.len          = CS_strmaxcat(N2.str       , rs.SQLGetData(fldnum++).c_str(), 16) ;  
            R1.len          = CS_strmaxcat(R1.str       , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            R2.len          = CS_strmaxcat(R2.str       , rs.SQLGetData(fldnum++).c_str(), 32) ;  
            S1.len          = CS_strmaxcat(S1.str       , rs.SQLGetData(fldnum++).c_str(), 120) ;  
            S2.len          = CS_strmaxcat(S2.str       , rs.SQLGetData(fldnum++).c_str(), 120) ;  

            sonum.Trim() ;
            empnum.Trim() ;
            prtcode.Trim() ;
            task.Trim() ;
            tasktime.Trim() ;
            station.Trim() ;
            rtype.Trim() ;
            arc.Trim() ; 
            N1.Trim() ;
            N2.Trim() ;
            R1.Trim() ;
            R2.Trim() ;
            S1.Trim() ;
            S2.Trim() ;

			//if(sonum!="235487")
			//	continue;


			//TIME FUNCTION
			char datestr[64] ;
			csString time;
			CDateTime dtime ; 
			dtime.SetNow() ; 
			int DayTemp = dtime.m_nDay;
			int MonthTemp = dtime.m_nMonth;
			if(DayTemp-10>0)
			{
				DayTemp = DayTemp - 10;
			}
			else if(DayTemp -10 <=0 )
			{
				DayTemp = 28+(DayTemp -10);
				int tempMonth = MonthTemp -1;
				if(tempMonth -1 >0)
				{
					dtime.m_nDay = DayTemp;
					dtime.m_nMonth = tempMonth;
				}
				else if(tempMonth -1 == 0)
				{
					dtime.m_nDay = DayTemp;
					MonthTemp = 12;
				}
			}
	
			dtime.FormatDateTimeSecs(datestr, 0) ;
			datestr;
			
			char qry2[256] ; 
			//,'3','4','5','7'
			sprintf(qry2,"UPDATE %s.EXCOTASK SET ARC = 'N' WHERE  ARC IN ('4')  AND PLANT = '%s' AND SONUM = '%s' AND PRTCODE = '%s' AND CTIME <'%s'",
				gCMSparms.dbname, gCMSparms.plantID, sonum.c_str(),prtcode.c_str(),datestr) ; 
			try
			{
			  CSQLRecordset rs2(m_db1) ;
			  rs2 << qry2 ; 
			  rs2.SQLExec();
			}
			catch (CSQLException* e)
			{
				char msg[4096] ; 
				_snprintf(msg, 4000, "CMSBOMRTE::Check SO Number = %d, msg = %s\r\n", 
								e->m_nRetCode, e->m_strError.c_str());
				msg[4000] = 0 ; 
				msg[4001] = 0 ; 
				LogError(msg) ; 
				e->Delete();

			}

            if (rtype == "PPT")
            {
                int xx =0 ; 
                xx++ ; 
            }

            int soNumber = atoi(sonum.c_str()) ; 
            if (!firstN)
            {
                if (arc == "N")
                    firstN = 1 ; 
                else
                    continue ; 
            }
			
            gCMSparms.pevp->evd.sonum = atoi(sonum.c_str()) ; 
            gCMSparms.pevp->evd.empnum = atoi(empnum.c_str()) ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.part, prtcode.c_str(), 8) ;   ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.task, task.c_str(), 8) ;   ; 
            CS_strmaxcpy(gCMSparms.pevp->evd.station, station.c_str(), 16) ;
            
            CDateTime dt ;  
            SQL_ConvertTime(tasktime.c_str(), dt) ; 
            time_t eventTime = dt.GetTimeT() ; 
            gCMSparms.pevp->evd.tasktime = eventTime ; 

            // Look up all the relevant routing information for this task record
            TaskMapItr itm ; 
            int maperr = 0 ; 

            EventData &evt = gCMSparms.pevp->evd ; 
            
             // Process normally 
                maperr = gCMSparms.pevp->MapDecadeData(itm, true) ; 


                if (maperr)
                {
                    char errcode = 'E' ; 
                    switch(maperr)
                    {
                        case -2 :
                            errcode = '1' ; 
                            break ;
                        case -22 :
                            errcode = '2' ; 
                            break ;
                        case -23 :
                            errcode = '3' ; 
                            break ;
                        case -25 :
                            errcode = '4' ; 
                            break ;
                        case -100 :
                            errcode = '5' ; 
                            break ;
                        case -122 :
                            errcode = '6' ; 
                            break ; 
						case -20 :
							errcode = '7';
							break;
                    }

                    char uqry[256] ; 
                    try
                    {
                        sprintf(uqry, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
                                    " PLANT='%s' AND SONUM='%s' AND EMPNUM='%s' AND PRTCODE='%s' AND"
                                    " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='%s'", 
                                    gCMSparms.dbname, errcode, 
                                    gCMSparms.plantID, 
                                    sonum.c_str(), empnum.c_str(), prtcode.c_str(), 
                                    task.c_str(), tasktime.c_str(), station.c_str(), 
                                    rtype.c_str()) ; 

                        CSQLRecordset rsu(m_db1) ;
                        rsu << uqry ; 
                        rsu.SQLExec();
                    }
                    catch (CSQLException* e)
                    {
                        if (gCMSparms.pevp->fpLOG)
                        {
                            fprintf(gCMSparms.pevp->fpLOG, 
                                            "SQL error %d loading job record details:\n"
                                            "   %s\n"
                                            "   QRY=>'%s'\n", 
                                        (int)e->m_nRetCode, e->m_strError.c_str(), uqry) ;
                            fflush(gCMSparms.pevp->fpLOG) ; 
                        }
                        //throw 1 ; 
                    }
				}
			 }
		}
		catch (CSQLException* e)
        {
            if (gCMSparms.pevp->fpLOG)
            {
                fprintf(gCMSparms.pevp->fpLOG, 
                                "SQL error %d loading job record details:\n"
                                "   %s\n"
                                "   QRY=>'%s'\n", 
                            (int)e->m_nRetCode, e->m_strError.c_str(), qry) ;
                fflush(gCMSparms.pevp->fpLOG) ; 
            }
        }

}

int SQL_ConvertTime(const char *str, CDateTime &dt)
{
    if (!str || !str[0])
    {
        memset(&dt, 0, sizeof(CDateTime)) ; 
        return -1 ; 
    }

    // SQL datetime string returned as follows: 
    //      2007-10-20 17:35:14.920
    //      YYYY-MM-DD HH:MM:SS.SSS
    //      012345678901234567890123
    //                1         2   

    dt.m_nSecs  = atoi(str+17) ;  /* seconds after the minute - [0,59] */
    dt.m_nMins  = atoi(str+14) ;  /* minutes after the hour - [0,59] */
    dt.m_nHours = atoi(str+11) ; /* hours since midnight - [0,23] */
    dt.m_nDay   = atoi(str+8) ;  /* day of the month - [1,31] */
    dt.m_nMonth = atoi(str+5) ;  /* months since January - [1,12] */
    dt.m_nYear  = atoi(str) ;

    return 0 ; 
}


int BatchUpdChk()
{
	printf("Program is running BatchUpdate Checkit will be closed when it's done...\r") ;
	CCMSDatabase m_db1 ;
	try {
        m_db1.OpenEx(gParms.CMSodbc, gParms.CMSDBusr, gParms.CMSDBpwd) ;
    }
    catch (...)
    {
        printf("Error connecting to SolarSoft database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }
	int ordnum;
	int empnum;
	csString part;
	csString task;
	csString station;
	csString timetemp;
	int foundBatchchk = -1;
	int foundrprrx3chk = -1;
	int BatchUpdCheck = -1;
	char datestr[64] ;
	char datestrnow[64];
	csString time;
	CDateTime dtime ; 
	dtime.SetNow() ; 
	dtime.FormatDateTimeSecs(datestrnow, 0) ;

	int DayTemp = dtime.m_nDay;
	int MonthTemp = dtime.m_nMonth;
	if(DayTemp- 2>0)
	{
		DayTemp = DayTemp - 10;
		dtime.m_nDay = DayTemp;
	}
	else if(DayTemp - 2 <=0 )
	{
		DayTemp = 28+(DayTemp -10);
		int tempMonth = MonthTemp -1;
		if(tempMonth -1 >0)
		{
			dtime.m_nDay = DayTemp;
			dtime.m_nMonth = tempMonth;
		}
		else if(tempMonth -1 == 0)
		{
			dtime.m_nDay = DayTemp;
			MonthTemp = 12;
		}
	}
	
	dtime.FormatDateTimeSecs(datestr, 0) ;
	datestr;
	//Delete record is 2 days old

	char qryD[512];
	sprintf(qryD,"DELETE FROM %s.BATCHUPD "
			"WHERE ITIME < '%s'", gCMSparms.dbname, datestr);


	try {
			CSQLRecordset rs(m_db1) ;
			rs << qryD ; 
			rs.SQLExec();
		}
		catch (CSQLException* e)
		{
			if (gCMSparms.pevp->fpLOG)
			{
				fprintf(gCMSparms.pevp->fpLOG, 
					"SQL error %d updating task ARC flag for:\r\n"
					"      QRY='%s'\r\n"
					"      Error: '%s'\r\n",
				(int)e->m_nRetCode, qryD,  e->m_strError.c_str()) ;
		     	fflush(gCMSparms.pevp->fpLOG) ; 
				}
		}

	char qryB[512];
	//WHERE ITIME > '%s'
	sprintf(qryB,"SELECT * FROM %s.BATCHUPD ", gCMSparms.dbname);
	try
	{
		CSQLRecordset rs(m_db1) ;
        rs << qryB ; 
        rs.SQLExec();
		while (rs.SQLFetch())
        {
			ordnum =  atoi(rs.SQLGetData(2).c_str()) ; 
			empnum = atoi(rs.SQLGetData(3).c_str()) ;
			part = rs.SQLGetData(4).c_str();
			task = rs.SQLGetData(5).c_str();
			station = rs.SQLGetData(7).c_str();
			timetemp = rs.SQLGetData(6).c_str();

			part.Trim();
			task.Trim();
			station.Trim();
			timetemp.Trim();


			csString OARDATS(64); 
			csString OAPARTS(64);
			csString OAJOBS(64);
			csString OASEQS(64);
			csString OADEPTS(64);
			csString OARESCS(64);
			csString OAPOSTS(64);
			char qryBatchChk[256];
	
			sprintf(qryBatchChk,"SELECT COUNT(*) FROM %s.BATCHUPD WHERE PLANT = '%s' AND SONUM = '%d'"
				"AND EMPNUM = '%d' AND PRTCODE = '%s' AND TASK = '%s' AND STATION = '%s' AND TASKTIMEET >= '%s'",
				gCMSparms.dbname,gCMSparms.plantID,ordnum,empnum,part.c_str(),task.c_str(),station.c_str(),timetemp.c_str());
		
			try {
					CSQLRecordset rs(m_db1) ;
					rs << qryBatchChk ; 
					rs.SQLExec();
					 while (rs.SQLFetch())
					{
						foundBatchchk = atoi(rs.SQLGetData(1).c_str()) ; 
					}
			
				}
				catch (CSQLException* e)
				{
					if (gCMSparms.pevp->fpLOG)
					{
						fprintf(gCMSparms.pevp->fpLOG, 
							"SQL error %d updating task ARC flag for:\r\n"
							"      QRY='%s'\r\n"
							"      Error: '%s'\r\n",
						(int)e->m_nRetCode, qryBatchChk,  e->m_strError.c_str()) ;
		     			fflush(gCMSparms.pevp->fpLOG) ; 
					 }
				 }
				//Sleep(10);
				if(foundBatchchk<=0)
					continue;

				if(foundBatchchk >0)
				{
					char qryRprrx3Input[256];
					sprintf(qryRprrx3Input,"SELECT OARDATS, OAPARTS, OAJOB#S, OASEQ#S,OADEPTS, OARESCS FROM %s.BATCHUPD"
						" WHERE PLANT = '%s' AND SONUM = '%d' AND EMPNUM = '%d' AND PRTCODE = '%s' AND TASK = '%s' AND STATION = '%s' AND TASKTIMEET >= '%s'" 
						,gCMSparms.dbname,gCMSparms.plantID,ordnum,empnum,part.c_str(),task.c_str(),station.c_str(),timetemp.c_str());
					try {
							CSQLRecordset rs(m_db1) ;
							rs << qryRprrx3Input ; 
							rs.SQLExec();
							 while (rs.SQLFetch())
							{
								int fldnum = 1;

								OARDATS.len = CS_strmaxcat(OARDATS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ; 
								OAPARTS.len = CS_strmaxcat(OAPARTS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
								OAJOBS.len = CS_strmaxcat(OAJOBS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
								OASEQS.len = CS_strmaxcat(OASEQS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
								OADEPTS.len = CS_strmaxcat(OADEPTS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;
								OARESCS.len = CS_strmaxcat(OARESCS.str    , rs.SQLGetData(fldnum++).c_str(), 60) ;

								OARDATS.Trim(); 
								OAPARTS.Trim();
								OAJOBS.Trim();
								OASEQS.Trim();
								OADEPTS.Trim();
								OARESCS.Trim();
							}
			
						}
						catch (CSQLException* e)
						{
							if (gCMSparms.pevp->fpLOG)
							{
								fprintf(gCMSparms.pevp->fpLOG, 
									"SQL error %d updating task ARC flag for:\r\n"
									"      QRY='%s'\r\n"
									"      Error: '%s'\r\n",
								(int)e->m_nRetCode, qryRprrx3Input,  e->m_strError.c_str()) ;
		     					fflush(gCMSparms.pevp->fpLOG) ; 
							 }
						 }
						//Sleep(10);
						char rprrxChk[256];
						sprintf(rprrxChk,"SELECT COUNT (*) FROM %s.RPRRX3 "
							"WHERE OARDAT = '%s' AND OAPART = '%s' AND  OAJOB# = '%s' AND OASEQ# = '%s' AND OADEPT = '%s' AND OARESC = '%s'" 
							,gCMSparms.dbname,OARDATS.c_str(),OAPARTS.c_str(),OAJOBS.c_str(),OASEQS.c_str(),OADEPTS.c_str(),OARESCS.c_str());

						try {
								CSQLRecordset rs(m_db1) ;
								rs << rprrxChk ; 
								rs.SQLExec();
								 while (rs.SQLFetch())
								{
									foundrprrx3chk = atoi(rs.SQLGetData(1).c_str()) ; 
								}
			
							}
							catch (CSQLException* e)
							{
								if (gCMSparms.pevp->fpLOG)
								{
									fprintf(gCMSparms.pevp->fpLOG, 
										"SQL error %d updating task ARC flag for:\r\n"
										"      QRY='%s'\r\n"
										"      Error: '%s'\r\n",
									(int)e->m_nRetCode, rprrxChk,  e->m_strError.c_str()) ;
		     						fflush(gCMSparms.pevp->fpLOG) ; 
								 }
							}
						///	Sleep(10);
							//if(foundrprrx3chk<=0)
								//return BatchUpdCheck;
							if(foundrprrx3chk>0)
							{
								char rprrx3result[256];
								sprintf(rprrx3result,"SELECT OAPOST FROM %s.RPRRX3 "
								"WHERE OARDAT = '%s' AND OAPART = '%s' AND  OAJOB# = '%s' AND OASEQ# = '%s' AND OADEPT = '%s' AND OARESC = '%s'" 
								,gCMSparms.dbname,OARDATS.c_str(),OAPARTS.c_str(),OAJOBS.c_str(),OASEQS.c_str(),OADEPTS.c_str(),OARESCS.c_str());

								try {
										CSQLRecordset rs(m_db1) ;
										rs << rprrx3result ; 
										rs.SQLExec();
										 while (rs.SQLFetch())
										{
											OAPOSTS.len = CS_strmaxcat(OAPOSTS.str    , rs.SQLGetData(1).c_str(), 60) ; 
											OAPOSTS.Trim();
											break;
										}
			
									}
									catch (CSQLException* e)
									{
										if (gCMSparms.pevp->fpLOG)
										{
											fprintf(gCMSparms.pevp->fpLOG, 
												"SQL error %d updating task ARC flag for:\r\n"
												"      QRY='%s'\r\n"
												"      Error: '%s'\r\n",
											(int)e->m_nRetCode, rprrx3result,  e->m_strError.c_str()) ;
		     								fflush(gCMSparms.pevp->fpLOG) ; 
										 }
									}
								//	Sleep(10);
							}
					}
					if(OAPOSTS == "Y")
					{
						BatchUpdCheck = 1;
						char qrybatchresult[512];
						sprintf(qrybatchresult,"DELETE FROM %s.BATCHUPD "
							"WHERE OARDATS = '%s' AND OAPARTS = '%s' AND  OAJOB#S = '%s' AND OASEQ#S = '%s' AND OADEPTS = '%s' AND OARESCS = '%s' AND "
							"PLANT = '%s' AND SONUM = '%d' AND EMPNUM = '%d' AND PRTCODE = '%s' AND TASK = '%s' AND STATION = '%s' AND TASKTIMEET >= '%s'",
							gCMSparms.dbname, OARDATS.c_str(),OAPARTS.c_str(),OAJOBS.c_str(),OASEQS.c_str(),OADEPTS.c_str(),OARESCS.c_str(),gCMSparms.plantID,ordnum,empnum,part.c_str(),task.c_str(),station.c_str(),timetemp.c_str());
				
							try {
								CSQLRecordset rs(m_db1) ;
								rs << qrybatchresult ; 
								rs.SQLExec();
							}
							catch (CSQLException* e)
							{
								if (gCMSparms.pevp->fpLOG)
								{
									fprintf(gCMSparms.pevp->fpLOG, 
										"SQL error %d updating task ARC flag for:\r\n"
										"      QRY='%s'\r\n"
										"      Error: '%s'\r\n",
									(int)e->m_nRetCode, qrybatchresult,  e->m_strError.c_str()) ;
		     						fflush(gCMSparms.pevp->fpLOG) ; 
									}
							}
					}
					else if(foundrprrx3chk<=0 || OAPOSTS != "Y")
					{
						char qryexcotask[512];
						sprintf(qryexcotask,"UPDATE %s.EXCOTASK SET ARC = 'N' WHERE PLANT = '%s' AND SONUM = '%d' AND EMPNUM = '%d' AND PRTCODE = '%s' AND TASK = '%s' AND STATION = '%s' AND TASKTIME >= '%s'",
							gCMSparms.dbname,gCMSparms.plantID,ordnum,empnum,part.c_str(),task.c_str(),station.c_str(),timetemp.c_str());
						try {
								CSQLRecordset rs(m_db1) ;
								rs << qryexcotask ; 
								rs.SQLExec();
							}
							catch (CSQLException* e)
							{
								if (gCMSparms.pevp->fpLOG)
								{
									fprintf(gCMSparms.pevp->fpLOG, 
										"SQL error %d updating task ARC flag for:\r\n"
										"      QRY='%s'\r\n"
										"      Error: '%s'\r\n",
									(int)e->m_nRetCode, qryexcotask,  e->m_strError.c_str()) ;
		     						fflush(gCMSparms.pevp->fpLOG) ; 
									}
							}


					}

			}
	}
	catch (CSQLException* e)
	{
		if (gCMSparms.pevp->fpLOG)
		{
			fprintf(gCMSparms.pevp->fpLOG, 
				"SQL error %d updating task ARC flag for:\r\n"
				"      QRY='%s'\r\n"
				"      Error: '%s'\r\n",
			(int)e->m_nRetCode, qryB,  e->m_strError.c_str()) ;
			fflush(gCMSparms.pevp->fpLOG) ; 
		}
	}
	return BatchUpdCheck;
}

int CadCompare()
{
	printf("Program is running CompareCadTable it will be closed when it's done...\r") ;
	CCMSDatabase m_db1 ;
	try {
        m_db1.OpenEx(gParms.CMSodbc, gParms.CMSDBusr, gParms.CMSDBpwd) ;
    }
    catch (...)
    {
        printf("Error connecting to SolarSoft database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }
	char qry[512];
		
    CDateTime firsttime ; 
    int foundFirstTime = 0 ;
    
	char datestrStart[64] ;
	char datestrStop[64];
	csString time;
	CDateTime dtime ; 
	dtime.SetNow() ; 
	dtime.FormatDateTimeSecs(datestrStop, 0) ;
	int HourTemp = dtime.m_nHours;
	int HourTemp2 = dtime.m_nHours;
	int DayTemp = dtime.m_nDay;
	int MonthTemp = dtime.m_nMonth;
	//check past two hours for the past
	
	if(DayTemp - 10>0)
	{
		DayTemp = DayTemp - 10;
		dtime.m_nDay = DayTemp;
	}
	else if(DayTemp - 10 <=0)
	{
		DayTemp = 28 + (DayTemp - 10);
		int tempMonth = MonthTemp - 1;
		if(tempMonth -1 >0)
		{
			dtime.m_nDay = DayTemp;
			dtime.m_nMonth = tempMonth;
		}
		else if(tempMonth - 1 == 0)
		{
			dtime.m_nDay = DayTemp;
			MonthTemp = 12;
		}
	}

	dtime.FormatDateTimeSecs(datestrStart, 0) ;

	
	_snprintf(qry, 0x3FF0,
        "select * from %s.cupdate as a where not exists (select * from %s.cadupdate as b where a.sonum = b.sonum) and tasktime >= '%s' and tasktime <= '%s'",
		gParms.CMSDBName, gParms.CMSDBName, datestrStart, datestrStop) ; 
	
	csString movedir("T:\\ACCT\\FFdone") ; 
    CDateTime dt ; 
    dt.SetNow() ; 
    char subdir[1024] ; 
    sprintf(subdir, "%s\\%04d%02d", movedir.c_str(), 
                        dt.m_nYear, dt.m_nMonth) ; 
	if(CheckDirectory(subdir)<=0)
		return 0;
    try {
        CSQLRecordset rs(m_db1) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
          sonum  = atoi(rs.SQLGetData(1).c_str()) ;
		  csString folderPath = csString(subdir);

		  char filename[128];
		  csString fullpath;
		  //Get file name from the directory, using sales number to match the one from table.
		  if(GetFileName(folderPath.c_str())>0)
			csString testtemp = cs_fileName;
		  else
		  {
			//AfxMessageBox("Warning: Could not find sales order on file, please check information against your CAD drawing!",MB_OK) ; 
			 continue;
		  }
		  fullpath = folderPath + "\\"+ cs_fileName;
		  sprintf(filename, "%s", fullpath);
		  if(get_file_size(filename))
		  {
			  int testmof = 0;
			  //BuildMoveToName(cs_archiveFullPath.c_str(), 1);
			  cs_archiveFullPath = "T:\\ACCT\\FF\\"+cs_fileName;
			  if (!MoveFileEx(fullpath.c_str(), cs_archiveFullPath.c_str(), MOVEFILE_COPY_ALLOWED))
			  {
			    	//	AfxMessageBox("Cannot move file to achive folder.",MB_OK) ;
			  }
			  Sleep(500);
		  }

        }
    }
    catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d getting first 'N' type EXCOTASK record:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }

	return 0;
}
int get_file_size(const char *file_name) 
{
        struct stat buf;
        if ( stat(file_name, &buf) != 0 ) 
			return(0);
        return( buf.st_size );
} 

int CheckDirectory(char *subdir)
{
	int ret = 0 ;
    DWORD dwAttr = GetFileAttributes(subdir);
    int dirExists = false ; 
    if(dwAttr != INVALID_FILE_ATTRIBUTES && 
       dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {   // this is a directory
        dirExists = true ; 
		ret = 1;
    }

    if (!dirExists && !CreateDirectory(subdir, 0))
    {
//        AfxMessageBox("Cannot create MMYY directory.",MB_OK) ;
        ret = -1 ;
    }
    return ret ; 
}

int GetFileName(char *dirname)
{
    
    csString listDir(dirname) ; 
    listDir += "\\*" ; 

    int filecount = 0 ; 
    WIN32_FIND_DATA findData ; 
    HANDLE hFind = FindFirstFile(listDir.c_str(), &findData) ; 
	
	int m_nMappedSONUM = sonum;
	
    
	if (hFind == INVALID_HANDLE_VALUE)
    {   // OUTOFMEMORY
        DWORD errnum = GetLastError() ; 
        if (errnum != ERROR_FILE_NOT_FOUND)
        {
//           AfxMessageBox("Invalid File Handle.",MB_OK) ; 
			return 0; 
        }
    } 
    else 
    {
        FileRef fref ; 
        do {
            if (!CS_IsDots(findData.cFileName) && 
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                && !strstr(findData.cFileName, FFTEMPNAME))
            {
                strcpy(fref.filename, findData.cFileName) ;
                time(&(fref.fltime)) ; 
                char *pls = strrchr(fref.filename, '\\') ; 
                if (pls)
                    pls++ ; 
                else
                    pls = fref.filename ; 
                fref.ordernumber = atoi(pls) ;
				if (fref.ordernumber < 100000)
					fref.ordernumber += 200000 ; 
			    if(m_nMappedSONUM==fref.ordernumber)
				{
					cs_fileName  = findData.cFileName;
					return 1;
					break;
				}
			}
        } while (FindNextFile(hFind, &findData)) ;

        FindClose(hFind);
    }
	return 0;
}

//Move to Achive Directory
csString BuildMoveToName(char *prefix, int mode)
{
    csString movename(prefix) ;

    char datestr[64] ; 
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 1) ;
    if (mode == 0)
        movename += datestr + csString(".txt") ; 
    else if (mode == 2)
        movename = "IGNORED_" + movename  ;

    csString movedir("T:\\ACCT\\FF") ; 
    /*CDateTime dt ; 
    dt.SetNow() ; */
    char subdir[1024] ; 
    sprintf(subdir, "%s", movedir.c_str()) ; 
	
    // INVALID_FILE_ATTRIBUTES

    CheckDirectory(subdir) ; 
	csString archiveFullPath (subdir);
	cs_archiveFullPath = archiveFullPath+"\\"+movename;
    return AddFile2Path(subdir, movename) ; 

}