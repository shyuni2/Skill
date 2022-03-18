#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <list>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

class NetUser
{
public:
	bool m_Connect = false; // ����ƴ��� �Ǵ�
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	string m_csName;
	short m_Port;
	// ���۱�� �߰�
	char m_szRecvBuffer[2048];
	int m_PacketPos; //  ��Ŷ�� �����ּ�, ��Ŷ�� ����
	int m_WritePos; // ������ ���� ��ġ
	int m_ReadPos; // 
	list<Packet> m_PacketPool; // ��Ŷ �ֱ� (���Ḯ��Ʈ ����)
public:
	int DispatchRead(char* szRecvBuffer, int RecvByte);
	void set(SOCKET sock, SOCKADDR_IN addr);
};
