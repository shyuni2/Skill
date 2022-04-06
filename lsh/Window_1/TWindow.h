// 윈도우의 클래스화, 매크로함수 만들기

#pragma once

#include "STD.h"

class TWindow
{
public:
	HINSTANCE	m_hInstance; 
	HWND		m_hWnd;
	RECT		m_rtClient;
	RECT		m_rtWindow;

public:
	BOOL WinRegisterClass(HINSTANCE hInstance);
	BOOL SetWindow(const WCHAR* szTitle = L"Sample", int iWidth = 800, int iHeight = 600);
	bool WinRun();
};

