#pragma once
#include "SCore.h"
#include "SMap.h"
#include "SCamera.h"
#include "SDxRT.h"
#include "SBox.h"

class Sample : public SCore
{
public: 
	SMap m_MapObj;
	SBoxObj m_BoxObj;
	//std::vector<SBox> m_vBoxObj;
	SCamera m_MainCamera;
	//Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pPixelShader;
	SDxRT	  m_dxRT;
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
	void RenderProjectionShadow(SMatrix* matWorld, SMatrix* matShadow, SMatrix* matView, SMatrix* matProj); // �����׸��� ������
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


