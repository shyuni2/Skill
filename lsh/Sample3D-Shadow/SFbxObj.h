#pragma once
#include "SFbxImporter.h"
#include "Camera.h"

class SFbxObj :public Obj3D
{
public:
	Camera* m_pMainCamera;
	SFbxImporter* m_pMeshImp;
	SFbxImporter* m_pAnimImporter;
	BoneWorld m_matBoneArray;
	std::vector<SFbxObj> m_DrawList;
public:
	float m_fDir = 1.0f; // �Ÿ�
	float m_fTime = 0.0f; // �ð�
	float m_fSpeed = 1.0f; // �ӵ�
public:
	void GenAABB()override; // aabb
	bool RenderShadow(Shader* pShader); // �׸��� ������
	T::TMatrix Interplate(SFbxImporter* pAnimImp, SFbxModel* pModel, float fFrame); // ����
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release() override;

};
