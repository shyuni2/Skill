#include "TDxObject.h"

void TDxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pCOntext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pCOntext;
}

// ȭ����ǥ ��ġ�� �������� NDC��ȯ�ϴ� �������Լ�
void TDxObject::Convert(TVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList)
{
	// �簢���� ������� �ﰢ���� �ΰ� �پ����
	// 0         1,4
	//
	// 2,3       5          �ð�������� ���ư�
	// ����� ��� �ø��� �����ؾ��Ұ��� �������ϱ� ���ͷ� ���� 
	// ���ʹ� �������� �迭��, ���Ḯ��Ʈ�� �����ͷ� ����ؼ� �����ؾ��ϴϱ� �ȵ�
	vector<SimpleVertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;
	list[0].v = { center.x - halfWidth,center.y - halfHeight };
	list[1].v = { center.x + halfWidth,center.y - halfHeight }; // 1���� ���θ� ������
	list[2].v = { center.x - halfWidth,center.y + halfHeight }; // 2���� ���θ� ������
	list[3].v = list[2].v;
	list[4].v = list[1].v; // 3,4 �� 2,1�� �����ϱ�
	list[5].v = { center.x + halfWidth,center.y + halfHeight }; // 5���� ���� ���� ������

	Convert(list, retList);
}

// ȭ����ǥ�踦 NDC�� ��ȯ
void TDxObject::Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 �� ��ǥ�� 0 ~ 1 ���� ��ȯ
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 ��ǥ�� -1 ~ +1 �� ��ȯ ::: -1 ~ +1 ��ǥ�� 0 ~ 1��ǥ�� ��ȯ , �Ѵ� �Ǿ����
		// x = x * 2 - 1				::: x = x * 0.5f + 0.5f
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
}

// ������Ʈ �����
bool TDxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, TVector2 vPos, float fWidth, float fHeight)
{
	// ȭ������� �������� ����
	if ((vPos.x - fWidth / 2.0f) < 0) return false;
	if ((vPos.x + fWidth / 2.0f) > g_rtClient.right) return false;
	if ((vPos.y - fWidth / 2.0f) < 0) return false;
	if ((vPos.y + fWidth / 2.0f) > g_rtClient.bottom) return false;

	SetDevice(pd3dDevice, pContext);
	HRESULT hr;
	// ui�� ���
	m_InitScreenList.resize(6); // ���� ���� 6���ϱ�
	m_InitScreenList[0].v = TVector2(0.0f, 0.0f);
	m_InitScreenList[1].v = TVector2(fWidth, 0.0f);
	m_InitScreenList[2].v = TVector2(0.0f, fHeight);
	m_InitScreenList[3].v = TVector2(0.0f, fHeight);
	m_InitScreenList[4].v = TVector2(fWidth, 0.0f);
	m_InitScreenList[5].v = TVector2(fWidth, fHeight);

	m_vPos = vPos;
	Convert(m_vPos, fWidth, fHeight, m_VertexList);

	//gpu �޸𸮿� ���� �Ҵ� (���ϴ� �Ҵ� ũ��)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC)); // ZeroMemory (0���� ä�� �޸� ���� �����ּ�, 0���� ä�� ũ��)
	bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA)); // ZeroMemory (0���� ä�� �޸� ���� �����ּ�, 0���� ä�� ũ��)
	sd.pSysMem = &m_VertexList.at(0); // ������ �����Լ��� .at(0); 

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}
	
	// ���׸� -> ��ƿ��Ƽ -> txt ���� �ۼ�
	// ���̴� ������ -> ������Ʈ ������ ���ؼ� ���̴� ��ü ����
	ID3DBlob* pVSCodeResult = nullptr;
	ID3DBlob* pErrorMsgs = nullptr;
	hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &pVSCodeResult, &pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		return false;
	}

	hr = m_pd3dDevice->CreateVertexShader(pVSCodeResult->GetBufferPointer(), pVSCodeResult->GetBufferSize(), NULL, &m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}

	ID3DBlob* pPSCodeResult = nullptr;
	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &pPSCodeResult, &pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL,(char*)pErrorMsgs->GetBufferPointer(),"ERROR", MB_OK);
		return false;
	}

	hr = m_pd3dDevice->CreatePixelShader(pPSCodeResult->GetBufferPointer(),pPSCodeResult->GetBufferSize(),NULL,&m_pPixelShader);
	if (FAILED(hr))
	{
		return false;
	}

	// ���� ���̴��� ����� ���ؼ� �������̾ƿ��� �����Ѵ�.
	// ���� ������ �� ������ � ������ �������̴��� �����Ұ���
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32_FLOAT, 0,0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(layout, NumElements, pVSCodeResult->GetBufferPointer(), pVSCodeResult->GetBufferSize(), &m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

// �ʱ�ȭ
bool TDxObject::Init()
{
	return true;
}

bool TDxObject::Frame()
{
	return true;
}

// �������Ӹ��� ����� ����� �Ѹ��� ����������
bool TDxObject::Render()
{
	m_pContext->IASetInputLayout(m_pVertexLayout);

	//VSSetShader�� ���ڰ����� *pVertexShader, ppClassInstances, NumClassInstances ������ ����
	// *pVertexShader = m_pVertexShader�� ���߰� 
	// ppClassInstances�� ���̴��� �������̽��� ������� �����Ƿ� NULL
	// NumClassInstances�� �迭�� �ִ� Ŭ����-�ν��Ͻ� �������̽��� �� �����ϱ� 0
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);

	// PSSetShader�� ���ڰ����� *pPixelShader,ppClassInstances, NumClassInstances ������ ����
	// *pPixelShader = m_pPixelShader�� ���߰� 
	// ppClassInstances�� ���̴��� �������̽��� ������� �����Ƿ� NULL
	// NumClassInstances�� �迭�� �ִ� Ŭ����-�ν��Ͻ� �������̽��� �� �����ϱ� 0
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	UINT StartSlot; // ���۽���
	UINT NumBuffers; // ������ ������ ��
	UINT Strides = sizeof(SimpleVertex);
	UINT Offsets = 0; // 0���� �ְ� �۾��ϸ� ��, ���ؽ� ������ ������ �־��ִ°� 1�� ������ 1�� 0���� ��
					  // UINT offsets=sizeof(SimpleVertex)*2�� �ϸ� 2���� 0���� ��, �̷��� �۾����� ����! ũ�⿡ ���� �޶����ٴ°͸� �˸� ��

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&Strides, &Offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ���⼭ ������ �Ѹ����� ������ �Ѹ����� ���Ҽ��ִ� ����� �ﰢ��

	m_pContext->Draw(m_VertexList.size(), 0); // Draw(1,1) 1������ 1�� �ѷ��� ��¶�, ����� 0�������� ����Ʈ �����ŭ �Ѹ�

	return true;
}

bool TDxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();

	m_pVertexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;

	return true;
}


TDxObject::TDxObject()
{
}

TDxObject::~TDxObject()
{}