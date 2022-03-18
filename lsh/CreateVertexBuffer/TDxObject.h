#pragma once
#include "TStd.h"
#include <d3dcompiler.h>
#pragma comment	(lib, "d3dcompiler.lib")

using namespace std;

// �ﰢ������ �� �������� ������ �ִµ� �� �������� ����(Vertex)�̶�� �θ�
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
	// ȭ����ǥ ��ġ�� �������� NDC��ȯ�ϴ� �������Լ�
	void Convert(TVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC�� ��ȯ
	void Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public :
	TDxObject();
	~TDxObject();
};