#include "stdafx.h"

char *CCADupdateDlg::ConvtStrToChar (CString stringInput)
{
	int num = stringInput.GetLength();
	static char inputString[512];
	for(int i = 0; i<=num; i++)
	{
		inputString[i] = stringInput[i];
	}
	return inputString;
}

CString *CCADupdateDlg::Split(char *input, char *delimiter, CString output[])
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

CString CCADupdateDlg::inputField(CString stringInput)
{
	stringInput = stringInput.Trim();
	CString tempArray[4];
	char* temp1 = ConvtStrToChar(stringInput);
	CString* temp2 = Split(temp1, ":", tempArray);
	CString temp3 = tempArray[1];
	temp3 = temp3.Trim();
	return temp3;
}

bool CCADupdateDlg::FlatFile(CString fileInput)
{
	fileInput = fileInput.Trim();
	bool FileTick = false;
	if(fileInput.Find("Y")>-1)
	{
		FileTick = true;
	}
	return FileTick;
}

bool CCADupdateDlg::vaildInput(CString validInput)
{
	bool checkInput = false;
	//If it's empty string the default value is false
	if(validInput=="Y" || validInput=="N")
	{
		checkInput = true;
	}
	else if(validInput=="")
	{
		checkInput = false;
	}
	else
	{
		checkInput = false;
		AfxMessageBox("Invalid Input",MB_OK) ; 
		exit(0);
	}
	return checkInput;
}

int CCADupdateDlg::SteelType(CString steel)
{
	/*if it's empty string the default steelNumber is 1. 
	if the string does not match existing steel type, the program will
	return Error messages.*/
	int steelNumber = 1;
	if(steel=="H-13")
	{
		steelNumber = 1;
	}
	else if(steel=="2714")
	{
		steelNumber = 2;
	}
	else if(steel=="EK38")
	{
		steelNumber = 3;
	}
	else if(steel=="HTVR")
	{
		steelNumber = 4;
	}
	else if(steel=="M2")
	{
		steelNumber = 5;
	}
	else if(steel=="QRO90")
	{
		steelNumber = 6;
	}
	else if(steel=="")
	{
		steelNumber = 1;
	}
	else
	{
		AfxMessageBox("Invalid Steel Type",MB_OK) ; 
		return -1;
	}
	
	return steelNumber;
}

int CCADupdateDlg::ReadInput()
{	
	
	char filename[20] = "testinput.txt";
	CString m_strLine, m_strText;
	FILE *fp;
	bool validInput;
	fp = fopen(filename, "r");
	char line[512]="";
	if(fp!=NULL)
	{
		// read each line in the file
		while(fgets(line,sizeof(line),fp)!=NULL)
		{
			//convert the line to a CString
			m_strLine = line;
			m_strLine.Replace(_T("\n"), _T("\r\n"));
			//store each line to the text string
			m_strText += m_strLine;
		}
		fclose(fp);
	}
	else
	{
		AfxMessageBox("Could not open file!",MB_OK) ; 
		return -1;
	}
	/*Flat File input example format.
	Order#: 228400,
	FDR:Y,FDRTB:,FDRHB:,FDRDIA:20,FDRTHK:20,FDRSTEEL:H-13,
	MND:Y,MNDTB:Y,MNDHB:,MNDDIA:10,MNDTHK:10,MNDSTEEL:2714,
	PLT:N,PLTTB:,PLTHB:,PLTDIA:13,PLTTHK:12,PLTSTEEL:H-13,
	BKR:,BKRTB:,BKRHB:,BKRDIA:10,BKRTHK:13,BKRSTEEL:EK38,
	BOL:,BOLTB:,BOLHB:,BOLDIA:16,BOLTHK:18,BOLSTEEL:M2,
	SUB:,SUBTB:,SUBHB:,SUBDIA:,SUBTHK:,SUBSTEEL:H-13,
	RNG:,RNGTB:,RNGHB:,RNGDIA:,RNGTHK:,RNGSTEEL:H-13
	*/
	//CString temp = "Order#: 228400,FDR: Y,FDRTB:,FDRHB  :,FDRDIA:20,FDRTHK:20,MND:Y,MNDTB:Y,MNDHB:,MNDDIA:10,MNDTHK:10,PLT:N,PLTTB:,PLTHB:,PLTDIA:13,PLTTHK:12,BKR:,BKRTB:,BKRHB:,BKRDIA:10,BKRTHK:13,BOL:,BOLTB:,BOLHB:,BOLDIA:16,BOLTHK:18,SUB:,SUBTB:,SUBHB:,SUBDIA:,SUBTHK:,RNG:,RNGTB:,RNGHB:,RNGDIA:,RNGTHK:,STEEL:H-13"; 
	CString temp = m_strText;
	CString orderField = _T("ORDER#");
	CString FDRField = _T("FDR:");
	CString FDRTBField = _T("FDRTB:");
	CString FDRHBField = _T("FDRHB:");
	CString FDRDIAField = _T("FDRDIA:");
	CString FDRTHKField = _T("FDRTHK:");
	CString FDRSTEELField = _T("FDRSTEEL:");
	CString MNDField = _T("MND:");
	CString MNDTBField = _T("MNDTB:");
	CString MNDHBField = _T("MNDHB:");
	CString MNDDIAField = _T("MNDDIA:");
	CString MNDTHKField = _T("MNDTHK:");
	CString MNDSTEELField = _T("MNDSTEEL:");
	CString PLTField = _T("PLT:");
	CString PLTTBField = _T("PLTTB:");
	CString PLTHBField = _T("PLTHB:");
	CString PLTDIAField = _T("PLTDIA:");
	CString PLTTHKField = _T("PLTTHK:");
	CString PLTSTEELField = _T("PLTSTEEL:");
	CString BKRField = _T("BKR:");
	CString BKRTBField = _T("BKRTB:");
	CString BKRHBField = _T("BKRHB:");
	CString BKRDIAField = _T("BKRDIA:");
	CString BKRTHKField = _T("BKRTHK:");
	CString BKRSTEELField = _T("BKRSTEEL:");
	CString BOLField = _T("BOL:");
	CString BOLTBField = _T("BOLTB:");
	CString BOLHBField = _T("BOLHB:");
	CString BOLDIAField = _T("BOLDIA:");
	CString BOLTHKField = _T("BOLTHK:");
	CString BOLSTEELField = _T("BOLSTEEL:");
	CString SUBField = _T("SUB:");
	CString SUBTBField = _T("SUBTB:");
	CString SUBHBField = _T("SUBHB:");
	CString SUBDIAField = _T("SUBDIA:");
	CString SUBTHKField = _T("SUBTHK:");
	CString SUBSTEELField = _T("SUBSTEEL:");
	CString RNGField = _T("RNG:"); 
	CString RNGTBField = _T("RNGTB:");
	CString RNGHBField = _T("RNGHB:");
	CString RNGDIAField = _T("RNGDIA:");
	CString RNGTHKField = _T("RNGTHK:");
	CString RNGSTEELField = _T("RNGSTEEL:");


	char* input = ConvtStrToChar (temp);
	CString splitString[512];
	CString* output = Split(input, ",",splitString);
	for(int p = 0; p<=512; p++)
	{
		if(splitString[p]=="")
			break;
		splitString[p]=splitString[p].MakeUpper().Trim();
		if(splitString[p].Find(orderField)>-1)
		{
			m_csSONUM = inputField(splitString[p]);
			//long lNum1 =  _wtoi64(ordertemp);
		}
		else if(splitString[p].Find(FDRField)>-1)
		{
			CString FDRstring = inputField(splitString[p]);
			validInput = vaildInput(FDRstring);
			m_bFDR = FlatFile(FDRstring);
		}
		else if(splitString[p].Find(FDRTBField)>-1)
		{
			CString FDRTBstring = inputField(splitString[p]);
			validInput = vaildInput(FDRTBstring);
			mFDRTB_Chk = FlatFile(FDRTBstring);
		}
		else if(splitString[p].Find(FDRHBField)>-1)
		{
			CString FDRHBstring = inputField(splitString[p]);
			validInput = vaildInput(FDRHBstring);
			mFDRHB_Chk = FlatFile(FDRHBstring);
		}
		else if(splitString[p].Find(FDRDIAField)>-1)
		{
			CString FDRDIAstring = splitString[p];
			m_csFDRDIA = inputField(FDRDIAstring);
		}
		else if(splitString[p].Find(FDRTHKField)>-1)
		{
			CString FDRTHKstring = splitString[p];
			m_csFDRTHK = inputField(FDRTHKstring);
		}
		else if(splitString[p].Find(FDRSTEELField)>-1)
		{
			CString FDRSTEELstring = splitString[p];
			f_FDRSTEEL = inputField(FDRSTEELstring);
			m_FDRSTEEL = SteelType(f_FDRSTEEL);
		}
		else if(splitString[p].Find(MNDField)>-1)
		{
			CString MNDstring = inputField(splitString[p]);
			validInput = vaildInput(MNDstring);
			m_bMND = FlatFile(MNDstring);
		}
		else if(splitString[p].Find(MNDTBField)>-1)
		{
			CString MNDTBstring = inputField(splitString[p]);
			validInput = vaildInput(MNDTBstring);
			mMNDTB_Chk = FlatFile(MNDTBstring);
		}
		else if(splitString[p].Find(MNDHBField)>-1)
		{
			CString MNDHBstring = inputField(splitString[p]);
			validInput = vaildInput(MNDHBstring);
			mMNDHB_Chk = FlatFile(MNDHBstring);
		}
		else if(splitString[p].Find(MNDDIAField)>-1)
		{
			CString MNDDIAstring = splitString[p];
			m_csMNDDIA = inputField(MNDDIAstring);
		}
		else if(splitString[p].Find(MNDTHKField)>-1)
		{
			CString MNDTHKstring = splitString[p];
			m_csMNDTHK = inputField(MNDTHKstring);
		}
		else if(splitString[p].Find(MNDSTEELField)>-1)
		{
			CString MNDSTEELstring = splitString[p];
			f_MNDSTEEL = inputField(MNDSTEELstring);
			m_MNDSTEEL = SteelType(f_MNDSTEEL);
		}
		else if(splitString[p].Find(PLTField)>-1)
		{
			CString PLTstring = inputField(splitString[p]);
			validInput = vaildInput(PLTstring);
			m_bPLT = FlatFile(PLTstring);
		}
		else if(splitString[p].Find(PLTTBField)>-1)
		{
			CString PLTTBstring = inputField(splitString[p]);
			validInput = vaildInput(PLTTBstring);
			mPLTTB_Chk = FlatFile(PLTTBstring);
		}
		else if(splitString[p].Find(PLTHBField)>-1)
		{
			CString PLTHBstring = inputField(splitString[p]);
			validInput = vaildInput(PLTHBstring);
			mPLTHB_Chk = FlatFile(PLTHBstring);
		}
		else if(splitString[p].Find(PLTDIAField)>-1)
		{
			CString PLTDIAstring = splitString[p];
			m_csPLTDIA = inputField(PLTDIAstring);
		}
		else if(splitString[p].Find(PLTTHKField)>-1)
		{
			CString PLTTHKstring = splitString[p];
			m_csPLTTHK = inputField(PLTTHKstring);
		}
		else if(splitString[p].Find(PLTSTEELField)>-1)
		{
			CString PLTSTEELstring = splitString[p];
			f_PLTSTEEL = inputField(PLTSTEELstring);
			m_PLTSTEEL = SteelType(f_PLTSTEEL);
		}
		else if(splitString[p].Find(BKRField)>-1)
		{
			CString BKRstring = inputField(splitString[p]);
			validInput = vaildInput(BKRstring);
			m_bBKR = FlatFile(BKRstring);
		}
		else if(splitString[p].Find(BKRTBField)>-1)
		{
			CString BKRTBstring = inputField(splitString[p]);
			validInput = vaildInput(BKRTBstring);
			mBKRTB_Chk = FlatFile(BKRTBstring);
		}
		else if(splitString[p].Find(BKRHBField)>-1)
		{
			CString BKRHBstring = inputField(splitString[p]);
			validInput = vaildInput(BKRHBstring);
			mBKRHB_Chk = FlatFile(BKRHBstring);
		}
		else if(splitString[p].Find(BKRDIAField)>-1)
		{
			CString BKRDIAstring = splitString[p];
			m_csBKRDIA = inputField(BKRDIAstring);
		}
		else if(splitString[p].Find(BKRTHKField)>-1)
		{
			CString BKRTHKstring = splitString[p];
			m_csBKRTHK = inputField(BKRTHKstring);
		}
		else if(splitString[p].Find(BKRSTEELField)>-1)
		{
			CString BKRSTEELstring = splitString[p];
			f_BKRSTEEL = inputField(BKRSTEELstring);
			m_BKRSTEEL = SteelType(f_BKRSTEEL);
		}
		else if(splitString[p].Find(BOLField)>-1)
		{
			CString BOLstring = inputField(splitString[p]);
			validInput = vaildInput(BOLstring);
			m_bBOL= FlatFile(BOLstring);
		}
		else if(splitString[p].Find(BOLTBField)>-1)
		{
			CString BOLTBstring = inputField(splitString[p]);
			validInput = vaildInput(BOLTBstring);
			mBOLTB_Chk= FlatFile(BOLTBstring);
		}
		else if(splitString[p].Find(BOLHBField)>-1)
		{
			CString BOLHBstring = inputField(splitString[p]);
			validInput = vaildInput(BOLHBstring);
			mBOLHB_Chk= FlatFile(BOLHBstring);
		}
		else if(splitString[p].Find(BOLDIAField)>-1)
		{
			CString BOLDIAstring = splitString[p];
			m_csBOLDIA = inputField(BOLDIAstring);
		}
		else if(splitString[p].Find(BOLTHKField)>-1)
		{
			CString BOLTHKstring = splitString[p];
			m_csBOLTHK = inputField(BOLTHKstring);
		}
		else if(splitString[p].Find(BOLSTEELField)>-1)
		{
			CString BOLSTEELstring = splitString[p];
			f_BOLSTEEL = inputField(BOLSTEELstring);
			m_BOLSTEEL = SteelType(f_BOLSTEEL);
		}
		else if(splitString[p].Find(SUBField)>-1)
		{
			CString SUBstring = inputField(splitString[p]);
			validInput = vaildInput(SUBstring);
			m_bSUB = FlatFile(SUBstring);
		}
		else if(splitString[p].Find(SUBTBField)>-1)
		{
			CString SUBTBstring = inputField(splitString[p]);
			validInput = vaildInput(SUBTBstring);
			mSBLTB_Chk = FlatFile(SUBTBstring);
		}
		else if(splitString[p].Find(SUBHBField)>-1)
		{
			CString SUBHBstring = inputField(splitString[p]);
			validInput = vaildInput(SUBHBstring);
			mSBLHB_Chk = FlatFile(SUBHBstring);
		}
		else if(splitString[p].Find(SUBDIAField)>-1)
		{
			CString SUBDIAstring = splitString[p];
			m_csSUBDIA= inputField(SUBDIAstring);
		}
		else if(splitString[p].Find(SUBTHKField)>-1)
		{
			CString SUBTHKstring = splitString[p];
			m_csSUBTHK= inputField(SUBTHKstring);
		}
		else if(splitString[p].Find(SUBSTEELField)>-1)
		{
			CString SUBSTEELstring = splitString[p];
			f_SUBSTEEL = inputField(SUBSTEELstring);
			m_SUBSTEEL = SteelType(f_SUBSTEEL);
		}
		else if(splitString[p].Find(RNGField)>-1)
		{
			CString RNGstring = inputField(splitString[p]);
			validInput = vaildInput(RNGstring);
			m_bRNG = FlatFile(RNGstring);
		}
		else if(splitString[p].Find(RNGTBField)>-1)
		{
			CString RNGTBstring = inputField(splitString[p]);
			validInput = vaildInput(RNGTBstring);
			mRNGTB_Chk = FlatFile(RNGTBstring);
		}
		else if(splitString[p].Find(RNGHBField)>-1)
		{
			CString RNGHBstring = inputField(splitString[p]);
			validInput = vaildInput(RNGHBstring);
			mRNGHB_Chk = FlatFile(RNGHBstring);
		}
		else if(splitString[p].Find(RNGDIAField)>-1)
		{
			CString RNGDIAstring = splitString[p];
			m_csRNGDIA = inputField(RNGDIAstring);
		}
		else if(splitString[p].Find(RNGTHKField)>-1)
		{
			CString RNGTHKstring = splitString[p];
			m_csRNGTHK = inputField(RNGTHKstring);
		}
		else if(splitString[p].Find(RNGSTEELField)>-1)
		{
			CString RNGSTEELstring = splitString[p];
			f_RNGSTEEL = inputField(RNGSTEELstring);
			m_RNGSTEEL = SteelType(f_RNGSTEEL);
		}
		
	}
	return 0;

	
}

int CCADupdateDlg::ReadInput2()
{
	char filename[35] = "Infor.txt";
	//char filename[20] = "e:\\testinput.txt";
	CString m_strLine, m_strText;
	FILE *fp;
	fp = fopen(filename, "r");
	char line[512]="";
	if(fp!=NULL)
	{
		// read each line in the file
		while(fgets(line,sizeof(line),fp)!=NULL)
		{
			//convert the line to a CString
			m_strLine = line;
			m_strLine.Replace(_T("\n"), _T("\r\n"));
			//store each line to the text string
			m_strText += m_strLine;
		}
		fclose(fp);
	}
	else
	{
		AfxMessageBox("Could not open file!",MB_OK) ; 
		return -1;
	}
	CString temp = m_strText;
	CString orderField = _T("SO#:");

	CString FDRDIAField = _T("FDRDIA:");
	CString FDRTHKField = _T("FDRTHK:");
	CString MNDDIAField = _T("MNDDIA:");
	CString MNDTHKField = _T("MNDTHK:");
	CString PLTDIAField = _T("PLTDIA:");
	CString PLTTHKField = _T("PLTTHK:");
	CString BKRDIAField = _T("BKRDIA:");
	CString BKRTHKField = _T("BKRTHK:");
	CString BOLDIAField = _T("BOLDIA:");
	CString BOLTHKField = _T("BOLTHK:");
	CString SUBDIAField = _T("SUBDIA:");
	CString SUBTHKField = _T("SUBTHK:");
	CString RNGDIAField = _T("RNGDIA:");
	CString RNGTHKField = _T("RNGTHK:");

	char* input = ConvtStrToChar (temp);
	CString splitString[512];
	CString* output = Split(input, ",",splitString);
	for(int p = 0; p<=512; p++)
	{
		if(splitString[p]=="")
			break;
		splitString[p]=splitString[p].MakeUpper().Trim();
		if(splitString[p].Find(orderField)>-1)
		{
			CString tempSO;
			tempSO =  inputField(splitString[p]);
			if(tempSO.Find("/")>-1)
			{
				multiSO = true;
				multi_SO = 1;
				char* tempInput = ConvtStrToChar(tempSO);
				CString* tempSO2 = Split(tempInput, "/", splitSO);
				m_csSONUM = "2" + splitSO[0].Trim();
				baseSO = m_csSONUM;
				f_csSONUM =  m_csSONUM;
			}
			else
			{
				//f_csSONUM = "2" + inputField(splitString[p]);
				m_csSONUM = "2" + inputField(splitString[p]);
				f_csSONUM =  m_csSONUM;
			}
		}
		else if(splitString[p].Find(FDRDIAField)>-1)
		{
			CString FDRDIAstring = splitString[p];
			f_csFDRDIA = inputField(FDRDIAstring);
			//m_csFDRDIA = inputField(FDRDIAstring);
		}
		else if(splitString[p].Find(FDRTHKField)>-1)
		{
			CString FDRTHKstring = splitString[p];
			f_csFDRTHK = inputField(FDRTHKstring);
			//m_csFDRTHK = inputField(FDRTHKstring);
		}
		
		else if(splitString[p].Find(MNDDIAField)>-1)
		{
			CString MNDDIAstring = splitString[p];
			f_csMNDDIA = inputField(MNDDIAstring);
			//m_csMNDDIA = inputField(MNDDIAstring);
		}
		else if(splitString[p].Find(MNDTHKField)>-1)
		{
			CString MNDTHKstring = splitString[p];
			f_csMNDTHK = inputField(MNDTHKstring);
			//m_csMNDTHK = inputField(MNDTHKstring);
		}
		
		else if(splitString[p].Find(PLTDIAField)>-1)
		{
			CString PLTDIAstring = splitString[p];
			f_csPLTDIA = inputField(PLTDIAstring);
			//m_csPLTDIA = inputField(PLTDIAstring);
		}
		else if(splitString[p].Find(PLTTHKField)>-1)
		{
			CString PLTTHKstring = splitString[p];
			f_csPLTTHK = inputField(PLTTHKstring);
			//m_csPLTTHK = inputField(PLTTHKstring);
		}
		
		else if(splitString[p].Find(BKRDIAField)>-1)
		{
			CString BKRDIAstring = splitString[p];
			f_csBKRDIA = inputField(BKRDIAstring);
			//m_csBKRDIA = inputField(BKRDIAstring);
		}
		else if(splitString[p].Find(BKRTHKField)>-1)
		{
			CString BKRTHKstring = splitString[p];
			f_csBKRTHK = inputField(BKRTHKstring);
			//m_csBKRTHK = inputField(BKRTHKstring);
		}
		
		else if(splitString[p].Find(BOLDIAField)>-1)
		{
			CString BOLDIAstring = splitString[p];
			f_csBOLDIA = inputField(BOLDIAstring);
			m_csBOLDIA = inputField(BOLDIAstring);
		}
		else if(splitString[p].Find(BOLTHKField)>-1)
		{
			CString BOLTHKstring = splitString[p];
			f_csBOLTHK = inputField(BOLTHKstring);
			//m_csBOLTHK = inputField(BOLTHKstring);
		}
		else if(splitString[p].Find(SUBDIAField)>-1)
		{
			CString SUBDIAstring = splitString[p];
			f_csSUBDIA= inputField(SUBDIAstring);
			//m_csSUBDIA= inputField(SUBDIAstring);
		}
		else if(splitString[p].Find(SUBTHKField)>-1)
		{
			CString SUBTHKstring = splitString[p];
			f_csSUBTHK= inputField(SUBTHKstring);
			//m_csSUBTHK= inputField(SUBTHKstring);
		}
		else if(splitString[p].Find(RNGDIAField)>-1)
		{
			CString RNGDIAstring = splitString[p];
			f_csRNGDIA = inputField(RNGDIAstring);
			//m_csRNGDIA = inputField(RNGDIAstring);
		}
		else if(splitString[p].Find(RNGTHKField)>-1)
		{
			CString RNGTHKstring = splitString[p];
			f_csRNGTHK = inputField(RNGTHKstring);
			//m_csRNGTHK = inputField(RNGTHKstring);
		}
	}
	return 0;
}

int CCADupdateDlg::ReadInput3()
{
	if(splitSO[multi_SO].GetLength()>0)
	{
		int length = splitSO[multi_SO].GetLength();
		if(length == 1)
		{
			CString change1 = splitSO[multi_SO].Trim();
			CString change2 = baseSO.Mid(0,5).Trim();
			m_csSONUM = change2+change1;
		}
		if(length == 2)
		{
			CString change1 = splitSO[multi_SO].Trim();
			CString change2 = baseSO.Mid(0,4).Trim();
			m_csSONUM = change2+change1;
		}
		if(length == 3)
		{
			CString change1 = splitSO[multi_SO].Trim();
			CString change2 = baseSO.Mid(0,3).Trim();
			m_csSONUM = change2+change1;
		}
		if(length == 4)
		{
			CString change1 = splitSO[multi_SO].Trim();
			CString change2 = baseSO.Mid(0,2).Trim();
			m_csSONUM = change2+change1;
		}
		if(length == 5)
		{
			CString change1 = splitSO[multi_SO].Trim();
			CString change2 = baseSO.Mid(0,1).Trim();
			m_csSONUM = change2+change1;
		}
		multi_SO++;
	}
	else
	{
		multiSO = false;
	}

	return 0;
}

//int CCADupdateDlg::SaleOrder()
//{
//
//}

/* ----------------------------------------------------------------------------
    To find standalone subparts do:
    select * from prodtest.ocri where ddpart like '%MA%' and ddord# < 400000
 ---------------------------------------------------------------------------- */
// This is the default button to capture the enter key. 
int CCADupdateDlg::ExtractSONUMs(const char *sostr, char sonums[MAXNUMSONUMS][32]) 
{
    int i ; 
    int sonumCount = 0 ; 

    char lastSONUM[16] ; 
    lastSONUM[0] = 0 ; 

    char wrkstr[64] ; 
    strncpy(wrkstr, sostr, 62) ; 

    wrkstr[63] = 0 ; 
    char *tok = strtok(wrkstr, "/ ") ; 
    while (tok != 0)
    {
        if (atoi(tok) > 9999)
        {   // Then this is a complete SO number definition.
            strcpy(sonums[sonumCount], tok) ; 
            strcpy(lastSONUM, sonums[sonumCount++]) ; 
        }
        else
        {   // We have a partial token with an extension
            if (lastSONUM[0] && strlen(tok) < MAXSONUMLEN)
            {   // Then we can build a new tok value
                char sostr[16] ; 
                int toklen = strlen(tok) ; 
                int baselen = strlen(lastSONUM) ;
                for (i=0; i < baselen - toklen; i++)
                    sostr[i] = lastSONUM[i] ; 
                for (i=0; i < toklen; i++)
                {
                    sostr[baselen - toklen + i] = tok[i] ; 
                }
                sostr[baselen] = 0 ; 

                strcpy(sonums[sonumCount], sostr) ; 
                strcpy(lastSONUM, sonums[sonumCount++]) ; 
            }
        }
        tok = strtok(0, "/ ") ; 
    }

    return sonumCount ; 
}

int CCADupdateDlg::InitializeOrderList()
{
	//ReadInput2();
	Enter = true;
	pcms->FFtmpnum = 1 ; 
	CString SONumber = m_csSONUM;
	if(SONumber.Find("/")>-1)
	{
		int nosonum = ExtractSONUMs(SONumber,sonums);
		int *SONumberArray = new int[nosonum] ; 
		int nsos;
		nsos = nosonum;
		SOCount = nsos;
		MultiSoCAD = true;
		for(int i = 0; i<nsos; i++)
		{
			SONumberArray[i] = atoi(sonums[i]);
			SubSO[i] = SONumberArray[i];
			if(SubSO[i] < 100000)
				SubSO[i] += 200000 ; 
		}
		
	}

	if(MultiSoCAD)
	{
		if(SOCount>0)
		{
			regCADUpdate = false;
			m_csSONUM.Format("%d",SubSO[countMultiSO]);
			if(SubSO[countMultiSO]<0)
			{
				AfxMessageBox("Process Failed", MB_OK) ; 
				exit(0);
			}
			checkStage = countMultiSO;
			countMultiSO++;
			
			//TSO--;
		}
		else
		{
			MultiSoCAD = false;
			AfxMessageBox("Finished running for multipile sales order", MB_OK) ; 
			OnOK() ;
		}
	}
	
    pcms->firstRun = 1 ; 
	//Add code if there is multipile Sale Order. go through this multiple times


	bool res = pcms->InitOrderList((LPCTSTR)m_csSONUM) ;
    pcms->firstRun = 0 ; 

    if (!res)
	{
        AfxMessageBox("ERROR occured trying to get order details") ; 
		if(multiSO||false)
			exit(0);
	}
    if (pcms->activeOrders.size() == 0)
    {
        if (!loopMode)
		{
           AfxMessageBox("ERROR occured trying to get order details") ; 
		   errord = true;
		}
		if(multiSO||false)
			exit(0);
		return -2 ; 
    }

    if (pcms->activeOrders[0].status =='H')
    {
        AfxMessageBox("JOB IS ON HOLD") ; 
        pcms->activeOrders.clear() ; 
        pcms->FreeOrderList();
        return -1 ; 
    }

    unsigned int i ; 
    CMSOrder *pord = &(pcms->activeOrders[0]) ; 
    for (i=0; i < 3; i++)
    {
        if (pord->feederCount[i] > 1 || 
            pord->mandrelCount[i] > 1 || 
            pord->plateCount[i] > 1 || 
            pord->backerCount[i] > 1 || 
            pord->bolsterCount[i] > 1 || 
            pord->subbolsterCount[i] > 1 || 
            pord->ringCount[i] > 1)
        {
            // These two parts match which should never happen. 
            AfxMessageBox("ERROR: there are duplicate parts on this order.\r\n"
                "This must be corrected by sales before this order\r\n"
                "can be processed further. If the order looks OK, then the\r\n"
                "tables (CJOBH, CJOBDM), are likely corrupted.\r\n") ; 

            pcms->activeOrders.clear() ; 
            pcms->FreeOrderList();
			if(multiSO||false)
				exit(0);		
            return -1 ; 
        }
    }
    // Need to search to see if there are duplicate records for this order. 
    for (i=0; i < pord->jobvec.size() - 1; i++)
    {
        CMSJob *pjoba =  &(pord->jobvec[i]) ; 
        for (unsigned int j=i+1; j < pord->jobvec.size(); j++)
        {
            CMSJob *pjobb =  &(pord->jobvec[j]) ; 
            if (pjoba->subCount != pjobb->subCount)
                continue ; // mismatch so not the same. 

            if (pjoba->partname != pjobb->partname)
                continue ; // mismatch so not the same. 

            if (pjoba->mattype != pjobb->mattype)
                continue ; // mismatch so not the same. 

            // These two parts match which should never happen. 
            AfxMessageBox("ERROR: there are two duplicate parts on this order.\r\n"
                "This must be corrected by sales before this order\r\n"
                "can be processed further. (CJOBH, CJOBDM)\r\n") ; 

            pcms->activeOrders.clear() ; 
            pcms->FreeOrderList();
			if(multiSO||false)
				exit(0);	
            return -1 ; 
        }
    }
	int testa = 0;
    return 0 ; 
}
void CCADupdateDlg::Load()
{
	pcms->oIDX = -1 ;
			
			if (InitializeOrderList())
			{
				//EndWaitCursor() ;
				GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 
				return ; 
			}
		
			if (pcms->activeOrders.size() > 0)
			{
				pcms->LoadFeaturesAndOptions() ;

				pcms->oIDX = 0 ; 
				origOrder = pcms->activeOrders[pcms->oIDX] ; 
			}
			SetControls(origOrder) ; 
}
void CCADupdateDlg::OnDefaultButtonClicked()
{
	
    int i = 0 ;
	
	if((regCADUpdate||pass)&&!multiSO&&!MultiSoCAD)
	{
		stage = 1;
		//f_csSONUM =  m_csSONUM;
		UpdateData(TRUE); 
		
		if (lastCtrl == IDC_SONUM_EDIT)
		{   
			// Then load record based on the entered value. 
			BeginWaitCursor() ; 
			// pcms->activeOrders.clear();
			pcms->oIDX = -1 ;
			// pcms->InitOrderList((LPCTSTR)m_csSONUM) ;
			if (InitializeOrderList())
			{
				EndWaitCursor() ;
				GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 
				return ; 
			}
		
			if (pcms->activeOrders.size() > 0)
			{
				pcms->LoadFeaturesAndOptions() ;

				pcms->oIDX = 0 ; 
				origOrder = pcms->activeOrders[pcms->oIDX] ; 
			}
			SetControls(origOrder) ;
			// add 10mm thk to sub parts
			if (m_bMND)
			{
				double thk = atof(m_csMNDTHK.GetBuffer());
				m_csMNDTHK.Format("%.2f", thk);
				if (m_bBKR)
				{
					thk = atof(m_csBKRTHK.GetBuffer());
					m_csBKRTHK.Format("%.2f", thk);
				}
				if (m_bPLT)
				{
					thk = atof(m_csPLTTHK.GetBuffer());
					m_csPLTTHK.Format("%.2f", thk);
				}
				if (m_bFDR)
				{
					thk = atof(m_csFDRTHK.GetBuffer());
					m_csFDRTHK.Format("%.2f", thk);
				}
				if (m_bSUB)
				{
					thk = atof(m_csSUBTHK.GetBuffer());
					m_csSUBTHK.Format("%.2f", thk);
				}
				if (m_bRNG)
				{
					thk = atof(m_csRNGTHK.GetBuffer());
					m_csRNGTHK.Format("%.2f", thk);
				}
			}
			UpdateData(FALSE) ; // set all the control values with new data
			EndWaitCursor() ; 
		}
		else if (lastCtrl == IDC_FROM_EDIT)
		{
			GetDlgItem(IDC_TO_EDIT)->SetFocus() ; 
		}
		else if (lastCtrl == IDC_TO_EDIT)
		{
			GetDlgItem(IDC_TO_EDIT)->SetFocus() ; 
        
			ProcessLoop() ; 
		}
	}
	else if(multiSO1)
	{
		
		pcms->oIDX = -1 ;
		InitializeOrderList();
		if (pcms->activeOrders.size() > 0)
		{
				pcms->LoadFeaturesAndOptions() ;

				pcms->oIDX = 0 ; 
				origOrder = pcms->activeOrders[pcms->oIDX] ; 
		}
		SetControls(origOrder) ;
	}
	else if(MultiSoCAD)
	{
		if(stage<0)
		{
			stage = 1;
			UpdateData(TRUE); 
		
			if (lastCtrl == IDC_SONUM_EDIT)
			{   
				// Then load record based on the entered value. 
				BeginWaitCursor() ; 
				// pcms->activeOrders.clear();
				pcms->oIDX = -1 ;
				// pcms->InitOrderList((LPCTSTR)m_csSONUM) ;
				if (InitializeOrderList())
				{
					EndWaitCursor() ;
					GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 
					return ; 
				}
		
				if (pcms->activeOrders.size() > 0)
				{
					pcms->LoadFeaturesAndOptions() ;

					pcms->oIDX = 0 ; 
					origOrder = pcms->activeOrders[pcms->oIDX] ; 
				}
				SetControls(origOrder) ; 
				UpdateData(FALSE) ; // set all the control values with new data
				EndWaitCursor() ; 
			}
			else if (lastCtrl == IDC_FROM_EDIT)
			{
				GetDlgItem(IDC_TO_EDIT)->SetFocus() ; 
			}
			else if (lastCtrl == IDC_TO_EDIT)
			{
				GetDlgItem(IDC_TO_EDIT)->SetFocus() ; 
        
				ProcessLoop() ; 
			}

		}
		else
		{
			pcms->oIDX = -1 ;
			InitializeOrderList();
			if (pcms->activeOrders.size() > 0)
			{
					pcms->LoadFeaturesAndOptions() ;

					pcms->oIDX = 0 ; 
					origOrder = pcms->activeOrders[pcms->oIDX] ; 
			}
			UpdateData(FALSE) ;
			SetControls(origOrder) ;
		}
	}
	
    // Else do nothing
}

char *NumberStr(char *buf, int num)
{
    sprintf(buf, "%d", num) ; 
    return buf ; 
}

void CCADupdateDlg::ProcessLoop()
{
    int soFrom = atoi((LPCTSTR)m_csSOFrom) ; 
    int soTo = atoi((LPCTSTR)m_csSOTo) ; 

    if ((soFrom > soTo) ||
        (soFrom < 100000) ||
        (soTo > 1000000))
    {
        AfxMessageBox("SO Numbers out of range") ; 
		if(multiSO||false)
				exit(0);	
        return ; 
    }

    loopMode = 1 ; 
    pcms->skipStockCheck = 1 ; 

    for (int i=soFrom; i <= soTo; i++)
    {   // Crank out standard releases for all these orders
        char sostr[32] ;
        sprintf(sostr, "%d", i) ; 
        m_csSONUM = sostr ; 
		UpdateData(FALSE) ; 
        lastCtrl = IDC_SONUM_EDIT ; 
        OnDefaultButtonClicked() ;
		UpdateData(TRUE) ; 

        // Now see if there is data that needs updating. 
        if (pcms->activeOrders.size() == 0)
        {
            fprintf(gCMSparms.pevp->fpLOG, "Skipping order number %d\n", i) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
            continue ; 
        }

        fprintf(gCMSparms.pevp->fpLOG, "Processing order %d\n", i) ; 
        fflush(gCMSparms.pevp->fpLOG) ; 

        CMSOrder *pord = &pcms->activeOrders[0] ; 
        if (pord->jobvec.size() == 0) 
        {
            fprintf(gCMSparms.pevp->fpLOG, "Skipping order number %d - no jobs\n", i) ;
            fflush(gCMSparms.pevp->fpLOG) ; 
            continue ; 
        }

        if (pord->bHollowDie)
        {
            double stackHeight = 0 ; 
            char *px = pord->jobvec[0].partname.Find("X", 1) ; 
            if (px && toupper(*px) == 'X')
            {
                px++ ; 
                while (isspace(*px))
                    px++ ; 
                stackHeight = atof(px) ; 
            }

            int mThk = 70 ; 
            int pThk = 50 ; 
            int bThk = 50 ; 

            if (stackHeight > 0)
            {
                stackHeight *= 25.4 ;
                mThk = (int)(stackHeight * 0.6) ; 
                pThk = (int)(stackHeight * 0.3) ; 
                bThk = (int)(stackHeight * 0.35) ; 
            }

            char buf[64] ; 

            for (int j=0; j < (int)pord->jobvec.size(); j++)
            {
                if (pord->jobvec[j].length <= 1.0)
                {
                    if (pord->jobvec[j].IsMandrel())
                        m_csMNDTHK = NumberStr(buf, mThk) ; 
                    else if (pord->jobvec[j].IsPlate())
                        m_csPLTTHK = NumberStr(buf, pThk) ; 
                    else if (pord->jobvec[j].IsBacker())
                        m_csBKRTHK = NumberStr(buf, bThk) ; 
                }
            }
        }
		UpdateData(FALSE) ; 
        OnBnClickedOk() ; 
    }

    pcms->skipStockCheck = 0 ; 
    loopMode = 0 ; 
}