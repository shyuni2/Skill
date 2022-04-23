#pragma once
#include "STD.h"
#include "SBoxObj.h"

class SFrustum : public SBoxObj
{
public:
	S::SPlane m_Plane[6];
	S::SVector3 m_vFrustum[8];
public:
	bool Init();
	bool PostRender();
	void CreateFrustum(S::SMatrix& matView, S::SMatrix& matProj);
public:
	BOOL ClassifyPoint(S::SVector3* v);
	BOOL ClassifySphere(Sphere* v);
	BOOL ClassifyOBB(SBox* v);
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
};

