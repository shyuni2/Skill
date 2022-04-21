#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include "SObj3D.h"
using namespace std;

struct MapObj
{
	std::wstring name;
	S::SMatrix matWorld; // �������
	S::SVector3 vPos; // ��ġ
	Box box;
	SObj3D* pObject;
	S::SVector3 m_vLight; // ??����
	S::SVector3 m_vUp; // ���⺤�� 
	S::SVector3 m_vLook; // �ü����� 
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
		// �ڽ��� ������
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
	Box	m_Box;
	int m_iDepth; // ����
	int m_iCurrentLod = 0; // ���� LOD
	int m_dwLodType; //0 ~ 16
	bool m_bLeaf = false; // ������� 
	std::vector<SNode*> m_pChild; // �ڽ� ���
	std::vector<SNode*> m_pNeighborList; // �̿����, ��(0)��(1)��(2)��(3)
	std::vector<int> m_CornerList; // �����ε���
	std::list<MapObj*> m_StaticObjectList; // ���� ������Ʈ ����Ʈ
	std::list<MapObj*> m_DynamicObjectList; // ���� ������Ʈ ����Ʈ
	void AddStaticObject(MapObj* obj); // ���� ������Ʈ �߰�
	void AddDynamicObject(MapObj* obj); // ���� ������Ʈ �߰�
	void DelDynamicObject(MapObj* obj); // ���� ������Ʈ ����
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
