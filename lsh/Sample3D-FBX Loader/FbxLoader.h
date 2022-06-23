#pragma once
#include "SObj3D.h"
#include <fbxsdk.h>

struct Track
{
	UINT iFrame;
	SMatrix matTrack;
};

class FbxObj : public SObj3D
{
public:
	SMatrix m_matLocal; // �������
	SMatrix m_matAnim; // �ִϸ��̼� ���
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	FbxObj* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
public: // ���� ���͸���
	std::vector<std::wstring> m_szTexFileList;
	using SubVertex = std::vector<Vertex>;
	std::vector<SubVertex> m_pSubVertexList;
	std::vector<ID3D11Buffer*> m_pVBList;
	std::vector<STexture*> m_pTextureList;
	std::vector<Track> m_AnimTrack;
public:
	virtual bool SetVertexData() override;
	virtual bool CreateVertexBuffer()override;
	virtual bool SetIndexData() override;
	virtual bool PostRender() override;
	virtual bool Release() override;
};

/*
* FBX ����
* 1. SDK ������(FbxManager) ��ü�� ���� ����
* 2. �� ��ü�� ����Ͽ� ��(FbxScene) ��ü ����
* 3. �� ��ü�� ����Ͽ� FBX SDK ��ü ����
* 
* Mesh��? �ٰ���(polygon)���� ������� ������Ʈ��
*/

class FbxLoader
{
public:
	FbxManager* m_pFbxManager; 
	FbxImporter* m_pFbxImporter; // ���� �������� ����� FbxImporter�� ���� �߻�ȭ��
	FbxScene* m_pFbxScene; 
	FbxNode* m_pRootNode;
	std::vector<FbxObj*> m_DrawList;
	std::vector<FbxObj*> m_TreeList;
public:
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, FbxObj* fbxParent = nullptr); // ��� ��带 �� ������ �޽������Ͱ� ������ draw����
	virtual void ParseMesh(FbxObj* pObject); 
public:
	std::string	ParseMaterial(FbxSurfaceMaterial* pMtrl); 
	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv);
	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);
	int GetSubMaterialIndex(int iPlygon, FbxLayerElementMaterial* pMtrl);
public:
	// MAX ��ǥ��� Direct3D�� Y��� X���� �������Ͱ� �ٸ��� ������ �����͸� ����Ѵ�
	SMatrix DxConvertMatrix(SMatrix m);
	SMatrix ConvertMatrix(FbxMatrix& m);
	SMatrix ConvertAMatrix(FbxAMatrix& m);
	void ParseAnimation();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

