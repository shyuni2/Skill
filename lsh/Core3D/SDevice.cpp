#include "SDevice.h"

ID3D11Device* g_pd3dDevice = nullptr;

// -- ����̽� �ʱ⼳��
HRESULT SDevice::InitDeivice()
{
	HRESULT hr = S_OK; 
	CreateDevice(); // ����̽� ����
	CreateRenderTargetView(); // ����Ÿ�ٺ� ����
	CreateDetphStencilView(); // ���̽��ٽǺ� ����
	SetViewport(); // ����Ʈ ����
	return hr;
}
// -- ����̽� ��������
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

// -- ����̽� ����
bool SDevice::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; //Direct2D �� Direct3D ���ҽ��� ��ȣ��� �����ϰ� ��
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fl[] // ������ Ư�������� ���� �����ϴ� ���̴� ������ �ٸ�
	{
		D3D_FEATURE_LEVEL_11_0, // ���̴� 5.0 ����
		D3D_FEATURE_LEVEL_10_0, // ���̴� 4.0 ����
	};

	// m_SwapChainDesc (����ü�� �Ӽ���) �Ҵ�
	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Width = m_rtClient.right; // �ػ��� �ʺ� = Ŭ���̾�Ʈ�� ���� ũ��
	m_SwapChainDesc.BufferDesc.Height = m_rtClient.bottom; // �ػ��� ���� = Ŭ���̾�Ʈ�� ���� ũ��
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // ȭ�� �ֻ����� ���ڰ�
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� �ֻ����� �и�
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ������� �ȼ� ����, �Ϲ������� �̰� ���� ��
	m_SwapChainDesc.SampleDesc.Count = 1; 
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ǥ�� �� ���ҽ� ������ ���� �ɼ� �÷���, ����ü���� ���۸� �����Ϸ��� < DXGI_USAGE_RENDER_TARGET_OUTPUT > �̾�� �Ѵ�
	m_SwapChainDesc.BufferCount = 1; // ����ü���� ���� ����
	m_SwapChainDesc.OutputWindow = m_hWnd; // ���â�� HWND �ڵ� NULL�� �ɼ� ����
	m_SwapChainDesc.Windowed = true; // ������ ��� TRUE, Ǯ��ũ�� ��� FALSE

	// ���� ���������� ����̽� ��ü ����
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, Flags, fl, 1, D3D11_SDK_VERSION, &m_SwapChainDesc, m_pSwapChain.GetAddressOf(), m_pd3dDevice.GetAddressOf(), &m_FeatureLevel, m_pImmediateContext.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}	
	DXGI_SWAP_CHAIN_DESC scd;
	m_pSwapChain->GetDesc(&scd); // ����ü�� ��ü�� ���� ����ü�� ������ ����
	g_pd3dDevice = m_pd3dDevice.Get();
	return true;
}
// -- ����Ÿ�� �� ����
bool SDevice::CreateRenderTargetView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	// ������ ����Ÿ�� �並 ����̽��� ����Ҽ��ֵ��� ����
	m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL); // OMSetRenderTargets : ����Ÿ���� �����ϴ� �Լ�

	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	m_pRenderTargetView->GetDesc(&rtvd); // ����Ÿ�� �� ��ü�� ���� ����Ÿ�� �� ������ ����
	return true;
}
// -- ���� ���ٽ� �� ����
bool SDevice::CreateDetphStencilView()
{
	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = m_SwapChainDesc.BufferDesc.Width; // �ؽ�ó�� �ʺ� = �ػ��� �ʺ�
	DescDepth.Height = m_SwapChainDesc.BufferDesc.Height; // �ؽ�ó�� ���� = �ػ��� ����
	DescDepth.MipLevels = 1; // �Ӹ� ������ ����
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;

	// �� ���� ���� �� ���ٽ� ���� ����
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	if (DescDepth.Format == DXGI_FORMAT_R24G8_TYPELESS || DescDepth.Format == DXGI_FORMAT_D32_FLOAT)
	{
		// ���̸� ���� ���̸� ����
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	}

	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	if (FAILED(hr = m_pd3dDevice->CreateTexture2D(&DescDepth, NULL, &pDSTexture)))
	{
		return false;
	}

	// ���̴� ���ҽ� ����, ���� �� �����쿡�� ���
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc; // ���� ���ٽ� ��
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc; // ���̴� ���ҽ� ��
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	switch (DescDepth.Format) // ���� ���� ���˿� ���� �޶���
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

	// ���ٽ� ���ҽ��� ���� ���
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	if (FAILED(hr = m_pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, m_pDepthStencilView.GetAddressOf())))
	{
		return false;
	}

	return true;
}
// -- ����Ʈ ����
bool SDevice::SetViewport()
{
	// �۾����� ������ġ
	m_ViewPort.TopLeftX = 0; 
	m_ViewPort.TopLeftY = 0;
	// ������ġ���������� ���� �� ���� ũ�� = ������� ũ��
	m_ViewPort.Width = m_SwapChainDesc.BufferDesc.Width;
	m_ViewPort.Height = m_SwapChainDesc.BufferDesc.Height;
	// ���� ��
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &m_ViewPort); // RSSetViewports : ������ ����Ʈ�� ������ �����ϴ� �Լ� 
	return true;
}
// -- ������ �Ҵ� ����
bool SDevice::CleapupDevice()
{
	// Comptr�� �ٲ㼭 ������
	return true;
}

SDevice::SDevice()
{
	// �����Ҷ� �����Ⱚ�� �������� ������ �ʱ�ȭ
	m_pd3dDevice = nullptr;	
	m_pImmediateContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
}
SDevice::~SDevice()
{

}