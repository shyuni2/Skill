#pragma once
#include "SObj2D.h"

using CollisionFunction = std::function<void(SBaseObj*, DWORD)>;
using SelectFunction = std::function<void(SBaseObj*, DWORD)>;

class ObjMgr : public Singleton< ObjMgr>
{
private:
	int m_iExcueteCollisionID;
	int m_iExcueteSelectID;
	std::map<int, SBaseObj*> m_ObjList;
	std::map<int, SBaseObj*> m_SelectList;	
public:
	friend Singleton< ObjMgr>;
public:	
	typedef std::map<int, CollisionFunction>::iterator FuncionIterator;
	std::map<int, CollisionFunction> m_fnCollisionExecute;
	typedef std::map<int, SelectFunction>::iterator FuncionIterator;
	std::map<int, SelectFunction> m_fnSelectExecute;
public:
	void AddCollisionExecute(SBaseObj* owner, CollisionFunction func);
	void DeleteCollisionExecute(SBaseObj* owner);
	void AddSelectExecute(SBaseObj* owner, CollisionFunction func);
	void DeleteSelectExecute(SBaseObj* owner);
public:
	bool Init();
	bool Frame();
	bool Release();
	void CallRecursive(SBaseObj* pSrcObj, DWORD dwState);
private:
	ObjMgr();
public:
	virtual ~ObjMgr();
};
#define I_ObjectMgr   ObjMgr::Get()
