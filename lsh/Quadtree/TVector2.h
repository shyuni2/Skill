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
	// º¤ÅÍ µ¡¼À
	SVector2 operator + (const SVector2& v);
	// º¤ÅÍ »¬¼À
	SVector2 operator - (const SVector2& v);
	// ½ºÄ®¶ó °ö¼À
	SVector2 operator * (float fValue);
	SVector2 operator / (float fValue);
	bool operator == (const SVector2& v);
	bool operator != (const SVector2& v);
	// Á¤±ÔÈ­
	SVector2 Normalize();
	SVector2 Normal();
	friend SVector2 Normalize(SVector2& v);
	// Å©±â
	float Length();

};

