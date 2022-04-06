#pragma once
#include "Obj3D.h"

class SkyObj : public Obj3D
{
public:
	Math::Matrix m_matViewSky;
	Texture* m_pTexArray[6];
	Texture* m_pTexCube;
	Microsoft::WRL::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRVArray[6];
public:
	bool PostRender();
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
public:
	SkyObj();
	virtual ~SkyObj();
};

