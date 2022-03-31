#include "Obj3D.h"

void Obj3D::SetMatrix(T::Matrix* matWorld, T::Matrix* matView, T::Matrix* matProj)
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
	
	T::D3DXVec3Normalize(&m_vLight, &m_vLight);
	T::D3DXVec3Normalize(&m_vUp, &m_vUp);
	T::D3DXVec3Normalize(&m_vLook, &m_vLook);

	m_BoxCollision.vAxis[0] = m_vLight;
	m_BoxCollision.vAxis[1] = m_vUp;
	m_BoxCollision.vAxis[2] = m_vLook;

	// GenAABB();
	m_BoxCollision.vMin = T::Vector3(100000, 100000, 100000);
	m_BoxCollision.vMax = T::Vector3(-100000, -100000, -100000);
	for (int iV = 0; iV < 8; iV++)
	{
		T::Vector3 pos;
		T::D3DXVec3TransformCoord(&pos, &m_BoxCollision.vList[iV], &m_matWorld);
		if (m_BoxCollision.vMin.x > pos.x)
		{
			m_BoxCollision.vMin.x = pos.x;
		}
		if (m_BoxCollision.vMin.y > pos.y)
		{
			m_BoxCollision.vMin.y = pos.y;
		}
		if (m_BoxCollision.vMin.z > pos.z)
		{
			m_BoxCollision.vMin.z = pos.z;
		}

		if (m_BoxCollision.vMax.x < pos.x)
		{
			m_BoxCollision.vMax.x = pos.x;
		}
		if (m_BoxCollision.vMax.y < pos.y)
		{
			m_BoxCollision.vMax.y = pos.y;
		}
		if (m_BoxCollision.vMax.z < pos.z)
		{
			m_BoxCollision.vMax.z = pos.z;
		}
	}

	T::Vector3 vHalf = m_BoxCollision.vMax - m_BoxCollision.vCenter;
	m_BoxCollision.size.x = fabs(T::D3DXVec3Dot(&m_BoxCollision.vAxis[0], &vHalf));
	m_BoxCollision.size.y = fabs(T::D3DXVec3Dot(&m_BoxCollision.vAxis[1], &vHalf));
	m_BoxCollision.size.z = fabs(T::D3DXVec3Dot(&m_BoxCollision.vAxis[2], &vHalf));
	m_BoxCollision.vCenter = (m_BoxCollision.vMin + m_BoxCollision.vMax);
	m_BoxCollision.vCenter /= 2.0f;
}
void Obj3D::AddPosition(T::Vector3 vPos)
{
	// ������ġ
	m_vPos += vPos;
	//  10,10f    ~     w(50, 10)
	//
	//   h
	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}
void Obj3D::SetPosition(T::Vector3 vPos)
{
	m_vPos = vPos;
	m_matWorld._41 = m_vPos.x;
	m_matWorld._42 = m_vPos.y;
	m_matWorld._43 = m_vPos.z;
}
bool Obj3D::SetVertexData()
{
	return true;
}
bool Obj3D::SetIndexData()
{
	m_IndexList.clear();
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	return true;
}
void Obj3D::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f)
	{
		m_bFadeIn = false;
	}
}
void Obj3D::FadeOut()
{
	m_fAlpha = m_fAlpha - g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f)
	{
		m_bFadeOut = false;
	}
}
bool Obj3D::Frame()
{
	if (m_bFadeIn)	FadeIn();
	if (m_bFadeOut)	FadeOut();
	m_ConstantList.Color = m_vColor;
	m_ConstantList.Timer = T::Vector4(g_fGameTimer, 0, 0, 1.0f);

	m_BoxCollision.vCenter = m_vPos;
	T::Matrix matWorld = m_matWorld;
	matWorld._41 = 0.0f; matWorld._42 = 0.0f; matWorld._43 = 0.0f;
	m_BoxCollision.vAxis[0] = T::Vector3(1, 0, 0);
	m_BoxCollision.vAxis[1] = T::Vector3(0, 1, 0);
	m_BoxCollision.vAxis[2] = T::Vector3(0, 0, 1);

	m_BoxCollision.size.x = 1.0f;
	m_BoxCollision.size.y = 1.0f;
	m_BoxCollision.size.z = 1.0f;

	m_BoxCollision.vMin = T::Vector3(-1.0f, -1.0f, -1.0f);
	m_BoxCollision.vMax = T::Vector3(1.0f, 1.0f, 1.0f);
	return true;
}
void Obj3D::GenAABB()
{
	// aabb 
	m_BoxCollision.vMin = T::Vector3(100000, 100000, 100000);
	m_BoxCollision.vMax = T::Vector3(-100000, -100000, -100000);
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
	m_BoxCollision.vList[0] = T::Vector3(m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[1] = T::Vector3(m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[2] = T::Vector3(m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[3] = T::Vector3(m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);

	m_BoxCollision.vList[4] = T::Vector3(m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[5] = T::Vector3(m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[6] = T::Vector3(m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[7] = T::Vector3(m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
}
Obj3D::Obj3D()
{
	m_fAlpha = 1.0f;
	m_vColor = T::Vector4(1, 1, 1, 1);

	m_vLight.x = 1;
	m_vLight.y = 0;
	m_vLight.z = 0;
	m_vUp.x = 0;
	m_vUp.y = 1;
	m_vUp.z = 0;
	m_vLook.x = 0;
	m_vLook.y = 0;
	m_vLook.z = 1;

	m_BoxCollision.vAxis[0] = T::Vector3(1, 0, 0);
	m_BoxCollision.vAxis[1] = T::Vector3(0, 1, 0);
	m_BoxCollision.vAxis[2] = T::Vector3(0, 0, 1);
	m_BoxCollision.size.x = 1.0f;
	m_BoxCollision.size.y = 1.0f;
	m_BoxCollision.size.z = 1.0f;
	m_BoxCollision.vMin = T::Vector3(-1.0f, -1.0f, -1.0f);
	m_BoxCollision.vMax = T::Vector3(1.0f, 1.0f, 1.0f);
}
Obj3D::~Obj3D()
{

}