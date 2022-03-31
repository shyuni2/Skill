#pragma once
#include "Frustum.h"

class Camera : public Frustum
{
public:
	float m_fRadius=10.0f;
	T::Quaternion m_qRotation;
public:
	T::Vector3 m_vCamera;
	T::Vector3 m_vTarget;
	T::Vector3 m_vDefaultUp;

	T::Vector3 m_vRight; //x	
	T::Vector3 m_vUp; //y 
	T::Vector3 m_vLook; // z	

	T::Matrix m_matWorld;
	T::Matrix m_matView;
	T::Matrix m_matProj;
public:
	void CreateViewMatrix(T::Vector3 p,T::Vector3 t=T::Vector3(0, 0, 0), T::Vector3 u = T::Vector3(0,1,0));
	void CreateProjMatrix(float fovy = XM_PI*0.25f, float Aspect = 1.44f, float zn=0.1f, float zf=5000.0f);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Update(T::Vector4 vValue);
public:
	void MoveLook(float fValue);
	void MoveSide(float fValue);
	void MoveUp(float fValue);
	bool UpdateVector();
public:
	Camera();
	virtual ~Camera() {}
};

