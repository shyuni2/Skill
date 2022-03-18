#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h> // ���� �������
#include <list>
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

// ��� ���� ���α׷����� ������ ȣ���ϱ����� �ݵ�� ���� �ʱ�ȭ �Լ��� ���� ���� ȣ���ؾ���
// ���� �ʱ�ȭ �Լ� : int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
// wVersionRequested ���� MAKEWORD(2,2) ���, lpWSAData��  WSADATA Ÿ���� ����ü�� ���� ������
// ���α׷��� �����Ҷ��� ���� ���� �Լ��� ȣ���ؾ���
// ���� �����Լ� : int WSACleanup(void)

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

void main()
{
	WSADATA WSA; // WSADAD ����ü �̸��� WSA�� ����
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0) // �����ʱ�ȭ�Լ� WSAStartup�� 0�� �ƴҶ�
	{
		return;
	}
	// ������ �帧
	// 1. listen()(Ŭ�� �����ϴ°� �����ϱ⶧��) �̶�� ������ ����
	// 2.	-> ���ε� bind �۾�(Ŭ�󿡼� ����) : ���Ͽ� ��ȭ��ȣ�� �����Ѵ�(Ŭ�󿡼� �Է¸��ϸ��)
	// 3.	-> ��ȭ�ðŸ� ��ٸ��»���
	// 4.	-> ��ȭ���� ���� / accept() ���°��� ������ Ŭ���̾�Ʈ�� ����� ������ ��ȭ�ߴ��� �����ߴ��� �˼�����
	// 5.	-> recv, send�۾��ϸ��

	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0); // socket(������ �ּ�ü��, ����Ÿ�� , ����� ��������)
														 // AF_INET : ���ͳ� �������� ���, SOCK_STREAM : TCP���, �ι�° ���ڿ��� ����ϴ°� ���� �ڵ����� Ÿ�� �����ִ� �򰥸��� �ʰ� 0���� ������ ��
	SOCKADDR_IN SAddr; // ����� ���������� ������ �´� ���� ����ü ���
					   // �Լ� ���ڷ� ����Ҷ��� �׻� �ּҰ��� �����ϸ� �ݵ�� ������������ ��ȯ�ؼ� ����ؾ��Ѵ�
	ZeroMemory(&SAddr, sizeof(SAddr)); // �ϴ� �޸��ʱ�ȭ�� ����
	SAddr.sin_family = AF_INET; // �ּ�ü�踦 ��Ÿ���� �׻� AF_INET�� ����Ѵ�
	SAddr.sin_port = htons(10000); // 10000������ ����, ������ ��Ʈ��ȣ�� ��ġ�ؾ���, 10000������ ���������ʰ� htons�Լ��� �� ���� : ȣ��Ʈ����Ʈ�� ��Ʈ��ũ����Ʈ short�� �ٲ������, ����Ʈ �����Լ�
	SAddr.sin_addr.s_addr = htonl(INADDR_ANY); // �������ּҸ� ��Ÿ��, ������ �ټ��� Ŭ�� �����ؾ��ϱ⶧���� ������ �������ϰ�, INADDR_ANY ����ǻ�ͷ� �����¾� �ٹްڴ� ��� ��ũ���Լ�

	// ���ε� �۾�
	int Ret = bind(ListenSock, (sockaddr*)&SAddr, sizeof(SAddr)); // bind(Ŭ���̾�Ʈ ������ ������ �������� ���� ����, �����ּ� ����ü, �����ּ� ����ü ����
																 // ���� = 0, ���� = SOCKET_ERROR
	if (Ret == SOCKET_ERROR) return; // ���ε��Լ� ���ϰ��� ������ ����
	// ���� �۾�
	Ret = listen(ListenSock, SOMAXCONN); // listen(bind�Լ��� ���� �������ּҿ� ������Ʈ��ȣ�� ������ ����, ���Ӱ����� Ŭ���̾�Ʈ ����)
										  // SOMAXCONN : ���������� �ִ밪 ���
	if (Ret == SOCKET_ERROR) return; // �����Լ� ���ϰ��� ������ ����

	SOCKADDR_IN ClientAddr; // �������� ������ �Լ����ڷ� ����Ҷ��� �׻� �ּҰ��� �����ϸ� �ݵ�� ������������ ��ȯ�ؼ� ����ؾ���
	int AddrC = sizeof(ClientAddr); // Ŭ���̾�Ʈ�ּҸ� ��� ����

	cout << "���� ����� >" << endl; // ������ ��������� ����ϴ� �޼���

	// ����ŷ ���� �����
	u_long on = 1; // u_long : ����Ʈ �����Լ�
	ioctlsocket(ListenSock, FIONBIO, &on); // ioctlsocket(����ŷ���� ���� ����, ���Ͽ����� ������ ������ �ǹ��ϴ� Ŀ�ǵ�, 0�̸� ���ŷ��尡 �ǰ� 0�̾ƴѰ��� ������ ����ŷ���� ����)

	// ����Ʈ �����Լ���? ����Ʈ ���Ĺ���� Ʋ����� �߸��� �����Ͱ� ���޵� ���ɼ��� �ִ� 
	// �̷��� ��ȣ���� ���ֱ� ���ؼ� �������ּҿ� ��Ʈ��ȣ�� ����Ʈ ���� ����� �򿣵������ ���ϵǾ��ִ�. 
	// �׷���, ���� ���μ��������� ����Ʈ ������ ��Ʋ����� ������� �ϰ��־ �������ּҿ� ��Ʈ��ȣ�� �����ϴ� ��İ� ���� �ʴ�.
	// ���� �򿣵���� ��Ʈ��ũ ����Ʈ �����̶���ϰ� �ý����� ����ϴ� ���� ����� ȣ��Ʈ ����Ʈ �����̶� �Ѵ�.
	// ����Ʈ ���� �Լ��� ���� htonl() �̶�� �Ǿ��ִµ� h�� ȣ��Ʈ n�� ��Ʈ��ũ l,s�� long��, short�� �̴� ��Ȳ������ �°� ����ϸ� ��

	// ���ŷ, ����ŷ�̶� ? 
	// ���ŷ�� � �ý����� �������� ��Ʈ��ũ �ý����� ���ۿϷ��Ҷ����� ��������
	// ����ŷ�� �ý����ݿ� ���Ͽ� ��Ʈ��ũ �ý����� ���ó���Ҽ����� ���� �ý������� ���ϵǾ� ��ϵ����ʰ� ��

	list<User> userlist; // ��������Ʈ�� �˱����� ���, �迭������ϸ� �������� ��Ȳ�� ����ؾ��ϱ� ������ list�����

	//������ ���۾��� �ݺ��Ǿ�� �������ڸ��� ������ ��츦 ���ټ�����
	while (1)
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &AddrC); // accept(Ŭ���̾�Ʈ ������ �����Ҹ������� ���� ����, �����ּ� ����ü ������ ����, ���� ����ü�� ũ�⸦ ��Ÿ���� ������ ������ �ּ�)

		// Ŭ���̾�Ʈ ���� �������� �ڵ�
		if (ClientSock == SOCKET_ERROR) // Ŭ���̾�Ʈ ������ �����̸�
		{
			int Error = WSAGetLastError(); // ���� �����ڵ�
			if (Error != WSAEWOULDBLOCK) // 
			{
				cout << "Error Code = " << Error << endl; // �����ڵ� ���, ���� error�� int�� �Ǿ����� char�� �ؼ� ���ڷ� ������������ �� �����ϰ� ����غ���
				break;
			}
		}
		else // Ŭ���̾�Ʈ ������ ������ �ƴϸ�
		{
			User user;
			user.set(ClientSock, ClientAddr);
			userlist.push_back(user); // ��������Ʈ �ڿ� ���� Ǫ����
			cout << "ip =" << inet_ntoa(ClientAddr.sin_addr) << "port =" << ntohs(ClientAddr.sin_port) << " ==> Log In" << endl; // inet_ntoa : ��Ʈ��ũ ����Ʈ ���� ����� 4����Ʈ �ּҸ� ���ڿ��ּҷ� ǥ��
			// ����ŷ���� �����
			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);
			cout << userlist.size() << " �� ������ >" << endl;
		}

		// ��������Ʈ ���� �ڵ�
		if (userlist.size() > 0) // ������ �Ѹ��̶� ������
		{
			list <User> ::iterator Sockiter; // ���Ϲݺ��ڻ���
			for (Sockiter = userlist.begin(); Sockiter != userlist.end(); ) // for������ Sockiter�� ++�Ǹ� ������ ���ﶧ ����ؾ���, erase�� ��ȯ�� �߿�
			{
				User user = *Sockiter; // ���Ϲݺ��� ������ ����
				char szRecvBuffer[256] = { 0, };
				int RecvByte = recv(user.user_sock, szRecvBuffer, 256, 0); // recv : ������ �ְ�޴� �Լ�
																	 // recv(��Ŵ��� ����� ����, ���� �����͸� ������ ����(char���̾����), �����͹����� ũ��, Ư���� �ɼ��� �ֱ����� - �Ⱦ��� 0)
																	 // ���� : ���� ����Ʈ�� �Ǵ� 0, ���� : SOCKET_ERROR
				if (RecvByte == 0) // RecvByte�� 0�̸� Ŭ�� ������
				{
					cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> Log Out" << endl;
					break;
					closesocket(user.user_sock);
					Sockiter = userlist.erase(Sockiter);
				}
				if (RecvByte == SOCKET_ERROR) // ���ú��Լ��� �����϶�
				{
					int Error = WSAGetLastError();
					//cout << "Error Code = " << Error << endl; // �����ڵ� ����ϰ�
					if (Error != WSAEWOULDBLOCK) // ������ WSAEWOULDBLOCK�� �ƴϸ�
					{
						Sockiter = userlist.erase(Sockiter);
					}
					else // ������ WSAEWOULDBLOCK�̸�
					{
						Sockiter++;
					}
				}
				else // ���ú��Լ��� ������ �ƴҶ�
				{
					list<User> ::iterator Senditer; // ����ݺ��� ����
					for (Senditer = userlist.begin(); Senditer != userlist.end(); ) // ����ݺ��ڰ� ��������Ʈ�� ó������ ���������� 
					{
						User user = *Senditer; // ����ݺ��� ������ ����
						cout << szRecvBuffer << "����" << endl; // ����ڰ� �Է��� ���� ��� �Լ�
						int SendByte = send(user.user_sock, szRecvBuffer, RecvByte, 0); // send : �����͸� �޴� �Լ�
																				  // send(����� ���� ����� ����, ���������͸� ����ִ� ����, ���� ������ ũ��, Ư���� �ɼ��� �ֱ����� - �Ⱦ��� 0)
																				  // ���� : ���� ����Ʈ�� �Ǵ� 0, ���� : SOCKET_ERROR
						cout << user.user_sock << ":" << SendByte << "����" << endl;

						if (SendByte == SOCKET_ERROR) // ���ú��Լ��� �����϶�
						{
							int Error = WSAGetLastError();
							cout << "Error Code = " << Error << endl; // �����ڵ� ����ϰ�
							if (Error != WSAEWOULDBLOCK) // ������ WSAEWOULDBLOCK�� �ƴϸ�
							{
								closesocket(user.user_sock);
								Senditer = userlist.erase(Senditer);
								cout << user.user_name << "������ ��������" << endl;
							}
							else // ������ WSAEWOULDBLOCK�̸�
							{
								Senditer++;
							}
						}
						if (Sockiter != userlist.end()) // ��������Ʈ ������ �ڿ��� �����ϱ�
						{
							Sockiter++;
						}
						
					}
				}
			}
		}
	}
	closesocket(ListenSock);
	WSACleanup(); // ���� �����Լ�
}
					
