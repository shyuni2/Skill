#include "FbxLoader.h"

bool FbxLoader::Load(std::string filename)
{
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);
	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		ParseMesh(m_ObjList[iObj]);
	}
	return true;
}
void FbxLoader::PreProcess(FbxNode* node, FbxNode* parent)
{
	FbxMesh* pMesh = node->GetMesh();
	if (pMesh)
	{
		FbxObj* fbx = new FbxObj;
		fbx->m_pFbxParent = parent;
		fbx->m_pFbxNode = node;
		m_ObjList.push_back(fbx);
	}
	int iNumChild = node->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* child = node->GetChild(iNode);
		PreProcess(child, node);
	}
}
void FbxLoader::ParseMesh(FbxObj* pObject)
{

}
std::string FbxLoader::ParseMaterial(FbxSurfaceMaterial* pMtrl)
{

}

void FbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv)
{

}
FbxColor FbxLoader::ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex)
{

}
FbxVector4 FbxLoader::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{

}

bool FbxLoader::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxScene, "");
	return true;
}
bool FbxLoader::Frame()
{
	return true;
}
bool FbxLoader::Render()
{
	return true;
}
bool FbxLoader::Release()
{
	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		m_ObjList[iObj]->Release();
	}
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
	return true;
}