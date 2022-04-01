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
		TMatrix ViewLookAt(Math::TVector3& vPosition, Math::TVector3& vTarget, Math::TVector3& vUp); // 외적을 통한 뷰 행렬 계산
		TMatrix CreateViewLook(Math::TVector3& vPosition, Math::TVector3& vTarget, Math::TVector3& vUp); // 내적을 통한 뷰 행렬 계산
		TMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // 원근 투영 행렬 계산
		static TMatrix RotationViewYawPitchRoll(float yaw, float pitch, float roll); // Yaw(Y축), Pitch(X축), Roll(Z축) 값으로 회전하는 회전행렬 만듬
	public:
		TMatrix()
		{
			Identity();
		};
	};
}
