#include "SInput.h"

POINT g_ptMouse;

// -- 입력값 받아옴
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
	POINT ptOffset = g_ptMouse; // 마우스 정보 저장

	GetCursorPos(&m_ptMouse); //화면(스크린)좌표계
	ScreenToClient(g_hWnd, &m_ptMouse); //클라이언트(윈도우)좌표계
	g_ptMouse = m_ptMouse;

	for (int iKey = 0; iKey < 256; iKey++) // 키보드 상태값 저장
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

	// 마우스 상태값 저장
	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON]; 
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];

	if (m_dwMouseState[0] == KEY_PUSH) // 왼쪽클릭 누르면
	{
		m_bDrag = true; // 드래그 시작
		m_ptMouseClick = m_ptMouse; // 클릭
	}
	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false; // 드래그 끝
	}
	if (m_bDrag) // 드래그 상태값
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
	// 생성할때 값 초기화
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}
SInput::~SInput()
{

}