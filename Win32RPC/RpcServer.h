#ifndef RPCSERVER_H_
#define RPCSERVER_H_
#include <string>
#include <windows.h>

class CRpcServer
{
public:
	CRpcServer();
	~CRpcServer();
	DWORD RpcServerStart(int port);
	DWORD RpcServerStart(const std::string& strPipeGuid);
	bool RpcStopServer();
	bool RpcWait();
protected:
	static DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/);
private:
	HANDLE m_hThread;
};

#endif /*RPCSERVER_H_*/