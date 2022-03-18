#pragma once
#include "Obj2D.h"

class ObjectNpc2D :   public Obj2D
{
public:
	void HitOverlap(BaseObj* pObj, DWORD dwState);
	void HitSelect(BaseObj* pObj, DWORD dwState);
public:
	bool Frame() override;
public:
	ObjectNpc2D();
	virtual ~ObjectNpc2D();
};

