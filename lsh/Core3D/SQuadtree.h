#pragma once
#include "SNode.h"
#include "SMap.h"
#include "SCamera.h"

// ��Ʈ��� : �θ� ���� ���
// ������� : �ڽ��� ���� ���

class SQuadtree
{
public:
	SMap* m_pMap=nullptr;
	SCamera* m_pCamera = nullptr;
	int m_iWidth;
	int m_iHeight;
	SNode* m_pRootNode; // ��Ʈ���
	int m_iLeafDepth = 0; // ��������� ����
	int m_iMaxDepth = 0; // �ִ� ����
	int m_iNumLOD = 1; // LOD ����
	int m_iLeafLOD = 1; // ������� LOD
	static int g_iCount;
public:
	std::list<SMapObj*> m_ObjList;
	std::vector<SNode*> g_pDrawLeafNodes;
	std::vector<SNode*> g_pLeafNodes;
	std::queue<SNode*> g_Queue;	
	std::vector<DWORD> m_IndexList;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
	int m_iNumFace; // ���̽� ����
	int g_iValue = 0;
public:
	void Build(int iWidth, int iHeight, int iMaxDepth);
	SNode* CreateNode(SNode* pParent, float x, float y, float w, float h); // ��� ����
public:
	void Build(SMap* pMap, int iMaxDepth);
	void BuildTree(SNode* pParent); // Ʈ�� ����
	SBox GenBoundingBox(SNode* pNode);
	SVector2 GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	bool AddStaticObject(SMapObj* obj);
	bool AddDynamicObject(SMapObj* obj);
	void DynamicDeleteObject(SNode* pNode);
	SNode* FindNode(SNode* pNode, SBox& box);
	bool CheckBox(SBox& a, SBox& b);
public:
	void SetIndexData(SNode* pNode, int iLodLevel);
	bool CreateIndexBuffer(SNode* pNode, int iLodLevel);
	void Update(SCamera* pCamera);
	bool PreRender();
	bool Render();
	bool PostRender();
	void RenderObject(SNode* pNode);
	void RenderTile(SNode* pNode);
public:
	void FindNeighborNode(); // �̿���� ã��
	SNode* CheckBoxtoPoint(S::SVector3 p);
	void GetRatio(SNode* pNode);
	int GetLodType(SNode* pNode);
	int UpdateIndexList(SNode* pNode, DWORD dwCurentIndex, DWORD dwNumLevel);
	int SetLodIndexBuffer(SNode* pNode, DWORD& dwCurentIndex, DWORD dwA, DWORD dwB, DWORD dwC, DWORD dwType);
#ifdef _DEBUG // ����� ����϶� ����
public:
	SBoxObj m_BoxDebug;
	void DrawDebugInit(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	void DrawDebugRender(SBox* pBox);
#endif
public:
	void PrintObjectList(SNode* pNode);
public:
	SQuadtree() {};
	virtual ~SQuadtree()
	{
		m_BoxDebug.Release();
		delete m_pRootNode;
	}
};
