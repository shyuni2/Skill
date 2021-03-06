#include "SMatrix.h"

namespace SMath
{
	SMatrix SMatrix::operator * (SMatrix const& matrix)
	{
		SMatrix OutMatrix;
		for (int iColumn = 0; iColumn < 4; iColumn++)
		{
			for (int iRow = 0; iRow < 4; iRow++)
			{
				OutMatrix.m[iRow][iColumn] = m[iRow][0] * matrix.m[0][iColumn] + m[iRow][1] * matrix.m[1][iColumn] + m[iRow][2] * matrix.m[2][iColumn] + m[iRow][3] * matrix.m[3][iColumn];
			}
		}
		return OutMatrix;
	}
	void SMatrix::XRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_22 = fCos;
		_23 = fSin;
		_32 = -fSin;
		_33 = fCos;
	}
	void SMatrix::YRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_11 = fCos;
		_13 = -fSin;
		_31 = fSin;
		_33 = fCos;
	}
	void SMatrix::ZRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_11 = fCos;
		_12 = fSin;
		_21 = -fSin;
		_22 = fCos;
	}
	void SMatrix::Translation(const SMath::SVector3& v)
	{
		_41 = v.x;
		_42 = v.y;
		_43 = v.z;
	}
	void SMatrix::Translation(float x, float y, float z)
	{
		_41 = x;
		_42 = y;
		_43 = z;
	}
	void SMatrix::Scale(const SMath::SVector3& vector)
	{
		_11 = vector.x;
		_22 = vector.y;
		_33 = vector.z;
	}
	void SMatrix::Scale(float x, float y, float z)
	{
		_11 = x;
		_22 = y;
		_33 = z;
	}
	void SMatrix::Identity()
	{
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
		_11 = _22 = _33 = _44 = 1.0f;
	}
	SMatrix SMatrix::Transpose()
	{
		SMatrix matrix;
		matrix._11 = _11; matrix._12 = _21; matrix._13 = _31; matrix._14 = _41;
		matrix._21 = _12; matrix._22 = _22; matrix._23 = _32; matrix._24 = _42;
		matrix._31 = _13; matrix._32 = _23; matrix._33 = _33; matrix._34 = _43;
		matrix._41 = _14; matrix._42 = _24; matrix._43 = _34; matrix._44 = _44;
		return matrix;
	}
	SMatrix SMatrix::ViewLookAt(SMath::SVector3& vPosition, SMath::SVector3& vTarget, SMath::SVector3& vUp)
	{
		SMatrix matrix;
		SMath::SVector3 vDirection = (vTarget - vPosition).Normal();		// Z Axis
		SMath::SVector3 vRightVector = (vUp ^ vDirection).Normal();		// X Axis
		SMath::SVector3 vUpVector = (vDirection ^ vRightVector).Normal();	// Y Axis

		_11 = vRightVector.x;	_12 = vUpVector.x;	_13 = vDirection.x;
		_21 = vRightVector.y;	_22 = vUpVector.y;	_23 = vDirection.y;
		_31 = vRightVector.z;	_32 = vUpVector.z;	_33 = vDirection.z;

		_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
		_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
		_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
		memcpy((void*)&matrix, this, 16 * sizeof(float));
		return matrix;
	}
	SMatrix SMatrix::CreateViewLook(SMath::SVector3& vPosition, SMath::SVector3& vTarget, SMath::SVector3& vUp)
	{
		SMatrix matrix;
		SMath::SVector3 vDirection = vTarget - vPosition;
		vDirection = vDirection.Normal();//z
		float fDot = vUp | vDirection;
		// ?????? ?????? ????
		SMath::SVector3 vUpVector = vUp - (vDirection * fDot);
		vUpVector = vUpVector.Normal();
		SMath::SVector3 vRightVector = vUpVector ^ vDirection;

		_11 = vRightVector.x;	_12 = vUpVector.x;	_13 = vDirection.x;
		_21 = vRightVector.y;	_22 = vUpVector.y;	_23 = vDirection.y;
		_31 = vRightVector.z;	_32 = vUpVector.z;	_33 = vDirection.z;
		_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
		_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
		_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
		memcpy((void*)&matrix, this, 16 * sizeof(float));
		return matrix;
	}
	SMatrix SMatrix::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
	{
		float    h, w, Q;

		h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
		w = h / Aspect;

		Q = fFarPlane / (fFarPlane - fNearPlane);

		SMatrix ret;
		memset(this, 0, sizeof(SMatrix));

		_11 = w;
		_22 = h;
		_33 = Q;
		_43 = -Q * fNearPlane;
		_34 = 1;

		memcpy((void*)&ret, this, 16 * sizeof(float));
		return ret;
	}
	SMatrix SMatrix::RotationViewYawPitchRoll(float yaw, float pitch, float roll)
	{
		SMatrix matY;
		matY.YRotate(yaw);
		SMatrix matX;
		matY.YRotate(pitch);
		SMatrix matZ;
		matY.YRotate(roll);
		SMatrix ret = matZ * matX * matY;
		return ret;
	}
}