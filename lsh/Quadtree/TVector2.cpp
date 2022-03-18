#include "TVector2.h"

TVector2::TVector2()
{
	x = y = 0.0f;
}

TVector2::TVector2 (float x, float y)
{
	// 자기자신이 x, y 일때
	// this 는 주로 멤버변수를 초기화할때 사용
	this->x = x;
	this->y = y;
}

TVector2::TVector2(const TVector2& v)
{
	x = v.x;
	y = v.y;
}

// 벡터 덧셈 
TVector2 TVector2 :: operator + (const TVector2& v)
{
	TVector2 ret;
	this->x += v.x;
	this->y += v.y;
	return ret;
}

// 백터 뺄셈
TVector2 TVector2:: operator - (const TVector2& v)
{
	TVector2 ret;
	this->x -= v.x;
	this->y -= v.y;
	return ret;
}

// 스칼라곱
TVector2 TVector2::operator * (float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	return *this;
}
TVector2 TVector2::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	return *this;
}
bool TVector2::operator == (const TVector2& v)
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
bool TVector2::operator != (const TVector2& v)
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

// 정규화
// 자기자신을 정규화할건지, 벡터를 정규화할건지
TVector2 TVector2::Normal()
{
	TVector2 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	return ret;
}
TVector2 TVector2::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	return *this;
}
TVector2 Normalize(TVector2& v)
{
	TVector2 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	return ret;
}
// 크기
// ret 리턴값
float TVector2::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}