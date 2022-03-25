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
	UINT m_iNumCols=0; // ������ ���� �������� ����
	UINT m_iNumRows = 0; // ������ ���� �������� ����
	UINT m_iNumVertices = 0; // ���� ����
	UINT m_iNumCellCols = 0; // ���μ� ����
	UINT m_iNumCellRows = 0; // ���μ� ����
	UINT m_iNumFaces = 0; // ���̽� ����
	float m_fCellDistance = 1.0f; // ���� ����
public:
	float GetHeight(float fPosX, float fPosZ); //
	float GetHeightMap(int row, int col); // 
	float Lerp(float fStart, float fEnd, float fTangent); // ��������
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

