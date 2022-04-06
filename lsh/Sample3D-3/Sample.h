#pragma once
#include "TCore.h"
#include "PlaneObj.h"
#include "Camera.h"
#include "Map.h"
#include "SkyObj.h"
#include "BoxObj.h"
#include "Quadtree.h" 

#define  MAX_NUM_OBJECTS 100
class Sample : public TCore
{
	Camera		    m_Camera;
	Camera			m_CameraTopView;
	Map			m_MapObj;
	BoxObj			m_PlayerObj;
	std::vector<MapObj*> m_pObjList;
	SkyObj			m_SkyObj;
	Quadtree		m_Quadtree;
	BoxObj*		m_pBoxObj;
public:
	void    CreateMapObject();
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	bool    MiniMapRender();
	virtual bool	Release()  override;	
public:
	Sample();
	virtual ~Sample();
};

