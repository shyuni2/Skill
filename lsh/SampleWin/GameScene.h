#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#include "SoundMgr.h"
#include "UIObj.h"

class GameScene :   public World
{
public:
	PlayerObj2D m_PlayerObj;
	Sound* m_pBGM;
	Texture* m_pBackImage;
	Texture* m_pChangeColorTex[10];
public:
	bool Load(std::wstring file) override;
	bool CreateModelType();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

