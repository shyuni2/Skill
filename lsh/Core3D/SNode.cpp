#include "SNode.h"

void SNode::AddStaticObject(MapObj* obj)
{
	m_StaticObjectList.push_back(obj);
}
void SNode::AddDynamicObject(MapObj* obj)
{
	m_DynamicObjectList.push_back(obj);
}
void SNode::DelDynamicObject(MapObj* obj)
{
	m_DynamicObjectList.clear();
}

// -- 노드가 생성될때
SNode::SNode() 
{
	m_pParent = nullptr; // 시작노드의 부모는 x
	m_iDepth = 0; // 깊이 0
	for (std::list<MapObj*>::iterator iter = m_StaticObjectList.begin(); iter != m_StaticObjectList.end(); iter++)
	{
		MapObj* pObj = *iter;
		delete pObj;
	}
	m_StaticObjectList.clear();
};
// 0, 4, 20 ,24
SNode::SNode(float x, float y, float w, float h) : SNode()
{
	m_CornerList.push_back(x);
	m_CornerList.push_back(y);
	m_CornerList.push_back(w);
	m_CornerList.push_back(h);

	m_pChild.resize(4);
	m_pChild[0] = nullptr;
	m_pChild[1] = nullptr;
	m_pChild[2] = nullptr;
	m_pChild[3] = nullptr;
}
SNode::~SNode()
{
	delete m_pChild[0];
	delete m_pChild[1];
	delete m_pChild[2];
	delete m_pChild[3];
}