#pragma once
#include "TNetUser.h"

class TNetwork
{
public:
	SOCKET m_ListenSock;
public:
	bool InitNetwork();
	bool InitServer(int protocol, int iport, const char* ip = nullptr);
	bool CloseNetwork();
};

