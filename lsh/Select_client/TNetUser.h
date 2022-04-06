#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "STD.h" // 전에 만들었던 라이브러리 연결
#include "TPacket.h"

using namespace std;

class TNetUser
{
public:
	bool m_bConnect = false; // 연결됐는지 판단
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	string m_csName;
	short m_iPort;
	// 버퍼기능 추가
	char m_szRecvBuffer[2048];
	int m_iPacketPos; //  패킷의 시작주소, 패킷의 시작
	int m_iWritePos; // 현재의 저장 위치
	int m_iReadPos; // 
	list<TPacket> m_packetPool; // 패킷 넣기 (연결리스트 구조)
public:
	int DispatchRead(char* szRecvBuffer, int iRecvByte);
	void set(SOCKET sock, SOCKADDR_IN addr);
};
