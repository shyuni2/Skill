#include "SWorld.h"
#include "SObjMgr.h"

SWorld* SWorld::m_pWorld = nullptr;

bool SWorld::Load(std::wstring saveFile)
{
	return true;
}
bool SWorld::Init()
{
	return true;
}
bool SWorld::Frame()
{
	for (auto obj : m_UIObj)
	{
		SObj2D* pObj = obj.get();
		if (pObj != nullptr)
		{
			pObj->Frame();
		}
	}
	for (auto obj : m_NpcObj)
	{
		SObj2D* pObj = obj.get();
		if (pObj != nullptr)
		{
			pObj->Frame();
		}
	}
	return true;
}
bool SWorld::Render()
{
	for (auto obj : m_UIObj)
	{
		SObj2D* pObj = obj.get();
		if (pObj != nullptr)
		{
			pObj->Render();
		}
	}
	for (auto obj : m_NpcObj)
	{
		SObj2D* pObj = obj.get();
		if (pObj->m_bDead == false)
		{
			pObj->Render();
		}
	}
	return true;
}
bool SWorld::Release()
{
	for (auto obj : m_UIObj)
	{
		if (obj != nullptr)
		{
			obj->Release();
			obj = nullptr;
		}
		
	}
	for (auto obj : m_ItemObj)
	{
		if (obj != nullptr)
		{
			obj->Release();
			obj = nullptr;
		}
	}
	for (auto obj : m_NpcObj)
	{
		if (obj != nullptr)
		{
			obj->Release();
			obj = nullptr;
		}
	}
	for (auto obj : m_MapObj)
	{
		if (obj != nullptr)
		{
			obj->Release();
			obj = nullptr;
		}
	}
	m_ItemObj.clear();
	m_UIObj.clear();
	m_NpcObj.clear();
	m_MapObj.clear();
	return true;
}

SWorld::SWorld()
{

}

SWorld::~SWorld()
{
	Release();
}