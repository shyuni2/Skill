#pragma once
#include "Node.h"


class Quadtree
{
public: // 쿼드트리를 만드려면? 가로(width), 세로(height), 최대깊이, 시작노드(Root)가 있어야함 
	int	m_iWidth;
	int	m_iHeight;
	int	m_iMaxDepth;
	Node* m_pRootNode;

public:
	vector<Node*> g_ppArray;
	queue<Node*> g_Queue;
	int g_iValue = 0;

public:
	void Init(int iWidth, int iHeight, int iMaxDepth);
	Node* CreateNode(Node* pParent, float x, float y, float w, float h);
	void BuildTree(Node* pParent);
	bool AddObject(TObject* obj);
	Node* FindNode(Node* pNode, int x, int y);
	Node* FindNode(Node* pNode, TRect rt);

public:
	void PrintObjectList(Node* pNode);
};

