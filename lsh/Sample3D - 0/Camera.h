#pragma once
#include "STD.h"

class Camera
{
public:
	Vector3 m_vCamera;
	Vector3 m_vTarget;
	Vector3 m_vDefaultUP;
public:
	Vector3 m_vLight; // x
	Vector3 m_vUp; // y 
	Vector3 m_vLook; // z
public:
	Matrix m_matWorld;
	Matrix m_matView;
	Matrix m_matProj;
public:
	virtual bool	Init();
	virtual bool	Frame();
	Camera();
	virtual ~Camera() {}
};

