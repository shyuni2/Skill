#pragma once
#include "Obj3D.h"
struct Face
{
	UINT v0, v1, v2; // vb index;
	Vector3 vNomal; // vb index;
};
//struct TVertexFace
//{
//	std::vector<UINT> iFaceList;
//};
class Map : public Obj3D
{
public:
	std::vector< Face> m_FaceList;
	//std::vector< TVertexFace> m_VertexFaceList;

	UINT		m_iNumCols=0;
	UINT		m_iNumRows = 0;
	UINT        m_iNumVertices = 0;
	UINT		m_iNumCellCols = 0;
	UINT		m_iNumCellRows = 0;
	UINT        m_iNumFaces = 0;
	float       m_iCellDistance = 1.0f;
	std::vector<float>  m_fHeightList;
public:
	virtual bool		CreateHeightMap(const TCHAR* strHeightMapTex);
	virtual bool		CreateMap(UINT width, UINT height, float fDistance);
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	virtual bool		Frame() override;
public:
	Map();
	virtual ~Map();
};

