#include "Map.h"
#include "WICTextureLoader.h"

float Map::GetHeight(float fPosX, float fPosZ)
{
	// fPos, fPosZ의 위치에 해당하는 높이맵 셀 찾기
	// m_iNumCols와 m_iNumRows는 가로, 세로 실제 크기값
	float fCellX = (float)(m_iNumCellCols * m_fCellDistance / 2.0f + fPosX);
	float fCellZ = (float)(m_iNumCellCols * m_fCellDistance / 2.0f + fPosZ);
	
	// 셀의 크기로 나누어 0 ~ 1 단위의 값으로 바꿔 높이맵 배열에 접근
	fCellX /= (float)m_fCellDistance;
	fCellZ /= (float)m_fCellDistance;

	// fCellX, fCellZ 값보다 작거나 같은 최대정수 (소수부분 잘라냄)
	float fVertexCol = ::floorf(fCellX);
	float fVertexRow = ::floorf(fCellZ);

	// 높이맵 범위를 벗어나면 강제로 초기화
	if (fVertexCol < 0.0f)
	{
		fVertexCol = 0.0f;
	}
	if (fVertexRow < 0.0f)
	{
		fVertexRow = 0.0f;
	}
	if ((float)(m_iNumCols - 2) < fVertexCol)
	{
		fVertexCol = (float)(m_iNumCols - 2);
	}
	if ((float)(m_iNumRows - 2) < fVertexCol)
	{
		fVertexRow = (float)(m_iNumRows - 2);
	}

	// 계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = GetHeightMap((int)fVertexRow, (int)fVertexCol);
	float B = GetHeightMap((int)fVertexRow, (int)fVertexCol + 1);
	float C = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol + 1);

	// A정점의 위치에서 떨어진값 (변위값)을 계산
	float fDeltaX = fCellX - fVertexCol;
	float fDeltaZ = fCellZ - fVertexRow;
	// 보간작업을 위한 페이스를 찾는다
	float fHeight = 0.0f;
	// 윗 페이스를 기준으로 보간한다
	if (fDeltaZ < (1.0f - fDeltaX)) // ABC
	{
		float uy = B - A; // A -> B
		float vy = C - A; // A -> C 
		// 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다
		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	}
	// 아래페이스를 기준으로 보간
	else // DCB
	{
		float uy = C - D; // A -> B
		float vy = B - D; // A -> C 
		// 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다
		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	}
	return fHeight;
}
float Map::GetHeightMap(int row, int col)
{
	return m_VertexList[row * m_iNumRows + col].p.y;
}
float Map::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart * fTangent) + (fEnd * fTangent);
}

bool Map::Frame()
{
	Vector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);

	vLight = vLight.Normal() * -1.0f;
	m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;
	return true;
}
bool Map::CreateHeightMap(const TCHAR* strHeightMapTex)
{
	HRESULT hr;	
	ID3D11ShaderResourceView* pSRV = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	size_t maxsize = 0;
	if (FAILED(hr = CreateWICTextureFromFileEx(m_pd3dDevice, strHeightMapTex, maxsize, D3D11_USAGE_STAGING, 0, D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ, 0, 
												DirectX::WIC_LOADER_DEFAULT, pTexture.GetAddressOf(), nullptr)))
	{
		return false;
	}
	ID3D11Texture2D* pTexture2D = NULL;
	if (FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);

	m_fHeightList.resize(desc.Height * desc.Width);

	if (pTexture2D)
	{
		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(m_pContext->Map((ID3D11Resource*)pTexture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MappedFaceDest)))
		{
			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
			Vertex	v;
			for (UINT row = 0; row < desc.Height; row++)
			{
				UINT rowStart = row * MappedFaceDest.RowPitch;
				for (UINT col = 0; col < desc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					m_fHeightList[row * desc.Width + col] = (float)uRed;	/// DWORD이므로 pitch/4	
				}
			}
			m_pContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
		}
	}

	m_iNumRows = desc.Height;
	m_iNumCols = desc.Width;

	if(pTexture2D) pTexture2D->Release();
	return true;
}
bool Map::CreateMap(UINT width, UINT height, float fDistance)
{
	m_iNumCols = width;
	m_iNumRows = height;
	m_fCellDistance = fDistance;
	m_iNumVertices = m_iNumCols * m_iNumRows;
	m_iNumCellCols = m_iNumCols - 1; // 가로셀은 정점 가로정점개수 - 1
	m_iNumCellRows = m_iNumRows - 1; // 세로셀은 정점 세로정점개수 - 1
	m_iNumFaces = m_iNumCellCols * m_iNumCellRows * 2;

	return true;
}
bool Map::SetVertexData()
{
	m_VertexList.resize(m_iNumVertices);	
	float  hHalfCol = (m_iNumCols - 1) / 2.0f;
	float  hHalfRow = (m_iNumRows - 1) / 2.0f;
	float  ftxOffetU = 1.0f / (m_iNumCols - 1);
	float  ftxOffetV = 1.0f / (m_iNumRows - 1);
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int index = iRow * m_iNumCols + iCol;
			m_VertexList[index].p.x = (iCol- hHalfCol)* m_fCellDistance;
			m_VertexList[index].p.y = m_fHeightList[index];
			m_VertexList[index].p.z = -((iRow - hHalfRow)* m_fCellDistance);
			m_VertexList[index].n = Vector3(0, 1, 0);
			m_VertexList[index].c = Vector4(randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), 1);
			m_VertexList[index].t = Vector2(ftxOffetU * iCol, ftxOffetV * iRow);
		}
	}
	return true;
}
bool Map::SetIndexData()
{
	m_IndexList.resize(m_iNumFaces*3);
	UINT iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			m_IndexList[iIndex+0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex+1] = (iRow * m_iNumCols + iCol)+1;
			m_IndexList[iIndex+2] = (iRow+1)* m_iNumCols + iCol;

			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2]+1;
			
			iIndex += 6;
		}
	}

	iIndex = 0;
	Vector3 vLight(100, 100, 0);
	vLight = vLight.Normal() * 1.0f;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			// 0face
			Face face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];
			Vector3 vNormal;
			Vector3 vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			Vector3 vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();
			face.vNomal = (vE0 ^ vE1).Normal();

			m_VertexList[face.v0].n += face.vNomal;
			m_VertexList[face.v1].n += face.vNomal;
			m_VertexList[face.v2].n += face.vNomal;

			float fDot = max(0.0f, vLight | face.vNomal);
			m_VertexList[face.v0].c = Vector4(fDot, fDot, fDot,1);
			m_VertexList[face.v1].c = Vector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = Vector4(fDot, fDot, fDot, 1);
			m_FaceList.push_back(face);

			// 1face
			face.v0 = m_IndexList[iIndex + 3];
			face.v1 = m_IndexList[iIndex + 4];
			face.v2 = m_IndexList[iIndex + 5];
			vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();
			face.vNomal = (vE0 ^ vE1).Normal();

			m_VertexList[face.v0].n += face.vNomal;
			m_VertexList[face.v1].n += face.vNomal;
			m_VertexList[face.v2].n += face.vNomal;

			fDot = max(0.0f, vLight | face.vNomal);
			m_VertexList[face.v0].c = Vector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = Vector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = Vector4(fDot, fDot, fDot, 1);
			m_FaceList.push_back(face);

			iIndex += 6;
		}
	}
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			m_VertexList[iRow * m_iNumCols + iCol].n.Normalize();
			float fDot = max(0.0f, vLight | m_VertexList[iRow * m_iNumCols + iCol].n);
			m_VertexList[iRow * m_iNumCols + iCol].c = Vector4(fDot, fDot, fDot, 1);
		}
	}
	return true;
}
Map::Map()
{

}
Map::~Map()
{

}