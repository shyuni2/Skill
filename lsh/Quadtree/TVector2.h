#pragma once
#include <math.h>

struct TFloat2
{
	union
	{
		float x, y;
		float v[2];
	};
};


class SVector2 : public TFloat2
{
public:
	SVector2();
	SVector2(float x, float y);
	SVector2(const SVector2& v);
public:
	// ���� ����
	SVector2 operator + (const SVector2& v);
	// ���� ����
	SVector2 operator - (const SVector2& v);
	// ��Į�� ����
	SVector2 operator * (float fValue);
	SVector2 operator / (float fValue);
	bool operator == (const SVector2& v);
	bool operator != (const SVector2& v);
	// ����ȭ
	SVector2 Normalize();
	SVector2 Normal();
	friend SVector2 Normalize(SVector2& v);
	// ũ��
	float Length();

};

