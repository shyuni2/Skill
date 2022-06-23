#pragma once
#include "SObj3D.h"

class SkyObj : public SObj3D
{
public:
	Math::Matrix m_matViewSky;
	STexture* m_pTexArray[6];
	STexture* m_pTexCube;
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

