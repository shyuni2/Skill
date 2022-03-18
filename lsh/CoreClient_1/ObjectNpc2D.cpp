#include "ObjectNpc2D.h"

bool ObjectNpc2D::Frame()
{
	return true;
}

void ObjectNpc2D::HitOverlap(BaseObject* pObj, DWORD dwState)
{

}
void ObjectNpc2D::HitSelect(BaseObject* pObj, DWORD dwState)
{

}

ObjectNpc2D::ObjectNpc2D()
{
	m_fSpeed = 20.0f + (rand() % 300); // ¼Ó·Â
	m_vDirection.x = (rand() % 2 == 0) ? 1.0f : -1.0f;
	m_vDirection.y = (rand() % 2 == 0) ? 1.0f : -1.0f;
}
ObjectNpc2D::~ObjectNpc2D()
{

}