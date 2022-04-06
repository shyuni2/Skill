#pragma once
#include "Node.h"


class Quadtree
{
public: // ����Ʈ���� �������? ����(width), ����(height), �ִ����, ���۳��(Root)�� �־���� 
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

