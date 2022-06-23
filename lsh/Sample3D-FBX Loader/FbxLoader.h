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
	SMatrix m_matLocal; // 로컬행렬
	SMatrix m_matAnim; // 애니메이션 행렬
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	FbxObj* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
public: // 서브 메터리얼
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
* FBX 순서
* 1. SDK 관리자(FbxManager) 객체를 만들어서 시작
* 2. 위 객체를 사용하여 씬(FbxScene) 객체 생성
* 3. 씬 객체를 사용하여 FBX SDK 객체 생성
* 
* Mesh란? 다각형(polygon)으로 만들어진 지오메트리
*/

class FbxLoader
{
public:
	FbxManager* m_pFbxManager; 
	FbxImporter* m_pFbxImporter; // 씬을 가져오는 기능은 FbxImporter에 의해 추상화됨
	FbxScene* m_pFbxScene; 
	FbxNode* m_pRootNode;
	std::vector<FbxObj*> m_DrawList;
	std::vector<FbxObj*> m_TreeList;
public:
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, FbxObj* fbxParent = nullptr); // 모든 노드를 다 돌고나서 메쉬데이터가 있으면 draw해줌
	virtual void ParseMesh(FbxObj* pObject); 
public:
	std::string	ParseMaterial(FbxSurfaceMaterial* pMtrl); 
	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv);
	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);
	int GetSubMaterialIndex(int iPlygon, FbxLayerElementMaterial* pMtrl);
public:
	// MAX 좌표계는 Direct3D의 Y축과 X축의 기저벡터가 다르기 때문에 컨버터를 사용한다
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

