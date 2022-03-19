#pragma once
#include "Core.h"

#include "IntroScene.h"
#include "GameScene.h"

class Sample : public Core
{
public:
	IntroScene m_IntroScene;
	GameScene m_GameScene;
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
	~Sample();
};

