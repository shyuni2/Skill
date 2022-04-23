#pragma once
#include "SWindow.h"

// 작업순서
// 1. ID3D11Device / ID3D11DeviceContext / IDXGISwapChain 선언 및 생성
// 2. ID3D11RenderTargetView 선언 및 생성
// 3. D3D11_VIEWPORT 설정
// 4. ID3D11RenderTargetView 객체에 컬러를 채움 (BackBuffer를 지움)
// 5. IDXGISwapChain 객체를 사용하여 출력
// 6. 모든 생성된 객체들을 소멸 또는 삭제

// 용어 정리
// ID3D11Device : 리소스의 생성을 담당
// ID3D11DeviceContext : 랜더링 담당
// 뷰포트 : 스크린의 어떤 위치에 작업한 내용을 표현할것인지 구역설정하는것
// 스왑체인 : 더블버퍼링(화면교체) 방식을 사용하기 위함

class SDevice : public SWindow
{
public:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice; // 디바이스 객체
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext; // 디바이스 컨텍스트 객체
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain; // 스왑체인 객체
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView; // 메인 랜더타겟 뷰
	D3D_FEATURE_LEVEL m_FeatureLevel; // Dx11 특성레벨 속성값
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc; // 스왑체인 속성값
	D3D11_VIEWPORT m_ViewPort; // 뷰포트 속성값
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView; // 깊이 스텐실뷰 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV; // 서브 리소스뷰
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pDsvSRV;// 깊이버퍼 리소스뷰
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

