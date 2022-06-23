#pragma once
#include "SCore.h"
#include "SCamera.h"
#include "SMap.h"
#include "SBoxObj.h"
#include "SQuadtree.h" 
#include "Intersect.h"

class Sample : public Intersect
{
	SCamera m_Camera;
	SCamera m_CameraTopView;
	SMap m_MapObj;
	std::vector<SMapObj*> m_pObjList;
	SQuadtree m_Quadtree;
	SBoxObj*	m_pBoxObj;
public:
	virtual void CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:
	virtual bool Init()  override;
	virtual bool Frame()  override;
	virtual bool Render()  override;
	virtual bool Release()  override;	
public:
	Sample();
	virtual ~Sample();
};

