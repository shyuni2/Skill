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
	// 카메라 ---------------------------
	m_CameraTopView.CreateViewMatrix(T::TVector3(0, 3000.0f, -1), T::TVector3(0, 0.0f, 0));
	m_CameraTopView.CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 10000.0f);

	m_Camera.Init();
	m_Camera.CreateViewMatrix(T::TVector3(0, 500.0f, -100.0f), T::TVector3(0, 0.0f, 0));
	m_Camera.CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	m_Camera.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VSColor");
	m_Camera.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PSColor");
	m_Camera.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
	if (!m_Camera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}
	
	// 지형 ---------------------------
	m_MapObj.Init();
	m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_MapObj.CreateHeightMap(L"../../data/map/129.jpg");
	Texture* pTexMap = I_Texture.Load(L"../../data/map/020.bmp");
	m_MapObj.m_pColorTex = pTexMap;	
	m_MapObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"map.hlsl", "VS");
	m_MapObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"map.hlsl", "PS");
	m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 60.0f);
	if (!m_MapObj.Create(m_pd3dDevice.Get(),m_pImmediateContext.Get()))
	{
		return false;
	}
	m_Quadtree.DrawDebugInit(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_Quadtree.m_pCamera = &m_Camera;
	m_Quadtree.Build(&m_MapObj, 3);
	
	return true;
}
bool Sample::Frame()
{	
	T::TVector2 dir = Input::Get().GetDelta();
	T::TMatrix matRotate;
	T::TMatrix matScale;

	T::D3DXMatrixRotationY(&matRotate, -dir.y);
	T::D3DXMatrixScaling(&matScale, 100, 100, 100);

	float y = m_MapObj.GetHeight(m_Camera.m_vCamera.x, m_Camera.m_vCamera.z);
	
	// 카메라이동 방향키 ---------------------------
	if (Input::Get().GetKey('A'))
	{
		m_Camera.MoveSide(-g_fSecPerFrame * 1000.0f);
	}
	if (Input::Get().GetKey('D'))
	{
		m_Camera.MoveSide(g_fSecPerFrame * 1000.0f);
	}
	if (Input::Get().GetKey('W'))
	{
		m_Camera.MoveLook(g_fSecPerFrame * 1000.0f);
	}
	if (Input::Get().GetKey('S'))
	{
		m_Camera.MoveLook(-g_fSecPerFrame * 1000.0f);
	}
	
	m_Camera.Update(T::TVector4(-dir.x, -dir.y,0,0));
	m_MapObj.Frame();
	m_Quadtree.Update(&m_Camera);

	// 마우스 피킹 ---------------------------
	if (Input::Get().m_dwMouseState[1] == KEY_HOLD)
	{
		POINT ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(g_hWnd, &ptCursor);
		T::TVector3 vView, vProj; // view
		vProj.x = (((2.0f * ptCursor.x - 2.0f* m_ViewPort.TopLeftX) / m_ViewPort.Width) - 1 ) ;
		vProj.y = -(((2.0f * ptCursor.y - 2.0f * m_ViewPort.TopLeftY) / m_ViewPort.Height) - 1);
		vProj.z = 1.0f;
		vView.x = vProj.x / m_Camera.m_matProj._11;
		vView.y = vProj.y / m_Camera.m_matProj._22;
		vView.z = vProj.z;
		T::TMatrix m;
		T::D3DXMatrixInverse(&m, nullptr, &m_Camera.m_matView);

		// 지형 ---------------------------
		T::TRay ray;		
		ray.direction.x = vView.x*m._11 + vView.y*m._21 + vView.z*m._31;
		ray.direction.y = vView.x*m._12 + vView.y*m._22 + vView.z*m._32;
		ray.direction.z = vView.x*m._13 + vView.y*m._23 + vView.z*m._33;
		ray.position.x = m._41;
		ray.position.y = m._42;
		ray.position.z = m._43;
		T::D3DXVec3Normalize(&ray.direction, &ray.direction);
		T::TVector3 vStart = ray.position; // 교점
		T::TVector3 vEnd = ray.position + ray.direction * m_Camera.m_fFarDistance; 
		for (int iNode = 0; iNode < m_Quadtree.g_pDrawLeafNodes.size(); iNode++)
		{
			Node* pNode = m_Quadtree.g_pDrawLeafNodes[iNode];

			for (int i = 0; i < pNode->m_IndexList[0].size(); i += 3)
			{
				T::TVector3 v0, v1, v2;
				DWORD i0 = pNode->m_IndexList[0][i + 0];
				DWORD i1 = pNode->m_IndexList[0][i + 1];
				DWORD i2 = pNode->m_IndexList[0][i + 2];
				v0 = m_MapObj.m_VertexList[i0].p;
				v1 = m_MapObj.m_VertexList[i1].p;
				v2 = m_MapObj.m_VertexList[i2].p;
				
				float t, u, v;
				if (IntersectTriangle(ray.position, ray.direction, v0, v1, v2, &t, &u, &v))
				{
					m_vIntersection = ray.position + ray.direction * t;
					m_MapObj.m_VertexList[i0].c = T::TVector4(1, 0, 0, 1);
					m_MapObj.m_VertexList[i1].c = T::TVector4(1, 0, 0, 1);
					m_MapObj.m_VertexList[i2].c = T::TVector4(1, 0, 0, 1);
					m_MapObj.m_pContext->UpdateSubresource(m_MapObj.m_pVertexBuffer, 0, NULL, &m_MapObj.m_VertexList.at(0), 0, 0);

					DisplayText("\n%10.4f, %10.4f, %10.4f ", m_vIntersection.x, m_vIntersection.y, m_vIntersection.z);
					m_vIntersectionList.push_back(m_vIntersection);
				}
			}
		}
	}
	return true;
}
bool Sample::Render()
{		
	if (m_bWireFrame)
	{
		m_pImmediateContext->RSSetState(DxState::g_pRSBackCullWireFrame);
	}		
	else
	{
		m_pImmediateContext->RSSetState(DxState::g_pRSBackCullSolid);
	}

	m_pImmediateContext->PSSetSamplers(0, 1, &DxState::m_pSSLinear);
	m_MapObj.SetMatrix(nullptr, &m_Camera.m_matView,&m_Camera.m_matProj);
	m_Quadtree.Render();	

	// 글 ---------------------------
	std::wstring msg = L"FPS :";
	msg += std::to_wstring(m_GameTimer.m_iFPS);
	msg += L", Play Time :";
	msg += std::to_wstring(m_GameTimer.m_fTimer);
	msg += L"\n카메라 이동 : w, a, s, d";
	msg += L"\n와이어프레임 on/off : f";
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 0, 1));

	return true;
}

bool Sample::Release()
{
	m_MapObj.Release();
	m_Camera.Release();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{

}

RUN();