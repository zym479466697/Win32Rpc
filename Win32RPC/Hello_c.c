

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue May 12 15:27:42 2020
 */
/* Compiler settings for Hello.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "Hello_h.h"

#define TYPE_FORMAT_STRING_SIZE   11                                
#define PROC_FORMAT_STRING_SIZE   61                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _Hello_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } Hello_MIDL_TYPE_FORMAT_STRING;

typedef struct _Hello_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } Hello_MIDL_PROC_FORMAT_STRING;

typedef struct _Hello_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } Hello_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const Hello_MIDL_TYPE_FORMAT_STRING Hello__MIDL_TypeFormatString;
extern const Hello_MIDL_PROC_FORMAT_STRING Hello__MIDL_ProcFormatString;
extern const Hello_MIDL_EXPR_FORMAT_STRING Hello__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: HelloWorld, ver. 1.0,
   GUID={0x4556509F,0x618A,0x46CF,{0xAB,0x3D,0xED,0x73,0x6E,0xD6,0x64,0x77}} */

handle_t HelloWorld_Binding;


static const RPC_CLIENT_INTERFACE HelloWorld___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x4556509F,0x618A,0x46CF,{0xAB,0x3D,0xED,0x73,0x6E,0xD6,0x64,0x77}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE HelloWorld_v1_0_c_ifspec = (RPC_IF_HANDLE)& HelloWorld___RpcClientInterface;

extern const MIDL_STUB_DESC HelloWorld_StubDesc;

static RPC_BINDING_HANDLE HelloWorld__MIDL_AutoBindHandle;


void Hello( 
    /* [string][in] */ const unsigned char *psz,
    /* [string][out] */ unsigned char osz[ 10 ])
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&HelloWorld_StubDesc,
                  (PFORMAT_STRING) &Hello__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&psz);
    
}


void Shutdown( void)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&HelloWorld_StubDesc,
                  (PFORMAT_STRING) &Hello__MIDL_ProcFormatString.Format[36],
                  ( unsigned char * )0);
    
}


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const Hello_MIDL_PROC_FORMAT_STRING Hello__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Hello */

			0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* 0 */
/* 14 */	0x43,		/* Oi2 Flags:  srv must size, clt must size, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter psz */

/* 24 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 26 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 28 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter osz */

/* 30 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 32 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 34 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Procedure Shutdown */

/* 36 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x1 ),	/* 1 */
/* 44 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	0x40,		/* Oi2 Flags:  has ext, */
			0x0,		/* 0 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };

static const Hello_MIDL_TYPE_FORMAT_STRING Hello__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x26,		/* FC_CSTRING */
			0x5c,		/* FC_PAD */
/*  8 */	NdrFcShort( 0xa ),	/* 10 */

			0x0
        }
    };

static const unsigned short HelloWorld_FormatStringOffsetTable[] =
    {
    0,
    36
    };


static const MIDL_STUB_DESC HelloWorld_StubDesc = 
    {
    (void *)& HelloWorld___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &HelloWorld_Binding,
    0,
    0,
    0,
    0,
    Hello__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

