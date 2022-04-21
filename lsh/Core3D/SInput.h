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
	float m_fRadianX = 0.0f; // x ������
	float m_fRadianY = 0.0f; // y ������
	DWORD m_dwKeyState[256]; // Ű���� ���°�
	POINT m_ptMouse; // ���콺
	DWORD m_dwMouseState[3]; // ���콺 ���°�
	bool m_bDrag = false; // �巡��
	POINT m_ptMouseClick; // ���콺 Ŭ��
	POINT m_ptDeltaMouse; // ���콺 ��Ÿ��
public:
	static SInput& Get()
	{
		static SInput theSingle;
		return theSingle;
	}
public:
	DWORD GetKey(DWORD dwKey); // �Է°� �޾ƿ�
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

