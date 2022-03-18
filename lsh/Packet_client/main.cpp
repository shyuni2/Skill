#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

int SendMsg(SOCKET sock, char* msg, WORD type) // 방법 1
{
	// 1번 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	// 2번 패킷 전송 : 운영체제 sendbuffer(short바이트), recvbuffer
	char* pMsg = (char*)&packet;
	int SendSize = 0;
	do {
		int SendByte = send(sock, &pMsg[SendSize],
			packet.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len);
	return SendSize;
}
int SendPacket(SOCKET sock, char* msg, WORD type)
{
	Packet uPacket(type);
	uPacket << 999 << "홍길동" << (short)50 << msg;
	Packet uPacketTest(uPacket);
	ChatMsg recvdata;
	ZeroMemory(&recvdata, sizeof(recvdata));
	uPacketTest >> recvdata.index >> recvdata.name
		>> recvdata.damage >> recvdata.message;
	char* pData = (char*)&uPacket.m_uPacket;
	int SendSize = 0;
	do {
		int SendByte = send(sock, &pData[SendSize],
			uPacket.m_uPacket.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		SendSize += SendByte;
	} while (SendSize < uPacket.m_uPacket.ph.len);
	return SendSize;
}

int RecvPacketHeader(SOCKET sock, UPACKET& recvPacket)
{
	char szRecvBuffer[256] = { 0, };
	// 패킷헤더 받기
	ZeroMemory(&recvPacket, sizeof(recvPacket));
	bool Run = true;
	int RecvSize = 0;
	do {
		int RecvByte = recv(sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
		RecvSize += RecvByte;
		if (RecvByte == 0)
		{
			closesocket(sock);
			cout << "접속종료" << endl;
			return -1;
		}
		if (RecvByte == SOCKET_ERROR)
		{
			int Error = WSAGetLastError();
			if (Error != WSAEWOULDBLOCK)
			{
				cout << "비정상 접속종료" << endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (RecvSize < PACKET_HEADER_SIZE);
	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
	return 1;
}
int RecvPacketData(SOCKET sock, UPACKET& recvPacket)
{
	// 데이터 받기
	int RecvSize = 0;
	do {
		int RecvByte = recv(sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - RecvSize, 0);
		RecvSize += RecvByte;
		if (RecvByte == 0)
		{
			closesocket(sock);
			cout << "접속종료" << endl;
			return -1;
		}
		if (RecvByte == SOCKET_ERROR)
		{
			int Error = WSAGetLastError();
			if (Error != WSAEWOULDBLOCK)
			{
				cout << "비정상 접속종료" << endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (RecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
	return 1;
}

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.87"); // 서버에 접속할 아이피

	int Ret = connect(sock, (sockaddr*)&sa, sizeof(sa));
	if (Ret == SOCKET_ERROR)
	{
		return;
	}
	cout << "접속성공" << endl;

	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	char szBuffer[256] = { 0, };
	int End = 0;
	while (1)
	{
		if (_kbhit() == 1)
		{
			int Value = _getche();
			if (Value == '\r' && strlen(szBuffer) == 0)
			{
				cout << "정상 종료" << endl;
				break;
			}
			if (Value == '\r')
			{
				// 방법 1
				// int SendByte = SendMsg(sock, szBuffer, PACKET_CHAT_MSG);
				// 방법 2
				int SendByte = SendPacket(sock, szBuffer, PACKET_CHAT_MSG);
				if (SendByte < 0)
				{
					cout << "비정상 접속종료" << endl;
					break;
				}
				End = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else
			{
				szBuffer[End++] = Value;
			}
		}
		else
		{
			UPACKET packet;
			int iRet = RecvPacketHeader(sock, packet);
			if (iRet < 0) break;
			if (iRet == 1)
			{
				int Ret = RecvPacketData(sock, packet);
				if (Ret < 0)
				{
					break;
				}
				if (Ret == 0) 
				{
					continue;
				}

				// 메세지 처리
				Packet data;
				data.m_uPacket = packet;
				ChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				cout << "\n" << "[" << recvdata.name << "]" << recvdata.message;
			}
		}
	}
	cout << "접속종료" << endl;
	closesocket(sock);
	WSACleanup();
}