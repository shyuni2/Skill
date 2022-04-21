#pragma once
#include "SDxObj.h"

class SObj2D : public SDxObj
{
public:
	std::vector<SimpleVertex> m_VertexList2D;
	RECT m_rtSource;
	RECT m_rtDraw;	
public:
	S::SVector4 m_vColor;
	S::SVector2 m_vPos;
	S::SVector2 m_vDirection;
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:	
	virtual void SetRectSouce(RECT rt);
	virtual void SetRectDraw(RECT rt);
	virtual void AddPosition(S::SVector2 vPos);
	virtual void SetPosition(S::SVector2 vPos);		
	virtual void UpdateRectDraw(RECT rt);
public:
	virtual void Convert(S::SVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);	// 화면좌표 위치를 중점으로 NDC 변환
	virtual void Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList); // 화면좌표계를 NDC 변환
	virtual void ConvertIndex(S::SVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList); // 화면좌표계를 NDC 변환
	virtual void ConvertIndex(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList); // 화면좌표계를 NDC 변환
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void  UpdateData() {}
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
public:
	SObj2D();
	virtual ~SObj2D();
};

