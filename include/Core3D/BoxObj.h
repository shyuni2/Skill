#pragma once
#include "Obj3D.h"
class BoxObj : public Obj3D
{
public:
	Texture* m_pTexCube;
	bool PostRender();
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	BoxObj();
	virtual ~BoxObj();
};

