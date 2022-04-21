#include "SVector2.h"

namespace SMath
{
	SVector2::SVector2()
	{
		x = y = 0.0f;
	}
	SVector2::SVector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	SVector2::SVector2(const SVector2& v)
	{
		x = v.x;
		y = v.y;
	}
	SVector2 SVector2::operator + (const SVector2& v)
	{
		SVector2 ret;
		ret.x = this->x + v.x;
		ret.y = this->y + v.y;	
		return ret;
	}
	SVector2 SVector2::operator - (const SVector2& v)
	{
		SVector2 ret;
		ret.x = this->x - v.x;
		ret.y = this->y - v.y;
		return ret;
	}

	SVector2 SVector2::operator * (float fValue)
	{
		SVector2 ret;
		ret.x = this->x * fValue;
		ret.y = this->y * fValue;	
		return ret;
	}
	SVector2 SVector2::operator / (float fValue)
	{
		SVector2 ret;
		ret.x = this->x / fValue;
		ret.y = this->y / fValue;
		return ret;
	}
	SVector2 SVector2::operator += (const SVector2& v)
	{
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		return *this;
	}
	SVector2 SVector2::operator -= (const SVector2& v)
	{
		this->x = this->x - v.x;
		this->y = this->y - v.y;
		return *this;
	}
	bool SVector2::operator == (const SVector2& v)
	{
		if (fabs(x - v.x) < 0.0001f)
		{
			if (fabs(y - v.y) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	bool SVector2::operator != (const SVector2& v)
	{
		if (fabs(x - v.x) < 0.0001f)
		{
			if (fabs(y - v.y) < 0.0001f)
			{
				return false;
			}
		}
		return true;
	}

	SVector2 SVector2::Normal()
	{
		SVector2 ret;
		float length = 1.0f / Length();
		ret.x = x * length;
		ret.y = y * length;
		return ret;
	}
	SVector2 SVector2::Normalize()
	{
		float length = 1.0f / Length();
		x *= length;
		y *= length;
		return *this;
	}
	SVector2 Normalize( SVector2& v)
	{
		SVector2 ret;
		float length = 1.0f / v.Length();
		ret.x = v.x * length;
		ret.y = v.y * length;
		return ret;
	}
	// 크기
	float SVector2::Length()
	{
		float ret = x * x + y * y;
		return sqrt(ret);
	}
	// 두벡터의 거리 반환
	float SVector2::Distance(SVector2& v)
	{
		float fDist = (*this - v).Length();
		return fDist;
	}
}