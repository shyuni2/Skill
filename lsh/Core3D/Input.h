#pragma once
#include "STD.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};

class Input
{
public: 
	float m_fRadianX = 0.0f;
	float m_fRadianY = 0.0f;
	DWORD m_dwKeyState[256]; 
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
	bool m_bDrag = false;
	POINT m_ptMouseClick;
	POINT m_ptDeltaMouse;
public:
	static Input& Get()
	{
		static Input theSingle;
		return theSingle;
	}
public:
	DWORD GetKey(DWORD dwKey);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	T::TVector2 GetDelta();
private:
	 Input();
public:
	virtual ~Input();
};

