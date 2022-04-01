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
	static  ID3D11DepthStencilState* g_pDSSDepthEnable; // 가능
	static  ID3D11DepthStencilState* g_pDSSDepthDisable; // 불가능
public:
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};