#pragma once
#include "Obj2D.h"

class World
{
public:
	enum TWorldID{ T_LOADING, T_LOGIN, T_LOBBY, T_ZONE, T_RESULT, };
public:
	ID3D11Device* m_pd3dDevice;	// 디바이스 객체
	ID3D11DeviceContext* m_pContext;// 다비이스 컨텍스트 객체
public:
	bool m_bLoadZone = false;
	static World* m_pWorld;
	using m_mapIter = std::vector<std::shared_ptr<Obj2D>>::iterator;
public:
	std::vector<std::shared_ptr<Obj2D>> m_UIObj;
	std::vector<std::shared_ptr<Obj2D>> m_ItemObj;
	std::vector<std::shared_ptr<Obj2D>> m_NpcObj;
	std::vector<std::shared_ptr<Obj2D>> m_MapObj;	
public:
	virtual bool Load(std::wstring saveFile);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	World();
	virtual ~World();
};

