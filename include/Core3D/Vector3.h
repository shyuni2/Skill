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
	Vector3 operator + (const Vector3& v);
	Vector3 operator - (const Vector3& v);
	Vector3 operator * (float fValue);
	Vector3 operator / (float fValue);
	float operator | (Vector3 const& v); // 내적
	Vector3 operator ^ (Vector3 const& v); // 외적
	bool operator == (const Vector3& v);
	bool operator != (const Vector3& v);
public:
	void  operator += (const Vector3& v);
	void  operator -= (const Vector3& v);
public: // 정규화
	Vector3 Normalize();
	Vector3 Normal();
	friend Vector3 Normalize(Vector3& v);
public:
	float Length(); // 크기
};

