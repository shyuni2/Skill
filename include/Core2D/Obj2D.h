#pragma once
#include "DxObj.h"

class Obj2D : public DxObj
{
public:
	RECT m_rtSource;
	RECT m_rtDraw;	
	Vector4	m_vColor;
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:	
	virtual void SetRectSouce(RECT rt);
	virtual void SetRectDraw(RECT rt);
	virtual void AddPosition(Vector2 vPos);
	virtual void SetPosition(Vector2 vPos);		
	virtual void UpdateRectDraw(RECT rt);
public:
	virtual void Convert(Vector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList); // 화면좌표 위치를 중점으로 NDC 변환
	virtual void Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList); // 화면좌표계를 NDC 변환
	virtual void ConvertIndex(Vector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	virtual void ConvertIndex(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void  UpdateData() {};
public:
	Obj2D();
	virtual ~Obj2D();
};

