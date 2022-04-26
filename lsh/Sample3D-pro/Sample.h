#pragma once
#include "SCore.h"
#include "SMap.h"
#include "SCamera.h"
#include "SFbxObj.h"

class Sample : public SCore
{
public: // 오브젝트
	SMap m_MapObj;
public: // 쉐도우 관련
	// 쉐이더
	SShader* m_pProjShadowVShader = nullptr;
	SShader* m_pProjShadowPShader = nullptr;
	// 빛
	SVector3 m_vLightPos;
	SVector3 m_vLightDir;
	// 행렬
	SMatrix m_matShadow;
	SMatrix m_matViewLight;
	SMatrix m_matProjLight;
public:
	bool RenderMap(); // 맵 렌더링
	void RenderShadow(SMatrix* matView, SMatrix* matProj); // 그림자 렌더링
	void RenderObject(SMatrix* matWorld, SMatrix* matView, SMatrix* matProj); // 오브젝트 렌더링
public: // 윈도우 크기 변경 함수
	virtual void CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
public:
	Sample();
	~Sample();
};

