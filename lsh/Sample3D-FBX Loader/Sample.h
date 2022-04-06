#pragma once
#include "Core.h"
#include "FbxLoader.h"

class Sample : public Core
{
	FbxLoader m_FbxObj;
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

