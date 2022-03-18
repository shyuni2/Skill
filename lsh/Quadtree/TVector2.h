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


class TVector2 : public TFloat2
{
public:
	TVector2();
	TVector2(float x, float y);
	TVector2(const TVector2& v);
public:
	// º¤ÅÍ µ¡¼À
	TVector2 operator + (const TVector2& v);
	// º¤ÅÍ »¬¼À
	TVector2 operator - (const TVector2& v);
	// ½ºÄ®¶ó °ö¼À
	TVector2 operator * (float fValue);
	TVector2 operator / (float fValue);
	bool operator == (const TVector2& v);
	bool operator != (const TVector2& v);
	// Á¤±ÔÈ­
	TVector2 Normalize();
	TVector2 Normal();
	friend TVector2 Normalize(TVector2& v);
	// Å©±â
	float Length();

};

