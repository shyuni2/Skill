#pragma once
#include "Vector3.h"

struct float4x4
{
	union 
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class Matrix : public float4x4
{
public:
	Matrix operator * (Matrix const& Matrix);
public: // ȸ��
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);
public: // ��ȯ
	void Translation(const Vector3& v);
	void Translation(float x, float y, float z);
public: // ũ��
	void Scale(const Vector3& vector);
	void Scale(float x, float y, float z);
public:
	void Identiity(); // �������
	Matrix Transpose(); // ��ġ���
public:
	Matrix ViewLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUP); // ������ ���� �� ��� ���
	Matrix CreateViewLook(Vector3& vPosition, Vector3& vTarget, Vector3& vUp); // ������ ���� �� ��� ���
	Matrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // ���� ���� ��� ���
public:
	Matrix()
	{
		Identiity();
	};
	~Matrix() {};
};

