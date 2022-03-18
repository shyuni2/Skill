#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <list>
#include <string>
#include "TPacket.h"
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

class TNetUser
{
public:
	bool m_bConnect = false; // ����ƴ��� �Ǵ�
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	string m_csName;
	short m_iPort;
	// ���۱�� �߰�
	char m_szRecvBuffer[2048];
	int m_iPacketPos; //  ��Ŷ�� �����ּ�, ��Ŷ�� ����
	int m_iWritePos; // ������ ���� ��ġ
	int m_iReadPos; // 
	list<TPacket> m_packetPool; // ��Ŷ �ֱ� (���Ḯ��Ʈ ����)
public:
	int DispatchRead(char* szRecvBuffer, int iRecvByte);
	void set(SOCKET sock, SOCKADDR_IN addr);
};
