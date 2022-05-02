#include "SBox.h"

bool SBox::RenderShadow(SShader* pShader)
{
	return true;
}

bool SBox::Init()
{
	return true;
}
bool SBox::Frame()
{
	return true;
}
bool SBox::Render()
{
	I_ObjectMgr.Set(m_pd3dDevice, m_pContext);

	SBoxObj* pBoxObj = &m_DrawList[];
	m_pContext->UpdateSubresource(m_pMeshImp->m_pBoneCB, 0, NULL, &m_matBoneArray, 0, 0);
	m_pContext->VSSetConstantBuffers(1, 1, &m_matBoneArray);

	S::SVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
	S::D3DXVec3Normalize(&vLight, &vLight);
	vLight = vLight * -1.0f;
	pBoxObj->m_LightConstantList.vLightDir.x = vLight.x;
	pBoxObj->m_LightConstantList.vLightDir.y = vLight.y;
	pBoxObj->m_LightConstantList.vLightDir.z = vLight.z;
	pBoxObj->m_LightConstantList.vLightDir.w = 1.0f;
	pBoxObj->m_LightConstantList.vCameraDir.x = m_pMainCamera->m_vLook.x;
	pBoxObj->m_LightConstantList.vCameraDir.y = m_pMainCamera->m_vLook.y;
	pBoxObj->m_LightConstantList.vCameraDir.z = m_pMainCamera->m_vLook.z;
	pBoxObj->m_LightConstantList.vCameraDir.w = 1.0f;
	pBoxObj->m_LightConstantList.vCameraPos.x = m_pMainCamera->m_vCamera.x;
	pBoxObj->m_LightConstantList.vCameraPos.y = m_pMainCamera->m_vCamera.y;
	pBoxObj->m_LightConstantList.vCameraPos.z = m_pMainCamera->m_vCamera.z;
	pBoxObj->m_LightConstantList.vCameraPos.w = 1.0f;

	pBoxObj->m_ConstantList.Timer.x = m_iShadowID;
	pBoxObj->m_ConstantList.Color = m_vShadowColor;
	pBoxObj->m_LightConstantList.matLight = m_LightConstantList.matLight;
	pBoxObj->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
	
	pBoxObj->m_bAlphaBlend = m_bAlphaBlend;
	pBoxObj->m_pVShader = m_pVShader;
	pBoxObj->m_pPShader = m_pPShader;
	pBoxObj->PreRender();
	pBoxObj->Draw();
	pBoxObj->PostRender();
	return true;
}
bool SBox::Release()
{
	return true;
}