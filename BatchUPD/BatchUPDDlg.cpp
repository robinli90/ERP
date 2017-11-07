// BatchUPDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BatchUPD.h"
#include "BatchUPDDlg.h"
#include <time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int ReWork;
int Scrap;

// CBatchUPDDlg dialog



CBatchUPDDlg::CBatchUPDDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBatchUPDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ToTime = COleDateTime::GetCurrentTime();
	m_FromTime = COleDateTime::GetCurrentTime();
}

void CBatchUPDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_grid);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_ToTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_FromTime);
}

BEGIN_MESSAGE_MAP(CBatchUPDDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, OnBnClickedSave)
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButtonStart)
END_MESSAGE_MAP()


UINT LoadInitialData(void *pbatch) 
{
    CBatchUPDDlg *pbu = (CBatchUPDDlg *)pbatch ; 
    pbu->LoadJobListMaster() ; 
    return 0 ; 
}

int CBatchUPDDlg::Split(char *input, char *delimiter, char output[][256])
{
    char *pch;
    pch = strtok(input, delimiter);
    int i = 0;
    while (i < 15 && pch != NULL)
    {
        CS_strmaxcpy(output[i++], pch, 250) ; 
        pch = strtok (NULL, delimiter);
    }
    return i ;
}


BOOL CBatchUPDDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // progress bar
	m_Progress.SetStep(1);
    // grid captions
    m_grid.Clear() ; 
    for(int i = 0; i < m_grid.get_Cols(); i++)
    {   
        // Set the text alignment in the columns
        m_grid.put_ColAlignment(i, CMsflexgrid1::flexAlignLeftCenter) ;
    }
    m_grid.put_ColWidth(0,8200); //Combined Field
    m_grid.put_ColWidth(1,450) ;  // qty
    m_grid.put_ColWidth(2,450) ;  // scrap
    m_grid.put_ColWidth(3,500) ;  // serial 
    m_grid.put_ColWidth(4,700) ;  // runtime
    m_grid.put_ColWidth(5,700) ;  // pending 
    m_grid.put_ColWidth(6,650) ;  // actual time
    m_grid.put_ColWidth(7,500) ;  // Serial
    m_grid.put_ColWidth(8,3000) ;  // decade track info
    char combinedHeader[256] ; 
    sprintf(combinedHeader, "%-6s; %-20s; %-5s; %-3s; %-10s; %-13s; %-5s", "SO#", "Part", "Res", "SEQ", "Job#", "StartTime", "RunStd") ; 
    m_grid.put_TextMatrix(0,0,combinedHeader) ;
    m_grid.put_TextMatrix(0,1,"Qty") ;
    m_grid.put_TextMatrix(0,2,"Scrp") ;
    m_grid.put_TextMatrix(0,3,"Ser#") ;
    m_grid.put_TextMatrix(0,4,"RunTime") ;
    m_grid.put_TextMatrix(0,5,"Pend'g") ;
    m_grid.put_TextMatrix(0,6,"Actual") ;
    m_grid.put_TextMatrix(0,7,"Ser#") ;
    m_grid.put_TextMatrix(0,8,"Decade Trk Info") ;
    // grid font
    m_grid.put_FontName("Courier New") ; 
    m_grid.put_FontSize(8.0) ; 

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    return TRUE;  // return TRUE  unless you set the focus to a control	
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBatchUPDDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBatchUPDDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CBatchUPDDlg::OnBnClickedSave()
{
    if (IDYES == AfxMessageBox("Save changes to file for processing?", MB_YESNO))
    {
        if (!SaveBatchFlatFile())
        {
            OnOK();
        }
    }
}

csString *Split(char *input, char *delimiter, csString output[])
{
	char * pch;
	pch = strtok(input, delimiter);
	int i = 0;
	while (pch != NULL)
	{
		output[i]= pch;
		i++;
		pch = strtok (NULL, delimiter);
	}
	
	return output;
}

char *ConvtStrToChar (csString stringInput)
{
	int num = stringInput.Length();
	static char inputString[512];
	for(int i = 0; i<=num; i++)
	{
		inputString[i] = stringInput[i];
	}
	return inputString;
}

int ExtractPrtCode(csString prtName)
{
	int findPrt = -1;
	csString splitStringSO[512];
	char* c_prtSplit = ConvtStrToChar(prtName);
	csString* s_prtSplit = Split(c_prtSplit, " ",splitStringSO);
	s_prtSplit[0].Trim();
	int testa = sizeof(s_prtSplit);
	//if first element is not HD then the prtcode is in 0th place.
	if(s_prtSplit[0] != "HD")
	{
		csString s_prtSplitF = s_prtSplit[0];
		s_prtSplitF.Trim();
		if(s_prtSplitF=="BAH")
		{
			//"B%"; and != "BO";
			findPrt = 1; 
		}
		else if(s_prtSplitF=="BOH")
		{
			//"O%"  OR "BO";
			findPrt = 2;
		}
		else if(s_prtSplitF=="FDR")
		{
			//"F%";
			findPrt = 3; 
		}
		else if(s_prtSplitF=="RI")
		{
			//"R%";
			findPrt = 4; 
		}
		else if(s_prtSplitF=="SD")
		{
			findPrt = 5;
		}
	}
	else if(s_prtSplit[0] == "HD")
	{
		//if first elemnt is HD then the prtcode is in 4th place.
		if(sizeof(s_prtSplit)>=4)
		{
			csString s_prtSplitF = s_prtSplit[4];
			if(s_prtSplitF.FindIDX("BAC")>-1)
				findPrt = 6;
			else if (s_prtSplitF.FindIDX("PLAT")>-1)
				findPrt = 7;
			else if (s_prtSplitF.FindIDX("MAND")>-1)
				findPrt = 8;
		}
	}
	return findPrt;
}

int ScrapFound(csString SONUM, csString PRTCODE)
{
	CBatchUPDApp *pApp = (CBatchUPDApp*)AfxGetApp() ; 
	int scrap = -1;
	char qry[512];
	sprintf(qry,"SELECT COUNT (*) FROM %s.EXCOTASK WHERE PLANT = '%s' AND SONUM = '%s'"
		" AND PRTCODE LIKE %s AND SCRAP = 'T'", gCMSparms.dbname, gCMSparms.plantID, SONUM.c_str(), PRTCODE.c_str());
	try
	{
		CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
		{
			scrap = atoi(rs.SQLGetData(1).c_str());
		}
	}
	 catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading department codes:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }
	return scrap;	
}

int ReWorkFound (csString SONUM, csString PRTCODE)
{
	CBatchUPDApp *pApp = (CBatchUPDApp*)AfxGetApp() ; 
	int RWScrap = -1;
	char qry[512];
	sprintf(qry,"SELECT COUNT (*) FROM %s.EXCOTASK WHERE PLANT = '%s' AND SONUM = '%s'"
		" AND PRTCODE LIKE %s AND REWORK = 'T'", gCMSparms.dbname, gCMSparms.plantID, SONUM.c_str(), PRTCODE.c_str());
	try
	{
		CSQLRecordset rs(pApp->cmsdata.m_db) ;
        rs << qry ; 
        rs.SQLExec();
        while (rs.SQLFetch())
		{
			RWScrap = atoi(rs.SQLGetData(1).c_str());
		}
	}
	 catch (CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading department codes:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
        }
    }
	return RWScrap;	
}

int AllStepsDone(CMSJob *J)
{
	for (size_t i=0; i < J->cjobdrVec.size(); i++)
    {
        if (J->cjobdrVec[i].actualRunTime <= 0 &&
            J->cjobdrVec[i].pendingRunTime <= 0 && 
            J->cjobdrVec[i].totalRunTime <= 0 && 
            J->cjobdrVec[i].qtydone == 0 && 
            J->cjobdrVec[i].seqno != gCMSparms.seqMerge)
        {   // Then this step is still pending
            return 0 ; 
        }
    }
    return 1 ; 
}

int CBatchUPDDlg::SaveBatchFlatFile()
{

    int retcode = 0 ; 

    CString csSO, csPart, csRes, csSEQ, csJOB, csSerl ;
    CString csTime, csPdng, csAct, csQty, csQAct, csSerV ; 
    CString csQtyS, csStTm; 

    //"SO#;Part;Res;SEQ;Job;StartTime;RunStd"
    CString csCombine;
    CString csSOField = _T("SO#");
    CString csPartField = _T("Part");
    CString csResField = _T("Res");
    CString csSEQField = _T("SEQ");
    CString csJOBField = _T("Job");
    CString csStartTimeField = _T("StartTime");
    CString csRunStd = _T("RunStd");

    ResJobMap xmap ; 

    csString jnum(64) ;  // allocate sufficent space for job number

    CMSOrdXRefMap ordmap ; 

    // The 0'th row in the grid are the header titles

    if (deptMode)
    {   
        // This MODE is now ignored and this code should never be used 
        // and does not work. Left just in case for the future, but will 
        // have to be completely reworked based on the master mode code. 
        for (int i=1; i <= numRows; i++)
        {
            //Didn't change this part
            csSEQ  = m_grid.get_TextMatrix(i, 4) ; 
            csJOB  = m_grid.get_TextMatrix(i, 5) ; 
            csTime = m_grid.get_TextMatrix(i, 7) ; 
            csAct  = m_grid.get_TextMatrix(i, 8) ;

            csAct.Trim() ; 

            if (csJOB.GetLength() > 0 && csAct.GetLength() > 0)
            {
                CS_strmaxcpy(jnum.str, (LPCTSTR)csJOB, 32) ; 
                jnum.Trim() ; 

                JobRecMapItr ijm = jobmap.find(jnum) ; 
                if (ijm != jobmap.end())
                {
                    ijm->second.actualTime = atof((LPCTSTR)csAct) ; 
                    ijm->second.bModified = 1 ; 
                    
                    ResJobXRef xref ; 
                    xref.ijm = ijm ; 
                    xref.job = ijm->second.jobnum ; 
                    xref.res = ijm->second.res ; 
                    xref.SetKey() ; 
                    csString key = xref.key ; 

                    xmap.insert(make_pair(key, xref)) ; 
                }
            }
        }
    }
    else
    {   // master list mode

        // Go through and group all the jobs by order so that we can see which 
        // ones are complete. 
        for (int i=1; i < numRows; i++)
        {
            csCombine = m_grid.get_TextMatrix(i, 0);

            // char inputString[100];
			char input[1024] ; 
			CS_strmaxcpy(input, (LPCTSTR)csCombine, 500) ; 
            char splitString[16][256];
            int nflds = Split(input, ";",splitString);

            //Put back csSO, csSEQ, csJOB and csStTm back from Combined field
            csSO = splitString[0];
            csSEQ = splitString[3];
            csJOB = splitString[4];
            csStTm  = splitString[5];

            csQty  = m_grid.get_TextMatrix(i, 1) ; //Qty
            csQtyS = m_grid.get_TextMatrix(i, 2) ; //Scrap
            csSerl = m_grid.get_TextMatrix(i, 3) ;//Serial Number
            csTime = m_grid.get_TextMatrix(i, 4) ;//RunTime
            csPdng = m_grid.get_TextMatrix(i, 5) ;//pending
            csAct  = m_grid.get_TextMatrix(i, 6) ;//Actual Time
            csSerV = m_grid.get_TextMatrix(i, 7) ; // serial number override
			csSerl = "";

            csSO.Trim() ; 
            csAct.Trim() ; 
            csSerV.Trim() ; 

            csString job((LPCTSTR) csJOB) ; 
            job.Trim() ; 

            if (csSO == "227220")
            {
                int xx = 0 ; 
                xx++ ; 
            }

            if (job.size() > 0)
            {
                CMSJobMapItr ijm = jobsmap.find(job) ; 

                if (ijm != jobsmap.end())
                {   
                    // Now find the order record
                    CMSOrdXRefMapItr ior = ordmap.find(csString((LPCSTR)csSO)) ; 
                    if (ior == ordmap.end())
                    {   // Then add it to the map
                        CMSOrdXRef ordx ; 
                        ordx.ordernum = csSO ; 

                        pair<CMSOrdXRefMapItr, bool> iopair ;
                        iopair = ordmap.insert(make_pair(csSO, ordx)) ; 
                        if (iopair.second)
                            ior = iopair.first ; 
                    }

                    int found = 0; 
                    if (ior != ordmap.end())
                    {   // See if this job is in the order map
                        for (size_t k=0; k < ior->second.jv.size(); k++)
                        {
                            if (ior->second.jv[k]->jobnum == job) 
                            {
                                found = true ; 
                                break ; 
                            }
                        }
                    }

                    if (!found)
                    {   // Add this job
                        ior->second.jv.push_back(&(ijm->second)) ;
                    }
                }
            }
        }

        char prevpart[64], lastpart[64] ; 
        char prevjob[64], lastjob[64] ; 
        int lastseq ; 
        int finalseq = 0 ; 
        int xlinenum = 1 ; 
        double totalTime = 0.0 ; 

        prevpart[0] = 0 ; 
        prevjob[0] = 0 ; 
  
        FILE *fpx = fopen("C:\\CMS\\WIPlist.txt", "wt") ; 
    
        for (int i=1; i < numRows; i++)
        {
            lastjob[0] = 0 ; 
            lastpart[0] = 0 ; 
            lastseq = 0 ;
			totalTime = 0 ; 

            csCombine = m_grid.get_TextMatrix(i, 0) ;

			csCombine.Trim() ; 
			if (csCombine.GetLength() == 0)
				continue ; 

            char input[1024] ; 
			CS_strmaxcpy(input, (LPCTSTR)csCombine, 500);
            static char splitString[16][256];
            int nflds = Split(input, ";", splitString);

            //Put back csSO, csSEQ, csJOB and csStTm back from Combined field
            csSO = splitString[0] ;
            csPart = splitString[1] ;
            csSEQ = splitString[3] ;
            csJOB = splitString[4] ;
            csStTm  = splitString[5] ;
            csQty  = m_grid.get_TextMatrix(i, 1) ; 
            csQtyS = m_grid.get_TextMatrix(i, 2) ; 
            csSerl = m_grid.get_TextMatrix(i, 3) ;
            csTime = m_grid.get_TextMatrix(i, 4) ;
            csPdng = m_grid.get_TextMatrix(i, 5) ;
            csAct  = m_grid.get_TextMatrix(i, 6) ;
            csSerV = m_grid.get_TextMatrix(i, 7) ; 

            csPart.Trim() ; 
            csAct.Trim() ; 
            csSerV.Trim() ; 
            csQtyS.Trim() ; 

            csString job((LPCTSTR) csJOB) ; 
            job.Trim() ; 

            csString part((LPCTSTR) csPart) ; 
            part.Trim() ; 

            if (job.size() > 0)
            {   // Then this isn't a blank row
                CMSJobMapItr ijm = jobsmap.find(job) ;
                if (ijm != jobsmap.end())
                {
                    csString seq((LPCTSTR)csSEQ) ; 
                    seq.Trim() ; 
                    int nSeq = atoi(seq.c_str()) ; 

                    // Now find the specific sequence step
                    for (int j=0; j < (int)ijm->second.cjobdrVec.size(); j++)
                    {
                        // CMSJob
                        if (ijm->second.cjobdrVec[j].seqno == nSeq)
                        {   // Found it

                            CS_strmaxcpy(lastjob, job.c_str(), 40) ; 
                            CS_strmaxcpy(lastpart, part.c_str(), 40) ; 
                            lastseq = nSeq ; 

                            RouteDataRec *prr = &(ijm->second.cjobdrVec[j]) ;

                            // Now decide if we need to actually update this data within Solarsoft
                            // UPDATE DECISION LOGIC
                            if ((csAct.GetLength() > 0) ||
                                (csSerV.GetLength() > 0 && atoi((LPCTSTR)csSEQ) == 100) || 
                                (atof(csTime) > 0 && atoi(csQty) == 0) || 
                                (atof(csPdng) > 0) ||
                                (atoi(csSerl) != 0) || 
                                (prr->bProcFlags & PRCF_SET_TIME_STAMP) ||
                                (prr->bSetStdRunIfBlank & 0x01)
                               ) 
                            {	// Then update this record 
                                prr->actualRunTime = atof((LPCTSTR)csAct) ; 
                                prr->bModified = 1 ;

                                if ((prr->actualRunTime == 0) && 
                                    ((prr->bSetStdRunIfBlank & 0x01) || 
                                     (prr->bProcFlags & PRCF_SET_TIME_STAMP)) && 
                                    (prr->pendingRunTime == 0.0))
                                {   // Then force this record to the run standard time.
                                    prr->actualRunTime = prr->runstd ; 
                                }
								
                                if (csSerV.GetLength() > 0 && atoi((LPCTSTR)csSEQ) == 100)
                                {   // override the defined serial number. 
                                    prr->serialnum = atoi((LPCTSTR)csSerV) ; 
                                }
                                //cross reference to the resource table.
                                ResJobXRef xref ; 
                                xref.ijob = ijm ; 
                                xref.job = job ; 
                                xref.res = ijm->second.cjobdrVec[j].resource ; 
                                xref.idx = j ; 
                                xref.SetKey(nSeq) ; 
                                csString key = xref.key ; 

                                xmap.insert(make_pair(key, xref)) ; 
                            }

                            if (prr->actualRunTime > 0.001)
                                totalTime = prr->actualRunTime ;
                            else
                                totalTime = prr->totalRunTime + prr->pendingRunTime ; 

                            break ; 
                        }
                    }
                }
            }

            if ((prevjob[0] && strcmp(prevjob, lastjob) != 0) ||
				(prevpart[0] && strcmp(prevpart, lastpart) != 0)
			   )
            {   // This is a new job, process the last active job
                csString jobstr(prevjob) ;

                if (fpx && finalseq > 0)
                {
                    fprintf(fpx, "\"001PRD\",\"%s\",\"%s\",\"%03d\",%d,1.0,\"EA\",1\n",
                                prevpart, prevjob, finalseq, xlinenum++) ; 
                }
                finalseq = 0 ; 
            }


            CS_strmaxcpy(prevjob, lastjob, 40) ; 
            CS_strmaxcpy(prevpart, lastpart, 40) ; 
            if (lastseq > 0 && totalTime > 0)
                finalseq = lastseq ; 

        }  // end for grid row

        fclose(fpx) ; 
    }


    // Now go through orders and see which ones are fully complete with the exception
    // of sequence step 800. 
    CMSOrdXRefMapItr ior ;  
    for (ior = ordmap.begin(); ior != ordmap.end(); ior++)
    {
		int masterCount=0, subCount=0;


        bool allDone = true ; 
        for (size_t k=0; allDone &&  (k < ior->second.jv.size()); k++)
        {
            CMSJob *pjob = ior->second.jv[k] ; 
			if(pjob->subCount>1)
			{
				masterCount++;
			}
			else 
				subCount++;
            if (pjob->ordNum == "227220")
            {
                int xx = 0 ; 
                xx++ ; 
            }

            if (!AllStepsDone(pjob))
                allDone = false ; 
        }

		if(masterCount&&subCount==0)
			allDone = false;

        if (allDone)
        {   // Go through and complete the 800 sequence steps
            for (size_t k=0; k < ior->second.jv.size(); k++)
            {
                CMSJob *pjob = ior->second.jv[k] ; 

                // Complete the job
                size_t n = pjob->cjobdrVec.size() - 1 ; 
                if (pjob->cjobdrVec[n].seqno == gCMSparms.seqMerge)
                {
                    CMSJobMapItr ijm = jobsmap.find(pjob->jobnum) ; 
                    if (ijm != jobsmap.end())
                    {
                        RouteDataRec *prr = &(pjob->cjobdrVec[n]) ;
                        prr->bModified = 1 ; 
                        prr->actualRunTime = prr->runstd ; 

                        ResJobXRef xref ; 
                        xref.ijob = ijm ; 
                        xref.job = pjob->jobnum ; 
                        xref.res = prr->resource ; 
                        xref.idx = (int)n ; 
                        xref.SetKey(gCMSparms.seqMerge) ; 
                        csString key = xref.key ; 

                        xmap.insert(make_pair(key, xref)) ; 
                    }
                    else
                    {   // Should never get here
                        // Log error
                    }
                }
            }
        }
    }

    // Go through and assign the prevScrapCount value
    CMSJobMapItr ijmi ; 
    for (ijmi = jobsmap.begin(); ijmi != jobsmap.end(); ijmi++)
    {
        double prescrap = 0 ; 
        ijmi->second.ilastActiveSeq = -1 ; 
        for (int jj=(int)ijmi->second.cjobdrVec.size()-1; jj >= 0; jj--)
        {
            RouteDataRec *prec = &(ijmi->second.cjobdrVec[jj]) ;
            prec->finalQty = 0 ; 
            if (ijmi->second.ilastActiveSeq < 0 && (prec->RunTime() > 0))
                ijmi->second.ilastActiveSeq = jj ; 

            prec->prevScrapCount = prescrap ;
            prescrap += prec->qtyscrap ;
        }
    }

    BatchHeader hdr ;
    memset(&hdr, 0x20, sizeof(BatchHeader)) ;
    CS_strmaxcpy(hdr.plant, gCMSparms.plantID, 3) ;
    hdr.shift = '1' ;
	CDate FromTime;
	FromTime = CDate(m_FromTime.GetYear(), m_FromTime.GetMonth(), m_FromTime.GetDay());
	hdr.reportdate = FromTime;
    //hdr.reportdate.SetNow() ;
    hdr.fiscYear  = 0 ; 
    hdr.fiscMonth = 0 ; 

    // Fiscal period is in YYPP format, where PP is the month into the entities
    // year depending on the financial year end. Thus For Exco Nov 2010 = 1102
    // Since there fiscal year starts Oct 1. 
    
    char tmpstr[512] ; 

    CDate fpd ; 
	fpd = CDate(m_FromTime.GetYear(), m_FromTime.GetMonth(), m_FromTime.GetDay());
   
	int m = (fpd.m_nMonth - 9) % 12 ; 
    hdr.shiftGroup = ' ' ; // leave blank for now
    char batchName[512] ; 
    char tmpbatch[512] ; 

    _snprintf(tmpbatch, 500, "C:\\CMS\\%s.BCH", gCMSparms.plantID) ; 
    _snprintf(batchName, 500, "%s%s.BCH", gCMSparms.batchDir, gCMSparms.plantID) ; 

    FILE *fp = fopen(tmpbatch, "wb") ; 

    // CMSJob

    int len ; 
    ResJobMapItr ix ;
    csString lastRes ;

    if (deptMode)
    {
        for (ix = xmap.begin(); ix != xmap.end(); ix++)
        {
            if (lastRes != ix->second.res)
            {   // Then this is a new resource so output the header record
                len = hdr.SetString(tmpstr) ; 
                fwrite(tmpstr, 1, len, fp) ; 
                fflush(fp) ; 
                lastRes = ix->second.res ;
            }

               
            if (ix->second.ijm->second.bModified)
            {   // Then output this record. 
                JobRec *pjr = &(ix->second.ijm->second) ;
                double deltaTime = 0.0 ;
                deltaTime = pjr->actualTime - pjr->totalTime ; 

                BatchDetail dtl ;

                CS_strmaxcpy(dtl.dept,      pjr->dept, 8) ;
                CS_strmaxcpy(dtl.resource,  pjr->res,  8) ;
                CS_strmaxcpy(dtl.part,      pjr->part, 20) ;
                sprintf(dtl.seqnum, "%03d", pjr->seqnum) ;
                CS_strmaxcpy(dtl.indcode,   " ", 4) ;
                dtl.machtime = deltaTime ; 
                CS_strmaxcpy(dtl.orderNum,  pjr->jobnum.c_str(), 12 ) ;
                dtl.nummen  = '1' ; 
                dtl.nummach = '1' ; 
                dtl.dbldig = 'N' ; 
                dtl.nMen2 = 0 ; 
                dtl.nMach2 = 0 ; 

                len = dtl.SetString(tmpstr) ; 
                fwrite(tmpstr, 1, len, fp) ; 
                fflush(fp) ; 
            }
        }
    }
    else
    {   // master mode
        for (ix = xmap.begin(); ix != xmap.end(); ix++)
        {
            if (lastRes != ix->second.res)
            {   // Then this is a new resource so output the header record
                len = hdr.SetString(tmpstr) ; 
                fwrite(tmpstr, 1, len, fp) ; 
                fflush(fp) ; 
                lastRes = ix->second.res ;
            }
                
            CMSJob *pjob = &(ix->second.ijob->second) ;
            int i = ix->second.idx ; 

            double newRunTime = 0.0 ; 
            int newQty = 0 ; 
            int maxQty = (int)(pjob->cjobdrVec[i].prevScrapCount + 1) ; 

            if (pjob->cjobdrVec[i].actualRunTime != 0.0)
                newRunTime = pjob->cjobdrVec[i].actualRunTime ; 
            else
                newRunTime = pjob->cjobdrVec[i].RunTime() ; 

            //   Modified Nov 12, 2010 -logic changed to just adjust out the actual quantities
            if (pjob->cjobdrVec[i].seqno == 100)
            {   // Then this is the saw which is a special case
                if (pjob->cjobdrVec[i].qtysaw)
                {
                    newQty = (int)(pjob->cjobdrVec[i].qtydone + 1) ;
                    if (pjob->cjobdrVec[i].qtydone + newQty > maxQty)
                        newQty = (int)(maxQty - pjob->cjobdrVec[i].qtydone) ; 
                }
                else
                {   // There was no saw tracking event. So work out what the 
                    // valid quantity should be
                    if (pjob->ilastActiveSeq > 0 &&
                        pjob->cjobdrVec[i].qtydone > maxQty)
                    {
                        newQty = maxQty ;
                    }
                    else if (pjob->ilastActiveSeq >= i &&
                             pjob->cjobdrVec[i].qtydone == 0)
                    {
                        newQty = 1 ;
                    }
                }


            }
            else
            {   // Let standard logic apply 
                if ( pjob->cjobdrVec[i].bModified ||
                    (pjob->cjobdrVec[i].qtydone == 0 && newRunTime > 0.0))
                {
                    newQty = (int)(pjob->cjobdrVec[i].prevScrapCount + 1 - 
                                            pjob->cjobdrVec[i].qtydone) ; 
                    if (pjob->cjobdrVec[i].qtydone + newQty > maxQty)
                        newQty = (int)(maxQty - pjob->cjobdrVec[i].qtydone) ; 
                }
                else if (newRunTime > 0.0)
                {
                    int ip = i - 1 ; 
                    if (ip >= 0)
                    {   // If the previous step quantity is > then this one
                        // then set this one to match up to the previous
                        if (pjob->cjobdrVec[i].qtydone < pjob->cjobdrVec[ip].qtydone)
                            newQty = (int)(pjob->cjobdrVec[ip].qtydone) ;
                        if (pjob->cjobdrVec[i].qtydone + newQty > maxQty)
                            newQty = (int)(maxQty - pjob->cjobdrVec[i].qtydone) ; 
                    }
                }
            }

            if (newQty || (i > 0 && pjob->cjobdrVec[i-1].bTrackCAMmtl))
                pjob->cjobdrVec[i].bModified = 1 ;
            
            

            // The bModified flag is really all we should be looking at. Need to follow
            // through and see why the qtydone==0 && runtime > 0 part of the if clause 
            // is there. Not sure if it actually does anything anymore since most of the 
            // logic is handled in the area above labelled "UPDATE DECISION LOGIC"
            if (pjob->cjobdrVec[i].bModified ||
                (pjob->cjobdrVec[i].qtydone == 0 && newRunTime > 0.0))
            {   // Then output this record. 

                if (pjob->cjobdrVec[i].seqno == 100 && newQty == 0)
                    continue ; // skip this record, a DTL record on it's own causes double material tracking. 
                double deltaTime = 0.0 ;

                // Only apply a time delta if the user actually entered an adjustment amount. 
                // Otherwise leave deltaTime as zero. The only reason deltaTime would be zero
                // is if we are going to update the quantity in the PRT record. 
                if (fabs(pjob->cjobdrVec[i].actualRunTime) >= 0.01)
                    deltaTime = pjob->cjobdrVec[i].actualRunTime - pjob->cjobdrVec[i].totalRunTime ; 
                else if (pjob->cjobdrVec[i].pendingRunTime > 0.01)
                    deltaTime = pjob->cjobdrVec[i].pendingRunTime ; 

                if (deltaTime == 0 && newQty == 0 && 
                    !(i > 0 && pjob->cjobdrVec[i-1].bTrackCAMmtl))
                {
                    continue ; // then skip this one
                }
            
                BatchDetail dtl ;
				int seqnumber = 0;
                // UPDATE TO INCLUDE PART QUANTITIES ;

                dtl.dept[0] = gCMSparms.plantID[0] ; 
                dtl.dept[1] = gCMSparms.plantID[1] ; 
                dtl.dept[2] = gCMSparms.plantID[2] ; 
                CS_strmaxcpy(dtl.dept+3,    pjob->cjobdrVec[i].dept.c_str(), 5) ;
                CS_strmaxcpy(dtl.resource,  pjob->cjobdrVec[i].resource.c_str(),  8) ;
                CS_strmaxcpy(dtl.part,      pjob->partname.c_str(), 20) ; 
                sprintf(dtl.seqnum, "%03d", pjob->cjobdrVec[i].seqno) ;
				seqnumber = pjob->cjobdrVec[i].seqno;
                CS_strmaxcpy(dtl.indcode,   " ", 4) ;
                dtl.machtime = deltaTime ; 
                CS_strmaxcpy(dtl.orderNum,  pjob->jobnum.c_str(), 12) ;
                dtl.nummen  = '1' ; 
                dtl.nummach = '1' ; 
                dtl.dbldig = 'N' ; 
                dtl.nMen2 = 0 ; 
                dtl.nMach2 = 0 ; 

                len = dtl.SetString(tmpstr) ; 
                fwrite(tmpstr, 1, len, fp) ; 
                fflush(fp) ; 

                // Now output part records as required
				//newQty != 0
                if (newQty != 0)
                {   // Force it to one, since all parts have a quantity of 1
                    
                    // TODO - allow scrap quantities to increase quantity.
                    // NO - scrap will require generation of a new work order. 
                    int qty = newQty ;
					
                    BatchPart prt ;
					//=================================================
					if(seqnumber == 780&&pjob->cjobdrVec[i].taskET == "IC")
					{
						int test = 0;
					}

					if((ReWork >0||Scrap>0)&&(seqnumber == 780||seqnumber == 790)&&pjob->cjobdrVec[i].taskET != "IC")
						continue;
					CS_strmaxcpy(prt.partnum, pjob->partname.c_str(), 20) ; 
					
					prt.qtygood = qty ; 
					prt.qtyscrap = 0.0 ; 
					CS_strmaxcpy(prt.units, "EA", 4) ; 
					prt.reason[0] = 0 ; 
					CS_strmaxcpy(prt.empdept, pjob->cjobdrVec[i].dept.c_str(), 2) ;
					prt.empnum = 99999 ; 
					prt.chargedept[0] = 0 ; 
					prt.chargeresc[0] = 0 ; 
					prt.lotnum[0] = 0 ; 
					prt.stamplot = ' ' ; 
					prt.createserial = ' ' ; 
					prt.outlib[0] = 0 ; 
					prt.queuename[0] = 0 ; 
					prt.usr1[0] = 0 ; 
					prt.usr2[0] = 0 ; 
					prt.usr3[0] = 0 ; 
					prt.voidser = 0.0 ; 
					prt.prodser[0] = 0 ; 
                    
					if (pjob->cjobdrVec[i].seqno == 100 || 
						(i > 0 && pjob->cjobdrVec[i-1].bTrackCAMmtl))
					{
						prt.nobackflush = 'Y' ; 
					}
					else
					{
						prt.nobackflush = 'N' ; 
					}

					prt.scanid[0] = 0 ; 

					len = prt.SetString(tmpstr); 
					fwrite(tmpstr, 1, len, fp) ;
					fflush(fp) ; 
					
					if(pjob->cjobdrVec[i].prevScrapCount >0)
					{
						if((qty > 0&&pjob->cjobdrVec[i].qtydone < pjob->cjobdrVec[i].prevScrapCount+1)&& pjob->cjobdrVec[i].prevScrapCount >0&&pjob->cjobdrVec[i].serialnum)
						{
							BatchMaterial mtl ; 
							CS_strmaxcpy(mtl.matpart, pjob->cjobdrVec[i].material.c_str(), 20) ; 
							CS_strmaxcpy(mtl.stockroom, "STL", 3) ; 
							mtl.reqmode = 'R' ; 
							mtl.backflush = 'Y' ; 
							mtl.qty = pjob->cjobdrVec[i].mtlqty ; 
							CS_strmaxcpy(mtl.units, pjob->cjobdrVec[i].mtlunits.c_str(), 3) ; 
							mtl.transdate.m_nYear = 0 ; 
							mtl.seqnum[0] = 0 ; 
							mtl.lotnum[0] = 0 ; 
							mtl.sernum = 0;
							mtl.isScrap = 'N' ; 

							len = mtl.SetString(tmpstr) ; 
							fwrite(tmpstr, 1, len, fp) ; 
							fflush(fp) ; 

							if (i > 0 && pjob->cjobdrVec[i-1].seqno == 30)
							{
								BatchMaterial mtl30 ; 
								CS_strmaxcpy(mtl30.matpart, pjob->partname.c_str(), 20) ; 
								CS_strmaxcpy(mtl30.stockroom, "PRD", 3) ; 
								mtl30.reqmode = 'R' ; 
								mtl30.backflush = 'Y' ; 
								mtl30.qty = 1.0 ; 
								CS_strmaxcpy(mtl30.units, "EA", 3) ; 
								mtl30.transdate.m_nYear = 0 ; 
								CS_strmaxcpy(mtl30.seqnum, "030", 3) ; 
								mtl30.lotnum[0] = 0 ; 
								mtl30.sernum = 0 ; 
								mtl30.isScrap = 'N' ; 

								len = mtl30.SetString(tmpstr) ; 
								fwrite(tmpstr, 1, len, fp) ; 
								fflush(fp) ; 
							}
						}
						else if (pjob->cjobdrVec[i].bTrackCAMmtl)
						{   // Track material for a CAM operation
							BatchMaterial mtl ; 
							CS_strmaxcpy(mtl.matpart, pjob->partname.c_str(), 20) ; 
							CS_strmaxcpy(mtl.stockroom, "PRD", 3) ; 
							mtl.reqmode = 'R' ; 
							mtl.backflush = 'Y' ; 
							mtl.qty = 1.0 ; 
							CS_strmaxcpy(mtl.units, "EA", 3) ; 
							mtl.transdate.m_nYear = 0 ; 
							CS_strmaxcpy(mtl.seqnum, "030", 3) ; 
							mtl.lotnum[0] = 0 ; 
							mtl.sernum = 0;
							mtl.isScrap = 'N' ; 

							len = mtl.SetString(tmpstr) ; 
							fwrite(tmpstr, 1, len, fp) ; 
							fflush(fp) ; 
						}
					}
					else
					{
						if (pjob->cjobdrVec[i].serialnum && qty == 1 && pjob->cjobdrVec[i].prevScrapCount == 0 )
						{   // This is a saw entry with material consumption data
							BatchMaterial mtl ; 
							CS_strmaxcpy(mtl.matpart, pjob->cjobdrVec[i].material.c_str(), 20) ; 
							CS_strmaxcpy(mtl.stockroom, "STL", 3) ; 
							mtl.reqmode = 'R' ; 
							mtl.backflush = 'Y' ; 
							mtl.qty = pjob->cjobdrVec[i].mtlqty ; 
							CS_strmaxcpy(mtl.units, pjob->cjobdrVec[i].mtlunits.c_str(), 3) ; 
							mtl.transdate.m_nYear = 0 ; 
							mtl.seqnum[0] = 0 ; 
							mtl.lotnum[0] = 0 ; 
							mtl.sernum = 0;
							mtl.isScrap = 'N' ; 

							len = mtl.SetString(tmpstr) ; 
							fwrite(tmpstr, 1, len, fp) ; 
							fflush(fp) ; 

							if (i > 0 && pjob->cjobdrVec[i-1].seqno == 30)
							{
								BatchMaterial mtl30 ; 
								CS_strmaxcpy(mtl30.matpart, pjob->partname.c_str(), 20) ; 
								CS_strmaxcpy(mtl30.stockroom, "PRD", 3) ; 
								mtl30.reqmode = 'R' ; 
								mtl30.backflush = 'Y' ; 
								mtl30.qty = 1.0 ; 
								CS_strmaxcpy(mtl30.units, "EA", 3) ; 
								mtl30.transdate.m_nYear = 0 ; 
								CS_strmaxcpy(mtl30.seqnum, "030", 3) ; 
								mtl30.lotnum[0] = 0 ; 
								mtl30.sernum = 0 ; 
								mtl30.isScrap = 'N' ; 

								len = mtl30.SetString(tmpstr) ; 
								fwrite(tmpstr, 1, len, fp) ; 
								fflush(fp) ; 
							}
						}
						else if (pjob->cjobdrVec[i].bTrackCAMmtl)
						{   // Track material for a CAM operation
							BatchMaterial mtl ; 
							CS_strmaxcpy(mtl.matpart, pjob->partname.c_str(), 20) ; 
							CS_strmaxcpy(mtl.stockroom, "PRD", 3) ; 
							mtl.reqmode = 'R' ; 
							mtl.backflush = 'Y' ; 
							mtl.qty = 1.0 ; 
							CS_strmaxcpy(mtl.units, "EA", 3) ; 
							mtl.transdate.m_nYear = 0 ; 
							CS_strmaxcpy(mtl.seqnum, "030", 3) ; 
							mtl.lotnum[0] = 0 ; 
							mtl.sernum = 0;
							mtl.isScrap = 'N' ; 

							len = mtl.SetString(tmpstr) ; 
							fwrite(tmpstr, 1, len, fp) ; 
							fflush(fp) ; 
						}
					}
                }
            }
        }
    }


    // Output all the turned blank type records. 
	
    if (bkvec.size())
    {
        // Then this is a new resource so output the header record
        csString prevRes ; 

        for (int i=0; i < (int)bkvec.size(); i++)
        {
            if (prevRes != bkvec[i].res)
            {
                len = hdr.SetString(tmpstr) ; 
                fwrite(tmpstr, 1, len, fp) ; 
                fflush(fp) ; 

                prevRes = bkvec[i].res ; 
            }


            BatchDetail dtl ;

            // UPDATE TO INCLUDE PART QUANTITIES ;

            dtl.dept[0] = gCMSparms.plantID[0] ; 
            dtl.dept[1] = gCMSparms.plantID[1] ; 
            dtl.dept[2] = gCMSparms.plantID[2] ; 
            CS_strmaxcpy(dtl.dept,      bkvec[i].dept.c_str(), 5) ;
            CS_strmaxcpy(dtl.resource,  bkvec[i].res.c_str(),  8) ;
            CS_strmaxcpy(dtl.part,      bkvec[i].part.c_str(), 20) ; 
            sprintf(dtl.seqnum, "%03d", bkvec[i].seqnum) ;
            CS_strmaxcpy(dtl.indcode,   " ", 4) ;
            dtl.machtime = 10 ; 
            dtl.orderNum[0] = 0 ; 
            dtl.nummen  = '1' ; 
            dtl.nummach = '1' ; 
            dtl.dbldig = 'N' ; 
            dtl.nMen2 = 0 ; 
            dtl.nMach2 = 0 ; 

            len = dtl.SetString(tmpstr) ; 
            fwrite(tmpstr, 1, len, fp) ; 
            fflush(fp) ; 
            
            BatchPart bprt ;
            
            CS_strmaxcpy(bprt.partnum,   bkvec[i].part.c_str(), 20) ; 
            if (bkvec[i].pickRec)
            {
                bprt.qtygood = 1 ; 
            }
            else
            {
                bprt.qtygood = (int)bkvec[i].qty ; 
            }
            bprt.qtyscrap = 0.0 ; 
            CS_strmaxcpy(bprt.units, "EA", 4) ; 
            bprt.reason[0] = 0 ; 
            CS_strmaxcpy(bprt.empdept, bkvec[i].dept.str + 3, 2) ;
            bprt.empnum = 99999 ; // bkvec[i].empnum ; 
            bprt.chargedept[0] = 0 ; 
            bprt.chargeresc[0] = 0 ; 

            sprintf(tmpstr, "%d", bkvec[i].serial) ; 
            CS_strmaxcpy(bprt.lotnum, tmpstr, 18) ; 

            bprt.stamplot = ' ' ; 
            bprt.createserial = ' ' ; 
            bprt.outlib[0] = 0 ; 
            bprt.queuename[0] = 0 ; 
            bprt.usr1[0] = 0 ; 
            bprt.usr2[0] = 0 ; 
            bprt.usr3[0] = 0 ; 
            bprt.voidser = 0.0 ; 
            bprt.prodser[0] = 0 ; 

            if (bkvec[i].seqnum == 100)
                bprt.nobackflush = 'Y' ; 
            else
                bprt.nobackflush = 'N' ; 

            bprt.scanid[0] = 0 ; 

            len = bprt.SetString(tmpstr); 
            fwrite(tmpstr, 1, len, fp) ; 
            fflush(fp) ; 

            // Material Record 

            BatchMaterial mtl ; 
            CS_strmaxcpy(mtl.matpart,   bkvec[i].mtl.c_str(), 20) ; 
            CS_strmaxcpy(mtl.stockroom, "STL", 3) ; 
            mtl.reqmode = 'R' ; 
            mtl.backflush = 'Y' ; 
            mtl.qty = atof(bkvec[i].mtlqty.c_str()) ; 
            CS_strmaxcpy(mtl.units, bkvec[i].mtlunit.c_str(), 3) ; 
            mtl.transdate.m_nYear = 0 ; 
            mtl.seqnum[0] = 0 ; 
            if (bkvec[i].pickRec)
            {
                sprintf(mtl.lotnum, "%d", bkvec[i].serial) ; 
                mtl.sernum = 0 ; 
            }
            else
            {
                mtl.lotnum[0] = 0 ; 
				mtl.sernum = 0 ;
            }
            mtl.isScrap = 'N' ; 

            len = mtl.SetString(tmpstr) ; 
            fwrite(tmpstr, 1, len, fp) ; 
            fflush(fp) ; 
        }
    }

    fclose(fp) ; 

    if (AfxMessageBox("Select YES to run batch flat file command", MB_YESNO) ==  IDYES)
    {
        csString path, basename ; 
        SplitPathAndFile(csString(gCMSparms.batchDir), path, basename) ; 
        
        if (!CS_DirExists(path.c_str())) 
        {
            _snprintf(tmpstr, 500, 
                "The directory:\r\n'  %s'\r\ndoes not exist. Check the C:\\CMS\\cmscfg.ini file",
                    gCMSparms.batchDir) ; 
            AfxMessageBox(tmpstr, MB_ICONEXCLAMATION) ; 
        }


        int attempts = 0 ; 
        int failed = 0 ; 
        while (!CopyFile(tmpbatch, batchName, FALSE))
        {
            if (++attempts > 5)
            {
                failed = 1 ;
                break ; 
            }

            Sleep(500) ; 
            FILE *fp = fopen(batchName, "rt") ; 
            if (fp)
            {
                fclose(fp) ; 
                break ; 
            }
        }

        if (!failed)
        {
            csString batchPath(batchName) ; 
            csString bchDir, bchName ; 
            SplitPathAndFile(batchPath, bchDir, bchName) ; 
            if (bchDir.Right(1) == "\\") 
                bchDir.TrimRight(1) ; 
            int i = bchDir.FindLastIDX("\\") ; 
            csString bdir ; 
            bdir = bchDir.Mid(i+1) ; 
            csString cmd(1024) ; 
            _snprintf(cmd.str, 1000, "PD818CMD %s %s %s 2 1 BERR.TXT 1 2",
                        gCMSparms.plantID, bdir.c_str(), bchName.c_str()) ;

            SaveUpdateArcFlag() ; 

            if (!IBM_RunCommand(cmd))
            {   // Success update the status of all processed task records

                // Need to check for ERR file in Q:\BATCH before processing the ARC
                // flags update. 
                UpdateArcFlag() ; 
            }
        }
        else
        {
            SaveUpdateArcFlag() ; 

            char msg[2048] ; 
            _snprintf(msg, 2000, "Failed to copy:\r\n%s\r\n         to:\r\n%s", 
                            tmpbatch, batchName) ; 
            AfxMessageBox(msg, MB_ICONEXCLAMATION) ;
            retcode |= 0x01 ; // error 
        }
    }
    else
    {
        SaveUpdateArcFlag() ; 

        retcode |= 0x02 ; 
    }

    return retcode ; 
}




int CBatchUPDDlg::UpdateArcFlag() 
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    char qry[256] ; 
    char tmpstr[128] ; 

    ResRecMapItr irrm ;
    for (irrm = resmap.begin(); irrm != resmap.end(); irrm++)
    {
        ResRec *pres = &(irrm->second) ; 
        for (unsigned int i=0; i < pres->evvec.size(); i++)
        {
            if (pres->evvec[i].setArcState != 0)
            {   // Then set this record. 

                int retry = 0 ; 
                while (retry++ < 5)
                {
                    sprintf(qry, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
                        " PLANT='%s' AND SONUM='%d' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                        " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='EVT'", 
                        gCMSparms.dbname, pres->evvec[i].setArcState, 
                        gCMSparms.plantID, 
                        pres->evvec[i].ordnum, 
                        pres->evvec[i].empnum, 
                        pres->evvec[i].part.c_str(), 
                        pres->evvec[i].task.c_str(), 
                        pres->evvec[i].dt.FormatDateTimeSecs(tmpstr), 
                        pres->evvec[i].station.c_str()) ; 

                    try {
                        CSQLRecordset rs(pApp->cmsdata.m_db) ;
                        rs << qry ; 
                        rs.SQLExec();
                        break ; // exit retry loop if successful
                    }
                    catch (CSQLException* e)
                    {
                        if (gCMSparms.pevp->fpLOG)
                        {
                            fprintf(gCMSparms.pevp->fpLOG, 
                                "SQL error %d updating task ARC flag for:\r\n"
                                "      QRY='%s'\r\n"
                                "      Error: '%s'\r\n",
                                        (int)e->m_nRetCode, qry,  e->m_strError.c_str()) ;

                            fflush(gCMSparms.pevp->fpLOG) ; 
                        }
                    }

                    Sleep(100) ; 
                }
            }
        }
    }



    for (size_t i=0; i < processedTasks.size(); i++)
    {
        if (processedTasks[i].setArcState != 0)
        {   // Then set this record. 

            int retry = 0 ; 
            while (retry++ < 5)
            {
                sprintf(qry, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
                    " PLANT='%s' AND SONUM='%d' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                    " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='%s'", 
                    gCMSparms.dbname, 
                    processedTasks[i].setArcState, 
                    gCMSparms.plantID, 
                    processedTasks[i].ordnum, 
                    processedTasks[i].empnum, 
                    processedTasks[i].part.c_str(), 
                    processedTasks[i].task.c_str(), 
                    processedTasks[i].dt.FormatDateTimeSecs(tmpstr), 
                    processedTasks[i].station.c_str(),
                    processedTasks[i].rtype.c_str()) ; 

                try {
                    CSQLRecordset rs(pApp->cmsdata.m_db) ;
                    rs << qry ; 
                    rs.SQLExec();
                    break ; // exit retry loop if successful
                }
                catch (CSQLException* e)
                {
                    if (gCMSparms.pevp->fpLOG)
                    {
                        fprintf(gCMSparms.pevp->fpLOG, 
                            "SQL error %d updating task ARC flag for:\r\n"
                            "      QRY='%s'\r\n"
                            "      Error: '%s'\r\n",
                                    (int)e->m_nRetCode, qry,  e->m_strError.c_str()) ;

                        fflush(gCMSparms.pevp->fpLOG) ; 
                    }
                }
                Sleep(100) ; 
            }
        }
    }

    for (int i=0; i < (int)bkvec.size(); i++)
    {
        int retry = 0 ; 
        while (retry++ < 5)
        {
            if (bkvec[i].pickRec)
            {   // PPT record
                sprintf(qry, "UPDATE %s.EXCOTASK SET ARC='Y' WHERE"
                    " PLANT='%s' AND SONUM='%s' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                    " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='PPT'",
                    gCMSparms.dbname, 
                    gCMSparms.plantID,
                    bkvec[i].sonum.c_str(),
                    bkvec[i].empnum,
                    bkvec[i].prtcode.c_str(), 
                    bkvec[i].taskcode.c_str(), 
                    bkvec[i].tasktime.c_str(), 
                    bkvec[i].station.c_str()) ;
            }
            else
            {   // This is a TBL record

                sprintf(qry, "UPDATE %s.EXCOTASK SET ARC='Y' WHERE"
                    " PLANT='%s' AND SONUM='%s' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                    " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='TBL'",
                    gCMSparms.dbname, 
                    gCMSparms.plantID,
                    bkvec[i].sonum.c_str(),
                    bkvec[i].empnum,
                    bkvec[i].prtcode.c_str(), 
                    bkvec[i].taskcode.c_str(), 
                    bkvec[i].tasktime.c_str(), 
                    bkvec[i].station.c_str()) ;
            }

            try {
                CSQLRecordset rs(pApp->cmsdata.m_db) ;
                rs << qry ; 
                rs.SQLExec();
                break ; // exit retry loop if successful
            }
            catch (CSQLException* e)
            {
                if (gCMSparms.pevp->fpLOG)
                {
                    fprintf(gCMSparms.pevp->fpLOG, 
                        "SQL error %d updating task ARC flag for:\r\n"
                        "      QRY='%s'\r\n"
                        "      Error: '%s'\r\n",
                                (int)e->m_nRetCode, qry,  e->m_strError.c_str()) ;

                    fflush(gCMSparms.pevp->fpLOG) ; 
                }
            }
            Sleep(100) ; 
        }
    }

    return 0 ; 
}


int CBatchUPDDlg::SaveUpdateArcFlag() 
{
    CBatchUPDApp *pApp = (CBatchUPDApp *)AfxGetApp() ; 
    char tmpstr[128] ;

    CDateTime dt ;
    dt.SetNow() ; 
    dt.FormatDateTimeSecs(tmpstr, 1) ; 
    csString sqlfile ; 
    sqlfile = "C:\\CMS\\SQL_TASKARC_" ; 
    sqlfile += tmpstr ; 
    sqlfile += ".txt" ; 

    FILE *fp = fopen(sqlfile.c_str(), "wt") ; 

    ResRecMapItr irrm ;
    for (irrm = resmap.begin(); irrm != resmap.end(); irrm++)
    {
        ResRec *pres = &(irrm->second) ; 
        for (unsigned int i=0; i < pres->evvec.size(); i++)
        {
            if (pres->evvec[i].setArcState != 0)
            {   // Then set this record. 

                fprintf(fp, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
                    " PLANT='%s' AND SONUM='%d' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                    " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='EVT' ;\n", 
                    gCMSparms.dbname, pres->evvec[i].setArcState, 
                    gCMSparms.plantID, 
                    pres->evvec[i].ordnum, 
                    pres->evvec[i].empnum, 
                    pres->evvec[i].part.c_str(), 
                    pres->evvec[i].task.c_str(), 
                    pres->evvec[i].dt.FormatDateTimeSecs(tmpstr), 
                    pres->evvec[i].station.c_str()) ; 
                fflush(fp) ; 
            }
        }
    }


    for (size_t i=0; i < processedTasks.size(); i++)
    {
        if (processedTasks[i].setArcState != 0)
        {   // Then set this record. 

            fprintf(fp, "UPDATE %s.EXCOTASK SET ARC='%c' WHERE"
                " PLANT='%s' AND SONUM='%d' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='%s' ;\n", 
                gCMSparms.dbname, 
                processedTasks[i].setArcState, 
                gCMSparms.plantID, 
                processedTasks[i].ordnum, 
                processedTasks[i].empnum, 
                processedTasks[i].part.c_str(), 
                processedTasks[i].task.c_str(), 
                processedTasks[i].dt.FormatDateTimeSecs(tmpstr), 
                processedTasks[i].station.c_str(),
                processedTasks[i].rtype.c_str()) ; 
            fflush(fp) ; 
        }
    }

    for (int i=0; i < (int)bkvec.size(); i++)
    {
        if (bkvec[i].pickRec)
        {
            fprintf(fp, "UPDATE %s.EXCOTASK SET ARC='Y' WHERE"
                " PLANT='%s' AND SONUM='%s' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='PPT' ;\n",
                gCMSparms.dbname, 
                gCMSparms.plantID,
                bkvec[i].sonum.c_str(),
                bkvec[i].empnum,
                bkvec[i].prtcode.c_str(), 
                bkvec[i].taskcode.c_str(), 
                bkvec[i].tasktime.c_str(), 
                bkvec[i].station.c_str()) ;
        }
        else
        {
            fprintf(fp, "UPDATE %s.EXCOTASK SET ARC='Y' WHERE"
                " PLANT='%s' AND SONUM='%s' AND EMPNUM='%d' AND PRTCODE='%s' AND"
                " TASK='%s' AND TASKTIME='%s' AND STATION='%s' AND RTYPE='TBL' ;\n",
                gCMSparms.dbname, 
                gCMSparms.plantID,
                bkvec[i].sonum.c_str(),
                bkvec[i].empnum,
                bkvec[i].prtcode.c_str(), 
                bkvec[i].taskcode.c_str(), 
                bkvec[i].tasktime.c_str(), 
                bkvec[i].station.c_str()) ;
        }
        fflush(fp) ; 
    }


    fclose(fp) ; 
    return 0 ; 
}

BEGIN_EVENTSINK_MAP(CBatchUPDDlg, CDialog)
ON_EVENT(CBatchUPDDlg, IDC_MSFLEXGRID1, DISPID_DBLCLICK, DblClickMsflexgrid1, VTS_NONE)
END_EVENTSINK_MAP()

void CBatchUPDDlg::DblClickMsflexgrid1()
{

    long r = m_grid.get_Row() ;     
    CString csCombine = m_grid.get_TextMatrix(r, 0);

    char input[1024];
    CS_strmaxcpy(input, (LPCTSTR)csCombine, 1000);
    char splitString[16][256];
    int nflds = Split(input, ";", splitString);

}

void CBatchUPDDlg::OnBnClickedButtonStart()
{	
    UpdateData(TRUE) ; 
    AfxBeginThread(LoadInitialData, this); 
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
}