#pragma once
#include "TVector3.h"

// 충돌타입 
// RECT_OUT 떨어져있음, RECT_IN 안에 있음, RECT_OVERLAP 걸쳐있음

enum TCollisionType
{
	RECT_OUT = 0, RECT_IN, RECT_OVERLAP
};

// 상자
struct TRect
{
	TVector3 vMin; // 최소
	TVector3 vMax; // 최대
	TVector3 middle; // 중간
	TVector3 size; // 길이

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

	TRect(TVector3 vMin, TVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		middle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}

	TRect(TVector3 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + TVector3(w, h);
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
	static bool   RectToPoint(TRect rt, TVector3 v);
	static TCollisionType    RectToRect(TRect, TRect);
	static TRect  UnionRect(TRect rt1, TRect rt2);
	static bool  IntersectRect(TRect rt1, TRect rt2, TRect* rt);
};

