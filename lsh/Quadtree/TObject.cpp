#include "TObject.h"


// 벡터의 위치
void   TObject::SetPos(SVector2 pos)
{
	m_vPos = pos;
}

// x,y 위치
void   TObject::SetPos(float x, float y)
{
	m_vPos.x = x;
	m_vPos.y = y;
}

// 사각형의 위치
void   TObject::SetRect(TRect rt)
{
	m_rt = rt;
}