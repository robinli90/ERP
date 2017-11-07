/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jun 17 12:39:48 1997
 */
/* Compiler settings for adtAD400.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __adtAD400_h__
#define __adtAD400_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __AD400Index_FWD_DEFINED__
#define __AD400Index_FWD_DEFINED__
typedef interface AD400Index AD400Index;
#endif 	/* __AD400Index_FWD_DEFINED__ */


#ifndef __IAD400Index_FWD_DEFINED__
#define __IAD400Index_FWD_DEFINED__
typedef interface IAD400Index IAD400Index;
#endif 	/* __IAD400Index_FWD_DEFINED__ */


#ifndef __AD400Connection_FWD_DEFINED__
#define __AD400Connection_FWD_DEFINED__
typedef interface AD400Connection AD400Connection;
#endif 	/* __AD400Connection_FWD_DEFINED__ */


#ifndef __Connection_FWD_DEFINED__
#define __Connection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Connection Connection;
#else
typedef struct Connection Connection;
#endif /* __cplusplus */

#endif 	/* __Connection_FWD_DEFINED__ */


#ifndef __Index_FWD_DEFINED__
#define __Index_FWD_DEFINED__

#ifdef __cplusplus
typedef class Index Index;
#else
typedef struct Index Index;
#endif /* __cplusplus */

#endif 	/* __Index_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "oledb.h"
#include "oleidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __AD400_LIBRARY_DEFINED__
#define __AD400_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: AD400
 * at Tue Jun 17 12:39:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 


typedef /* [v1_enum][helpstring][uuid] */ 
enum ad400SeekEnum
    {	ad400SeekFirstEQ	= 0x1,
	ad400SeekLastEQ	= 0x2,
	ad400SeekGE	= 0x4,
	ad400SeekGT	= 0x8,
	ad400SeekLE	= 0x10,
	ad400SeekLT	= 0x20
    }	ad400SeekEnum;


EXTERN_C const IID LIBID_AD400;

#ifndef __AD400Index_INTERFACE_DEFINED__
#define __AD400Index_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: AD400Index
 * at Tue Jun 17 12:39:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_AD400Index;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("1E3B37A1-C131-11D0-96ED-08005AA4DF58")
    AD400Index : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBookmark( 
            /* [in] */ VARIANT Key,
            /* [in] */ ad400SeekEnum dwSeekOptions,
            /* [retval][out] */ VARIANT __RPC_FAR *pBookmark) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AD400IndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AD400Index __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AD400Index __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AD400Index __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AD400Index __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AD400Index __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AD400Index __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AD400Index __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBookmark )( 
            AD400Index __RPC_FAR * This,
            /* [in] */ VARIANT Key,
            /* [in] */ ad400SeekEnum dwSeekOptions,
            /* [retval][out] */ VARIANT __RPC_FAR *pBookmark);
        
        END_INTERFACE
    } AD400IndexVtbl;

    interface AD400Index
    {
        CONST_VTBL struct AD400IndexVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AD400Index_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AD400Index_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AD400Index_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AD400Index_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AD400Index_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AD400Index_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AD400Index_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AD400Index_GetBookmark(This,Key,dwSeekOptions,pBookmark)	\
    (This)->lpVtbl -> GetBookmark(This,Key,dwSeekOptions,pBookmark)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AD400Index_GetBookmark_Proxy( 
    AD400Index __RPC_FAR * This,
    /* [in] */ VARIANT Key,
    /* [in] */ ad400SeekEnum dwSeekOptions,
    /* [retval][out] */ VARIANT __RPC_FAR *pBookmark);


void __RPC_STUB AD400Index_GetBookmark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AD400Index_INTERFACE_DEFINED__ */


#ifndef __IAD400Index_INTERFACE_DEFINED__
#define __IAD400Index_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAD400Index
 * at Tue Jun 17 12:39:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object][hidden] */ 



EXTERN_C const IID IID_IAD400Index;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("1E3B37A3-C131-11D0-96ED-08005AA4DF58")
    IAD400Index : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRowset( 
            /* [in] */ IRowset __RPC_FAR *pIRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAD400IndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAD400Index __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAD400Index __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAD400Index __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRowset )( 
            IAD400Index __RPC_FAR * This,
            /* [in] */ IRowset __RPC_FAR *pIRowset);
        
        END_INTERFACE
    } IAD400IndexVtbl;

    interface IAD400Index
    {
        CONST_VTBL struct IAD400IndexVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAD400Index_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAD400Index_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAD400Index_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAD400Index_SetRowset(This,pIRowset)	\
    (This)->lpVtbl -> SetRowset(This,pIRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAD400Index_SetRowset_Proxy( 
    IAD400Index __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pIRowset);


void __RPC_STUB IAD400Index_SetRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAD400Index_INTERFACE_DEFINED__ */


#ifndef __AD400Connection_INTERFACE_DEFINED__
#define __AD400Connection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: AD400Connection
 * at Tue Jun 17 12:39:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_AD400Connection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("5AD4A0AE-C0A7-11D0-96ED-08005AA4DF58")
    AD400Connection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR System,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR Password) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenIndex( 
            /* [in] */ BSTR TableName,
            /* [in] */ BSTR IndexName,
            /* [retval][out] */ AD400Index __RPC_FAR *__RPC_FAR *ppAD400Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AD400ConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AD400Connection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AD400Connection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AD400Connection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ BSTR System,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR Password);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenIndex )( 
            AD400Connection __RPC_FAR * This,
            /* [in] */ BSTR TableName,
            /* [in] */ BSTR IndexName,
            /* [retval][out] */ AD400Index __RPC_FAR *__RPC_FAR *ppAD400Index);
        
        END_INTERFACE
    } AD400ConnectionVtbl;

    interface AD400Connection
    {
        CONST_VTBL struct AD400ConnectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AD400Connection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AD400Connection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AD400Connection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AD400Connection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AD400Connection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AD400Connection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AD400Connection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AD400Connection_Open(This,System,UserID,Password)	\
    (This)->lpVtbl -> Open(This,System,UserID,Password)

#define AD400Connection_OpenIndex(This,TableName,IndexName,ppAD400Index)	\
    (This)->lpVtbl -> OpenIndex(This,TableName,IndexName,ppAD400Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AD400Connection_Open_Proxy( 
    AD400Connection __RPC_FAR * This,
    /* [in] */ BSTR System,
    /* [in] */ BSTR UserID,
    /* [in] */ BSTR Password);


void __RPC_STUB AD400Connection_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AD400Connection_OpenIndex_Proxy( 
    AD400Connection __RPC_FAR * This,
    /* [in] */ BSTR TableName,
    /* [in] */ BSTR IndexName,
    /* [retval][out] */ AD400Index __RPC_FAR *__RPC_FAR *ppAD400Index);


void __RPC_STUB AD400Connection_OpenIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AD400Connection_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Connection;

class DECLSPEC_UUID("5AD4A0AF-C0A7-11D0-96ED-08005AA4DF58")
zz400Connection;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Index;

class DECLSPEC_UUID("1E3B37A2-C131-11D0-96ED-08005AA4DF58")
Index;
#endif
#endif /* __AD400_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

//5AD4A0AF-C0A7-11D0-96ED-08005AA4DF58
DEFINE_GUID(CLSID_Connection,		0x5AD4A0AF, 0xC0A7, 0x11D0, 0x96, 0xED, 0x08, 0, 0x5A, 0xA4, 0xDF, 0x58);

//5AD4A0AE-C0A7-11D0-96ED-08005AA4DF58
DEFINE_GUID(IID_AD400Connection,	0x5AD4A0AE, 0xC0A7, 0x11D0, 0x96, 0xED, 0x08, 0, 0x5A, 0xA4, 0xDF, 0x58);

//1E3B37A2-C131-11D0-96ED-08005AA4DF58
DEFINE_GUID(CLSID_Index,			0x1E3B37A2, 0xC131, 0x11D0, 0x96, 0xED, 0x08, 0, 0x5A, 0xA4, 0xDF, 0x58);

//1E3B37A1-C131-11D0-96ED-08005AA4DF58
DEFINE_GUID(IID_AD400Index,			0x1E3B37A1, 0xC131, 0x11D0, 0x96, 0xED, 0x08, 0, 0x5A, 0xA4, 0xDF, 0x58);
