#pragma once
#include "SFrustum.h"

class SCamera : public SFrustum
{
public:
	float m_fNearDistance= 0.01f; // �ٰŸ�
	float m_fFarDistance = 1000.0f; // ���Ÿ�
public:
	float m_fPitch = 0.0f; // x�� ����
	float m_fYaw = 0.0f; // z�� ����
	float m_fRoll = 0.0f; // y�� ����
	float m_fRadius = 10.0f; // ������
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
	void CreateViewMatrix(S::SVector3 p,S::SVector3 t=S::SVector3(0, 0, 0), S::SVector3 u = S::SVector3(0,1,0)); // �� ��� ����
	void CreateProjMatrix(float fovy = XM_PI*0.25f, float Aspect = 1.44f, float zn=0.1f, float zf=5000.0f); // ���� ��� ����
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

