#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int iDepth;
	int iValue;
	Node* pLeft;// 이진트리를 만들어내는 노드
	Node* pRight; // 왼쪽 오른쪽으로 안하고 child[2]로도 가능
	// Node* pChile[8]; 8진트리

	Node()
	{
		iValue = -1;
		pLeft = nullptr;
		pRight = nullptr;
	}
	Node(int i)
	{
		iValue = i;
		pLeft = nullptr;
		pRight = nullptr;
	}
	~Node()
	{
		delete pLeft;
		delete pRight; // 동적할당해제해줘야함
	}
};
// Node* g_pArray[7]; // 뎁스가 7개 배열로 되어있음

//Node* g_pArray[7] ;
//Node* g_pArrayLoad[7];

queue<Node*> g_Queue;
int g_iValue = 0;

void BinaryNode(Node* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->pLeft = new Node(++g_iValue);
	// g_pArray[g_iValue] = pNode->pLeft; 
		
	pNode->pRight = new Node(++g_iValue); // 자식이니까 뎁스값 추가
	// g_pArray[g_iValue] = pNode->pRight; // 트리가 배열에 저장됨

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1;

	BinaryNode(pNode->pLeft);
	BinaryNode(pNode->pRight);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth 값 이용해서 탐색하는게 레벨오더 (큐 응용)

//void BinaryNodeLoad(Node* pNode)
//{
//	// node = left(2k+1)
//	// node = left(2(k+1))
//	// parent = (k-1)/2
//	int iLeft = 2 * pNode->iValue + 1;
//	int iRight = 2 * (pNode->iValue + 1);
//	int iParent = (pNode->iValue - 1) / 2;
//
//	pNode->pLeft = g_pArrayLoad[iLeft];
//	pNode->pRight = g_pArrayLoad[iRight];
//
//	BinaryNodeLoad(pNode->pLeft);
//	BinaryNodeLoad(pNode->pRight);
//
//}

void BinaryNodePrintA(Node* pNode) // preorder 90%가 preorder씀
{
	if (pNode == nullptr) return;
	cout << pNode->iValue; // 프린트를 앞에 넣으면?
	BinaryNodePrintA(pNode->pLeft);
	BinaryNodePrintA(pNode->pRight);
}
// 호출되는 순서
//                 root(0)
//         left(1)          right(4)
//     L(2)      R(3)     L (5)     R(6) 


void BinaryNodePrintB(Node* pNode) // inorder
{
	if (pNode == nullptr) return;
	BinaryNodePrintB(pNode->pLeft);
	cout << pNode->iValue; // 프린트를 중간에 넣으면?
	BinaryNodePrintB(pNode->pRight);
}
// 호출되는 순서
//                 root(3)
//         left(1)          right(5)
//     L(0)     R(2)     L (4)     R(6) 


void BinaryNodePrintC(Node* pNode) // postorder
{
	if (pNode == nullptr) return;
	BinaryNodePrintC(pNode->pLeft);
	BinaryNodePrintC(pNode->pRight);
	cout << pNode->iValue; // 프린트를 뒤에 넣으면?
}
// 호출되는 순서
//                 root(6)
//         left(2)          right(5)
//     L(0)      R(1)     L (3)     R(4) 

void BinaryNodePrintLevelOrder(Node* pNode) // 레벨오더
{
	do 
	{
		{
			if (pNode->pLeft != nullptr)
				g_Queue.push(pNode->pLeft);
			if (pNode->pRight != nullptr)
				g_Queue.push(pNode->pRight); // 일단 자식이있다면 push
		}
		if (g_Queue.empty())break; 
		pNode = g_Queue.front();
		cout << pNode->iValue;

		if (pNode != nullptr) // 
		{
			g_Queue.pop();
		}
		if (g_Queue.empty())break; // front가 없으면 break
		pNode = g_Queue.front(); // front : 제일 먼저 들어간거 빼내는거지 삭제하는게 아님
	} while (pNode);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth 값 이용해서 탐색하는게 레벨오더 (큐 응용)
// cnt(뎁스 개수) = 2^(depth+1) -1, 

void main()
{

	Node* pRoot = new Node(0);
	// g_pArray[0] = pRoot;
	pRoot->iDepth = 0;
	BinaryNode(pRoot);

	/*for (int iNode = 0; iNode < 7; iNode++)
	{
		g_pArray[iNode] = g_pArray[0];
	}
	Node* pRootCopy = g_pArray[0];
	BinaryNodeLoad(pRootCopy);*/

	BinaryNodePrintA(pRoot);
	BinaryNodePrintB(pRoot);
	BinaryNodePrintC(pRoot);

	g_Queue.push(pRoot); 
	BinaryNodePrintLevelOrder(pRoot);

	delete pRoot; // 동적할당 해제
}