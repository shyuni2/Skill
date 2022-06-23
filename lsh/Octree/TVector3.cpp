#include "SVector3.h"

SVector3::SVector3()
{
	x = y = 0.0f;
}

SVector3::SVector3(float x, float y, float z)
{
	// 자기자신이 x, y 일때
	// this 는 주로 멤버변수를 초기화할때 사용
	this->x = x;
	this->y = y;
	this->z = z;
}

SVector3::SVector3(const SVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

// 벡터 덧셈 
SVector3 SVector3 :: operator + (const SVector3& v)
{
	SVector3 ret;
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return ret;
}

// 백터 뺄셈
SVector3 SVector3:: operator - (const SVector3& v)
{
	SVector3 ret;
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return ret;
}

// 스칼라곱
SVector3 SVector3::operator * (float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	this->z *= fValue;
	return *this;
}
SVector3 SVector3::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	this->z /= fValue;
	return *this;
}
bool SVector3::operator == (const SVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return true;
			}
		}
	}
	return false;
}
bool SVector3::operator != (const SVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return false;
			}
		}
	}
	return true;
}

// 정규화
// 자기자신을 정규화할건지, 벡터를 정규화할건지
SVector3 SVector3::Normal()
{
	SVector3 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	ret.z = z * length;
	return ret;
}
SVector3 SVector3::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	z *= length;
	return *this;
}
SVector3 Normalize(SVector3& v)
{
	SVector3 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	ret.z = v.z * length;
	return ret;
}
// 크기
// ret 리턴값
float SVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}