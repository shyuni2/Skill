#include "Obj3D.h"

void		Obj3D::SetMatrix(Matrix* matWorld,
	Matrix* matView, Matrix* matProj)
{
	m_ConstantList.matWorld = m_matWorld.Transpose();
	if (matWorld != nullptr)
	{
		m_ConstantList.matWorld = matWorld->Transpose();
	}
	if (matView != nullptr)
	{
		m_ConstantList.matView = matView->Transpose();
	}
	if (matProj != nullptr)
	{
		m_ConstantList.matProj = matProj->Transpose();
	}

	m_vLight.x = m_matWorld._11;
	m_vLight.y = m_matWorld._12;
	m_vLight.z = m_matWorld._13;
	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;
	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

}
void		Obj3D::AddPosition(Vector3 vPos)
{
	// 현재위치
	m_vPos += vPos;
	//  10,10f    ~     w(50, 10)
	//
	//   h
	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(
			m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}
/// <summary>
/// m_rtDraw, m_rtCollision 갱신된다.
/// </summary>
/// <param name="vPos"></param>
void		Obj3D::SetPosition(Vector3 vPos)
{
	m_vPos = vPos;
	m_matWorld._41 = m_vPos.x;
	m_matWorld._42 = m_vPos.y;
	m_matWorld._43 = m_vPos.z;
}
bool    Obj3D::SetVertexData()
{
	return true;
}
bool    Obj3D::SetIndexData()
{
	m_IndexList.clear();
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	return true;
}
void    Obj3D::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f)
	{
		m_bFadeIn = false;
	}
}
void    Obj3D::FadeOut()
{
	m_fAlpha = m_fAlpha - g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f)
	{
		m_bFadeOut = false;
	}
}
bool	Obj3D::Frame()
{
	if (m_bFadeIn)	FadeIn();
	if (m_bFadeOut)	FadeOut();
	m_ConstantList.Color = m_vColor;
	m_ConstantList.Timer = Vector4(g_fGameTimer, 0, 0, 1.0f);

	m_vLight.x = 1;
	m_vLight.y = 0;
	m_vLight.z = 0;
	m_vUp.x = 0;
	m_vUp.y = 1;
	m_vUp.z = 0;
	m_vLook.x = 0;
	m_vLook.y = 0;
	m_vLook.z = 1;

	return true;
}
Obj3D::Obj3D()
{
	m_fAlpha = 1.0f;
	m_vColor = Vector4(1, 1, 1, 1);
}
Obj3D::~Obj3D()
{

}