#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "NetUser.h"

list<NetUser> m_UserList; // 지역에서 전역으로 빼줌
CRITICAL_SECTION CS; // 크리티컬섹션 이름

// 보내는 함수
int SendMsg(SOCKET sock, char*msg, WORD type)
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
// 브로드캐스트 함수
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

// 받는함수
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
	user.DispatchRead(szRecvBuffer, RecvByte); // 유저마다 저장소가 있어야됨
	return 1;
}
// 스레드 생성, 스레드 함수를 벗어나는 일이 발생하면 쓰레드 종료가 된다
// 받는 스레드
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
		Sleep(1); // 스위칭
	}
}
// 보내는 스레드
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
		Sleep(1); // 스위칭
	}
}


void main()
{
	InitializeCriticalSection(&CS); // 초기화할 크리티컬 섹션 포인터 전달
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

	cout << "--- 서버 실행중 ---" << endl;

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);

	// 스레드 생성 
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread(
		0, // 보안속성, 0은 기본사이즈만 쓰겠다는 의미
		0, // 스택 크기 지정, 0은 기본사이즈만 쓰겠다는 의미
		SendTread, // 반환, 
		(LPVOID)ListenSock, // 소켓을 넘겨줘야 send를 함
		0,// 쓰레드 만들자마자 일시킬래 or 대기시켜놓고 원하는 시점에 일시킬래? 정할수있는 자리, 0을 넣으면 쓰레드를 만들자마자 SendTread를 실행
		&ThreadIdSend // 생성된 쓰레드에대한 인덱스를 반환해준다 , 종업원의 번호라고 생각
	);
	CloseHandle(hThreadSend); // 이렇게 놔도 쓰레드 돌아가는덴 문제가 없음, 관리를 안하겠다는 뜻이지 쓰레드를 종료한다는 뜻이 아님, 내가 제어안할래~

	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread(
		0,
		0, // 0은 기본사이즈만 쓰겠다는 의미
		RecvThread, // 반환, 
		(LPVOID)ListenSock, // 소켓을 넘겨줘야 recv를 함
		0,// 쓰레드 만들자마자 일시킬래 or 대기시켜놓고 원하는 시점에 일시킬래? 정할수있는 자리, 0을 넣으면 쓰레드를 만들자마자 RecvTread를 실행
		&ThreadIdRecv // 생성된 쓰레드에대한 인덱스를 반환해준다 , 종업원의 번호라고 생각
	);
	CloseHandle(hThreadRecv);

	// 메인스레드 작업
	while (1)
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &CAlength);
		if (ClientSock == SOCKET_ERROR)
		{
			int error = WSAGetLastError(); // WSAGetLastError 가장 최근에 발생한 소켓에러의 정보값
			if (error != WSAEWOULDBLOCK)
			{
				cout << "ErrorCode = " << error << endl;
				break;
			}
		}
		else // 에러가 아니면 정상 작동해야함
		{
			NetUser user;
			user.set(ClientSock, ClientAddr);
			EnterCriticalSection(&CS);
			m_UserList.push_back(user);
			LeaveCriticalSection(&CS);

			cout << "IP = " << inet_ntoa(ClientAddr.sin_addr) << "Port = " << ntohs(ClientAddr.sin_port) << " " << endl;

			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);
			cout << m_UserList.size() << "명 접속중" << endl;
		}
		Sleep(1);
	}
	cout << "접속종료" << endl;
	
	closesocket(ListenSock);
	WSACleanup();

	DeleteCriticalSection(&CS); // 크리티컬 섹션 소멸
}