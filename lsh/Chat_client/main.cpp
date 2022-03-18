#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

void main()
{
	WSADATA WSA; // WSADAD ����ü �̸��� wsa�� ����
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0) // �����ʱ�ȭ�Լ� WSAStartup�� 0�� �ƴҶ�
	{
		return;
	}
	// Ŭ���̾�Ʈ�� �帧
	// 1. ���ϻ���
	// 2.	-> ������ ����õ� connect 
	// 3.	-> recv, send �̿��� �������� ������ �ۼ���

	SOCKET ConnectSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SAddr; 
					   
	ZeroMemory(&SAddr, sizeof(SAddr));
	SAddr.sin_family = AF_INET; 
	SAddr.sin_port = htons(10000); // ��Ʈ��ȣ 10000
	SAddr.sin_addr.s_addr = inet_addr("192.168.0.117"); // ���� �����Ƿ� ����, �� ������ 192.168.0.117, inet_ntoa : ��Ʈ��ũ ����Ʈ ���� ����� 4����Ʈ �ּҸ� ���ڿ��ּҷ� ǥ��

	int RetC = connect(ConnectSock, (sockaddr*)&SAddr, sizeof(SAddr)); // Ŀ��Ʈ�Լ��� ���� ����
	if (RetC == SOCKET_ERROR) // Ŀ��Ʈ�� �������� ����
	{
		return;
	}
	// Ŀ��Ʈ�� ������ �ƴϸ� ������ ���Ἲ��
	cout << "���� ���� >" << endl;

	u_long on = 1;
	ioctlsocket(ConnectSock, FIONBIO, &on);
	
	char szBuffer[256] = { 0, };
	int End = 0;

	while (1)
	{
		if (_kbhit() == 1) // _kbhit : Ű���尡 ���ȴ��� üũ���ִ� �Լ�
		{
			int KValue = _getche(); // _getche : Ű���� �Է¹ް� ������ִ� �Լ�
			if (KValue == '\r' && strlen(szBuffer) == 0)
			{
				break;
			}
			if (KValue == '\r') // ���� �Է��� ������
			{
				int SendByte = send(ConnectSock, szBuffer, End, 0); // send(����� ���� ����� ����, ���������͸� ����ִ� ����, ���� ������ ũ��, Ư���� �ɼ��� �ֱ����� - �Ⱦ��� 0)
				if (SendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						cout << "������ ���� ����" << endl;
					}
				}
				End = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256); // �޸� �ʱ�ȭ
			}
			else // ���� �Է� ����������
			{
				szBuffer[End++] = KValue;
			}
		}
		else
		{
			char szRecvBuffer[256] = { 0, };
			int RecvByte = recv(ConnectSock, szBuffer, 256, 0);

			if (RecvByte == 0)
			{
				cout << "��������" << endl;
				break;
			}
			if (RecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					cout << "������ ��������" << endl;
					break;
				}
			}
			else
			{
				cout << "\n" << szRecvBuffer;
				ZeroMemory(szRecvBuffer, sizeof(char) * 256);
			}
		}
	}
	cout << "��������" << endl;
	closesocket(ConnectSock);
	WSACleanup();
}