#include "ObjectNpc2D.h"

void ObjectNpc2D::HitOverlap(BaseObj* pObj, DWORD dwState)
{
	if (dwState == CollisionType::Overlap)
	{
		//pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
	}
}

void ObjectNpc2D::HitSelect(BaseObj* pObj, DWORD dwState)
{
	if (m_dwSelectState & HOVER)
	{
		INT K = 0;
	}
	if (m_dwSelectState & FOCUS)
	{
		INT K = 0;
	}
	if (m_dwSelectState & ACTIVE)
	{
		INT K = 0;
	}
	if (m_dwSelectState & SELECTED)
	{
		m_bSelect = true;
		m_bDead = true;
	}
}
bool ObjectNpc2D::Frame()
{
	Vector2 p;
	if (m_vPos.x > g_rtClient.right - 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.right - 50.0f;
	}
	if (m_vPos.x < g_rtClient.left+ 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.left + 50.0f;
	}
	p = m_vDirection * (m_fSpeed * g_fSecPerFrame);
	AddPosition(p);
	return true;
}
ObjectNpc2D::ObjectNpc2D()
{
	m_fSpeed = 200.f; // ¼Ó·Â
	m_vDirection.x = (rand()%2 == 0) ? 1.0f : -1.0f;
	m_dwCollisonType = CollisionType::Overlap;
	m_dwSelectType = SelectType::Select_Overlap;
}
ObjectNpc2D::~ObjectNpc2D()
{
	
}