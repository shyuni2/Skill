#pragma once
#include "SObj3D.h"

class SSkyObj : public SObj3D
{
public:	
	STexture* m_pTexArray[6]; // �ؽ��� �迭
	STexture* m_pTexCube; // ť�� �ؽ���
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

