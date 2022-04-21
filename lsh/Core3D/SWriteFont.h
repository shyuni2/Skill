#pragma once
#include "STD.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// �۾� �ܰ�
// 1. ID2D1Factory�� IDWriteFactory��ü ����
// 2. ID2D1RenderTarget ��ü ����(DX11�� DirectWrite ����)
// 3. IDWriteTextFormat ��ü ����
//< ������ �ؽ�Ʈ ����ϴ� ���>
// 4. �ؽ�Ʈ ���� ����
// 5. �ؽ�Ʈ ���
//< �پ��� �������� �ؽ�Ʈ ����ϴ� ���>
// 6. IDWriteTextLayout ��ü ����
// 7. �ؽ�Ʈ ���
// 8. ��ü �Ҹ�

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

