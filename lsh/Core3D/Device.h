#pragma once
#include "Window.h"

class Device : public Window
{
public:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	ComPtr<IDXGISwapChain> m_pSwapChain;
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;	
	D3D11_VIEWPORT m_ViewPort;
public:
	HRESULT InitDeivice();
	virtual bool CreateDevice();
	virtual bool CreateRenderTargetView();
	virtual bool SetViewport();
	virtual bool CleapupDevice();
	void ResizeDevice(UINT iWidth, UINT iHeight);
public:
	Device();
	virtual ~Device();
};

