#include "Sample.h"

void Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}

bool Sample::Init()
{
	m_FbxObj.Init();
	//m_FbxObj.Load("../../data/fbx/SM_Barrel.fbx");
	//m_FbxObj.Load("../../data/fbx/SM_Rock.fbx");
	//m_FbxObj.Load("../../data/fbx/MultiCameras.fbx");
	//m_FbxObj.Load("../../data/fbx/st00sc00.fbx");
	//m_FbxObj.Load("../../data/fbx/SM_Tree_Var01.fbx");
	m_FbxObj.Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");

	Texture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	Shader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
	Shader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");
	for (int iObj = 0; iObj < m_FbxObj.m_DrawList.size(); iObj++)
	{
		m_FbxObj.m_DrawList[iObj]->Init();
		m_FbxObj.m_DrawList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_DrawList[iObj]->m_szTexFileName);
		m_FbxObj.m_DrawList[iObj]->m_pVShader = pVShader;
		m_FbxObj.m_DrawList[iObj]->m_pPShader = pPShader;
		if (!m_FbxObj.m_DrawList[iObj]->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
		{
			return false;
		}
	}

	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));

	return true;
}
bool Sample::Frame()
{
	return true;
}
bool Sample::Render()
{
	return true;
}
bool Sample::Release()
{
	m_FbxObj.Release();
	return true;
}

Sample::Sample()
{

}
Sample::~Sample()
{

}

RUN();