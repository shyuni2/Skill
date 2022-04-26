#include "Sample.h"

// 현재 해야할거 리스트
// 박스 텍스쳐
// 박스 두개
// 카메라에 붙은 이상한거
// 맵 평면으로
// 카메라 위치
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
	m_CameraTopView.CreateViewMatrix(S::SVector3(0, 3000.0f, -1), S::SVector3(0, 0.0f, 0));
	m_CameraTopView.CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 10000.0f);

	m_MainCamera.Init();
	m_MainCamera.CreateViewMatrix(S::SVector3(0, 500.0f, -100.0f), S::SVector3(0, 0.0f, 0));
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
	m_BoxObj.Init();
	m_BoxObj.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_BoxObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Obj.hlsl", "VS");
	m_BoxObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Obj.hlsl", "PS");
	//m_BoxObj.SetPosition(S::SVector3(0.0f, 1.0f, 0.0f));
	if (!m_BoxObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}

	return true;
}
void Sample::RenderShadow(SMatrix* matView, SMatrix* matProj)
{

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

	m_BoxObj.m_matWorld = matScale * matRotate;
	m_BoxObj.m_vPos.y = m_MapObj.GetHeight(m_BoxObj.m_vPos.x, m_BoxObj.m_vPos.z) + 50;
	m_BoxObj.SetPosition(m_BoxObj.m_vPos);
	m_BoxObj.Frame();

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

	// 메인카메라 렌더링
	m_MainCamera.SetMatrix(nullptr, &m_CameraTopView.m_matView, &m_CameraTopView.m_matProj);
	m_MainCamera.Render();

	// 박스 렌더링
	m_BoxObj.SetMatrix(nullptr, &m_CameraTopView.m_matView, &m_CameraTopView.m_matProj); 
	m_BoxObj.Render();

	return true;
}
bool Sample::Release()
{
	return true;
}

RUN();