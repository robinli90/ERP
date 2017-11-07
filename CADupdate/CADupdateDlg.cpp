// CADupdateDlg.cpp : implementation file
//
#include "stdafx.h"

// CCADupdateDlg dialog
CCADupdateDlg::CCADupdateDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCADupdateDlg::IDD, pParent)
    , m_csSONUM(_T("")), m_bFDR(FALSE), m_bMND(FALSE), m_bPLT(FALSE), m_bBKR(FALSE), m_bBOL(FALSE)
    , m_bSUB(FALSE), m_bRNG(FALSE), m_csOrderDate(_T("")), m_csReqdDate(_T("")), m_nCavs(_T(""))
    , m_csFDRDIA(_T("")), m_csMNDDIA(_T("")), m_csPLTDIA(_T("")), m_csBKRDIA(_T(""))
    , m_csBOLDIA(_T("")), m_csSUBDIA(_T("")), m_csRNGDIA(_T("")), m_csFDRTHK(_T(""))
    , m_csMNDTHK(_T("")), m_csPLTTHK(_T("")), m_csBKRTHK(_T("")), m_csBOLTHK(_T(""))
    , m_csSUBTHK(_T("")), m_csRNGTHK(_T("")), m_csDetails(_T("")), m_bFDROrig(FALSE)
    , m_bMNDOrig(FALSE), m_bPLTOrig(FALSE), m_bBKROrig(FALSE), m_bBOLOrig(FALSE)
    , m_bSUBOrig(FALSE), m_bRNGOrig(FALSE)
    , m_csSOFrom(_T(""))
    , m_csSOTo(_T(""))
    , mFDRTB_Chk(FALSE)
    , mFDRHB_Chk(FALSE)
    , mMNDTB_Chk(FALSE)
    , mMNDHB_Chk(FALSE)
    , mPLTTB_Chk(FALSE)
    , mPLTHB_Chk(FALSE)
    , mBKRTB_Chk(FALSE)
    , mBKRHB_Chk(FALSE)
    , mBOLTB_Chk(FALSE)
    , mBOLHB_Chk(FALSE)
    , mSBLTB_Chk(FALSE)
    , mSBLHB_Chk(FALSE)
    , mRNGTB_Chk(FALSE)
    , mRNGHB_Chk(FALSE)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME) ;
    pcms = 0 ;
    lastCtrl = 0 ;
    firstPaint = 0 ;
    loopMode = 0 ;
}

void CCADupdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if(false||!multiSO)
		DDX_Text(pDX, IDC_SONUM_EDIT, m_csSONUM);
    DDX_Text(pDX, IDC_SONUM_EDIT, m_csSONUM);
	if(!multiSO1)
	{
		DDX_Check(pDX, IDC_FDR_CHK, m_bFDR);
		DDX_Check(pDX, IDC_MND_CHK, m_bMND);
		DDX_Check(pDX, IDC_PLT_CHK, m_bPLT);
		DDX_Check(pDX, IDC_BKR_CHK, m_bBKR);
		DDX_Check(pDX, IDC_BOL_CHK, m_bBOL);
		DDX_Check(pDX, IDC_SUB_CHK, m_bSUB);
		DDX_Check(pDX, IDC_RNG_CHK, m_bRNG);
	}
    DDX_Text(pDX, IDC_ORDERDATE_EDIT, m_csOrderDate);
    DDX_Text(pDX, IDC_REQDATE_EDIT, m_csReqdDate);
    DDX_Text(pDX, IDC_NCAVS_EDIT, m_nCavs);
    DDX_Text(pDX, IDC_FDRDIA_EDIT, m_csFDRDIA);
    DDX_Text(pDX, IDC_MNDDIA_EDIT, m_csMNDDIA);
    DDX_Text(pDX, IDC_PLTDIA_EDIT, m_csPLTDIA);
    DDX_Text(pDX, IDC_BKRDIA_EDIT, m_csBKRDIA);
    DDX_Text(pDX, IDC_BOLDIA_EDIT, m_csBOLDIA);
    DDX_Text(pDX, IDC_SUBDIA_EDIT, m_csSUBDIA);
    DDX_Text(pDX, IDC_RNGDIA_EDIT, m_csRNGDIA);

	DDX_Text(pDX, IDC_FDRTHK_EDIT, m_csFDRTHK);
	DDX_Text(pDX, IDC_MNDTHK_EDIT, m_csMNDTHK);
	DDX_Text(pDX, IDC_PLTTHK_EDIT, m_csPLTTHK);
	DDX_Text(pDX, IDC_BKRTHK_EDIT, m_csBKRTHK);
	DDX_Text(pDX, IDC_BOLTHK_EDIT, m_csBOLTHK);
	DDX_Text(pDX, IDC_SUBTHK_EDIT, m_csSUBTHK);
	DDX_Text(pDX, IDC_RNGTHK_EDIT, m_csRNGTHK);

    DDX_Control(pDX, IDC_FDRSTEEL_COMBO, m_comboFDRSTEEL);
    DDX_Control(pDX, IDC_MNDSTEEL_COMBO, m_comboMNDSTEEL);
    DDX_Control(pDX, IDC_PLTSTEEL_COMBO, m_comboPLTSTEEL);
    DDX_Control(pDX, IDC_BKRSTEEL_COMBO, m_comboBKRSTEEL);
    DDX_Control(pDX, IDC_BOLSTEEL_COMBO, m_comboBOLSTEEL);
    DDX_Control(pDX, IDC_SUBSTEEL_COMBO, m_comboSUBSTEEL);
    DDX_Control(pDX, IDC_RNGSTEEL_COMBO, m_comboRNGSTEEL);
    DDX_Text(pDX, IDC_ORDERDETAILS_EDIT, m_csDetails);
    DDX_Check(pDX, IDC_FDRORIG_CHK, m_bFDROrig);
    DDX_Check(pDX, IDC_MNDORIG_CHK, m_bMNDOrig);
    DDX_Check(pDX, IDC_PLTORIG_CHK, m_bPLTOrig);
    DDX_Check(pDX, IDC_BKRORIG_CHK, m_bBKROrig);
    DDX_Check(pDX, IDC_BOLORIG_CHK, m_bBOLOrig);
    DDX_Check(pDX, IDC_SUBORIG_CHK, m_bSUBOrig);
    DDX_Check(pDX, IDC_RNGORIG_CHK, m_bRNGOrig);
    DDX_Control(pDX, IDC_OPS_LIST, m_listOPTIONS);
    DDX_Text(pDX, IDC_FROM_EDIT, m_csSOFrom);
    DDX_Text(pDX, IDC_TO_EDIT, m_csSOTo);
    DDX_Check(pDX, IDC_FDRBLANK, mFDRTB_Chk);
    DDX_Check(pDX, IDC_FDRHARD, mFDRHB_Chk);
    DDX_Check(pDX, IDC_MNDBLANK, mMNDTB_Chk);
    DDX_Check(pDX, IDC_MNDHARD, mMNDHB_Chk);
    DDX_Check(pDX, IDC_PLTBLANK, mPLTTB_Chk);
    DDX_Check(pDX, IDC_PLTHARD, mPLTHB_Chk);
    DDX_Check(pDX, IDC_BKRBLANK, mBKRTB_Chk);
    DDX_Check(pDX, IDC_BKRHARD, mBKRHB_Chk);
    DDX_Check(pDX, IDC_BOLBLANK, mBOLTB_Chk);
    DDX_Check(pDX, IDC_BOLHARD, mBOLHB_Chk);
    DDX_Check(pDX, IDC_SBLBLANK, mSBLTB_Chk);
    DDX_Check(pDX, IDC_SBLHARD, mSBLHB_Chk);
    DDX_Check(pDX, IDC_RNGBLANK, mRNGTB_Chk);
    DDX_Check(pDX, IDC_HDRHARD, mRNGHB_Chk);
}

BEGIN_MESSAGE_MAP(CCADupdateDlg, CDialog)
    //{{AFX_MSG_MAP(CCADupdateDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_EN_CHANGE(IDC_SONUM_EDIT, OnEnChangeSonumEdit)
    ON_BN_CLICKED(IDC_DEF_BUTTON, OnDefaultButtonClicked)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_HELP, OnBnClickedHelp)
    ON_EN_SETFOCUS(IDC_FROM_EDIT, OnEnSetfocusFromEdit)
    ON_EN_SETFOCUS(IDC_TO_EDIT, OnEnSetfocusToEdit)
    ON_EN_SETFOCUS(IDC_SONUM_EDIT, OnEnSetfocusSonumEdit)
    ON_EN_KILLFOCUS(IDC_FROM_EDIT, OnEnKillfocusFromEdit)
    ON_EN_KILLFOCUS(IDC_TO_EDIT, OnEnKillfocusToEdit)
    ON_EN_CHANGE(IDC_TO_EDIT, OnEnChangeToEdit)
    ON_BN_CLICKED(IDC_FDRBLANK, OnBnClickedFdrblank)
    ON_BN_CLICKED(IDC_FDRHARD, OnBnClickedFdrhard)
    ON_BN_CLICKED(IDC_MNDBLANK, OnBnClickedMndblank)
    ON_BN_CLICKED(IDC_MNDHARD, OnBnClickedMndhard)
    ON_BN_CLICKED(IDC_PLTBLANK, OnBnClickedPltblank)
    ON_BN_CLICKED(IDC_PLTHARD, OnBnClickedPlthard)
    ON_BN_CLICKED(IDC_BKRBLANK, OnBnClickedBkrblank)
    ON_BN_CLICKED(IDC_BKRHARD, OnBnClickedBkrhard)
    ON_BN_CLICKED(IDC_BOLBLANK, OnBnClickedBolblank)
    ON_BN_CLICKED(IDC_BOLHARD, OnBnClickedBolhard)
    ON_BN_CLICKED(IDC_SBLBLANK, OnBnClickedSblblank)
    ON_BN_CLICKED(IDC_SBLHARD, OnBnClickedSblhard)
    ON_BN_CLICKED(IDC_RNGBLANK, OnBnClickedRngblank)
    ON_BN_CLICKED(IDC_HDRHARD, OnBnClickedHdrhard)
	ON_CBN_SELCHANGE(IDC_FDRSTEEL_COMBO, &CCADupdateDlg::OnCbnSelchangeFdrsteelCombo)
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CCADupdateDlg::OnCbnSelchangeCombo1)
ON_EN_CHANGE(IDC_BKRDIA_EDIT, &CCADupdateDlg::OnEnChangeBkrdiaEdit)
END_MESSAGE_MAP()

// CCADupdateDlg message handlers
BOOL CCADupdateDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog. The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);  // Set big icon
    SetIcon(m_hIcon, FALSE); // Set small icon

    // TODO: Add extra initialization here
    InitSteelCombo(m_comboFDRSTEEL) ; 
    InitSteelCombo(m_comboMNDSTEEL) ; 
    InitSteelCombo(m_comboPLTSTEEL) ; 
    InitSteelCombo(m_comboBKRSTEEL) ; 
    InitSteelCombo(m_comboBOLSTEEL) ; 
    InitSteelCombo(m_comboSUBSTEEL) ; 
    InitSteelCombo(m_comboRNGSTEEL) ; 

    GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ; 

#ifdef _DEBUG
    GetDlgItem(IDC_FROM_EDIT)->ShowWindow(SW_SHOWNORMAL) ; 
    GetDlgItem(IDC_TO_EDIT)->ShowWindow(SW_SHOWNORMAL) ;
#endif 

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCADupdateDlg::InitSteelCombo(CComboBox &combo)
{
    combo.ResetContent() ; 
    combo.AddString(" ") ; 
    for (int i=0; i < (int)pcms->steelvec.size(); i++)
        combo.AddString(pcms->steelvec[i].prefix.c_str()) ; 

	combo.SetCurSel(0) ; 
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCADupdateDlg::OnPaint() 
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
        if (!firstPaint)
        {
            GetDlgItem(IDC_SONUM_EDIT)->SetFocus() ;
            firstPaint = 1 ;
        }
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCADupdateDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CCADupdateDlg::OnEnChangeSonumEdit()
{
    lastCtrl = IDC_SONUM_EDIT ;
}

void ConvertThickToMM(CString &str, double thk) 
{
    csString wrks ; 
    if (CompEQ(thk,0))
        str = "0" ; 
    else
        str = wrks.Format("%.2f", thk * 25.4 - STEEL_CUTALLOWANCE).c_str() ; 
}

void CCADupdateDlg::SetControls(CMSOrder &ord)
{
    // Update all control values
    m_bFDROrig = ord.bHasFDR ; 
    m_bMNDOrig = ord.bHasMND ; 
    m_bPLTOrig = ord.bHasPLT ; 
    m_bBKROrig = ord.bHasBKR ; 
    m_bBOLOrig = ord.bHasBOL ; 
    m_bSUBOrig = ord.bHasSUB ; 
    m_bRNGOrig = ord.bHasRNG ; 

    m_bFDR = m_bFDROrig ; 
    m_bMND = m_bMNDOrig ; 
    m_bPLT = m_bPLTOrig ; 
    m_bBKR = m_bBKROrig ; 
    m_bBOL = m_bBOLOrig ; 
    m_bSUB = m_bSUBOrig ;
    m_bRNG = m_bRNGOrig ; 

    char datestr[64] ; 
    m_csDetails = ord.custCode.c_str() ; 
    m_csDetails += " - " ; 
    m_csDetails += ord.custName.c_str() ; 
    m_csDetails += "\r\n" ; 

    unsigned int i, j ; 
    for (i=0; i < ord.jobvec.size(); i++)
    {
        m_csDetails += ord.jobvec[i].partname.c_str() ; 
        m_csDetails += " : " ; 
        m_csDetails += ord.jobvec[i].mattype.c_str() ; 
        m_csDetails += "\r\n" ; 
    }

    m_csOrderDate = ord.orderDate.FormatDate(datestr) ;
    m_csReqdDate  = ord.reqdDate.FormatDate(datestr) ; 

    csString wrks ; 
    m_csFDRDIA = wrks.Format("%.3f", ord.fdrDia).c_str() ; 
    m_csMNDDIA = wrks.Format("%.3f", ord.mndDia).c_str() ; 
    m_csPLTDIA = wrks.Format("%.3f", ord.pltDia).c_str() ; 
    m_csBKRDIA = wrks.Format("%.3f", ord.bkrDia).c_str() ; 
    m_csBOLDIA = wrks.Format("%.3f", ord.bolDia).c_str() ; 
    m_csSUBDIA = wrks.Format("%.3f", ord.subDia).c_str() ; 
    m_csRNGDIA = wrks.Format("%.3f", ord.rngDia).c_str() ; 

    ConvertThickToMM(m_csFDRTHK, ord.fdrThk) ; 
    ConvertThickToMM(m_csMNDTHK, ord.mndThk) ; 
    ConvertThickToMM(m_csPLTTHK, ord.pltThk) ; 
    ConvertThickToMM(m_csBKRTHK, ord.bkrThk) ; 
    ConvertThickToMM(m_csBOLTHK, ord.bolThk) ; 
    ConvertThickToMM(m_csSUBTHK, ord.subThk) ; 
    ConvertThickToMM(m_csRNGTHK, ord.rngThk) ; 

	if (ord.jobFDR())
		m_comboFDRSTEEL.SetCurSel(ord.jobFDR()->steel) ;

	if (ord.jobMND())
		m_comboMNDSTEEL.SetCurSel(ord.jobMND()->steel) ;

	if (ord.jobPLT())
		m_comboPLTSTEEL.SetCurSel(ord.jobPLT()->steel) ;

	if (ord.jobBKR())
		m_comboBKRSTEEL.SetCurSel(ord.jobBKR()->steel) ;

	if (ord.jobBOL())
		m_comboBOLSTEEL.SetCurSel(ord.jobBOL()->steel) ;

	if (ord.jobSUB())
		m_comboSUBSTEEL.SetCurSel(ord.jobSUB()->steel) ;

	if (ord.jobRNG())
		m_comboRNGSTEEL.SetCurSel(ord.jobRNG()->steel) ;


	m_nCavs = wrks.Format("%d", ord.nCavities).c_str() ; 

	m_listOPTIONS.ResetContent() ; 

	csStringList strlist ; 
	for (i=0; i < ord.jobvec.size() ; i++)
	{
		for (j=0; j < ord.jobvec[i].optvec.size(); j++)
		{
			csString optstring ; 
			optstring = ord.jobvec[i].partname.Left(2) ; 
			optstring += ":" ; 
			optstring += ord.jobvec[i].optvec[j].optname.c_str() ; 
			if (ord.jobvec[i].optvec[j].optname.c_str() == "CAVITIES")
			{
				csString cavnum ; 
				optstring += cavnum.Format(" %d", ord.jobvec[i].optvec[j].qty) ; 
			}

			if (optstring == "HD:HOLES")
				continue ; 

			csStringListItr is = find(strlist.begin(), strlist.end(), optstring) ; 
			if (is == strlist.end())
			{
				m_listOPTIONS.AddString(optstring.c_str()) ;
				strlist.push_back(optstring) ; 
			}
		}
	}
}

void CCADupdateDlg::OnBnClickedHelp()
{
    AfxMessageBox(
        "The left column of checkboxes indicates what the current order contains as parts\n"
        "You can add or delete parts by setting the state of the checkbox in the second column.\n"
        "Check the CADUpdate.cfg file to verify your setup information, as well you want to\n"
        "make sure that the files referenced in CADUpdate.cfg are valid. A log file called\n"
        "CADupdate_LogFile.txt is generated in the same directory where this executable is\n"
        "launched from.\n\n"
        "The diameter values are in inches whereas the thickness parameters are in millimeters\n"
        "The system will check against the standard stock sizes and find the best matching\n"
        "material size based on the information you enter. If the required material is not in\n"
        "stock, a warning is issued, which you can choose to ignore, or you can increase the\n"
        "stock diameter so that a larger piece of material is consumed from inventory. The\n"
        "diameter and thickness you enter here only relate to what needs to be taken from\n"
        "inventory to create the part and has nothing to do with the actual final finished\n"
        "dimensions of the part (although they will typically be closely related)" ) ; 
}

void CCADupdateDlg::OnEnSetfocusFromEdit()
{
    lastCtrl = IDC_FROM_EDIT ; 
}

void CCADupdateDlg::OnEnSetfocusToEdit()
{
    lastCtrl = IDC_TO_EDIT ; 
}

void CCADupdateDlg::OnEnSetfocusSonumEdit()
{
    lastCtrl = IDC_SONUM_EDIT ; 
}

void CCADupdateDlg::OnEnKillfocusFromEdit()
{
    lastCtrl = 0 ;
}

void CCADupdateDlg::OnEnKillfocusToEdit()
{
    lastCtrl = 0 ;
}

void CCADupdateDlg::OnEnChangeToEdit()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void CCADupdateDlg::OnBnClickedFdrblank()
{
    UpdateData(TRUE) ; 
    if (mFDRTB_Chk)
        mFDRHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedFdrhard()
{
    UpdateData(TRUE) ; 
    if (mFDRHB_Chk)
        mFDRTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedMndblank()
{
    UpdateData(TRUE) ; 
    if (mMNDTB_Chk)
        mMNDHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedMndhard()
{
    UpdateData(TRUE) ; 
    if (mMNDHB_Chk)
        mMNDTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedPltblank()
{
    UpdateData(TRUE) ; 
    if (mPLTTB_Chk)
        mPLTHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedPlthard()
{
    UpdateData(TRUE) ; 
    if (mPLTHB_Chk)
        mPLTTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedBkrblank()
{
    UpdateData(TRUE) ; 
    if (mBKRTB_Chk)
        mBKRHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedBkrhard()
{
    UpdateData(TRUE) ; 
    if (mBKRHB_Chk)
        mBKRTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedBolblank()
{
    UpdateData(TRUE) ; 
    if (mBOLTB_Chk)
        mBOLHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedBolhard()
{
    UpdateData(TRUE) ; 
    if (mBOLHB_Chk)
        mBOLTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedSblblank()
{
    UpdateData(TRUE) ; 
    if (mSBLTB_Chk)
        mSBLHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedSblhard()
{
    UpdateData(TRUE) ; 
    if (mSBLHB_Chk)
        mSBLTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedRngblank()
{
    UpdateData(TRUE) ; 
    if (mRNGTB_Chk)
        mRNGHB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}

void CCADupdateDlg::OnBnClickedHdrhard()
{
    UpdateData(TRUE) ; 
    if (mRNGHB_Chk)
        mRNGTB_Chk = FALSE ; 
    UpdateData(TRUE) ; 
}


void CCADupdateDlg::OnCbnSelchangeFdrsteelCombo()
{
	// TODO: Add your control notification handler code here
}


void CCADupdateDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void CCADupdateDlg::OnEnChangeBkrdiaEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
