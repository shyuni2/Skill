#pragma once
#include "BaseMgr.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#pragma comment	(lib, "d3dcompiler.lib")

class Texture
{
public:
	int m_iIndex;
	std::wstring m_csName;
	std::wstring m_szMsg;
	TCHAR m_szBuffer[256];
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
	D3D11_TEXTURE2D_DESC m_TextureDesc;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	Texture();
	virtual ~Texture();
};

class TextureMgr : public BaseMgr<Texture, TextureMgr>					
{
private:
	friend class Singleton<TextureMgr>;
	TextureMgr() {};
public:
	~TextureMgr() {};
};
#define I_Texture TextureMgr::Get()