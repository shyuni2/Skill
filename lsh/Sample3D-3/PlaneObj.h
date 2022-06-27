#pragma once
#include "SObj3D.h"

class PlaneObj :   public SObj3D
{
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
public:
	PlaneObj();
	virtual ~PlaneObj();
};

