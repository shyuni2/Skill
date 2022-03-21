#include "Map.h"
#include "WICTextureLoader.h"

bool Map::CreateHeightMap(const TCHAR* strHeightMapTex)
{
	Vector3 vLight(cosf(g_fGameTimer) * 100.f, 100, sinf(g_fGameTimer) * 100.f);
	vLight = vLight.Normal() * -1.0f;
	m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;

	return true;
}
bool Map::CreateMap(UINT iWidth, UINT iHeight, float fDistance)
{
	HRESULT hr;
	ID3D10ShaderResourceView* pSRV = nullptr;

	return true;
}
bool Map::SetVertexData()
{
	return true;
}
bool Map::SetIndexData()
{
	return true;
}
bool Map::Frame()
{
	return true;
}

Map::Map()
{

}
Map::~Map()
{

}