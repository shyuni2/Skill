#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#include "UIObj.h"
#include "SoundMgr.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"

class IntroScene : public World
{
public:
	Sound* m_pBGM;
	Texture* m_pChangeColorTex[10];
	Texture* m_pColorTex;
	World* m_pNextWorld;
public:
	bool CreateModelType();
	bool Load(std::wstring file) override;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

