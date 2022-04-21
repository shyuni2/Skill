#pragma once
#include "TMath.h"

// -- �浹 ���
enum CollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
// -- 2D�簢��
struct Rect2D
{
	// ȭ����ǥ��+���ʻ���� ����

	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vCenter;
	T::TVector2 size;
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
	Rect2D(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect2D(T::TVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector2(w, h);
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// -- 3D �簢��
struct Rect
{
	// ȭ����ǥ��+�߾��� ����

	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vCenter;
	T::TVector2 size;
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
	Rect(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect(T::TVector2 pos, float w, float h)
	{
		vCenter = pos;
		this->vMin = vCenter - T::TVector2(w/2.0f, h/2.0f);
		this->vMax = vCenter + T::TVector2(w / 2.0f, h / 2.0f);		
		this->size.x = w;
		this->size.y = h;
	}
};
// -- �ڽ�
struct Box 
{
	// aabb �浹 �˻��� : �� �� ���⿡�� ������ ���� ��ġ���� Ȯ��
	// obb �浹 �˻��� : �ٿ�� �ڽ��� ��ġ���� Ȯ��, ȸ���ϴ� ������� �߽����� �߽��� �������� ���ε� �ڽ� ���� Ȯ��

	T::TVector3 vList[8];
	//aabb
	T::TVector3 vMin;
	T::TVector3 vMax;
	// obb
	T::TVector3 vCenter; // �߽�
	T::TVector3 vAxis[3]; // ������ 3�� x, y, z
	T::TVector3 size;
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
	Box(T::TVector3 vMin, T::TVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Box(T::TVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector3(w, h,q);
		vCenter = (vMax + vMin);
		vCenter /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// -- ��
struct Sphere 
{
	T::TVector3 vCenter;
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
	static bool SphereToPoint(Sphere rt, T::TVector3 v);
	static bool RectToPoint(Rect rt, int x, int y);
	static bool RectToPoint(Rect rt, T::TVector2 v);
	static CollisionResult RectToRect(Rect,Rect);
	static CollisionResult ToRect(Rect rt1, Rect rt2);
	static Rect UnionRect(Rect rt1, Rect rt2);
	static bool IntersectRect(Rect rt1, Rect rt2, Rect* rt);
public:
	static bool BoxToPoint(Box rt, int x, int y, int z);
	static bool BoxToPoint(Box rt, T::TVector3 v);
	static CollisionResult BoxToBox(Box, Box);
	static Box UnionBox(Box rt1, Box rt2);
	static bool IntersectBox(Box rt1, Box rt2, Box* rt);
};

