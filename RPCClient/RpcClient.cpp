#include "RpcClient.h"
#include "../RPC/BaseRPC_h.h"     // 引用MIDL 生成的头文件
#include <iostream>
#pragma comment(lib, "Rpcrt4.lib")


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

//strPipe=>8dd50205-3108-498f-96e8-dbc4ec074cf9
CRpcClient::CRpcClient(const std::string& strPipe)
{
	char szPipe[64] = { 0 };
	sprintf_s(szPipe, "\\pipe\\{%s}", strPipe.c_str());
	m_strPipe = szPipe;
}

CRpcClient::CRpcClient(int port)
{
	char szPort[32] = { 0 };
	sprintf_s(szPort, "%d", port);
	m_strPort = szPort;
}


CRpcClient::~CRpcClient()
{
}

DWORD CRpcClient::Request(const char* szRequest, char* pszResponse)
{
	RPC_STATUS status;
	unsigned char* szStringBinding = NULL;
	if (!m_strPort.empty())
	{
		status = RpcStringBindingComposeA(
			NULL, // UUID to bind to.
			reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // Use TCP/IP protocol.
			reinterpret_cast<unsigned char*>("localhost"), // TCP/IP network address to use.
			reinterpret_cast<unsigned char*>((char*)m_strPort.c_str()), // TCP/IP port to use.
			NULL, // Protocol dependent network options to use.
			&szStringBinding); // String binding output.
	}
	else
	{
		status = RpcStringBindingComposeA(
			NULL, // UUID to bind to.
			(unsigned char*)"ncacn_np", // Use pipe protocol.
			NULL, // 
			(unsigned char*)m_strPipe.c_str(), // pipe )"\\pipe\\{8dd50205-3108-498f-96e8-dbc4ec074cf9}"
			NULL, // Protocol dependent network options to use.
			&szStringBinding); // String binding output.
	}
	
	if (status)
		return RpcHandleError("RpcStringBindingCompose", status);

	// Validates the format of the string binding handle and converts
	// it to a binding handle.
	// Connection is not done here either.
	status = RpcBindingFromStringBindingA(
		szStringBinding, // The string binding to validate.
		&BaseRPC_Binding); // Put the result in the explicit binding handle.
	if (status)
		return RpcHandleError("RpcBindingFromStringBinding", status);

	// 下面是调用服务端的函数了
	RpcTryExcept
	{
		PRPCSTRING str;
		RPC_Request((unsigned char *)szRequest, &str);
		printf("outstring:%s \n", str->string);
		pszResponse = new char(str->length);
		memcpy(pszResponse, str->string, str->length);
		midl_user_free(str);
	}
	RpcExcept(1)
	{
		printf("RPC Exception %d\n", RpcExceptionCode());
	}
	RpcEndExcept

	// 释放资源
	RpcStringFreeA(&szStringBinding);
	RpcBindingFree(&BaseRPC_Binding);
	return 0;
}