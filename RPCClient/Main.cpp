// RPCClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "RpcClient.h"
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")

int main(int argc, char * argv[])
{
	CRpcClient client("3dc09478-3b72-434a-b5e0-cb46c0e12a92");
	char* psz = NULL;
	client.Request(argv[1], psz);
	if (psz)
		delete psz;
	return 0;
}

