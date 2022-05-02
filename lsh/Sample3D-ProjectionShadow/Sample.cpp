#include "Sample.h"
#include "SObjMgr.h"

// 현재 해야할거 리스트
// 박스 텍스쳐
// 빛 그림자
// 박스 이동

bool Sample::RenderMap()
{
	m_MapObj.Init();
	m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_MapObj.CreateHeightMap(L"../../data/map/129.jpg");
	STexture* pTexMap = I_Texture.Load(L"../../data/map/020.bmp");
	m_MapObj.m_pColorTex = pTexMap;
	m_MapObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"map.hlsl", "VS");
	m_MapObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"map.hlsl", "PS");
	m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 100.0f);
	if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}
	return true;
}
bool Sample::RenderMainCamera()
{
	m_MainCamera.Init();
	m_MainCamera.CreateViewMatrix(S::SVector3(-1000, 350.0f, 0.0f), S::SVector3(0, 0.0f, 0));
	m_MainCamera.CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	m_MainCamera.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"maincamera.hlsl", "VS");
	m_MainCamera.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"maincamera.hlsl", "PS");
	m_MainCamera.SetPosition(S::SVector3(0.0f, 1000.0f, 0.0f));
	if (!m_MainCamera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}
	return true;
}
bool Sample::RenderObject()
{
	//m_BoxObj.Init();
	//m_BoxObj.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	//m_BoxObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Obj.hlsl", "VS");
	//m_BoxObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Obj.hlsl", "PS");
	//if (!m_BoxObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	//{
	//	return false;
	//}
	//
	std::vector<std::wstring> listname;
	listname.push_back(L"../../data/fbx/Greystone.fbx");

	I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());

	SBox* pBox = &m_FbxObj[iObj];
	pBox->Init();
	pBox->m_iShadowID = (iObj * 2) + 1;
	pBox->m_vShadowColor = SVector4(pBox->m_iShadowID / 255.0f, 1, 1, 1);
	pBox->m_pMainCamera = m_pMainCamera;
	pBox->m_pd3dDevice = m_pd3dDevice.Get();
	pBox->m_pContext = m_pImmediateContext.Get();
	pBox->m_pMeshImp = I_ObjectMgr.Load(listname[iObj]);
	pBox->m_pVShader = I_Shader.CreateVertexShader(g_pd3dDevice, L"Obj.hlsl", "VS");
	pBox->m_pPShader = I_Shader.CreatePixelShader(g_pd3dDevice, L"Obj.hlsl", "PSMRT");

	pBox->m_DrawList.resize(pBox->m_pMeshImp->m_DrawList.size());
	int iRow = iObj / 10;
	int iCol = iObj / 10;
	int iOffRow = iObj % 10;
	int iOffCol = iObj % 10;
	S::SVector3 vPos = { -2000.0f + iOffCol * 300.0f,0, -2000.0f + iRow * 300.0f };
	vPos.y = m_MapObj.SMap::GetHeight(vPos.x, vPos.z);
	pBox->SetPosition(vPos);
	for (int iDraw = 0; iDraw < pBox->m_pMeshImp->m_DrawList.size(); iDraw++)
	{
		pBox->m_pMeshImp->m_DrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
	}
	m_FbxObj[0].m_pAnimImporter = m_FbxObj[1].m_pMeshImp;
	return true;
}
void Sample::RenderProjectionShadow(SMatrix* matWorld, SMatrix* matShadow, SMatrix* matView, SMatrix* matProj)
{
	ApplyDSS(m_pImmediateContext.Get(), SDxState::g_pDSSDepthEnable);
	ApplyRS(m_pImmediateContext.Get(), SDxState::g_pRSNoneCullSolid);
	ApplyBS(m_pImmediateContext.Get(), SDxState::m_AlphaBlend);

	SMatrix matWorldShadow = (*matWorld) * (*matShadow);
	m_BoxObj.SetMatrix(&matWorldShadow, matView, matProj);
	m_BoxObj.PreRender();
	m_pImmediateContext.Get()->PSSetShader(m_pPixelShader.Get(), NULL, 0); // ?
	m_BoxObj.PostRender();
}

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
	RenderMap();
	RenderMainCamera();
	RenderObject();
	
	return true;
}
bool Sample::Frame()
{
	// 빛
	SMatrix matRotation;
	SVector3 vLight = m_vLightPos;
	D3DXMatrixRotationY(&matRotation, g_fGameTimer);
	D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
	D3DXVec3Normalize(&m_vLightDir, &vLight);

	// 카메라 이동처리
	S::SVector2 dir = SInput::Get().GetDelta();
	S::SMatrix matRotate;
	S::SMatrix matScale;
	S::D3DXMatrixRotationY(&matRotate, -dir.y);
	S::D3DXMatrixScaling(&matScale, 100, 100, 100);
	float y = m_MapObj.GetHeight(m_MainCamera.m_vCamera.x, m_MainCamera.m_vCamera.z);

	// 카메라이동 방향키(w, a, s, d)
	if (SInput::Get().GetKey('A'))
	{
		m_MainCamera.MoveSide(-g_fSecPerFrame * 1000.0f);
	}
	if (SInput::Get().GetKey('D'))
	{
		m_MainCamera.MoveSide(g_fSecPerFrame * 1000.0f);
	}
	if (SInput::Get().GetKey('W'))
	{
		m_MainCamera.MoveLook(g_fSecPerFrame * 1000.0f);
	}
	if (SInput::Get().GetKey('S'))
	{
		m_MainCamera.MoveLook(-g_fSecPerFrame * 1000.0f);
	}
	m_MainCamera.Update(S::SVector4(-dir.x, -dir.y, 0, 0));
	m_MapObj.Frame();

	// 그림자
	SVector4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (m_dxRT.Begin(m_pImmediateContext.Get(), vClearColor))
	{
		//-----------------------------------------------------
		// 1패스:그림자맵 생성
		//-----------------------------------------------------		
		SVector3 vEye = vLight;
		SVector3 vLookat = { 0,0,0 };
		SVector3 vUp = SVector3(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&m_matViewLight, &vEye, &vLookat, &vUp);
		//D3DXMatrixPerspectiveFovLH(&m_matProjLight, XM_PI / 4, 1, 0.1f, 20000.0f);
		D3DXMatrixOrthoOffCenterLH(&m_matProjLight,
			-6000 / 2, 6000.0f / 2, -6000.0f / 2, 6000.0f / 2, 0.0f, 20000.0f);
		if (m_bDepthShadow)
		{
			RenderDepthShadow(&m_matViewLight, &m_matProjLight);
		}
		else
		{
			RenderProjectionShadow(&m_matViewLight, &m_matProjLight);
		}
	}
	// 박스
	m_BoxObj.m_matWorld = matScale * matRotate;
	m_BoxObj.m_vPos.y = m_MapObj.GetHeight(m_BoxObj.m_vPos.x, m_BoxObj.m_vPos.z) + 300;
	m_BoxObj.SetPosition(m_BoxObj.m_vPos);
	m_BoxObj.Frame();

	////-----------------------------------------------------
	//// 1패스: 지형 + 쉐도우 랜더링
	////-----------------------------------------------------		
	//m_CustomMap.SeSMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	//m_cbShadow.g_matShadow[0] = m_CustomMap.m_matWorld * m_matViewLight[0] * m_matProjLight[0] * m_matTexture;
	//m_cbShadow.g_matShadow[1] = m_CustomMap.m_matWorld * m_matViewLight[1] * m_matProjLight[1] * m_matTexture;
	//D3DXMatrixTranspose(&m_cbShadow.g_matShadow[0], &m_cbShadow.g_matShadow[0]);
	//D3DXMatrixTranspose(&m_cbShadow.g_matShadow[1], &m_cbShadow.g_matShadow[1]);
	//GetContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
	//GetContext()->VSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());

	//ApplySS(GetContext(), SDxState::g_pSSClampLinear, 1);
	//m_CustomMap.PreRender(GetContext());
	//{
	//	ID3D11ShaderResourceView* pSRV[] = { m_RT[0].m_pSRV.Get(),m_RT[1].m_pSRV.Get() };
	//	GetContext()->PSSetShaderResources(1, 2, pSRV);
	//}
	//m_CustomMap.PostRender(GetContext());

	return true;
}
bool Sample::Render()
{
	// 글 렌더링
	std::wstring msg = L"< 카메라 이동 : w, a, s, d >";
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 0, 1));

	// 맵 렌더링
	m_MapObj.SetMatrix(nullptr, &m_MainCamera.m_matView, &m_MainCamera.m_matProj);
	m_MapObj.Render();

	// 박스 렌더링
	m_BoxObj.SetMatrix(nullptr, &m_MainCamera.m_matView, &m_MainCamera.m_matProj);
	m_BoxObj.Render();


	// 메인카메라 렌더링
	m_MainCamera.Render();

	return true;
}
bool Sample::Release()
{
	return true;
}

RUN();

