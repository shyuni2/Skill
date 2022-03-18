#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <list>
#include <string>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")

using namespace std;

struct User // 유저 설정
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
	// 1. 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	// 2. 패킷 전송
	char* pMsg = (char*)&packet;
	int SendSize = 0;
	do {
		int SendByte = send(sock, &pMsg[SendSize], packet.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1; // 오류
			}
		}
	} while (SendSize < packet.ph.len); // do while 쓴 이유 : 일단 메세지를 보내기는 해야하기때문에, 보낼 길이가 패킷헤더길이 보다 작을때까지 반복
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
				return -1; // 오류
			}
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len); 
	return SendSize;
}

// 패킷을 추가해서 조금만 달라질뿐 기존과 크게 변하는건 없다

void main()
{
	WSADATA WSA;
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SAddr; // 함수 인자로 사용할때는 항상 주소값을 전달하며 반드시 포인터형으로 반환해서 사용해야한다
	ZeroMemory(&SAddr, sizeof(SAddr)); // 일단 메모리초기화를 해줌
	SAddr.sin_family = AF_INET;
	SAddr.sin_port = htons(10000);
	SAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 바인드 작업
	int Ret = bind(ListenSock, (sockaddr*)&SAddr, sizeof(SAddr)); // bind(클라이언트 접속을 수용할 목적으로 만든 소켓, 소켓주소 구조체, 소켓주소 구조체 길이
	if (Ret == SOCKET_ERROR) return; // 바인드함수 리턴값이 에러면 리턴
	// 리슨 작업
	Ret = listen(ListenSock, SOMAXCONN); // listen(bind함수에 의해 아이피주소와 지역포트번호가 설정된 소켓, 접속가능한 클라이언트 개수)
	if (Ret == SOCKET_ERROR) return; // 리슨함수 리턴값이 에러면 리턴

	SOCKADDR_IN ClientAddr; // 위에서도 썼지만 함수인자로 사용할때는 항상 주소값을 전달하며 반드시 포인터형으로 반환해서 사용해야함
	int AddrC = sizeof(ClientAddr); // 클라이언트주소를 담는 변수

	cout << "서버 연결됨 >" << endl; // 서버가 연결됐을때 출력하는 메세지

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on); // ioctlsocket(논블로킹으로 만들 소켓, 소켓에대한 수행할 동작을 의미하는 커맨드, 0이면 블로킹모드가 되고 0이아닌값을 넣으면 논블로킹모드로 설정)

	list<User> userlist; // 유저리스트를 알기위해 사용, 배열을사용하면 빠졌을때 상황을 고려해야하기 때문에 list사용함

	//서버는 이작업이 반복되어야 실행하자마자 꺼지는 경우를 없앨수있음
	while (1)
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &AddrC); // accept(클라이언트 접속을 수용할목적으로 만든 소켓, 소켓주소 구조체 변수를 정의, 소켓 구조체의 크기를 나타내는 정수형 변수의 주소)

		if (ClientSock == SOCKET_ERROR) // 클라이언트 소켓이 에러이면
		{
			int Error = WSAGetLastError(); // 소켓 오류코드
			if (Error != WSAEWOULDBLOCK) // 
			{
				cout << "Error Code = " << Error << endl; // 오류코드 출력
				break;
			}
		}
		else // 클라이언트 소켓이 에러가 아니면
		{
			User user;
			user.set(ClientSock, ClientAddr);
			userlist.push_back(user); // 유저리스트 뒤에 유저 푸쉬백

			cout << "ip =" << inet_ntoa(ClientAddr.sin_addr) << "port =" << ntohs(ClientAddr.sin_port) << " ==> Log In" << endl; // inet_ntoa : 네트워크 바이트 정렬 방식의 4바이트 주소를 문자열주소로 표현

			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);

			cout << userlist.size() << " 명 접속중 >" << endl;
		}

		// 유저리스트 관리 코드 > 여기서 패킷을 넣음
		if (userlist.size() > 0) // 유저가 한명이라도 있을때
		{
			list <User> ::iterator Sockiter; // 소켓반복자생성
			for (Sockiter = userlist.begin(); Sockiter != userlist.end(); ) // for문에서 Sockiter가 ++되면 나가고 지울때 고려해야함, erase의 반환값 중요
			{
				User user = *Sockiter; // 소켓반복자 포인터 설정
				char szRecvBuffer[256] = { 0, };
				// 패킷 헤더 받기
				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int RecvSize = 0;
				do {
					int RecvByte = recv(user.user_sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);// recv(통신대상과 연결된 소켓, 받은 데이터를 저장할 버퍼(char형이어야함), 데이터버퍼의 크기, 특별한 옵션을 주기위함 - 안쓰면 0)
					RecvSize += RecvByte;
					if (RecvByte == 0) // RecvByte가 0이면 클라 나간거
					{
						closesocket(user.user_sock); // 나갔으면 닫아주고
						Sockiter = userlist.erase(Sockiter); // 지워준다

						cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> Log Out" << endl;
						continue;
					}
					if (RecvByte != SOCKET_ERROR)
					{
						int Error = WSAGetLastError();
						if (Error != WSAEWOULDBLOCK)
						{
							Sockiter = userlist.erase(Sockiter);

							cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> 비정상 접속종료" << endl;
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

				// 데이터 받기
				RecvSize = 0;
				do {
					int RecvByte = recv(user.user_sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - RecvSize, 0);
					RecvSize += RecvByte;
					if (RecvByte == 0)
					{
						closesocket(user.user_sock);
						Sockiter = userlist.erase(Sockiter);
						cout << user.user_name << "접속종료" << endl;
						continue;
					}
					if (RecvByte == SOCKET_ERROR)
					{
						int Error = WSAGetLastError();
						if (Error != WSAEWOULDBLOCK)
						{
							Sockiter = userlist.erase(Sockiter);
							cout << "ip = " << inet_ntoa(ClientAddr.sin_addr) << "port = " << ntohs(ClientAddr.sin_port) << " ==> 비정상 접속종료" << endl;
						}
						else
						{
							Sockiter++;
						}
					}
				} while (RecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE); // 짤린데이터를 다 받아야하기 때문에

				Packet data;
				data.m_uPacket = recvPacket;
				ChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));

				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				cout << "\n" << "[ " << recvdata.name << " ]" << recvdata.message;

				// 패킷 완성
				list<User> ::iterator Senditer;
				for (Senditer = userlist.begin(); Senditer != userlist.end(); )
				{
					User user = *Senditer;
					int SendMsgSize = SendMsg(user.user_sock, recvPacket);
					if (SendMsgSize < 0)
					{
						closesocket(user.user_sock);
						Senditer = userlist.erase(Senditer);
						cout << user.user_name << "비정상 접속종료" << endl;
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
	WSACleanup(); // 윈속 종료함수
}
