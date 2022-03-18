#include "TNode.h"

void TNode::AddObject(TObject* obj) // 객체 추가
{
	// 객체 리스트 푸시백 할때 객체 동적할당
	// list의 push_back은 뒷쪽으로 객체를 삽입
	m_ObjectList.push_back(obj);
}

TNode::TNode() // 생성자
{
	// 생성될때 깊이 0 부모, 자식 모두 NULL
	m_pParent = nullptr;
	m_iDepth = 0;
	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;

	// list의 begin()은 맨 앞의 원소를 가리키는 iterator을 반환
	// list의 end()는 맨 마지막의 다음원소를 가리키는 (맨 마지막을 알 수 있는) iterator을 반환 
	// iter가 맨 앞 원소이고 iter가 객체의 맨 끝이 아닐때까지 iter증가
	for (list<TObject*>::iterator iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
	{
		TObject* pObj = *iter;
		delete pObj;
	}
	m_ObjectList.clear();
}

TNode::TNode(float x, float y, float w, float h) : TNode()
{
	m_rt.vMin.x = x;
	m_rt.vMin.y = y;

	m_rt.vMax.x = x + w; // vMax.x는 x + 가로길이
	m_rt.vMax.y = y + h;

	m_rt.middle.x = x + (w / 2.0f); // 중간 middle.x는 x + (가로길이 / 2)
	m_rt.middle.y = y + (h / 2.0f);

	m_rt.size.x = w; // 가로길이
	m_rt.size.y = h;

	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;
}

TNode::~TNode() // 동적할당 해제
{
	delete pChild[0];
	delete pChild[1];
	delete pChild[2];
	delete pChild[3];
}