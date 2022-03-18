#include "TQuadtree.h"

// ��� �����
TNode* TQuadtree::CreateNode(TNode* pParent, float x, float y, float w, float h)
{
	TNode* pNode = new TNode(x, y, w, h);
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}
	return pNode;
}

// Ʈ�� �ʱ�ȭ
void TQuadtree::Init(int iWidth, int iHeight, int iMaxDepth)
{
	m_iMaxDepth = iMaxDepth;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pRootNode = CreateNode(nullptr, 0, 0, m_iWidth, m_iHeight);
	BuildTree(m_pRootNode);
}

// Ʈ�� �����
void TQuadtree::BuildTree(TNode* pParent)
{
	// ���̰� �ִ�����϶� ����
	if (pParent->m_iDepth == m_iMaxDepth) return;
	// 1���� ���ڸ�, 2���� x�� �̵�, 3���� x,y �Ѵ��̵�, 4���� x����ġ y�� �̵� - �簢�� �ð����
	// 0���� x,y
	pParent->pChild[0] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMin.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	// 1���� mx,y
	pParent->pChild[1] = CreateNode(pParent, pParent->m_rt.middle.x, pParent->m_rt.vMin.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[1]);
	// 2���� mx,my
	pParent->pChild[2] = CreateNode(pParent,
		pParent->m_rt.middle.x, pParent->m_rt.middle.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[2]);
	// 3���� x1,my
	pParent->pChild[3] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.middle.y, pParent->m_rt.size.x / 2.0f, pParent->m_rt.size.y / 2.0f);
	BuildTree(pParent->pChild[3]);
}

// ��ü �߰�
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
		// iNode�� 0���� ����, iNode�� �ϳ��� �߰��Ǹ鼭 iNode�� 4�����϶����� 
		for (int iNode = 0; iNode < 4; iNode++)
		{
			// �ڽ� �迭 �� iNode�� ���̸�
			if (pNode->pChild[iNode] != nullptr)
			{
				// �ڽ� �迭�� iNode�� �簢�� ���� ����Ű��
				if (TCollision::RectToPoint(
					pNode->pChild[iNode]->m_rt,
					x, y))
				{
					g_Queue.push(pNode->pChild[iNode]);
					break;
				}
			}
		}
		// ť empty()�� ť�� ��������� true �ƴϸ� false�� ��ȯ
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

// ��ü����Ʈ ���
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
