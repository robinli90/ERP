/********************************************************************/
/* Copyright = 5722-XE1 (C) Copyright IBM Corp 1994, 2005.          */
/*  All rights reserved.                                            */
/*  Licensed Material - Program property of IBM                     */
/*  Refer to copyright instructions form number G120-2083.          */
/********************************************************************/
//********************************************************************
//
// File:
//   cwba4hyf.h
//
// Purpose:
//   Defines IBM COM interfaces that are used to implement iSeries
//   Navigator plug-ins.
//
//      IA4HierarchyFolder  Provides a means of adding additional 
//                          folders to the iSeries Navigator 
//                          object hierarchy.
//
//      IA4PropSheetNotify  Supplies additional notifications needed
//                          when adding property pages to one of the 
//                          property sheets for the Users and Groups
//                          component of iSeries Navigator.
//
//      IA4SortingHierarchyFolder
//                          Indicates that an IA4HierarchyFolder
//                          implementation supports the sorting of items
//                          in an iSeries Navigator folder.
//
//      IA4TasksManager     Used to add tasks to a task view for an
//                          object in the iSeries Navigator hierarchy.
//
//      IA4PublicObjectHierarchyFolder
//                          Indicates that an IA4HierarchyFolder
//                          implementation externalizes a representation
//                          of a system resource for use by other components.
//
//      IA4FilteringHierarchyFolder
//                          Indicates that an IA4HierarchyFolder
//                          implementation supports filtering of a list
//                          through specification of predefined include
//                          criteria.
//
// For more information, browse the  iSeries Information Center and
// Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//********************************************************************

#ifndef _CWBA4HYF_H_
#define _CWBA4HYF_H_

/////////////////////////////////////////////////////////////////////////////
// Define the interface IDs

// {BB8F7360-DB33-11d0-82BD-08005AA74F5C}
static const GUID IID_IA4HierarchyFolder = 
{ 0xbb8f7360, 0xdb33, 0x11d0, { 0x82, 0xbd, 0x8, 0x0, 0x5a, 0xa7, 0x4f, 0x5c } };

// {63815F56-BC01-4586-8E76-F9624C36D048}
static const GUID IID_IA4HierarchyFolderW = 
{ 0x63815f56, 0xbc01, 0x4586, { 0x8e, 0x76, 0xf9, 0x62, 0x4c, 0x36, 0xd0, 0x48 } };

// {DD77E420-F7A9-11d0-82BD-08005AA74F5C}
static const GUID IID_IA4PropSheetNotify = 
{ 0xdd77e420, 0xf7a9, 0x11d0, { 0x82, 0xbd, 0x8, 0x0, 0x5a, 0xa7, 0x4f, 0x5c } };

// {FDFE4B3D-AE20-493c-AE3B-D98C42748299}
static const GUID IID_IA4PropSheetNotifyW = 
{ 0xfdfe4b3d, 0xae20, 0x493c, { 0xae, 0x3b, 0xd9, 0x8c, 0x42, 0x74, 0x82, 0x99 } };

// {354191F0-0E57-11d3-912F-002035AE927B}
static const GUID IID_IA4SortingHierarchyFolder = 
{ 0x354191f0, 0xe57, 0x11d3, { 0x91, 0x2f, 0x0, 0x20, 0x35, 0xae, 0x92, 0x7b } };

// {7B97B861-541F-11d3-8DC0-002035C01242}
static const GUID IID_IA4TasksManager = 
{ 0x7b97b861, 0x541f, 0x11d3, { 0x8d, 0xc0, 0x0, 0x20, 0x35, 0xc0, 0x12, 0x42 } };

// {853C682A-1179-47eb-8BA7-C32F8617033E}
static const GUID IID_IA4TasksManagerW = 
{ 0x853c682a, 0x1179, 0x47eb, { 0x8b, 0xa7, 0xc3, 0x2f, 0x86, 0x17, 0x3, 0x3e } };

// {ED9DF108-ABFD-11d3-9173-002035AE927B}
static const GUID IID_IA4PublicObjectHierarchyFolder = 
{ 0xed9df108, 0xabfd, 0x11d3, { 0x91, 0x73, 0x0, 0x20, 0x35, 0xae, 0x92, 0x7b } };

// {4F66615D-3821-4cb4-ABED-817751B750B0}
static const GUID IID_IA4PublicObjectHierarchyFolderW = 
{ 0x4f66615d, 0x3821, 0x4cb4, { 0xab, 0xed, 0x81, 0x77, 0x51, 0xb7, 0x50, 0xb0 } };

// {B42658D8-F502-11d3-9189-002035AE927B}
static const GUID IID_IA4ListObject = 
{ 0xb42658d8, 0xf502, 0x11d3, { 0x91, 0x89, 0x0, 0x20, 0x35, 0xae, 0x92, 0x7b } };

// {04C0AE0F-7C4E-4f63-A8AD-A9DF9EFCBAB5}
static const GUID IID_IA4ListObjectW = 
{ 0x4c0ae0f, 0x7c4e, 0x4f63, { 0xa8, 0xad, 0xa9, 0xdf, 0x9e, 0xfc, 0xba, 0xb5 } };

// {3D20CF70-B2F9-11d3-9173-002035AE927B}
static const GUID IID_IA4FilteringHierarchyFolder = 
{ 0x3d20cf70, 0xb2f9, 0x11d3, { 0x91, 0x73, 0x0, 0x20, 0x35, 0xae, 0x92, 0x7b } };

// {CC6ED68F-85AC-4ff1-9851-CF3AE28D17D1}
static const GUID IID_IA4FilteringHierarchyFolderW = 
{ 0xcc6ed68f, 0x85ac, 0x4ff1, { 0x98, 0x51, 0xcf, 0x3a, 0xe2, 0x8d, 0x17, 0xd1 } };

#ifdef UNICODE
#define IID_IA4HierarchyFolder              IID_IA4HierarchyFolderW
#define IID_IA4PropSheetNotify              IID_IA4PropSheetNotifyW
#define IID_IA4TasksManager                 IID_IA4TasksManagerW
#define IID_IA4PublicObjectHierarchyFolder  IID_IA4PublicObjectHierarchyFolderW
#define IID_IA4ListObject                   IID_IA4ListObjectW
#define IID_IA4FilteringHierarchyFolder     IID_IA4FilteringHierarchyFolderW
#endif

//*****************************************************************************
// IA4HierarchyFolder
// ==================
// The IA4HierarchyFolder interface is used to add additional folders to the
// iSeries Navigator object hierarchy.  Folders may be inserted under the
// following parent folders:
//
//      Server
//      Basic Operations
//      Work Management
//      Configuration and Service
//      Network
//      Network Servers
//      Security
//      Users and Groups
//      Database
//      File Systems
//      Backup
//      Application Development
//      Management Central
//      Management Central Task Activity
//      Management Central Scheduled Tasks
//      Management Central Definitions
//      Management Central Monitors
//      Management Central Configuration and Service
//      Management Central Extreme Support
//
// The iSeries Navigator learns of the existence of an IA4HierarchyFolder
// implementation via registry entries defined for iSeries Navigator
// plug-ins.  For more information, browse the  iSeries Information Center
// and Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4HierarchyFolder::BindToList
//	Returns an instance of IA4HierarchyFolder which corresponds to a particular
//	folder in the iSeries Navigator hierarchy.
//
// IA4HierarchyFolder::DisplayErrorMessage
//	Called to display an error message to the user whenever BindToList returns
//	an error.
//
// IA4HierarchyFolder::Activate
//	Places the IA4HierarchyFolder instance in an activated state.
//
// IA4HierarchyFolder::Deactivate
//	Places the IA4HierarchyFolder instance in a deactivated state.
//
// IA4HierarchyFolder::GetItemCount
//	Returns the total count of objects contained in a particular folder in
//	the iSeries Navigator hierarchy.
//
// IA4HierarchyFolder::ItemAt
//	Returns an SHITEMID (item identifier) structure for the folder object
//	at the specified position in the list of folder contents.
//
// IA4HierarchyFolder::GetAttributesOf
//	Returns the attributes of a folder in the iSeries Navigator hierarchy.
//	The attribute flags are the same as those defined for IShellFolder::GetAttributesOf
//	(see shlobj.h).
//
// IA4HierarchyFolder::GetIconIndexOf
//	Returns the index into the plug-in's resource DLL which may be used to
//	load the icon for the hierarchy folder.
//
// IA4HierarchyFolder::GetColumnInfo
//	Returns an array of structures describing the columns needed to display the
//	contents of a particular folder in details view.
// 
// IA4HierarchyFolder::GetColumnDataItem
//	Returns a data field for a folder or object to be displayed in a column
//	in the list view of iSeries Navigator.
//
// IA4HierarchyFolder::GetToolbarInfo
//	Returns a structure describing the custom toolbar assocated with the
//	specified folder in the iSeries Navigator hierarchy.
//
// IA4HierarchyFolder::Refresh
//	Destroys any cached folder objects and rebuilds the cache using new
//	data obtained from the server.
//
// IA4HierarchyFolder::GetListObject
//	Returns a pointer to the plug-in's proxy object given a fully-qualified
//	object name.
//
// IA4HierarchyFolder::ProcessTerminating
//	Called when the user closes the iSeries Navigator window.  Provides
//	the plug-in with an opportunity to save persistent data.
//
//*****************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Define delimiters used to construct an iSeries Navigator item identifier

#define HYF_TYPE_MARKER    _T('\x01')
#define HYF_INDEX_MARKER   _T('\x02')

/////////////////////////////////////////////////////////////////////////////
// Additional flags defined by iSeries Navigator for IContextMenu::QueryContextMenu

#define UNITY_CMF_CUSTOM      0x00010000        // Return the custom menu items
#define UNITY_CMF_NEW         0x00020000        // Return the New menu items
#define UNITY_CMF_STANDARD    0x00040000        // Return the supported standard items
#define UNITY_CMF_OPTIONS     0x00080000        // Report on items in the Options pulldown
#define UNITY_CMF_VIEWMENU    0x00400000        // View menu is being processed
#define UNITY_CMF_FILEMENU    0x00800000        // File menu is being processed

#define A4HYF_INFO_PROPERTIESADDED	0x40000000L		// OR'd with HRESULT to indicate
													// that plug-in has added its own
													// 'Properties' menu item

#define A4HYF_GAO_HASTASKPAD        0x00000008L     // OR'd with IShellFolder::GetAttributesOf
                                                    // flags to indicate that the folder has a 
                                                    // taskpad.

#define A4HYF_GAO_AUTOEXPAND        0x00000200L     // OR'd with IShellFolder::GetAttributesOf
                                                    // flags to indicate that a folder should
                                                    // should be expanded initially.

#define A4HYF_GAO_PREFILTERING      0x00000400L     // OR'd with IShellFolder::GetAttributesOf
                                                    // flags to indicate that the folder permits
                                                    // filtering before the list is enumerated.

/////////////////////////////////////////////////////////////////////////////
// Define the A4hyfColumnInfo struct for GetColumnInfo

struct A4hyfColumnItem {
	char	szText[160];	// Translated NLS string for column heading
	UINT	uWidth;			// Default width in characters
	LPARAM	lParam;			// Application-defined value which is
							// returned on GetColumnDataItem
};
typedef A4hyfColumnItem * LPA4HYFCOLUMNITEM;
typedef const A4hyfColumnItem * LPCA4HYFCOLUMNITEM;

struct A4hyfColumnItemW {
	wchar_t	szText[160];	// Translated NLS string for column heading
	UINT	uWidth;			// Default width in characters
	LPARAM	lParam;			// Application-defined value which is
							// returned on GetColumnDataItem
};
typedef A4hyfColumnItemW * LPA4HYFCOLUMNITEMW;
typedef const A4hyfColumnItemW * LPCA4HYFCOLUMNITEMW;

#ifdef UNICODE
#define A4hyfColumnItem     A4hyfColumnItemW
#define LPA4HYFCOLUMNITEM   LPA4HYFCOLUMNITEMW
#define LPCA4HYFCOLUMNITEM  LPCA4HYFCOLUMNITEMW
#endif

struct A4hyfColumnItemEx {
    char    szText[160];    // Translated NLS string for column heading
    UINT    uWidth;         // Default width in characters
    LPARAM  lParam;         // Application-defined value which is
                            // returned on GetColumnDataItem
    int     nAlignment;     // text alignment LVCFMT_LEFT, LVCFMT_RIGHT, or LVCFMT_CENTER
};
typedef A4hyfColumnItemEx * LPA4HYFCOLUMNITEMEX;
typedef const A4hyfColumnItemEx * LPCA4HYFCOLUMNITEMEX;

struct A4hyfColumnItemExW {
    wchar_t szText[160];    // Translated NLS string for column heading
    UINT    uWidth;         // Default width in characters
    LPARAM  lParam;         // Application-defined value which is
                            // returned on GetColumnDataItem
    int     nAlignment;     // text alignment LVCFMT_LEFT, LVCFMT_RIGHT, or LVCFMT_CENTER
};
typedef A4hyfColumnItemExW * LPA4HYFCOLUMNITEMEXW;
typedef const A4hyfColumnItemExW * LPCA4HYFCOLUMNITEMEXW;

#ifdef UNICODE
#define A4hyfColumnItemEx       A4hyfColumnItemExW
#define LPA4HYFCOLUMNITEMEX     LPA4HYFCOLUMNITEMEXW
#define LPCA4HYFCOLUMNITEMEX    LPCA4HYFCOLUMNITEMEXW
#endif

struct A4hyfColumnItemEx2 {
   char    szText[512];    // Translated NLS string for column heading
   UINT    uWidth;         // Default width in characters
   LPARAM  lParam;         // Application-defined value which is
                           // returned on GetColumnDataItem
   int     nAlignment;     // text alignment LVCFMT_LEFT, LVCFMT_RIGHT, or LVCFMT_CENTER
   UINT    uLines;         // Number of lines to display in the column heading
   HBITMAP hBitmap;        // Bitmap to display in the column heading
};
typedef A4hyfColumnItemEx2 * LPA4HYFCOLUMNITEMEX2;
typedef const A4hyfColumnItemEx2 * LPCA4HYFCOLUMNITEMEX2;

struct A4hyfColumnItemEx2W {
   wchar_t szText[512];    // Translated NLS string for column heading
   UINT    uWidth;         // Default width in characters
   LPARAM  lParam;         // Application-defined value which is
                           // returned on GetColumnDataItem
   int     nAlignment;     // text alignment LVCFMT_LEFT, LVCFMT_RIGHT, or LVCFMT_CENTER
   UINT    uLines;         // Number of lines to display in the column heading
   HBITMAP hBitmap;        // Bitmap to display in the column heading
};
typedef A4hyfColumnItemEx2W * LPA4HYFCOLUMNITEMEX2W;
typedef const A4hyfColumnItemEx2W * LPCA4HYFCOLUMNITEMEX2W;

#ifdef UNICODE
#define A4hyfColumnItemEx2      A4hyfColumnItemEx2W
#define LPA4HYFCOLUMNITEMEX2    LPA4HYFCOLUMNITEMEX2W
#define LPCA4HYFCOLUMNITEMEX2   LPCA4HYFCOLUMNITEMEX2W
#endif

struct A4hyfColumnInfo {
   UINT                 nSize;            // Size in bytes of this structure
   UINT                 nColumnCount;     // Count of column items in the array
   LPA4HYFCOLUMNITEM    lpColumnItems;    // Array of A4hyfColumnItem or NULL
   LPA4HYFCOLUMNITEMEX  lpColumnItemsEx;  // Array of A4hyfColumnItemEx or NULL
   LPA4HYFCOLUMNITEMEX2 lpColumnItemsEx2; // Array of A4hyfColumnItemEx2 or NULL.
};
typedef A4hyfColumnInfo * LPA4HYFCOLUMNINFO;
typedef const A4hyfColumnInfo * LPCA4HYFCOLUMNINFO;


/////////////////////////////////////////////////////////////////////////////
// Define the A4hyfToolbarInfo struct for GetToolbarInfo

struct A4hyfToolbarInfo {
	UINT		nItemCount;		// Count of TBBUTTON array elements
	LPCTBBUTTON	tbItems;		// Array of TBBUTTON items
	UINT		uBitmapID;		// Resource ID of toolbar bitmap
	HINSTANCE	hInstance;		// Instance handle of resource DLL
};
typedef A4hyfToolbarInfo * LPA4HYFTOOLBARINFO;
typedef const A4hyfToolbarInfo * LPCA4HYFTOOLBARINFO;

/////////////////////////////////////////////////////////////////////////////
// Define HRESULT codes for IA4HierarchyFolder
//  - The low-order 16 bits define the return code.
//  - The high-order 16 bits must not change.

//
// MessageId: A4HYF_E_LISTDATAERROR
//
// MessageText:
//
//  An error occurred attempting to retrieve the list of objects 
//  for a folder in the hierarchy.
//
#define A4HYF_E_LISTDATAERROR			_HRESULT_TYPEDEF_(0xA0040001L)

//
// MessageId: A4HYF_OK_LISTCOMPLETE
//
// MessageText:
//
//  The list of objects has been completely constructed.
//
#define A4HYF_OK_LISTCOMPLETE			_HRESULT_TYPEDEF_(0x20040002L)

//
// MessageId: A4HYF_OK_LISTNOTCOMPLETE
//
// MessageText:
//
//  The list of objects is only partially constructed.
//
#define A4HYF_OK_LISTNOTCOMPLETE		_HRESULT_TYPEDEF_(0x20040003L)

/////////////////////////////////////////////////////////////////////////////
// Declare the IA4HierarchyFolder interface

#undef INTERFACE
#define INTERFACE IA4HierarchyFolder

DECLARE_INTERFACE_(IA4HierarchyFolder, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4HierarchyFolder methods
	STDMETHOD(BindToList)(THIS_ HWND hwndOwner, LPCITEMIDLIST pidlFolder, REFIID riid, LPVOID* ppvOut) PURE;
	STDMETHOD(DisplayErrorMessage)(THIS) PURE;

	STDMETHOD(Activate)(THIS) PURE;
	STDMETHOD(Deactivate)(THIS) PURE;

	STDMETHOD(GetItemCount)(THIS_ ULONG* pCount) PURE;
	STDMETHOD(ItemAt)(THIS_ ULONG ulIndex, LPITEMIDLIST* ppidl) PURE;
	STDMETHOD(GetAttributesOf)(THIS_ LPCITEMIDLIST pidl, ULONG* rgfInOut) PURE;
	STDMETHOD(GetIconIndexOf)(THIS_ LPCITEMIDLIST pidl, UINT pwFlags, int* piIndex) PURE;

	STDMETHOD(GetColumnInfo)(THIS_ LPVOID* ppvInfo) PURE;
	STDMETHOD(GetColumnDataItem)(THIS_ LPCITEMIDLIST pidl, LPARAM lParam,
		char * pszColumnData, UINT cchMax) PURE;

	STDMETHOD(GetToolbarInfo)(THIS_ LPCITEMIDLIST pidl, LPVOID* ppvInfo) PURE;

	STDMETHOD(Refresh)(THIS) PURE;

	STDMETHOD(GetListObject)(THIS_ const char * pszFileName, LPVOID* ppvObj) PURE;

	STDMETHOD(ProcessTerminating)(THIS) PURE;
};

typedef IA4HierarchyFolder* LPA4HIERARCHYFOLDER;
typedef const IA4HierarchyFolder* LPCA4HIERARCHYFOLDER;

#undef INTERFACE
#define INTERFACE IA4HierarchyFolderW

DECLARE_INTERFACE_(IA4HierarchyFolderW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4HierarchyFolder methods
	STDMETHOD(BindToList)(THIS_ HWND hwndOwner, LPCITEMIDLIST pidlFolder, REFIID riid, LPVOID* ppvOut) PURE;
	STDMETHOD(DisplayErrorMessage)(THIS) PURE;

	STDMETHOD(Activate)(THIS) PURE;
	STDMETHOD(Deactivate)(THIS) PURE;

	STDMETHOD(GetItemCount)(THIS_ ULONG* pCount) PURE;
	STDMETHOD(ItemAt)(THIS_ ULONG ulIndex, LPITEMIDLIST* ppidl) PURE;
	STDMETHOD(GetAttributesOf)(THIS_ LPCITEMIDLIST pidl, ULONG* rgfInOut) PURE;
	STDMETHOD(GetIconIndexOf)(THIS_ LPCITEMIDLIST pidl, UINT pwFlags, int* piIndex) PURE;

	STDMETHOD(GetColumnInfo)(THIS_ LPVOID* ppvInfo) PURE;
	STDMETHOD(GetColumnDataItem)(THIS_ LPCITEMIDLIST pidl, LPARAM lParam,
		LPWSTR pszColumnData, UINT cchMax) PURE;

	STDMETHOD(GetToolbarInfo)(THIS_ LPCITEMIDLIST pidl, LPVOID* ppvInfo) PURE;

	STDMETHOD(Refresh)(THIS) PURE;

	STDMETHOD(GetListObject)(THIS_ LPCWSTR pszFileName, LPVOID* ppvObj) PURE;

	STDMETHOD(ProcessTerminating)(THIS) PURE;
};

typedef IA4HierarchyFolderW* LPA4HIERARCHYFOLDERW;
typedef const IA4HierarchyFolderW* LPCA4HIERARCHYFOLDERW;

#ifdef UNICODE
#define IA4HierarchyFolder      IA4HierarchyFolderW
#define LPA4HIERARCHYFOLDER     LPA4HIERARCHYFOLDERW
#define LPCA4HIERARCHYFOLDER    LPCA4HIERARCHYFOLDERW
#endif


//*****************************************************************************
// IA4PropSheetNotify
// ==================
// The IA4PropSheetNotify interface is used to supply the implementation of
// IShellPropSheetExt with notifications that are needed when adding additional
// property pages to one of the Users and Groups property sheets.  These 
// notifications are necessary because the Users and Groups property sheets
// may be created and destroyed many times before the user clicks the OK
// button on the main Properties dialog.   IA4PropSheetNotify provides a
// way to inform the IShellPropSheetExt implementation when changes made
// by the user should be saved.
// 
// The iSeries Navigator learns of the existence of an IA4PropSheetNotify
// implementation via registry entries defined for iSeries Navigator
// plug-ins.  For more information, browse the iSeries Information Center
// and Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4PropSheetNotify::InformUserState
//	Called immediately following creation of the IShellPropSheetExt instance
//	to inform the implementation whether this user already exists on the
//	server, or whether the user is being created for the first time.
//
// IA4PropSheetNotify::ApplyChanges
//	Called to inform the implementation that the user's data should now
//	be saved.
//
// IA4HierarchyFolder::GetErrorMessage
//	Called when errors are returned on ApplyChanges to retrieve the 
//	implementation's error message text.
//
//*****************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Define flags for InformUserState

#define IUS_USEREXISTS			0x0001	// User already exists on the server
#define IUS_NEWUSER             0x0002	// User to be created
#define IUS_NEWUSERBASEDON		0x0003	// User to be created based on an existing user

/////////////////////////////////////////////////////////////////////////////
// Declare the IA4PropSheetNotify interface

#undef INTERFACE
#define INTERFACE IA4PropSheetNotify

DECLARE_INTERFACE_(IA4PropSheetNotify, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4PropSheetNotify methods
	STDMETHOD(InformUserState)(THIS_ UINT wUserState) PURE;
	STDMETHOD(ApplyChanges)(THIS_ const char * pszNewUserName) PURE;
	STDMETHOD(GetErrorMessage)(THIS_ char * pszErrMsg, UINT cchMax) PURE;
};

typedef IA4PropSheetNotify* LPA4PROPSHEETNOTIFY;
typedef const IA4PropSheetNotify* LPCA4PROPSHEETNOTIFY;

#undef INTERFACE
#define INTERFACE IA4PropSheetNotifyW

DECLARE_INTERFACE_(IA4PropSheetNotifyW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4PropSheetNotify methods
	STDMETHOD(InformUserState)(THIS_ UINT wUserState) PURE;
	STDMETHOD(ApplyChanges)(THIS_ LPCWSTR pszNewUserName) PURE;
	STDMETHOD(GetErrorMessage)(THIS_ LPWSTR pszErrMsg, UINT cchMax) PURE;
};

typedef IA4PropSheetNotifyW* LPA4PROPSHEETNOTIFYW;
typedef const IA4PropSheetNotifyW* LPCA4PROPSHEETNOTIFYW;

#ifdef UNICODE
#define IA4PropSheetNotify      IA4PropSheetNotifyW
#define LPA4PROPSHEETNOTIFY     LPA4PROPSHEETNOTIFYW
#define LPCA4PROPSHEETNOTIFY    LPCA4PROPSHEETNOTIFYW
#endif

//*****************************************************************************
// IA4SortingHierarchyFolder
// =========================
// An interface which indicates that an IA4HierarchyFolder implementation
// supports the sorting of items in an iSeries Navigator folder.
// When a user requests that the list be resorted on the data in a designated
// list view column, the IA4SortingHierarchyFolder implementation is notified by
// calling SortOnColumn with an indication of which column has been selected
// by the user, and whether the sort order should be ascending or descending.
// On return from this method the user interface will refresh the list, causing
// the items to be displayed in the new order.
//
// This interface does not support sorting on multiple table columns.
// 
// iSeries Navigator learns of the existence of an IA4SortingHierarchyFolder
// implementation by querying for the interface on an existing reference to
// an instance of IA4HierarchyFolder. For more information, browse the 
// iSeries Information Center and Technical Studio web sites at
// http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4SortingHierarchyFolder::IsSortingEnabled
// Indicates whether sorting is enabled for a folder. This method is called
// when the user initially selects a container of system objects to determine
// whether the list view column headers should be enabled for sorting.
//
// IA4SortingHierarchyFolder::SortOnColumn
// Sorts the list on the specified list view column. This method is called
// when the user has clicked on a list view column header. The
// IA4SortingHierarchyFolder implementation should update its state information
// indicating the order in which items are to be sorted. On return from this
// method, iSeries Navigator will immediately refresh the list by calling
// IA4HierarchyFolder->Refresh().
//
//*****************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Declare the IA4SortingHierarchyFolder interface

#undef INTERFACE
#define INTERFACE IA4SortingHierarchyFolder

DECLARE_INTERFACE_(IA4SortingHierarchyFolder, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4SortingHierarchyFolder methods
	STDMETHOD(IsSortingEnabled)(THIS) PURE;
	STDMETHOD(SortOnColumn)(THIS_ UINT columnID, UINT sortOrder) PURE;
};

typedef IA4SortingHierarchyFolder* LPA4SORTINGHIERARCHYFOLDER;
typedef const IA4SortingHierarchyFolder* LPCA4SORTINGHIERARCHYFOLDER;


//*****************************************************************************
// IA4TasksManager
// ===============
// The IA4TasksManager interface is used to add additional tasks to a task
// view for an object in the iSeries Navigator hierarchy.
//
// The iSeries Navigator learns of the existence of an IA4TasksManager
// implementation via registry entries defined for iSeries Navigator
// plug-ins.  For more information, browse the iSeries Information Center
// and Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4TasksManager::QueryTasks
//  Returns a list of tasks supported by this object. This method is called
//  when the user interface needs to display the available tasks in the task
//  view. IShellExtInit::Initialize is invoked prior to calling this method.
//
// IA4TasksManager::TaskSelected
//  Informs the IA4TasksManager implementation that a particular task has been 
//  selected by the user. QueryTasks is always invoked prior to calling this 
//  method.
//
//*****************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Additional flags for IA4TasksManager::QueryTasks

#define A4TASK_CUSTOM		0x00000001	// Return the custom tasks
#define A4TASK_CASCADING    0x00000002      // Return the cascading tasks
#define A4TASK_RELATEDTASKS	0x00000004	// Return the related tasks

/////////////////////////////////////////////////////////////////////////////
// Define the task descriptor struct returned by IA4TasksManager

typedef struct A4TaskDescriptor* LPA4TASKDESCRIPTOR;
typedef const struct A4TaskDescriptor* LPCA4TASKDESCRIPTOR;
struct A4TaskDescriptor {
    LPSTR               szText;     // NLS translated text
    LPSTR               szHelpText; // NLS translated help text
    LPSTR               szVerb;     // language independent verb
    BOOL                bEnabled;   // indicates if task is currently available.
    HICON               hImage;     // handle to image
    INT                 nTaskID;    // task identifier to invoke
    LPA4TASKDESCRIPTOR lpNext;     // next task
    LPA4TASKDESCRIPTOR lpSubTasks; // sub tasks
};

typedef struct A4TaskDescriptorW* LPA4TASKDESCRIPTORW;
typedef const struct A4TaskDescriptorW* LPCA4TASKDESCRIPTORW;
struct A4TaskDescriptorW {
    LPWSTR              szText;     // NLS translated text
    LPWSTR              szHelpText; // NLS translated help text
    LPWSTR              szVerb;     // language independent verb
    BOOL                bEnabled;   // indicates if task is currently available.
    HICON               hImage;     // handle to image
    INT                 nTaskID;    // task identifier to invoke
    LPA4TASKDESCRIPTORW lpNext;     // next task
    LPA4TASKDESCRIPTORW lpSubTasks; // sub tasks
};

#ifdef UNICODE
#define A4TaskDescriptor        A4TaskDescriptorW
#define LPA4TASKDESCRIPTOR      LPA4TASKDESCRIPTORW
#define LPCA4TASKDESCRIPTOR     LPCA4TASKDESCRIPTORW
#endif

////////////////////////////////////////////////////////////////////////////
// Declare the IA4TasksManager interface

#undef INTERFACE
#define INTERFACE IA4TasksManager

DECLARE_INTERFACE_(IA4TasksManager, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4TasksManager methods
	STDMETHOD(QueryTasks)(THIS_ UINT uFlags, LPCSTR lpVerb, LPVOID* ppvTaskDescriptor) PURE;
	STDMETHOD(TaskSelected)(THIS_ UINT uTask, HWND hWnd) PURE; 
    
};
typedef IA4TasksManager* LPA4TASKSMANAGER;
typedef const IA4TasksManager* LPCA4TASKSMANAGER;

#undef INTERFACE
#define INTERFACE IA4TasksManagerW

DECLARE_INTERFACE_(IA4TasksManagerW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4TasksManager methods
	STDMETHOD(QueryTasks)(THIS_ UINT uFlags, LPCWSTR lpVerb, LPVOID* ppvTaskDescriptor) PURE;
	STDMETHOD(TaskSelected)(THIS_ UINT uTask, HWND hWnd) PURE; 
    
};
typedef IA4TasksManagerW* LPA4TASKSMANAGERW;
typedef const IA4TasksManagerW* LPCA4TASKSMANAGERW;

#ifdef UNICODE
#define IA4TasksManager     IA4TasksManagerW
#define LPA4TASKSMANAGER    LPA4TASKSMANAGERW
#define LPCA4TASKSMANAGER   LPCA4TASKSMANAGERW
#endif


//*****************************************************************************
// IA4PublicObjectHierarchyFolder
// ==============================
// The IA4PublicObjectHierarchyFolder interface is implemented by a plug-in
// when it desires to make its list objects available for use by other by other
// plug-ins.  It is assumed that the plug-in developer documents a public class
// or interface for this purpose.
//
// The iSeries Navigator learns of the existence of an IA4PublicObjectHierarchyFolder
// implementation via registry entries defined for iSeries Navigator
// plug-ins.  For more information, browse the iSeries Information Center
// and Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4PublicObjectHierarchyFolder::GetPublicListObject
//	Returns a pointer to the component's public list object given a fully-qualified
//	object name.
//
//*****************************************************************************

////////////////////////////////////////////////////////////////////////////
// Declare the IA4PublicObjectHierarchyFolder interface

#undef INTERFACE
#define INTERFACE IA4PublicObjectHierarchyFolder

DECLARE_INTERFACE_(IA4PublicObjectHierarchyFolder, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4PublicObjectHierarchyFolder methods
	STDMETHOD(GetPublicListObject)(THIS_ const char * pszFileName, LPVOID* ppvObj) PURE;
};
typedef IA4PublicObjectHierarchyFolder* LPA4PUBLICOBJECTHIERARCHYFOLDER;
typedef const IA4PublicObjectHierarchyFolder* LPCA4PUBLICOBJECTHIERARCHYFOLDER;

#undef INTERFACE
#define INTERFACE IA4PublicObjectHierarchyFolderW

DECLARE_INTERFACE_(IA4PublicObjectHierarchyFolderW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4PublicObjectHierarchyFolder methods
	STDMETHOD(GetPublicListObject)(THIS_ LPCWSTR pszFileName, LPVOID* ppvObj) PURE;
};
typedef IA4PublicObjectHierarchyFolderW* LPA4PUBLICOBJECTHIERARCHYFOLDERW;
typedef const IA4PublicObjectHierarchyFolderW* LPCA4PUBLICOBJECTHIERARCHYFOLDERW;

#ifdef UNICODE
#define IA4PublicObjectHierarchyFolder      IA4PublicObjectHierarchyFolderW
#define LPA4PUBLICOBJECTHIERARCHYFOLDER     LPA4PUBLICOBJECTHIERARCHYFOLDERW
#define LPCA4PUBLICOBJECTHIERARCHYFOLDER    LPCA4PUBLICOBJECTHIERARCHYFOLDERW
#endif

//*****************************************************************************
// IA4ListObject
// =============
// The IA4ListObject interface is implemented by IBM components when they
// desire to make list objects available for use by other plug-ins.
// See the description of IA4PublicObjectHierarchyFolder above.
//
// Other plug-ins obtain a pointer to an instance of this interface by calling
// IA4PublicObjectHierarchyFolder::GetPublicListObject and casting the result
// to a pointer to an instance of IA4ListObject. When the instance is no longer
// needed they should release the object by calling IUnknown::Release on the
// IA4ListObject pointer.
//
// For more information, browse the iSeries Information Center and
// Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4ListObject::GetAttributes
//	Returns a list of supported attribute IDs and the type of data
//  associated with each. The returned arrays are allocated in
//  static heap storage - the calling program should not attempt
//  to release this memory.
//
// IA4ListObject::GetValue
//  Given an attribute ID, returns the current value of the attribute.
//  If lpszValue is NULL, the length of the attribute data is returned
//  in cchValue. If lpszValue is non-NULL it is assumed to point to a
//  valid character buffer into which the data will be copied, and
//  whose length is specified in cchValue.
//
//*****************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Define the supported data types for an attribute

#define A4OBJ_TYPE_CHAR     1   // signed char
#define A4OBJ_TYPE_SHORT    2   // short int
#define A4OBJ_TYPE_INT      3   // int
#define A4OBJ_TYPE_FLOAT    4   // float
#define A4OBJ_TYPE_DOUBLE   5   // double
#define A4OBJ_TYPE_STRING   6   // char array
#define A4OBJ_TYPE_BOOL     7   // int
#define A4OBJ_TYPE_BYTES    8   // signed byte array

/////////////////////////////////////////////////////////////////////////////
// Define HRESULT codes for IA4ListObject
//  - The low-order 16 bits define the return code.
//  - The high-order 16 bits must not change.

//
// MessageId: A4OBJ_E_NULL_PARAMETER
//
// MessageText:
//
//  A method parameter was NULL.
//
#define A4OBJ_E_NULL_PARAMETER  			_HRESULT_TYPEDEF_(0xE0050001L)

//
// MessageId: A4OBJ_E_VALUE_NOT_AVAILABLE
//
// MessageText:
//
//  The object is unable to return a value for the specified key.
//
#define A4OBJ_E_VALUE_NOT_AVAILABLE			_HRESULT_TYPEDEF_(0xE0050002L)

//
// MessageId: A4OBJ_OK_BUFFER_TOO_SMALL
//
// MessageText:
//
//  The requested value was too large to fit into the specified
//  character array.
//
#define A4OBJ_OK_BUFFER_TOO_SMALL			_HRESULT_TYPEDEF_(0x20050003L)

////////////////////////////////////////////////////////////////////////////
// Declare the IA4ListObject interface

#undef INTERFACE
#define INTERFACE IA4ListObject

DECLARE_INTERFACE_(IA4ListObject, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IA4ListObject methods
    STDMETHOD(GetAttributes)(THIS_ UINT* lpcAttrs, LPCSTR** lpszKeys, LONG** lpnTypes) PURE;
    STDMETHOD(GetValue)(THIS_ LPCSTR lpszKey, LPSTR lpszValue, UINT* cchValue) PURE;
};
typedef IA4ListObject* LPA4LISTOBJECT;

#undef INTERFACE
#define INTERFACE IA4ListObjectW

DECLARE_INTERFACE_(IA4ListObjectW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IA4ListObject methods
    STDMETHOD(GetAttributes)(THIS_ UINT* lpcAttrs, LPCWSTR** lpszKeys, LONG** lpnTypes) PURE;
    STDMETHOD(GetValue)(THIS_ LPCWSTR lpszKey, LPWSTR lpszValue, UINT* cchValue) PURE;
};
typedef IA4ListObjectW* LPA4LISTOBJECTW;

#ifdef UNICODE
#define IA4ListObject   IA4ListObjectW
#define LPA4LISTOBJECT  LPA4LISTOBJECTW
#endif

//*****************************************************************************
// IA4FilteringHierarchyFolder
// ===========================
// An interface which indicates that an IA4HierarchyFolder implementation
// supports filtering of a list through specification of predefined include
// criteria.
//
// The iSeries Navigator learns of the existence of an IA4FilteringHierarchyFolder
// implementation via registry entries defined for iSeries Navigator
// plug-ins.  For more information, browse the iSeries Information Center
// and Technical Studio web sites at http://www.ibm.com/eserver/iseries/infocenter.
//
// Methods in Vtable Order
// =======================
// IA4FilteringHierarchyFolder::GetFilterDescription
//	Returns a text description of the current include criteria.
//
//*****************************************************************************

////////////////////////////////////////////////////////////////////////////
// Declare the IA4FilteringHierarchyFolder interface

#undef INTERFACE
#define INTERFACE IA4FilteringHierarchyFolder

DECLARE_INTERFACE_(IA4FilteringHierarchyFolder, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4FilteringHierarchyFolder methods
	STDMETHOD(GetFilterDescription)(THIS_ LPSTR lpszDescription, UINT cchMax) PURE;
};
typedef IA4FilteringHierarchyFolder* LPA4FILTERINGHIERARCHYFOLDER;
typedef const IA4FilteringHierarchyFolder* LPCA4FILTERINGHIERARCHYFOLDER;

#undef INTERFACE
#define INTERFACE IA4FilteringHierarchyFolderW

DECLARE_INTERFACE_(IA4FilteringHierarchyFolderW, IUnknown)
{
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;

	// IA4FilteringHierarchyFolder methods
	STDMETHOD(GetFilterDescription)(THIS_ LPWSTR lpszDescription, UINT cchMax) PURE;
};
typedef IA4FilteringHierarchyFolderW* LPA4FILTERINGHIERARCHYFOLDERW;
typedef const IA4FilteringHierarchyFolderW* LPCA4FILTERINGHIERARCHYFOLDERW;

#ifdef UNICODE
#define IA4FilteringHierarchyFolder     IA4FilteringHierarchyFolderW
#define LPA4FILTERINGHIERARCHYFOLDER    LPA4FILTERINGHIERARCHYFOLDERW
#define LPCA4FILTERINGHIERARCHYFOLDER   LPCA4FILTERINGHIERARCHYFOLDERW
#endif

#endif //_CWBA4HYF_H_
