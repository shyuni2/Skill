#pragma once
#include "SMath.h"

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
// -- 3D �簢��
struct Rect
{
	// ȭ����ǥ��+�߾��� ����

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
// -- �ڽ�
struct SBox 
{
	// aabb �浹 �˻��� : �� �� ���⿡�� ������ ���� ��ġ���� Ȯ��
	// obb �浹 �˻��� : �ٿ�� �ڽ��� ��ġ���� Ȯ��, ȸ���ϴ� ������� �߽����� �߽��� �������� ���ε� �ڽ� ���� Ȯ��

	S::SVector3 vList[8];
	//aabb
	S::SVector3 vMin;
	S::SVector3 vMax;
	// obb
	S::SVector3 vCenter; // �߽�
	S::SVector3 vAxis[3]; // ������ 3�� x, y, z
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
// -- ��
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

