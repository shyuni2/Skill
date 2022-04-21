#pragma once
#include "STD.h"
#include "SBoxObj.h"

class SFrustum : public SBoxObj
{
public:
	T::TPlane m_Plane[6];
	T::TVector3 m_vFrustum[8];
public:
	bool Init();
	bool PostRender();
	void CreateFrustum(T::TMatrix& matView, T::TMatrix& matProj);
public:
	BOOL ClassifyPoint(T::TVector3* v);
	BOOL ClassifySphere(Sphere* v);
	BOOL ClassifyOBB(Box* v);
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
};

