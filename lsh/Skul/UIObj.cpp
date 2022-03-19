#include "UIObj.h"
#include "World.h"
#include "SoundMgr.h"

bool UIObj::SetVertexData()
{
	//ConvertIndex(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	// 0  a   1     2  b   3
	// c  lt          rt
	// 4     5      6     7
	//              
	// 8     9     10    11
	// d lb           rb 
	// 12    13    14    15 
	Vector2 vLT = { (float)m_rtOffset.left,  (float)m_rtOffset.top };
	Vector2 vRT = { (float)m_rtOffset.right, (float)m_rtOffset.top };
	Vector2 vLB = { (float)m_rtOffset.left, (float)m_rtOffset.bottom };
	Vector2 vRB = { (float)m_rtOffset.right, (float)m_rtOffset.bottom };

	float fWidth = m_fWidth;
	float fHeight = m_fHeight;
	if (m_pColorTex != nullptr)
	{
		fWidth = m_pColorTex->m_TextureDesc.Width;
		fHeight = m_pColorTex->m_TextureDesc.Height;
	}
	Vector2 tLT = { vLT.x / fWidth, vLT.y / fHeight };
	Vector2 tRT = { vRT.x / fWidth, vRT.y / fHeight };
	Vector2 tLB = { vLB.x / fWidth, vLB.y / fHeight };
	Vector2 tRB = { vRT.x / fWidth, vRT.y / fHeight };	


	std::vector<SimpleVertex> list(16);
	float halfWidth = m_fWidth / 2.0f;
	float halfHeight = m_fHeight / 2.0f;
	list[0].v = { m_vPos.x - halfWidth, m_vPos.y - halfHeight };
	list[0].t = { (float)m_rtOffsetTex.left,(float)m_rtOffsetTex.top };
	list[3].v = { m_vPos.x + halfWidth, m_vPos.y - halfHeight };
	list[3].t = { (float)m_rtOffsetTex.right,(float)m_rtOffsetTex.top };
	list[12].v = { m_vPos.x - halfWidth, m_vPos.y + halfHeight };
	list[12].t = { (float)m_rtOffsetTex.left,(float)m_rtOffsetTex.bottom };
	list[15].v = { m_vPos.x + halfWidth, m_vPos.y + halfHeight };
	list[15].t = { (float)m_rtOffsetTex.right,(float)m_rtOffsetTex.bottom };
	list[5].v = { list[0].v.x + vLT.x, list[0].v.y + vLT.y };
	list[5].t = { list[0].t.x + tLT.x, list[0].t.y + tLT.y };
	list[6].v = { list[3].v.x - vRT.x, list[3].v.y + vRT.y };
	list[6].t = { list[3].t.x - tRT.x, list[3].t.y + tRT.y };
	list[9].v = { list[12].v.x + vLB.x, list[12].v.y - vLB.y };
	list[9].t = { list[12].t.x + tLB.x, list[12].t.y - tLB.y };
	list[10].v = { list[15].v.x - vRB.x, list[15].v.y - vRB.y };
	list[10].t = { list[15].t.x - tRB.x, list[15].t.y - tRB.y };
	
	list[1].v = { list[5].v.x, list[0].v.y };
	list[1].t = { list[5].t.x, list[0].t.y };
	list[2].v = { list[6].v.x, list[3].v.y };
	list[2].t = { list[6].t.x, list[3].t.y };

	list[4].v = { list[0].v.x, list[5].v.y };
	list[4].t = { list[0].t.x, list[5].t.y };
	list[7].v = { list[3].v.x, list[6].v.y };
	list[7].t = { list[3].t.x, list[6].t.y };

	list[8].v = { list[12].v.x, list[9].v.y };
	list[8].t = { list[12].t.x, list[9].t.y };
	list[11].v = { list[15].v.x, list[10].v.y };
	list[11].t = { list[15].t.x, list[10].t.y };

	list[13].v = { list[9].v.x, list[12].v.y };
	list[13].t = { list[9].t.x, list[12].t.y };
	list[14].v = { list[10].v.x, list[15].v.y };
	list[14].t = { list[10].t.x, list[15].t.y };

	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 -> 0 ~ 1 -> -1 ~ +1
		list[i].v.x = list[i].v.x / g_rtClient.right;
		list[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 -> -1 ~ +1 :::: -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1;  ::::  x= x * 0.5f + 0.5f;
		list[i].v.x = list[i].v.x * 2.0f - 1.0f;
		list[i].v.y = -1.0f * (list[i].v.y * 2.0f - 1.0f);
	}
	m_VertexList = list;
	return true;
}
bool UIObj::SetIndexData()
{
	m_IndexList.clear();
	// 0  a   1     2  b   3
	// c  lt          rt
	// 4     5      6     7
	//              
	// 8     9     10    11
	// d lb           rb 
	// 12    13    14    15 
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(4);
	m_IndexList.push_back(4); m_IndexList.push_back(1); m_IndexList.push_back(5);
	m_IndexList.push_back(1); m_IndexList.push_back(2); m_IndexList.push_back(5);
	m_IndexList.push_back(5); m_IndexList.push_back(2); m_IndexList.push_back(6);
	m_IndexList.push_back(2); m_IndexList.push_back(3); m_IndexList.push_back(6);
	m_IndexList.push_back(6); m_IndexList.push_back(3); m_IndexList.push_back(7);

	m_IndexList.push_back(4); m_IndexList.push_back(5); m_IndexList.push_back(8);
	m_IndexList.push_back(8); m_IndexList.push_back(5); m_IndexList.push_back(9);
	m_IndexList.push_back(5); m_IndexList.push_back(6); m_IndexList.push_back(9);
	m_IndexList.push_back(9); m_IndexList.push_back(6); m_IndexList.push_back(10);
	m_IndexList.push_back(6); m_IndexList.push_back(7); m_IndexList.push_back(10);
	m_IndexList.push_back(10); m_IndexList.push_back(7); m_IndexList.push_back(11);


	m_IndexList.push_back(8); m_IndexList.push_back(9); m_IndexList.push_back(12);
	m_IndexList.push_back(12); m_IndexList.push_back(9); m_IndexList.push_back(13);
	m_IndexList.push_back(9); m_IndexList.push_back(10); m_IndexList.push_back(13);
	m_IndexList.push_back(13); m_IndexList.push_back(10); m_IndexList.push_back(14);
	m_IndexList.push_back(10); m_IndexList.push_back(11); m_IndexList.push_back(14);
	m_IndexList.push_back(14); m_IndexList.push_back(11); m_IndexList.push_back(15);

	return true;
}
bool UIObj::Frame()
{
	Obj2D::Frame();
	return true;
}
bool UIObj::Render()
{
	Obj2D::Render();
	return true;
}
bool ImageObj::Init()
{
	m_bFadeIn = true;
	return true;
}
bool ImageObj::Frame()
{
	m_vColor.x = m_fAlpha;
	m_vColor.y = m_fAlpha;
	m_vColor.z = m_fAlpha;
	m_vColor.w = 1.0f;
	Obj2D::Frame();	
	return true;
}
bool ImageObj::Render()
{
	Obj2D::Render();
	return true;
}
bool ButtonObj::Init()
{
	//m_bFadeIn = true;
	return true;
}
bool ButtonObj::Frame()
{
	Obj2D::Frame();
	return true;
}
bool ButtonObj::Render()
{
	Obj2D::Render();
	return true;
}
void ButtonObj::HitSelect(BaseObj* pObj, DWORD dwState)
{
	std::string state;
	if (m_dwPreSelectState == m_dwSelectState)
	{
		return;
	}
	if (m_pStatePlayList.size() <= 0) return;

	switch (m_dwSelectState)
	{
		case SelectState::DEFAULT:
		{
			if (m_pStatePlayList[0].pTex == nullptr) break;
			m_pColorTex = m_pStatePlayList[0].pTex;			
			state += "DEFAULT\n";
		}break;

		case SelectState::SELECTED: 
		{
			if (m_pStatePlayList[3].pTex == nullptr) break;
			m_pColorTex = m_pStatePlayList[3].pTex;
			m_pStatePlayList[3].pSound->PlayEffect();
			World::m_pWorld->m_bLoadZone = true;
			state += "SELECTED\n";
		}break;
		case SelectState::HOVER: 
		{
			if (m_pStatePlayList[1].pTex == nullptr) break;
			m_pColorTex = m_pStatePlayList[1].pTex;
			m_pStatePlayList[1].pSound->PlayEffect();

			//state += "HOVER\n";
		}break;
		case SelectState::ACTIVE:
		{
			if (m_pStatePlayList[2].pTex == nullptr) break;
			m_pColorTex = m_pStatePlayList[2].pTex;
			m_pStatePlayList[2].pSound->PlayEffect();
			state += "ACTIVE\n";
		}break;
		case SelectState::FOCUS: 
		{
			if (m_pStatePlayList[2].pTex == nullptr) break;
			m_pColorTex = m_pStatePlayList[2].pTex;
			m_pStatePlayList[2].pSound->PlayEffect();
			//state += "FOCUS\n";
		}break;
		default:
		{
			state += std::to_string(m_dwSelectState);
		}
	}	
	m_dwPreSelectState = m_dwSelectState;
	//DisplayText(state.c_str());
}

bool ListCtrlObj::Create(int xCount, int yCount)
{
	UpdateData();

	int iHalfWidth  = m_fWidth / xCount;
	int iHalfHeight = m_fHeight / yCount;
	Vector2 pStart = { (float)m_rtDraw.left, (float)m_rtDraw.top };
	pStart.x += m_fWidth / xCount / 2.0f;
	pStart.y += m_fHeight / yCount / 2.0f;
	for (int iCol = 0; iCol < xCount; iCol++)
	{
		for (int iRow = 0; iRow < yCount; iRow++)
		{
			UIModel* pNewBtn = I_UI.GetPtr(L"IntroStart")->Clone();
			pNewBtn->m_pParent = this;
			pNewBtn->m_csName = L"Btn";
			pNewBtn->m_csName += std::to_wstring(iRow* yCount+ iCol);
			pNewBtn->SetRectDraw({ 0,0, iHalfWidth,iHalfHeight });
			pNewBtn->SetPosition(Vector2(pStart.x + iHalfWidth * iCol, pStart.y + iHalfHeight * iRow));
			pNewBtn->UpdateData();
			Add(pNewBtn);
		}
	}
	return true;
}
void ListCtrlObj::HitSelect(BaseObj* pObj, DWORD dwState)
{
	std::string state="\n";
	if (m_dwPreSelectState == m_dwSelectState)
	{		
		return;
	}
	m_dwPreSelectState = m_dwSelectState;	
	state = std::to_string(m_dwSelectState);
	DisplayText(state.c_str());
}