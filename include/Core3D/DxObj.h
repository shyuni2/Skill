#pragma once
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "DxState.h"
#include "Collision.h"

struct SimpleVertex
{
	T::TVector2 v;
	T::TVector2 t;
};
struct Vertex
{
	T::TVector3 p; // 위치
	T::TVector3 n; // 노말
	T::TVector4 c; // 컬러
	T::TVector2 t; // 텍셀

	Vertex(T::TVector3 p1, T::TVector3 n1, T::TVector4 c1, T::TVector2 t1)
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
// 0001  - 기본
// 0010  - 권총
// 0100  - 장총
// 1000  - 수류탄
 
// 0111 = 7(속성)
// 1111 = 15
enum SelectState
{
	DEFAULT = 0,  // 커서가 위에 없을 때(FOCUS상태에서 다른 곳을 ACTIVE하면 전환된다.)
	HOVER = 1,	// 커서가 위에 있을 때
	FOCUS = 2,	// ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
	ACTIVE = 4,	// 마우스 왼쪽 버튼 누르고 있을 때
	SELECTED = 8, // ACTIVE 상태에서 왼쪼버튼 놓았을 때
};

class BaseObj
{
public:
	std::wstring m_csName;
public:
	BaseObj* m_pParent = nullptr;
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
	virtual void HitOverlap(BaseObj* pObj, DWORD dwState);
	virtual void HitSelect(BaseObj* pObj, DWORD dwState);
	virtual void SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisonType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:	
	BaseObj()
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
	T::TMatrix  matWorld;
	T::TMatrix  matView;
	T::TMatrix  matProj;
	T::TVector4 Color;
	T::TVector4 Timer;
};

struct BoneWorld
{
	T::TMatrix  matBoneWorld[255];
};

struct LightData
{
	T::TVector4 vLightDir;
	T::TVector4 vLightPos;
	T::TVector4 vCameraDir;
	T::TVector4 vCameraPos;
};

class DxObj : public BaseObj
{
public:
	Texture* m_pColorTex = nullptr;
	Texture* m_pMaskTex = nullptr;
	Shader*  m_pVShader = nullptr;
	Shader*  m_pPShader = nullptr;
	D3D11_TEXTURE2D_DESC m_TextureDesc;
public:
	std::vector<SimpleVertex> m_InitScreenList;
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
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext=nullptr;
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
	DxObj();
	~DxObj();
};

