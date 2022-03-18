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
	// ���� �̵�
	if (Input::Get().GetKey(LEFT) == KEY_HOLD)
	{
		Vector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame; // �ð��� ����ȭ
		AddPosition(pos);
	}
	// ������ �̵�
	if (Input::Get().GetKey(RIGHT) == KEY_HOLD)
	{
		Vector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	// z �뽬
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
			pos.x -= m_fSpeed * 2 * g_fSecPerFrame; // �ð��� ����ȭ
			AddPosition(pos);
		}
		if (Input::Get().GetKey(RIGHT) == KEY_HOLD)
		{
			Vector2 pos;
			pos.x += m_fSpeed * 2 * g_fSecPerFrame;
			AddPosition(pos);
		}
	}
	// c ����
	if (Input::Get().GetKey(C) == KEY_PUSH)
	{
		Sound* pSound = I_Sound.GetPtr(L"jump.MP3");
		if (pSound != nullptr)
		{
			pSound->PlayEffect();
		}
	}
	// x ����
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
	m_fSpeed = 200.0f; // �ӷ�
	m_dwCollisonType = CollisionType::Overlap;
	m_dwSelectType = SelectType::Select_Overlap;
}

PlayerObj2D::~PlayerObj2D()
{	

}