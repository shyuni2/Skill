#include "SInput.h"

POINT g_ptMouse;

// -- �Է°� �޾ƿ�
DWORD SInput::GetKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
bool SInput::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256 );
	return true;
}
S::SVector2 SInput::GetDelta()
{
	S::SVector2 ret;
	m_fRadianY += (SInput::Get().m_ptDeltaMouse.x / (float)g_rtClient.right) * BASIS_PI;
	m_fRadianX += (SInput::Get().m_ptDeltaMouse.y / (float)g_rtClient.bottom) * BASIS_PI;
	return SVector2(m_fRadianX, m_fRadianY);
}
bool SInput::Frame() 
{	
	POINT ptOffset = g_ptMouse; // ���콺 ���� ����

	GetCursorPos(&m_ptMouse); //ȭ��(��ũ��)��ǥ��
	ScreenToClient(g_hWnd, &m_ptMouse); //Ŭ���̾�Ʈ(������)��ǥ��
	g_ptMouse = m_ptMouse;

	for (int iKey = 0; iKey < 256; iKey++) // Ű���� ���°� ����
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

	// ���콺 ���°� ����
	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON]; 
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];

	if (m_dwMouseState[0] == KEY_PUSH) // ����Ŭ�� ������
	{
		m_bDrag = true; // �巡�� ����
		m_ptMouseClick = m_ptMouse; // Ŭ��
	}
	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false; // �巡�� ��
	}
	if (m_bDrag) // �巡�� ���°�
	{
		m_ptDeltaMouse.x = ptOffset.x - m_ptMouse.x;
		m_ptDeltaMouse.y = ptOffset.y - m_ptMouse.y;
	}
	return true;
}
bool SInput::Render() 
{
	return true;
}
bool SInput::Release() 
{
	return true;
}
SInput::SInput()
{
	// �����Ҷ� �� �ʱ�ȭ
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}
SInput::~SInput()
{

}