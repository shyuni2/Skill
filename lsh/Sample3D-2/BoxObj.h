#pragma once
#include "SObj3D.h"

class BoxObj : public SObj3D
{
public:
	STexture* m_pTexCube;
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	bool	PostRender();
public:
	BoxObj();
	virtual ~BoxObj();
};

