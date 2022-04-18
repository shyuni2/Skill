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
	class TVector2 : public Float2
	{
	public:
		TVector2();
		TVector2(float x, float y);
		TVector2(const TVector2& v);
	public:
		TVector2 operator + (const TVector2& v);
		TVector2 operator - (const TVector2& v);
		TVector2 operator * (float fValue);
		TVector2 operator / (float fValue);
		TVector2 operator += (const TVector2& v);
		TVector2 operator -= (const TVector2& v);
		bool operator == (const TVector2& v);
		bool operator != (const TVector2& v);
		// 정규화
		TVector2 Normalize();
		TVector2 Normal();
		friend TVector2 Normalize(TVector2& v);

		float Length(); // 크기
		float Distance(TVector2& v); //거리
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
	class TVector4 : public Float4
	{
	public:
		TVector4()
		{
			v[0] = 0.0f;
			v[1] = 0.0f;
			v[2] = 0.0f;
			v[3] = 0.0f;
		};
		TVector4(float x, float y, float z, float w)
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}
		TVector4(const TVector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}
	};
}