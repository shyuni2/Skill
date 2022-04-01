#pragma once
#include "TVector3.h"

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

	class TMatrix : public float4x4
	{
	public:
		TMatrix operator * (TMatrix const& matrix);
		void XRotate(float fRadian);
		void YRotate(float fRadian);
		void ZRotate(float fRadian);
		void Translation(const Math::TVector3& v);
		void Translation(float x, float y, float z);
		void Scale(const Math::TVector3& vector);
		void Scale(float x, float y, float z);
		void Identity();
		TMatrix Transpose();		
		TMatrix ViewLookAt(Math::TVector3& vPosition, Math::TVector3& vTarget, Math::TVector3& vUp); // ������ ���� �� ��� ���
		TMatrix CreateViewLook(Math::TVector3& vPosition, Math::TVector3& vTarget, Math::TVector3& vUp); // ������ ���� �� ��� ���
		TMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // ���� ���� ��� ���
		static TMatrix RotationViewYawPitchRoll(float yaw, float pitch, float roll); // Yaw(Y��), Pitch(X��), Roll(Z��) ������ ȸ���ϴ� ȸ����� ����
	public:
		TMatrix()
		{
			Identity();
		};
	};
}
