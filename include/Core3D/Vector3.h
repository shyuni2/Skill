#pragma once
#include "Vector2.h"

struct Float3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};

class Vector3 : public Float3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);
public:
	Vector3 operator + (const Vector3& v); // µ¡¼À
	Vector3 operator - (const Vector3& v); // »¬¼À
	Vector3 operator * (float fValue); // °ö¼À
	Vector3 operator / (float fValue); // ³ª´°¼À 
	float operator | (Vector3 const& v); // ³»Àû
	Vector3 operator ^ (Vector3 const& v); // ¿ÜÀû
	void operator += (const Vector3& v);
	void operator -= (const Vector3& v);
public:
	bool operator == (const Vector3& v);
	bool operator != (const Vector3& v);
public:// Á¤±ÔÈ­
	Vector3 Normalize();
	Vector3 Normal();
	friend Vector3 Normalize(Vector3& v);
public:
	float Length(); // Å©±â
};

