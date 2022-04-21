#pragma once
#include "SObj3D.h"
#include <fbxsdk.h>
#include "SCamera.h"

// ��Ƽ��Ʈ��  (VB[0], VB[1])
// ��ǲ���̾ƿ� ( PNCTIW ) -> �������̴� ����

struct PNCT
{
	S::SVector3 p;
	S::SVector3 n;
	S::SVector4 c;
	S::SVector2 t;
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
	SMatrix matTrack;
	S::SVector3 s; // ũ�� 
	S::SQuaternion r; // ȸ��
	S::SVector3 t; // �̵�
};
struct Weight
{
	std::vector<int> vIndex;  // ������ ��ġ�� ����� �ε���
	std::vector<float>  vWeight; // ����ġ
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
	SMatrix m_matLocal;
	SMatrix m_matAnim;
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
	std::vector<STexture*> m_pTextureList;
	std::vector<Track> m_AnimTrack;
	std::map<std::wstring, SMatrix>	m_dxMatrixBindPoseMap;
public:
	virtual bool SetVertexData() override;
	virtual bool CreateVertexBuffer()override;
	virtual bool SetIndexData() override;
	virtual bool CreateInputLayout() override;
	virtual bool PostRender() override;
	virtual bool Release() override;
};
