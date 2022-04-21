#pragma once
#include "SDxObj.h"

class SObj3D : public SDxObj
{
public:
	S::SVector3 m_vPos; // 위치
	S::SVector3 m_vDirection; // 거리
	S::SVector4 m_vColor; // 색
public:		    
	S::SMatrix m_matWorld; // 월드행렬
	S::SMatrix m_matView; // 뷰행렬
	S::SMatrix m_matProj; // 투영행렬
public:		    
	S::SVector3 m_vLight; // x	
	S::SVector3 m_vUp; // y 
	S::SVector3 m_vLook; // z
public:
	// 페이드 인 아웃 : 장면이 시작될때 검은색이나 흰색에서 서서히 나타나게하는 기법
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(S::SVector3 vPos);
	virtual void SetPosition(S::SVector3 vPos);	
public:			 
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void SetMatrix(S::SMatrix* matWorld, S::SMatrix* matView, S::SMatrix* matProj);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
	virtual void UpdateData();
	virtual void UpdateCollision();
	virtual void GenAABB();
public:
	SObj3D();
	virtual ~SObj3D();
};

