#pragma once
#include "DxObj.h"

class Obj3D : public DxObj
{
public:
	T::TVector3			m_vPos;
	T::TVector3			m_vDirection;
	T::TVector4			m_vColor;
public:
	T::TMatrix			m_matWorld;
	T::TMatrix			m_matView;
	T::TMatrix			m_matProj;
public:
	T::TVector3			m_vLight; //x	
	T::TVector3			m_vUp; //y 
	T::TVector3			m_vLook; // z
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(T::TVector3 vPos);
	virtual void SetPosition(T::TVector3 vPos);	
public:			 
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void SetMatrix(T::TMatrix* matWorld, T::TMatrix* matView, T::TMatrix* matProj);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
	virtual void UpdateData();
	virtual void UpdateCollision();
	virtual void GenAABB();
public:
	Obj3D();
	virtual ~Obj3D();
};

