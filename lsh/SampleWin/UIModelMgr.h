#pragma once
#include "BaseMgr.h"
#include "Obj2D.h"
#include "SoundMgr.h"

struct StatePlayData
{
	Texture* pTex;
	Sound* pSound;

	StatePlayData(const StatePlayData& data)
	{
		pTex = data.pTex;
		pSound = data.pSound;
		DisplayText("StatePlayDataCopy\n");
	}
	StatePlayData()
	{
		DisplayText("StatePlayData\n");
	}
	StatePlayData(Texture* a, Sound* b)
	{
		pTex = a;
		pSound = b;
		DisplayText("StatePlayData\n");
	}
};

class UIModel : public Obj2D
{
public:
	std::vector<StatePlayData> m_pStatePlayList;
	RECT m_rtOffset;
	RECT m_rtOffsetTex;
public:
	virtual UIModel* Clone() { return nullptr; }; 
	virtual void UpdateData() {}
};

class UIModelComposed : public UIModel
{
public:
	std::list< UIModel*> m_Components;
public:
	virtual UIModel* Clone();
	virtual void Add(UIModel* pObj);
	virtual void  UpdateData();
public:
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

class UIModelMgr : public BaseMgr<UIModel, UIModelMgr>
{
	friend class Singleton<UIModelMgr>;
private:
	UIModelMgr() {};
public:
	~UIModelMgr() {};
};

#define I_UI UIModelMgr::Get()

