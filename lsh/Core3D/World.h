#pragma once
#include "Obj2D.h"

class World
{
public:
	enum WorldID { LOADING, LOGIN, LOBBY, ZONE, RESULT, };
public:
	ID3D11Device* m_pd3dDevice;	
	ID3D11DeviceContext* m_pContext;
	bool m_bLoadZone = false;
public:
	static World* m_pWorld;
	using m_mapIter = std::vector<std::shared_ptr<Obj2D>>::iterator;
public:
	std::vector<std::shared_ptr<Obj2D>> m_UIObj;
	std::vector<std::shared_ptr<Obj2D>> m_ItemObj;
	std::vector<std::shared_ptr<Obj2D>> m_NpcObj;
	std::vector<std::shared_ptr<Obj2D>> m_MapObj;	
public:	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool Load(std::wstring saveFile);
public:
	World();
	virtual ~World();
};

