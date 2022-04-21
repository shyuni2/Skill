#pragma once
#include <windows.h>
#pragma comment	(lib, "Winmm.lib")

class STimer
{
public:
	int m_iFPS; // 첫번째 프레임
	float m_fSecondPerFrame; // 두번째 프레임
	float m_fTimer; // 시간
	DWORD m_dwBeforeTime; // 전 시간
public:
	float m_fFPSTimer = 0.0f;	
	int	m_iFPSCounter = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

