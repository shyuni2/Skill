#pragma once
#include <iostream>
#include <math.h>

namespace SMath
{
	// -- Vector2 
	struct Float2
	{
		union
		{
			struct { float x, y; };
			float v[2];
		};
	};	
	class SVector2 : public Float2
	{
	public:
		SVector2();
		SVector2(float x, float y);
		SVector2(const SVector2& v);
	public:
		SVector2 operator + (const SVector2& v);
		SVector2 operator - (const SVector2& v);
		SVector2 operator * (float fValue);
		SVector2 operator / (float fValue);
		SVector2 operator += (const SVector2& v);
		SVector2 operator -= (const SVector2& v);
		bool operator == (const SVector2& v);
		bool operator != (const SVector2& v);
		// 정규화
		SVector2 Normalize();
		SVector2 Normal();
		friend SVector2 Normalize(SVector2& v);

		float Length(); // 크기
		float Distance(SVector2& v); //거리
	};

	// -- Vector4
	struct Float4
	{
		union
		{
			struct { float x, y, z, w; };
			float v[4];
		};
	};
	class SVector4 : public Float4
	{
	public:
		SVector4()
		{
			v[0] = 0.0f;
			v[1] = 0.0f;
			v[2] = 0.0f;
			v[3] = 0.0f;
		};
		SVector4(float x, float y, float z, float w)
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}
		SVector4(const SVector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}
	};
}