#include "PlayerObj2D.h"
#include "Input.h"

void PlayerObj2D::HitOverlap(BaseObj* pObj, DWORD dwState)
{
	if (dwState == CollisionType::Overlap)
	{
		//pObj->m_bAlphaBlend = false;
	}	
}
bool PlayerObj2D::Frame()
{
	// 왼쪽 이동
	if (Input::Get().GetKey(LEFT) == KEY_HOLD)
	{
		Vector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame; // 시간의 동기화
		AddPosition(pos);
	}
	// 오른쪽 이동
	if (Input::Get().GetKey(RIGHT) == KEY_HOLD)
	{
		Vector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	// z 대쉬
	if (Input::Get().GetKey(Z) == KEY_HOLD)
	{
		Sound* pSound = I_Sound.GetPtr(L"dash.MP3");
		if (pSound != nullptr)
		{
			pSound->PlayEffect();
		}

		if (Input::Get().GetKey(LEFT) == KEY_HOLD)
		{
			Vector2 pos;
			pos.x -= m_fSpeed * 2 * g_fSecPerFrame; // 시간의 동기화
			AddPosition(pos);
		}
		if (Input::Get().GetKey(RIGHT) == KEY_HOLD)
		{
			Vector2 pos;
			pos.x += m_fSpeed * 2 * g_fSecPerFrame;
			AddPosition(pos);
		}
	}
	// c 점프
	if (Input::Get().GetKey(C) == KEY_PUSH)
	{
		Sound* pSound = I_Sound.GetPtr(L"jump.MP3");
		if (pSound != nullptr)
		{
			pSound->PlayEffect();
		}
	}
	// x 공격
	if (Input::Get().GetKey(X) == KEY_PUSH)
	{
		Sound* pSound = I_Sound.GetPtr(L"atk1.MP3");
		if (pSound != nullptr)
		{
			pSound->PlayEffect();
		}
	}

	return true;
}
PlayerObj2D::PlayerObj2D()
{
	m_fSpeed = 200.0f; // 속력
	m_dwCollisonType = CollisionType::Overlap;
	m_dwSelectType = SelectType::Select_Overlap;
}

PlayerObj2D::~PlayerObj2D()
{	

}