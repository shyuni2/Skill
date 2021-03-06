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
	// 1. 소켓연결
	SOCKET sock = socket
	(
		AF_INET, // 주소체계 지정 : 인터넷프로토콜 사용하겠다
		SOCK_STREAM, // 소켓타입 지정 : TCP 사용하겠다, STREAM 쓰면 TCP, DGRAM 쓰면 UDP 둘중 하나 사용하면됨
		0 // 사용할 프로토콜 지정 : 두번째 인자에서 사용하는걸 보고 자동으로 지정해주니 넣지말자
	);
	//sockaddr sa; // 소켓주소 만들기
	//CHAR sa_data[14]; // IP,PORT
	SOCKADDR_IN sa; // 이걸 사용하면 위에 주석 사용안해도 됨
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // 10000번으로 접속, 서버랑 포트번호가 일치해야함, 10000번으로 직접넣지않고 함수를 씀, htons : 호스트바이트를 네트워크 바이트 short로 바꿔주는 함수 
	// 바이트 정렬 앞에서부터 넣을래 뒤에서 부터 넣을래?
	sa.sin_addr.s_addr = inet_addr("192.168.0.12"); // 문자열을 일일히 바꿔줘야함,문자열을 4바이트로 바꿔주는 함수 존재 inet_addr
	// 네트워크에선 무조건 정수말고 변환해주는걸입력
	int iRet = connect
	(
		sock,
		(sockaddr*)&sa,// 소켓 주소를 만들어서 넣어주자
		sizeof(sa)
	); // 커넥팅
	char szBuffer[] = "안녕하세요"; // 클라가 보내는거 서버가 접속하자마자 보내는 메세지를 만들 수 있음
	int SendByte = send
	(
		sock,
		szBuffer,// 소켓 주소를 만들어서 넣어주자
		sizeof(szBuffer[256]),
		0
	); // 커넥팅
	char szRecvBuffer[256] = { 0, };
	int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
	cout << szRecvBuffer;
	closesocket(sock); // 클라에서도 나가기 설정
	WSACleanup();
}