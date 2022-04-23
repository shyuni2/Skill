#pragma once
#include "SMath.h"

// -- 충돌 결과
enum CollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
// -- 2D사각형
struct Rect2D
{
	// 화면좌표계+왼쪽상단이 원점

	S::SVector2 vMin;
	S::SVector2 vMax;
	S::SVector2 vCenter;
	S::SVector2 size;
	bool operator == (const Rect2D& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	Rect2D() {};
	Rect2D(S::SVector2 vMin, S::SVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect2D(S::SVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + S::SVector2(w, h);
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// -- 3D 사각형
struct Rect
{
	// 화면좌표계+중앙이 원점

	S::SVector2 vMin;
	S::SVector2 vMax;
	S::SVector2 vCenter;
	S::SVector2 size;
	bool operator == (const Rect& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	Rect() {};
	Rect(S::SVector2 vMin, S::SVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect(S::SVector2 pos, float w, float h)
	{
		vCenter = pos;
		this->vMin = vCenter - S::SVector2(w/2.0f, h/2.0f);
		this->vMax = vCenter + S::SVector2(w / 2.0f, h / 2.0f);		
		this->size.x = w;
		this->size.y = h;
	}
};
// -- 박스
struct SBox 
{
	// aabb 충돌 검사방법 : 각 축 방향에서 상자의 변이 겹치는지 확인
	// obb 충돌 검사방법 : 바운딩 박스로 겹치는지 확인, 회전하던 상관없이 중심점과 중심점 기준으로 바인딩 박스 영역 확인

	S::SVector3 vList[8];
	//aabb
	S::SVector3 vMin;
	S::SVector3 vMax;
	// obb
	S::SVector3 vCenter; // 중심
	S::SVector3 vAxis[3]; // 기저축 3개 x, y, z
	S::SVector3 size;
	bool operator == (const SBox& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	SBox() {};
	SBox(S::SVector3 vMin, S::SVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	SBox(S::SVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + S::SVector3(w, h,q);
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// -- 구
struct Sphere 
{
	S::SVector3 vCenter;
	float fRadius;
	Sphere()
	{
		fRadius = 3.0f;
	}
};

class SCollision
{
public:
	static bool SphereToPoint(Sphere rt, int x, int y, int z);
	static bool SphereToPoint(Sphere rt, S::SVector3 v);
	static bool RectToPoint(Rect rt, int x, int y);
	static bool RectToPoint(Rect rt, S::SVector2 v);
	static CollisionResult RectToRect(Rect,Rect);
	static CollisionResult ToRect(Rect rt1, Rect rt2);
	static Rect UnionRect(Rect rt1, Rect rt2);
	static bool IntersectRect(Rect rt1, Rect rt2, Rect* rt);
public:
	static bool BoxToPoint(SBox rt, int x, int y, int z);
	static bool BoxToPoint(SBox rt, S::SVector3 v);
	static CollisionResult BoxToBox(SBox, SBox);
	static SBox UnionBox(SBox rt1, SBox rt2);
	static bool IntersectBox(SBox rt1, SBox rt2, SBox* rt);
};

