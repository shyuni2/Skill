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
	// 1. 소켓연결 소켓만드는건 서버랑 클라랑 다르지않음
	SOCKET sock = socket
	(
		AF_INET, // 주소체계 지정 : 인터넷프로토콜 사용하겠다
		SOCK_STREAM, // 소켓타입 지정 : TCP 사용하겠다, STREAM 쓰면 TCP, DGRAM 쓰면 UDP 둘중 하나 사용하면됨
		0 // 사용할 프로토콜 지정 : 두번째 인자에서 사용하는걸 보고 자동으로 지정해주니 넣지말자
	); 

	SOCKADDR_IN sa; 
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // 10000번으로 접속, 서버랑 포트번호가 일치해야함, 10000번으로 직접넣지않고 함수를 씀, htons : 호스트바이트를 네트워크 바이트 short로 바꿔주는 함수 
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // 서버는 다수의 클라가 접속해야하기때문에 아이피 지정안하고, INADDR_ANY 내컴퓨터로 들어오는애 다받겠다 라는 뜻, 매크로함수 대신 포트번호는 10000번 이어야함
	
	// 서버에선 세개의 함수를 써야함 bind, listen, accept
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa)); // 소켓과 전화번호 연결
	if (iRet == SOCKET_ERROR) return; // 0아닌수가 나오면 오류
	// 여기까지 포트가 서버랑 연결작업
	listen(sock, SOMAXCONN); // sock : 전화기 연결, SOMAXCONN : 내가 듣는데 접속한사람이 동시다발적이면 SOMAXCONN만큼 들어주겠다
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN clientAddr;
	int CALength = sizeof(clientAddr);
	cout << "서버 가동중....." << endl;

	//서버는 이작업이 반복되어야 실행하자마자 꺼지는 경우를 없앨수있음
	while (1)
	{
		SOCKET clientSock = accept(sock, (sockaddr*)&clientAddr, &CALength); // 값이 아니라 주소를 원한다
																		 // 소켓으로 연결해야된다 소켓으로 대화해야함, accept가 반환타입 : 소켓 accept가 반환되면 누가 접속했는지 알려줌

		if (clientSock == SOCKET_ERROR) // iRecvByte가 0이면 클라 나간거
		{
			int iError = WSAGetLastError();
			cout << "ErrorCode = " << iError << endl;
			// 넌블로킹으로 반환될떈 작업이없어서 반환된거
			if (iError != WSAEWOULDBLOCK) // 진짜 오륜지 아닌지 확인, 에러긴 에런데 블로킹에러가 같으면 오류, WSAEWOULDBLOCK가 뜨면 정상! WSAEWOULDBLOCK가 아니면 오류
			{
				break;
			}
			continue;
		}
		cout << "ip = " << inet_ntoa(clientAddr.sin_addr) // ip를 스트링으로 변환
			<< "port = " << ntohs(clientAddr.sin_port) << " " << endl; // 네트워크바이트정렬된애를 호스트정렬바이트로 출력하는거니까 변환

		u_long on = 1;
		ioctlsocket(clientSock, FIONBIO, &on); // 클라이언트 소켓을 넌블로킹으로 

		while (1)
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
			if (iRecvByte == 0) // iRecvByte가 0이면 클라 나간거
			{
				cout << "ip = " << inet_ntoa(clientAddr.sin_addr)
					<< "port = " << ntohs(clientAddr.sin_port)
					<< "==> Log Out" << endl;
				break;
			}
			if (iRecvByte == SOCKET_ERROR) // iRecvByte가 0이면 클라 나간거
			{
				int iError = WSAGetLastError();
				cout << "ErrorCode = " << iError << endl;
				// 넌블로킹으로 반환될떈 작업이없어서 반환된거
				if (WSAGetLastError() != WSAEWOULDBLOCK) // 진짜 오륜지 아닌지 확인, 에러긴 에런데 블로킹에러가 같으면 오류, WSAEWOULDBLOCK가 뜨면 정상! WSAEWOULDBLOCK가 아니면 오류
				{
					break;
				}
			}
			else
			{
				cout << szRecvBuffer << "받음" << endl;
				int SendByte = send(clientSock, szRecvBuffer, iRecvByte, 0);
				cout << SendByte << "보냄." << endl;
			}
		}
		closesocket(clientSock);
	}
	WSACleanup(); 
}