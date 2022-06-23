#include "SVector3.h"

SVector3::SVector3()
{
	x = y = 0.0f;
}

SVector3::SVector3(float x, float y, float z)
{
	// �ڱ��ڽ��� x, y �϶�
	// this �� �ַ� ��������� �ʱ�ȭ�Ҷ� ���
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

// ���� ���� 
SVector3 SVector3 :: operator + (const SVector3& v)
{
	SVector3 ret;
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return ret;
}

// ���� ����
SVector3 SVector3:: operator - (const SVector3& v)
{
	SVector3 ret;
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return ret;
}

// ��Į���
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

// ����ȭ
// �ڱ��ڽ��� ����ȭ�Ұ���, ���͸� ����ȭ�Ұ���
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
// ũ��
// ret ���ϰ�
float SVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}