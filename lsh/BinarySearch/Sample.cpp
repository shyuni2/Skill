#include <iostream>

using namespace std;

struct Node
{
	int iDepth;
	int iValue;
	Node* pLeft;
	Node* pRight; // ����Ʈ���� ������ ���
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
	pNode->pRight = new Node(++g_iValue); // �ڽ��̴ϱ� ������ �߰�

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1;

	BinaryNode(pNode->pLeft);
	BinaryNode(pNode->pRight);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth �� �̿��ؼ� Ž���ϴ°� �������� (ť ����)

void BinaryNodePrintA(Node* pNode) // preorder 90%�� preorder��
{
	if (pNode == nullptr) return ;
	cout << pNode->iValue; // ����Ʈ�� �տ� ������?
	BinaryNodePrintA(pNode->pLeft);
	BinaryNodePrintA(pNode->pRight);
}
// ȣ��Ǵ� ����
//                 root(0)
//         left(1)          right(4)
//     L(2)      R(3)     L (5)     R(6) 


void BinaryNodePrintB(Node* pNode) // inorder
{
	if (pNode == nullptr) return;
	BinaryNodePrintB(pNode->pLeft);
	cout << pNode->iValue; // ����Ʈ�� �߰��� ������?
	BinaryNodePrintB(pNode->pRight);
}
// ȣ��Ǵ� ����
//                 root(3)
//         left(1)          right(5)
//     L(0)     R(2)     L (4)     R(6) 


void BinaryNodePrintC(Node* pNode) // postorder
{
	if (pNode == nullptr) return;
	BinaryNodePrintC(pNode->pLeft);
	BinaryNodePrintC(pNode->pRight);
	cout << pNode->iValue; // ����Ʈ�� �ڿ� ������?
}
// ȣ��Ǵ� ����
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