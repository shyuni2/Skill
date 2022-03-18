#include "LobbyServer.h"

DWORD WINAPI WokerThread(LPVOID param)
{
	LobbyServer* pServer = (LobbyServer*)param;
	DWORD dwTransfer; // 얼만큼 읽었는지, 썼는지
	ULONG_PTR KeyValue; // 완료 포트값
	OVERLAPPED* pOverlapped; // 비동기 작업한 오버랩구조체, 오버랩구조체가 있으니 offset 사용가능! 어디서부터 어디까지 읽었는지 알아야 뒤에서부터 읽으니까

	while (1)
	{
		if (WaitForSingleObject(pServer->m_hKillEvent, 1) == WAIT_OBJECT_0)
		{
			break;
		}
		// 완료큐에 데이터가 있으면 작업 시작
		BOOL bReturn = ::GetQueuedCompletionStatus(pServer->g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);
		ChatUser* pUser = (ChatUser*)KeyValue;
		TOV* pOV = (TOV*)pOverlapped;
		if (bReturn == TRUE && pUser & pOV)
		{
			if (dwTransfer == 0 && pOV->type == 1000)
			{
				pUser->m_bConnect = false;
			}
			else
			{
				pUser->Dispatch(dwTransfer, pOV);
			}
		}
		else
		{
			if (GetLastError() != WAIT_TIMEOUT)
			{
				::SetEvent(pServer->m_hKillEvent);
				break;
			}
		}
	}
	return 1;
}
bool LobbyServer::AddUser(SOCKET sock, SOCKADDR_IN ClientAddr)
{
	ChatUser* user = new ChatUser;
	user->set(sock, ClientAddr);
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on); // 파일생성과 동일

	EnterCriticalSection(&m_CS);
	m_UserList.push_back(user);
	LeaveCriticalSection(&m_CS);

	::CreateIoCompletionPort((HANDLE)sock, g_hIOCP, (ULONG_PTR)user, 0);
	user->Recv();

	char ip[INET_ADDRSTRLEN];
	cout << "ip =" << inet_ntop(AF_INET, &(ClientAddr.sin_addr), ip, INET_ADDRSTRLEN) << "port =" << ntohs(ClientAddr.sin_port) << endl;

	return true;
}

bool LobbyServer::InitServer(int iPort)
{
	Server::InitServer(iPort);
	g_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	for (int Thread = 0; Thread < MAX_WORKER_THREAD; Thread++)
	{
		DWORD id;
		g_hWorkThread[Thread] = ::CreateThread(0, 0, WokerThread, this, 0, &id);
	}
	return true;
}
bool LobbyServer::Run()
{
	while (1)
	{
		EnterCriticalSection(&m_CS);
		for (NetUser* tUser : m_UserList)
		{
			ChatUser* pChat = (ChatUser*)tUser;
			if (pChat->m_PacketPool.size() > 0)
			{
				Broadcast(tUser);
			}
		}
		list<NetUser*>::iterator iter;
		for (iter = m_UserList.begin(); iter != m_UserList.end();)
		{
			if ((*iter)->m_bConnect == false)
			{
				(*iter)->DisConnect();
				delete (*iter);
				iter = m_UserList.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
	return true;
}
bool LobbyServer::Release()
{
	CloseHandle(g_hIOCP);
	Server::Release();
	return true;
}