#pragma once
#include "SWindow.h"

// �۾�����
// 1. ID3D11Device / ID3D11DeviceContext / IDXGISwapChain ���� �� ����
// 2. ID3D11RenderTargetView ���� �� ����
// 3. D3D11_VIEWPORT ����
// 4. ID3D11RenderTargetView ��ü�� �÷��� ä�� (BackBuffer�� ����)
// 5. IDXGISwapChain ��ü�� ����Ͽ� ���
// 6. ��� ������ ��ü���� �Ҹ� �Ǵ� ����

// ��� ����
// ID3D11Device : ���ҽ��� ������ ���
// ID3D11DeviceContext : ������ ���
// ����Ʈ : ��ũ���� � ��ġ�� �۾��� ������ ǥ���Ұ����� ���������ϴ°�
// ����ü�� : ������۸�(ȭ�鱳ü) ����� ����ϱ� ����

class SDevice : public SWindow
{
public:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice; // ����̽� ��ü
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext; // ����̽� ���ؽ�Ʈ ��ü
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain; // ����ü�� ��ü
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView; // ���� ����Ÿ�� ��
	D3D_FEATURE_LEVEL m_FeatureLevel; // Dx11 Ư������ �Ӽ���
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc; // ����ü�� �Ӽ���
	D3D11_VIEWPORT m_ViewPort; // ����Ʈ �Ӽ���
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView; // ���� ���ٽǺ� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV; // ���� ���ҽ���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pDsvSRV;// ���̹��� ���ҽ���
public:
	HRESULT InitDeivice();
	void ResizeDevice(UINT iWidth, UINT iHeight);
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
public:
	virtual bool CreateDevice();
	virtual bool CreateRenderTargetView();
	virtual bool CreateDetphStencilView();
	virtual bool SetViewport();	
	virtual bool CleapupDevice();
public:
	SDevice();
	virtual ~SDevice();
};

