#pragma once
#include "TCore.h"
#include "TFbxObj.h"
#include "TShape.h"
#include "TMap.h"

struct cbDataShadow
{
    TMatrix g_matShadow1; // Lw * Lv * Lp	
};
class TLight
{
public:
    TVector3    m_vPos;
    TVector3    m_vInitPos;
    TVector3    m_vTarget;
    TVector3    m_vDir;
    TMatrix     m_matWorld;
    TMatrix     m_matView;
    TMatrix     m_matProj;
public:
    void Set(TVector3    vPos, TVector3    vTarget)
    {
        m_vInitPos = vPos;
        m_vPos = vPos;
        m_vTarget = vTarget;
        m_vDir = m_vTarget - m_vPos;
        D3DXVec3Normalize(&m_vDir, &m_vDir);
        TVector3 vUp(0, 1, 0);
        D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProj, XM_PI * 0.25f, 1.0f, 1.0f, 500.0f);
    }
    bool Frame()
    {
        D3DXMatrixRotationY(&m_matWorld, XM_PI*g_fGameTimer*0.1f );
        D3DXVec3TransformCoord(&m_vPos, &m_vInitPos, &m_matWorld);
        m_vDir = m_vTarget - m_vPos;
        D3DXVec3Normalize(&m_vDir, &m_vDir);
        TVector3 vUp(0, 1, 0);
        D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProj, XM_PI * 0.25f, 1.0f, 1.0f, 500.0f);

        return true;
    }
};
class Sample : public TCore
{       
    TMatrix m_matTex;
    cbDataShadow m_ShadowCB;
    TLight m_Light1;
    TPlaneShape m_MapObj;
	TViewRT m_Rt;
	TFbxObj m_FbxCharacter;		
	TMatrix	m_matShadow;
	ID3D11PixelShader* m_pPSShadow = nullptr;
    ID3D11PixelShader* m_pPSShadowMap = nullptr;
    ID3D11Buffer* m_pShadowCB = nullptr;
public:
    HRESULT CreateConstantBuffer();
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
    Sample() {};
    virtual ~Sample() {};
};

