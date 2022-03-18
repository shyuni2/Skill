#include "TCollision.h"

// �簢���� �� �浹
// �簢���� x,y�� �ε�������
bool   TCollision::RectToPoint(TRect rt, int x, int y)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x && rt.vMin.y <= y && rt.vMax.y >= y)
	{
		return true; // �浹
	}
	return false; // �浹����
}
// �簢���� ���Ϳ� �浹�ϴ���
bool   TCollision::RectToPoint(TRect rt, TVector2 v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x && rt.vMin.y <= v.y && rt.vMax.y >= v.y)
	{
		return true;
	}
	return false;
}

// ������ (����)
TRect   TCollision::UnionRect(TRect rt1, TRect rt2)
{
	TRect rt;
	// Min.x�� rt1�� �ּ� x���� rt2�� �ּ�x�� ���� ������ rt1 �ּ�x �ƴϸ� rt2 x
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	// ���α��̴� ūx - ����x
	rt.size.x = rt.vMax.x - rt.vMin.x;
	rt.size.y = rt.vMax.y - rt.vMin.y;
	// �߰����̴� ū��+������ ������2
	rt.middle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}

// ������ (��ħ)
bool   TCollision::IntersectRect(TRect rt1, TRect rt2, TRect* pRect)
{
	TRect rt;
	TRect rtUnion = UnionRect(rt1, rt2);
	// �������� �ߺ����̰� �����ϱ� �����
	// �������� ���α��̰� rt1�� ���α��� + rt2�� ���α��̺��� �۰ų� ����, ���α��̰� rt1�� ���α��� + rt2�� ���α��̺��� �۰ų� ������
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			// rt1�� �ּ� x�� rt2�� �ּ� x���� ������ rt2�� �ּ� x �ƴϸ� rt1�� �ּ� x
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

// �浹Ÿ�� 
// RECT_OUT ����������, RECT_IN �ȿ� ����, RECT_OVERLAP ��������
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