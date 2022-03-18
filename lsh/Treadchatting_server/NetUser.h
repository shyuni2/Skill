#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <list>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

class NetUser
{
public:
	bool m_Connect = false; // 연결됐는지 판단
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	string m_csName;
	short m_Port;
	// 버퍼기능 추가
	char m_szRecvBuffer[2048];
	int m_PacketPos; //  패킷의 시작주소, 패킷의 시작
	int m_WritePos; // 현재의 저장 위치
	int m_ReadPos; // 
	list<Packet> m_PacketPool; // 패킷 넣기 (연결리스트 구조)
public:
	int DispatchRead(char* szRecvBuffer, int RecvByte);
	void set(SOCKET sock, SOCKADDR_IN addr);
};
