#include "PlayerObj2D.h"
#include "Input.h"

bool PlayerObj2D::Frame()
{ 
	// w a s d 키보드 입력값
	if (Input::Get().GetKey('W') == KEY_HOLD)
	{
		Vector2 pos;
		// 시간의 동기화(유저마다 네트워크 환경이 다를수 있기 때문에 해줘야함)
		pos.y -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (Input::Get().GetKey('A') == KEY_HOLD)
	{
		Vector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (Input::Get().GetKey('S') == KEY_HOLD)
	{
		Vector2 pos;
		pos.y += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (Input::Get().GetKey('D') == KEY_HOLD)
	{
		Vector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	return true;
}
void PlayerObj2D::HitOverlap(BaseObject * pObj, DWORD dwState)
{
	if (dwState == CollisionType::Overlap)
	{
		pObj->m_bAlphaBlend = false; // 부딪히면 투명배경 꺼짐
	}
}

PlayerObj2D::PlayerObj2D()
{
	m_fSpeed = 300.0f; // 속력
}
PlayerObj2D::~PlayerObj2D()
{
	
}