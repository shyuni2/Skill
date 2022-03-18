#pragma once
#include "Obj2D.h"

using CollisionFunction = std::function<void(BaseObj*, DWORD)>;
using SelectFunction = std::function<void(BaseObj*, DWORD)>;

class ObjMgr : public Singleton< ObjMgr>
{
private:
	int m_iExcueteCollisionID;
	int m_iExcueteSelectID;
	std::map<int, BaseObj*> m_ObjectList;
	std::map<int, BaseObj*> m_SelectList;	
public:
	friend Singleton< ObjMgr>;
public:	
	typedef std::map<int, CollisionFunction>::iterator FuncionIterator;
	std::map<int, CollisionFunction> m_fnCollisionExecute;
	typedef std::map<int, SelectFunction>::iterator FuncionIterator;
	std::map<int, SelectFunction> m_fnSelectExecute;
public:
	void  AddCollisionExecute(BaseObj* owner, CollisionFunction func);
	void  DeleteCollisionExecute(BaseObj* owner);
	void  AddSelectExecute(BaseObj* owner, CollisionFunction func);
	void  DeleteSelectExecute(BaseObj* owner);
	bool  Init();
	bool  Frame();
	bool  Release();
	void  CallRecursive(BaseObj* pSrcObj, DWORD dwState);
private:
	ObjMgr();
public:
	virtual ~ObjMgr();
};
#define I_ObjectMgr   ObjMgr::Get()
