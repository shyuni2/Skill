#include "Device.h"

HRESULT Device::InitDeivice()
{
	HRESULT hr = S_OK; 
	CreateDevice();
	CreateRenderTargetView();
	SetViewport();
	return hr;
}
bool Device::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;	//D2DWIRETE 연동 필수
#endif
	D3D_FEATURE_LEVEL fl[]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};

	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Width = m_rtClient.right;
	m_SwapChainDesc.BufferDesc.Height = m_rtClient.bottom;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.OutputWindow = m_hWnd;
	m_SwapChainDesc.Windowed = true;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, Flags, fl, 1, D3D11_SDK_VERSION, &m_SwapChainDesc, m_pSwapChain.GetAddressOf(), m_pd3dDevice.GetAddressOf(), &m_FeatureLevel, m_pImmediateContext.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}	
	return true;
}
bool Device::CreateRenderTargetView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());

	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);
	return true;
}
bool Device::SetViewport()
{	
	// 뷰포트 세팅
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = m_SwapChainDesc.BufferDesc.Width;
	m_ViewPort.Height = m_SwapChainDesc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
	return true;
}
void Device::ResizeDevice(UINT iWidth, UINT iHeight)
{
	m_pImmediateContext->OMSetRenderTargets(0,NULL, NULL);
	if (m_pRenderTargetView)m_pRenderTargetView->Release();

	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags);
	if( SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);
	}
	CreateRenderTargetView();
	SetViewport();
}
bool Device::CleapupDevice()
{
	////if (m_pd3dDevice)m_pd3dDevice->Release();	// 디바이스 객체
	//if (m_pImmediateContext)m_pImmediateContext->Release();// 다비이스 컨텍스트 객체
	//if (m_pSwapChain)m_pSwapChain->Release();	// 스왑체인 객체
	//if (m_pRenderTargetView)m_pRenderTargetView->Release();
	////m_pd3dDevice = nullptr;	// 디바이스 객체
	//m_pImmediateContext = nullptr;// 다비이스 컨텍스트 객체
	//m_pSwapChain = nullptr;	// 스왑체인 객체
	//m_pRenderTargetView = nullptr;
	return true;
}
Device::Device()
{
	m_pd3dDevice = nullptr;	// 디바이스 객체
	m_pImmediateContext = nullptr;// 다비이스 컨텍스트 객체
	m_pSwapChain = nullptr;	// 스왑체인 객체
	m_pRenderTargetView = nullptr;
}
Device::~Device()
{

}