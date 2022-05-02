#pragma once
#include "SBoxObj.h"
#include "SCamera.h"
#include "SObjMgr.h"


class SBox :public SObj3D
{
public:
	SCamera* m_pMainCamera;
	UINT m_iShadowID = 0;
	SVector4 m_vShadowColor;
public:
	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
	BoneWorld m_matBoneArray;
	std::vector<SBox> m_DrawList;
public:
	bool RenderShadow(SShader* pShader);
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release() override;
};
