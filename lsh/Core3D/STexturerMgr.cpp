#include "STextureMgr.h"
bool	STexture::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		pd3dDevice,
		filename.c_str(),
		(ID3D11Resource**)m_pTexture.GetAddressOf(),
		m_pSRV.GetAddressOf());
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			pd3dDevice,
			filename.c_str(),
			(ID3D11Resource**)m_pTexture.GetAddressOf(),
			m_pSRV.GetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}
	}
	m_pTexture->GetDesc(&m_TextureDesc);
	return true;
}
bool	STexture::Init()
{
	return true;
}
bool	STexture::Frame()
{	
	return true;
}
bool	STexture::Render()
{
	return true;
}
bool	STexture::Release()
{
	return true;
}
STexture::STexture()
{

}
STexture::~STexture()
{

}

