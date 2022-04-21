#pragma once
#include "STD.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};

class SInput
{
public: 
	float m_fRadianX = 0.0f; // x 반지름
	float m_fRadianY = 0.0f; // y 반지름
	DWORD m_dwKeyState[256]; // 키보드 상태값
	POINT m_ptMouse; // 마우스
	DWORD m_dwMouseState[3]; // 마우스 상태값
	bool m_bDrag = false; // 드래그
	POINT m_ptMouseClick; // 마우스 클릭
	POINT m_ptDeltaMouse; // 마우스 델타값
public:
	static SInput& Get()
	{
		static SInput theSingle;
		return theSingle;
	}
public:
	DWORD GetKey(DWORD dwKey); // 입력값 받아옴
	S::SVector2 GetDelta();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();	
private:
	 SInput();
public:
	virtual ~SInput();
};

