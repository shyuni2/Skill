#pragma once
#include "SObj3D.h"

class SSkyObj : public SObj3D
{
public:	
	STexture* m_pTexArray[6]; // 텍스쳐 배열
	STexture* m_pTexCube; // 큐브 텍스쳐
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRVArray[6];
public:
	virtual void SetMatrix(S::SMatrix* matWorld,S::SMatrix* matView, S::SMatrix* matProj);
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
public:
	bool Render();
	bool PostRender();
public:
	SSkyObj();
	virtual ~SSkyObj();
};

