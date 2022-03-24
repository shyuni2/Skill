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
	if (Input::Get().GetKey('V')== KEY_PUSH)
	{
		m_bWireFrame = !m_bWireFrame;
	}
	m_GameTimer.Frame();
	Input::Get().Frame();
	I_ObjectMgr.Frame();
	I_Sound.Frame();
	Frame();
	m_dxWrite.Frame();
	return true;
}
bool Core::CoreRender()
{	
	float color[4] = { 1, 0, 0,1.0f };
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
	
	Render(); // ����ۿ� ������

	m_GameTimer.Render();
	Input::Get().Render();

	m_dxWrite.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool Core::CoreRelease()
{
	Release();
	DxState::Release();
	m_dxWrite.Release();
	m_GameTimer.Release();
	Input::Get().Release();
	CleapupDevice();	
	return true;
}
void Core::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == nullptr) return;
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