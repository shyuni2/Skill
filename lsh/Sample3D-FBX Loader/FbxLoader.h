#pragma once
#include "Obj3D.h"
#include <fbxsdk.h>

class FbxObj : public Obj3D
{
public:
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	FbxObj* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
public:
	bool SetIndexData() { return true; }
};

class FbxLoader
{
public:
	FbxManager* m_pFbxManager; // FBX SDK ������ ��ü ����
	FbxImporter* m_pFbxImporter; // ���� �������±��
	FbxScene* m_pFbxScene; // �� ��������
	FbxNode* m_pRootNode; // ��Ʈ���
	std::vector<FbxObj*>  m_ObjList;
public:
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, FbxNode* parent); // ��ó��
	virtual void ParseMesh(FbxObj* pObject); 
	std::string ParseMaterial(FbxSurfaceMaterial* pMtrl); 
public:
	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv);
	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

