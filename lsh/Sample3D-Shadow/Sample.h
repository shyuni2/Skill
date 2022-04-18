#pragma once
#include "Core.h"
#include "SFbxObj.h"
#include "Map.h"
#include "Quadtree.h"
#include "SQuadObject.h"

// 맵생성 클래스 
class SSampleMap : public Map
{
public:
	virtual float GetHeight(int index) override
	{
		return Map::GetHeight(index) * 0.1f;
	}
	virtual ~SSampleMap() {};
};

class Sample : public Core
{
	SSampleMap m_MapObj; 
	Quadtree m_Quadtree;
	std::vector<SFbxObj> m_FbxObj;
	SQuadObject m_QuadObj;
	Shader* m_pShadowPShader = nullptr; 
	Texture* m_pLightTex; 
	Texture* m_pNormalMap;
public:
	bool LoadMap();
	bool LoadFbx();
public:
	void DisplayErrorBox(const WCHAR* lpszFunction);
	DWORD LoadAllPath(const TCHAR* argv, std::vector<std::wstring>& list);
public:
	void RenderIntoBuffer(ID3D11DeviceContext* pContext);
	void RenderMRT(ID3D11DeviceContext* pContext);
public:
	virtual void CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:			 
	virtual bool Init()  override;
	virtual bool Frame()  override;
	virtual bool Render()  override;
	virtual bool Release()  override;

public:
	Sample();
	virtual ~Sample();
};

