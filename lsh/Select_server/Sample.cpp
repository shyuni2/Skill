#include "TNetwork.h"


// return에서 정상종료는 0 , 에러가나서 종료되는건 -1

list<TNetUser> userlist;

// 메세지 보내는 함수 
int SendMsg(SOCKET sock, char*msg, WORD type)
{
	// 1번 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	// 2번 패킷 전송 : 운영체제 sendbuffer(short바이트), recvbuffer
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
			// 넌블로킹일때 사용한거라 지금은 필요없음
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len);
	return SendSize;
}

// 유저추가
int AddUser(SOCKET sock) 
{
	SOCKADDR_IN ClientAddr;
	int CALength = sizeof(ClientAddr);
	SOCKET Clientsock = accept(sock, (sockaddr*)&ClientAddr, &CALength);
	if (Clientsock == SOCKET_ERROR)
	{
		return -1;
	}
	else
	{
		TNetUser user;
		user.set(Clientsock, ClientAddr);
		userlist.push_back(user);
		cout << " ip = " << inet_ntoa(ClientAddr.sin_addr) << " port = " << ntohs(ClientAddr.sin_port) << " " << endl;
		cout << userlist.size() << "명 접속중" << endl;
	}
	return 1;
}

// 메세지 받는 함수
int RecvUser(TNetUser& user)
{
	char szRecvBuffer[1024] = { 0, };
	int iRecvByte = recv(user.m_Sock, szRecvBuffer, 256, 0);
	if (iRecvByte == 0)
	{
		closesocket(user.m_Sock);
		return 0;
	}
	if (iRecvByte == SOCKET_ERROR)
	{
		return -1;
	}
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}

void main()
{
	TNetwork net;
	net.InitNetwork();
	net.InitServer(SOCK_STREAM, 10000); // TCP방식 , 포트번호

	SOCKADDR_IN clientAddr;
	int CALength = sizeof(clientAddr);

	cout << "서버 연결됨> " << endl;

	// select를 사용할거라, 아래 주석 처리해서 블로킹 상태 만듬
	// u_long on = 1;
	// ioctlsocket(ListenSock, FIONBIO, &on);
	
	FD_SET rSet; // readset,  누가 들어왔거나 메세지가 도착했거나
	FD_SET wSet; // writeset,  누가 메세지를 보냈거나
	// timeval timeout;
	while (1)
	{
		// 셀렉트쓰면 좋은점 스레드 안쓰고 블로킹 넌블로킹 안따짐, 대신 사용법이 귀찮음 매번 반복할때마다 초기화하고 설정을 해줘야함
		// 초기화 작업
		// FD_SET은 구조체 배열이다, 쓰레기값이 있을수있으니 FD_ZERO를 이용해 초기화를 사용해야함
		FD_ZERO(&rSet); // accept, recv
		FD_ZERO(&wSet); // send
		// 설정
		FD_SET(net.m_ListenSock, &rSet); // 리슨소켓에 누가 들어왔거나 메세지를 보냈다는 걸 확인함
		
		list<TNetUser>::iterator useriter;
		for (useriter = userlist.begin(); useriter != userlist.end();)
		{
			if ((*useriter).m_bConnect == false)
			{
				cout << (*useriter).m_csName << "접속종료됨" << endl;
				useriter = userlist.erase(useriter);
				continue;
			}
			FD_SET((*useriter).m_Sock, &rSet);
			// 만약 user에서 보낸 패킷이 있으면
			if ((*useriter).m_packetPool.size() > 0)
			{
				FD_SET((*useriter).m_Sock, &wSet);
			}
			useriter++;
		}
		// 현재 블로킹 상태기때문에 
		int iRet = select( // 반환값에 따라서 작업이 가능
			0, // 무조건 0
			&rSet,
			&wSet,
			NULL,
			NULL // 타임아웃 쓰면 타임아웃일때 조건을 설정할수있음
		);
		if (FD_ISSET(net.m_ListenSock, &rSet)) // 반환되면 누가 들어왔거나 메세지를 보냈다는거임
		{
			// accept(), userlist 추가 처리해야함
			if (AddUser(net.m_ListenSock) < 0)
			{
				break;
			}
		}
		
		for (TNetUser& user : userlist)
		{
			if (FD_ISSET(user.m_Sock, &rSet)) // 반환되면 누가 들어왔거나 메세지를 보냈다는거임
			{
				// recv() 해야함
				int iRet = RecvUser(user);
				if (iRet <= 0) // 리시브 값이 0보다 작거나 같으면 유저랑 연결 안됐다는 뜻
				{
					user.m_bConnect = false; // 연결실패
				} 
			}
		}
		for (TNetUser& user : userlist) 
		{
			if (FD_ISSET(user.m_Sock, &wSet)) // wSet이 반환됐다 -> 지금 보낼수있다
			{
				// send() 해야함
				if (user.m_packetPool.size() > 0)
				{
					// 중간에 나간거 리스트 삭제하면 안됨 일괄작업하는게 좋다
					list<TPacket>::iterator iter;
					for (iter = user.m_packetPool.begin(); iter != user.m_packetPool.begin(); )
					{
						for (TNetUser& senduser : userlist)
						{
							int iRet = SendMsg(senduser.m_Sock, (*iter).m_uPacket);
							if (iRet <= 0)
							{
								senduser.m_bConnect = false;
							}
						}
						iter = user.m_packetPool.erase(iter);
					}
				}
			}
		}
	}
	net.CloseNetwork();
}