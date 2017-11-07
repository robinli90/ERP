// CADupdateDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "CMSData.h"
#include <CSStdlibs/fileparams.h>
#define MAXNUMSONUMS            30
#define MAXSONUMLEN             7 
// CCADupdateDlg dialog
class CCADupdateDlg : public CDialog
{
    // Construction
public:
    int firstPaint ; 

    CCADupdateDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum { IDD = IDD_CADUPDATE_DIALOG };

    CMSBOMRTE *pcms ; 
    CMSEventProcessing *pevp ; 
    CMSOrder origOrder ; // original order information
    CMSOrder updOrder ; // updated order info
	CMSOrder cadOrder; // steel order information if running AutoCAD
    int lastCtrl ; 
    int loopMode ;

	CString m_strODBC ; 
    CString m_strODBCusr ; 
    CString m_strODBCpwd ; 
    
	CSQLDatabase m_sql ; 
protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
	
	BOOL ready;
	BOOL regCADUpdate;
	BOOL CADMultiSO;
	BOOL pass;
	BOOL multiSO;
	BOOL multiSO1;
	int x;

    afx_msg void OnEnChangeSonumEdit();
    afx_msg void OnDefaultButtonClicked();
    CString m_csSONUM;
    CString m_csDetails;
    BOOL m_bFDR;
    BOOL m_bMND;
    BOOL m_bPLT;
    BOOL m_bBKR;
    BOOL m_bBOL;
    BOOL m_bSUB;
    BOOL m_bRNG;
    CString m_csOrderDate;
    CString m_csReqdDate;
    CString m_nCavs;
    CString m_csFDRDIA;
    CString m_csMNDDIA;
    CString m_csPLTDIA;
    CString m_csBKRDIA;
    CString m_csBOLDIA;
    CString m_csSUBDIA;
    CString m_csRNGDIA;
    CString m_csFDRTHK;
    CString m_csMNDTHK;
    CString m_csPLTTHK;
    CString m_csBKRTHK;
    CString m_csBOLTHK;
    CString m_csSUBTHK;
    CString m_csRNGTHK;
	CString cad_csSONUM;
	
    CComboBox m_comboFDRSTEEL;
    CComboBox m_comboMNDSTEEL;
    CComboBox m_comboPLTSTEEL;
    CComboBox m_comboBKRSTEEL;
    CComboBox m_comboBOLSTEEL;
    CComboBox m_comboSUBSTEEL;
    CComboBox m_comboRNGSTEEL;
    CListBox m_listOPTIONS;
    BOOL m_bFDROrig;
    BOOL m_bMNDOrig;
    BOOL m_bPLTOrig;
    BOOL m_bBKROrig;
    BOOL m_bBOLOrig;
    BOOL m_bSUBOrig;
    BOOL m_bRNGOrig;

    BOOL mFDRTB_Chk;
    BOOL mFDRHB_Chk;
    BOOL mMNDTB_Chk;
    BOOL mMNDHB_Chk;
    BOOL mPLTTB_Chk;
    BOOL mPLTHB_Chk;
    BOOL mBKRTB_Chk;
    BOOL mBKRHB_Chk;
    BOOL mBOLTB_Chk;
    BOOL mBOLHB_Chk;
    BOOL mSBLTB_Chk;
    BOOL mSBLHB_Chk;
    BOOL mRNGTB_Chk;
    BOOL mRNGHB_Chk;
    
	BOOL Enter;
	BOOL errord;
	//Declare variable for Flat file
	CString f_csSONUM;
    CString f_csDetails;
    BOOL f_bFDR;
    BOOL f_bMND;
    BOOL f_bPLT;
    BOOL f_bBKR;
    BOOL f_bBOL;
    BOOL f_bSUB;
    BOOL f_bRNG;
    CString f_csOrderDate;
    CString f_csReqdDate;
    CString f_nCavs;
    CString f_csFDRDIA;
    CString f_csMNDDIA;
    CString f_csPLTDIA;
    CString f_csBKRDIA;
    CString f_csBOLDIA;
    CString f_csSUBDIA;
    CString f_csRNGDIA;
    CString f_csFDRTHK;
    CString f_csMNDTHK;
    CString f_csPLTTHK;
    CString f_csBKRTHK;
    CString f_csBOLTHK;
    CString f_csSUBTHK;
    CString f_csRNGTHK;
	CString f_FDRSTEEL;
    CString f_MNDSTEEL;
    CString f_PLTSTEEL;
    CString f_BKRSTEEL;
    CString f_BOLSTEEL;
    CString f_SUBSTEEL;
    CString f_RNGSTEEL;
	CString baseSO;
	char sonums[MAXNUMSONUMS][32] ;
	int SubSO[128];
	int countMultiSO;
	bool MultiSoCAD;
	int m_FDRSTEEL;
	int m_MNDSTEEL;
	int m_PLTSTEEL;
	int m_BKRSTEEL;
	int m_BOLSTEEL;
	int m_SUBSTEEL;
	int m_RNGSTEEL;
	int stage;
	int a_FDRSTEEL;
	int a_MNDSTEEL;
	int a_PLTSTEEL;
	int a_BKRSTEEL;
	int a_BOLSTEEL;
	int a_SUBSTEEL;
	int a_RNGSTEEL;

	int multi_SO;
	int SOCount ;
	int checkStage;
	BOOL fFDRTB_Chk;
    BOOL fFDRHB_Chk;
    BOOL fMNDTB_Chk;
    BOOL fMNDHB_Chk;
    BOOL fPLTTB_Chk;
    BOOL fPLTHB_Chk;
    BOOL fBKRTB_Chk;
    BOOL fBKRHB_Chk;
    BOOL fBOLTB_Chk;
    BOOL fBOLHB_Chk;
    BOOL fSBLTB_Chk;
    BOOL fSBLHB_Chk;
    BOOL fRNGTB_Chk;
    BOOL fRNGHB_Chk;
	
	CString splitSO[64];

    afx_msg void OnBnClickedOk();

	void ClickOK();
    void InitSteelCombo(CComboBox &combo); 
	void InitSteelComboAuoCAD(int i) ;
    void SetControls(CMSOrder &ord) ; 
	void GetSteel(CMSOrder &ord) ;
	void SetControlsFlatFile(CMSOrder &ord);
    int UpdateOrderValues(CMSOrder &order) ;
    int InitializeOrderList() ;
    void ProcessLoop() ;
	int ReadInput();
	int ReadInput2();
	int ReadInput3();
	BOOL MultiOrder(bool test);
	CString inputField(CString stringInput);
	CString *Split(char *input, char *delimiter, CString output[]);
	char *ConvtStrToChar (CString stringInput);
	bool FlatFile(CString fileInput);
	int SteelType(CString steel);
	bool vaildInput(CString validInput);
	void Load();
	int CheckSoNum(CString strSONumber);
	int UpdateRecord (CString sonum);

	int CheckSoNumDec(CString strSONumber, CString prtcode);
	int InsertRecordDec (CString sonum, CString prtcode, CString steel);
	int UpdateRecordDec (CString sonum, CString prtcode, CString steel);
	int ExtractSONUMs(const char *sostr, char sonums[MAXNUMSONUMS][32]) ;
	CString SteelType (int steel);
    afx_msg void OnBnClickedHelp();
    afx_msg void OnEnSetfocusFromEdit();
    afx_msg void OnEnSetfocusToEdit();
    afx_msg void OnEnSetfocusSonumEdit();
    afx_msg void OnEnKillfocusFromEdit();
    afx_msg void OnEnKillfocusToEdit();
    CString m_csSOFrom;
    CString m_csSOTo;
    afx_msg void OnEnChangeToEdit();
    afx_msg void OnBnClickedFdrblank();
    afx_msg void OnBnClickedFdrhard();
    afx_msg void OnBnClickedMndblank();
    afx_msg void OnBnClickedMndhard();
    afx_msg void OnBnClickedPltblank();
    afx_msg void OnBnClickedPlthard();
    afx_msg void OnBnClickedBkrblank();
    afx_msg void OnBnClickedBkrhard();
    afx_msg void OnBnClickedBolblank();
    afx_msg void OnBnClickedBolhard();
    afx_msg void OnBnClickedSblblank();
    afx_msg void OnBnClickedSblhard();
    afx_msg void OnBnClickedRngblank();
    afx_msg void OnBnClickedHdrhard();
	afx_msg void OnEnChangePltthkEdit();
	afx_msg void OnEnChangeMndthkEdit();
	afx_msg void OnEnChangeRngthkEdit();
	afx_msg void OnEnChangeFdrthkEdit();
	afx_msg void OnEnChangeBolthkEdit();
	afx_msg void OnBnClickedCancel();
	afx_msg void ExitMFCApp();
	afx_msg void OnCbnSelchangeFdrsteelCombo();
	afx_msg void OnCbnSelchangeMndsteelCombo();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeBkrdiaEdit();
};
