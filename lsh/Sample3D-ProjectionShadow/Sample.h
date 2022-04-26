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

public: // �� & �׸���
	// ���̴�
	SShader* m_pProjShadowVShader = nullptr;
	SShader* m_pProjShadowPShader = nullptr;
	// ��
	SVector3 m_vLightPos; // ��ġ
	SVector3 m_vLightDir; // �Ÿ�
	// ���
	SMatrix m_matShadow; 
	SMatrix m_matViewLight;
	SMatrix m_matProjLight;
public:
	bool RenderMap(); // �� ������
	bool RenderMainCamera(); // ����ī�޶� ������
	bool RenderObject(); // ������Ʈ ������
	void RenderShadow(SMatrix* matView, SMatrix* matProj); // �׸��� ������
public: // ������ ũ�� ���� �Լ�
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

