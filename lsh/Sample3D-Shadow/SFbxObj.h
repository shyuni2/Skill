#pragma once
#include "SFbxImporter.h"
#include "SCamera.h"
class SFbx :public SObj3D
{
public:
	SCamera* m_pMainCamera;
public:
	SFbxImporter* m_pMeshImp;
	SFbxImporter* m_pAnimImporter;
	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
	BoneWorld			m_matBoneArray;
	std::vector<SFbx>	m_DrawList;
public:
	virtual bool	Init()override;
	virtual bool	Frame()override;
	virtual bool	Render()override;
	virtual bool    Release() override;
	void			GenAABB()override;
public:
	bool	RenderShadow(SShader* pShader);
	S::SMatrix Interplate(SFbxImporter* pAnimImp,SFbxModel* pModel, float fFrame);
};
