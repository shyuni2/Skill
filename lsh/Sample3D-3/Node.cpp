#include "Node.h"

void Node::AddObject(MapObj* obj)
{
	m_StaticObjectList.push_back(obj);
}
void Node::AddDynamicObject(MapObj* obj)
{
	m_DynamicObjectList.push_back(obj);
}
void Node::DelDynamicObject(MapObj* obj)
{
	m_DynamicObjectList.clear();
}
Node::Node() 
{
	m_pParent = nullptr;
	m_iDepth = 0;
	for (std::list<MapObj*>::iterator iter = m_StaticObjectList.begin();
		iter != m_StaticObjectList.end();
		iter++)
	{
		MapObj* pObj = *iter;
		delete pObj;
	}
	m_StaticObjectList.clear();
};

// 0, 4, 20 ,24
Node::Node(float x, float y, float w, float h) : Node()
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
Node::~Node()
{
	delete m_pChild[0];
	delete m_pChild[1];
	delete m_pChild[2];
	delete m_pChild[3];
}