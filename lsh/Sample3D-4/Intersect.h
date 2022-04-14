#pragma once
#include "Core.h"

class Intersect : public Core
{
public:
	T::TVector3	m_vIntersection;
	std::vector<T::TVector3> m_vIntersectionList;
	bool GetIntersection(T::TVector3 vStart, T::TVector3 vEnd, T::TVector3 v0, T::TVector3 v1, T::TVector3 v2, T::TVector3 vNormal); // ���� ���
	bool PointInPolygon(T::TVector3 vert, T::TVector3 faceNormal, T::TVector3 v0, T::TVector3 v1, T::TVector3 v2); // ������ �� ���� ���� �׽�Ʈ 
	bool IntersectTriangle(const TVector3& orig, const TVector3& dir, TVector3& v0, TVector3& v1, TVector3& v2, FLOAT* t, FLOAT* u, FLOAT* v);
};

