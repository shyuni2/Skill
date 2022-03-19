#include "IntroScene.h"
#include "Input.h"
#include <string>
#include "ObjMgr.h"
#include "UIModelMgr.h"

bool IntroScene::CreateModelType()
{
	Shader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	Shader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");

	// 배경 어디를 눌러도 화면 전환되게 버튼처리
	std::shared_ptr<ButtonObj> btnObj(new ButtonObj);
	btnObj->m_csName = L"ButtonObj:IntroStart";
	btnObj->Init();
	btnObj->m_rtOffset = { 0, 0, 0, 0 };
	btnObj->SetRectDraw({ 0,0, 0,0 });
	btnObj->SetPosition(Vector2(300, 300));
	Texture* pTex = I_Texture.Load(L"../../data/menu/main.PNG");
	Sound* pSound = I_Sound.Load("../../data/Sound/startmenu.MP3");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/menu/main.PNG");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/menu/main.PNG");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/menu/main.PNG");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	if (!btnObj->Create(m_pd3dDevice, m_pContext, L"../../data/shader/DefaultUI.txt", L"../../data/menu/main.PNG"))
	{
		return false;
	}
	btnObj->SetCollisionType(CollisionType::Ignore, SelectType::Select_Overlap);
	pSound->Release();
	I_UI.m_list.insert(std::make_pair(L"IntroStart", btnObj));
	
	return true;
}
bool IntroScene::Init()
{
	World::Init();
	return true;
}
bool IntroScene::Load(std::wstring file)
{	
	m_pBGM = I_Sound.Load("../../data/Sound/startmenu.MP3");	
	m_pColorTex = I_Texture.Load(L"../../data/menu/Main.PNG");
	
	CreateModelType();

	Obj2D* pIntroStart = I_UI.GetPtr(L"IntroStart")->Clone();
	pIntroStart->m_csName = L"IntroStart";
	pIntroStart->SetRectDraw({ 0,0, g_rtClient.right,g_rtClient.bottom });
	pIntroStart->SetPosition(Vector2(952,521));
	pIntroStart->UpdateData();
		
	m_UIObj.push_back(std::shared_ptr<Obj2D>(pIntroStart));
	
	return true;
}
bool IntroScene::Frame()
{	
	if (m_bLoadZone && m_pNextWorld!=nullptr)
	{
		I_ObjectMgr.Release();
		m_pNextWorld->Load(L"zone.txt");
		World::m_pWorld = m_pNextWorld;
	}
	m_pBGM->Frame();
	World::Frame();
	return true;
}
bool	IntroScene::Render() 
{	
	World::Render();
	return true;
}
bool	IntroScene::Release() 
{	
	World::Release();
	return true;
}