#pragma once
#include "TCore.h"
#include "TAsyncSelect.h"

class Sample : public TCore
{
	TAsyncSelect m_Net; // 여기에 연결할거임
	HWND m_hEdit;
	HWND m_hButton; // 전송버튼
	HWND m_hListBox; // 채팅창
public:
	virtual bool Init()  override;
	virtual bool Frame()  override;
	virtual bool Render()  override;
	virtual bool Release()  override;
	virtual LRESULT  MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Sample();
	~Sample();
};

