#include "PlayerObj2D.h"
#include "Input.h"

bool PlayerObj2D::Frame()
{ 
	// w a s d Ű���� �Է°�
	if (Input::Get().GetKey('W') == KEY_HOLD)
	{
		Vector2 pos;
		// �ð��� ����ȭ(�������� ��Ʈ��ũ ȯ���� �ٸ��� �ֱ� ������ �������)
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
		pObj->m_bAlphaBlend = false; // �ε����� ������ ����
	}
}

PlayerObj2D::PlayerObj2D()
{
	m_fSpeed = 300.0f; // �ӷ�
}
PlayerObj2D::~PlayerObj2D()
{
	
}