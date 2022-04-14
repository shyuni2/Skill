#include "Intersect.h"

bool Intersect::GetIntersection(T::TVector3 vStart, T::TVector3 vEnd, T::TVector3 v0, T::TVector3 v1, T::TVector3 v2, T::TVector3 vNormal) 
{
	T::TVector3 vDirection = vEnd - vStart;
	T::TVector3 v0toStart = v0 - vStart;
	float A = T::D3DXVec3Dot(&vNormal, &vDirection);
	float a = T::D3DXVec3Dot(&vNormal, &v0toStart);
	float t = a / A;
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}
	m_vIntersection = vStart + vDirection * t;
	return true;
}

bool Intersect::PointInPolygon(T::TVector3 vert, T::TVector3 faceNormal, T::TVector3 v0, T::TVector3 v1, T::TVector3 v2) 
{
	T::TVector3 e0, e1, e2, iInter, vNormal;
	e0 = v1 - v0;
	e1 = v2 - v1;
	e2 = v0 - v2;

	iInter = vert - v0;
	T::D3DXVec3Cross(&vNormal, &e0, &iInter);
	T::D3DXVec3Normalize(&vNormal, &vNormal);
	float fDot = D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	iInter = vert - v1;
	T::D3DXVec3Cross(&vNormal, &e1, &iInter);
	T::D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = T::D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	iInter = vert - v2;
	T::D3DXVec3Cross(&vNormal, &e2, &iInter);
	T::D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = T::D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;
	return true;
};
bool Intersect::IntersectTriangle(const TVector3& orig, const TVector3& dir, TVector3& v0, TVector3& v1, TVector3& v2, FLOAT* t, FLOAT* u, FLOAT* v)
{
	TVector3 edge1 = v1 - v0;
	TVector3 edge2 = v2 - v0;

	TVector3 pvec;
	D3DXVec3Cross(&pvec, &dir, &edge2);

	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	TVector3 tvec;
	if (det > 0)
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if (det < 0.0001f) { return false; }

	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det) { return false; }

	TVector3 qvec;
	D3DXVec3Cross(&qvec, &tvec, &edge1);

	*v = D3DXVec3Dot(&dir, &qvec);
	if (*v < 0.0f || *u + *v > det) { return false; }

	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;
	return true;
}