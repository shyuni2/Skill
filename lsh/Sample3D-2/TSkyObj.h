#pragma once
#include "Obj3D.h"
class TSkyObj : public Obj3D
{
public:
	T::TMatrix				m_matViewSky;
	Texture*			m_pTexArray[6];
	Texture*			m_pTexCube;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRVArray[6];
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	virtual bool		LoadTexture(const TCHAR* szColorFileName,
							const TCHAR* szMaskFileName);
	bool	PostRender();
public:
	TSkyObj();
	virtual ~TSkyObj();
};

