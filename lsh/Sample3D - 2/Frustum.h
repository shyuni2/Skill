#pragma once
#include "STD.h"
#include "BoxObj.h"

class Frustum : public BoxObj
{
public:
	T::Plane   m_Plane[6];
	T::Vector3 m_vFrustum[8];
public:
	bool Init();
	void CreateFrustum(T::Matrix& matView, T::Matrix& matProj);
public:
	BOOL ClassifyPoint(T::Vector3* v);
	BOOL ClassifySphere(Sphere* v);
	BOOL ClassifyOBB(Box* v);
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	bool PostRender();
};

