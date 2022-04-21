#pragma once
#include "SBaseMgr.h"
#include <d3dcompiler.h>

class SShader
{
public:
	int	m_iIndex;
	std::wstring m_csName;
	std::wstring m_szMsg;
	TCHAR m_szBuffer[256];
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* m_pVSCodeResult = nullptr;
	ID3DBlob* m_pErrorMsgs = nullptr;
	ID3DBlob* m_pPSCodeResult = nullptr;
public:	
	virtual bool CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "VS");
	virtual bool CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "PS");
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	SShader();
	virtual ~SShader();
};

class SShaderMgr :  public SBaseMgr<SShader, SShaderMgr>
{
	friend class Singleton<SShaderMgr>;
public:
	SShader* CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
	SShader* CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
private:
	SShaderMgr();
public:
	~SShaderMgr();
};
#define I_Shader SShaderMgr::Get()