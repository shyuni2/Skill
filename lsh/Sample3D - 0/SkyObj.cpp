#include "SkyObj.h"

bool SkyObj::PostRender()
{
	for (int iTex = 0; iTex < 6; iTex++)
	{
		m_pContext->PSSetShaderResources(0, 1, m_pTexArray[iTex]->m_pSRV.GetAddressOf());
		m_pContext->DrawIndexed(6, 6 * iTex, 0);
	}

	return true;
}

bool SkyObj::SetVertexData()
{
	// Local Coord
	// Box
	//  0        1 
	//     ¿øÁ¡
	//  2        3
	m_VertexList.resize(24);

	int index = 0;

	//// +Z plane
	//m_VertexList[index].p = Vector3(1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	//// -Z plane
	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	//// +X plane
	//m_VertexList[++index].p = Vector3(1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	//// -X plane
	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(-1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(-1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(-1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(-1.0f, 0.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	//// -y plane
	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, -1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, -1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, -1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(1.0f, -1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, -1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	//// +y plane
	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(1.0f, 1.0f, 1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 0.0f);

	//m_VertexList[++index].p = Vector3(-1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(0.0f, 1.0f);

	//m_VertexList[++index].p = Vector3(1.0f, 1.0f, -1.0f);
	//m_VertexList[index].n = Vector3(0.0f, 1.0f, 0.0f);
	//m_VertexList[index].c = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[index].t = Vector2(1.0f, 1.0f);

	m_VertexList.resize(24);
	m_VertexList[0] = Vertex(Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[1] = Vertex(Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[2] = Vertex(Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[3] = Vertex(Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	// µÞ¸é
	m_VertexList[4] = Vertex(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[5] = Vertex(Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[6] = Vertex(Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[7] = Vertex(Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[8] = Vertex(Vector3(1.0f, 1.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[9] = Vertex(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[10] = Vertex(Vector3(1.0f, -1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[11] = Vertex(Vector3(1.0f, -1.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));

	// ¿ÞÂÊ
	m_VertexList[12] = Vertex(Vector3(-1.0f, 1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[13] = Vertex(Vector3(-1.0f, 1.0f, -1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[14] = Vertex(Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[15] = Vertex(Vector3(-1.0f, -1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));

	// À­¸é
	m_VertexList[16] = Vertex(Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector4(1.0f, 0.5f, 1.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[17] = Vertex(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector4(1.0f, 0.5f, 1.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[18] = Vertex(Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector4(1.0f, 0.5f, 1.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[19] = Vertex(Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector4(1.0f, 0.5f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));

	// ¾Æ·§¸é
	m_VertexList[20] = Vertex(Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f));
	m_VertexList[21] = Vertex(Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f));
	m_VertexList[22] = Vertex(Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f));
	m_VertexList[23] = Vertex(Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));

	return true;
}
bool SkyObj::SetIndexData()
{
	//m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	//m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	//m_IndexList.push_back(4); m_IndexList.push_back(5); m_IndexList.push_back(6);
	//m_IndexList.push_back(6); m_IndexList.push_back(5); m_IndexList.push_back(7);
	//m_IndexList.push_back(8); m_IndexList.push_back(9); m_IndexList.push_back(10);
	//m_IndexList.push_back(10); m_IndexList.push_back(9); m_IndexList.push_back(11);
	//m_IndexList.push_back(12); m_IndexList.push_back(13); m_IndexList.push_back(14);
	//m_IndexList.push_back(14); m_IndexList.push_back(13); m_IndexList.push_back(15);
	//m_IndexList.push_back(16); m_IndexList.push_back(17); m_IndexList.push_back(18);
	//m_IndexList.push_back(18); m_IndexList.push_back(17); m_IndexList.push_back(19);
	//m_IndexList.push_back(20); m_IndexList.push_back(21); m_IndexList.push_back(22);
	//m_IndexList.push_back(22); m_IndexList.push_back(21); m_IndexList.push_back(23);

	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

	return true;
}
bool SkyObj::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{

	m_pTexArray[0] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_front.bmp");
	m_pTexArray[1] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_back.bmp");
	m_pTexArray[2] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_right.bmp");
	m_pTexArray[3] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_left.bmp");
	m_pTexArray[4] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_up.bmp");
	m_pTexArray[5] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_down.bmp");

	m_TextureDesc = m_pTexArray[0]->m_TextureDesc;
	return true;
}

SkyObj::SkyObj()
{

}
SkyObj::~SkyObj()
{

}
