#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <list>
#include <string>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

struct User // ���� ����
{
	SOCKET user_sock;
	SOCKADDR_IN user_addr;
	string user_name;
	short user_port;
	void set(SOCKET Usock, SOCKADDR_IN Uaddr)
	{
		user_sock = Usock;
		user_addr = Uaddr;
		user_name = inet_ntoa(Uaddr.sin_addr);
		user_port = ntohs(Uaddr.sin_port);
	}
};

int SendMsg(SOCKET sock, char* msg, WORD type)
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
				return -1; // ����
			}
		}
	} while (SendSize < packet.ph.len); // do while �� ���� : �ϴ� �޼����� ������� �ؾ��ϱ⶧����, ���� ���̰� ��Ŷ������� ���� ���������� �ݺ�
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
				return -1; // ����
			}
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len); 
	return SendSize;
}

// ��Ŷ�� �߰��ؼ� ���ݸ� �޶����� ������ ũ�� ���ϴ°� ����

void main()
{
	WSADATA WSA;
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SAddr; // �Լ� ���ڷ� ����Ҷ��� �׻� �ּҰ��� �����ϸ� �ݵ�� ������������ ��ȯ�ؼ� ����ؾ��Ѵ�
	ZeroMemory(&SAddr, sizeof(SAddr)); // �ϴ� �޸��ʱ�ȭ�� ����
	SAddr.sin_family = AF_INET;
	SAddr.sin_port = htons(10000);
	SAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// ���ε� �۾�
	int Ret = bind(ListenSock, (sockaddr*)&SAddr, sizeof(SAddr)); // bind(Ŭ���̾�Ʈ ������ ������ �������� ���� ����, �����ּ� ����ü, �����ּ� ����ü ����
	if (Ret == SOCKET_ERROR) return; // ���ε��Լ� ���ϰ��� ������ ����
	// ���� �۾�
	Ret = listen(ListenSock, SOMAXCONN); // listen(bind�Լ��� ���� �������ּҿ� ������Ʈ��ȣ�� ������ ����, ���Ӱ����� Ŭ���̾�Ʈ ����)
	if (Ret == SOCKET_ERROR) return; // �����Լ� ���ϰ��� ������ ����

	SOCKADDR_IN ClientAddr; // �������� ������ �Լ����ڷ� ����Ҷ��� �׻� �ּҰ��� �����ϸ� �ݵ�� ������������ ��ȯ�ؼ� ����ؾ���
	int AddrC = sizeof(ClientAddr); // Ŭ���̾�Ʈ�ּҸ� ��� ����

	cout << "���� ����� >" << endl; // ������ ��������� ����ϴ� �޼���

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on); // ioctlsocket(����ŷ���� ���� ����, ���Ͽ����� ������ ������ �ǹ��ϴ� Ŀ�ǵ�, 0�̸� ���ŷ��尡 �ǰ� 0�̾ƴѰ��� ������ ����ŷ���� ����)

	list<User> userlist; // ��������Ʈ�� �˱����� ���, �迭������ϸ� �������� ��Ȳ�� ����ؾ��ϱ� ������ list�����

	//������ ���۾��� �ݺ��Ǿ�� �������ڸ��� ������ ��츦 ���ټ�����
	while (1)
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &AddrC); // accept(Ŭ���̾�Ʈ ������ �����Ҹ������� ���� ����, �����ּ� ����ü ������ ����, ���� ����ü�� ũ�⸦ ��Ÿ���� ������ ������ �ּ�)

		if (ClientSock == SOCKET_ERROR) // Ŭ���̾�Ʈ ������ �����̸�
		{
			int Error = WSAGetLastError(); // ���� �����ڵ�
			if (Error != WSAEWOULDBLOCK) // 
			{
				cout << "Error Code = " << Error << endl; // �����ڵ� ���
				break;
			}
		}
		else // Ŭ���̾�Ʈ ������ ������ �ƴϸ�
		{
			User user;
			user.set(ClientSock, ClientAddr);
			userlist.push_back(user); // ��������Ʈ �ڿ� ���� Ǫ����

			cout << "ip =" << inet_ntoa(ClientAddr.sin_addr) << "port =" << ntohs(ClientAddr.sin_port) << " ==> Log In" << endl; // inet_ntoa : ��Ʈ��ũ ����Ʈ ���� ����� 4����Ʈ �ּҸ� ���ڿ��ּҷ� ǥ��

			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);

			cout << userlist.size() << " �� ������ >" << endl;
		}

		// ��������Ʈ ���� �ڵ� > ���⼭ ��Ŷ�� ����
		if (userlist.size() > 0) // ������ �Ѹ��̶� ������
		{
			list <User> ::iterator Sockiter; // ���Ϲݺ��ڻ���
			for (Sockiter = userlist.begin(); Sockiter != userlist.end(); ) // for������ Sockiter�� ++�Ǹ� ������ ���ﶧ ����ؾ���, erase�� ��ȯ�� �߿�
			{
				User user = *Sockiter; // ���Ϲݺ��� ������ ����
				char szRecvBuffer[256] = { 0, };
				// ��Ŷ ��� �ޱ�
				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int RecvSize = 0;
				do {
					int RecvByte = recv(user.user_sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);// recv(��Ŵ��� ����� ����, ���� �����͸� ������ ����(char���̾����), �����͹����� ũ��, Ư���� �ɼ��� �ֱ����� - �Ⱦ��� 0)
					RecvSize += RecvByte;
					if (RecvByte == 0) // RecvByte�� 0�̸� Ŭ�� ������
					{
						closesocket(user.user_sock); // �������� �ݾ��ְ�
						Sockiter = userlist.erase(Sockiter); // �����ش�

						cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> Log Out" << endl;
						continue;
					}
					if (RecvByte != SOCKET_ERROR)
					{
						int Error = WSAGetLastError();
						if (Error != WSAEWOULDBLOCK)
						{
							Sockiter = userlist.erase(Sockiter);

							cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> ������ ��������" << endl;
						}
						else
						{
							break;
						}
					}
				} while (RecvSize < PACKET_HEADER_SIZE);
				if (RecvSize == SOCKET_ERROR)
				{
					if (Sockiter != userlist.end())
					{
						Sockiter++;
					}
				}
				memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);

				// ������ �ޱ�
				RecvSize = 0;
				do {
					int RecvByte = recv(user.user_sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - RecvSize, 0);
					RecvSize += RecvByte;
					if (RecvByte == 0)
					{
						closesocket(user.user_sock);
						Sockiter = userlist.erase(Sockiter);
						cout << user.user_name << "��������" << endl;
						continue;
					}
					if (RecvByte == SOCKET_ERROR)
					{
						int Error = WSAGetLastError();
						if (Error != WSAEWOULDBLOCK)
						{
							Sockiter = userlist.erase(Sockiter);
							cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> ������ ��������" << endl;
						}
						else
						{
							Sockiter++;
						}
					}
				} while (RecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE); // ©�������͸� �� �޾ƾ��ϱ� ������

				Packet data;
				data.m_uPacket = recvPacket;
				ChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));

				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				cout << "\n" << "[ " << recvdata.name << " ]" << recvdata.message;

				// ��Ŷ �ϼ�
				list<User> ::iterator Senditer;
				for (Senditer = userlist.begin(); Senditer != userlist.end(); )
				{
					User user = *Senditer;
					int SendMsgSize = SendMsg(user.user_sock, recvPacket);
					if (SendMsgSize < 0)
					{
						closesocket(user.user_sock);
						Senditer = userlist.erase(Senditer);
						cout << user.user_name << "������ ��������" << endl;
					}
					else
					{
						Senditer++;
					}
				}
				if (Senditer != userlist.end())
				{
					Senditer++;
				}
			}
		}
	}
	closesocket(ListenSock);
	WSACleanup(); // ���� �����Լ�
}
