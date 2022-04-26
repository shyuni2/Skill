#pragma once
#include "SCore.h"
#include "SMap.h"
#include "SCamera.h"

class Sample : public SCore
{
public: 
	SMap m_MapObj;
	SCamera m_MainCamera;
	SCamera m_CameraTopView;
	SBoxObj m_BoxObj;

public: // 빛 & 그림자
	// 쉐이더
	SShader* m_pProjShadowVShader = nullptr;
	SShader* m_pProjShadowPShader = nullptr;
	// 빛
	SVector3 m_vLightPos; // 위치
	SVector3 m_vLightDir; // 거리
	// 행렬
	SMatrix m_matShadow; 
	SMatrix m_matViewLight;
	SMatrix m_matProjLight;
public:
	bool RenderMap(); // 맵 렌더링
	bool RenderMainCamera(); // 메인카메라 렌더링
	bool RenderObject(); // 오브젝트 렌더링
	void RenderShadow(SMatrix* matView, SMatrix* matProj); // 그림자 렌더링
public: // 윈도우 크기 변경 함수
	virtual void CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
public:
	Sample() {};
	~Sample() {};
};

