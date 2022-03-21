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
public: // 회전
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);
public: // 변환
	void Translation(const Vector3& v);
	void Translation(float x, float y, float z);
public: // 크기
	void Scale(const Vector3& vector);
	void Scale(float x, float y, float z);
public:
	void Identiity(); // 단위행렬
	Matrix Transpose(); // 전치행렬
public:
	Matrix ViewLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUP); // 외적을 통한 뷰 행렬 계산
	Matrix CreateViewLook(Vector3& vPosition, Vector3& vTarget, Vector3& vUp); // 내적을 통한 뷰 행렬 계산
	Matrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // 원근 투영 행렬 계산
public:
	Matrix()
	{
		Identiity();
	};
	~Matrix() {};
};

