#pragma once
#include "Object2D.h"

class PlayerObj2D : public Object2D
{
public:
	bool Frame() override; 
public: // �浹ó��
	virtual void HitOverlap(BaseObject* pObj, DWORD dwState); 
public:
	PlayerObj2D();
	virtual ~PlayerObj2D();
};

