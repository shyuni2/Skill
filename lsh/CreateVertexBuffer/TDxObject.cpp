#include "TDxObject.h"

void TDxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pCOntext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pCOntext;
}

// 화면좌표 위치를 중점으로 NDC변환하는 컨버터함수
void TDxObject::Convert(TVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList)
{
	// 사각형을 만드려면 삼각형이 두개 붙어야함
	// 0         1,4
	//
	// 2,3       5          시계방향으로 돌아감
	// 멤버를 계속 늘리면 수정해야할것이 많아지니까 벡터로 지정 
	// 벡터는 연속적인 배열임, 연결리스트는 포인터로 사용해서 지정해야하니까 안됨
	vector<SimpleVertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;
	list[0].v = { center.x - halfWidth,center.y - halfHeight };
	list[1].v = { center.x + halfWidth,center.y - halfHeight }; // 1번은 가로만 움직임
	list[2].v = { center.x - halfWidth,center.y + halfHeight }; // 2번은 세로만 움직임
	list[3].v = list[2].v;
	list[4].v = list[1].v; // 3,4 는 2,1과 같으니까
	list[5].v = { center.x + halfWidth,center.y + halfHeight }; // 5번은 가로 세로 움직임

	Convert(list, retList);
}

// 화면좌표계를 NDC로 변환
void TDxObject::Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 인 좌표를 0 ~ 1 으로 변환
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 좌표를 -1 ~ +1 로 변환 ::: -1 ~ +1 좌표를 0 ~ 1좌표로 변환 , 둘다 되어야함
		// x = x * 2 - 1				::: x = x * 0.5f + 0.5f
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
}

// 오브젝트 만들기
bool TDxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, TVector2 vPos, float fWidth, float fHeight)
{
	// 화면밖으로 못나가게 설정
	if ((vPos.x - fWidth / 2.0f) < 0) return false;
	if ((vPos.x + fWidth / 2.0f) > g_rtClient.right) return false;
	if ((vPos.y - fWidth / 2.0f) < 0) return false;
	if ((vPos.y + fWidth / 2.0f) > g_rtClient.bottom) return false;

	SetDevice(pd3dDevice, pContext);
	HRESULT hr;
	// ui에 사용
	m_InitScreenList.resize(6); // 현재 점이 6개니까
	m_InitScreenList[0].v = TVector2(0.0f, 0.0f);
	m_InitScreenList[1].v = TVector2(fWidth, 0.0f);
	m_InitScreenList[2].v = TVector2(0.0f, fHeight);
	m_InitScreenList[3].v = TVector2(0.0f, fHeight);
	m_InitScreenList[4].v = TVector2(fWidth, 0.0f);
	m_InitScreenList[5].v = TVector2(fWidth, fHeight);

	m_vPos = vPos;
	Convert(m_vPos, fWidth, fHeight, m_VertexList);

	//gpu 메모리에 버퍼 할당 (원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC)); // ZeroMemory (0으로 채울 메모리 블럭의 시작주소, 0으로 채울 크기)
	bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA)); // ZeroMemory (0으로 채울 메모리 블럭의 시작주소, 0으로 채울 크기)
	sd.pSysMem = &m_VertexList.at(0); // 벡터의 시작함수는 .at(0); 

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}
	
	// 새항목 -> 유틸리티 -> txt 파일 작성
	// 쉐이더 컴파일 -> 오브젝트 파일을 통해서 셰이더 객체 생성
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

	// 정점 쉐이더의 결과를 통해서 정점레이아웃을 생성한다.
	// 정점 버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지
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

// 초기화
bool TDxObject::Init()
{
	return true;
}

bool TDxObject::Frame()
{
	return true;
}

// 매프레임마다 백버퍼 지우고 뿌리고 더블프레임
bool TDxObject::Render()
{
	m_pContext->IASetInputLayout(m_pVertexLayout);

	//VSSetShader는 인자값으로 *pVertexShader, ppClassInstances, NumClassInstances 세가지 받음
	// *pVertexShader = m_pVertexShader로 정했고 
	// ppClassInstances는 셰이더가 인터페이스를 사용하지 않으므로 NULL
	// NumClassInstances는 배열에 있는 클래스-인스턴스 인터페이스의 수 없으니까 0
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);

	// PSSetShader는 인자값으로 *pPixelShader,ppClassInstances, NumClassInstances 세가지 받음
	// *pPixelShader = m_pPixelShader로 정했고 
	// ppClassInstances는 셰이더가 인터페이스를 사용하지 않으므로 NULL
	// NumClassInstances는 배열에 있는 클래스-인스턴스 인터페이스의 수 없으니까 0
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	UINT StartSlot; // 시작슬롯
	UINT NumBuffers; // 설정할 버퍼의 수
	UINT Strides = sizeof(SimpleVertex);
	UINT Offsets = 0; // 0으로 넣고 작업하면 됨, 버텍스 버퍼의 개수를 넣어주는곳 1을 넣으면 1이 0번이 됨
					  // UINT offsets=sizeof(SimpleVertex)*2로 하면 2번이 0번이 됨, 이렇게 작업할일 없음! 크기에 따라서 달라진다는것만 알면 됨

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&Strides, &Offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 여기서 점으로 뿌릴건지 선으로 뿌릴건지 정할수있다 현재는 삼각형

	m_pContext->Draw(m_VertexList.size(), 0); // Draw(1,1) 1번정점 1개 뿌려라 라는뜻, 현재는 0번정점을 리스트 사이즈만큼 뿌림

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