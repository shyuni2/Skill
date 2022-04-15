#pragma once
#include "SFbxImporter.h"
#include "Camera.h"

class SFbxObj : public Obj3D
{
public:
	Camera* m_pMainCamera;
	SFbxImporter* m_pMeshImporter;
	SFbxImporter* m_pAnimImporter;
	BoneWorld m_matBoneArray;
public:
	std::vector<SFbxObj> m_DrawList;
	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	void GenAABB() override;
public:
	T::TMatrix Interplate(SFbxImporter* pAnimImporter, SFbxModel* pModel, float fTime);
};

