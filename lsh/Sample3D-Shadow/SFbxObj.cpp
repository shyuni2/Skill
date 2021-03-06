#define  _CRT_SECURE_NO_WARNINGS
#include "SFbxObj.h"
bool	SFbx::Init()
{	
	m_fTime = 61;
	return true;
}
bool	SFbx::Frame()
{
	/*m_fTime += g_fSecPerFrame * m_pMeshImp->m_Scene.iFrameSpeed * m_fDir * m_fSpeed;
	if (m_fTime >= m_pMeshImp->m_Scene.iEnd)
	{
		m_fDir *= -1.0f;
	}
	if (m_fTime <= m_pMeshImp->m_Scene.iStart)
	{
		m_fDir *= -1.0f;
	}
	int iFrame = m_fTime;
	iFrame = max(0, min(m_pMeshImp->m_Scene.iEnd, iFrame));*/
	/*for (int iObj = 0; iObj < m_pMeshImp->m_TreeList.size(); iObj++)
	{
		SFbxModel* pObject = m_pMeshImp->m_TreeList[iObj];
		if (pObject->m_AnimTrack.size() > 0)
		{
			auto binepose = pObject->m_matBindPoseMap.find(pObject->m_iIndex);
			if (binepose != pObject->m_matBindPoseMap.end())
			{
				SMatrix matInverseBindpose = binepose->second;
				m_matBoneArray.matBoneWorld[iObj] =
					matInverseBindpose *
					pObject->m_AnimTrack[iFrame].matTrack;
			}
			else
			{
				m_matBoneArray.matBoneWorld[iObj] =					
					pObject->m_AnimTrack[iFrame].matTrack;
			}
		}
		S::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[iObj],&m_matBoneArray.matBoneWorld[iObj]);
	}	*/
	return true;
}
S::SMatrix SFbx::Interplate(SFbxImporter* pAnimImp, SFbxModel* pModel, float fTime)
{
	S::SMatrix matAnim;
	Scene tScene = pAnimImp->m_Scene;
	int iStart = max(tScene.iStart, fTime);
	int iEnd = min(tScene.iEnd, fTime + 1);
	// ???? = A ~ 7.5f ~ B
	//       9.5f <=10   ~     20 -> 20.1
	Track A = pModel->m_AnimTrack[iStart];
	Track B = pModel->m_AnimTrack[iEnd];
	float s = fTime- (float)iStart; // 0~1
	S::SVector3 pos;
	S::D3DXVec3Lerp(&pos, &A.t, &B.t, s);
	S::SVector3 scale;
	S::D3DXVec3Lerp(&scale, &A.s, &B.s, s);
	S::SQuaternion rotation;
	S::D3DXQuaternionSlerp(&rotation, &A.r, &B.r, s);
	S::SMatrix matScale;
	S::D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	S::SMatrix matRotation;
	S::D3DXMatrixRotationQuaternion(&matRotation, &rotation);
	
	matAnim = matScale * matRotation;
	matAnim._41 = pos.x;
	matAnim._42 = pos.y;
	matAnim._43 = pos.z;
	//S::SMatrix matTrans;
	//S::D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);
	//matAnim = pModel->m_AnimTrack[(int)fTime].matTrack;
	return matAnim;
}
bool	SFbx::Render()
{		
	SFbxImporter* pAnimImp = nullptr;
	if (m_pAnimImporter!=nullptr)
	{
		pAnimImp = m_pAnimImporter;
	}
	else
	{
		pAnimImp = m_pMeshImp;
	}
	m_fTime += g_fSecPerFrame * pAnimImp->m_Scene.iFrameSpeed * m_fDir * 0.33f;// m_fSpeed;
	if (m_fTime >= pAnimImp->m_Scene.iEnd)
	{
		//m_fDir *= -1.0f;
		m_fTime = pAnimImp->m_Scene.iStart;
	}

	int iFrame = m_fTime;
	iFrame = max(0, min(pAnimImp->m_Scene.iEnd-1, iFrame));

	for (int iObj = 0; iObj < m_pMeshImp->m_DrawList.size(); iObj++)	
	{
		SFbxModel* pFbxObj = m_pMeshImp->m_DrawList[iObj];	
		if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD") != nullptr)// != L"SK_Mannequin_LOD0")
		{
			if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD0") == nullptr)// != L"SK_Mannequin_LOD0")
			{
				continue;
			}
		}

		if (pFbxObj->m_bSkinned)
		{			
			for( auto data : pAnimImp->m_pFbxModelMap)
			{
				std::wstring name = data.first;
				SFbxModel* pAnimModel = data.second;
				auto model = m_pMeshImp->m_pFbxModelMap.find(name);
				if (model == m_pMeshImp->m_pFbxModelMap.end())
				{
					continue; // error
				}
				SFbxModel* pTreeModel = model->second;
				if (pTreeModel == nullptr)
				{
					continue; // error
				}
				auto binepose = pFbxObj->m_dxMatrixBindPoseMap.find(name);
				if (binepose != pFbxObj->m_dxMatrixBindPoseMap.end()&& pAnimModel)
				{
					SMatrix matInverseBindpose = binepose->second;
					m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex] =
						matInverseBindpose *				
						Interplate(pAnimImp, pAnimModel, m_fTime);
						//pAnimModel->m_AnimTrack[iFrame].matTrack;
				}
				S::D3DXMatrixTranspose( &m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex],
										&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex]);
			}
		}
		else
		{
			for (int inode = 0; inode < m_pMeshImp->m_TreeList.size(); inode++)
			{		
				SFbxModel* pFbxModel = m_pMeshImp->m_TreeList[inode];
				if (pFbxModel->m_AnimTrack.size() > 0)
				{					
					m_matBoneArray.matBoneWorld[inode] =
						Interplate(pAnimImp, pFbxModel, m_fTime);
						//pFbxModel->m_AnimTrack[iFrame].matTrack;
					
				}
				S::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[inode],
					&m_matBoneArray.matBoneWorld[inode]);
			}
		}

		m_pContext->UpdateSubresource(m_pMeshImp->m_pBoneCB, 0, NULL, &m_matBoneArray, 0, 0);
		m_pContext->VSSetConstantBuffers(2, 1, &m_pMeshImp->m_pBoneCB);

		S::SVector3 vLight(cosf(g_fGameTimer) * 100.0f,	100,sinf(g_fGameTimer) * 100.0f);
		S::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;
		pFbxObj->m_LightConstantList.vLightDir.x = vLight.x;
		pFbxObj->m_LightConstantList.vLightDir.y = vLight.y;
		pFbxObj->m_LightConstantList.vLightDir.z = vLight.z;
		pFbxObj->m_LightConstantList.vLightDir.w = 1.0f;
		pFbxObj->m_LightConstantList.vCameraDir.x = 
			m_pMainCamera->m_vLook.x;
		pFbxObj->m_LightConstantList.vCameraDir.y = 
			m_pMainCamera->m_vLook.y;
		pFbxObj->m_LightConstantList.vCameraDir.z = 
			m_pMainCamera->m_vLook.z;
		pFbxObj->m_LightConstantList.vCameraDir.w = 1.0f;
		pFbxObj->m_LightConstantList.vCameraPos.x = 
			m_pMainCamera->m_vCamera.x;
		pFbxObj->m_LightConstantList.vCameraPos.y = 
			m_pMainCamera->m_vCamera.y;
		pFbxObj->m_LightConstantList.vCameraPos.z = 
			m_pMainCamera->m_vCamera.z;
		pFbxObj->m_LightConstantList.vCameraPos.w = 1.0f;
		pFbxObj->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		pFbxObj->m_bAlphaBlend = m_bAlphaBlend;
		
		pFbxObj->PreRender();
		pFbxObj->Draw();
		pFbxObj->PostRender();	
	}
	return true;
}
bool	SFbx::RenderShadow(SShader* pShader)
{
	SFbxImporter* pAnimImp = nullptr;
	if (m_pAnimImporter != nullptr)
	{
		pAnimImp = m_pAnimImporter;
	}
	else
	{
		pAnimImp = m_pMeshImp;
	}
	m_fTime += g_fSecPerFrame * pAnimImp->m_Scene.iFrameSpeed * m_fDir * 0.33f;// m_fSpeed;
	if (m_fTime >= pAnimImp->m_Scene.iEnd)
	{
		//m_fDir *= -1.0f;
		m_fTime = pAnimImp->m_Scene.iStart;
	}

	int iFrame = m_fTime;
	iFrame = max(0, min(pAnimImp->m_Scene.iEnd - 1, iFrame));

	for (int iObj = 0; iObj < m_pMeshImp->m_DrawList.size(); iObj++)
	{
		SFbxModel* pFbxObj = m_pMeshImp->m_DrawList[iObj];
		if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD") != nullptr)// != L"SK_Mannequin_LOD0")
		{
			if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD0") == nullptr)// != L"SK_Mannequin_LOD0")
			{
				continue;
			}
		}

		if (pFbxObj->m_bSkinned)
		{
			for (auto data : pAnimImp->m_pFbxModelMap)
			{
				std::wstring name = data.first;
				SFbxModel* pAnimModel = data.second;
				auto model = m_pMeshImp->m_pFbxModelMap.find(name);
				if (model == m_pMeshImp->m_pFbxModelMap.end())
				{
					continue; // error
				}
				SFbxModel* pTreeModel = model->second;
				if (pTreeModel == nullptr)
				{
					continue; // error
				}
				auto binepose = pFbxObj->m_dxMatrixBindPoseMap.find(name);
				if (binepose != pFbxObj->m_dxMatrixBindPoseMap.end() && pAnimModel)
				{
					SMatrix matInverseBindpose = binepose->second;
					m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex] =
						matInverseBindpose *
						Interplate(pAnimImp, pAnimModel, m_fTime);
					//pAnimModel->m_AnimTrack[iFrame].matTrack;
				}
				S::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex],
					&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex]);
			}
		}
		else
		{
			for (int inode = 0; inode < m_pMeshImp->m_TreeList.size(); inode++)
			{
				SFbxModel* pFbxModel = m_pMeshImp->m_TreeList[inode];
				if (pFbxModel->m_AnimTrack.size() > 0)
				{
					m_matBoneArray.matBoneWorld[inode] =
						Interplate(pAnimImp, pFbxModel, m_fTime);
					//pFbxModel->m_AnimTrack[iFrame].matTrack;

				}
				S::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[inode],
					&m_matBoneArray.matBoneWorld[inode]);
			}
		}

		m_pContext->UpdateSubresource(m_pMeshImp->m_pBoneCB, 0, NULL, &m_matBoneArray, 0, 0);
		m_pContext->VSSetConstantBuffers(2, 1, &m_pMeshImp->m_pBoneCB);

		S::SVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
		S::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;
		pFbxObj->m_LightConstantList.vLightDir.x = vLight.x;
		pFbxObj->m_LightConstantList.vLightDir.y = vLight.y;
		pFbxObj->m_LightConstantList.vLightDir.z = vLight.z;
		pFbxObj->m_LightConstantList.vLightDir.w = 1.0f;
		pFbxObj->m_LightConstantList.vCameraDir.x =
			m_pMainCamera->m_vLook.x;
		pFbxObj->m_LightConstantList.vCameraDir.y =
			m_pMainCamera->m_vLook.y;
		pFbxObj->m_LightConstantList.vCameraDir.z =
			m_pMainCamera->m_vLook.z;
		pFbxObj->m_LightConstantList.vCameraDir.w = 1.0f;
		pFbxObj->m_LightConstantList.vCameraPos.x =
			m_pMainCamera->m_vCamera.x;
		pFbxObj->m_LightConstantList.vCameraPos.y =
			m_pMainCamera->m_vCamera.y;
		pFbxObj->m_LightConstantList.vCameraPos.z =
			m_pMainCamera->m_vCamera.z;
		pFbxObj->m_LightConstantList.vCameraPos.w = 1.0f;
		pFbxObj->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		

		pFbxObj->PreRender();
		pFbxObj->Draw();
		if (pShader != nullptr)
		{
			m_pContext->PSSetShader(pShader->m_pPixelShader, NULL, 0);
		}
		auto bAlphaBlend = pFbxObj->m_bAlphaBlend;
		pFbxObj->m_bAlphaBlend = true;
			pFbxObj->PostRender();
		pFbxObj->m_bAlphaBlend = bAlphaBlend;
	}
	return true;
}
bool	SFbx::Release()
{
	return true;
}

void        SFbx::GenAABB()
{
	// aabb 
	m_BoxCollision.vMin = S::SVector3(100000, 100000, 100000);
	m_BoxCollision.vMax = S::SVector3(-100000, -100000, -100000);
	for (int i = 0; i < m_VertexList.size(); i++)
	{
		if (m_BoxCollision.vMin.x > m_VertexList[i].p.x)
		{
			m_BoxCollision.vMin.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMin.y > m_VertexList[i].p.y)
		{
			m_BoxCollision.vMin.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMin.z > m_VertexList[i].p.z)
		{
			m_BoxCollision.vMin.z = m_VertexList[i].p.z;
		}

		if (m_BoxCollision.vMax.x < m_VertexList[i].p.x)
		{
			m_BoxCollision.vMax.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMax.y < m_VertexList[i].p.y)
		{
			m_BoxCollision.vMax.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMax.z < m_VertexList[i].p.z)
		{
			m_BoxCollision.vMax.z = m_VertexList[i].p.z;
		}
	}

	// 4      5
	// 6      7

	// 0     1
	// 2     3
	m_BoxCollision.vList[0] = S::SVector3(m_BoxCollision.vMin.x,
		m_BoxCollision.vMax.y,
		m_BoxCollision.vMin.z);
	m_BoxCollision.vList[1] = S::SVector3(m_BoxCollision.vMax.x,
		m_BoxCollision.vMax.y,
		m_BoxCollision.vMin.z);
	m_BoxCollision.vList[2] = S::SVector3(m_BoxCollision.vMin.x,
		m_BoxCollision.vMin.y,
		m_BoxCollision.vMin.z);
	m_BoxCollision.vList[3] = S::SVector3(m_BoxCollision.vMax.x,
		m_BoxCollision.vMin.y,
		m_BoxCollision.vMin.z);

	m_BoxCollision.vList[4] = S::SVector3(m_BoxCollision.vMin.x,
		m_BoxCollision.vMax.y,
		m_BoxCollision.vMax.z);
	m_BoxCollision.vList[5] = S::SVector3(m_BoxCollision.vMax.x,
		m_BoxCollision.vMax.y,
		m_BoxCollision.vMax.z);
	m_BoxCollision.vList[6] = S::SVector3(m_BoxCollision.vMin.x,
		m_BoxCollision.vMin.y,
		m_BoxCollision.vMax.z);
	m_BoxCollision.vList[7] = S::SVector3(m_BoxCollision.vMax.x,
		m_BoxCollision.vMin.y,
		m_BoxCollision.vMax.z);
}