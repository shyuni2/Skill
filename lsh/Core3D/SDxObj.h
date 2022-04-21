#pragma once
#include "SShaderMgr.h"
#include "STextureMgr.h"
#include "SDxState.h"
#include "SCollision.h"

struct SimpleVertex
{
	S::SVector2 v;
	S::SVector2 t;
};
struct Vertex
{
	S::SVector3 p; // 위치
	S::SVector3 n; // 노말
	S::SVector4 c; // 컬러
	S::SVector2 t; // 텍셀

	Vertex(S::SVector3 p1, S::SVector3 n1, S::SVector4 c1, S::SVector2 t1)
	{
		p = p1;
		n = n1;
		c = c1;
		t = t1;
	}
	Vertex()
	{

	}
};

enum CollisionType
{
	Block = 0,
	Overlap,
	Ignore,
};
enum SelectType
{
	Select_Block = 0,
	Select_Overlap,
	Select_Ignore,
};
enum SelectState
{
	DEFAULT = 0,  // 커서가 위에 없을 때(FOCUS상태에서 다른 곳을 ACTIVE하면 전환)
	HOVER = 1,	// 커서가 위에 있을 때
	FOCUS = 2,	// ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
	ACTIVE = 4,	// 마우스 왼쪽 버튼 누르고 있을 때
	SELECTED = 8, // ACTIVE 상태에서 왼쪽버튼 놓았을 때
};

class SBaseObj
{
public:
	std::wstring m_csName;
public:
	SBaseObj* m_pParent = nullptr;
	bool m_bDead;
	int	m_iCollisionID;
	int	m_iSelectID;
	float m_fSpeed;	
	float m_fWidth;
	float m_fHeight;
	Rect m_rtCollision;
	Box m_BoxCollision;
	DWORD m_dwCollisonType;
	DWORD m_dwSelectType;
	DWORD m_dwSelectState;
	DWORD m_dwPreSelectState;
	bool m_bSelect;
	bool m_bAlphaBlend;
public:
	virtual void HitOverlap(SBaseObj* pObj, DWORD dwState);
	virtual void HitSelect(SBaseObj* pObj, DWORD dwState);
	virtual void SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisonType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:	
	SBaseObj()
	{
		m_bDead = false;
		m_bSelect = false;
		m_bAlphaBlend = true;
		m_dwSelectState = DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;	
		m_dwCollisonType = CollisionType::Ignore;
		m_dwSelectType = SelectType::Select_Ignore;
	}
};
struct Index
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};
struct ConstantData
{
	S::SMatrix matWorld; // 월드행렬
	S::SMatrix matView; // 뷰행렬
	S::SMatrix matProj; // 투영행렬
	S::SVector4 Color;
	S::SVector4 Timer;
};
struct BoneWorld 
{
	S::SMatrix  matBoneWorld[255]; // 뼈대행렬?
};
struct LightData
{
	S::SVector4 vLightDir; // 빛 거리
	S::SVector4 vLightPos; // 빛 위치
	S::SVector4 vCameraDir; // 카메라 거리
	S::SVector4 vCameraPos; // 카메라 위치
};

class SDxObj : public SBaseObj
{
public:
	STexture* m_pColorTex = nullptr;
	STexture* m_pMaskTex = nullptr; 

	// 쉐이더 지정해주기 전까진 NULL
	SShader* m_pVShader = nullptr;
	SShader* m_pPShader = nullptr;

	D3D11_TEXTURE2D_DESC m_TextureDesc;
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	std::vector<SimpleVertex> m_InitScreenList;
public:
	std::vector<Vertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
public:
	std::vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
public:
	ConstantData m_ConstantList;
	ID3D11Buffer* m_pConstantBuffer = nullptr;
public:
	LightData m_LightConstantList;
	ID3D11Buffer* m_pLightConstantBuffer = nullptr;
public:	
	void SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool SetConstantData();
public:
	virtual bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, const TCHAR* szShaderFileName = nullptr, const TCHAR* szTextureFileName = nullptr, const TCHAR* szMaskFileName = nullptr);
	virtual bool CreateVertexBuffer();
	virtual bool CreateIndexBuffer();
	virtual bool CreateConstantBuffer();
	virtual bool CreateVertexShader(const TCHAR* szFile);
	virtual bool CreatePixelShader(const TCHAR* szFile);
	virtual bool CreateInputLayout();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool Draw();
	virtual bool PostRender();
	virtual bool Release();
public:
	SDxObj();
	~SDxObj();
};

