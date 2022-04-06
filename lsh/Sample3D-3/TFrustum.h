#pragma once
#include "STD.h"
#include "BoxObj.h"
class Frustum : public BoxObj
{
public:
	T::TPlane   m_Plane[6];
	T::TVector3 m_vFrustum[8];
public:
	bool		Init();
	void		CreateFrustum(	T::TMatrix& matView, 
								T::TMatrix& matProj);
	BOOL ClassifyPoint(T::TVector3* v);
	BOOL ClassifySphere(TSphere* v);
	BOOL ClassifyOBB(TBox* v);
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	bool	PostRender();
};

