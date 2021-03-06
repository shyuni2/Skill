#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include "SObj3D.h"
using namespace std;

struct SMapObj
{
	std::wstring name;
	S::SMatrix matWorld; // 월드행렬
	S::SVector3 vPos; // 위치
	SBox box;
	SObj3D* pObject;
	S::SVector3 m_vLight; // ??벡터
	S::SVector3 m_vUp; // 상향벡터 
	S::SVector3 m_vLook; // 시선벡터 
	void UpdateData()
	{
		m_vLight.x = matWorld._11;
		m_vLight.y = matWorld._12;
		m_vLight.z = matWorld._13;
		m_vUp.x = matWorld._21;
		m_vUp.y = matWorld._22;
		m_vUp.z = matWorld._23;
		m_vLook.x = matWorld._31;
		m_vLook.y = matWorld._32;
		m_vLook.z = matWorld._33;

		S::D3DXVec3Normalize(&m_vLight, &m_vLight);
		S::D3DXVec3Normalize(&m_vUp, &m_vUp);
		S::D3DXVec3Normalize(&m_vLook, &m_vLook);
	}
	void UpdateCollision()
	{
		// 박스의 기저축
		box.vAxis[0] = m_vLight;
		box.vAxis[1] = m_vUp;
		box.vAxis[2] = m_vLook;

		// GenAABB();
		box.vMin = S::SVector3(100000, 100000, 100000);
		box.vMax = S::SVector3(-100000, -100000, -100000);
		for (int iV = 0; iV < 8; iV++)
		{
			S::SVector3 pos;
			S::D3DXVec3TransformCoord(&pos, &box.vList[iV], &matWorld);
			if (box.vMin.x > pos.x)
			{
				box.vMin.x = pos.x;
			}
			if (box.vMin.y > pos.y)
			{
				box.vMin.y = pos.y;
			}
			if (box.vMin.z > pos.z)
			{
				box.vMin.z = pos.z;
			}

			if (box.vMax.x < pos.x)
			{
				box.vMax.x = pos.x;
			}
			if (box.vMax.y < pos.y)
			{
				box.vMax.y = pos.y;
			}
			if (box.vMax.z < pos.z)
			{
				box.vMax.z = pos.z;
			}
		}
		S::SVector3 vHalf = box.vMax - box.vCenter;
		box.size.x = fabs(S::D3DXVec3Dot(&box.vAxis[0], &vHalf));
		box.size.y = fabs(S::D3DXVec3Dot(&box.vAxis[1], &vHalf));
		box.size.z = fabs(S::D3DXVec3Dot(&box.vAxis[2], &vHalf));
		box.vCenter = (box.vMin + box.vMax);
		box.vCenter /= 2.0f;
	}
};

class SNode
{
public:
	int m_iIndex;
	SNode* m_pParent;
	SBox m_Box;
	int m_iDepth; // 깊이
	int m_iCurrentLod = 0; // 현재 LOD
	int m_dwLodType; //0 ~ 16
	bool m_bLeaf = false; // 리프노드 
	std::vector<SNode*> m_pChild; // 자식 노드
	std::vector<SNode*> m_pNeighborList; // 이웃노드, 북(0)남(1)서(2)동(3)
	std::vector<int> m_CornerList; // 정점인덱스
	std::list<SMapObj*> m_StaticObjectList; // 정적 오브젝트 리스트
	std::list<SMapObj*> m_DynamicObjectList; // 동적 오브젝트 리스트
	void AddStaticObject(SMapObj* obj); // 정적 오브젝트 추가
	void AddDynamicObject(SMapObj* obj); // 동적 오브젝트 추가
	void DelDynamicObject(SMapObj* obj); // 동적 오브젝트 삭제
public:
	using INDEXLIST = std::vector<DWORD>;// m_IndexList;
	using INDEXBUFFER = Microsoft::WRL::ComPtr<ID3D11Buffer>;// m_pIndexBuffer0;
	std::vector<INDEXLIST> m_IndexList;
	std::vector<INDEXBUFFER> m_pIndexBuffer;	
public:
	SNode();
	SNode(float x, float y, float w, float h);
	~SNode();
};
