#pragma once
#include <windows.h>
#pragma comment	(lib, "Winmm.lib")

class STimer
{
public:
	int m_iFPS; // ù��° ������
	float m_fSecondPerFrame; // �ι�° ������
	float m_fTimer; // �ð�
	DWORD m_dwBeforeTime; // �� �ð�
public:
	float m_fFPSTimer = 0.0f;	
	int	m_iFPSCounter = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

