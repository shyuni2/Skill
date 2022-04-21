#pragma once
#include "STD.h"

// �۾� ����
// 1. ������ Ŭ���� ���, �㰡
// 2. ������ ����
// 3. ������ ����

class SWindow 
{
public:
	HINSTANCE m_hInstance; // �ν��Ͻ� �ڵ�
	HWND m_hWnd; // ������ �ڵ�
	RECT m_rtClient; // Ŭ���̾�Ʈ ����
	RECT m_rtWindow; // ������ ����
public:
	BOOL SetWinClass(HINSTANCE hInstance); // 1. ������ Ŭ���� ���, �㰡
	BOOL SetWindow(const WCHAR* szTitle = L"Sample", int iWidth = 800, int iHeight = 600); // ������ ����
	bool WinRun(); // 3. ������ ����
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void ResizeDevice(UINT iWidth, UINT iHeight); // ������ ������¡
public:
	SWindow();
	virtual ~SWindow();
};

