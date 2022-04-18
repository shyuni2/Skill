#pragma once
#include "TVector2.h"

namespace SMath
{
	struct Float3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};

	class TVector3 : public Float3
	{
	public:
		TVector3();
		TVector3(float x, float y, float z);
		TVector3(const TVector3& v);
	public:
		TVector3 operator + (const TVector3& v);
		TVector3 operator - (const TVector3& v);
		TVector3 operator * (float fValue);
		TVector3 operator / (float fValue);
		float operator | (TVector3 const& v); // 내적
		TVector3 operator ^ (TVector3 const& v); // 외적
		bool operator == (const TVector3& v);
		bool operator != (const TVector3& v);
	public:
		void operator += (const TVector3& v);
		void operator -= (const TVector3& v);
	public: // 정규화
		TVector3 Normalize();
		TVector3 Normal();
		friend TVector3 Normalize(TVector3& v);
	public:
		float Length(); // 크기
	};
}
