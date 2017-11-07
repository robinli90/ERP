

// procff.cpp : Defines the entry point for the console application.
/*!
    This program is responsible for monitoring the iSeries flat file
    processing directory and a temporary holding directory somewhere on 
    a server that receives intermediate flat files from each workstation. 

    The intermediate files are then merged and transferred to the iSeries
    machine at the proper time in an attempt to minimize file collision
    and handling problems. We don't want to be updating the file while the 
    iSeries attempts to read it and so on. 
 */
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <Windows.h>
#include <libCMS/CMSBOMRTE.h>
#include "procff.h"
#include <conio.h>
#include <list>
#include <CSstdlibs/cslib.h>
#include <crtdefs.h>


// The global parameter set is contained here. 
ProcFFSetup procParms ; 
long int SO [1024];
int rerunstart = 0;
int sonumber = 0;
csString cs_fileName;
void PrintErrorMsg()
{
    printf(
        "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n"
        "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n"
        "   -----------------------------------------------------------------------\n"
        "     The flat file was not processed by the iSeries. Check to make sure\n"
        "     that the WORTUPLOAD process is scheduled and running and then restart\n"
        "     this process (re-run procff or the controlling batch file)\n\n"
        "     Also check the -e parameter move to directory for an FF.txt file\n"
        "     that may have caused an error. The WORTUPLOAD log file should have\n"
        "     a report with error information as well if this is the case.\n"
        "   -----------------------------------------------------------------------\n"
        "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n"
        "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n"
        ) ; 
}

int LogAndDeleteFile(FILE *fplog, csString &srcpath) ;

CMSConnectionParms gCMSparms ;
RunParms gParms ; 
CMSBOMRTE cmsdata ;
int SONumCount;

int main(int argc, char *argv[])
{
	gParms.evp.fpLOG = 0 ; 
    gCMSparms.pevp = &gParms.evp ; 

    if (ProcessArgs(argc, argv))
    {
        printusage() ; 
        exit(0) ; 
    }

	SetCurrentDirectory(gParms.taskdir) ;

    CCMSDatabase m_sql ;
	
    /*try {
        m_sql.OpenEx(gParms.odbcName, gParms.user, gParms.pwd) ;
    }
    catch (...)
    {
        printf("Error connecting to Decade database ODBC=%s\n", gParms.odbcName) ;
        exit(1) ; 
    }*/

    procParms.fplog = 0 ; 
    procParms.curLog[0] = 0 ; 
    if (procParms.logDirPrefix.size()) 
    {
        BuildDateName(procParms.curLog, procParms.logDirPrefix.c_str()) ; 
        procParms.fplog = fopen(procParms.curLog, "ab") ; 
    }

    FILE *fparchive = 0 ; 
    FILE *fpsql = 0 ; 
    FILE *fplog = 0 ;

    static char curArchive[512] ; 
    curArchive[0] = 0 ; 
    if (gParms.taskarchive[0])
    {
        BuildDateName(curArchive, gParms.taskarchive) ; 
        fparchive = fopen(curArchive, "ab") ; 
    }

    static char curLog[512] ; 
    curLog[0] = 0 ; 
    if (gParms.logfile[0]) 
    {
        BuildDateName(curLog, gParms.logfile) ; 
        fplog = fopen(curLog, "ab") ; 
        gParms.evp.fpLOG = fplog ; 
        CDateTime dt ; 
        dt.SetNow() ; 
        char dtstr[64] ; 
        dt.FormatDateTimeSecs(dtstr, 0) ; 
        LogError("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- \r\n") ; 
        LogError("OPENED LOG:") ; LogError(dtstr) ; LogError("\r\n") ; 
        LogError("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- \r\n") ; 
    }

    static char curSQLLog[512] ; 
    curSQLLog[0] = 0 ; 
    if (gParms.sqllogname[0]) 
    {
        BuildDateName(curSQLLog, gParms.sqllogname) ; 
        fpsql = fopen(curSQLLog, "ab") ; 
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

            if (fplog)
            {
                fprintf(fplog, pmsg) ; 
                fflush(fplog) ; 
            }
            else
            {
                printf(pmsg) ; 
            }
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

    gParms.evp.LoadMaps(gParms.evp.plantID) ; 

    printf("Processing....\n") ; 
    static char tmpname[512] ; 

    // *****************************************************************
    //  IBM DATA QUEUE HANDLING

    cwbCO_SysHandle isysread = 0 ; 
    cwbDQ_QueueHandle hqread = 0 ; 
    cwbSV_ErrHandle     hErr = 0 ; 
    cwbDQ_Data qData ; 
    unsigned char readBuf[4096] ; 
    int readBufLen = 4000 ; 

    if (!gParms.evp.bBatchMode)
    {
        IBM_OpenDataQ(isysread, hqread, gCMSparms.outputQ) ;

        // Create a data object
        if ( (qData = cwbDQ_CreateData()) == 0 )
        {   // Error occured
            IBM_CloseDataQ(isysread, hqread) ; 
            isysread = 0 ; 
            hqread = 0 ; 
        }

        // Set the data length and the data
        cwb_Boolean cvrt = 1 ; 
        unsigned int retval = 0 ; 
        if ((retval = cwbDQ_SetConvert(qData, cvrt)) != CWB_OK)
        {   // Error occured
            IBM_CloseDataQ(isysread, hqread) ; 
            isysread = 0 ; 
            hqread = 0 ; 
        }

        if ( cwbDQ_SetData(qData, readBuf, readBufLen) != CWB_OK )
        {   // Error occured
            IBM_CloseDataQ(isysread, hqread) ; 
            isysread = 0 ; 
            hqread = 0 ; 
        }
    }

    // *****************************************************************


    time(&gParms.evp.idseed) ; 
    gParms.evp.bUseCJOBDRRes = gParms.bUseRoutingResource ? true : false ; 
    if (gParms.bVerifySolarsoft)
        gCMSparms.InitVerification() ; 

    time_t lastEmpRead = 0 ; 



    printf("Processing....\n") ; 

    static char tmpname2[512] ; 

    FileRefMap frl ; // file list being processed. 
	FileRefMapItr ifr2 ; 
	FileRefMap frl3;
	FileRefMap frlFailed;
	FileRefMapItr ifrFailed;

    int IBMtestcount = 0 ; 
    int PROCESSwaitcount = 0 ; 
	int ProcFlag = 0;
    while (true)
    {
        if (kbhit()) 
        {
            if (_getch() == 0x03)
                break ; 
        }

        // ----------------------- Cycle the output files ----------------------
        if (procParms.logDirPrefix.size())
        {
            BuildDateName(tmpname2, procParms.logDirPrefix.c_str()) ; 
            if (strcmp(procParms.curLog,tmpname2) != 0)
            {
                fclose(procParms.fplog) ; 
                strcpy(procParms.curLog, tmpname2) ; 
                procParms.fplog = fopen(procParms.curLog, "ab") ; 
            }
        }
        // ----------------------- End cycle the output files ----------------------

		//if time is midnight, process the failed one 

        // Wait for the iSeries directory to be empty. 
        if (GetDirectoryList(procParms.IBMdir.c_str(), frl))
        {   // Then a file is still in the IBM directory waiting to 
            // be processed so don't do anything yet. 
            printf("Waiting for IBM to process flat file and delete it, waited %d seconds ...\r",
                ++IBMtestcount) ; 
            Sleep(1000) ; 
            PROCESSwaitcount = 0 ;
			//1800
            if (IBMtestcount > 1800)
            {   // Then the process has died potentially
                // Move the file to an error directory if defined, otherwise, dump
                // to log file and delete the file

				//Update CadUpdate Flag to Failed
				char filename[20] = "C:\\FF\\SO.txt" ;
				FILE *fp = fopen(filename, "r") ;
				Sleep(500);
				GetSO(fp);

				if(SO[0]>0)
				{
					//Check if Record exist
					for(int i = 0; i<1024; i++)
					{
						int test1 = SO[i];
						if(SO[i]>0)
						{
							CheckRecord(SO[i]);
							if(SONumCount>0)
							{
								//Update
								UpdateRecord(SO[i], 'F');
							}
							else if(SONumCount == 0)
							{
								//Insert
								InsertRecord(SO[i], 'F');
							}
							else
							{
								//error
							}
							//Find those SO# in FFdone. Move file into ReRun Folder for these SO one by one.
							//Create a function in procSupport to search file.
							
						}
					}
					if(procParms.ffDone[0] == '\0')
					{
						csString movedir(procParms.moveToDir) ; 
						CDateTime dt ; 
						dt.SetNow() ; 
						sprintf(procParms.ffDone, "%s\\%04d%02d", movedir.c_str(), dt.m_nYear, dt.m_nMonth) ; 
					}
					if (GetDirectoryList(procParms.ffDone, frlFailed))
					{
						ifrFailed = frlFailed.begin() ;
						Sleep(500);
						//csString moveTo
						char reRun[256];
						csString reRunFolder = "ReRun\\";
						sprintf(reRun,"%s",reRunFolder);
						for(int j = 0; j<1024; j++)
						{
							int test2 = SO[j];
							if(test2>0)
							{
								for(size_t i = 0; i<frlFailed.size(); i++)
								{
									if(test2 == ifrFailed->first.order&&ifrFailed->first.order>0)
									{
										//move file to ReRun Folder
										csString reRunPath = ifrFailed->second.filename;
										csString moveName1 = MoveFailedFile(reRun, reRunPath);
										csString srcpath1  = AddFile2Path(procParms.ffDone, ifrFailed->second.filename) ; 
										//    if (!CopyFile(tmpName.c_str(), mergeName.c_str(), MOVEFILE_COPY_ALLOWED))
										if (!CopyFile(srcpath1.c_str(),moveName1.c_str(),MOVEFILE_COPY_ALLOWED))
										{
											int erroroccur = 1;
											int failed = 1;
										}
										break;
									}
									ifrFailed++;
								}
							}
						}
					}

				}
				
				remove(filename);

                csString ffsrc = AddFile2Path(procParms.IBMdir, procParms.IBMfile) ; 
                LogToFile(procParms.fplog, "FLAT FILE ERROR\n") ; 
                LogToFile(procParms.fplog, "============== START OF ERR FILE =================\n") ; 

                FILE *ff = fopen(ffsrc.c_str(), "rt") ; 
                if (ff)
                {   
                    char buf[600] ; 
                    while (fgets(buf, 590, ff))
                        LogToFile(procParms.fplog,"%s", buf) ; 
                    fclose(ff) ; 
                }

                LogToFile(procParms.fplog, "================ END OF ERR FILE =================\n") ; 

                csString moveToFile, toBase, toExt ; 
                SplitFileAndExtension(procParms.IBMfile, toBase, toExt) ; 
                
                moveToFile = toBase + "_" ;

                CDateTime dt ;
                dt.SetNow() ; 
                char timestr[128] ; 
                moveToFile += dt.FormatDateTimeSecs(timestr, 1) ; 
                moveToFile += "." + toExt ;

				if(rerunstart == 1)
				{
					csString moveTo = AddFile2Path("ReRunFail", moveToFile) ; 
                              
					if (!MoveFileEx(ffsrc.c_str(), moveTo.c_str(), MOVEFILE_COPY_ALLOWED))
					{   // Then the move failed
						LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
								ffsrc.c_str(), moveToFile.c_str()) ;

						if (LogAndDeleteFile(procParms.fplog, ffsrc))
						{
							LogToFile(procParms.fplog,
								"ERROR - could not move or delete file from IBM directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
							printf(
								"ERROR - could not move or delete file from IBM directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
						}

					}
				}
				else
				{
					csString moveTo = AddFile2Path(procParms.errorDir, moveToFile) ; 
                              
					if (!MoveFileEx(ffsrc.c_str(), moveTo.c_str(), MOVEFILE_COPY_ALLOWED))
					{   // Then the move failed
						LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
								ffsrc.c_str(), moveToFile.c_str()) ;

						if (LogAndDeleteFile(procParms.fplog, ffsrc))
						{
							LogToFile(procParms.fplog,
								"ERROR - could not move or delete file from IBM directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
							printf(
								"ERROR - could not move or delete file from IBM directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
						}

					}
				}
                if (!procParms.continueOnError)
                {
                    PrintErrorMsg() ; 
                    break ; 
                }
            }
			if (GetDirectoryList(procParms.IBMdir.c_str(), frl)==0&&IBMtestcount<=1800)
			{
				char filename[20] = "C:\\FF\\SO.txt" ;
				FILE *fp = fopen(filename, "r") ;
				Sleep(500);
				GetSO(fp);

				if(SO[0]>0)
				{
					//Check if Record exist
					for(int i = 0; i<1024; i++)
					{
						int test1 = SO[i];
						if(SO[i]>0)
						{
							CheckRecord(SO[i]);
							if(SONumCount>0)
							{
								//Update
								UpdateRecord(SO[i], 'P');
							}
							else if(SONumCount == 0)
							{
								//Insert
								InsertRecord(SO[i], 'P');
							}
							else
							{
								//error
							}
						}
					}
				}
						
				remove(filename);


			}
            continue ; 
        }

		
        // The IBM directory is empty, so process the next set of files. 

        // grab the next file from the queue - if the queue is empty
	// refill it from the tasks directory
        IBMtestcount = 0 ; 
		//if(time is 11pm)
		csString time;
		CDateTime dtime ; 
		dtime.SetNow() ; 
		char datestr[64];
		dtime.FormatDateTimeSecs(datestr, 1) ;
		char wrkstr[64] ;
		strncpy(wrkstr, datestr, 62) ;
		wrkstr[63] = 0 ;
		char *timeNow = strtok(wrkstr, "_") ;
		timeNow = strtok(0,"_");
		int timeNow2 = atoi(timeNow);
		int timeStart = 000000;
		//if(timeStart >-1)
		if(timeNow2>timeStart&&timeNow2<050000)
		{
			rerunstart = 0;
			if(GetDirectoryList("ReRun"	,frl))
			{
				printf(" \nIBM dir empty, processing next reRun batch... \n");
				printf("Processing %d files...\n", frl.size());
				PROCESSwaitcount = 0;
				csString folderPath = "ReRun\\" ;
				//csString cs_fileName = "";
				//Check if SO number is processed
				if(GetSOName(folderPath.c_str())>0)
				{
					//Check if HOllowDie is processed
					if(CheckProcess (sonumber) > 1)
					{
						//delete file
						csString deletePath = "";
						deletePath = folderPath+cs_fileName;

						if (LogAndDeleteFile(procParms.fplog, deletePath))
						{
							LogToFile(procParms.fplog,
								"ERROR - could not move or delete file from ReRun directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
							printf(
								"ERROR - could not move or delete file from ReRun directory. This can cause\n"
								"   data corruption within Solarsoft. Manually correct the problem and then\n"
								"   restart this process.\n") ; 
						}
						continue;
					}
				}
				else
				{
					//AfxMessageBox("Warning: Could not find sales order on file, please check information against your CAD drawing!",MB_OK) ; 
					 continue;
				}
				ProcessFileSet2(frl);
			}
			else
			{
				printf("Waiting for ReRun files to process, waited %d seconds ...\r",
					++PROCESSwaitcount) ; 
				Sleep(1000) ; 
				continue ; 
			}
		}
		else
		{
			if (GetDirectoryList(procParms.watchDir.c_str(), frl))
			{
				rerunstart = 0;
				printf(" \nIBM dir empty, processing next batch...\n") ; 
				printf("Processing %d files...\n", frl.size()) ; 
				PROCESSwaitcount = 0 ;
				//Write SO number to a file
				ifr2 = frl.begin() ;
				char filename[20] = "C:\\FF\\SO.txt" ;
				FILE *fp = fopen(filename, "wb") ;
				Sleep(500);
				for(size_t i = 0; i<frl.size(); i++)
				{
					SO[i] = ifr2->first.order;
					char msg [64];
					sprintf(msg, "%d,",SO[i]) ; 
					SOToFile(fp,msg,filename);
					ifr2++;
				}
			


				ProcessFileSet(frl) ; 

			}
			else
			{
				rerunstart = 0;
				printf("Waiting for CAD files to process, waited %d seconds ...\r",
					++PROCESSwaitcount) ; 
				Sleep(1000) ; 
				continue ; 
			}
		}
        Sleep(2000) ; 
		

    }

    return 0 ; 
}

int ProcessFileSet2(FileRefMap &frl)
{

    csString tmpName = AddFile2Path("ReRun", FFTEMPNAME ) ; 
    FILE *fptmp = fopen(tmpName.c_str(), "wb") ; 

    Sleep(500) ; // allow a bit of time for file write completion

    procParms.Reset() ; 

    // If there are two files which reference the same order number then we only
    // process the first one in the list (which would have been the last one
    // that was created). The reason is that until this file is run through the 
    // flat file processor, only the last file produced would make sense. There
    // is no way to create these files until the previous file is processed so
    // ..... (think about it and it will make sense). Thus everything has to be
    // done in CADUpdate. You can't create another program which attempts to do
    // its own flatfile generation, unless you really watch and pay attention
    // to what is going on. 
    // 
    // The main reason for this is that Solarsoft complains if there are any 
    // duplicate records. 
    // 
    int lastOrderNumber = 0 ; 
    int bWroteSomething = 0 ; 
	csString tempName;
    FileRefMapItr ifr ; 

    ifr = frl.begin() ;
	 //while (ifr != frl.end())
    if (ifr != frl.end())
    {
        if (ifr->first.order == lastOrderNumber)
        {   // Delete this file from further consideration. 
            csString basename = GetFileName(ifr->second.filename) ;
            csString moveName = BuildMoveToName2(basename.c_str(), 2) ;
            csString srcpath = AddFile2Path("ReRun\\", ifr->second.filename) ; 
            if (!MoveFileEx(srcpath.c_str(), moveName.c_str(), MOVEFILE_COPY_ALLOWED))
            {   // Then the move failed
                LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
                        ifr->second.filename, moveName.c_str()) ; 

                // These files need to be deleted since they end up corrupting the 
                // overall processing on the Solarsoft side, since errors will
                // be generated if Solarsoft processes a job more than once. 
                if (LogAndDeleteFile(procParms.fplog, srcpath))
                {
                    LogToFile(procParms.fplog,
                        "ERROR - could not move or delete file from IBM directory. This can cause\n"
                        "   data corruption within Solarsoft. Manually correct the problem and then\n"
                        "   restart this process.\n") ; 
                    printf(
                        "ERROR - could not move or delete file from IBM directory. This can cause\n"
                        "   data corruption within Solarsoft. Manually correct the problem and then\n"
                        "   restart this process.\n") ; 
                }
            }
            else
            {
                LogToFile(procParms.fplog, "OK: processed '%s'\n", moveName.c_str()) ; 
            }

            FileRefMapItr ifrdel = ifr ;  
            ifr++ ; 
            frl.erase(ifrdel) ; // don't deal with this one anymore. 
        }
        else
        {   // This is a new order number so deal with it properly
            FILE *fp ; 
            int attempts = 0 ;   
            lastOrderNumber = ifr->first.order ; 
            csString pathname = AddFile2Path("ReRun\\", ifr->second.filename) ;
			tempName = ifr->second.filename;
            while (!(fp = fopen(pathname.c_str(), "rb")))
            {
                if (attempts++ > 10)
                    break ; 
                Sleep(250) ; 
            }

            if (!fp)
            {   // Couldn't open the file for reading. 
                LogToFile(procParms.fplog, 
                    "ERROR: couldn't open file '%s' for processing\n", ifr->second.filename) ;
            }
            else
            {

                /* 
                    As we scan through the file, need to maintain a current set of temp variables
                    as well as the mapped to variable definition that is used in the output file. 
                    As the variables are mapped, they are saved so that future values can be 
                    mapped equivalently. 

                    Note, the TMPxxx string in the RTE and BOM flat file is a 10 character 
                    string, so we are always subsituting 10 characters at a time. This is 
                    defined as FFTMPSZ
                */
                TmpVarVec tmpv ; 
                char buf[512] ; 

                while (fgets(buf, 512, fp))
                {
                    char *ps = strstr(buf, FFTMPPREFIX) ; 
                    if (ps)
                    {   // Found a temp string, map it and output it
                        TmpVar tvar ;
                        memcpy(tvar.srctmp, ps, FFTMPSZ) ;
                        tvar.srctmp[FFTMPSZ] = 0 ;
                        
                        // Does this already exist
                        int i = FindTmpCount(tmpv, tvar) ; 
                        if (i >= 0)
                        {   // Then we found the tmp variable so don't create a new one. 
                        }
                        else
                        {   // Need to add this one to the variable list
                            tvar.count = procParms.tmpCount++ ; 
                            tmpv.push_back(tvar) ; 
                            i = (int)tmpv.size() - 1 ; 
                        }

                        char tmpval[32] ; 
                        sprintf(tmpval, "TMP%d          ", tmpv[i].count) ; 
                        memcpy(ps, tmpval, 10) ; 

                    }

                    // Now dump out the line to the final output file which will contain 
                    // the merged data set of all the input files. 
                    if (strlen(buf))
                        bWroteSomething = 1 ; 
                    fprintf(fptmp, "%s", buf) ; 
                }

                fclose(fp) ; 
            }
           // ifr++ ; 
        }
    }

    // Close the output file 
    fclose(fptmp) ; 

    csString mergeName = BuildMoveToName2("MERGED_RTEBOM_") ; 

    int errorCode = 0 ; 
    if (!CopyFile(tmpName.c_str(), mergeName.c_str(), MOVEFILE_COPY_ALLOWED))
    {   // Something went wrong with the copy file 
        LogToFile(procParms.fplog, 
            "ERROR: could not copy '%s' to '%s'\n",
                tmpName.c_str(), mergeName.c_str()) ; 
        errorCode = 1 ; 
        printf("ERROR: see log file...\n") ; 
    }
    else
    {   // Everything is working so far, now archive all the source input files. 
        // Move the file to the IBM iSeries flat file processing directory. 
        csString ffdest = AddFile2Path(procParms.IBMdir, procParms.IBMfile) ; 
        int moveStat = 0 ; 
        if (bWroteSomething )
        {
            moveStat = MoveFileEx(tmpName.c_str(), ffdest.c_str(), MOVEFILE_COPY_ALLOWED) ; 
            LogToFile(procParms.fplog, "Skipping empty merge file...\n") ; 
        }

        if (bWroteSomething && !moveStat)
        {
            LogToFile(procParms.fplog, 
                "ERROR: could not move '%s' to '%s' Err#=%08x\n",
                    tmpName.c_str(), ffdest.c_str(),
                    GetLastError()) ;

            errorCode = 2 ; 
        }
        else
        {   // Success or there was nothing to move to the IBM dir. 
           // for (ifr = frl.begin() ; ifr != frl.end(); ifr++)
			if(ifr!=frl.end())
            {   
                csString basename = GetFileName(tempName) ;
                csString moveName = BuildMoveToName2(basename.c_str(), 1) ;
                csString srcpath = AddFile2Path("ReRun\\", tempName) ; 
                if (!MoveFileEx(srcpath.c_str(), moveName.c_str(), MOVEFILE_COPY_ALLOWED))
                {   // Then the move failed
                    //LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
                        //    tempName, moveName.c_str()) ; 

                    if (LogAndDeleteFile(procParms.fplog, srcpath))
                    {
                        LogToFile(procParms.fplog,
                            "ERROR - could not move or delete file. This can cause\n"
                            "   data corruption within Solarsoft. Manually correct the problem and then\n"
                            "   restart this process.\n") ; 
                        printf(
                            "ERROR - could not move or delete file from IBM directory. This can cause\n"
                            "   data corruption within Solarsoft. Manually correct the problem and then\n"
                            "   restart this process.\n") ; 
                    }

                    errorCode = 3 ;  
                }
                else
                {
                    LogToFile(procParms.fplog, "OK: processed '%s'\n", moveName.c_str()) ; 
                }
            }
        }
    }

    if (!errorCode)
        printf("    done.\n") ; 
    else
        printf("    error %d,  retrying operation...\n", errorCode) ; 

    return 0 ;
}
int LogAndDeleteFile(FILE *fplog, csString &srcpath) 
{
    FILE *fp = fopen(srcpath.c_str(), "rb") ; 
    if (fp)
    {
        LogToFile(fplog, "FLAT FILE MOVE ERROR - HAD TO DELETE THIS FILE, possible duplicate file, or run twice...\n") ; 
        LogToFile(fplog, "============== START OF ERR FILE =================\n") ; 

        char buf[1000] ;
        while (fgets(buf, 590, fp))
            LogToFile(fplog,"%s", buf) ; 
        fclose(fp) ; 

        LogToFile(fplog, "================ END OF ERR FILE =================\n") ; 
    }
    
    int retcode = 0 ; 
    if (!DeleteFile(srcpath.c_str()))
    {
        LogToFile(fplog, "ERROR: couldn't delete file '%s'\n", srcpath.c_str()) ; 
        retcode = -1 ; 
    }
    else
    {
        LogToFile(fplog, "Deleted file '%s'\n", srcpath.c_str()) ; 
    }
    
    return retcode ; 
}

//! Process the list of files. 
/*!
    This is the main processing loop. The files in the watch directory 
    are each scanned through and the TMPxxx strings are extracted and 
    remapped to unique values so that they can all exist in the same 
    file and be processed as a set by the Solarsoft flat file processor. 
 */
int ProcessFileSet(FileRefMap &frl)
{
    csString tmpName = AddFile2Path(procParms.watchDir, FFTEMPNAME ) ; 
    FILE *fptmp = fopen(tmpName.c_str(), "wb") ; 

    Sleep(500) ; // allow a bit of time for file write completion

    procParms.Reset() ; 

    // If there are two files which reference the same order number then we only
    // process the first one in the list (which would have been the last one
    // that was created). The reason is that until this file is run through the 
    // flat file processor, only the last file produced would make sense. There
    // is no way to create these files until the previous file is processed so
    // ..... (think about it and it will make sense). Thus everything has to be
    // done in CADUpdate. You can't create another program which attempts to do
    // its own flatfile generation, unless you really watch and pay attention
    // to what is going on. 
    // 
    // The main reason for this is that Solarsoft complains if there are any 
    // duplicate records. 
    // 
    int lastOrderNumber = 0 ; 
    int bWroteSomething = 0 ; 

    FileRefMapItr ifr ; 

    ifr = frl.begin() ;
    while (ifr != frl.end())
    {
        if (ifr->first.order == lastOrderNumber)
        {   // Delete this file from further consideration. 
            csString basename = GetFileName(ifr->second.filename) ;
            csString moveName = BuildMoveToName(basename.c_str(), 2) ;
            csString srcpath = AddFile2Path(procParms.watchDir, ifr->second.filename) ; 
            if (!MoveFileEx(srcpath.c_str(), moveName.c_str(), MOVEFILE_COPY_ALLOWED))
            {   // Then the move failed
                LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
                        ifr->second.filename, moveName.c_str()) ; 

                // These files need to be deleted since they end up corrupting the 
                // overall processing on the Solarsoft side, since errors will
                // be generated if Solarsoft processes a job more than once. 
                if (LogAndDeleteFile(procParms.fplog, srcpath))
                {
                    LogToFile(procParms.fplog,
                        "ERROR - could not move or delete file from IBM directory. This can cause\n"
                        "   data corruption within Solarsoft. Manually correct the problem and then\n"
                        "   restart this process.\n") ; 
                    printf(
                        "ERROR - could not move or delete file from IBM directory. This can cause\n"
                        "   data corruption within Solarsoft. Manually correct the problem and then\n"
                        "   restart this process.\n") ; 
                }
            }
            else
            {
                LogToFile(procParms.fplog, "OK: processed '%s'\n", moveName.c_str()) ; 
            }

            FileRefMapItr ifrdel = ifr ;  
            ifr++ ; 
            frl.erase(ifrdel) ; // don't deal with this one anymore. 
        }
        else
        {   // This is a new order number so deal with it properly
            FILE *fp ; 
            int attempts = 0 ;   
            lastOrderNumber = ifr->first.order ; 
            csString pathname = AddFile2Path(procParms.watchDir, ifr->second.filename) ;
            while (!(fp = fopen(pathname.c_str(), "rb")))
            {
                if (attempts++ > 10)
                    break ; 
                Sleep(250) ; 
            }

            if (!fp)
            {   // Couldn't open the file for reading. 
                LogToFile(procParms.fplog, 
                    "ERROR: couldn't open file '%s' for processing\n", ifr->second.filename) ;
            }
            else
            {

                /* 
                    As we scan through the file, need to maintain a current set of temp variables
                    as well as the mapped to variable definition that is used in the output file. 
                    As the variables are mapped, they are saved so that future values can be 
                    mapped equivalently. 

                    Note, the TMPxxx string in the RTE and BOM flat file is a 10 character 
                    string, so we are always subsituting 10 characters at a time. This is 
                    defined as FFTMPSZ
                */
                TmpVarVec tmpv ; 
                char buf[512] ; 

                while (fgets(buf, 512, fp))
                {
                    char *ps = strstr(buf, FFTMPPREFIX) ; 
                    if (ps)
                    {   // Found a temp string, map it and output it
                        TmpVar tvar ;
                        memcpy(tvar.srctmp, ps, FFTMPSZ) ;
                        tvar.srctmp[FFTMPSZ] = 0 ;
                        
                        // Does this already exist
                        int i = FindTmpCount(tmpv, tvar) ; 
                        if (i >= 0)
                        {   // Then we found the tmp variable so don't create a new one. 
                        }
                        else
                        {   // Need to add this one to the variable list
                            tvar.count = procParms.tmpCount++ ; 
                            tmpv.push_back(tvar) ; 
                            i = (int)tmpv.size() - 1 ; 
                        }

                        char tmpval[32] ; 
                        sprintf(tmpval, "TMP%d          ", tmpv[i].count) ; 
                        memcpy(ps, tmpval, 10) ; 

                    }

                    // Now dump out the line to the final output file which will contain 
                    // the merged data set of all the input files. 
                    if (strlen(buf))
                        bWroteSomething = 1 ; 
                    fprintf(fptmp, "%s", buf) ; 
                }

                fclose(fp) ; 
            }
            ifr++ ; 
        }
    }

    // Close the output file 
    fclose(fptmp) ; 

    csString mergeName = BuildMoveToName("MERGED_RTEBOM_") ; 

    int errorCode = 0 ; 
    if (!CopyFile(tmpName.c_str(), mergeName.c_str(), MOVEFILE_COPY_ALLOWED))
    {   // Something went wrong with the copy file 
        LogToFile(procParms.fplog, 
            "ERROR: could not copy '%s' to '%s'\n",
                tmpName.c_str(), mergeName.c_str()) ; 
        errorCode = 1 ; 
        printf("ERROR: see log file...\n") ; 
    }
    else
    {   // Everything is working so far, now archive all the source input files. 
        // Move the file to the IBM iSeries flat file processing directory. 
        csString ffdest = AddFile2Path(procParms.IBMdir, procParms.IBMfile) ; 
        int moveStat = 0 ; 
        if (bWroteSomething )
        {
            moveStat = MoveFileEx(tmpName.c_str(), ffdest.c_str(), MOVEFILE_COPY_ALLOWED) ; 
            LogToFile(procParms.fplog, "Skipping empty merge file...\n") ; 
        }

        if (bWroteSomething && !moveStat)
        {
            LogToFile(procParms.fplog, 
                "ERROR: could not move '%s' to '%s' Err#=%08x\n",
                    tmpName.c_str(), ffdest.c_str(),
                    GetLastError()) ;

            errorCode = 2 ; 
        }
        else
        {   // Success or there was nothing to move to the IBM dir. 
            for (ifr = frl.begin() ; ifr != frl.end(); ifr++)
            {   
                csString basename = GetFileName(ifr->second.filename) ;
                csString moveName = BuildMoveToName(basename.c_str(), 1) ;
                csString srcpath = AddFile2Path(procParms.watchDir, ifr->second.filename) ; 
                if (!MoveFileEx(srcpath.c_str(), moveName.c_str(), MOVEFILE_COPY_ALLOWED))
                {   // Then the move failed
                    LogToFile(procParms.fplog, "ERROR: could not move '%s' to '%s'\n", 
                            ifr->second.filename, moveName.c_str()) ; 

                    if (LogAndDeleteFile(procParms.fplog, srcpath))
                    {
                        LogToFile(procParms.fplog,
                            "ERROR - could not move or delete file. This can cause\n"
                            "   data corruption within Solarsoft. Manually correct the problem and then\n"
                            "   restart this process.\n") ; 
                        printf(
                            "ERROR - could not move or delete file from IBM directory. This can cause\n"
                            "   data corruption within Solarsoft. Manually correct the problem and then\n"
                            "   restart this process.\n") ; 
                    }

                    errorCode = 3 ;  
                }
                else
                {
                    LogToFile(procParms.fplog, "OK: processed '%s'\n", moveName.c_str()) ; 
                }
            }
        }
    }

    if (!errorCode)
        printf("    done.\n") ; 
    else
        printf("    error %d,  retrying operation...\n", errorCode) ; 

    return 0 ;
}




int CheckRecord (int sonum)
{
	 char uqry[256] ; 
	 //SO[0] = 123456;
	 sprintf(uqry, "select count(*) from %s.CADUPDATE WHERE SONUM = '%d'", 
					 gParms.evp.m_db.dbname, sonum) ; 
	int retry = 0 ; 
	
    
    try
    {
        CSQLRecordset rs(gParms.evp.m_db);
        rs << uqry ; 
        rs.SQLExec();
		//bool test = rs.SQLFetch();
        while (rs.SQLFetch())
        {
            SONumCount = atoi(rs.SQLGetData(1).c_str()) ; 
			//break;
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

        gParms.evp.m_db.Reconnect() ; 

    }
	return 0;
}

int UpdateRecord (int sonum, char condition)
{
	
	/*SYSTEMTIME st;
    GetSystemTime(&st);
	char timestring[128] ; 
    sprintf(timestring, "%4d-%02d-%02d %02d:%02d:%02d", 
                st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);*/
	char datestr[64] ;
	csString time;
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 0) ;

	time = datestr;
	char uqry[512] ; 
    try
    {
        sprintf(uqry, "UPDATE %s.CADUPDATE SET STATUS='%c', TASKTIME='%s' WHERE " "SONUM='%d'", 
                    gParms.evp.m_db.dbname, condition, datestr, sonum);

        CSQLRecordset rsu(gParms.evp.m_db) ;
        rsu << uqry ; 
        rsu.SQLExec();
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

        gParms.evp.m_db.Reconnect() ; 

    }
	return 0;
}

int InsertRecord (int sonum, char condition)
{
	char datestr[64] ;
	csString time;
    CDateTime dtime ; 
    dtime.SetNow() ; 
    dtime.FormatDateTimeSecs(datestr, 0) ;

	char uqry[256] ; 
    try
    {
		//tasktime equal when Q:ff empty, or simply way when the merge file is done.
		//insert into cmsdat.cadupdate (SONUM, STATUS, TASKTIME) values ('123456','w','2010-12-30 23:30:35.000000')

        sprintf(uqry, "INSERT INTO %s.CADUPDATE (SONUM, STATUS, TASKTIME) values ('%d', '%c', '%s')", 
                    gParms.evp.m_db.dbname, sonum, condition, datestr);

        CSQLRecordset rsu(gParms.evp.m_db) ;
        rsu << uqry ; 
        rsu.SQLExec();
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

        gParms.evp.m_db.Reconnect() ; 

    }
	return 0;
}

int SOToFile(FILE *fp, const char *formatstr, ...) 
{
    if (!fp)
        return -1 ; // can't, file doesn't exist. 

    int retcode = 0 ; 
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
    try {
        vfprintf(fp, formatstr, marker) ;
        fflush(fp) ; 
    }
    catch(...)
    {
        retcode = -2 ; 
    }
    va_end(marker) ; 

    return retcode ; 
}

int GetSO(FILE *fp)
{
	csString m_strLine, m_strText;
	char line[512]="";
	if(fp!=NULL)
	{
		// read each line in the file
		while(fgets(line,sizeof(line),fp)!=NULL)
		{
			//convert the line to a CString
			m_strLine = line;
			//store each line to the text string
			m_strText += m_strLine;
		}
		fclose(fp);
	}
	else
	{
		return -1;
	}

	int j, i=0; // used to iterate through array

    char userInput[1024], *token[80]; //user input and array to hold max possible tokens, aka 80.
	char *temp;
	int num = m_strText.len;
	static char inputString[512];
	for(int i = 0; i<=num; i++)
	{
		inputString[i] = m_strText[i];
	}
		
    token[0] = strtok(inputString, ","); //get pointer to first token found and store in 0
                                       //place in array
    while(token[i]!= NULL) {   //ensure a pointer was found
        i++;
        token[i] = strtok(NULL, ","); //continue to tokenize the string
    }
    long int test2[1024];
    for(j = 0; j <= i-1; j++) {
        sprintf(userInput, "%s", token[j]); //print out all of the tokens
		
		test2[j] = strtol(userInput,&temp,10);
		SO[j] = test2[j];
    }

    return 0;


}

int GetSOName(char *dirname)
{
    
    csString listDir(dirname) ; 
    listDir += "\\*" ; 

    int filecount = 0 ; 
    WIN32_FIND_DATA findData ; 
    HANDLE hFind = FindFirstFile(listDir.c_str(), &findData) ; 
	
	//int m_nMappedSONUM = sonum;
	
    
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
				sonumber = fref.ordernumber ;
				if(sonumber>200000)
				{
					cs_fileName = findData.cFileName;
					return 1;
				}
				//cs_fileName  = findData.cFileName;
			   // if(m_nMappedSONUM==fref.ordernumber)
			//	{
				//	cs_fileName  = findData.cFileName;
					//return 1;
				//	break;
				//}
			}
        } while (FindNextFile(hFind, &findData)) ;

        FindClose(hFind);
    }
	return 0;
}

int CheckProcess (int sonum)
{
	int count = 0;
	char uqry[256] ; 
	 //SO[0] = 123456;
	sprintf(uqry, "select count(*) from %s.cjobh WHERE dnord# = '%d' AND DNPART LIKE 'HD%'", 
					 gParms.evp.m_db.dbname, sonum) ; 
    try
    {
        CSQLRecordset rs(gParms.evp.m_db);
        rs << uqry ; 
        rs.SQLExec();
		//bool test = rs.SQLFetch();
        while (rs.SQLFetch())
        {
            count = atoi(rs.SQLGetData(1).c_str()) ; 
			//break;
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

        gParms.evp.m_db.Reconnect() ; 
		count = -1;
    }
	return count;
}