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
	UINT m_iNumCols=0; // �� ����
	UINT m_iNumRows = 0; // �� ����
	UINT m_iNumVertices = 0; // �ʵ��� ����
	UINT m_iNumCellCols = 0; // ���� �� ����
	UINT m_iNumCellRows = 0; // ��� �� ����
	UINT m_iNumFaces = 0; // ���̽� ����
	float m_fCellDistance = 1.0f; // �� ���� �Ÿ�
	std::vector<float> m_fHeightList; // ����
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	virtual bool CreateHeightMap(const TCHAR* strHeightMapTex); // ���̸� ����
	virtual bool CreateMap(UINT width, UINT height, float fDistance); // �� ����
	virtual bool Frame() override;
	virtual float GetHeight(int index);
	float GetHeight(float fPosX, float fPosZ);
	float GetHeightmap(int row, int col);
	float Lerp(float fStart, float fEnd, float fTangent); // ����
public:
	SMap() {};
	virtual ~SMap() {};
};

