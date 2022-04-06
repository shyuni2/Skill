#pragma once
#include "Obj3D.h"

class SkyObj : public Obj3D
{
public:	
	Texture*			m_pTexArray[6];
	Texture*			m_pTexCube;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRVArray[6];
public:
	virtual void		SetMatrix(T::TMatrix* matWorld,T::TMatrix* matView, T::TMatrix* matProj);
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	virtual bool		LoadTexture(const TCHAR* szColorFileName,
							const TCHAR* szMaskFileName);
	bool	Render();
	bool	PostRender();
public:
	SkyObj();
	virtual ~SkyObj();
};

