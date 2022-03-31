#pragma once
#include "DxObj.h"

class Obj3D : public DxObj
{
public:
	T::Vector3 m_vPos;
	T::Vector3 m_vDirection;
	T::Vector4 m_vColor;
	T::Matrix m_matWorld;
public:
	T::Vector3 m_vLight;
	T::Vector3 m_vUp;
	T::Vector3 m_vLook;
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(T::Vector3 vPos);
	virtual void SetPosition(T::Vector3 vPos);	
public:			 
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void  UpdateData() {}
	virtual void SetMatrix(T::Matrix* matWorld, T::Matrix* matView, T::Matrix* matProj);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
public:
	virtual void GenAABB();
public:
	Obj3D();
	virtual ~Obj3D();
};

