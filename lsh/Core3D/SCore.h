#pragma once
#include "SDevice.h"
#include "SDxObj.h"
#include "SInput.h"
#include "STimer.h"
#include "SWriteFont.h"
#include "SCamera.h"
#include "SSkyObj.h"

class SCore : public SDevice
{
public:
	SSkyObj m_SkyObj;
	SCamera* m_pMainCamera = nullptr;
	SCamera  m_DefaultCamera;
	STimer m_GameTimer;
	SWriteFont m_dxWrite;
	bool m_bWireFrame = false;
	SBoxObj m_BoxDebug;
private:
	bool CoreInit();	
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
public:
	bool GameRun();
	void ResizeDevice(UINT iWidth, UINT iHeight);
	void DrawDebugInit(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
public:
	virtual void CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
public:
	SCore();
	virtual ~SCore();
};

