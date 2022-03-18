#include "Accepter.h"
#include "Server.h"
#include <WS2tcpip.h>

bool Accepter::Run()
{
	Server* pServer = (Server*)m_pObject;
	SOCKET sock = pServer->m_ListenSock;
	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);

	while (1)
	{
		SOCKET ClientSock = accept(pServer->m_ListenSock, (sockaddr*)&ClientAddr, &iLen);
		if (ClientSock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "ErrorCode=" << iError << endl;
				break;
			}
		}
		else
		{
			pServer->AddUser(ClientSock, ClientAddr);
			cout << "- " << pServer->m_UserList.size() << " 명 접속중 -" << endl;
		}
		Sleep(1);
	}
	return 1;
}
Accepter::Accepter()
{

}
Accepter::Accepter(LPVOID value)
{

}