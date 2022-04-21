#include "SObjMgr.h"
#include "SInput.h"

void SObjMgr::AddCollisionExecute(SBaseObj* owner, CollisionFunction func)
{
	owner->m_iCollisionID = m_iExcueteCollisionID++;
	m_ObjList.insert(std::make_pair(owner->m_iCollisionID, owner));
	m_fnCollisionExecute.insert(std::make_pair(owner->m_iCollisionID, func));
}
void SObjMgr::DeleteCollisionExecute(SBaseObj* owner)
{
	std::map<int, SBaseObj*>::iterator objiter;
	objiter = m_ObjList.find(owner->m_iCollisionID);
	if (objiter != m_ObjList.end())
	{
		m_ObjList.erase(objiter);
	}

	FuncionIterator colliter = m_fnCollisionExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnCollisionExecute.end())
	{
		m_fnCollisionExecute.erase(colliter);
	}
}
void SObjMgr::AddSelectExecute(SBaseObj* owner, CollisionFunction func)
{
	owner->m_iSelectID = m_iExcueteSelectID++;
	m_SelectList.insert(std::make_pair(owner->m_iSelectID, owner));
	m_fnSelectExecute.insert(std::make_pair(owner->m_iSelectID, func));
}
void SObjMgr::DeleteSelectExecute(SBaseObj* owner)
{
	std::map<int, SBaseObj*>::iterator objiter;
	objiter = m_SelectList.find(owner->m_iCollisionID);
	if (objiter != m_SelectList.end())
	{
		m_SelectList.erase(objiter);
	}

	FuncionIterator colliter = m_fnSelectExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnSelectExecute.end())
	{
		m_fnSelectExecute.erase(colliter);
	}
}
bool SObjMgr::Init()
{
	return true;
}
void SObjMgr::CallRecursive(SBaseObj* pSrcObj,DWORD dwState)
{
	if (pSrcObj->m_pParent == nullptr)
	{		
		return;
	}
	CallRecursive(pSrcObj->m_pParent, dwState);
	pSrcObj->HitSelect(pSrcObj, dwState);
}
bool SObjMgr::Frame()
{
	// collision
	for (auto src : m_ObjList)
	{
		SBaseObj* pObjSrc = (SBaseObj*)src.second;
		if (pObjSrc->m_dwCollisonType == CollisionType::Ignore) continue;
		DWORD dwState= CollisionType::Overlap;
		for (auto dest : m_ObjList)
		{
			SBaseObj* pObjDest = (SBaseObj*)dest.second;
			if (pObjSrc == pObjDest) continue;
			if (SCollision::ToRect(pObjSrc->m_rtCollision, pObjDest->m_rtCollision))
			{
				FuncionIterator colliter = m_fnCollisionExecute.find(pObjSrc->m_iCollisionID);
				if (colliter != m_fnCollisionExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjDest, dwState);
				}
			}
		}
	}

	// mouse select
	for (auto src : m_SelectList)
	{
		SBaseObj* pObjSrc = (SBaseObj*)src.second;
		//if (pObjSrc->m_dwSelectType == SelectType::Select_Ignore) continue;
		DWORD dwState = SelectState::DEFAULT;

		if (pObjSrc->m_dwSelectType != SelectType::Select_Ignore &&
			SCollision::RectToPoint(
			pObjSrc->m_rtCollision, (float)g_ptMouse.x, (float)g_ptMouse.y))
		{
			DWORD dwKeyState = SInput::Get().m_dwMouseState[0];
			pObjSrc->m_dwSelectState = SelectState::HOVER;
			if (dwKeyState == KEY_PUSH)
			{
				pObjSrc->m_dwSelectState = SelectState::ACTIVE;
			}
			if (dwKeyState == KEY_HOLD)
			{
				pObjSrc->m_dwSelectState = SelectState::FOCUS;
			}
			if (dwKeyState == KEY_UP)
			{
				pObjSrc->m_dwSelectState = SelectState::SELECTED;
			}

			CallRecursive(pObjSrc, dwState);
			FuncionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
			if (colliter != m_fnSelectExecute.end())
			{			
				CollisionFunction call = colliter->second;
				call(pObjSrc, dwState);					
			}
		}
		else
		{
			if (pObjSrc->m_dwSelectState != SelectState::DEFAULT)
			{
				pObjSrc->m_dwSelectState = SelectState::DEFAULT;
				FuncionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
				if (colliter != m_fnSelectExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjSrc, dwState);
				}
			}
		}		
	}	
	return true;
}
bool SObjMgr::Release()
{
	m_ObjList.clear();
	m_SelectList.clear();
	return true;
}

SObjMgr::SObjMgr()
{
	m_iExcueteCollisionID = 0;
	m_iExcueteSelectID = 0;
};
SObjMgr::~SObjMgr() 
{
	Release();
};
