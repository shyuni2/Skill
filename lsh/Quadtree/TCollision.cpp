#include "TCollision.h"

// 사각형과 점 충돌
// 사각형이 x,y와 부딪히는지
bool   TCollision::RectToPoint(TRect rt, int x, int y)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x && rt.vMin.y <= y && rt.vMax.y >= y)
	{
		return true; // 충돌
	}
	return false; // 충돌안함
}
// 사각형이 벡터와 충돌하는지
bool   TCollision::RectToPoint(TRect rt, TVector2 v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x && rt.vMin.y <= v.y && rt.vMax.y >= v.y)
	{
		return true;
	}
	return false;
}

// 합집합 (포함)
TRect   TCollision::UnionRect(TRect rt1, TRect rt2)
{
	TRect rt;
	// Min.x는 rt1의 최소 x값이 rt2의 최소x값 보다 작으면 rt1 최소x 아니면 rt2 x
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	// 가로길이는 큰x - 작은x
	rt.size.x = rt.vMax.x - rt.vMin.x;
	rt.size.y = rt.vMax.y - rt.vMin.y;
	// 중간길이는 큰거+작은거 나누기2
	rt.middle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}

// 교집합 (겹침)
bool   TCollision::IntersectRect(TRect rt1, TRect rt2, TRect* pRect)
{
	TRect rt;
	TRect rtUnion = UnionRect(rt1, rt2);
	// 교집합은 중복길이가 있으니까 고려함
	// 합집합의 가로길이가 rt1의 가로길이 + rt2의 가로길이보다 작거나 같고, 세로길이가 rt1의 세로길이 + rt2의 세로길이보다 작거나 같을때
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			// rt1의 최소 x가 rt2의 최소 x보다 작으면 rt2의 최소 x 아니면 rt1의 최소 x
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ?rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ?rt2.vMin.y : rt1.vMin.y;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ?rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ?rt1.vMax.y : rt2.vMax.y;

			pRect->size.x = pRect->vMax.x - pRect->vMin.x;
			pRect->size.y = pRect->vMax.y - pRect->vMin.y;

			pRect->middle = (pRect->vMax + pRect->vMin) / 2.0f;
		}
		return true;
	}
	return false;
}

// 충돌타입 
// RECT_OUT 떨어져있음, RECT_IN 안에 있음, RECT_OVERLAP 걸쳐있음
TCollisionType   TCollision::RectToRect(TRect rt1, TRect rt2)
{
	TRect rtInterction;
	int iRet = IntersectRect(rt1, rt2, &rtInterction);
	if (iRet <= 0)
		return RECT_OUT;
	
	if (rtInterction == rt2) 
		return RECT_OVERLAP;

	return RECT_IN;
}