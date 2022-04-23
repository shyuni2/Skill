#include "SPlaneObj.h"

bool SPlaneObj::SetVertexData()
{
	// Local Coord
	// SBox
	//  0        1 
	//     ¿øÁ¡
	//  2        3
	m_VertexList.resize(4);
	// -Z plane
	m_VertexList[0].p = S::SVector3(-1.0f, 1.0f, 0.0f);
	m_VertexList[0].n = S::SVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = S::SVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[0].t = S::SVector2(0.0f, 0.0f);

	m_VertexList[1].p = S::SVector3(1.0f, 1.0f, 0.0f);
	m_VertexList[1].n = S::SVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = S::SVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[1].t = S::SVector2(1.0f, 0.0f);


	m_VertexList[2].p = S::SVector3(-1.0f, -1.0f, 0.0f);
	m_VertexList[2].n = S::SVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = S::SVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[2].t = S::SVector2(0.0f, 1.0f);


	m_VertexList[3].p = S::SVector3(1.0f, -1.0f, 0.0f);
	m_VertexList[3].n = S::SVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].c = S::SVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[3].t = S::SVector2(1.0f, 1.0f);
	return true;
}
bool SPlaneObj::SetIndexData()
{
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(3); m_IndexList.push_back(2); m_IndexList.push_back(1);
	return true;
}
SPlaneObj::SPlaneObj()
{

}
SPlaneObj::~SPlaneObj()
{

}