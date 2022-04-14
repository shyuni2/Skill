#pragma once
#include "Core.h"
#include "Camera.h"
#include "Map.h"
#include "BoxObj.h"
#include "Quadtree.h" 
#include "Intersect.h"

class Sample : public Intersect
{
	Camera m_Camera;
	Camera m_CameraTopView;
	Map m_MapObj;
	std::vector<MapObj*> m_pObjList;
	Quadtree m_Quadtree;
	BoxObj*	m_pBoxObj;
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

