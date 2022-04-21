#pragma once
#include "SVector2.h"

namespace SMath
{
	// -- Vector3
	struct Float3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};

	class SVector3 : public Float3
	{
	public:
		SVector3();
		SVector3(float x, float y, float z);
		SVector3(const SVector3& v);
	public:
		SVector3 operator + (const SVector3& v);
		SVector3 operator - (const SVector3& v);
		SVector3 operator * (float fValue);
		SVector3 operator / (float fValue);
		float operator | (SVector3 const& v); // 내적
		SVector3 operator ^ (SVector3 const& v); // 외적
		bool operator == (const SVector3& v);
		bool operator != (const SVector3& v);
	public:
		void operator += (const SVector3& v);
		void operator -= (const SVector3& v);
	public: // 정규화
		SVector3 Normalize();
		SVector3 Normal();
		friend SVector3 Normalize(SVector3& v);
	public:
		float Length(); // 크기
	};
}
