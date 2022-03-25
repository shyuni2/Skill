#pragma once
#include "Obj3D.h"
struct Face
{
	UINT v0, v1, v2; 
	Math::Vector3 vNomal;
};

class Map : public Obj3D
{
public:
	std::vector< Face> m_FaceList;
	std::vector<float>  m_fHeightList;
public:
	UINT m_iNumCols=0; // 생성할 맵의 가로정점 개수
	UINT m_iNumRows = 0; // 생성할 맵의 세로정점 개수
	UINT m_iNumVertices = 0; // 정점 개수
	UINT m_iNumCellCols = 0; // 가로셀 개수
	UINT m_iNumCellRows = 0; // 세로셀 개수
	UINT m_iNumFaces = 0; // 페이스 개수
	float m_fCellDistance = 1.0f; // 셀의 길이
public:
	float GetHeight(float fPosX, float fPosZ); //
	float GetHeightMap(int row, int col); // 
	float Lerp(float fStart, float fEnd, float fTangent); // 선형보간
public:
	virtual bool CreateHeightMap(const TCHAR* strHeightMapTex);
	virtual bool CreateMap(UINT width, UINT height, float fDistance);
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool Frame() override;
public:
	Map();
	virtual ~Map();
};

