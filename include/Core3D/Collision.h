#pragma once
#include "Matrix.h"

enum CollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
// È­¸éÁÂÇ¥°è+¿ÞÂÊ»ó´ÜÀÌ ¿øÁ¡
struct Rect2D
{
	Math::Vector2 vMin;
	Math::Vector2 vMax;
	Math::Vector2 vMiddle;
	Math::Vector2 size;
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
	Rect2D(Math::Vector2 vMin, Math::Vector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect2D(Math::Vector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + Math::Vector2(w, h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// È­¸éÁÂÇ¥°è+Áß¾ÓÀÌ ¿øÁ¡
struct Rect
{
	Math::Vector2 vMin;
	Math::Vector2 vMax;
	Math::Vector2 vMiddle;
	Math::Vector2 size;
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
	Rect(Math::Vector2 vMin, Math::Vector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect(Math::Vector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - Math::Vector2(w/2.0f, h/2.0f);
		this->vMax = vMiddle + Math::Vector2(w / 2.0f, h / 2.0f);		
		this->size.x = w;
		this->size.y = h;
	}
};
struct Box
{
	Math::Vector3 vMin;
	Math::Vector3 vMax;
	Math::Vector3 vMiddle;
	Math::Vector3 size;
	bool operator == (const Box& v)
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
	Box() {};
	Box(Math::Vector3 vMin, Math::Vector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Box(Math::Vector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + Math::Vector3(w, h,q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct Sphere
{
	Math::Vector2 vCenter;
	float    fRadius;
	Sphere()
	{
		fRadius = 3.0f;
	}
};
class Collision
{
public:
	static bool SphereToPoint(Sphere rt, int x, int y);
	static bool SphereToPoint(Sphere rt, Math::Vector2 v);
	static bool RectToPoint(Rect rt, int x, int y);
	static bool RectToPoint(Rect rt, Math::Vector2 v);
	static CollisionResult RectToRect(Rect,Rect);
	static CollisionResult ToRect(Rect rt1, Rect rt2);
	static Rect UnionRect(Rect rt1, Rect rt2);
	static bool IntersectRect(Rect rt1, Rect rt2, Rect* rt);
public:
	static bool BoxToPoint(Box rt, int x, int y, int z);
	static bool BoxToPoint(Box rt, Math::Vector3 v);
	static CollisionResult BoxToBox(Box, Box);
	static Box UnionBox(Box rt1, Box rt2);
	static bool IntersectBox(Box rt1, Box rt2, Box* rt);
};

