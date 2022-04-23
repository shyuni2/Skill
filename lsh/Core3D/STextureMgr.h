#pragma once
#include "SBaseMgr.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

#pragma comment	(lib, "d3dcompiler.lib")

class STexture
{
public:
	int	m_iIndex;
	std::wstring m_csName;
	std::wstring m_szMsg;
	TCHAR m_szBuffer[256];
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
	D3D11_TEXTURE2D_DESC m_TextureDesc;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename); // 텍스쳐 로드
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	STexture() {};
	virtual ~STexture() {};
};

class STextureMgr : public SBaseMgr<STexture, STextureMgr>					
{
	friend class Singleton<STextureMgr>; // 싱글톤 사용
public:
	// 텍스쳐든 백버퍼든 원하는 스트링으로 출력해주는 기능
	static HRESULT SaveFile(ID3D11DeviceContext* pContext, ID3D11Texture2D* pRes, T_STR name);
	static HRESULT SaveFile(ID3D11DeviceContext* pContext, IDXGISwapChain* pSwapChain, T_STR name);
private:
	STextureMgr() {};
public:
	~STextureMgr() {};
};

#define I_Texture STextureMgr::Get()