#include "Sample.h"

bool Sample::RenderMap()
{
	m_MapObj.Init();
	m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 10.0f);
	if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"MapRT.hlsl", L"../../data/map/wetsand.bmp"))
	{
		return false;
	}


	return true;
}
void Sample::RenderShadow(SMatrix* matView, SMatrix* matProj)
{

}
void Sample::RenderObject(SMatrix* matWorld, SMatrix* matView, SMatrix* matProj)
{

}

void Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}


bool Sample::Init()
{
	RenderMap();
	return true;
}
bool Sample::Frame()
{
	return true;
}
bool Sample::Render()
{
	return true;
}
bool Sample::Release()
{
	return true;
}

RUN();