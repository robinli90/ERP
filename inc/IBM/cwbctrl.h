
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Mar 04 17:27:20 2007
 */
/* Compiler settings for C:\spk\sp4681\cwbctrl.odl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __cwbctrl_h__
#define __cwbctrl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSystemListBox_FWD_DEFINED__
#define ___DSystemListBox_FWD_DEFINED__
typedef interface _DSystemListBox _DSystemListBox;
#endif 	/* ___DSystemListBox_FWD_DEFINED__ */


#ifndef ___DSystemListBoxEvents_FWD_DEFINED__
#define ___DSystemListBoxEvents_FWD_DEFINED__
typedef interface _DSystemListBoxEvents _DSystemListBoxEvents;
#endif 	/* ___DSystemListBoxEvents_FWD_DEFINED__ */


#ifndef __cwbSystemListBox_FWD_DEFINED__
#define __cwbSystemListBox_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbSystemListBox cwbSystemListBox;
#else
typedef struct cwbSystemListBox cwbSystemListBox;
#endif /* __cplusplus */

#endif 	/* __cwbSystemListBox_FWD_DEFINED__ */


#ifndef ___DDQEditBox_FWD_DEFINED__
#define ___DDQEditBox_FWD_DEFINED__
typedef interface _DDQEditBox _DDQEditBox;
#endif 	/* ___DDQEditBox_FWD_DEFINED__ */


#ifndef ___DDQEditBoxEvents_FWD_DEFINED__
#define ___DDQEditBoxEvents_FWD_DEFINED__
typedef interface _DDQEditBoxEvents _DDQEditBoxEvents;
#endif 	/* ___DDQEditBoxEvents_FWD_DEFINED__ */


#ifndef __cwbDataQueueTextBox_FWD_DEFINED__
#define __cwbDataQueueTextBox_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbDataQueueTextBox cwbDataQueueTextBox;
#else
typedef struct cwbDataQueueTextBox cwbDataQueueTextBox;
#endif /* __cplusplus */

#endif 	/* __cwbDataQueueTextBox_FWD_DEFINED__ */


#ifndef ___DRmtCmdButton_FWD_DEFINED__
#define ___DRmtCmdButton_FWD_DEFINED__
typedef interface _DRmtCmdButton _DRmtCmdButton;
#endif 	/* ___DRmtCmdButton_FWD_DEFINED__ */


#ifndef ___DRmtCmdButtonEvents_FWD_DEFINED__
#define ___DRmtCmdButtonEvents_FWD_DEFINED__
typedef interface _DRmtCmdButtonEvents _DRmtCmdButtonEvents;
#endif 	/* ___DRmtCmdButtonEvents_FWD_DEFINED__ */


#ifndef __cwbRemoteCommandButton_FWD_DEFINED__
#define __cwbRemoteCommandButton_FWD_DEFINED__

#ifdef __cplusplus
typedef class cwbRemoteCommandButton cwbRemoteCommandButton;
#else
typedef struct cwbRemoteCommandButton cwbRemoteCommandButton;
#endif /* __cplusplus */

#endif 	/* __cwbRemoteCommandButton_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __CwbctrlLib_LIBRARY_DEFINED__
#define __CwbctrlLib_LIBRARY_DEFINED__

/* library CwbctrlLib */
/* [control][helpstring][helpcontext][helpfile][version][uuid] */ 

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("F905FE00-1AC6-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0001
    {	cwbdqSend	= 0,
	cwbdqReceive	= 1
    } 	cwbdqTransferTypeConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("F905FE01-1AC6-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0002
    {	cwbAlignLeft	= 0,
	cwbAlignCenter	= 1,
	cwbAlignRight	= 2
    } 	cwbAlignmentConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("F905FE02-1AC6-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0003
    {	cwbcoConfigured	= 0,
	cwbcoConnected	= 1,
	cwbcoNotConnected	= 2
    } 	cwbcoSystemTypeConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("70BD97C0-3B8B-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0004
    {	cwbBorderNone	= 0,
	cwbBorderFixedSingle	= 1,
	cwbBorderSizable	= 2
    } 	cwbBorderStyleConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("70BD97C1-3B8B-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0005
    {	cwbScrollNone	= 0,
	cwbScrollHorizontal	= 1,
	cwbScrollVertical	= 2,
	cwbScrollBoth	= 3
    } 	cwbScrollBarConstants;

typedef /* [helpcontext][helpstring][uuid] */  DECLSPEC_UUID("70BD97C2-3B8B-11cf-9930-10005A62858B") 
enum __MIDL___MIDL_itf_cwbctrl_0000_0006
    {	cwbAppearFlat	= 0,
	cwbAppear3D	= 1
    } 	cwbAppearanceConstants;


DEFINE_GUID(LIBID_CwbctrlLib,0x0BE8E8CD,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifndef ___DSystemListBox_DISPINTERFACE_DEFINED__
#define ___DSystemListBox_DISPINTERFACE_DEFINED__

/* dispinterface _DSystemListBox */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DSystemListBox,0x0BE8E8C1,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8C1-E2BE-11CE-9930-10005A62858B")
    _DSystemListBox : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSystemListBoxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSystemListBox * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSystemListBox * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSystemListBox * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSystemListBox * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSystemListBox * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSystemListBox * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSystemListBox * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSystemListBoxVtbl;

    interface _DSystemListBox
    {
        CONST_VTBL struct _DSystemListBoxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSystemListBox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DSystemListBox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DSystemListBox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DSystemListBox_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DSystemListBox_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DSystemListBox_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DSystemListBox_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSystemListBox_DISPINTERFACE_DEFINED__ */


#ifndef ___DSystemListBoxEvents_DISPINTERFACE_DEFINED__
#define ___DSystemListBoxEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSystemListBoxEvents */
/* [helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DSystemListBoxEvents,0x0BE8E8C2,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8C2-E2BE-11CE-9930-10005A62858B")
    _DSystemListBoxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSystemListBoxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSystemListBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSystemListBoxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSystemListBoxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSystemListBoxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSystemListBoxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSystemListBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSystemListBoxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSystemListBoxEventsVtbl;

    interface _DSystemListBoxEvents
    {
        CONST_VTBL struct _DSystemListBoxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSystemListBoxEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DSystemListBoxEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DSystemListBoxEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DSystemListBoxEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DSystemListBoxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DSystemListBoxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DSystemListBoxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSystemListBoxEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbSystemListBox,0x0BE8E8C0,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("0BE8E8C0-E2BE-11CE-9930-10005A62858B")
cwbSystemListBox;
#endif

#ifndef ___DDQEditBox_DISPINTERFACE_DEFINED__
#define ___DDQEditBox_DISPINTERFACE_DEFINED__

/* dispinterface _DDQEditBox */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DDQEditBox,0x0BE8E8C6,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8C6-E2BE-11CE-9930-10005A62858B")
    _DDQEditBox : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDQEditBoxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDQEditBox * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDQEditBox * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDQEditBox * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDQEditBox * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDQEditBox * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDQEditBox * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDQEditBox * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDQEditBoxVtbl;

    interface _DDQEditBox
    {
        CONST_VTBL struct _DDQEditBoxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDQEditBox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DDQEditBox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DDQEditBox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DDQEditBox_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DDQEditBox_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DDQEditBox_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DDQEditBox_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDQEditBox_DISPINTERFACE_DEFINED__ */


#ifndef ___DDQEditBoxEvents_DISPINTERFACE_DEFINED__
#define ___DDQEditBoxEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DDQEditBoxEvents */
/* [helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DDQEditBoxEvents,0x0BE8E8C7,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8C7-E2BE-11CE-9930-10005A62858B")
    _DDQEditBoxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDQEditBoxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDQEditBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDQEditBoxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDQEditBoxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDQEditBoxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDQEditBoxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDQEditBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDQEditBoxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDQEditBoxEventsVtbl;

    interface _DDQEditBoxEvents
    {
        CONST_VTBL struct _DDQEditBoxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDQEditBoxEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DDQEditBoxEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DDQEditBoxEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DDQEditBoxEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DDQEditBoxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DDQEditBoxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DDQEditBoxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDQEditBoxEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbDataQueueTextBox,0x0BE8E8C5,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("0BE8E8C5-E2BE-11CE-9930-10005A62858B")
cwbDataQueueTextBox;
#endif

#ifndef ___DRmtCmdButton_DISPINTERFACE_DEFINED__
#define ___DRmtCmdButton_DISPINTERFACE_DEFINED__

/* dispinterface _DRmtCmdButton */
/* [hidden][helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DRmtCmdButton,0x0BE8E8CB,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8CB-E2BE-11CE-9930-10005A62858B")
    _DRmtCmdButton : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DRmtCmdButtonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DRmtCmdButton * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DRmtCmdButton * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DRmtCmdButton * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DRmtCmdButton * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DRmtCmdButton * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DRmtCmdButton * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DRmtCmdButton * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DRmtCmdButtonVtbl;

    interface _DRmtCmdButton
    {
        CONST_VTBL struct _DRmtCmdButtonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DRmtCmdButton_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DRmtCmdButton_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DRmtCmdButton_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DRmtCmdButton_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DRmtCmdButton_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DRmtCmdButton_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DRmtCmdButton_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DRmtCmdButton_DISPINTERFACE_DEFINED__ */


#ifndef ___DRmtCmdButtonEvents_DISPINTERFACE_DEFINED__
#define ___DRmtCmdButtonEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DRmtCmdButtonEvents */
/* [helpstring][helpcontext][uuid] */ 


DEFINE_GUID(DIID__DRmtCmdButtonEvents,0x0BE8E8CC,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BE8E8CC-E2BE-11CE-9930-10005A62858B")
    _DRmtCmdButtonEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DRmtCmdButtonEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DRmtCmdButtonEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DRmtCmdButtonEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DRmtCmdButtonEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DRmtCmdButtonEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DRmtCmdButtonEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DRmtCmdButtonEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DRmtCmdButtonEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DRmtCmdButtonEventsVtbl;

    interface _DRmtCmdButtonEvents
    {
        CONST_VTBL struct _DRmtCmdButtonEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DRmtCmdButtonEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DRmtCmdButtonEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DRmtCmdButtonEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DRmtCmdButtonEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DRmtCmdButtonEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DRmtCmdButtonEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DRmtCmdButtonEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DRmtCmdButtonEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_cwbRemoteCommandButton,0x0BE8E8CA,0xE2BE,0x11CE,0x99,0x30,0x10,0x00,0x5A,0x62,0x85,0x8B);

#ifdef __cplusplus

class DECLSPEC_UUID("0BE8E8CA-E2BE-11CE-9930-10005A62858B")
cwbRemoteCommandButton;
#endif
#endif /* __CwbctrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


