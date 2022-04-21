#include "SDxObj.h"
#include "SObjMgr.h"

void SBaseObj::HitOverlap(SBaseObj* pObj, DWORD dwState)
{

}
void SBaseObj::HitSelect(SBaseObj* pObj, DWORD dwState)
{
	int k = 0;
}
void SDxObj::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}
bool SDxObj::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	m_pColorTex = I_Texture.Load(szColorFileName);
	if (szMaskFileName != nullptr)
	{
		m_pMaskTex = I_Texture.Load(szMaskFileName);
	}
	m_TextureDesc = m_pColorTex->m_TextureDesc;
	return true;
}
bool SDxObj::SetVertexData()
{
	return true;
}
bool SDxObj::SetIndexData()
{
	return true;
}
bool SDxObj::SetConstantData()
{
	ZeroMemory(&m_ConstantList, sizeof(ConstantData));
	m_ConstantList.matWorld = S::SMatrix();
	m_ConstantList.matView = S::SMatrix();
	m_ConstantList.matProj = S::SMatrix();

	m_ConstantList.Color.x = 0.0f;
	m_ConstantList.Color.y = 1.0f;
	m_ConstantList.Color.z = 0.0f;
	m_ConstantList.Color.w = 1.0f;

	m_ConstantList.Timer.x = 0.0f;
	m_ConstantList.Timer.y = 1.0f;
	m_ConstantList.Timer.z = 0.0f;
	m_ConstantList.Timer.w = 0.0f;

	ZeroMemory(&m_LightConstantList, sizeof(LightData));
	m_LightConstantList.vLightDir.x = 0.0f;
	m_LightConstantList.vLightDir.y = 1.0f;
	m_LightConstantList.vLightDir.z = 0.0f;
	m_LightConstantList.vLightDir.w = 1.0f;

	m_LightConstantList.vLightPos.x = 0.0f;
	m_LightConstantList.vLightPos.y = 1.0f;
	m_LightConstantList.vLightPos.z = 0.0f;
	m_LightConstantList.vLightPos.w = 0.0f;

	return true;
}
bool SDxObj::CreateVertexShader(const TCHAR* szFile)
{
	m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, szFile, "VS");
	return true;
}
bool SDxObj::CreatePixelShader(const TCHAR* szFile)
{
	m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, szFile, "PS");
	return true;
}
bool SDxObj::CreateVertexBuffer()
{
	if (m_VertexList.size() <= 0) return false;
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(Vertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}
	return true;
}
bool SDxObj::CreateIndexBuffer()
{
	HRESULT hr;
	if (m_IndexList.size() <= 0) return true;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_IndexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
	{
		return false;
	}
	return true;
}
bool SDxObj::CreateConstantBuffer()
{
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ConstantData);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_ConstantList;

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer)))
	{
		return false;
	}
	
	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pLightConstantBuffer)))
	{
		return false;
	}
	return true;
}
bool SDxObj::CreateInputLayout()
{
	// 정점 구조체를 정의했다면 그 구조체의 각 성분이 어떤 용도인지 Direct3D에 알려줘야한다
	// 그 수단이 Input Layout 객체
	// Input Layout 객체는 D3D11_INPUT_ELEMENT_DESC구조체로 이루어진 배열을 통해 구축한다
	// 정점쉐이더의 결과를 통해서 정점레이아웃을 생성한다
	// 정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL",0, DXGI_FORMAT_R32G32B32_FLOAT, 0,12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0,40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pd3dDevice->CreateInputLayout(layout, NumElements, m_pVShader->m_pVSCodeResult->GetBufferPointer(), m_pVShader->m_pVSCodeResult->GetBufferSize(), &m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool SDxObj::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, const TCHAR* szShaderFileName, const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	HRESULT hr;
	SetDevice(pd3dDevice, pContext);
	if (szColorFileName !=nullptr && !LoadTexture(szColorFileName, szMaskFileName))
	{
		return false;
	}
	if (!SetVertexData())
	{
		return false;
	}
	if (!SetIndexData())
	{
		return false;
	}
	if (!SetConstantData())
	{
		return false;
	}
	if (!CreateVertexBuffer())
	{
		return false;
	}
	if (!CreateIndexBuffer())
	{
		return false;
	}
	if (!CreateConstantBuffer())
	{
		return false;
	}
	if (szShaderFileName!= nullptr && 
		!CreateVertexShader(szShaderFileName))
	{
		return false;
	}
	if (szShaderFileName != nullptr &&
		!CreatePixelShader(szShaderFileName))
	{
		return false;
	}
	if (!CreateInputLayout())
	{
		return false;
	}
	return true;
}
bool SDxObj::Init()
{	
	return true;
}
bool SDxObj::Frame()
{
	return true;
}
bool SDxObj::Render()
{	
	PreRender();

	m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);

	m_pContext->GSSetShader(nullptr, NULL, 0);
	m_pContext->HSSetShader(nullptr, NULL, 0);
	m_pContext->DSSetShader(nullptr, NULL, 0);
	if (m_pVShader != nullptr)
	{
		m_pContext->VSSetShader(m_pVShader->m_pVertexShader, NULL, 0);
	}
	if (m_pPShader != nullptr)
	{
		m_pContext->PSSetShader(m_pPShader->m_pPixelShader, NULL, 0);
	}

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(SDxState::m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(SDxState::m_AlphaBlendDisable, 0, -1);
	}

	m_pContext->IASetInputLayout(m_pVertexLayout);	

	UINT Strides = sizeof(Vertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	PostRender();	
	return true;
}
bool SDxObj::PreRender()
{
	if (m_pColorTex != nullptr)
	{
		m_pContext->PSSetShaderResources(0, 1, m_pColorTex->m_pSRV.GetAddressOf());
	}
		
	if (m_pMaskTex != nullptr)
	{
		m_pContext->PSSetShaderResources(1, 1, m_pMaskTex->m_pSRV.GetAddressOf());
	}
		
	return true;
}
bool SDxObj::Draw()
{
	m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
	m_pContext->UpdateSubresource(m_pLightConstantBuffer, 0, NULL, &m_LightConstantList, 0, 0);

	m_pContext->GSSetShader(nullptr, NULL, 0);
	m_pContext->HSSetShader(nullptr, NULL, 0);
	m_pContext->DSSetShader(nullptr, NULL, 0);
	if (m_pVShader != nullptr)
	{
		m_pContext->VSSetShader(m_pVShader->m_pVertexShader, NULL, 0);
	}
	if (m_pPShader != nullptr)
	{
		m_pContext->PSSetShader(m_pPShader->m_pPixelShader, NULL, 0);
	}

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(SDxState::m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(SDxState::m_AlphaBlendDisable, 0, -1);
	}

	m_pContext->IASetInputLayout(m_pVertexLayout);

	UINT Strides = sizeof(Vertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext->VSSetConstantBuffers(1, 1, &m_pLightConstantBuffer);
	m_pContext->PSSetConstantBuffers(1, 1, &m_pLightConstantBuffer);

	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}
bool SDxObj::PostRender()
{
	if (m_IndexList.size() <= 0)
	{
		m_pContext->Draw(m_VertexList.size(), 0);
	}
	else
	{
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
	}
		
	return true;
}
bool SDxObj::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();	
	if (m_pVertexLayout) m_pVertexLayout->Release();
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVertexLayout = nullptr;
	return true;
}
SDxObj::SDxObj()
{
	m_fSpeed = 0.0001f;
}
SDxObj::~SDxObj()
{

}
