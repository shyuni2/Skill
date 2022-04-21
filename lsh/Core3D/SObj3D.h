#pragma once
#include "SDxObj.h"

class SObj3D : public SDxObj
{
public:
	S::SVector3 m_vPos; // ��ġ
	S::SVector3 m_vDirection; // �Ÿ�
	S::SVector4 m_vColor; // ��
public:		    
	S::SMatrix m_matWorld; // �������
	S::SMatrix m_matView; // �����
	S::SMatrix m_matProj; // �������
public:		    
	S::SVector3 m_vLight; // x	
	S::SVector3 m_vUp; // y 
	S::SVector3 m_vLook; // z
public:
	// ���̵� �� �ƿ� : ����� ���۵ɶ� �������̳� ������� ������ ��Ÿ�����ϴ� ���
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(S::SVector3 vPos);
	virtual void SetPosition(S::SVector3 vPos);	
public:			 
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void SetMatrix(S::SMatrix* matWorld, S::SMatrix* matView, S::SMatrix* matProj);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
	virtual bool Frame() override;
	virtual void UpdateData();
	virtual void UpdateCollision();
	virtual void GenAABB();
public:
	SObj3D();
	virtual ~SObj3D();
};

