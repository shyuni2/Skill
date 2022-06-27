#pragma once
#include "Node.h"
#include "Map.h"
#include "Camera.h"
class Quadtree
{
public:
	Map*	m_pMap=nullptr;
	Camera* m_pCamera = nullptr;
	int		m_iWidth;
	int		m_iHeight;
	int		m_iMaxDepth;
	Node*  m_pRootNode;
	static  int g_iCount;
public:
	std::list<MapObj*> m_ObjectList;
	std::vector<Node*> g_pDrawLeafNodes;
	std::vector<Node*> g_pLeafNodes;
	std::queue<Node*> g_Queue;	
	int g_iValue = 0;
public:
	void		Build(int iWidth, int iHeight, int iMaxDepth);
	Node*		CreateNode(Node* pParent, float x, float y, float w, float h);
public:
	void		Build(Map* pMap, int iMaxDepth);
	void		BuildTree(Node* pParent);
	SBox		GenBoundingBox(Node* pNode);
	SVector2	GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	bool		AddObject(MapObj* obj);
	bool		AddDynamicObject(MapObj* obj);

	void		DynamicDeleteObject(Node* pNode);
	Node*		FindNode(Node* pNode, TBox& box);
	bool		CheckBox(TBox& a, TBox& b);
public:
	void		SetIndexData(Node* pNode);
	bool		CreateIndexBuffer(Node* pNode);
	void		Update(Camera* pCamera);
	bool		Render();
	void		RenderObject(Node* pNode);
	void		RenderTile(Node* pNode);
public:
	void PrintObjectList(Node* pNode);
//	void BinaryNodePrintInOrder(Node* pNode);
//	void BinaryNodePrintPostOrder(Node* pNode);
//	void BinaryNodePrintLevelOrder(Node* pNode);

public:
	Quadtree() {};
	virtual ~Quadtree()
	{
		delete m_pRootNode;
	}
};
