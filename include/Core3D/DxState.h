#include "STD.h"

class DxState
{
public:
	static ID3D11BlendState* m_AlphaBlend;
	static ID3D11BlendState* m_AlphaBlendDisable;
public:
	static ID3D11SamplerState* m_pSSLinear;
	static ID3D11SamplerState* m_pSSPoint;
public:
	static ID3D11RasterizerState* g_pRSBackCullWireFrame;
	static ID3D11RasterizerState* g_pRSNoneCullWireFrame;
public:
	static ID3D11RasterizerState* g_pRSBackCullSolid;
	static ID3D11RasterizerState* g_pRSNoneCullSolid;
public:
	static  ID3D11DepthStencilState* g_pDSSDepthEnable; // ����
	static  ID3D11DepthStencilState* g_pDSSDepthDisable; // �Ұ���
public:
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};