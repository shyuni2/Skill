#include "SDevice.h"

ID3D11Device* g_pd3dDevice = nullptr;

// -- 디바이스 초기설정
HRESULT SDevice::InitDeivice()
{
	HRESULT hr = S_OK; 
	CreateDevice(); // 디바이스 생성
	CreateRenderTargetView(); // 랜더타겟뷰 생성
	CreateDetphStencilView(); // 깊이스텐실뷰 생성
	SetViewport(); // 뷰포트 생성
	return hr;
}
// -- 디바이스 리사이즈
void SDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTargetView)
	{
		m_pRenderTargetView->Release();
	}

	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);
	}
	CreateRenderTargetView();
	SetViewport();
}

void SDevice::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	if (pd3dDeviceContext == NULL) return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Shaders
	pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

	// IA clear
	pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
	pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
	pd3dDeviceContext->IASetInputLayout(NULL);

	// Constant buffers
	pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

	// Resources
	pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

	// Samplers
	pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

	// Render targets
	pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

	// States
	FLOAT blendFactor[4] = { 0,0,0,0 };
	pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
	pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
	pd3dDeviceContext->RSSetState(NULL);
}

// -- 디바이스 생성
bool SDevice::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; //Direct2D 와 Direct3D 리소스의 상호운영을 가능하게 함
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fl[] // 선택한 특성레벨에 따라 지원하는 쉐이더 버전이 다름
	{
		D3D_FEATURE_LEVEL_11_0, // 쉐이더 5.0 지원
		D3D_FEATURE_LEVEL_10_0, // 쉐이더 4.0 지원
	};

	// m_SwapChainDesc (스왑체인 속성값) 할당
	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Width = m_rtClient.right; // 해상도의 너비 = 클라이언트의 가로 크기
	m_SwapChainDesc.BufferDesc.Height = m_rtClient.bottom; // 해상도의 높이 = 클라이언트의 세로 크기
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // 화면 주사율의 분자값
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // 화면 주사율의 분모값
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 백버퍼의 픽셀 포맷, 일반적으로 이걸 많이 씀
	m_SwapChainDesc.SampleDesc.Count = 1; 
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 표면 및 리소스 생성에 관한 옵션 플래그, 스왑체인의 버퍼를 생성하려면 < DXGI_USAGE_RENDER_TARGET_OUTPUT > 이어야 한다
	m_SwapChainDesc.BufferCount = 1; // 스왑체인의 버퍼 개수
	m_SwapChainDesc.OutputWindow = m_hWnd; // 출력창의 HWND 핸들 NULL이 될수 없다
	m_SwapChainDesc.Windowed = true; // 윈도우 모드 TRUE, 풀스크린 모드 FALSE

	// 위의 설정값으로 디바이스 객체 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, Flags, fl, 1, D3D11_SDK_VERSION, &m_SwapChainDesc, m_pSwapChain.GetAddressOf(), m_pd3dDevice.GetAddressOf(), &m_FeatureLevel, m_pImmediateContext.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}	
	DXGI_SWAP_CHAIN_DESC scd;
	m_pSwapChain->GetDesc(&scd); // 스왑체인 객체에 현재 스왑체인 정보를 저장
	g_pd3dDevice = m_pd3dDevice.Get();
	return true;
}
// -- 랜더타겟 뷰 생성
bool SDevice::CreateRenderTargetView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	// 생성된 랜더타겟 뷰를 디바이스가 사용할수있도록 세팅
	m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL); // OMSetRenderTargets : 랜더타겟을 지정하는 함수

	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	m_pRenderTargetView->GetDesc(&rtvd); // 렌더타겟 뷰 객체에 현재 랜더타겟 뷰 정보를 저장
	return true;
}
// -- 깊이 스텐실 뷰 생성
bool SDevice::CreateDetphStencilView()
{
	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = m_SwapChainDesc.BufferDesc.Width; // 텍스처의 너비 = 해상도의 너비
	DescDepth.Height = m_SwapChainDesc.BufferDesc.Height; // 텍스처의 높이 = 해상도의 높이
	DescDepth.MipLevels = 1; // 밉맵 수준의 갯수
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;

	// 백 버퍼 깊이 및 스텐실 버퍼 생성
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	if (DescDepth.Format == DXGI_FORMAT_R24G8_TYPELESS || DescDepth.Format == DXGI_FORMAT_D32_FLOAT)
	{
		// 깊이맵 전용 깊이맵 생성
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	}

	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	if (FAILED(hr = m_pd3dDevice->CreateTexture2D(&DescDepth, NULL, &pDSTexture)))
	{
		return false;
	}

	// 쉐이더 리소스 생성, 깊이 맵 쉐도우에서 사용
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc; // 깊이 스텐실 뷰
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc; // 쉐이더 리소스 뷰
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	switch (DescDepth.Format) // 깊이 버퍼 포맷에 따라 달라짐
	{
	case DXGI_FORMAT_R32_TYPELESS:
	{
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	}break;
	case DXGI_FORMAT_R24G8_TYPELESS:
	{
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	}break;
	}
	if (srvDesc.Format == DXGI_FORMAT_R32_FLOAT || srvDesc.Format == DXGI_FORMAT_R24_UNORM_X8_TYPELESS)
	{
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		if (FAILED(hr = m_pd3dDevice->CreateShaderResourceView(pDSTexture.Get(), &srvDesc, &m_pDsvSRV)))
		{
			return false;
		}
	}

	// 스텐실 리소스에 접근 방법
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	if (FAILED(hr = m_pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, m_pDepthStencilView.GetAddressOf())))
	{
		return false;
	}

	return true;
}
// -- 뷰포트 세팅
bool SDevice::SetViewport()
{
	// 작업영역 시작위치
	m_ViewPort.TopLeftX = 0; 
	m_ViewPort.TopLeftY = 0;
	// 시작위치에서부터의 가로 및 세로 크기 = 백버퍼의 크기
	m_ViewPort.Width = m_SwapChainDesc.BufferDesc.Width;
	m_ViewPort.Height = m_SwapChainDesc.BufferDesc.Height;
	// 깊이 값
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &m_ViewPort); // RSSetViewports : 구현된 뷰포트의 구조를 세팅하는 함수 
	return true;
}
// -- 포인터 할당 해제
bool SDevice::CleapupDevice()
{
	// Comptr로 바꿔서 삭제함
	return true;
}

SDevice::SDevice()
{
	// 생성할때 쓰레기값이 들어가있을수 있으니 초기화
	m_pd3dDevice = nullptr;	
	m_pImmediateContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
}
SDevice::~SDevice()
{

}