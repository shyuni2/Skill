#pragma once
#include "SObj3D.h"

struct Face
{
	UINT v0, v1, v2; // vb index;
	T::TVector3 vNomal; // vb index;
};
//struct TVertexFace
//{
//	std::vector<UINT> iFaceList;
//};
class SMap : public SObj3D
{
public:
	std::vector< Face> m_FaceList;
	UINT m_iNumCols=0; // 열 개수
	UINT m_iNumRows = 0; // 행 개수
	UINT m_iNumVertices = 0; // 필드의 정점
	UINT m_iNumCellCols = 0; // 열당 셀 개수
	UINT m_iNumCellRows = 0; // 행당 셀 개수
	UINT m_iNumFaces = 0; // 페이스 개수
	float m_fCellDistance = 1.0f; // 셀 간의 거리
	std::vector<float> m_fHeightList; // 높이
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	virtual bool CreateHeightMap(const TCHAR* strHeightMapTex); // 높이맵 생성
	virtual bool CreateMap(UINT width, UINT height, float fDistance); // 맵 생성
	virtual bool Frame() override;
	virtual float GetHeight(int index);
	float GetHeight(float fPosX, float fPosZ);
	float GetHeightmap(int row, int col);
	float Lerp(float fStart, float fEnd, float fTangent); // 보간
public:
	SMap() {};
	virtual ~SMap() {};
};

