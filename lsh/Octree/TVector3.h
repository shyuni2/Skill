#pragma once
#include <math.h>

struct TFloat3
{
	union
	{
		float x, y,z;
		float v[3];
	};
};


class TVector3 : public TFloat3
{
public:
	TVector3();
	TVector3(float x, float y, float z);
	TVector3(const TVector3& v);
public:
	// º¤ÅÍ µ¡¼À
	TVector3 operator + (const TVector3& v);
	// º¤ÅÍ »¬¼À
	TVector3 operator - (const TVector3& v);
	// ½ºÄ®¶ó °ö¼À
	TVector3 operator * (float fValue);
	TVector3 operator / (float fValue);
	bool operator == (const TVector3& v);
	bool operator != (const TVector3& v);
	// Á¤±ÔÈ­
	TVector3 Normalize();
	TVector3 Normal();
	friend TVector3 Normalize(TVector3& v);
	// Å©±â
	float Length();

};

