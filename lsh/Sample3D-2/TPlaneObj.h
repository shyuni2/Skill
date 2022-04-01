#pragma once
#include "Obj3D.h"
class TPlaneObj :   public Obj3D
{
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
public:
	TPlaneObj();
	virtual ~TPlaneObj();
};

