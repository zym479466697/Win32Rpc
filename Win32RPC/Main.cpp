// Win32RPC.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RpcServer.h"

int main()
{
	CRpcServer server;
	server.RpcServerStart("3dc09478-3b72-434a-b5e0-cb46c0e12a92");
	server.RpcWait();
	return 0;
}
