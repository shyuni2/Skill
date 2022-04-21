#pragma once
#include "SObj3D.h"

class SBoxObj : public SObj3D
{
public:
	Texture* m_pTexCube;
	bool PostRender();
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	SBoxObj();
	virtual ~SBoxObj();
};

