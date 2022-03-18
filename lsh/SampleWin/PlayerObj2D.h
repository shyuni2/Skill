#pragma once
#include "Obj2D.h"
#include "SoundMgr.h"

#define LEFT 0x25
#define RIGHT 0x27

#define Z 0x5A // �뽬
#define X 0x58 // ����
#define C 0x43 // ����

class PlayerObj2D :  public Obj2D
{
public:
	virtual void HitOverlap(BaseObj* pObj, DWORD dwState);
public:
	bool Frame() override;
public:
	PlayerObj2D();
	virtual ~PlayerObj2D();
};

