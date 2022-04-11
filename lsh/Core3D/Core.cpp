#include "Core.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

bool Core::CoreInit()
{
	m_GameTimer.Init();	
	Input::Get().Init();
	if( SUCCEEDED(InitDeivice()))
	{
		I_Shader.Set(m_pd3dDevice.Get());
		I_Texture.Set(m_pd3dDevice.Get());
		DxState::SetState(m_pd3dDevice.Get());
		if (m_dxWrite.Init())
		{
			IDXGISurface1* pSurface = nullptr;
			HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pSurface);
			if (SUCCEEDED(hr))
			{
				m_dxWrite.SetRenderTarget(pSurface);
			}
			if (pSurface) pSurface->Release();
		}
	}

	m_DefaultCamera.Init();
	m_DefaultCamera.CreateViewMatrix(T::TVector3(0, 500.0f, -100.0f), T::TVector3(0, 0.0f, 0));
	m_DefaultCamera.CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	m_DefaultCamera.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_DefaultCamera.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VSColor");
	m_DefaultCamera.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PSColor");
	m_DefaultCamera.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
	if (!m_DefaultCamera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}

	m_pMainCamera = &m_DefaultCamera;
	Init();

	return true;
}
bool Core::GameRun()
{
	CoreInit();
	while(WinRun())
	{
		CoreFrame();
		CoreRender();
	}
	CoreRelease();

	MemoryReporting();
	return true;
}
bool Core::CoreFrame()
{
	if (Input::Get().GetKey('F') == KEY_PUSH) // 와이어 프레임 키 f
	{
		m_bWireFrame = !m_bWireFrame;
	}

	m_GameTimer.Frame();
	Input::Get().Frame();
	m_pMainCamera->Frame();
	I_ObjectMgr.Frame();
	I_Sound.Frame();
	Frame();
	m_dxWrite.Frame();

	return true;
}
bool Core::CoreRender()
{	
	float color[4] = { 1, 1, 1, 1.0f }; // 윈도우 색 설정

	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	m_pImmediateContext->PSSetSamplers(0, 1, &DxState::m_pSSLinear);	
	m_pImmediateContext->PSSetSamplers(1, 1, &DxState::m_pSSPoint);
	m_pImmediateContext->OMSetDepthStencilState(DxState::g_pDSSDepthEnable, 0x00);
	
	if (m_bWireFrame)
	{
		m_pImmediateContext->RSSetState(DxState::g_pRSBackCullWireFrame);
	}		
	else
	{
		m_pImmediateContext->RSSetState(DxState::g_pRSBackCullSolid);
	}
	
	Render(); // 백버퍼에 랜더링
	m_GameTimer.Render();
	Input::Get().Render();
	m_dxWrite.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool Core::CoreRelease()
{
	Release();
	m_DefaultCamera.Release();
	DxState::Release();
	m_dxWrite.Release();
	m_GameTimer.Release();
	Input::Get().Release();
	CleapupDevice();	
	return true;
}
void Core::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == nullptr)
	{ 
		return;
	}
	DeleteResizeDevice(iWidth, iHeight);

	m_dxWrite.DeleteDeviceResize();
		
	Device::ResizeDevice(iWidth, iHeight);
	
	IDXGISurface1* pSurface = nullptr;
	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pSurface);

	if (SUCCEEDED(hr))
	{
		m_dxWrite.SetRenderTarget(pSurface);
	}
	if (pSurface) pSurface->Release();

	CreateResizeDevice(iWidth, iHeight);
}
Core::Core()
{

}
Core::~Core()
{
	
}