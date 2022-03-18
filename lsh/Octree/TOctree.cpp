#include "TQuadtree.h"

// 노드 만들기
TNode* TQuadtree::CreateNode(TNode* pParent, float x, float y, float w, float h)
{
	TNode* pNode = new TNode(x, y, w, h);
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}
	return pNode;
}

// 트리 초기화
void TQuadtree::Init(int iWidth, int iHeight, int iMaxDepth)
{
	m_iMaxDepth = iMaxDepth;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pRootNode = CreateNode(nullptr, 0, 0, m_iWidth, m_iHeight);
	BuildTree(m_pRootNode);
}

// 트리 만들기
void TQuadtree::BuildTree(TNode* pParent)
{
	// 깊이가 최대깊이일때 리턴
	if (pParent->m_iDepth == m_iMaxDepth) return;
	// 1번은 제자리, 2번은 x만 이동, 3번은 x,y 둘다이동, 4번은 x원위치 y만 이동 - 사각형 시계방향
	// 0번은 x,y
	pParent->pChild[0] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMin.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	// 1번은 mx,y
	pParent->pChild[1] = CreateNode(pParent, pParent->m_rt.middle.x, pParent->m_rt.vMin.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[1]);
	// 2번은 mx,my
	pParent->pChild[2] = CreateNode(pParent,
		pParent->m_rt.middle.x, pParent->m_rt.middle.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[2]);
	// 3번은 x1,my
	pParent->pChild[3] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.middle.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[3]);
}

// 객체 추가
bool TQuadtree::AddObject(TObject* obj)
{
	TNode* pFindNode = FindNode(m_pRootNode, obj->m_rt);
	if (pFindNode != nullptr)
	{
		pFindNode->AddObject(obj);
		return true;
	}
	return false;
}

TNode* TQuadtree::FindNode(TNode* pNode, int x, int y)
{
	do {
		// iNode가 0부터 시작, iNode가 하나씩 추가되면서 iNode가 4이하일때까지 
		for (int iNode = 0; iNode < 4; iNode++)
		{
			// 자식 배열 안 iNode가 널이면
			if (pNode->pChild[iNode] != nullptr)
			{
				// 자식 배열안 iNode가 사각형 안을 가리키면
				if (TCollision::RectToPoint(
					pNode->pChild[iNode]->m_rt,
					x, y))
				{
					g_Queue.push(pNode->pChild[iNode]);
					break;
				}
			}
		}
		// 큐 empty()는 큐가 비어있으면 true 아니면 false를 반환
		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		g_Queue.pop();
	} while (pNode);
	return pNode;
}

TNode* TQuadtree::FindNode(TNode* pNode, TRect rt)
{
	do {
		for (int iNode = 0; iNode < 4; iNode++)
		{
			if (pNode->pChild[iNode] != nullptr)
			{
				TRect intersect;
				TCollisionType iRet = TCollision::RectToRect(
					pNode->pChild[iNode]->m_rt,
					rt);
				if (iRet == RECT_OVERLAP)
				{
					g_Queue.push(pNode->pChild[iNode]);
					break;
				}
			}
		}
		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		g_Queue.pop();
	} while (pNode);
	return pNode;
}

// 객체리스트 출력
void TQuadtree::PrintObjectList(TNode* pNode)
{
	if (pNode == nullptr) return;
	for (std::list<TObject*>::iterator iter = pNode->m_ObjectList.begin();
		iter != pNode->m_ObjectList.end();
		iter++)
	{
		TObject* pObj = *iter;
		cout << "[" << pNode->m_iDepth << "]" << pObj->m_vPos.x << ":" << pObj->m_vPos.y << " ";
	}
	std::cout << std::endl;
	for (int iNode = 0; iNode < 4; iNode++)
	{
		PrintObjectList(pNode->pChild[iNode]);
	}
}
