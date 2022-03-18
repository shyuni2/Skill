#pragma once
#include "NetUser.h"

class Network
{
public:
	SOCKET m_Sock;
	std::list<NetUser> userlist;
	NetUser m_PlayerUser;
public:
	bool InitNetwork();
	bool InitServer(int protocol, int iport, const char* ip=nullptr);
	bool CloseNetwork();
public:
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int SendMsg(SOCKET sock, char* msg, int iSize, WORD type);
	int AddUser(SOCKET sock);
	int RecvUser(NetUser& user);
};

