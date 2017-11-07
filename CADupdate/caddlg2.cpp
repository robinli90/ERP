#include "stdafx.h"
#include <afxdb.h>

/* ---------------------------------------------------------------
There are 4 things that can change from the original 
data set. 
1 - part can be added or deleted
2 - the part thickness could change
3 - the part diameter could change
4 - the steel type could change. 


For part additions and deletions there is no updating
to worry about, simply create the add or delete record
and your done. 

If the diameter changes, then the material type has 
to be updated. If the thickness changes, then the 
part quantity must be modified. This can be done at the
same time as a material change if required. 

If the steel changes, then this is treated the same
as a material type change, thus a steel type change
or a diameter change are treated exactly the same way. 

Thus the there are 3 cases
1 - ADD RECORD
2 - DELETE RECORD
3 - CHANGE RECORD

Must go through all the dialog values and see which
case we fall into and then output the required data. 

To do this simply save all the updated data in the 
activeOrder[0] record and then call the output prcessing. 
--------------------------------------------------------------- */


void CCADupdateDlg::ClickOK()
{
	
	INT_PTR nResponse = DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}
void CCADupdateDlg::OnBnClickedOk()
{
    int i = 0 ; 
	if(!Enter||errord)
		exit(1);

	// check if thickness is valid
	UpdateData(TRUE);
	if (atof(m_csFDRTHK)>19.5*25.4 || atof(m_csBKRTHK)>19.5*25.4 || atof(m_csBOLTHK)>19.5*25.4||atof(m_csMNDTHK)>19.5*25.4||atof(m_csPLTTHK)>19.5*25.4||atof(m_csRNGTHK)>19.5*25.4)
	{
        AfxMessageBox("Please check thickness data!") ; 
        return ; 	
	}


	if (UpdateOrderValues(pcms->activeOrders[0]))
		return ; // an error occured so do not exit. 

    pcms->steelStockMsg.clear() ; 
    
    CMSOrder *pord = &pcms->activeOrders[0] ; 
    if (pord)
    {
        // Bad steel type check, no steel selected error. 
        int bError = 0 ; 
        for (i=0; i < (int)pord->jobvec.size(); i++)
        {
            if (pord->jobvec[i].bIsRequired && pord->jobvec[i].steel == 0 )
            {
                bError = 1 ; 
                break ;
            }
        }

        if (bError)
        {
            AfxMessageBox(
                "You have a part with no steel type defined. All parts\r\n"
                "must have a steel type selected. If you need to delete\r\n"
                "the part, then uncheck the box to the left of the part\r\n"
                "description\r\n") ; 
            return ; 
        }
    }


    // TODO: Add your control notification handler code here
    csString destdir = pcms->szFlatFileDir ; 
    csString destname = pcms->szFlatFilePrefix ; 
    csString destord  ; 
    destord.FormatSz(32, "%06d", atoi(pcms->activeOrders[0].orderNumber.c_str())) ; 
    csString destfull = AddFile2Path(destdir, destord)  ;
    destfull += "_" + destname ; 

    CDateTime dt ; 
    dt.SetNow() ; 
    char datestr[64] ; 
    dt.FormatDateTimeSecs(datestr, 1) ; 
    destfull += "_" + csString(datestr) + ".txt" ; 
    FILE *fp = fopen(destfull.c_str(), "wb") ; 
    if (!fp)
    {
        LogToFile(gCMSparms.logfp, "ERROR: couldn't open output file '%s'\n", 
            destfull.c_str()) ;
        char msg[2048] ; 
        sprintf(msg, "Failed to write to output file\n%s\n", 
            destfull.c_str()) ; 
        AfxMessageBox(msg, MB_OK) ;
    }
    else
    {   // File opened OK so process it. 
        BeginWaitCursor() ; 

        // Adjust the steel numbers to match the steelvec[] indexes
        CMSOrder *pord = &pcms->activeOrders[0] ; 

		//////////////////////////////////////////////////
        for (i=0; i < (int)pord->jobvec.size(); i++)
        {
            pord->jobvec[i].steel -= 1 ; 
            // Also re-number all the temporary job numbers because if the user errors out
            // on a single part, duplicate numbers can occur
            // MAYBE DON'T NEED THIS
        }
		/////////////////////////////////////////////////////////

        if (pcms->ProcessFlatFile(fp, origOrder, pcms->activeOrders[0]) < 0)
        {   // Then something was out of stock
            EndWaitCursor() ; 

            if (pcms->steelStockMsg.size())
            {
                AfxMessageBox(pcms->steelStockMsg.c_str(), MB_OK) ; 
                fclose(fp) ;
                DeleteFile(destfull.c_str()) ; 
                return ; 
            }

            bool makeChanges = false ; 

            for (i=0; i < (int)pord->jobvec.size(); i++)
            {
                if (pord->jobvec[i].bOutOfStock && !pord->jobvec[i].bStockOverride)
                {
                    if (!loopMode)
                    {   // Then perform standard processing
                        char msg[2048] ; 

                        if (pord->jobvec[i].IsPartBlank())
                        {
                            _snprintf(msg, 2000, 
                                "NO BLANK FOR:  %s and %s\n"
                                "If you want to be warned about this part again select YES,\n"
                                "otherwise select NO and the system will not re-check this\n"
                                "part material the next time you click save even though it\n"
                                "is out of stock.\n\n"
                                "Please verify the part sizes and click SAVE again.", 
                                        pord->jobvec[i].partname.c_str(), pord->jobvec[i].mattype.c_str()) ; 
                        }
                        else
                        {
                            _snprintf(msg, 2000, 
                                "MATERIAL OUT OF STOCK FOR %s\n"
                                "If you want to be warned about this part again select YES,\n"
                                "otherwise select NO and the system will not re-check this\n"
                                "part material the next time you click save even though it\n"
                                "is out of stock.\n\n"
                                "Please verify the part sizes and click SAVE again.", 
                                        pord->jobvec[i].mattype.c_str()) ; 
							 /*_snprintf(msg, 2000, 
                                "MATERIAL OUT OF STOCK FOR %s\n"
                                "Please enter the next size up. For example for 15.5 please enter 16\n"
								"If you have problem please see IT for support!"
								,pord->jobvec[i].mattype.c_str()) ; 
							 AfxMessageBox(msg, MB_OK);*/
                        }

                        if (AfxMessageBox(msg, MB_YESNO) != IDYES)
                        {   // Override the out of stock condition for 
                            // this particular part. 1-0
                            pord->jobvec[i].bStockOverride = 1 ; 
                        }
						pord->jobvec[i].bStockOverride = 1 ; 
                        makeChanges = true ; 
                    }
                    else
                    {   // override standard processing and just allow job to be processed. 
                        pord->jobvec[i].bStockOverride = 1 ; 
                    }
                }
            }

            // Set the steel values back 
            for (i=0; i < (int)pord->jobvec.size(); i++)
                pord->jobvec[i].steel += 1 ; 

            if (makeChanges)
            {   // Then abort and reset. 
                fclose(fp) ;
                DeleteFile(destfull.c_str()) ; 
				if(MultiSoCAD&&SOCount>0)
				{
					//InitializeOrderList();
					//SOCount--;
					//OnDefaultButtonClicked();
					OnBnClickedOk();
				}
                return ; 
            }


            // Else continue processing
        }
        else
        {
            EndWaitCursor() ; 
        }
		 
        fclose(fp) ; 

		// output log to decade
		UpdateData(TRUE);
		SYSTEMTIME lt;
		GetLocalTime(&lt);
		char uqry[256];
		sprintf(uqry, "insert into dbo.cadupdate_log values (%s, '%04d-%02d-%02d %02d:%02d:%02d.000')", m_csSONUM, lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond) ; 
		CDatabase database;
		database.OpenEx("DSN=decade;UID=jamie;PWD=jamie");
		database.ExecuteSQL(uqry);
		database.Close();
		
		if(multiSO)
		{
			multiSO1 = true;
			ReadInput3();
			OnDefaultButtonClicked();
			if(multiSO)
				OnBnClickedOk();
			else
				goto Done;
		}

		if (!loopMode)
		{
			//if(x<2)
			//{
Done:
			AfxMessageBox("DATA FILE SAVED SUCCESSFULLY", MB_OK) ; 
			//	x=3;
			//}

			//Update CUPDATE database if it's not already exist
			if(CCADupdateDlg::CheckSoNum(m_csSONUM)<1)
				CCADupdateDlg::UpdateRecord (m_csSONUM);


			if(MultiSoCAD)
			{
				//InitializeOrderList();
				SOCount--;
				OnDefaultButtonClicked();

				//OnBnClickedOk();
			}
			if(SOCount==0)
				OnOK() ;
		}
	}
}

int CCADupdateDlg::UpdateOrderValues(CMSOrder &order)
{
	
    int i = 0 ;
	UpdateData(TRUE) ; 

    // Create a job state variable in CMSJob and then based on the 
    // condition set things so that the logic top processflat file 
    // is simpler. 
    // Initialize the processing state
    for (i=0; i < (int)order.jobvec.size(); i++)
        order.jobvec[i].processState = 0 ; 

    // ****************************************************************
    // *********************    FEEDER     ****************************
    // ****************************************************************

    if (order.jobFDR())
    {   
        if (m_bFDR)
        {   // Then doing an update, maybe.
            order.bHasFDR = true ; 
            if (CompEQ(atof((LPCTSTR)m_csFDRTHK), 0))
            {
                AfxMessageBox("If you are using a FEEDER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{

					//AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					//exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mFDRTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mFDRHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 

			if ((order.jobFDR()->statFlags != newStat) || 
				(order.jobFDR()->steel != m_comboFDRSTEEL.GetCurSel()) ||
				!CompEQ(order.jobFDR()->diam, atof((LPCTSTR)m_csFDRDIA)) ||
				!CompEQ(order.jobFDR()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csFDRTHK))))
			{   // Then something has changed

				order.jobFDR()->processState = STATE_UPDATE ; 
				order.jobFDR()->diam = atof((LPCTSTR)m_csFDRDIA) ; 
				order.jobFDR()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csFDRTHK)) ; 
				order.jobFDR()->steel = m_comboFDRSTEEL.GetCurSel() ;
				order.jobFDR()->statFlags = newStat ; 


			}
			CString prt = "FE";
			CString steel = CCADupdateDlg::SteelType(order.jobFDR()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}
        }
        else
        {   // Then delete the part. 
            order.bHasFDR = false ; 
            order.jobFDR()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bFDR)
    {   // Then have to add a feeder since one didn't exist before. 
        if (CompEQ(atof((LPCTSTR)m_csFDRTHK), 0))
        {
            AfxMessageBox("If you are using a FEEDER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
			{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
			}
			return -1 ; 
        }


        order.bHasFDR = true ; 
        CMSJob newpart ;
        newpart.partcode = FEEDER_PARTCODE ; 
		newpart.steel = m_comboFDRSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csFDRDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csFDRTHK)) ; 
        newpart.processState = STATE_ADD ; 

        SetStatFlags((mFDRTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mFDRHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 

        int idx = -1 ; 
        if (pcms->FindPart("FDR", "", newpart.diam, 
                            newpart.length, newpart.partname)) 
        {
            char *msg = 0 ;
            idx = order.AppendJob(newpart, &msg) ; 
            if (msg)
                AfxMessageBox(msg, MB_OK) ; 
        }
        else
        {
            AfxMessageBox("No standard part exists for the FEEDER\r\n"
                "dimensions specified in the master parts list. There must\r\n"
                "be a valid part defined in Solarsoft before you can add\r\n"
                "the part. Please check the dimensions, and if correct\r\n"
                "report the problem to sales.", MB_OK) ; 
            return -1 ; 
        }

    }

    // ****************************************************************
    // *********************    MANDREL    ****************************
    // ****************************************************************
    if (order.jobMND())
    {   
        if (m_bMND)
        {   // Then doing an update, maybe.
            order.bHasMND = true ; 

            if (CompEQ(atof((LPCTSTR)m_csMNDTHK), 0))
            {
                AfxMessageBox("If you are using a MANDREL, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mMNDTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mMNDHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 

			if ((order.jobMND()->statFlags != newStat) ||
				(order.jobMND()->steel != m_comboMNDSTEEL.GetCurSel()) ||
				!CompEQ(order.jobMND()->diam, atof((LPCTSTR)m_csMNDDIA)) ||
				!CompEQ(order.jobMND()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csMNDTHK)+10.0/25.4)))
			{   // Then something has changed
				order.jobMND()->processState = STATE_UPDATE ; 

				order.jobMND()->diam = atof((LPCTSTR)m_csMNDDIA) ; 
				order.jobMND()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csMNDTHK)) +10.0/25.4; 
				order.jobMND()->steel = m_comboMNDSTEEL.GetCurSel() ;
				order.jobMND()->statFlags = newStat ; 
			}
			CString prt = "MN";
			CString steel = CCADupdateDlg::SteelType(order.jobMND()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}
        }
        else
        {   // Then delete the part. 
            order.bHasMND = false ; 
            order.jobMND()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bMND)
    {   // Then have to add one since none existed before. 
        order.bHasMND = true ; 

        if (CompEQ(atof((LPCTSTR)m_csMNDTHK), 0))
        {
            AfxMessageBox("If you are using a MANDREL, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
           if(multiSO1)
		   {
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
		   }
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = MANDREL_PARTCODE ; 
		newpart.steel = m_comboMNDSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csMNDDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csMNDTHK)) +10.0; 
        double thk = newpart.length ; 
        SetStatFlags((mMNDTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mMNDHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 
        newpart.processState = STATE_ADD ; 
        int idx = -1 ; 
        if (pcms->FindPart("HD", "MANDREL", newpart.diam, thk, newpart.partname)) 
        {
            char *msg = 0 ;
            idx = order.AppendJob(newpart, &msg) ; 
            if (msg)
                AfxMessageBox(msg, MB_OK) ;
        }
        else
        {
            AfxMessageBox("No standard part exists for the MANDREL\r\n"
                "dimensions specified in the master parts list. There must\r\n"
                "be a valid part defined in Solarsoft before you can add\r\n"
                "the part. Please check the dimensions, and if correct\r\n"
                "report the problem to sales.", MB_OK) ; 
            return -1 ; 
        }
    }

    // ****************************************************************
    // *********************    PLATE      ****************************
    // ****************************************************************
    if (order.jobPLT())
    {   
        if (m_bPLT)
        {   // Then doing an update, maybe.
            order.bHasPLT = true ; 
            if (CompEQ(atof((LPCTSTR)m_csPLTTHK), 0))
            {
                AfxMessageBox("If you are using a PLATE, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
               if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mPLTTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mPLTHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 
			if (m_bMND)
			{
				if ((order.jobPLT()->statFlags != newStat) ||
					(order.jobPLT()->steel != m_comboPLTSTEEL.GetCurSel()) ||
					!CompEQ(order.jobPLT()->diam, atof((LPCTSTR)m_csPLTDIA)) ||
					!CompEQ(order.jobPLT()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csPLTTHK)+10.0/25.4)))
				{   // Then something has changed
					order.jobPLT()->processState = STATE_UPDATE ; 

					order.jobPLT()->diam = atof((LPCTSTR)m_csPLTDIA) ; 
					order.jobPLT()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csPLTTHK)) +10.0/25.4; 
					order.jobPLT()->steel = m_comboPLTSTEEL.GetCurSel() ;
					order.jobPLT()->statFlags = newStat ; 
				}
			} else
			{
				if ((order.jobPLT()->statFlags != newStat) ||
					(order.jobPLT()->steel != m_comboPLTSTEEL.GetCurSel()) ||
					!CompEQ(order.jobPLT()->diam, atof((LPCTSTR)m_csPLTDIA)) ||
					!CompEQ(order.jobPLT()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csPLTTHK))))
				{   // Then something has changed
					order.jobPLT()->processState = STATE_UPDATE ; 

					order.jobPLT()->diam = atof((LPCTSTR)m_csPLTDIA) ; 
					order.jobPLT()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csPLTTHK)); 
					order.jobPLT()->steel = m_comboPLTSTEEL.GetCurSel() ;
					order.jobPLT()->statFlags = newStat ; 
				}
			}
			CString prt = "PL";
			CString steel = CCADupdateDlg::SteelType(order.jobPLT()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}				
        }
        else
        {   // Then delete the part. 
            order.bHasPLT = false ; 
            order.jobPLT()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bPLT)
    {   // Then have to add one since none existed before. 
        order.bHasPLT = true ; 

        if (CompEQ(atof((LPCTSTR)m_csPLTTHK), 0))
        {
            AfxMessageBox("If you are using a PLATE, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = PLATE_PARTCODE ; 
		newpart.steel = m_comboPLTSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csPLTDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csPLTTHK))+10.0 ; 
        double thk = newpart.length ; 
        newpart.processState = STATE_ADD ; 
        SetStatFlags((mPLTTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mPLTHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 
        int idx = -1 ; 

        bool errOnAdd = false ;
        if (order.bHollowDie)
        {
            if (pcms->FindPart("HD", "PLATE", newpart.diam, thk, newpart.partname)) 
            {
                char *msg = 0 ;
                idx = order.AppendJob(newpart, &msg) ; 
                if (msg)
                    AfxMessageBox(msg, MB_OK) ;  
            }
            else
                errOnAdd = true ; 
        }
        else
        {
            if (pcms->FindPart("SD", "", newpart.diam, thk, newpart.partname)) 
            {
                char *msg = 0 ;
                idx = order.AppendJob(newpart, &msg) ; 
                if (msg)
                    AfxMessageBox(msg, MB_OK) ; 
            }
            else
                errOnAdd = true ; 
        }

        if (errOnAdd)
        {
            AfxMessageBox("No standard part exists for the PLATE\r\n"
                "dimensions specified in the master parts list. There must\r\n"
                "be a valid part defined in Solarsoft before you can add\r\n"
                "the part. Please check the dimensions, and if correct\r\n"
                "report the problem to sales.", MB_OK) ; 
            return -1 ; 
        }
    }

    // ****************************************************************
    // *********************    BACKER     ****************************
    // ****************************************************************
    if (order.jobBKR())
    {
        if (m_bBKR)
        {   // Then doing an update, maybe.
            order.bHasBKR = true ; 

            if (CompEQ(atof((LPCTSTR)m_csBKRTHK), 0))
            {
                AfxMessageBox("If you are using a BACKER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{
					//ClickOK();
					AfxMessageBox("The process has been errored out! Mannually run CadUpdate. See your IT for support!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mBKRTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mBKRHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 

			if (m_bMND)
			{
				if ((order.jobBKR()->statFlags != newStat) ||
					(order.jobBKR()->steel != m_comboBKRSTEEL.GetCurSel()) ||
					!CompEQ(order.jobBKR()->diam, atof((LPCTSTR)m_csBKRDIA)) ||
					!CompEQ(order.jobBKR()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csBKRTHK)+10.0/25.4)))
				{   // Then something has changed
					order.jobBKR()->processState = STATE_UPDATE ; 
					order.jobBKR()->diam = atof((LPCTSTR)m_csBKRDIA) ; 
					order.jobBKR()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csBKRTHK)) +10.0/25.4; 
					order.jobBKR()->steel = m_comboBKRSTEEL.GetCurSel() ;
					order.jobBKR()->statFlags = newStat ; 
				}
			} else
			{
				if ((order.jobBKR()->statFlags != newStat) ||
					(order.jobBKR()->steel != m_comboBKRSTEEL.GetCurSel()) ||
					!CompEQ(order.jobBKR()->diam, atof((LPCTSTR)m_csBKRDIA)) ||
					!CompEQ(order.jobBKR()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csBKRTHK))))
				{   // Then something has changed
					order.jobBKR()->processState = STATE_UPDATE ; 
					order.jobBKR()->diam = atof((LPCTSTR)m_csBKRDIA) ; 
					order.jobBKR()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csBKRTHK)); 
					order.jobBKR()->steel = m_comboBKRSTEEL.GetCurSel() ;
					order.jobBKR()->statFlags = newStat ; 
				}
			}
			CString prt = "BA";
			CString steel = CCADupdateDlg::SteelType(order.jobBKR()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}
        }
        else
        {   // Then delete the part. 
            order.bHasBKR = false ; 
            order.jobBKR()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bBKR)
    {   // Then have to add one since none existed before. 
        order.bHasBKR = true ; 

        if (CompEQ(atof((LPCTSTR)m_csBKRTHK), 0))
        {
            AfxMessageBox("If you are using a BACKER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = BACKER_PARTCODE ; 
		newpart.steel = m_comboBKRSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csBKRDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csBKRTHK)) +10.0/25.4; 
        double thk = newpart.length ; 
        newpart.processState = STATE_ADD ; 
        SetStatFlags((mBKRTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mBKRHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 
        int idx = -1 ; 

        if (order.bHollowDie)
        {
            if (pcms->FindPart("HD", "BACKER", newpart.diam, thk, newpart.partname)) 
                idx = order.AppendJob(newpart) ; 
        }
        else
        {
            bool errOnAdd = false ;
            if (newpart.steel == STEEL_H13)
            {
                if (pcms->FindPart("BAH", "", newpart.diam, thk, newpart.partname)) 
                {
                    char *msg = 0 ;
                    idx = order.AppendJob(newpart, &msg) ; 
                    if (msg)
                        AfxMessageBox(msg, MB_OK) ; 
                }
                else
                    errOnAdd = true ; 
            }
            else
            {
                if (pcms->FindPart("BA2", "", newpart.diam, thk, newpart.partname)) 
                {
                    char *msg = 0 ;
                    idx = order.AppendJob(newpart, &msg) ; 
                    if (msg)
                        AfxMessageBox(msg, MB_OK) ; 
                }
                else
                    errOnAdd = true ; 
            }
            
            if (errOnAdd)
            {
                AfxMessageBox("No standard part exists for the BACKER\r\n"
                    "dimensions specified in the master parts list. There must\r\n"
                    "be a valid part defined in Solarsoft before you can add\r\n"
                    "the part. Please check the dimensions, and if correct\r\n"
                    "report the problem to sales.", MB_OK) ; 
                return -1 ; 
            }
        }
    }

    // ****************************************************************
    // *********************    BOLSTER    ****************************
    // ****************************************************************

    if (order.jobBOL())
    {   
        if (m_bBOL)
        {   // Then doing an update, maybe.
            order.bHasBOL = true ; 

            if (CompEQ(atof((LPCTSTR)m_csBOLTHK), 0))
            {
                AfxMessageBox("If you are using a BOLSTER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mBOLTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mBOLHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 

			if ((order.jobBOL()->statFlags != newStat) ||
				(order.jobBOL()->steel != m_comboBOLSTEEL.GetCurSel()) ||
				!CompEQ(order.jobBOL()->diam, atof((LPCTSTR)m_csBOLDIA)) ||
				!CompEQ(order.jobBOL()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csBOLTHK))))
			{   // Then something has changed
				order.jobBOL()->processState = STATE_UPDATE ; 
				order.jobBOL()->diam = atof((LPCTSTR)m_csBOLDIA) ; 
				order.jobBOL()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csBOLTHK)) ; 
				order.jobBOL()->steel = m_comboBOLSTEEL.GetCurSel() ;
				order.jobBOL()->statFlags = newStat ; 
			}
			CString prt = "BO";
			CString steel = CCADupdateDlg::SteelType(order.jobBOL()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}			
        }
        else
        {   // Then delete the part. 
            order.bHasBOL = false ; 
            order.jobBOL()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bBOL)
    {   // Then have to add one since none existed before. 
        order.bHasBOL = true ; 

        if (CompEQ(atof((LPCTSTR)m_csBOLTHK), 0))
        {
            AfxMessageBox("If you are using a BOLSTER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = BOLSTER_PARTCODE ; 
		newpart.steel = m_comboBOLSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csBOLDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csBOLTHK)) ; 
        double thk = newpart.length ; 
        newpart.processState = STATE_ADD ; 
        SetStatFlags((mBOLTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mBOLHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 
        int idx = -1 ; 

        if (newpart.steel == STEEL_H13)
        {
            if (pcms->FindPart("BOH", "", newpart.diam, thk, newpart.partname)) 
            {
                char *msg = 0 ;
                idx = order.AppendJob(newpart, &msg) ; 
                if (msg)
                    AfxMessageBox(msg, MB_OK) ;
            }
            else
            {
                AfxMessageBox("No standard part exists for the BOLSTER\r\n"
                    "dimensions specified in the master parts list. There must\r\n"
                    "be a valid part defined in Solarsoft before you can add\r\n"
                    "the part. Please check the dimensions, and if correct\r\n"
                    "report the problem to sales.", MB_OK) ; 
                return -1 ; 
            }
        }
        else
        {
            if (pcms->FindPart("BO2", "", newpart.diam, thk, newpart.partname)) 
                idx = order.AppendJob(newpart) ; 
        }
    }

    // ****************************************************************
    // *********************   SUB BOLSTER  ***************************
    // ****************************************************************
    if (order.jobSUB())
    {   
        if (m_bSUB)
        {   // Then doing an update, maybe.
            order.bHasSUB = true ; 

            if (CompEQ(atof((LPCTSTR)m_csSUBTHK), 0))
            {
                AfxMessageBox("If you are using a SUB-BOLSTER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

            int newStat = 0 ;
            SetStatFlags((mSBLTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                         (mSBLHB_Chk ? CMSJob::HARDENED_BLANK : 0), newStat) ; 

			if ((order.jobSUB()->statFlags != newStat) ||
				(order.jobSUB()->steel != m_comboSUBSTEEL.GetCurSel()) ||
				!CompEQ(order.jobSUB()->diam, atof((LPCTSTR)m_csSUBDIA)) ||
				!CompEQ(order.jobSUB()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csSUBTHK))))
			{   // Then something has changed
				order.jobSUB()->processState = STATE_UPDATE ; 
				order.jobSUB()->diam = atof((LPCTSTR)m_csSUBDIA) ; 
				order.jobSUB()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csSUBTHK)) ; 
				order.jobSUB()->steel = m_comboSUBSTEEL.GetCurSel() ;
				order.jobSUB()->statFlags = newStat ; 
			}
			CString prt = "SBO";
			CString steel = CCADupdateDlg::SteelType(order.jobSUB()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}
        }
        else
        {   // Then delete the part. 
            order.bHasSUB = false ; 
            order.jobSUB()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bSUB)
    {   // Then have to add one since none existed before. 

        if (AfxMessageBox("WARNING: you are about to add a SUB-BOLSTER to this\r\n"
            "order which will not appear on the sales order\r\n"
            "    Are you SURE you want to do this?", MB_YESNO) != IDYES)             
        {   // Then don't proceed
            return -1 ; 
        }

        order.bHasSUB = true ; 

        if (CompEQ(atof((LPCTSTR)m_csSUBTHK), 0))
        {
            AfxMessageBox("If you are using a SUB-BOLSTER, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = SUBBOLSTER_PARTCODE ; 
		newpart.steel = m_comboSUBSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csSUBDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csSUBTHK)) ; 
        double thk = newpart.length ; 
        newpart.processState = STATE_ADD ; 
        SetStatFlags((mSBLTB_Chk ? CMSJob::TURNED_BLANK : 0) | 
                     (mSBLHB_Chk ? CMSJob::HARDENED_BLANK : 0), newpart.statFlags) ; 
        int idx = -1 ; 

        if (newpart.steel == STEEL_H13)
        {
            if (pcms->FindPart("SBH", "", newpart.diam, thk, newpart.partname)) 
            {
                char *msg = 0 ;
                idx = order.AppendJob(newpart, &msg) ; 
                if (msg)
                    AfxMessageBox(msg, MB_OK) ;
            }
            else
            {
                AfxMessageBox("No standard part exists for the SUB-BOLSTER\r\n"
                    "dimensions specified in the master parts list. There must\r\n"
                    "be a valid part defined in Solarsoft before you can add\r\n"
                    "the part. Please check the dimensions, and if correct\r\n"
                    "report the problem to sales.", MB_OK) ; 
                return -1 ; 
            }

        }
        else
        {
            if (pcms->FindPart("SB2", "", newpart.diam, thk, newpart.partname)) 
                idx = order.AppendJob(newpart) ; 
        }
    }


    // ****************************************************************
    // *********************    DIE RING    ***************************
    // ****************************************************************
    if (order.jobRNG())
    {   
        if (m_bRNG)
        {   // Then doing an update, maybe.
            order.bHasRNG = true ; 

            if (CompEQ(atof((LPCTSTR)m_csRNGTHK), 0))
            {
                AfxMessageBox("If you are using a DIE RING, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
                if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
				return -1 ; 
            }

			if ((order.jobRNG()->steel != m_comboRNGSTEEL.GetCurSel()) ||
				!CompEQ(order.jobRNG()->diam, atof((LPCTSTR)m_csRNGDIA)) ||
				!CompEQ(order.jobRNG()->length, Thick_FinMM2StkIN(atof((LPCTSTR)m_csRNGTHK))))
			{   // Then something has changed
				order.jobRNG()->processState = STATE_UPDATE ; 
				order.jobRNG()->diam = atof((LPCTSTR)m_csRNGDIA) ; 
				order.jobRNG()->length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csRNGTHK)) ; 
				order.jobRNG()->steel = m_comboRNGSTEEL.GetCurSel() ;
			}
			CString prt = "DR";
			CString steel = CCADupdateDlg::SteelType(order.jobRNG()->steel) ;
			if(CCADupdateDlg::CheckSoNumDec(m_csSONUM,prt)<1)
			{
				//Insert
				CCADupdateDlg::InsertRecordDec(m_csSONUM,prt,steel);
			}
			else
			{
				//Update
				CCADupdateDlg::UpdateRecordDec(m_csSONUM,prt,steel);
			}
        }
        else
        {   // Then delete the part. 
            order.bHasRNG = false ; 
            order.jobRNG()->processState = STATE_DELETE ; 
        }
    }
    else if (m_bRNG)
    {   // Then have to add one since none existed before. 

        if (AfxMessageBox("WARNING: you are about to add a DIE RING to this\r\n"
            "order which will not appear on the sales order\r\n"
            "    Are you SURE you want to do this?", MB_YESNO) != IDYES)             
        {   // Then don't proceed
            return -1 ; 
        }

        order.bHasRNG = true ; 

        if (CompEQ(atof((LPCTSTR)m_csRNGTHK), 0))
        {
            AfxMessageBox("If you are using a DIR RING, the thickness cannot be zero", MB_ICONEXCLAMATION) ; 
            if(multiSO1)
				{
					AfxMessageBox("The process has been errored out!", MB_ICONEXCLAMATION) ; 
					exit(0);
				}
			return -1 ; 
        }

        CMSJob newpart ;
        newpart.partcode = RING_PARTCODE ; 
		newpart.steel = m_comboRNGSTEEL.GetCurSel() ; 
        newpart.diam  = atof((LPCTSTR)m_csRNGDIA) ; 
        newpart.length = Thick_FinMM2StkIN(atof((LPCTSTR)m_csRNGTHK)) ; 
        double thk = newpart.length ; 
        newpart.processState = STATE_ADD ; 
        int idx = -1 ; 

        if (newpart.steel == STEEL_H13)
        {
            if (pcms->FindPart("RI", "", newpart.diam, thk, newpart.partname)) 
            {
                char *msg = 0 ;
                idx = order.AppendJob(newpart, &msg) ; 
                if (msg)
                    AfxMessageBox(msg, MB_OK) ; 
            }
            else
            {
                AfxMessageBox("No standard part exists for the DIE RING\r\n"
                    "dimensions specified in the master parts list. There must\r\n"
                    "be a valid part defined in Solarsoft before you can add\r\n"
                    "the part. Please check the dimensions, and if correct\r\n"
                    "report the problem to sales.", MB_OK) ; 
                return -1 ; 
            }
        }
        else
        {
            AfxMessageBox("Only H-13 is currently supported for DIE RINGS") ; 
            return -1 ; 
        }
    }


    return 0 ; 
}