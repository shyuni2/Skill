#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Map.h"
#include "Camera.h"

class Sample : public Core
{
public:
	Camera m_Camera;
	Map m_MapObj;
	PlaneObj m_PlayerObj;
	PlaneObj m_ObjB;
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
