#include "Sample.h"
#include "ObjMgr.h"

void Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}

bool Sample::Init()
{	
	I_Sound.Init();

	m_IntroScene.Init();
	m_IntroScene.m_pd3dDevice = m_pd3dDevice.Get();
	m_IntroScene.m_pContext = m_pImmediateContext.Get();
	m_IntroScene.Load(L"intor.txt");
	m_IntroScene.m_pNextWorld = &m_GameScene;
	m_GameScene.m_pd3dDevice = m_pd3dDevice.Get();
	m_GameScene.m_pContext = m_pImmediateContext.Get();
		
	World::m_pWorld = &m_IntroScene;

	return true;
}
bool Sample::Frame()
{		
	World::m_pWorld->Frame();

	return true;
}
bool Sample::Render()
{	
	World::m_pWorld->Render();

	std::wstring msg = L"FPS : ";
	msg += std::to_wstring(m_GameTimer.m_iFPS);
	msg += L", Play Time : ";
	msg += std::to_wstring(m_GameTimer.m_fTimer);
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0,0,1,1));

	return true;
}
bool Sample::Release()
{	
	I_Sound.Release();
	m_IntroScene.Release();
	m_GameScene.Release();
	return true;
}

Sample::Sample()
{

}
Sample::~Sample()
{

}

RUN();