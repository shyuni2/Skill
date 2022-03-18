#pragma once
#include "TVector3.h"

// �浹Ÿ�� 
// RECT_OUT ����������, RECT_IN �ȿ� ����, RECT_OVERLAP ��������

enum TCollisionType
{
	RECT_OUT = 0, RECT_IN, RECT_OVERLAP
};

// ����
struct TRect
{
	TVector3 vMin; // �ּ�
	TVector3 vMax; // �ִ�
	TVector3 middle; // �߰�
	TVector3 size; // ����

	bool operator == (const TRect& v)
	{
		// fabs�� ���밪, ���̴� ���� �Ұ���
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

// �浹
class TCollision
{
public:
	static bool   RectToPoint(TRect rt, int x, int y);
	static bool   RectToPoint(TRect rt, TVector3 v);
	static TCollisionType    RectToRect(TRect, TRect);
	static TRect  UnionRect(TRect rt1, TRect rt2);
	static bool  IntersectRect(TRect rt1, TRect rt2, TRect* rt);
};

