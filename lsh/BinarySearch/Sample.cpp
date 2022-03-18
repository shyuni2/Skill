#include <iostream>

using namespace std;

struct Node
{
	int iDepth;
	int iValue;
	Node* pLeft;
	Node* pRight; // 이진트리를 만들어내는 노드
	Node (int i)
	{
		iValue = i;
		pLeft = nullptr;
		pRight = nullptr;
	}
};
int g_iValue = 0;

void BinaryNode(Node* pNode)
{
	if (pNode->iDepth == 2) return ;
	pNode->pLeft = new Node(++g_iValue);
	pNode->pRight = new Node(++g_iValue); // 자식이니까 뎁스값 추가

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1;

	BinaryNode(pNode->pLeft);
	BinaryNode(pNode->pRight);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth 값 이용해서 탐색하는게 레벨오더 (큐 응용)

void BinaryNodePrintA(Node* pNode) // preorder 90%가 preorder씀
{
	if (pNode == nullptr) return ;
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



void main()
{
	Node* pRoot = new Node(0);
	pRoot->iDepth = 0;
	BinaryNode(pRoot);
	BinaryNodePrintA(pRoot);
	BinaryNodePrintB(pRoot);
	BinaryNodePrintC(pRoot);
}