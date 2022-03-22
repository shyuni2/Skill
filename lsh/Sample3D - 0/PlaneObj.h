#pragma once
#include "Obj3D.h"
class PlaneObj :   public Obj3D
{
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
public:
	PlaneObj();
	virtual ~PlaneObj();
};

