#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector> // 배열(재할당 가능한)
#include <list>
#include "TObject.h"

using namespace std;

class Node 
{
public:
	Node* m_pParent;
	TRect  m_rt;

	int m_iDepth; // 깊이
	Node* pChild[4]; // 자식노드가 4개
	list<TObject*> m_ObjectList; // 객체를 연결리스트로 만들기위함
	void   AddObject(TObject* obj); // 객체 추가함수

public:
	Node();
	Node(float x, float y, float w, float h);
	~Node();
};
