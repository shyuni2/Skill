#pragma once
#include "SObj3D.h"
#include <fbxsdk.h>
#include "SCamera.h"

// 멀티스트림  (VB[0], VB[1])
// 인풋레이아웃 ( PNCTIW ) -> 정점쉐이더 전달

struct PNCT
{
	T::TVector3 p;
	T::TVector3 n;
	T::TVector4 c;
	T::TVector2 t;
};
struct VertexIW
{
	float i[4];
	float w[4];
	VertexIW()
	{
		i[0] = i[1] = i[2] = i[3] = 0;
		w[0] = w[1] = w[2] = w[3] = 0.0f;
	}
};
struct Track
{
	UINT iFrame;
	TMatrix matTrack;
	T::TVector3 s; // 크기 
	T::TQuaternion r; // 회전
	T::TVector3 t; // 이동
};
struct Weight
{
	std::vector<int> vIndex;  // 영향을 미치는 행렬의 인덱스
	std::vector<float>  vWeight; // 가중치
	void InsertWeight(int iBoneIndex, float fBoneWeight)
	{
		for (DWORD i = 0; i < vIndex.size(); ++i)
		{
			if (fBoneWeight > vWeight[i])
			{
				for (DWORD j = (vIndex.size() - 1); j > i; --j)
				{
					vIndex[j] = vIndex[j - 1];
					vWeight[j] = vWeight[j - 1];
				}
				vIndex[i] = iBoneIndex;
				vWeight[i] = fBoneWeight;
				break;
			}
		}
	}
	Weight()
	{
		vIndex.resize(8);
		vWeight.resize(8);
	}
};
struct Scene
{
	UINT iStart;
	UINT iEnd;
	UINT iFrameSpeed;
};

class SFbxModel : public SObj3D
{
public:
	SCamera* m_pMainCamera;
public:
	int m_iIndex = -1;
	bool m_bSkinned = false;
	TMatrix m_matLocal;
	TMatrix m_matAnim;
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	SFbxModel* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
public: // submaterial
	std::vector<std::wstring>  m_szTexFileList;
	using SubVertex = std::vector<Vertex>;
	using SubVertexIW = std::vector<VertexIW>;
	std::vector<SubVertex> m_pSubVertexList;
	std::vector<SubVertexIW> m_pSubIWVertexList;
	std::vector<Weight> m_WeightList;
public:
	std::vector<ID3D11Buffer*> m_pVBList;
	std::vector<ID3D11Buffer*> m_pVBWeightList;
	std::vector<Texture*> m_pTextureList;
	std::vector<Track> m_AnimTrack;
	std::map<std::wstring, TMatrix>	m_dxMatrixBindPoseMap;
public:
	virtual bool SetVertexData() override;
	virtual bool CreateVertexBuffer()override;
	virtual bool SetIndexData() override;
	virtual bool CreateInputLayout() override;
	virtual bool PostRender() override;
	virtual bool Release() override;
};
