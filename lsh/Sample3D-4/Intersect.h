#pragma once
#include "SCore.h"

class Intersect : public SCore
{
public:
	S::SVector3	m_vIntersection;
	std::vector<S::SVector3> m_vIntersectionList;
	bool GetIntersection(S::SVector3 vStart, S::SVector3 vEnd, S::SVector3 v0, S::SVector3 v1, S::SVector3 v2, S::SVector3 vNormal); // ���� ���
	bool PointInPolygon(S::SVector3 vert, S::SVector3 faceNormal, S::SVector3 v0, S::SVector3 v1, S::SVector3 v2); // ������ �� ���� ���� �׽�Ʈ 
	bool IntersectTriangle(const SVector3& orig, const SVector3& dir, SVector3& v0, SVector3& v1, SVector3& v2, FLOAT* t, FLOAT* u, FLOAT* v);
};

