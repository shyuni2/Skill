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
	FbxManager* m_pFbxManager; // FBX SDK 관리자 객체 생성
	FbxImporter* m_pFbxImporter; // 씬을 가져오는기능
	FbxScene* m_pFbxScene; // 씬 가져오기
	FbxNode* m_pRootNode; // 루트노드
	std::vector<FbxObj*>  m_ObjList;
public:
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, FbxNode* parent); // 전처리
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

