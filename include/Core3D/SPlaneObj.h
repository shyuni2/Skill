#pragma once
#include "SObj3D.h"

class SPlaneObj :   public SObj3D
{
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	SPlaneObj();
	virtual ~SPlaneObj();
};

