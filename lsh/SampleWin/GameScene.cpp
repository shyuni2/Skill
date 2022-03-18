#include "GameScene.h"
#include "Input.h"
#include "DxObj.h"

bool GameScene::CreateModelType()
{	
	Shader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	Shader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");

	// 배경이미지
	std::shared_ptr<ImageObj> obj(new ImageObj);
	obj->m_csName = L"ImageObj:BackImage";
	obj->Init();
	obj->SetRectDraw({ 0,0, g_rtClient.right,g_rtClient.bottom });
	obj->SetPosition(Vector2(0, 0));
	obj->m_pColorTex = m_pBackImage;
	obj->m_pMaskTex = nullptr;
	obj->m_pVShader = pVShader;
	obj->m_pPShader = pPShader;
	if (!obj->Create(m_pd3dDevice, m_pContext))
	{
		return false;
	}
	obj->SetCollisionType(CollisionType::Ignore, SelectType::Select_Ignore);
	I_UI.m_list.insert(std::make_pair(L"BackImage", obj));

	// UI


	return true;
}

bool GameScene::Init()
{
	return true;
}
bool GameScene::Load(std::wstring file)
{
	m_pBackImage = I_Texture.Load(L"../../data/map.jpg");

	for (int i = 0; i < 10; i++)
	{
		std::wstring name = L"../../data/";
		name += std::to_wstring(i);
		name += L".bmp";
		m_pChangeColorTex[i] = I_Texture.Load(name);
	}
	CreateModelType();

	// 배경
	Obj2D* pBackImage = I_UI.GetPtr(L"BackImage")->Clone();
	pBackImage->m_csName = L"ImageObj:BackImage";
	pBackImage->SetPosition(Vector2(952, 521));
	pBackImage->UpdateData();
	m_UIObj.push_back(std::shared_ptr<Obj2D>(pBackImage));

	// UI

	// 소리
	Sound* pSound = I_Sound.Load("../../data/Sound/stage.MP3");
	m_pBGM = I_Sound.Load("../../data/Sound/stage.MP3"); // bgm
	pSound = I_Sound.Load("../../data/Sound/dash.MP3");	
	pSound = I_Sound.Load("../../data/Sound/jump.MP3");
	pSound = I_Sound.Load("../../data/Sound/atk1.MP3");
	m_pBGM->Play(true);

	// 플레이어
	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(Vector2(400, 500));
	m_PlayerObj.SetRectSouce({ 53,40,42,56 });
	m_PlayerObj.SetRectDraw({ 0 ,675, 110, 144 });
	m_PlayerObj.m_csName = L"PlayerUser";	
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext, L"Shader.txt", L"../../data/skul/skul_little_bone_1.bmp", L"../../data/skul/skul_little_bone_2.bmp"))
	{
		return false;
	}
	
	// Npc - SwordMan 
	for (int iNpc = 0; iNpc < 1; iNpc++)
	{
		std::shared_ptr<ObjectNpc2D> npc = std::make_shared<ObjectNpc2D>();
		npc->m_csName = L"SwordMan";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(Vector2(50 + iNpc * 150, 50));
		if (iNpc % 1 == 0)
		{
			npc->SetRectSouce({ 0,0,32,56 });
			npc->SetRectDraw({ 0,630,86,151 });
		}
		else
		{
			npc->SetRectSouce({ 0,0,32,56 });
			npc->SetRectDraw({ 0,630,86,151 });
		}
		if (!npc->Create(m_pd3dDevice, m_pContext, L"Shader.txt", L"../../data/monster/SwordMan/Idle_1.bmp", L"../../data/monster/SwordMan/Idle_2.bmp"))
		{
			return false;
		}
		m_NpcObj.push_back(npc);
	}
	return true;
}
bool GameScene::Frame()
{	
	//// 공격
	//if (Input::Get().GetKey(X) == KEY_PUSH)
	//{
	//	Sound* pSound = I_Sound.GetPtr(L"atk1.MP3");
	//	if (pSound != nullptr)
	//	{
	//		pSound->PlayEffect();
	//	}
	//}
	//// 대쉬
	//if (Input::Get().GetKey(Z) == KEY_PUSH)
	//{
	//	Sound* pSound = I_Sound.GetPtr(L"dash.MP3");
	//	if (pSound != nullptr)
	//	{
	//		pSound->PlayEffect();
	//	}
	//}
	//// 점프
	//if (Input::Get().GetKey(C) == KEY_PUSH)
	//{
	//	Sound* pSound = I_Sound.GetPtr(L"jump.MP3");
	//	if (pSound != nullptr)
	//	{
	//		pSound->PlayEffect();
	//	}
	//}
	m_pBGM->Frame();

	// 볼륨 업&다운
	if (Input::Get().GetKey(VK_UP) == KEY_HOLD)
	{
		m_pBGM->VolumeUp(g_fSecPerFrame);
	}
	if (Input::Get().GetKey(VK_DOWN) == KEY_HOLD)
	{
		m_pBGM->VolumeDown(g_fSecPerFrame);
	}

	m_PlayerObj.Frame();
	World::Frame();
	return true;
}
bool GameScene::Render()
{		
	World::Render();
	m_PlayerObj.Render();
	return true;
}
bool GameScene::Release()
{
	m_PlayerObj.Release();
	
	return true;
}