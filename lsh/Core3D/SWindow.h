#pragma once
#include "STD.h"

// 작업 순서
// 1. 윈도우 클래스 등록, 허가
// 2. 윈도우 생성
// 3. 윈도우 실행

class SWindow 
{
public:
	HINSTANCE m_hInstance; // 인스턴스 핸들
	HWND m_hWnd; // 윈도우 핸들
	RECT m_rtClient; // 클라이언트 영역
	RECT m_rtWindow; // 윈도우 영역
public:
	BOOL SetWinClass(HINSTANCE hInstance); // 1. 윈도우 클래스 등록, 허가
	BOOL SetWindow(const WCHAR* szTitle = L"Sample", int iWidth = 800, int iHeight = 600); // 윈도우 생성
	bool WinRun(); // 3. 윈도우 실행
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void ResizeDevice(UINT iWidth, UINT iHeight); // 윈도우 리사이징
public:
	SWindow();
	virtual ~SWindow();
};

