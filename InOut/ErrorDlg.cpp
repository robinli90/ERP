// ErrorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "inout.h"
#include "InOutDlg.h"
#include "ErrorDlg.h"
#include <sstream>
#include "Trace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorDlg dialog


CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CErrorDlg::IDD, pParent)
{
    m_pList1 = m_pList2 = 0 ; 
    nList1 = nList2 = 0 ; 

    //{{AFX_DATA_INIT(CErrorDlg)
    m_nAllRadio = -1;
    m_dSeverity = 0.0;
    m_csNotes = _T("");
    //}}AFX_DATA_INIT
}


CErrorDlg::~CErrorDlg()
{
    delete[] m_pList1 ; 
    delete[] m_pList2 ; 
}

void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CErrorDlg)
    DDX_Control(pDX, IDC_ERREMPNUM, m_editErrEmp);
    DDX_Control(pDX, IDC_SONUM, m_editSONUM);
    DDX_Control(pDX, IDC_EMPNUM, m_editEmpNum);
    DDX_Control(pDX, IDC_ERRORS, m_listErrors);
    DDX_Control(pDX, IDC_ACTIONS, m_listActions);
    DDX_Control(pDX, IDC_PART_EDIT, m_ePart);
    DDX_Radio(pDX, IDC_ALL_RADIO, m_nAllRadio);
    DDX_Text(pDX, IDC_SEVERITY, m_dSeverity);
    DDX_Text(pDX, IDC_NOTE, m_csNotes);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorDlg, CDialog)
    //{{AFX_MSG_MAP(CErrorDlg)
    ON_BN_CLICKED(IDC_ALL_RADIO, OnAllRadio)
    ON_BN_CLICKED(IDC_BKR_RADIO, OnBkrRadio)
    ON_BN_CLICKED(IDC_BOL_RADIO, OnBolRadio)
    ON_BN_CLICKED(IDC_CLEAR, OnClear)
    ON_BN_CLICKED(IDC_CUSTOM_RADIO, OnCustomRadio)
    ON_BN_CLICKED(IDC_DRING_RADIO, OnDringRadio)
    ON_BN_CLICKED(IDC_FDR_RADIO, OnFdrRadio)
    ON_BN_CLICKED(IDC_INS_RADIO, OnInsRadio)
    ON_BN_CLICKED(IDC_MND_RADIO, OnMndRadio)
    ON_BN_CLICKED(IDC_PLT_RADIO, OnPltRadio)
    ON_BN_CLICKED(IDC_SAVE, OnSave)
    ON_BN_CLICKED(IDC_SBOL_RADIO, OnSbolRadio)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



BitMapRec::BitMapRec()
{
    hbmap = 0 ; 
}

BitMapRec::BitMapRec(const BitMapRec &bmr)
{
    name = bmr.name ; 
    hbmap = bmr.hbmap ;
}


BitMapRec &BitMapRec::operator=(const BitMapRec &bmr)
{
    name = bmr.name ; 
    hbmap = bmr.hbmap ;
    return *this ; 
}

int BitMapRec::operator==(BitMapRec &b) 
{
    if (name == b.name) return 1 ; 
    return 0 ; 
}

int BitMapRec::operator<(BitMapRec &b) 
{
    if (name < b.name) return 1 ; 
    return 0 ; 
}


/////////////////////////////////////////////////////////////////////////////
// CErrorDlg message handlers

// Returns ths index of the bitmap in the bmvec array
int CErrorDlg::GetBitMapIDX(CString &bmapname)
{
	size_t n;
    for (n = 0 ; n < bmvec.size() ; n++)
    {
        if (bmapname == bmvec[n].name)
            return (int)n ; 
    }

    BitMapRec bmr ; 
    bmr.name = bmapname ; 
    bmvec.push_back(bmr) ; 

    return (int)n ; 
}

// Defines the bitmaps within the bmvec array
int CErrorDlg::LoadBitmaps()
{
    // Note all the bitmaps must be saved in the same directory as the application
    // is launched from
    size_t i ; 
    for (i = 0; i < bmvec.size(); i++)
    {
        CString bmappath ; 
        bmappath = CString("bitmaps\\") +  bmvec[i].name ;

        bmvec[i].hbmap = static_cast<HBITMAP>(LoadImage(NULL, static_cast<LPCTSTR>(bmappath),
                                                IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) ;
        bmvec[i].bmap.Attach(bmvec[i].hbmap) ; 
    }   

    // Now create the single master image list
    if (!m_imglst.Create(20, 20, ILC_COLOR, 0, 32))
        throw CString("Error creating error image list.");

    for (i = 0 ; i < bmvec.size(); i++)
    {
        // create image list
        m_imglst.Add(&(bmvec[i].bmap), RGB(0, 0, 0)) ;
    }
    return 0 ; 
}

int CErrorDlg::BuildBitMapList()
{
    // Loop through both of the selection lists so that we can 
    // build a vector containing a unique set of bitmaps that 
    // will be required for both lists. Thus we will only 
    // be storing the bitmaps once even though they may appear
    // in multiple lists. 
    int i, idx ; 
    for (i=0; i < nList1; i++)
    {
        idx = GetBitMapIDX(m_pList1[i].bmapname) ; 
        m_pList1[i].bmapidx = idx ; 
    }
    
    for (i=0; i < nList2; i++)
    {
        idx = GetBitMapIDX(m_pList2[i].bmapname) ; 
        m_pList2[i].bmapidx = idx ; 
    }

    // The bmvec now contains the names of the bitmaps required for both lists

    // Load the bitmaps into memory
    LoadBitmaps() ; 


    return 0 ; 
}


int CErrorDlg::LoadList(const char *stationtype, const char *listdes, ListMapRecPtr &precs, int &nrecs)
{
    /*
    select ns.noteid as nid, ns.notesubid as sid, nd.description as desctxt, 
           nc.bmapname as bmap, nd.perfind as perfind
     from d_notestations as ns, d_noteclass as nc, d_notedef as nd
     where stationid = 'DSCN' and listdes = 'E'  and 
           ns.noteid = nd.classid and ns.notesubid = nd.subid and
           ns.noteid = nc.classid	
     order by posidx
    */
    // Load the first list

    std::stringstream ss ;
    ss << "SELECT ns.noteid AS nid, ns.notesubid AS sid, nd.description AS desctxt, " ;
    ss << "nc.bmapname AS bmap, nd.perfind AS perfind " ;
    ss << "FROM d_notestations AS ns, d_noteclass AS nc, d_notedef AS nd " ;
    ss << "WHERE ns.stationid = '" << stationtype << "' " ;
    ss << " AND ns.taskcode = '" << static_cast<LPCTSTR>(m_strErrTask) << "' " ; 
    ss << " AND ns.listdes = '" << listdes << "' AND " ;
    ss << "      ns.noteid = nd.classid and ns.notesubid = nd.subid and " ;
    ss << "      ns.noteid = nc.classid	" ;
    ss << "ORDER BY ns.posidx" ;

    // The item labels are
    //  nid  sid  desctxt  bmap  perfind

    try
    {
        _CommandPtr pCommand;
        pCommand.CreateInstance(__uuidof(Command)) ;
        pCommand->ActiveConnection = m_pConn ;
        pCommand->CommandText = _bstr_t(ss.str().c_str()) ;
        
        _RecordsetPtr pRecordset ;
        pRecordset.CreateInstance(__uuidof(Recordset)) ;
        pRecordset->CursorLocation = adUseClient ;
        pRecordset->Open(static_cast<IDispatch *>(pCommand), vtMissing, adOpenForwardOnly,
                                        adLockReadOnly, adCmdUnknown) ;

        // Allocate memory to save the data list
        nrecs  = pRecordset->GetRecordCount() ;
        precs = new ListMapRec[nrecs + 1] ;

        int n = 0 ; 
        while(!pRecordset->adoEOF && n < nrecs)
        {
            _variant_t var ;
            var = pRecordset->Fields->GetItem("nid")->GetValue() ;
            precs[n].noteid = static_cast<char *>(_bstr_t(var.bstrVal)) ;
            
            var = pRecordset->Fields->GetItem("sid")->GetValue() ;
            precs[n].subid = static_cast<char *>(_bstr_t(var.bstrVal)) ;

            var = pRecordset->Fields->GetItem("desctxt")->GetValue() ;
            precs[n].desctxt = static_cast<char *>(_bstr_t(var.bstrVal)) ;
            precs[n].desctxt.TrimRight() ; 

            var = pRecordset->Fields->GetItem("bmap")->GetValue() ;
            precs[n].bmapname = static_cast<char *>(_bstr_t(var.bstrVal)) ;

            var = pRecordset->Fields->GetItem("perfind")->GetValue() ;
            precs[n].perfind = var.dblVal ;

            n++ ; 
            pRecordset->MoveNext() ;
        }
    }
    catch (_com_error &e)
    {
        g_Trace.Error("CErrroDlg::LoadLists", static_cast<char *>(e.Description())) ;
        return -1 ;
    }

    return 0 ; 

}

int CErrorDlg::InitListCtrl(ListMapRecPtr precs, int nrecs, CListCtrl &lstctrl, CString &listname)
{
    lstctrl.InsertColumn(1, static_cast<LPCTSTR>(listname), LVCFMT_LEFT, 190) ;
    
    // set image list into list control
    lstctrl.SetImageList(&m_imglst, LVSIL_SMALL) ;

    for (int i=0; i < nrecs; i++)
    {
        int nIndex = lstctrl.InsertItem(i, precs[i].desctxt, precs[i].bmapidx);
        lstctrl.SetItemData(i, i);
    }

    return 0 ; 
}

int CErrorDlg::GetLastEmpNum(const char *taskstr)
{
    int empret = 99999 ; 
    if (taskstr == "*")
    {   // Then simply grab the last record
        if (nLastTasks > 0)
            empret = pLastTasks[0].emp ;
    }
    else
    {
        for (int i=0; i < nLastTasks; i++)
        {
            if (pLastTasks[i].task == taskstr)
            {
                empret = pLastTasks[i].emp ; 
                break ; 
            }
        }
    }

    return empret ; 
}

int CErrorDlg::FindErrEmpNum()
{
    int emperr = 99998 ; 
    if (m_strErrTask == "DR")
    {   // Search for the last DD record
        emperr = GetLastEmpNum("DD") ; 
        if (emperr > 99990)
            emperr = GetLastEmpNum("DI") ; 
    }
    else if (m_strErrTask == "SR")
    {   // Search for the last DD record
        emperr = GetLastEmpNum("SH") ; 
        if (emperr > 99990)
            emperr = GetLastEmpNum("SI") ; 
    }
    else if (m_strErrTask == "CR")
    {   // Search for the last DD record
        emperr = GetLastEmpNum("CO") ; 
        if (emperr > 99990)
            emperr = GetLastEmpNum("CI") ; 
    }
    else if (m_strErrTask == "SX")
    {   // Set to no one
        emperr = 99999 ; 
    }
    if (m_strErrTask == "PX")
    {   // Search for the last record
        emperr = 99999 ; // no auto fill for the plant errors. 
    }

    return emperr ; 
}

BOOL CErrorDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    // CWnd
    m_ePart.EnableWindow(FALSE) ; 
    m_nAllRadio = 0 ; 

    m_editSONUM.SetWindowText(static_cast<LPCTSTR>(m_strSONUM)) ; 
    m_editEmpNum.SetWindowText(static_cast<LPCTSTR>(m_strEmpNum)) ; 

    // Work out what the error employee number should be. 
    CString eemp ; 
    eemp.Format("%d", FindErrEmpNum()) ; 
    m_editErrEmp.SetWindowText(static_cast<LPCTSTR>(eemp)) ; 

    // Load the lists based on the station setup type
    m_pList1 = m_pList2 = 0 ; 
    nList1 = nList2 = 0 ; 

    LoadList(static_cast<LPCTSTR>(piod->m_stationType), "E", m_pList1, nList1) ; 
    LoadList(static_cast<LPCTSTR>(piod->m_stationType), "A", m_pList2, nList2) ; 

    // Create the list of necessary bitmaps use by the various lists
    BuildBitMapList() ; 

    // Dump into the list controls
    InitListCtrl(m_pList1, nList1, m_listErrors,  piod->m_csList1Name) ; 
    InitListCtrl(m_pList2, nList2, m_listActions, piod->m_csList2Name) ; 

    UpdateData(FALSE) ; 
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CErrorDlg::OnAllRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnBkrRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnBolRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnClear() 
{
    // Reset all parameters
    m_nAllRadio = 0 ;
    m_dSeverity = 0.0 ;
    m_csNotes = _T("") ;
    m_editEmpNum.SetWindowText(_T("")) ;
    m_editErrEmp.SetWindowText(_T("")) ;
    m_editSONUM.SetWindowText(_T("")) ;
    UpdateData(FALSE) ; 
}

void CErrorDlg::OnCustomRadio() 
{
    m_ePart.EnableWindow(TRUE) ; 
}

void CErrorDlg::OnDringRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnFdrRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnInsRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnMndRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnPltRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

void CErrorDlg::OnSbolRadio() 
{
    m_ePart.EnableWindow(FALSE) ; 
}

// Returns 0 on ok, else an error code
int CErrorDlg::SetPartStr(CString &partstr)
{
    partstr = "G" ; 
    switch(m_nAllRadio)
    {
        case -1 :   // nothing selected
        case 0 :    // All selected
            partstr = "G" ; 
            break ; 
        case 1 :    // FDR
            partstr = "F" ; 
            break ; 
        case 2 :    // MND
            partstr = "M" ; 
            break ; 
        case 3 :    // PLT
            partstr = "P" ; 
            break ; 
        case 4 :    // BKR
            partstr = "B" ; 
            break ; 
        case 5 :    // BOL
            partstr = "O" ; 
            break ; 
        case 6 :    // SBOL
            partstr = "S" ; 
            break ; 
        case 7 :    // DRING
            partstr = "R" ; 
            break ; 
        case 8 :    // INS
            partstr = "I" ; 
            break ; 
        case 9 :    // CUSTOM
        {
            CString csPart ; 
            m_ePart.GetWindowText(csPart) ; 
            if (csPart.GetLength() > 3)
            {
                AfxMessageBox("Max 3 character part code") ; 
                m_ePart.SetFocus() ; 
                return -1 ; 
            }
            partstr = csPart ; 
            break ; 
        }
        default:
            return -2 ; 
    }
    return 0 ; 
}

void CErrorDlg::OnSave() 
{
    // Write record to database
    UpdateData(TRUE) ; 

    // Validate employee number

    CString csEmpNum ; 
    m_editEmpNum.GetWindowText(csEmpNum) ; 
    if (!ValidEmpNum(csEmpNum))
    {
        AfxMessageBox("Invalid employee number.") ;
        m_editEmpNum.SetFocus() ; 
        return ;
    }
    
    // load and validate error employee number
    CString csErrEmp ;
    m_editErrEmp.GetWindowText(csErrEmp) ;
    if (!ValidEmpNum(csErrEmp))
    {
        AfxMessageBox("Invalid responsible employee number.") ;
        m_editErrEmp.SetFocus() ; 
        return ;
    }
    
    // load and validate so number
    char sos[MAXNUMSONUMS][32] ; 
    int nsos ;

    CString csSONUM ;
    m_editSONUM.GetWindowText(csSONUM);
    if (!ValidSONUMs(csSONUM, sos, nsos))
    {
        AfxMessageBox("Invalid SO#.") ;
        m_editSONUM.SetFocus() ;
        return ;
    }

    CString csPart ; 
    if (SetPartStr(csPart))
        return ; // an error occured

    // load and validate errors types

    int nList1 ; 
    CString list1id[5], list1subid[5] ; 
    POSITION poserr = m_listErrors.GetFirstSelectedItemPosition();
    if (poserr == NULL)
    { 
        AfxMessageBox("Please select an error type.");
        m_listErrors.SetFocus();
        return;
    }
    else
    {
        nList1 = 0 ; 
        while (poserr && nList1 < 5)
        {
            int nItem = m_listErrors.GetNextSelectedItem(poserr) ;
            // This index gives the offset into the m_pList1 ListMapRec array
            list1id[nList1]    = m_pList1[nItem].noteid ;
            list1subid[nList1] = m_pList1[nItem].subid ;
            nList1++ ;
        }
    }

    CString list2id, list2subid ; 
    POSITION posaction = m_listActions.GetFirstSelectedItemPosition();
    if (posaction == NULL)
    { 
        list2id    = "NONE" ;
        list2subid = "NONE" ;
    }
    else
    {
        int nItem = m_listActions.GetNextSelectedItem(posaction) ;
        // This index gives the offset into the m_pList1 ListMapRec array
        list2id    = m_pList2[nItem].noteid ; 
        list2subid = m_pList2[nItem].subid ; 
    }
    
    if (!piod->m_bBypassDB)
    {
        // **********************************************
        // Field names in d_notes in order
        // ordernumber, notetime, empnum, refempnum, part
        // cost, noteid, notesubid, actionid, actionsubid,
        // otherid, othersubid, note, taskcode
        // **********************************************

        m_csNotes.TrimLeft() ;
        m_csNotes.TrimRight() ;
        // Strip ' chars from the note since this badly mangles the SQL query string

        int i = 0 ; 
        while (i < m_csNotes.GetLength())
        {
            if (m_csNotes[i] == '\'') 
            {
                m_csNotes = m_csNotes.Left(i) + m_csNotes.Mid(i+1) ; 
            }
            else
            {
                i++ ; 
            }
        }

        if (m_csNotes.GetLength() == 0)
            m_csNotes = " " ; 

        // Create one record for each shop order number
        for (i=0; i < nsos; i++)
        {
            std::stringstream ss;
            ss << "INSERT INTO d_notes (ordernumber, notetime, empnum, refempnum, part, " ;
            ss << "     cost, noteid, notesubid, note2, notesub2, note3, notesub3, note4, notesub4, " ;
            ss << "     note5, notesub5, actionid, actionsubid, otherid, othersubid, note, taskcode) VALUES (" ;
            ss << Exco100kMapSONUM(sos[i]) << ", GETDATE(), " << static_cast<LPCTSTR>(csEmpNum) << ", " ;
            ss << static_cast<LPCTSTR>(csErrEmp) << ", '" << static_cast<LPCTSTR>(csPart) << "', " << m_dSeverity << ", " ; 
            ss << "'" << static_cast<LPCTSTR>(list1id[0]) << "', '" << static_cast<LPCTSTR>(list1subid[0]) << "', " ;
            ss << "'" << static_cast<LPCTSTR>(list1id[1]) << "', '" << static_cast<LPCTSTR>(list1subid[1]) << "', " ;
            ss << "'" << static_cast<LPCTSTR>(list1id[2]) << "', '" << static_cast<LPCTSTR>(list1subid[2]) << "', " ;
            ss << "'" << static_cast<LPCTSTR>(list1id[3]) << "', '" << static_cast<LPCTSTR>(list1subid[3]) << "', " ;
            ss << "'" << static_cast<LPCTSTR>(list1id[4]) << "', '" << static_cast<LPCTSTR>(list1subid[4]) << "', " ;
            ss << "'" << static_cast<LPCTSTR>(list2id) << "', '" << static_cast<LPCTSTR>(list2subid) << "', "  ;
            ss << "'NONE', 'NONE', " ;
            ss << "'" << static_cast<LPCTSTR>(m_csNotes) << "', '" << static_cast<LPCTSTR>(m_strErrTask) << "'" ;
            ss << ")";
        
            try
            {
                m_pConn->Execute(_bstr_t(ss.str().c_str()), NULL, adCmdText);
            }
            catch (_com_error &e)
            {
                FILE *fpqry = fopen("c:\\qryerr.txt", "w") ;
                fprintf(fpqry, "%s\n", ss.str().c_str()) ;
                fclose(fpqry) ;

                g_Trace.Error("CInOutDlg::ProcessTask 1", static_cast<char *>(e.Description()));
                FILE *fp = fopen("InOutErr.log", "at") ; 
                fprintf(fp, "INSERT INTO error: %s\n", static_cast<char *>(e.Description())) ; 
                fclose(fp) ; 
                MessageBox("Error writing error. Please try again.");
                return;
            }
        }
    }
    
    // AfxMessageBox("Saved.");
    saved = 1 ; 
    
    PostMessage(WM_CLOSE) ; 
}

