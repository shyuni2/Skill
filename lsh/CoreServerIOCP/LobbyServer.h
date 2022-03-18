#pragma once
#include "Server.h"
#include "ChatUser.h"
#define MAX_WORKER_THREAD 3

class LobbyServer :public Server
{
public:
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	HANDLE g_hIOCP;
public:
	virtual bool InitServer(int iPort);
	virtual bool Run();
	virtual bool Release();
	virtual bool AddUser(SOCKET sock, SOCKADDR_IN ClientAddr);
};

