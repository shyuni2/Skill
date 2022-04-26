#pragma once
#include "SObj3D.h"

class BoxObj : public SObj3D
{
public:
	STexture* m_pTexCube;
public:
	bool PostRender();
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	BoxObj();
	virtual ~BoxObj();
};

