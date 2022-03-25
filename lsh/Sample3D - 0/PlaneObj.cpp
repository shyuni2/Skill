#include "PlaneObj.h"
bool		PlaneObj::SetVertexData()
{
	// Local Coord
	// Box
	//  0        1 
	//     ����
	//  2        3
	m_VertexList.resize(4);
	// -Z plane
	m_VertexList[0].p = Math::Vector3(-1.0f, 1.0f, 0.0f);
	m_VertexList[0].n = Math::Vector3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[0].t = Math::Vector2(0.0f, 0.0f);

	m_VertexList[1].p = Math::Vector3(1.0f, 1.0f, 0.0f);
	m_VertexList[1].n = Math::Vector3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[1].t = Math::Vector2(1.0f, 0.0f);


	m_VertexList[2].p = Math::Vector3(-1.0f, -1.0f, 0.0f);
	m_VertexList[2].n = Math::Vector3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[2].t = Math::Vector2(0.0f, 1.0f);


	m_VertexList[3].p = Math::Vector3(1.0f, -1.0f, 0.0f);
	m_VertexList[3].n = Math::Vector3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].c = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[3].t = Math::Vector2(1.0f, 1.0f);
	return true;
}
bool		PlaneObj::SetIndexData()
{
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(3); m_IndexList.push_back(2); m_IndexList.push_back(1);
	return true;
}
PlaneObj::PlaneObj()
{

}
PlaneObj::~PlaneObj()
{

}