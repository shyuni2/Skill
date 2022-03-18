#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int iDepth;
	int iValue;
	Node* pLeft;// ����Ʈ���� ������ ���
	Node* pRight; // ���� ���������� ���ϰ� child[2]�ε� ����
	// Node* pChile[8]; 8��Ʈ��

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
		delete pRight; // �����Ҵ������������
	}
};
// Node* g_pArray[7]; // ������ 7�� �迭�� �Ǿ�����

//Node* g_pArray[7] ;
//Node* g_pArrayLoad[7];

queue<Node*> g_Queue;
int g_iValue = 0;

void BinaryNode(Node* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->pLeft = new Node(++g_iValue);
	// g_pArray[g_iValue] = pNode->pLeft; 
		
	pNode->pRight = new Node(++g_iValue); // �ڽ��̴ϱ� ������ �߰�
	// g_pArray[g_iValue] = pNode->pRight; // Ʈ���� �迭�� �����

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1;

	BinaryNode(pNode->pLeft);
	BinaryNode(pNode->pRight);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth �� �̿��ؼ� Ž���ϴ°� �������� (ť ����)

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

void BinaryNodePrintA(Node* pNode) // preorder 90%�� preorder��
{
	if (pNode == nullptr) return;
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

void BinaryNodePrintLevelOrder(Node* pNode) // ��������
{
	do 
	{
		{
			if (pNode->pLeft != nullptr)
				g_Queue.push(pNode->pLeft);
			if (pNode->pRight != nullptr)
				g_Queue.push(pNode->pRight); // �ϴ� �ڽ����ִٸ� push
		}
		if (g_Queue.empty())break; 
		pNode = g_Queue.front();
		cout << pNode->iValue;

		if (pNode != nullptr) // 
		{
			g_Queue.pop();
		}
		if (g_Queue.empty())break; // front�� ������ break
		pNode = g_Queue.front(); // front : ���� ���� ���� �����°��� �����ϴ°� �ƴ�
	} while (pNode);
}
//             root d=0
//       left d=1       right d=1
//     L d=2      R d=2    L d=2      R d=2    
// depth �� �̿��ؼ� Ž���ϴ°� �������� (ť ����)
// cnt(���� ����) = 2^(depth+1) -1, 

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

	delete pRoot; // �����Ҵ� ����
}