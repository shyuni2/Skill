#pragma once
#include "TNetUser.h"

// �������� �����ѰŶ� ������� ���� 
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
	// Ŭ��ϱ� �����߰� �Լ��� �ʿ�x
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int RecvUser(TNetUser& user);
};

