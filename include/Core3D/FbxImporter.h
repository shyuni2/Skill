#pragma once
#include "Obj3D.h"
#include <fbxsdk.h>
#include "Camera.h"

// ��Ƽ��Ʈ��  (VB[0], VB[1])
// ��ǲ���̾ƿ� ( PNCTIW ) -> �������̴� ����

struct PNCT
{
	T::TVector3 p;
	T::TVector3 n;
	T::TVector4 c;
	T::TVector2 t;
};
struct VerterIW
{
	float i[4];
	float w[4];
	VerterIW()
	{
		i[0] = i[1] = i[2] = i[3] = 0;
		w[0] = w[1] = w[2] = w[3] = 0.0f;
	}
};
struct Track
{
	UINT iFrame;
	TMatrix matTrack;
	T::TVector3 s; // ũ�� 
	T::TQuaternion r; // ȸ��
	T::TVector3 t; // �̵�
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
class FbxImporter
{
};

