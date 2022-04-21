#include "SWriteFont.h"

// -- 화면이 리사이즈 될때 해제
void SWriteFont::DeleteDeviceResize()
{
	if (m_pd2dColorBrush)
	{
		m_pd2dColorBrush->Release();
	}
	if (m_pd2dRT)
	{
		m_pd2dRT->Release();
	}
}
// -- 랜더타겟 세팅
bool SWriteFont::SetRenderTarget(IDXGISurface1* pSurface)
{
	UINT dpi = GetDpiForWindow(g_hWnd);

	D2D1_RENDER_TARGET_PROPERTIES rtp;
	ZeroMemory(&rtp, sizeof(D2D1_RENDER_TARGET_PROPERTIES));
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	rtp.dpiX = dpi;
	rtp.dpiY = dpi;
	rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
	HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(pSurface, &rtp, &m_pd2dRT);
	if (FAILED(hr))
	{
		return false;
	}
	if (FAILED(m_pd2dRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pd2dColorBrush)))
	{
		return false;
	}
	return true;
}
// -- 화면에 뿌리기
void SWriteFont::Draw(std::wstring msg, RECT rt, D2D1::ColorF color, IDWriteTextFormat* tf)
{
	m_pd2dRT->BeginDraw(); // BeginDraw : 랜더타겟 객체로 그림을 그리려면 먼저 호출되어야함
	D2D_RECT_F fRT;
	fRT.top = rt.top;
	fRT.left = rt.left;
	fRT.right = rt.right;
	fRT.bottom = rt.bottom;

	m_pd2dColorBrush->SetColor(color);
	if (tf == nullptr)
	{
		m_pd2dRT->DrawText(msg.c_str(), msg.size(), m_pd2dTextFormat, &fRT, m_pd2dColorBrush);
	}			
	else
	{
		m_pd2dRT->DrawText(msg.c_str(), msg.size(), tf, &fRT, m_pd2dColorBrush);
	}
			
	m_pd2dRT->EndDraw();
}

bool SWriteFont::Init()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)(&m_pWriteFactory));
		if (SUCCEEDED(hr))
		{
			hr = m_pWriteFactory->CreateTextFormat(L"굴림", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"ko-kr", &m_pd2dTextFormat);
			hr = m_pWriteFactory->CreateTextFormat(L"Imprint MT Shadow", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"en-us", &m_pd2dMTShadowTF);
		}
	}
	if (SUCCEEDED(hr))
	{
		return true;
	}
	return false;
}
bool SWriteFont::Frame()
{	
	return true;
}
bool SWriteFont::Render() 
{
	m_pd2dRT->BeginDraw();
	m_pd2dRT->EndDraw();
	return true;
}
bool SWriteFont::Release() 
{
	if (m_pd2dMTShadowTF)m_pd2dMTShadowTF->Release();
	if (m_pd2dTextFormat)m_pd2dTextFormat->Release();
	if (m_pd2dColorBrush)m_pd2dColorBrush->Release();
	if (m_pd2dRT)m_pd2dRT->Release();
	if (m_pWriteFactory)m_pWriteFactory->Release();
	if (m_pd2dFactory)m_pd2dFactory->Release();
	return true;
}