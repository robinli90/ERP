#include "stdafx.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "SharedData.h"
#include "UpdateThread.h"

#define TIMER_ID	2357 // Must be non-zero

#define ICON_FILE "iconGreen.ico"

#define TRAYICONID	1//				ID number for the Notify Icon
#define SWM_TRAYMSG	(WM_APP + 1327)	//		the message ID sent to our window

#define SWM_SHOW	(SWM_TRAYMSG + 1)//	show the window
#define SWM_HIDE	(SWM_TRAYMSG + 2)//	hide the window
#define SWM_EXIT	(SWM_TRAYMSG + 3)//	close the window

// Global Variables:
SharedData *pSharedData;
UpdateThread *pUpdateThread;
HINSTANCE		hInst;	// current instance
NOTIFYICONDATA	niData;	// notify icon data
HICON hIcon;
UINT updateTimer;
HWND g_hWndDialog;

#define MIN_INTERVAL_BETWEEN_EMAILS 3600 // seconds
time_t g_lastEmail = 0L;

// Forward declarations of functions included in this code module:
BOOL				InitInstance(HINSTANCE, int);
BOOL				OnInitDialog(HWND hWnd);
void				ShowContextMenu(HWND hWnd);
ULONGLONG			GetDllVersion(LPCTSTR lpszDllName);

INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// Perform application initialization:
	pSharedData = new SharedData();

	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
		}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_STEALTHDIALOG);

	pUpdateThread = new UpdateThread();
	pUpdateThread->Start();

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)||
			!IsDialogMessage(msg.hwnd,&msg) ) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	pUpdateThread->Stop();
	Sleep(1000);

	delete pUpdateThread;

	return (int) msg.wParam;
}

//	Initialize the window and tray icon
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	 // store instance handle and create dialog
	hInst = hInstance;
	HWND hWnd = CreateDialog( hInstance, MAKEINTRESOURCE(IDD_DLG_DIALOG),
		NULL, (DLGPROC)DlgProc );
	if (!hWnd) return FALSE;

	g_hWndDialog = hWnd;

	// Fill the NOTIFYICONDATA structure and call Shell_NotifyIcon
	// zero the structure - note: Some Windows funtions require this but I can't be bothered which ones do and which ones don't.
	ZeroMemory(&niData,sizeof(NOTIFYICONDATA));

	niData.cbSize = 
		// sizes of lowest-version fields
				    sizeof(DWORD) 
					+ sizeof(HWND) 
					+ sizeof(UINT)
					+ sizeof(UINT)
					+ sizeof(UINT)
					+ sizeof(HICON)
					+ (sizeof(TCHAR)*64);

	// the ID number can be anything you choose
	niData.uID = TRAYICONID;

	// state which structure members are valid
	niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	// load the icon and error icon
	hIcon = (HICON)LoadImage(NULL,
					ICON_FILE,
					IMAGE_ICON, 0, 0,
					LR_DEFAULTSIZE|LR_LOADFROMFILE);
	niData.hIcon = hIcon;

	// the window to send messages to and the message to send
	// note:	the message value should be in the range of WM_APP through 0xBFFF
	niData.hWnd = hWnd;
    niData.uCallbackMessage = SWM_TRAYMSG;
	// tooltip message
    lstrcpyn(niData.szTip, _T("Decade Update Utility\nRunning normally"), sizeof(niData.szTip)/sizeof(TCHAR));
	Shell_NotifyIcon(NIM_ADD,&niData);
	return TRUE;
}

BOOL OnInitDialog(HWND hWnd)
{
	HMENU hMenu = GetSystemMenu(hWnd,FALSE);
	if (hMenu)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, IDM_ABOUT, _T("About"));
	}
	HICON hIcon = (HICON)LoadImage(hInst,
		MAKEINTRESOURCE(IDI_STEALTHDLG),
		IMAGE_ICON, 0,0, LR_SHARED|LR_DEFAULTSIZE);
	SendMessage(hWnd,WM_SETICON,ICON_BIG,(LPARAM)hIcon);
	SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);

	// schedule first periodic update NOT IN USE
	//    updateTimer = SetTimer(hWnd, TIMER_ID, UPDATE_INTERVAL, NULL);

	return TRUE;
}

// Name says it all
void ShowContextMenu(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	HMENU hMenu = CreatePopupMenu();
	if(hMenu)
	{
		if( IsWindowVisible(hWnd) )
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Show"));
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

		// note:	must set window to the foreground or the
		//			menu won't disappear when it should
		SetForegroundWindow(hWnd);

		TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
			pt.x, pt.y, 0, hWnd, NULL );
		DestroyMenu(hMenu);
	}
}

// Get dll version number
ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
{
    ULONGLONG ullVersion = 0;
	HINSTANCE hinstDll;
    hinstDll = LoadLibrary(lpszDllName);
    if(hinstDll)
    {
        DLLGETVERSIONPROC pDllGetVersion;
        pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");
        if(pDllGetVersion)
        {
            DLLVERSIONINFO dvi;
            HRESULT hr;
            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);
            hr = (*pDllGetVersion)(&dvi);
        }
        FreeLibrary(hinstDll);
    }
    return ullVersion;
}

// Message handler for the app
INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int tickCounter = 0;
	int wmId, wmEvent;

	switch (message) 
	{
	case SWM_TRAYMSG:
		switch(lParam)
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case WM_RBUTTONDOWN:
		case WM_CONTEXTMENU:
			ShowContextMenu(hWnd);
		}
		break;
	case WM_SYSCOMMAND:
		if((wParam & 0xFFF0) == SC_MINIMIZE)
		{
			ShowWindow(hWnd, SW_HIDE);
			return 1;
		}
		else if(wParam == IDM_ABOUT)
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam); 

		switch (wmId)
		{
		case SWM_SHOW:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case SWM_HIDE:
		case IDOK:
			ShowWindow(hWnd, SW_HIDE);
			break;
		case SWM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		}
		return 1;
	case WM_INITDIALOG:
		return OnInitDialog(hWnd);
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		niData.uFlags = 0;
		Shell_NotifyIcon(NIM_DELETE,&niData);
		PostQuitMessage(0);
		break;
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}