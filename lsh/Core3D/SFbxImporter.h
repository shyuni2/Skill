#pragma once
#include "SFbxModel.h"

class SFbxImporter : public SObj3D
{
public:
	Scene m_Scene;
	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
	BoneWorld m_matBoneArray;
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
	std::map<FbxNode*, int>	m_pFbxNodeMap;
	std::map<std::wstring, SFbxModel*> m_pFbxModelMap;
	std::vector<SFbxModel*> m_DrawList;
	std::vector<SFbxModel*> m_TreeList;
	ID3D11Buffer* m_pBoneCB = nullptr;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, SFbxModel* fbxParent = nullptr);
	virtual void ParseMesh(SFbxModel* pObject);
	std::string	ParseMaterial(FbxSurfaceMaterial* pMtrl);
public:
	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv);
	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);
	FbxVector4 ReadNormal(const FbxMesh* mesh, DWORD dwVertexNormalCount, FbxLayerElementNormal* VertexNormalSets, int controlPointIndex, int iVertexIndex);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
	bool ParseMeshSkinning(FbxMesh* pFbxMesh, SFbxModel* pObject);
public:
	// DX와 FBX는 좌표축이 다르기 때문에 변환해줘야함
	SMatrix DxConvertMatrix(SMatrix m);
	SMatrix ConvertMatrix(FbxMatrix& m);
	SMatrix ConvertAMatrix(FbxAMatrix& m);
	void ParseAnimation();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool CreateConstantBuffer(ID3D11Device* pDevice);
};

