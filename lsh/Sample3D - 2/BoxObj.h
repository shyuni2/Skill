#pragma once
#include "Obj3D.h"

class BoxObj : public Obj3D
{
public:
	Texture* m_pTexCube;
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	bool PostRender();
public:
	BoxObj();
	virtual ~BoxObj();
};

