#pragma once
#include "Window.h"

class Device : public Window
{
public:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	D3D_FEATURE_LEVEL m_FeatureLevel;	
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;	
	D3D11_VIEWPORT m_ViewPort;	
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pDsvSRV;// ±Ì¿Ãπˆ∆€ ∏Æº“Ω∫∫‰
public:
	HRESULT InitDeivice();
	virtual bool CreateDevice();
	virtual bool CreateRenderTargetView();
	virtual bool CreateDetphStencilView();
	virtual bool SetViewport();
	virtual bool CleapupDevice();
	void ResizeDevice(UINT iWidth, UINT iHeight);
public:
	Device();
	virtual ~Device();
};

