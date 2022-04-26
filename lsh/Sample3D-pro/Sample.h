#pragma once
#include "SCore.h"
#include "SMap.h"
#include "SCamera.h"
#include "SFbxObj.h"

class Sample : public SCore
{
public: // ������Ʈ
	SMap m_MapObj;
public: // ������ ����
	// ���̴�
	SShader* m_pProjShadowVShader = nullptr;
	SShader* m_pProjShadowPShader = nullptr;
	// ��
	SVector3 m_vLightPos;
	SVector3 m_vLightDir;
	// ���
	SMatrix m_matShadow;
	SMatrix m_matViewLight;
	SMatrix m_matProjLight;
public:
	bool RenderMap(); // �� ������
	void RenderShadow(SMatrix* matView, SMatrix* matProj); // �׸��� ������
	void RenderObject(SMatrix* matWorld, SMatrix* matView, SMatrix* matProj); // ������Ʈ ������
public: // ������ ũ�� ���� �Լ�
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

