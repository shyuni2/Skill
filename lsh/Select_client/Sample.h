#pragma once
#include "TCore.h"
#include "TAsyncSelect.h"

class Sample : public TCore
{
	TAsyncSelect m_Net; // ���⿡ �����Ұ���
	HWND m_hEdit;
	HWND m_hButton; // ���۹�ư
	HWND m_hListBox; // ä��â
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

