#ifndef RPCCLIENT_H_
#define RPCCLIENT_H_
#include <string>
#include <windows.h>

class CRpcClient
{
public:
	CRpcClient(const std::string& strPipe);
	CRpcClient(int port);
	~CRpcClient();
	DWORD Request(const char* szRequest, char* pszResponse);
private:
	std::string m_strPort;
	std::string m_strPipe;
};

#endif /*RPCCLIENT_H_*/