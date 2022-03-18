#pragma once
#include "TNode.h"


class TQuadtree
{
public: // 쿼드트리를 만드려면? 가로(width), 세로(height), 최대깊이, 시작노드(Root)가 있어야함 
	int	m_iWidth;
	int	m_iHeight;
	int	m_iMaxDepth;
	TNode* m_pRootNode;

public:
	vector<TNode*> g_ppArray;
	queue<TNode*> g_Queue;
	int g_iValue = 0;

public:
	void Init(int iWidth, int iHeight, int iMaxDepth);
	TNode* CreateNode(TNode* pParent, float x, float y, float w, float h);
	void BuildTree(TNode* pParent);
	bool AddObject(TObject* obj);
	TNode* FindNode(TNode* pNode, int x, int y);
	TNode* FindNode(TNode* pNode, TRect rt);

public:
	void PrintObjectList(TNode* pNode);
};

