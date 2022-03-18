#pragma once
#include "TStd.h"
#include <d3dcompiler.h>
#pragma comment	(lib, "d3dcompiler.lib")

using namespace std;

// 삼각형들은 세 꼭지점을 가지고 있는데 이 꼭지점을 정점(Vertex)이라고 부름
struct SimpleVertex
{
	TVector2 v;
};

class TDxObject
{
	float m_fSpeed;
	TVector2 m_vPos;
	vector<SimpleVertex> m_InitScreenList;
	vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;
public:
	void SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext); 
	bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, TVector2 pos, float fWidth, float fHeight);
	// 화면좌표 위치를 중점으로 NDC변환하는 컨버터함수
	void Convert(TVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList);
	// 화면좌표계를 NDC로 변환
	void Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public :
	TDxObject();
	~TDxObject();
};