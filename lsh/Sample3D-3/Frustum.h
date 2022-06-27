#pragma once
#include "STD.h"
#include "BoxObj.h"
class Frustum : public BoxObj
{
public:
	S::TPlane   m_Plane[6];
	S::SVector3 m_vFrustum[8];
public:
	bool		Init();
	void		CreateFrustum(	S::SMatrix& matView, 
								S::SMatrix& matProj);
	BOOL ClassifyPoint(S::SVector3* v);
	BOOL ClassifySphere(TSphere* v);
	BOOL ClassifyOBB(TBox* v);
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	bool	PostRender();
};

