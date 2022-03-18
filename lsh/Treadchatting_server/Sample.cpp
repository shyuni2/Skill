#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "NetUser.h"

list<NetUser> m_UserList; // �������� �������� ����
CRITICAL_SECTION CS; // ũ��Ƽ�ü��� �̸�

// ������ �Լ�
int SendMsg(SOCKET sock, char*msg, WORD type)
{
	// 1. ��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	// 2. ��Ŷ ����
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
int SendMsg(SOCKET sock, UPACKET& packet)
{
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
// ��ε�ĳ��Ʈ �Լ�
int Broadcast(NetUser& user)
{
	if (user.m_PacketPool.size() > 0)
	{
		list<Packet>::iterator iter;
		for (iter = user.m_PacketPool.begin(); iter != user.m_PacketPool.end(); )
		{
			for (NetUser& senduser : m_UserList)
			{
				int iRet = SendMsg(senduser.m_Sock, (*iter).m_uPacket);
				if (iRet <= 0)
				{
					senduser.m_Connect = false;
				}
			}
			iter = user.m_PacketPool.erase(iter);
		}
	}
	return 1;
}

// �޴��Լ�
int RecvUser(NetUser& user)
{
	char szRecvBuffer[1024] = { 0, };
	int RecvByte = recv(user.m_Sock, szRecvBuffer, 1024, 0);
	if (RecvByte == 0)
	{
		return 0;
	}
	if (RecvByte == SOCKET_ERROR)
	{
		int Error = WSAGetLastError();
		if (Error != WSAEWOULDBLOCK)
		{
			return -1;
		}
		return 2;
	}
	user.DispatchRead(szRecvBuffer, RecvByte); // �������� ����Ұ� �־�ߵ�
	return 1;
}
// ������ ����, ������ �Լ��� ����� ���� �߻��ϸ� ������ ���ᰡ �ȴ�
// �޴� ������
DWORD WINAPI RecvThread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	while (1)
	{
		EnterCriticalSection(&CS);
		list<NetUser>::iterator useriter;
		for (useriter = m_UserList.begin(); useriter != m_UserList.end();)
		{
			int ret = RecvUser(*useriter);
			if (ret <= 0)
			{
				useriter = m_UserList.erase(useriter);
			}
			else
			{
				useriter++;
			}
		}
		LeaveCriticalSection(&CS);
		Sleep(1); // ����Ī
	}
}
// ������ ������
DWORD WINAPI SendTread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	while (1)
	{
		EnterCriticalSection(&CS);
		list<NetUser>::iterator useriter;
		for (useriter = m_UserList.begin(); useriter != m_UserList.end(); )
		{
			int ret = Broadcast(*useriter);
			if (ret <= 0)
			{
				useriter = m_UserList.erase(useriter);
			}
			else
			{
				useriter++;
			}
		}
		LeaveCriticalSection(&CS);
		Sleep(1); // ����Ī
	}
}


void main()
{
	InitializeCriticalSection(&CS); // �ʱ�ȭ�� ũ��Ƽ�� ���� ������ ����
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR) 
	{ 
		return; 
	}
	ret = listen(ListenSock, SOMAXCONN);
	if (ret == SOCKET_ERROR) 
	{
		return; 
	}

	SOCKADDR_IN ClientAddr;
	int CAlength = sizeof(ClientAddr);

	cout << "--- ���� ������ ---" << endl;

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);

	// ������ ���� 
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread(
		0, // ���ȼӼ�, 0�� �⺻����� ���ڴٴ� �ǹ�
		0, // ���� ũ�� ����, 0�� �⺻����� ���ڴٴ� �ǹ�
		SendTread, // ��ȯ, 
		(LPVOID)ListenSock, // ������ �Ѱ���� send�� ��
		0,// ������ �����ڸ��� �Ͻ�ų�� or �����ѳ��� ���ϴ� ������ �Ͻ�ų��? ���Ҽ��ִ� �ڸ�, 0�� ������ �����带 �����ڸ��� SendTread�� ����
		&ThreadIdSend // ������ �����忡���� �ε����� ��ȯ���ش� , �������� ��ȣ��� ����
	);
	CloseHandle(hThreadSend); // �̷��� ���� ������ ���ư��µ� ������ ����, ������ ���ϰڴٴ� ������ �����带 �����Ѵٴ� ���� �ƴ�, ���� ������ҷ�~

	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread(
		0,
		0, // 0�� �⺻����� ���ڴٴ� �ǹ�
		RecvThread, // ��ȯ, 
		(LPVOID)ListenSock, // ������ �Ѱ���� recv�� ��
		0,// ������ �����ڸ��� �Ͻ�ų�� or �����ѳ��� ���ϴ� ������ �Ͻ�ų��? ���Ҽ��ִ� �ڸ�, 0�� ������ �����带 �����ڸ��� RecvTread�� ����
		&ThreadIdRecv // ������ �����忡���� �ε����� ��ȯ���ش� , �������� ��ȣ��� ����
	);
	CloseHandle(hThreadRecv);

	// ���ν����� �۾�
	while (1)
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &CAlength);
		if (ClientSock == SOCKET_ERROR)
		{
			int error = WSAGetLastError(); // WSAGetLastError ���� �ֱٿ� �߻��� ���Ͽ����� ������
			if (error != WSAEWOULDBLOCK)
			{
				cout << "ErrorCode = " << error << endl;
				break;
			}
		}
		else // ������ �ƴϸ� ���� �۵��ؾ���
		{
			NetUser user;
			user.set(ClientSock, ClientAddr);
			EnterCriticalSection(&CS);
			m_UserList.push_back(user);
			LeaveCriticalSection(&CS);

			cout << "IP = " << inet_ntoa(ClientAddr.sin_addr) << "Port = " << ntohs(ClientAddr.sin_port) << " " << endl;

			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);
			cout << m_UserList.size() << "�� ������" << endl;
		}
		Sleep(1);
	}
	cout << "��������" << endl;
	
	closesocket(ListenSock);
	WSACleanup();

	DeleteCriticalSection(&CS); // ũ��Ƽ�� ���� �Ҹ�
}