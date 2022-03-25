#pragma once
#include "STD.h"

class Camera
{
public:
	Math::Vector3 m_vCamera;
	Math::Vector3 m_vTarget;
	Math::Vector3 m_vDefaultUP;
public:
	Math::Vector3 m_vLight; // x
	Math::Vector3 m_vUp; // y 
	Math::Vector3 m_vLook; // z
public:
	Math::Matrix m_matWorld;
	Math::Matrix m_matView;
	Math::Matrix m_matProj;
public:
	virtual bool	Init();
	virtual bool	Frame();
	Camera();
	virtual ~Camera() {}
};

