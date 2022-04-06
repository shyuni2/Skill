#include "STD.h"

class DxState
{
public:
	// BlendState : 렌더링 파이프라인에서 픽셀 셰이더를 거쳐 생성된 단편이 어떻게 적용될지 결정하는 상태값
	static ID3D11BlendState* m_AlphaBlend;
	static ID3D11BlendState* m_AlphaBlendDisable;

	// ID3D11SamplerState : 텍스쳐를 띄울때 필요
	static ID3D11SamplerState* m_pSSLinear;
	static ID3D11SamplerState* m_pSSPoint;

	//
	static ID3D11RasterizerState* g_pRSBackCullWireFrame;
	static ID3D11RasterizerState* g_pRSNoneCullWireFrame;

	static ID3D11RasterizerState* g_pRSBackCullSolid;
	static ID3D11RasterizerState* g_pRSNoneCullSolid;

	//
	static ID3D11DepthStencilState* g_pDSSDepthEnable;
	static ID3D11DepthStencilState* g_pDSSDepthDisable;

	static ID3D11DepthStencilState* g_pDSSDepthEnableWriteDisable;
	static ID3D11DepthStencilState* g_pDSSDepthDisableWriteDisable;
public:
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};