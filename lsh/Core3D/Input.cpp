#include "Input.h"

POINT g_ptMouse;

DWORD Input::GetKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
bool Input::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256 );
	return true;
}
bool Input::Frame() 
{	
	POINT ptOffset = g_ptMouse; // 마우스 정보 저장

	GetCursorPos(&m_ptMouse); //화면(스크린)좌표계
	ScreenToClient(g_hWnd, &m_ptMouse); //클라이언트(윈도우)좌표계
	g_ptMouse = m_ptMouse;

	for (int iKey = 0; iKey < 256; iKey++) // 키보드
	{
		SHORT sKey = GetAsyncKeyState(iKey);
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[iKey] == KEY_FREE)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else
		{
			if (m_dwKeyState[iKey] == KEY_PUSH ||
				m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}
	}

	// 마우스
	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON]; 
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];

	if (m_dwMouseState[0] == KEY_PUSH)
	{
		m_bDrag = true;
		m_ptMouseClick = m_ptMouse;
	}
	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false;
	}
	if (m_bDrag) // 드래그
	{
		m_ptDeltaMouse.x = ptOffset.x - m_ptMouse.x;
		m_ptDeltaMouse.y = ptOffset.y - m_ptMouse.y;
	}
	return true;
}
bool Input::Render() 
{
	return true;
}
bool Input::Release() 
{
	return true;
}
Input::Input()
{
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}
Input::~Input()
{

}