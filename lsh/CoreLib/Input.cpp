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
	GetCursorPos(&m_ptMouse); //ȭ��(��ũ��)��ǥ��
	ScreenToClient(g_hWnd, &m_ptMouse); //Ŭ���̾�Ʈ(������)��ǥ��
	g_ptMouse = m_ptMouse;

	for (int iKey = 0; iKey < 256; iKey++)
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
			if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}
	}

	// ���콺 ��ư VK_LBUTTON,  VK_RBUTTON, VK_MBUTTON,
	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON];
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];
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

}
Input::~Input()
{

}