#pragma once
#include "Obj3D.h"

class TBoxObj : public Obj3D
{
public:
	Texture* m_pTexCube;
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	bool	PostRender();
public:
	TBoxObj();
	virtual ~TBoxObj();
};

