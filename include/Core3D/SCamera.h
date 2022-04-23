#pragma once
#include "SFrustum.h"

class SCamera : public SFrustum
{
public:
	float m_fNearDistance= 0.01f; // 근거리
	float m_fFarDistance = 1000.0f; // 원거리
public:
	float m_fPitch = 0.0f; // x축 기준
	float m_fYaw = 0.0f; // z축 기준
	float m_fRoll = 0.0f; // y축 기준
	float m_fRadius = 10.0f; // 반지름
public:
	S::SQuaternion m_qRotation;
	S::SVector3	m_vCamera;
	S::SVector3	m_vTarget;
	S::SVector3	m_vDefaultUp;

	S::SVector3	m_vRight; //x	
	S::SVector3	m_vUp; //y 
	S::SVector3	m_vLook; // z	

	S::SMatrix m_matWorld;
	S::SMatrix m_matView;
	S::SMatrix m_matProj;
public:
	void CreateViewMatrix(S::SVector3 p,S::SVector3 t=S::SVector3(0, 0, 0), S::SVector3 u = S::SVector3(0,1,0)); // 뷰 행렬 생성
	void CreateProjMatrix(float fovy = XM_PI*0.25f, float Aspect = 1.44f, float zn=0.1f, float zf=5000.0f); // 투영 행렬 생성
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Update(S::SVector4 vValue);
	void MoveLook(float fValue);
	void MoveSide(float fValue);
	void MoveUp(float fValue);
	bool UpdateVector();
	SCamera();
	virtual ~SCamera() {}
};

