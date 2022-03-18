#pragma once
#include "TNetUser.h"

// 서버에서 복사한거라 변경사항 있음 
class TNetwork
{
public:
	SOCKET m_Sock;
	list<TNetUser> userlist;
	TNetUser m_PlayerUser;
public:
	bool InitNetwork();
	bool InitServer(int protocol, int iport, const char* ip = nullptr);
	bool CloseNetwork();
public:
	// 클라니까 유저추가 함수는 필요x
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int RecvUser(TNetUser& user);
};

