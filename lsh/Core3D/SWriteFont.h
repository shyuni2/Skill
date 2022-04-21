#pragma once
#include "STD.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// 작업 단계
// 1. ID2D1Factory및 IDWriteFactory객체 생성
// 2. ID2D1RenderTarget 객체 생성(DX11에 DirectWrite 연동)
// 3. IDWriteTextFormat 객체 생성
//< 간단한 텍스트 출력하는 방법>
// 4. 텍스트 서식 지정
// 5. 텍스트 출력
//< 다양한 포맷으로 텍스트 출력하는 방법>
// 6. IDWriteTextLayout 객체 생성
// 7. 텍스트 출력
// 8. 객체 소멸

class SWriteFont
{
public:
	ID2D1Factory* m_pd2dFactory = nullptr;
	IDWriteFactory* m_pWriteFactory = nullptr;
	ID2D1RenderTarget* m_pd2dRT = nullptr;
	IDWriteTextFormat* m_pd2dTextFormat = nullptr;
	IDWriteTextFormat* m_pd2dMTShadowTF = nullptr;
	ID2D1SolidColorBrush* m_pd2dColorBrush = nullptr;
public:
	void DeleteDeviceResize();
	bool SetRenderTarget(IDXGISurface1* pSurface);
	void Draw(std::wstring msg, RECT rt, D2D1::ColorF color, IDWriteTextFormat* tf=nullptr);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

