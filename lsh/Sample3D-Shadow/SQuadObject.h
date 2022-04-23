#pragma once
#include "SPlaneObj.h"

#define MAX_MASKCOUNT 25 //625=25*25
struct TKernelMask
{
	float fMask[MAX_MASKCOUNT*MAX_MASKCOUNT];
};
struct VSCB
{
	float		g_fMask;
	float		g_fTexSizeX;
	float		g_fTexSizeY;
	float		a;
};
class SQuadObject : public SPlaneObj
{
public:
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D>             m_pColorTex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_pColorSRV;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      m_pColorRTV;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>             m_pNormalDepthTex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_pNormalDepthSRV;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      m_pNormalDepthRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pDsvSRV;// ±Ì¿Ãπˆ∆€ ∏Æº“Ω∫∫‰
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pMaskCB;
	VSCB							    m_MaskValue;

	Microsoft::WRL::ComPtr<ID3D11Buffer>                m_pMaskBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pMaskArray;
	int									m_iMask;
	float*								m_pfKernelMask;
public:
	HRESULT		CreateConstantBuffer(ID3D11Device* pd3dDevice);
	HRESULT		CreateTextures(ID3D11Device* pDevice, UINT iWidth, UINT iHeight);
	bool		SetBuffer(ID3D11Device* pd3dDevice);
	bool		Frame();
	bool		Render();
	void		ComputeKernel(int iMask=3);
	
public:
	SQuadObject(void);
	~SQuadObject(void);
};

