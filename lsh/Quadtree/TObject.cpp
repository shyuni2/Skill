#include "TObject.h"


// ������ ��ġ
void   TObject::SetPos(SVector2 pos)
{
	m_vPos = pos;
}

// x,y ��ġ
void   TObject::SetPos(float x, float y)
{
	m_vPos.x = x;
	m_vPos.y = y;
}

// �簢���� ��ġ
void   TObject::SetRect(TRect rt)
{
	m_rt = rt;
}