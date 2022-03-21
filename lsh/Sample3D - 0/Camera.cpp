#include "Camera.h"
#include "Input.h"

bool Camera::Init()
{
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUP);
	m_matProj.PerspectiveFovLH(1.0f, 100.0f, BASIS_PI * 0.25, (float)g_rtClient.right/(float)g_rtClient.bottom);

	return true;
}
bool Camera::Frame()
{
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUP);

	return true;
}

Camera::Camera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 9.0f;
	m_vCamera.z = -15.0f;
	m_vUP = Vector3(0, 1, 0);
}