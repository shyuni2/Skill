#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	// 1. ���Ͽ��� ���ϸ���°� ������ Ŭ��� �ٸ�������
	SOCKET sock = socket
	(
		AF_INET, // �ּ�ü�� ���� : ���ͳ��������� ����ϰڴ�
		SOCK_STREAM, // ����Ÿ�� ���� : TCP ����ϰڴ�, STREAM ���� TCP, DGRAM ���� UDP ���� �ϳ� ����ϸ��
		0 // ����� �������� ���� : �ι�° ���ڿ��� ����ϴ°� ���� �ڵ����� �������ִ� ��������
	); 

	SOCKADDR_IN sa; 
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // 10000������ ����, ������ ��Ʈ��ȣ�� ��ġ�ؾ���, 10000������ ���������ʰ� �Լ��� ��, htons : ȣ��Ʈ����Ʈ�� ��Ʈ��ũ ����Ʈ short�� �ٲ��ִ� �Լ� 
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // ������ �ټ��� Ŭ�� �����ؾ��ϱ⶧���� ������ �������ϰ�, INADDR_ANY ����ǻ�ͷ� �����¾� �ٹްڴ� ��� ��, ��ũ���Լ� ��� ��Ʈ��ȣ�� 10000�� �̾����
	
	// �������� ������ �Լ��� ����� bind, listen, accept
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa)); // ���ϰ� ��ȭ��ȣ ����
	if (iRet == SOCKET_ERROR) return; // 0�ƴѼ��� ������ ����
	// ������� ��Ʈ�� ������ �����۾�
	listen(sock, SOMAXCONN); // sock : ��ȭ�� ����, SOMAXCONN : ���� ��µ� �����ѻ���� ���ôٹ����̸� SOMAXCONN��ŭ ����ְڴ�
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN clientAddr;
	int CALength = sizeof(clientAddr);
	cout << "���� ������....." << endl;

	//������ ���۾��� �ݺ��Ǿ�� �������ڸ��� ������ ��츦 ���ټ�����
	while (1)
	{
		SOCKET clientSock = accept(sock, (sockaddr*)&clientAddr, &CALength); // ���� �ƴ϶� �ּҸ� ���Ѵ�
																		 // �������� �����ؾߵȴ� �������� ��ȭ�ؾ���, accept�� ��ȯŸ�� : ���� accept�� ��ȯ�Ǹ� ���� �����ߴ��� �˷���

		if (clientSock == SOCKET_ERROR) // iRecvByte�� 0�̸� Ŭ�� ������
		{
			int iError = WSAGetLastError();
			cout << "ErrorCode = " << iError << endl;
			// �ͺ��ŷ���� ��ȯ�ɋ� �۾��̾�� ��ȯ�Ȱ�
			if (iError != WSAEWOULDBLOCK) // ��¥ ������ �ƴ��� Ȯ��, ������ ������ ���ŷ������ ������ ����, WSAEWOULDBLOCK�� �߸� ����! WSAEWOULDBLOCK�� �ƴϸ� ����
			{
				break;
			}
			continue;
		}
		cout << "ip = " << inet_ntoa(clientAddr.sin_addr) // ip�� ��Ʈ������ ��ȯ
			<< "port = " << ntohs(clientAddr.sin_port) << " " << endl; // ��Ʈ��ũ����Ʈ���ĵȾָ� ȣ��Ʈ���Ĺ���Ʈ�� ����ϴ°Ŵϱ� ��ȯ

		u_long on = 1;
		ioctlsocket(clientSock, FIONBIO, &on); // Ŭ���̾�Ʈ ������ �ͺ��ŷ���� 

		while (1)
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
			if (iRecvByte == 0) // iRecvByte�� 0�̸� Ŭ�� ������
			{
				cout << "ip = " << inet_ntoa(clientAddr.sin_addr)
					<< "port = " << ntohs(clientAddr.sin_port)
					<< "==> Log Out" << endl;
				break;
			}
			if (iRecvByte == SOCKET_ERROR) // iRecvByte�� 0�̸� Ŭ�� ������
			{
				int iError = WSAGetLastError();
				cout << "ErrorCode = " << iError << endl;
				// �ͺ��ŷ���� ��ȯ�ɋ� �۾��̾�� ��ȯ�Ȱ�
				if (WSAGetLastError() != WSAEWOULDBLOCK) // ��¥ ������ �ƴ��� Ȯ��, ������ ������ ���ŷ������ ������ ����, WSAEWOULDBLOCK�� �߸� ����! WSAEWOULDBLOCK�� �ƴϸ� ����
				{
					break;
				}
			}
			else
			{
				cout << szRecvBuffer << "����" << endl;
				int SendByte = send(clientSock, szRecvBuffer, iRecvByte, 0);
				cout << SendByte << "����." << endl;
			}
		}
		closesocket(clientSock);
	}
	WSACleanup(); 
}