#pragma once
#include "Vector3.h"

namespace Math
{
	struct float4x4
	{
		union {
			struct {
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
		Matrix operator * (Matrix const& matrix);
		void XRotate(float fRadian);
		void YRotate(float fRadian);
		void ZRotate(float fRadian);
		void Translation(const Math::Vector3& v);
		void Translation(float x, float y, float z);
		void Scale(const Math::Vector3& vector);
		void Scale(float x, float y, float z);
		void Identity();
		Matrix Transpose();		
		Matrix ViewLookAt(Math::Vector3& vPosition, Math::Vector3& vTarget, Math::Vector3& vUp); // ������ ���� �� ��� ���
		Matrix CreateViewLook(Math::Vector3& vPosition, Math::Vector3& vTarget, Math::Vector3& vUp); // ������ ���� �� ��� ���
		Matrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // ���� ���� ��� ���
		static Matrix RotationViewYawPitchRoll(float yaw, float pitch, float roll); // Yaw(Y��), Pitch(X��), Roll(Z��) ������ ȸ���ϴ� ȸ����� ����
	public:
		Matrix()
		{
			Identity();
		};
	};
}
