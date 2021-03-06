#include "TAsyncSelect.h"

bool TAsyncSelect::Connect(HWND hWnd, int protocol, int iport, const char* ip)
{
	m_Sock = socket(AF_INET, protocol, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iport);
	sa.sin_addr.s_addr = inet_addr(ip);
	m_PlayerUser.m_Sock = m_Sock;

	// 윈속의 소켓이벤트를 메세지통하여 비동기적으로 통보받는다
	if (WSAAsyncSelect(m_Sock, hWnd, NETWORK_MSG, (FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)) // 소켓이벤트가 에러일때
	{
		return false;
	}
	int Ret = WSAConnect(m_Sock, (sockaddr*)&sa, sizeof(sa), NULL, NULL, NULL, NULL);
	if (Ret == SOCKET_ERROR) // 윈속연결이 에러일때
	{
		return false;
	}
	return true;
}
LRESULT TAsyncSelect::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case NETWORK_MSG:
	{
		WORD wRet = WSAGETSELECTEVENT(lParam);
		switch (wRet)
		{
		case FD_CONNECT:
		{
			m_bConnect = true;
		}break;
		case FD_CLOSE:
		{
			m_bConnect = false;
		}break;
		case FD_READ:
		{
			RecvUser(m_PlayerUser);
		}break;
		case FD_WRITE:
		{
			m_bConnect = false;
		}break;
		}
	}break;
	}
	return 0;
}