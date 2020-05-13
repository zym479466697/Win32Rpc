#include "RpcServer.h"
#include "../RPC/BaseRPC_h.h"
#include <iostream>
#pragma comment(lib, "Rpcrt4.lib")

void RPC_Request(
	/* [string][in] */ const unsigned char *pszIn,
	/* [out] */ PRPCSTRING *pszOut)
{

	printf("%s\n", pszIn);
	char*ptrName = (char*)pszIn;
	int len = strlen(ptrName) + 1;
	int allocateLen = len + 4;
	*pszOut = (PRPCSTRING)MIDL_user_allocate(allocateLen);
	(*pszOut)->size = allocateLen;
	(*pszOut)->length = len;
	strncpy_s((char*)(*pszOut)->string, len, ptrName, len);
}

/** 这也是我们在IDL 中定义的接口方法，提供关闭server 的机制*/
void RPC_Shutdown(void)
{
	// 下面的操作将导致 RpcServerListen() 退出
	RpcMgmtStopServerListening(NULL);
	RpcServerUnregisterIf(NULL, NULL, FALSE);
}

// Memory allocation function for RPC.
// The runtime uses these two functions for allocating/deallocating
// enough memory to pass the string to the server.
void* __RPC_USER midl_user_allocate(size_t size)
{
	return malloc(size);
}

// Memory deallocation function for RPC.
void __RPC_USER midl_user_free(void* p)
{
	free(p);
}


// Write a formatted error message to std::cerr.
DWORD RpcHandleError(const char* szFunction, DWORD dwError)
{
	void* pBuffer = NULL;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		LPSTR(&pBuffer),
		0,
		NULL);

	std::cerr << szFunction << " failed. "
		<< (pBuffer ? LPSTR(pBuffer) : "Unknown error. ")
		<< "(" << dwError << ")" << std::endl;
	LocalFree(pBuffer);
	return dwError;
}

CRpcServer::CRpcServer()
{
	m_hThread = INVALID_HANDLE_VALUE;
}


CRpcServer::~CRpcServer()
{
	RpcStopServer();
}


DWORD CRpcServer::RpcServerStart(int port)
{
	RPC_STATUS status = -1;
	if (m_hThread != INVALID_HANDLE_VALUE)
		return status;
	
	// Uses the protocol combined with the endpoint for receiving
	// remote procedure calls.
	char szPort[32] = { 0 };
	sprintf_s(szPort, "%d", port);
	status = RpcServerUseProtseqEpA(
		reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // Use TCP/IP protocol.
		RPC_C_PROTSEQ_MAX_REQS_DEFAULT, // Backlog queue length for TCP/IP.
		reinterpret_cast<unsigned char*>(szPort), // TCP/IP port to use.
		NULL); // No security.
	if (status)
		return RpcHandleError("RpcServerUseProtseqEp", status);

	std::clog << "Calling RpcServerRegisterIf" << std::endl;
	// Registers the ContextExample interface.
	status = RpcServerRegisterIf(BaseRPC_v1_0_s_ifspec, NULL, NULL);
	//status = RpcServerRegisterIf2(
	//	BaseRPC_v1_0_s_ifspec, // Interface to register.
	//	NULL, // Use the MIDL generated entry-point vector.
	//	NULL, // Use the MIDL generated entry-point vector.
	//	RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, // Forces use of security callback.
	//	RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Use default number of concurrent calls.
	//	(unsigned)-1, // Infinite max size of incoming data blocks.
	//	SecurityCallback); // Naive security callback.
	if (status)
		return RpcHandleError("RpcServerRegisterIf", status);

	std::clog << "Creating listen thread" << std::endl;
	HANDLE m_hThread = CreateThread(NULL, 0, RpcServerListenThreadProc, NULL, 0, NULL);
	if (!m_hThread)
		return RpcHandleError("CreateThread", GetLastError());
	return 0;
}


//strPipeGuid=>8dd50205-3108-498f-96e8-dbc4ec074cf9
DWORD CRpcServer::RpcServerStart(const std::string& strPipeGuid)
{
	RPC_STATUS status = -1;
	if (m_hThread != INVALID_HANDLE_VALUE)
		return status;

	// Uses the protocol combined with the endpoint for receiving
	char szPipeName[64] = { 0 };
	sprintf_s(szPipeName, "\\pipe\\{%s}", strPipeGuid.c_str());
	status = RpcServerUseProtseqEpA((unsigned char *)"ncacn_np", 20, (unsigned char *)szPipeName, NULL);
	//RpcServerUseProtseqEpA(reinterpret_cast<unsigned char*>("ncacn_np"), 
	//	20,
	//	reinterpret_cast<unsigned char*>(szPipeName), 
	//	NULL);
	if (status)
		return RpcHandleError("RpcServerUseProtseqEp", status);

	std::clog << "Calling RpcServerRegisterIf" << std::endl;
	// Registers the ContextExample interface.
	status = RpcServerRegisterIf(BaseRPC_v1_0_s_ifspec, NULL, NULL);
	if (status)
		return RpcHandleError("RpcServerRegisterIf", status);

	std::clog << "Creating listen thread" << std::endl;
	HANDLE m_hThread = CreateThread(NULL, 0, RpcServerListenThreadProc, NULL, 0, NULL);
	if (!m_hThread)
		return RpcHandleError("CreateThread", GetLastError());
	return 0;
}

// The thread that will listen for incoming RPC calls.
DWORD WINAPI CRpcServer::RpcServerListenThreadProc(LPVOID /*pParam*/)
{
	// Start to listen for remote procedure calls for all registered interfaces.
	// This call will not return until RpcMgmtStopServerListening is called.
	return RpcServerListen(
		1, // Recommended minimum number of threads.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Recommended maximum number of threads.
		FALSE); // Start listening now.
}

bool CRpcServer::RpcStopServer()
{
	RpcMgmtStopServerListening(NULL);
	RpcServerUnregisterIf(NULL, NULL, FALSE);
	if (m_hThread){
		WaitForSingleObject(m_hThread, 1000);
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
	return true;
}


bool CRpcServer::RpcWait()
{
	WaitForSingleObject(m_hThread, INFINITE);
	return true;
}