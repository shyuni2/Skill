#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

HANDLE hExecuteSemaphore; // �������� �ڵ�
HANDLE hConnectEvent; // �̺�Ʈ �ڵ�

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	// 1�� ��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));	
	// 2�� ��Ŷ ���� : �ü�� sendbuffer(short����Ʈ), recvbuffer
	char* pMsg = (char*)&packet;
	int SendSize = 0;
	do {
		int SendByte = send(sock, &pMsg[SendSize], packet.ph.len - SendSize, 0);
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
	// 1�� ��Ŷ ����
	Packet tPacket(type);
	tPacket << 999 << "�̽���" << (short)50 << msg;
	Packet tPacketTest(tPacket);
	ChatMsg recvdata;
	ZeroMemory(&recvdata, sizeof(recvdata));
	tPacketTest >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
	char* pData = (char*)&tPacket.m_uPacket;
	int SendSize = 0;
	do {
		int SendByte = send(sock, &pData[SendSize], tPacket.m_uPacket.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		SendSize += SendByte;
	} while (SendSize < tPacket.m_uPacket.ph.len);
	return SendSize;
}
int RecvPacketHeader(SOCKET sock, UPACKET& recvPacket)
{
	char szRecvBuffer[256] = { 0, };
	//��Ŷ��� �ޱ�
	ZeroMemory(&recvPacket, sizeof(recvPacket));
	bool bRun = true;
	int RecvSize = 0;
	do {
		int RecvByte = recv(sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
		RecvSize += RecvByte;
		if (RecvByte == 0)
		{
			closesocket(sock);
			cout << " ���������." << endl;
			return -1;
		}
		if (RecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << " ������ ���������." << endl;
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
	// ������ �ޱ�
	int RecvSize = 0;
	do {
		int RecvByte = recv(sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - RecvSize, 0);
		RecvSize += RecvByte;
		if (RecvByte == 0)
		{
			closesocket(sock);
			cout << " ���������." << endl;
			return -1;
		}
		if (RecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << " ������ ���������." << endl;
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

// ��� 1, win api ���
// ������ ������
DWORD WINAPI SendThread(LPVOID IpThreadParameter) 
{
	SOCKET sock = (SOCKET)IpThreadParameter;
	char szBuffer[256] = { 0, };
	while (1)
	{
		DWORD dwRet = WaitForSingleObject(hConnectEvent, INFINITE); // INFINITE �� �ϸ� �̺�Ʈ ������ ���
		if (dwRet != WAIT_OBJECT_0) // WAIT_OBJECT_0 : ��ٸ��� �̺�Ʈ�� �ñ׳� �� ���
		{
			break;
		}
		ZeroMemory(szBuffer, sizeof(char) * 256);
		fgets(szBuffer, 256, stdin); // Ű����� �Է¹޾ƶ�, ���;�ġ�� ��ȯ ��ġ�� �Լ�
		if (strlen(szBuffer) == 0) // ������ ���̰� ������ ����
		{
			cout << "���� ����" << endl;
			break;
		}
		// ��� 1
		//int SendByte = SendMsg(sock, szBuffer, PACKET_CHAT_MSG);
		// ��� 2
		int SendByte = SendPacket(sock, szBuffer, PACKET_CHAT_MSG);
		if (SendByte < 0)
		{
			cout << "������ ����" << endl;
			break;
		}
	}
	return 0; // �����Ҷ� �������ִ°� ����
} // ���Լ��� ����� ���� �߻��ϸ� ������ ����

// �޴� ������
DWORD WINAPI RecvThread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	while (1)
	{
		DWORD dwRet = WaitForSingleObject(hConnectEvent, INFINITE); // INFINITE �� �ϸ� �̺�Ʈ ������ ���
		if (dwRet != WAIT_OBJECT_0) // WAIT_OBJECT_0 : ��ٸ��� �̺�Ʈ�� �ñ׳� �� ���
		{
			break;
		}
		UPACKET packet;
		int ret = RecvPacketHeader(sock, packet);
		if (ret < 0) continue; // ������ ���������� ���� �Ǵϱ� continue
		if (ret == 1)
		{
			int ret = RecvPacketData(sock, packet);
			if (ret < 0) break;
			if (ret == 0) continue;
			// �޼��� ó��
			Packet data;
			data.m_uPacket = packet;
			ChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
			cout << "\n" << "[" << recvdata.name << "]" << recvdata.message;
		}
	}
	return 0;
}

void main()
{
	hConnectEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	// CreateEvent (���ȼӼ� ���������� ������, false�� �ڵ������̺�Ʈ true�� ���������̺�Ʈ, �̺�Ʈ ��ü�� �ʱ���¸� �ñ׳� ���·� �ϰ������ true ��ñ׳λ��·� �ϰ������ false, �̺�Ʈ ��ü�̸�)
	// �ڵ� ���� �̺�Ʈ : �����°� ����Ǹ� �ڵ����� ���ȣ ���°� ��
	// ���� ���� �̺�Ʈ : �����尡 ���ȣ���·� ���鶧���� ��ȣ�� ������
	hExecuteSemaphore = CreateSemaphore(NULL, 3, 3, L"Execute"); // ��������� ī��Ʈ�� ������
	// CreateSemaphore (NULL, �ʱⰪ ����, �ִ� ī��Ʈ��, �����Ǵ� ������� �̸��� �ٰ�� ���)
	if (WaitForSingleObject(hExecuteSemaphore, 0) == WAIT_TIMEOUT)
	{
		CloseHandle(hExecuteSemaphore);
		MessageBox(NULL, L"�̹� 3���� �ν��Ͻ��� �������Դϴ�.", L"�˸�", MB_OK);
		return;
	}
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	// ������ ����, ��ġ�� ������µ� ������ �־�� �����尡 �����ɼ� �ֱ⶧���� ������ �ؿ� ������
	// win api���
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread(
		0, // ���ȼӼ�, 0�� �⺻����� ���ڴٴ� �ǹ�
		0, // ���� ũ�� ����, 0�� �⺻����� ���ڴٴ� �ǹ�
		SendThread, // ��ȯ, 
		(LPVOID)sock, // ������ �Ѱ���� send�� ��
		0,// ������ �����ڸ��� �Ͻ�ų�� or �����ѳ��� ���ϴ� ������ �Ͻ�ų��? ���Ҽ��ִ� �ڸ�, 0�� ������ �����带 �����ڸ��� SendTread�� ����
		&ThreadIdSend // ������ �����忡���� �ε����� ��ȯ���ش� , �������� ��ȣ��� ����
	);
	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread(
		0,
		0, // 0�� �⺻����� ���ڴٴ� �ǹ�
		RecvThread, // ��ȯ, 
		(LPVOID)sock, // ������ �Ѱ���� recv�� ��
		0,// ������ �����ڸ��� �Ͻ�ų�� or �����ѳ��� ���ϴ� ������ �Ͻ�ų��? ���Ҽ��ִ� �ڸ�, 0�� ������ �����带 �����ڸ��� RecvTread�� ����
		&ThreadIdRecv // ������ �����忡���� �ε����� ��ȯ���ش� , �������� ��ȣ��� ����
	);

	Sleep(1000); // ����Ī�� �ǰ� ����Լ�

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1);
	sa.sin_addr.s_addr = inet_addr("192.168.0.87");
	int ret = connect(sock, (sockaddr*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		return;
	}
	cout << "���Ӽ���!" << endl;

	SetEvent(hConnectEvent); // �̺�Ʈ ����

	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on); // ������� ������

	// ���ν����� �۾�
	while (1) 
	{
		// ���߿� ���� �ڵ尡 ���������
		Sleep(1); 
	}
	cout << "��������" << endl;
	
	CloseHandle(hThreadSend);
	closesocket(sock);
	WSACleanup();

	CloseHandle(hConnectEvent); // �̺�Ʈ ����
}