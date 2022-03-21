#pragma once
#include "Obj3D.h"

struct Face
{
	// 버텍스버퍼 인덱스
	UINT v0, v1, v2; 
	Vector3 vNomal;
};


class Map : public Obj3D
{
public:
	std::vector <Face> m_FaceList;
	std::vector<float>  m_fHeightList;
public:
	UINT m_iNumCols = 0;
	UINT m_iNumRows = 0;
	UINT m_iNumVertices = 0;
	UINT m_iNumCellCols = 0;
	UINT m_iNumCellRows = 0;
	UINT m_iNumFaces = 0;
	float m_iCellDistance = 1.0f;
public:
	virtual bool CreateHeightMap(const TCHAR* strHeightMapTex);
	virtual bool CreateMap(UINT iWidth, UINT iHeight, float fDistance);
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool Frame() override;
public:
	Map();
	virtual ~Map();
};

