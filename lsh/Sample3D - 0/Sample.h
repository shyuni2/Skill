#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"
#include "Map.h"
#include "SkyObj.h"
#include "BoxObj.h"

class Sample : public Core
{
	Camera m_Camera;
	Map m_MapObj;
	BoxObj m_PlayerObj; // 박스, 플랜 등등으로 바꿔서 해보는중
	PlaneObj m_ObjB;
	SkyObj m_SkyObj;
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

