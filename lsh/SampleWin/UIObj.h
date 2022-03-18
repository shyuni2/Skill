#pragma once
#include "ObjMgr.h"
#include "UIModelMgr.h"

class UIObj : public UIModel
{
public:
	UIModel* Clone()
	{
		UIModel* pCopy = new UIObj(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	};
	void UpdateData() override
	{
		m_rtCollision = Rect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(CollisionType::Ignore, SelectType::Select_Overlap);
		I_ObjectMgr.AddCollisionExecute(this, std::bind(&BaseObj::HitOverlap, this, std::placeholders::_1, std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this, std::bind(&BaseObj::HitSelect, this, std::placeholders::_1, std::placeholders::_2)); 
	}
public:
	bool SetVertexData()override;
	bool SetIndexData()override;
	void HitSelect(BaseObj* pObj, DWORD dwState) override
	{
		int k = 0;
	}
public:	
	bool Frame() override;
	bool Render()override;
public:
	UIObj()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};

class ImageObj : public UIObj
{
public:
	UIModel* Clone()
	{
		UIModel* pCopy = new ImageObj(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	}; 
	void HitSelect(BaseObj* pObj, DWORD dwState) override
	{
		int k = 0;
	}
public:
	bool Init() override;
	bool Frame() override;
	bool Render()override;
};

class ButtonObj : public UIObj
{
public:
	UIModel* Clone()
	{
		UIModel* pCopy = new ButtonObj(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	};
public:
	virtual void HitSelect(BaseObj* pObj, DWORD dwState) override;
public:
	bool Init() override;
	bool Frame() override;
	bool Render()override;
public:
	ButtonObj() {}
	virtual ~ButtonObj() {}
};

class ListCtrlObj : public UIModelComposed
{
public:
	UIModel* Clone()
	{
		UIModelComposed* pModel = new ListCtrlObj;
		std::list< UIModel*>::iterator iter;
		for (iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			pModel->Add((*iter)->Clone());
		}
		return pModel;
	};	
	bool Create(int xCount, int yCount);
	void UpdateData() override
	{
		m_rtCollision = Rect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(CollisionType::Ignore, SelectType::Select_Overlap);
		I_ObjectMgr.AddCollisionExecute(this, std::bind(&BaseObj::HitOverlap, this, std::placeholders::_1, std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this, std::bind(&BaseObj::HitSelect, this, std::placeholders::_1, std::placeholders::_2));
	}
	virtual void HitSelect(BaseObj* pObj, DWORD dwState) override;
public:
	ListCtrlObj() {}
	virtual ~ListCtrlObj() {}
};
