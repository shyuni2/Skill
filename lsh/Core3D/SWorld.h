#pragma once
#include "SObj2D.h"

class SWorld
{
public:
	enum SWorldID{ S_LOADING, S_LOGIN, S_LOBBY, S_ZONE, S_RESULT, };
public:
	ID3D11Device* m_pd3dDevice;	// 디바이스 객체
	ID3D11DeviceContext* m_pContext;// 다비이스 컨텍스트 객체
public:
	bool m_bLoadZone = false;
	static SWorld* m_pWorld;
	using m_mapIter = std::vector<std::shared_ptr<SObj2D>>::iterator;
public:
	std::vector<std::shared_ptr<SObj2D>> m_UIObj;
	std::vector<std::shared_ptr<SObj2D>> m_ItemObj;
	std::vector<std::shared_ptr<SObj2D>> m_NpcObj;
	std::vector<std::shared_ptr<SObj2D>> m_MapObj;	
public:
	virtual bool Load(std::wstring saveFile);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	SWorld();
	virtual ~SWorld();
};

