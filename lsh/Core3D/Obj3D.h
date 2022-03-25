#pragma once
#include "DxObj.h"

class Obj3D : public DxObj
{
public:
	Math::Vector3 m_vPos;
	Math::Vector3 m_vDirection;
	Math::Vector4 m_vColor;
	Math::Matrix m_matWorld;
public:
	Math::Vector3 m_vLight;
	Math::Vector3 m_vUp;
	Math::Vector3 m_vLook;
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(Math::Vector3 vPos);
	virtual void SetPosition(Math::Vector3 vPos);	
public:			 
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void  UpdateData() {}
	virtual void SetMatrix(Math::Matrix* matWorld, Math::Matrix* matView, Math::Matrix* matProj);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
public:
	Obj3D();
	virtual ~Obj3D();
};

