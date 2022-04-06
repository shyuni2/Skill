#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector> // �迭(���Ҵ� ������)
#include <list>
#include "TObject.h"

using namespace std;

class Node 
{
public:
	Node* m_pParent;
	TRect  m_rt;

	int m_iDepth; // ����
	Node* pChild[4]; // �ڽĳ�尡 4��
	list<TObject*> m_ObjectList; // ��ü�� ���Ḯ��Ʈ�� ���������
	void   AddObject(TObject* obj); // ��ü �߰��Լ�

public:
	Node();
	Node(float x, float y, float w, float h);
	~Node();
};
