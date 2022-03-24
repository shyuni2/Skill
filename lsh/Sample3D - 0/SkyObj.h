#pragma once
#include "Obj3D.h"

class SkyObj : public Obj3D
{
public:
	Matrix m_matViewSky;
	Texture* m_pTexArray[6];
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

