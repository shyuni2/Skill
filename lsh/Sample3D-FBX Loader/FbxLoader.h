#pragma once
#include "Obj3D.h"
#include <fbxsdk.h>

struct Track
{
	UINT iFrame;
	TMatrix matTrack;
};

class FbxObj : public Obj3D
{
public:
	TMatrix m_matLocal;
	TMatrix m_matAnim;
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	FbxObj* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
public: // submaterial
	std::vector<std::wstring> m_szTexFileList;
	using TSubVertex = std::vector<Vertex>;
	std::vector<TSubVertex> m_pSubVertexList;
	std::vector<ID3D11Buffer*> m_pVBList;
	std::vector<Texture*> m_pTextureList;
	std::vector<Track> m_AnimTrack;
public:
	virtual bool SetVertexData() override;
	virtual bool CreateVertexBuffer()override;
	virtual bool SetIndexData() override;
	virtual bool PostRender() override;
	virtual bool Release() override;
};

class FbxLoader
{
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
	std::vector<FbxObj*>  m_DrawList;
	std::vector<FbxObj*>  m_TreeList;
public:
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, FbxObj* fbxParent = nullptr);
	virtual void ParseMesh(FbxObj* pObject);
	std::string	ParseMaterial(FbxSurfaceMaterial* pMtrl);

	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv);

	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);

	int GetSubMaterialIndex(int iPlygon, FbxLayerElementMaterial* pMtrl);
public:
	TMatrix DxConvertMatrix(TMatrix m);
	TMatrix ConvertMatrix(FbxMatrix& m);
	TMatrix ConvertAMatrix(FbxAMatrix& m);
	void ParseAnimation();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

