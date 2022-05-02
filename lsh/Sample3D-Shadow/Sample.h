#pragma once
#include "SCore.h"
#include "SFbxObj.h"
#include "SMap.h"
#include "SQuadtree.h"
#include "SQuadObject.h"
#include "SDxRT.h"

class SSampleMap : public SMap
{
public:
	virtual float		GetHeight(int index) override
	{
		return SMap::GetHeight(index) * 0.1f;
	}
	virtual ~SSampleMap() {}
};
class Sample : public SCore
{
	SSampleMap				m_MapObj;
	SQuadtree				m_Quadtree;
	std::vector<SFbx>		m_FbxObj;
	SQuadObject				m_QuadObj;
	SShader* m_pShadowPShader = nullptr;
	STexture* m_pLightTex;
	STexture* m_pNormalMap;
	bool		m_bDepthShadow = true;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>  m_pRSSlopeScaledDepthBias;
public:
	SShader* m_pProjShadowVShader = nullptr;
	SShader* m_pProjShadowPShader = nullptr;
	SDxRT		m_dxRT;
	SVector3	m_vLightPos;
	SVector3	m_vLightDir;
	SMatrix		m_matShadow;
	SMatrix		m_matViewLight;
	SMatrix		m_matProjLight;
	SMatrix		m_matTex;
	void		RenderDepthShadow(SMatrix* matView, SMatrix* matProj);
	void		RenderProjectionShadow(SMatrix* matView, SMatrix* matProj);
public:
	SShader* m_pDepthShadowVShader = nullptr;
	SShader* m_pDepthShadowPShader = nullptr;
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;
public:
	bool	LoadMap();
	bool    LoadFbx();
public:
	void		RenderIntoBuffer(ID3D11DeviceContext* pContext);
	void		RenderMRT(ID3D11DeviceContext* pContext);
public:
	Sample();
	virtual ~Sample();
};

