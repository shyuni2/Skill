#include "SCamera.h"
#include "SInput.h"

// -- 轰青纺 积己
void SCamera::CreateViewMatrix(S::SVector3 p, S::SVector3 t, S::SVector3 u)
{
	m_vCamera = p;
	m_vTarget = t;
	m_vUp = u;
	S::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vUp);	
	S::SMatrix mInvView;
	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	SVector3* pZBasis = (SVector3*)&mInvView._31;
	m_fYaw = atan2f(pZBasis->x, pZBasis->z);
	float fLen = sqrtf(pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x);
	m_fPitch = -atan2f(pZBasis->y, fLen);
	UpdateVector();
}

// -- 捧康青纺 积己
void SCamera::CreateProjMatrix(float fovy, float Aspect, float zn, float zf)
{
	m_fFarDistance = zf;
	m_fNearDistance = zn;
	S::D3DXMatrixPerspectiveFovLH(&m_matProj, fovy, Aspect, zn, zf);
}

bool SCamera::Init()
{
	SFrustum::Init();
	CreateViewMatrix(m_vCamera, m_vTarget, m_vUp);
	CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	UpdateVector();	
	return true;
}

bool SCamera::Update(S::SVector4 vDirValue)
{
	// vValue.x : pitch, y=yaw, z= roll, w =radius

	m_fPitch += vDirValue.x;
	m_fYaw += vDirValue.y;
	m_fRoll += vDirValue.z;

	S::SMatrix matRotation;
	S::D3DXQuaternionRotationYawPitchRoll(&m_qRotation, m_fYaw, m_fPitch, m_fRoll);

	m_vCamera += m_vLook * vDirValue.w;
	m_fRadius += vDirValue.w;

	S::D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL, &m_qRotation, &m_vCamera);
	S::D3DXMatrixInverse(&m_matView, NULL, &matRotation);

	return UpdateVector();
}
bool SCamera::UpdateVector()
{
	m_vRight.x = m_matView._11;
	m_vRight.y = m_matView._21;
	m_vRight.z = m_matView._31;

	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;

	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	CreateFrustum(m_matView, m_matProj);
	return true;
}
void SCamera::MoveLook(float fValue)
{
	m_vCamera += m_vLook * fValue;
}
void SCamera::MoveSide(float fValue)
{
	m_vCamera += m_vRight * fValue;
}
void SCamera::MoveUp(float fValue)
{
	m_vCamera += m_vUp * fValue;
}
bool SCamera::Frame()
{
	S::SVector2 dir = SInput::Get().GetDelta();
	if (SInput::Get().GetKey('A') || SInput::Get().GetKey(VK_LEFT))
	{
		MoveSide(-g_fSecPerFrame * 100.0f);
	}
	if (SInput::Get().GetKey('D') || SInput::Get().GetKey(VK_RIGHT))
	{
		MoveSide(g_fSecPerFrame * 100.0f);
	}
	//m_Camera.MoveLook(10.0f);
	if (SInput::Get().GetKey('W'))
	{
		MoveLook(g_fSecPerFrame * 100.0f);
	}
	if (SInput::Get().GetKey('S') || SInput::Get().GetKey(VK_DOWN))
	{
		MoveLook(-g_fSecPerFrame * 100.0f);
	}

	Update(S::SVector4(-dir.x, -dir.y, 0, 0));
	return true;
}
SCamera::SCamera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 0.0f;
	m_vCamera.z = 0.0f;

	m_vTarget.x = 0;
	m_vTarget.y = 0;
	m_vTarget.z = 100;

	m_vUp = m_vDefaultUp = S::SVector3(0, 1, 0);
}