#pragma once
#include "TVector2.h"

// 충돌타입 
// RECT_OUT 떨어져있음, RECT_IN 안에 있음, RECT_OVERLAP 걸쳐있음

enum TCollisionType
{
	RECT_OUT = 0, RECT_IN, RECT_OVERLAP
};

// 상자
struct TRect
{
	TVector2 vMin; // 최소
	TVector2 vMax; // 최대
	TVector2 middle; // 중간
	TVector2 size; // 길이

	bool operator == (const TRect& v)
	{
		// fabs는 절대값, 길이는 음수 불가능
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	
	TRect() {};

	TRect(TVector2 vMin, TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		middle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}

	TRect(TVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + TVector2(w, h);
		middle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};

// 충돌
class TCollision
{
public:
	static bool   RectToPoint(TRect rt, int x, int y);
	static bool   RectToPoint(TRect rt, TVector2 v);
	static TCollisionType    RectToRect(TRect, TRect);
	static TRect  UnionRect(TRect rt1, TRect rt2);
	static bool  IntersectRect(TRect rt1, TRect rt2, TRect* rt);
};

