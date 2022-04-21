#include "SCollision.h"

bool SCollision::SphereToPoint(Sphere sp, int x, int y, int z)
{
	float fDistance = (sp.vCenter - T::TVector3(x, y, z)).Length();
	if (fDistance <= sp.fRadius)
	{
		return true;
	}
	return false;
}
bool SCollision::SphereToPoint(Sphere sp, T::TVector3 v)
{
	float fDistance = (sp.vCenter - v).Length();
	if (fDistance <= sp.fRadius)
	{
		return true;
	}
	return false;
}
bool SCollision::RectToPoint(Rect rt, int x, int y)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x && rt.vMin.y <= y && rt.vMax.y >= y)
	{
		return true;
	}
	return false;
}
bool SCollision::RectToPoint(Rect rt, T::TVector2 v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x && rt.vMin.y <= v.y && rt.vMax.y >= v.y)
	{
		return true;
	}
	return false;
}
Rect SCollision::UnionRect(Rect rt1, Rect rt2)
{
	Rect rt;
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.size.x = rt.vMax.x - rt.vMin.x;
	rt.size.y = rt.vMax.y - rt.vMin.y;
	rt.vCenter = (rt.vMin + rt.vMax);
	rt.vCenter /= 2.0f;
	return rt;
}
bool SCollision::IntersectRect(Rect rt1, Rect rt2, Rect* pRect)
{
	Rect rt;
	Rect rtUnion = UnionRect(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ? rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ? rt1.vMax.y : rt2.vMax.y;

			pRect->size.x = pRect->vMax.x - pRect->vMin.x;
			pRect->size.y = pRect->vMax.y - pRect->vMin.y;
			pRect->vCenter = (pRect->vMax + pRect->vMin);
			pRect->vCenter /= 2.0f;
		}
		return true;
	}
	return false;
}
// 0 :  ������ �ִ�.
// 1 :  �ȿ� �ִ�.
// 2 :  ���� �ִ�.
CollisionResult SCollision::RectToRect(Rect rt1, Rect rt2)
{	
	Rect rtInterction;
	int iRet = IntersectRect(rt1, rt2, &rtInterction);
	if (iRet <= 0)
	{
		return RECT_OUT;
	}
	if (rtInterction == rt2) return RECT_OVERLAP;
	return RECT_IN;
}

CollisionResult SCollision::ToRect(Rect rt1,Rect rt2)
{
	// �Ÿ� ����
	float fDistanceX;
	float fDistanceY;
	fDistanceX = fabs(rt1.vCenter.x - rt2.vCenter.x);
	fDistanceY = fabs(rt1.vCenter.y - rt2.vCenter.y);
	float fToX = rt1.size.x / 2.0f + rt1.size.x / 2.0f;
	float fToY = rt1.size.y / 2.0f + rt1.size.y / 2.0f;
	if (fDistanceX < fToX && fDistanceY < fToY)
	{
		return RECT_OVERLAP;
	}
	return RECT_OUT;
}
bool SCollision::BoxToPoint(Box rt, int x, int y, int z)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x && rt.vMin.y <= y && rt.vMax.y >= y && rt.vMin.z <= z && rt.vMax.z >= z)
	{
		return true;
	}
	return false;
}
bool SCollision::BoxToPoint(Box rt, T::TVector3 v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x && rt.vMin.y <= v.y && rt.vMax.y >= v.y && rt.vMin.z <= v.z && rt.vMax.z >= v.z)
	{
		return true;
	}
	return false;
}
Box SCollision::UnionBox(Box rt1, Box rt2)
{
	Box rt;
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMin.z = rt1.vMin.z < rt2.vMin.z ? rt1.vMin.z : rt2.vMin.z;

	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.vMax.z = rt1.vMax.z < rt2.vMax.z ? rt2.vMax.z : rt1.vMax.z;

	rt.size = rt.vMax - rt.vMin;
	rt.vCenter = (rt.vMin + rt.vMax);
	rt.vCenter /= 2.0f;
	return rt;
}
bool SCollision::IntersectBox(Box rt1, Box rt2, Box* pRect)
{
	Box rt;
	Box rtUnion = UnionBox(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y) && rtUnion.size.z <= (rt1.size.z + rt2.size.z))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;
			pRect->vMin.z = rt1.vMin.z < rt2.vMin.z ? rt2.vMin.z : rt1.vMin.z;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ? rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ? rt1.vMax.y : rt2.vMax.y;
			pRect->vMax.z = rt1.vMax.z < rt2.vMax.z ? rt1.vMax.z : rt2.vMax.z;

			pRect->size = pRect->vMax - pRect->vMin;
			pRect->vCenter = (pRect->vMax + pRect->vMin);
			rt.vCenter /= 2.0f; 
		}
		return true;
	}
	return false;
}
// 0 :  ������ �ִ�.
// 1 :  �ȿ� �ִ�.
// 2 :  ���� �ִ�.
CollisionResult SCollision::BoxToBox(Box rt1, Box rt2)
{
	Box rtInterction;
	int iRet = IntersectBox(rt1, rt2, &rtInterction);
	if (iRet <= 0)
	{
		return RECT_OUT;
	}
	if (rtInterction == rt2) return RECT_OVERLAP;
	return RECT_IN;
}