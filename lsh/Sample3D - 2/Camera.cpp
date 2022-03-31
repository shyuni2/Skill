#include "Camera.h"
#include "Input.h"


void Camera::CreateViewMatrix(T::Vector3 p, T::Vector3 t, T::Vector3 u)
{
	m_vCamera = p;
	m_vTarget = t;
	m_vUp = u;
	T::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vUp);	
	UpdateVector();
}
void Camera::CreateProjMatrix(float fovy, float Aspect, float zn, float zf)
{
	T::D3DXMatrixPerspectiveFovLH(&m_matProj, fovy, Aspect, zn, zf);
}
bool Camera::Init()
{
	Frustum::Init();
	CreateViewMatrix(m_vCamera, m_vTarget, m_vUp);
	CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	UpdateVector();	
	return true;
}
// vValue.x : pitch, y=yaw, z= roll, w =radius
bool Camera::Update(T::Vector4 vDirValue)
{
	T::Matrix matRotation;
	T::D3DXQuaternionRotationYawPitchRoll(&m_qRotation, vDirValue.y, vDirValue.x, vDirValue.z);

	m_vCamera += m_vLook * vDirValue.w;
	m_fRadius += vDirValue.w;

	T::D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL, &m_qRotation, &m_vCamera);
	T::D3DXMatrixInverse(&m_matView, NULL, &matRotation);

	return UpdateVector();
}
bool Camera::UpdateVector()
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
void Camera::MoveLook(float fValue)
{
	m_vCamera += m_vLook * fValue;
}
void Camera::MoveSide(float fValue)
{
	m_vCamera += m_vRight * fValue;
}
void Camera::MoveUp(float fValue)
{
	m_vCamera += m_vUp * fValue;
}
bool Camera::Frame()
{
	/*if (Input::Get().GetKey(VK_LEFT))
	{
		m_vCamera.z -= g_fSecPerFrame * 1.0f;
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		m_vCamera.z += g_fSecPerFrame * 1.0f;
	}
	if (Input::Get().GetKey(VK_UP))
	{
		m_vCamera.y += g_fSecPerFrame * 1.0f;
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
		m_vCamera.y -= g_fSecPerFrame * 1.0f;
	}*/
	T::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vDefaultUp);
	return UpdateVector();
}
Camera::Camera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 0.0f;
	m_vCamera.z = 0.0f;
	m_vTarget.x = 0;
	m_vTarget.y = 0;
	m_vTarget.z = 100;
	m_vUp = m_vDefaultUp = T::Vector3(0, 1, 0);
}