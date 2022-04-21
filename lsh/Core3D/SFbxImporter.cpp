#define _CRT_SECURE_NO_WARNINGS
#include "SFbxImporter.h"

bool SFbxImporter::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	if (Load(to_wm(filename).c_str()))
	{
		CreateConstantBuffer(pd3dDevice);
		SShader* pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"", "VS");
		SShader* pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"", "PS");
		for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
		{
			m_DrawList[iObj]->Init();
			m_DrawList[iObj]->m_pVShader = pVShader;
			m_DrawList[iObj]->m_pPShader = pPShader;
			if (!m_DrawList[iObj]->Create(pd3dDevice, m_pContext))
			{
				return false;
			}
		}
	}
	return true;
}
bool SFbxImporter::Load(std::string filename)
{
	Init();
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);
	ParseAnimation();
	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		ParseMesh(m_DrawList[iObj]);
	}
	Release();
	return true;
}
void SFbxImporter::PreProcess(FbxNode* node, SFbxModel* fbxParent) //���� �۾��ϱ����� ��ü�� ��� �۾��Ǵ��� Ȯ���ϴ� �Լ�
{
	SFbxModel* fbx = nullptr;
	if (node != nullptr)
	{
		fbx = new SFbxModel;
		fbx->m_pFbxParent = node->GetParent();
		fbx->m_pFbxNode = node;
		fbx->m_csName = to_mw(node->GetName());
		fbx->m_pParentObj = fbxParent;
		fbx->m_iIndex = m_TreeList.size();
		m_TreeList.push_back(fbx);
		m_pFbxNodeMap.insert(std::make_pair(node, fbx->m_iIndex));
		m_pFbxModelMap.insert(std::make_pair(fbx->m_csName, fbx));
	}
	// camera, light, mesh, shape, animation
	FbxMesh* pMesh = node->GetMesh();
	if (pMesh)
	{
		m_DrawList.push_back(fbx); // �Ž��� �ѱ�
	}
	int iNumChild = node->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* child = node->GetChild(iNode);
		PreProcess(child, fbx);
	}
}
void SFbxImporter::ParseMesh(SFbxModel* pObject) 
{
	FbxMesh* pFbxMesh = pObject->m_pFbxNode->GetMesh();

	pObject->m_bSkinned = ParseMeshSkinning(pFbxMesh, pObject);
	// �������(�ʱ� ������Ʈ�� ��ġ�Ҷ� ���) 
	// ������ ��� : ���� ��ġ�� �Ǿ��ִ� ��Ŀ��ٰ� �߰����� ����� �����Ѵ�
	FbxAMatrix geom;
	FbxVector4 trans = pObject->m_pFbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot = pObject->m_pFbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pObject->m_pFbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
	
	geom.SetT(trans);
	geom.SetR(rot);
	geom.SetS(scale);

	FbxAMatrix normalMatrix = geom;
	normalMatrix = normalMatrix.Inverse();
	normalMatrix = normalMatrix.Transpose();

	// ���̾� ( 1���� ������, �������� ���ļ� ������ ����)
	std::vector<FbxLayerElementUV*> VertexUVSet;
	std::vector<FbxLayerElementVertexColor*> VertexColorSet;
	std::vector<FbxLayerElementMaterial*> MaterialSet;
	std::vector<FbxLayerElementNormal*>		VertexNormalSets;
	int iLayerCount = pFbxMesh->GetLayerCount();

	// �븻������?�� ����ϴ��Ŀ� ���� �����븻�� �޶����� ���� ���ʿ�� x 
	if (iLayerCount == 0 || pFbxMesh->GetLayer(0)->GetNormals() == nullptr)
	{
		pFbxMesh->InitNormals();
#if (FBXSDK_VERSION_MAJOR >= 2015)
		pFbxMesh->GenerateNormals();
#else
		pFbxMesh->ComputeVertexNormals();
#endif
	}

	for (int iLayer = 0; iLayer < iLayerCount; iLayer++)
	{
		FbxLayer* pFbxLayer = pFbxMesh->GetLayer(iLayer);
		if (pFbxLayer->GetUVs() != nullptr)
		{
			VertexUVSet.push_back(pFbxLayer->GetUVs());
		}
		if (pFbxLayer->GetVertexColors() != nullptr)
		{
			VertexColorSet.push_back(pFbxLayer->GetVertexColors());
		}
		if (pFbxLayer->GetNormals() != NULL)
		{
			VertexNormalSets.push_back(pFbxLayer->GetNormals());
		}
		if (pFbxLayer->GetMaterials() != nullptr)
		{
			MaterialSet.push_back(pFbxLayer->GetMaterials());
		}
	}

	//  1���� ������Ʈ�� �������� �ؽ�ó�� ����Ѵ�.
	//  ������ �ؽ�ó�� �̸��� ��� �����Ѵ�.
	//  � ���̽�(������)�� � �ؽ�ó�� ����ϴ�?
	//  ���� �ؽ�ó�� ����ϴ� ������� ���� �����Ѵ�.
	int iNumMtrl = pObject->m_pFbxNode->GetMaterialCount();
	for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
	{
		FbxSurfaceMaterial* pSurface = pObject->m_pFbxNode->GetMaterial(iMtrl);
		if (pSurface)
		{
			std::string texturename = ParseMaterial(pSurface);
			std::wstring szTexFileName = L"../../data/fbx/";
			szTexFileName += to_mw(texturename);
			pObject->m_szTexFileList.push_back(szTexFileName);
			pObject->m_pTextureList.push_back(I_Texture.Load(pObject->m_szTexFileList[iMtrl]));
		}
	}
	if (pObject->m_szTexFileList.size() > 0)
	{
		pObject->m_szTexFileName = pObject->m_szTexFileList[0];
	}
	if (iNumMtrl > 0)
	{
		pObject->m_pSubVertexList.resize(iNumMtrl);
		pObject->m_pSubIWVertexList.resize(iNumMtrl);
	}
	else
	{
		pObject->m_pSubVertexList.resize(1);
		pObject->m_pSubIWVertexList.resize(1);
	}

	int iBasePolyIndex = 0;
	// �ﰢ��, �簢��
	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	int iNumFace = 0;
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;

		int iSubMtrl = 0;
		if (iNumMtrl >= 1 && MaterialSet[0] != nullptr)
		{
			iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet[0]);
		}
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			// 1  2
			// 0  3
			// (max)021,032 ->  (dx)012, 023
			int VertexIndex[3] = { 0, iFace + 2, iFace + 1 };

			int CornerIndex[3];
			CornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			CornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
			CornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);

			// uv
			int u[3];
			u[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
			u[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
			u[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int DCCIndex = CornerIndex[iIndex];
				Vertex tVertex;
				// Max(x,z,y) ->(dx)x,y,z    		
				auto v = geom.MultT(pVertexPositions[DCCIndex]);
				tVertex.p.x = v.mData[0];
				tVertex.p.y = v.mData[2];
				tVertex.p.z = v.mData[1];


				if (VertexUVSet.size() > 0)
				{
					FbxLayerElementUV* pUVSet = VertexUVSet[0];
					FbxVector2 uv;
					ReadTextureCoord(pFbxMesh, pUVSet, DCCIndex, u[iIndex], uv);
					tVertex.t.x = uv.mData[0];
					tVertex.t.y = 1.0f - uv.mData[1];
				}

				FbxColor color = FbxColor(1, 1, 1, 1);
				if (VertexColorSet.size() > 0)
				{
					color = ReadColor(pFbxMesh, VertexColorSet.size(), VertexColorSet[0], DCCIndex, iBasePolyIndex + VertexIndex[iIndex]);
				}
				tVertex.c.x = color.mRed;
				tVertex.c.y = color.mGreen;
				tVertex.c.z = color.mBlue;
				tVertex.c.w = pObject->m_iIndex;

				if (VertexNormalSets.size() <= 0)
				{
					FbxVector4 normal = ReadNormal(pFbxMesh, DCCIndex, iBasePolyIndex + VertexIndex[iIndex]);
					normal = normalMatrix.MultT(normal);
					normal.Normalize();
					tVertex.n.x = normal.mData[0]; // x
					tVertex.n.y = normal.mData[2]; // z
					tVertex.n.z = normal.mData[1]; // y		
					D3DXVec3Normalize(&tVertex.n, &tVertex.n);
				}
				else
				{
					// Store vertex normal
					FbxVector4 finalNorm = ReadNormal(pFbxMesh, VertexNormalSets.size(), VertexNormalSets[0], DCCIndex, iBasePolyIndex + VertexIndex[iIndex]);
					finalNorm.mData[3] = 0.0; // �븻�� w�� 0���� ����
					finalNorm = normalMatrix.MultT(finalNorm);
					finalNorm.Normalize();
					tVertex.n.x = finalNorm.mData[0];
					tVertex.n.y = finalNorm.mData[2];
					tVertex.n.z = finalNorm.mData[1];
					D3DXVec3Normalize(&tVertex.n, &tVertex.n);
				}


				// ����ġ
				VertexIW iwVertex;
				if (pObject->m_bSkinned)
				{
					// ��Ű��
					Weight* weight = &pObject->m_WeightList[DCCIndex];
					for (int i = 0; i < 4; i++)
					{
						iwVertex.i[i] = weight->vIndex[i];
						iwVertex.w[i] = weight->vWeight[i];
					}
				}
				else // ������Ʈ�� ĳ���ʹ� ������ �۾��� �ϱ�����
				{
					// �Ϲݿ�����Ʈ ���ϸ��̼��� ��Ű�� �ɸ��� ȭ �۾�.
					iwVertex.i[0] = pObject->m_iIndex;
					iwVertex.w[0] = 1.0f;
				}
				// ���۰� �� �ΰ�? ���������� pnct/iw�� �������ֱ⶧����
				pObject->m_pSubVertexList[iSubMtrl].push_back(tVertex);
				pObject->m_pSubIWVertexList[iSubMtrl].push_back(iwVertex);
			}
		}
		iBasePolyIndex += iPolySize;
	}
}
std::string	SFbxImporter::ParseMaterial(FbxSurfaceMaterial * pMtrl)
{
	std::string name = pMtrl->GetName();
	auto Property = pMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);
	if (Property.IsValid())
	{
		const FbxFileTexture* tex = Property.GetSrcObject<FbxFileTexture>(0);
		if (tex != nullptr)
		{
			const CHAR* szFileName = tex->GetFileName();
			CHAR Drive[MAX_PATH];
			CHAR Dir[MAX_PATH];
			CHAR FName[MAX_PATH];
			CHAR Ext[MAX_PATH];
			_splitpath(szFileName, Drive, Dir, FName, Ext);
			std::string texName = FName;
			std::string ext = Ext;
			if (ext == ".tga" || ext == ".TGA")
			{
				ext.clear();
				ext = ".dds";
			}
			texName += ext;
			return texName;
		}
	}
	return std::string("");
}

void SFbxImporter::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex, FbxVector2& uv)
{
	FbxLayerElementUV* pFbxLayerElementUV = pUVSet;
	if (pFbxLayerElementUV == nullptr) { return; }

	switch (pFbxLayerElementUV->GetMappingMode())
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (pFbxLayerElementUV->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			FbxVector2 fbxUv = pFbxLayerElementUV->GetDirectArray().GetAt(vertexIndex);
			uv.mData[0] = fbxUv.mData[0];
			uv.mData[1] = fbxUv.mData[1];
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int id = pFbxLayerElementUV->GetIndexArray().GetAt(vertexIndex);
			FbxVector2 fbxUv = pFbxLayerElementUV->GetDirectArray().GetAt(id);
			uv.mData[0] = fbxUv.mData[0];
			uv.mData[1] = fbxUv.mData[1];
			break;
		}
		}
		break;
	}
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (pFbxLayerElementUV->GetReferenceMode())
		{
			// Always enters this part for the example model
		case FbxLayerElementUV::eDirect: // fbx 5.0 ������ ��
		case FbxLayerElementUV::eIndexToDirect:
		{
			uv.mData[0] = pFbxLayerElementUV->GetDirectArray().GetAt(uvIndex).mData[0];
			uv.mData[1] = pFbxLayerElementUV->GetDirectArray().GetAt(uvIndex).mData[1];
			break;
		}
		}
		break;
	}
	}

}
FbxColor SFbxImporter::ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex)
{
	FbxColor Value(1, 1, 1, 1);
	if (dwVertexColorCount > 0 && pVertexColorSet != NULL)
	{
		// Crack apart the FBX dereferencing system for Color coordinates		
		switch (pVertexColorSet->GetMappingMode())
		{
		case FbxLayerElement::eByControlPoint:
			switch (pVertexColorSet->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				Value = pVertexColorSet->GetDirectArray().GetAt(dwDCCIndex);
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				int iColorIndex = pVertexColorSet->GetIndexArray().GetAt(dwDCCIndex);
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			}
		case FbxLayerElement::eByPolygonVertex:
			switch (pVertexColorSet->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				int iColorIndex = dwVertexIndex;
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				int iColorIndex = pVertexColorSet->GetIndexArray().GetAt(dwVertexIndex);
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			}
			break;
		}
	}
	return Value;
}
FbxVector4 SFbxImporter::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	if (mesh->GetElementNormalCount() < 1) {}

	const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
	// �븻 ȹ�� 
	FbxVector4 result;
	// �븻 ���͸� ������ ���� 
	switch (vertexNormal->GetMappingMode()) 	// ���� ��� 
	{
		// ������ ���� 1���� ���� ��ǥ�� �ִ�.
	case FbxGeometryElement::eByControlPoint:
	{
		// control point mapping 
		switch (vertexNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result[0] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
			result[1] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
			result[2] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
		} break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex);
			// �ε����� ���´�. 
			result[0] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
			result[1] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
			result[2] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}break;
	}break;
	// ���� ���� 1���� ���� ��ǥ�� �ִ�.
	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (vertexNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result[0] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
			result[1] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
			result[2] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = vertexNormal->GetIndexArray().GetAt(vertexCounter);
			// �ε����� ���´�. 
			result[0] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
			result[1] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
			result[2] = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}
	}break;
	}
	return result;
}
FbxVector4 SFbxImporter::ReadNormal(const FbxMesh* mesh, DWORD dwVertexNormalCount, FbxLayerElementNormal* VertexNormalSets, int controlPointIndex, int iVertexIndex)
{
	FbxVector4 result(0, 0, 0);
	if (dwVertexNormalCount < 1)
	{
		return result;
	}
	int iVertexNormalLayer = mesh->GetElementNormalCount();

	const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
	// �븻 ȹ�� 

	// �븻 ���͸� ������ ���� 
	switch (VertexNormalSets->GetMappingMode()) 	// ���� ��� 
	{
		// ������ ���� 1���� ���� ��ǥ�� �ִ�.
	case FbxGeometryElement::eByControlPoint:
	{
		// control point mapping 
		switch (VertexNormalSets->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result[0] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(controlPointIndex).mData[0]);
			result[1] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(controlPointIndex).mData[1]);
			result[2] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(controlPointIndex).mData[2]);
		} break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = VertexNormalSets->GetIndexArray().GetAt(controlPointIndex);
			// �ε����� ���´�. 
			result[0] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[0]);
			result[1] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[1]);
			result[2] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}break;
	}break;
	// ���� ���� 1���� ���� ��ǥ�� �ִ�.
	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (vertexNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result[0] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(iVertexIndex).mData[0]);
			result[1] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(iVertexIndex).mData[1]);
			result[2] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(iVertexIndex).mData[2]);
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = VertexNormalSets->GetIndexArray().GetAt(iVertexIndex);
			// �ε����� ���´�. 
			result[0] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[0]);
			result[1] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[1]);
			result[2] = static_cast<float>(VertexNormalSets->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}
	}break;
	}
	return result;
}
int SFbxImporter::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
{
	// ���ι��
	//eNone,
	//eByControlPoint,  // ������
	//eByPolygonVertex, //  
	//eByPolygon, // �����︶�� �ٸ��� �ִ�.
	//eAllSame - ��üǥ�鿡 1���� ������ǥ�� �ִ�.
	int iSubMtrl = 0;
	if (pMaterialSetList != nullptr)
	{
		switch (pMaterialSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			// ���� ������ �迭�� ����Ǵ� ���
			switch (pMaterialSetList->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = iPoly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;
}
bool SFbxImporter::ParseMeshSkinning(FbxMesh* pFbxMesh, SFbxModel* pObject)
{
	int iDeformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (iDeformerCount == 0)
	{
		return false;
	}
	// ������ ������ �����Ѵ�.
	int iVertexCount = pFbxMesh->GetControlPointsCount();
	pObject->m_WeightList.resize(iVertexCount);

	for (int dwDeformerIndex = 0; dwDeformerIndex < iDeformerCount; dwDeformerIndex++)
	{
		auto pSkin = reinterpret_cast<FbxSkin*>(pFbxMesh->GetDeformer(dwDeformerIndex, FbxDeformer::eSkin));
		DWORD dwClusterCount = pSkin->GetClusterCount();
		// dwClusterCount�� ����� ��ü ������ ������ �־���.
		for (int dwClusterIndex = 0; dwClusterIndex < dwClusterCount; dwClusterIndex++)
		{
			auto pCluster = pSkin->GetCluster(dwClusterIndex);
			////
			FbxAMatrix matXBindPose;
			FbxAMatrix matReferenceGlobalInitPosition;
			pCluster->GetTransformLinkMatrix(matXBindPose);
			pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
			FbxMatrix matBindPose = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

			SMatrix matInvBindPos = DxConvertMatrix(ConvertMatrix(matBindPose));
			matInvBindPos = matInvBindPos.Invert();
			int  iBoneIndex = m_pFbxNodeMap.find(pCluster->GetLink())->second;
			std::wstring name = m_TreeList[iBoneIndex]->m_csName;
			pObject->m_dxMatrixBindPoseMap.insert(make_pair(name, matInvBindPos));

			int  dwClusterSize = pCluster->GetControlPointIndicesCount();
			// ������ �޴� �������� �ε���
			int* pIndices = pCluster->GetControlPointIndices();
			double* pWeights = pCluster->GetControlPointWeights();
			// iBoneIndex�� ������ �޴� �������� dwClusterSize�� �ִ�.
			for (int i = 0; i < dwClusterSize; i++)
			{
				// n�� ����(pIndices[i])�� iBoneIndex�� ��Ŀ� 
				// pWeights[i]�� ����ġ�� ����Ǿ���.
				int iVertexIndex = pIndices[i];
				float fWeight = pWeights[i];
				pObject->m_WeightList[iVertexIndex].InsertWeight(iBoneIndex, fWeight);
			}
		}
	}
	return true;
}

SMatrix SFbxImporter::DxConvertMatrix(SMatrix m)
{
	SMatrix mat;
	mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
	mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
	mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
	mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
	return mat;
}
SMatrix SFbxImporter::ConvertMatrix(FbxMatrix& m)
{
	SMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);
	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}
SMatrix SFbxImporter::ConvertAMatrix(FbxAMatrix& m) // �Ϲ������� ���ɸ�Ʈ������ ����Ѵ�? ���Ͱ������� ����� ����Ѵ�
{
	SMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);
	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}
void SFbxImporter::ParseAnimation()
{
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
	FbxAnimStack* stack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	if (stack == nullptr) return;

	FbxString TakeName = stack->GetName();
	FbxTakeInfo* TakeInfo = m_pFbxScene->GetTakeInfo(TakeName);
	FbxTimeSpan LocalTimeSpan = TakeInfo->mLocalTimeSpan;
	FbxTime start = LocalTimeSpan.GetStart();
	FbxTime end = LocalTimeSpan.GetStop();
	FbxTime Duration = LocalTimeSpan.GetDuration();

	FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
	FbxLongLong s = start.GetFrameCount(TimeMode);
	FbxLongLong n = end.GetFrameCount(TimeMode);
	m_Scene.iStart = s;
	m_Scene.iEnd = n;
	m_Scene.iFrameSpeed = 30;
	// 1�ʿ� 30 frame 
	// 1Frame = 160 Tick
	// 50 Frame 
	FbxTime time;
	Track tTrack;
	for (FbxLongLong t = s; t <= n; t++)
	{
		time.SetFrame(t, TimeMode);
		for (int iObj = 0; iObj < m_TreeList.size(); iObj++)
		{
			FbxAMatrix matGlobal = m_TreeList[iObj]->m_pFbxNode->EvaluateGlobalTransform(time);
			tTrack.iFrame = t;
			tTrack.matTrack = DxConvertMatrix(ConvertAMatrix(matGlobal));
			// ��ĺ���
			// ����� ����(SRT)
			S::D3DXMatrixDecompose(&tTrack.s, &tTrack.r, &tTrack.t, &tTrack.matTrack);
			m_TreeList[iObj]->m_AnimTrack.push_back(tTrack);
		}
	}
}

bool SFbxImporter::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

	FbxAxisSystem	 m_SceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	m_SceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();

	FbxSystemUnit	m_SceneSystemUnit = m_pFbxScene->GetGlobalSettings().GetSystemUnit();
	if (m_SceneSystemUnit.GetScaleFactor() != 1.0f)
	{
		FbxSystemUnit::cm.ConvertScene(m_pFbxScene);
	}
	return true;
}
bool SFbxImporter::Frame()
{
	return true;
}
bool SFbxImporter::Render()
{
	return true;
}
bool SFbxImporter::Release()
{
	if (m_pBoneCB) { m_pBoneCB->Release(); }
	m_pBoneCB = nullptr;
	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		m_DrawList[iObj]->Release();
	}
	if (m_pFbxScene) { m_pFbxScene->Destroy(); }
	if (m_pFbxImporter) { m_pFbxImporter->Destroy(); }
	if (m_pFbxManager) { m_pFbxManager->Destroy(); }
	m_pFbxScene = nullptr;
	m_pFbxImporter = nullptr;
	m_pFbxManager = nullptr;
	return true;
}
bool SFbxImporter::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	//gpu�޸𸮿� ���� �Ҵ�(���ϴ� �Ҵ� ũ��)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(BoneWorld);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(hr = pDevice->CreateBuffer(&bd, NULL, &m_pBoneCB))) { return false; }
	return true;
}