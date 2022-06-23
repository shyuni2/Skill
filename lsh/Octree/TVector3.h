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


class SVector3 : public TFloat3
{
public:
	SVector3();
	SVector3(float x, float y, float z);
	SVector3(const SVector3& v);
public:
	// º¤ÅÍ µ¡¼À
	SVector3 operator + (const SVector3& v);
	// º¤ÅÍ »¬¼À
	SVector3 operator - (const SVector3& v);
	// ½ºÄ®¶ó °ö¼À
	SVector3 operator * (float fValue);
	SVector3 operator / (float fValue);
	bool operator == (const SVector3& v);
	bool operator != (const SVector3& v);
	// Á¤±ÔÈ­
	SVector3 Normalize();
	SVector3 Normal();
	friend SVector3 Normalize(SVector3& v);
	// Å©±â
	float Length();

};

