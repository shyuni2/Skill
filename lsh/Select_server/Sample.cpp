#include "TNetwork.h"


// return���� ��������� 0 , ���������� ����Ǵ°� -1

list<TNetUser> userlist;

// �޼��� ������ �Լ� 
int SendMsg(SOCKET sock, char*msg, WORD type)
{
	// 1�� ��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	// 2�� ��Ŷ ���� : �ü�� sendbuffer(short����Ʈ), recvbuffer
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
			// �ͺ��ŷ�϶� ����ѰŶ� ������ �ʿ����
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len);
	return SendSize;
}

// �����߰�
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
		cout << userlist.size() << "�� ������" << endl;
	}
	return 1;
}

// �޼��� �޴� �Լ�
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
	net.InitServer(SOCK_STREAM, 10000); // TCP��� , ��Ʈ��ȣ

	SOCKADDR_IN clientAddr;
	int CALength = sizeof(clientAddr);

	cout << "���� �����> " << endl;

	// select�� ����ҰŶ�, �Ʒ� �ּ� ó���ؼ� ���ŷ ���� ����
	// u_long on = 1;
	// ioctlsocket(ListenSock, FIONBIO, &on);
	
	FD_SET rSet; // readset,  ���� ���԰ų� �޼����� �����߰ų�
	FD_SET wSet; // writeset,  ���� �޼����� ���°ų�
	// timeval timeout;
	while (1)
	{
		// ����Ʈ���� ������ ������ �Ⱦ��� ���ŷ �ͺ��ŷ �ȵ���, ��� ������ ������ �Ź� �ݺ��Ҷ����� �ʱ�ȭ�ϰ� ������ �������
		// �ʱ�ȭ �۾�
		// FD_SET�� ����ü �迭�̴�, �����Ⱚ�� ������������ FD_ZERO�� �̿��� �ʱ�ȭ�� ����ؾ���
		FD_ZERO(&rSet); // accept, recv
		FD_ZERO(&wSet); // send
		// ����
		FD_SET(net.m_ListenSock, &rSet); // �������Ͽ� ���� ���԰ų� �޼����� ���´ٴ� �� Ȯ����
		
		list<TNetUser>::iterator useriter;
		for (useriter = userlist.begin(); useriter != userlist.end();)
		{
			if ((*useriter).m_bConnect == false)
			{
				cout << (*useriter).m_csName << "���������" << endl;
				useriter = userlist.erase(useriter);
				continue;
			}
			FD_SET((*useriter).m_Sock, &rSet);
			// ���� user���� ���� ��Ŷ�� ������
			if ((*useriter).m_packetPool.size() > 0)
			{
				FD_SET((*useriter).m_Sock, &wSet);
			}
			useriter++;
		}
		// ���� ���ŷ ���±⶧���� 
		int iRet = select( // ��ȯ���� ���� �۾��� ����
			0, // ������ 0
			&rSet,
			&wSet,
			NULL,
			NULL // Ÿ�Ӿƿ� ���� Ÿ�Ӿƿ��϶� ������ �����Ҽ�����
		);
		if (FD_ISSET(net.m_ListenSock, &rSet)) // ��ȯ�Ǹ� ���� ���԰ų� �޼����� ���´ٴ°���
		{
			// accept(), userlist �߰� ó���ؾ���
			if (AddUser(net.m_ListenSock) < 0)
			{
				break;
			}
		}
		
		for (TNetUser& user : userlist)
		{
			if (FD_ISSET(user.m_Sock, &rSet)) // ��ȯ�Ǹ� ���� ���԰ų� �޼����� ���´ٴ°���
			{
				// recv() �ؾ���
				int iRet = RecvUser(user);
				if (iRet <= 0) // ���ú� ���� 0���� �۰ų� ������ ������ ���� �ȵƴٴ� ��
				{
					user.m_bConnect = false; // �������
				} 
			}
		}
		for (TNetUser& user : userlist) 
		{
			if (FD_ISSET(user.m_Sock, &wSet)) // wSet�� ��ȯ�ƴ� -> ���� �������ִ�
			{
				// send() �ؾ���
				if (user.m_packetPool.size() > 0)
				{
					// �߰��� ������ ����Ʈ �����ϸ� �ȵ� �ϰ��۾��ϴ°� ����
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