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
	// 1. ���Ͽ���
	SOCKET sock = socket
	(
		AF_INET, // �ּ�ü�� ���� : ���ͳ��������� ����ϰڴ�
		SOCK_STREAM, // ����Ÿ�� ���� : TCP ����ϰڴ�, STREAM ���� TCP, DGRAM ���� UDP ���� �ϳ� ����ϸ��
		0 // ����� �������� ���� : �ι�° ���ڿ��� ����ϴ°� ���� �ڵ����� �������ִ� ��������
	);
	//sockaddr sa; // �����ּ� �����
	//CHAR sa_data[14]; // IP,PORT
	SOCKADDR_IN sa; // �̰� ����ϸ� ���� �ּ� �����ص� ��
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // 10000������ ����, ������ ��Ʈ��ȣ�� ��ġ�ؾ���, 10000������ ���������ʰ� �Լ��� ��, htons : ȣ��Ʈ����Ʈ�� ��Ʈ��ũ ����Ʈ short�� �ٲ��ִ� �Լ� 
	// ����Ʈ ���� �տ������� ������ �ڿ��� ���� ������?
	sa.sin_addr.s_addr = inet_addr("192.168.0.12"); // ���ڿ��� ������ �ٲ������,���ڿ��� 4����Ʈ�� �ٲ��ִ� �Լ� ���� inet_addr
	// ��Ʈ��ũ���� ������ �������� ��ȯ���ִ°��Է�
	int iRet = connect
	(
		sock,
		(sockaddr*)&sa,// ���� �ּҸ� ���� �־�����
		sizeof(sa)
	); // Ŀ����
	char szBuffer[] = "�ȳ��ϼ���"; // Ŭ�� �����°� ������ �������ڸ��� ������ �޼����� ���� �� ����
	int SendByte = send
	(
		sock,
		szBuffer,// ���� �ּҸ� ���� �־�����
		sizeof(szBuffer[256]),
		0
	); // Ŀ����
	char szRecvBuffer[256] = { 0, };
	int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
	cout << szRecvBuffer;
	closesocket(sock); // Ŭ�󿡼��� ������ ����
	WSACleanup();
}