#include "Map.h"
#include "WICTextureLoader.h"
float Map::GetHeightmap(int row, int col)
{
	return m_VertexList[row * m_iNumRows + col].p.y;
}
float Map::GetHeight(float fPosX, float fPosZ)
{
	// fPosX/fPosZ�� ��ġ�� �ش��ϴ� ���̸ʼ��� ã�´�.
	// m_iNumCols��m_iNumRows�� ����/������ ���� ũ�Ⱚ��.
	float fCellX = (float)(m_iNumCellCols * m_fCellDistance / 2.0f + fPosX);
	float fCellZ = (float)(m_iNumCellRows * m_fCellDistance / 2.0f - fPosZ);

	// ���� ũ��� ������ 0~1 ������ ������ �ٲپ� ���̸� �迭�� �����Ѵ�.
	fCellX /= (float)m_fCellDistance;
	fCellZ /= (float)m_fCellDistance;

	// fCellX, fCellZ ������ �۰ų� ���� �ִ� ����( �Ҽ��κ��� �߶󳽴�.)
	float fVertexCol = ::floorf(fCellX);
	float fVertexRow = ::floorf(fCellZ);

	// ���̸� ������ ����� ������ �ʱ�ȭ �Ѵ�.
	if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
	if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
	if ((float)(m_iNumCols - 2) < fVertexCol)	fVertexCol = (float)(m_iNumCols - 2);
	if ((float)(m_iNumRows - 2) < fVertexRow)	fVertexRow = (float)(m_iNumRows - 2);

	// ���� ���� �÷��� �����ϴ� 4�� ������ ���̰��� ã�´�. 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = GetHeightmap((int)fVertexRow, (int)fVertexCol);
	float B = GetHeightmap((int)fVertexRow, (int)fVertexCol + 1);
	float C = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol + 1);

	// A������ ��ġ���� ������ ��(������)�� ����Ѵ�. 0 ~ 1.0f
	float fDeltaX = fCellX - fVertexCol;
	float fDeltaZ = fCellZ - fVertexRow;
	// �����۾��� ���� ���� ���ս��� ã�´�. 
	float fHeight = 0.0f;
	// �����̽��� �������� �����Ѵ�.
	// fDeltaZ + fDeltaX < 1.0f
	if (fDeltaZ < (1.0f - fDeltaX))  //ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C	
						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸX�� ���� ���� �������� ã�´�.		
		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	}
	// �Ʒ����̽��� �������� �����Ѵ�.
	else // DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B
						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸZ�� ���� ���� �������� ã�´�.		
		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	}
	return fHeight;
}
float Map::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart * fTangent) + (fEnd * fTangent);
}
bool Map::Frame()
{
	T::TVector3 vLight(cosf(g_fGameTimer)*100.0f, 
		            100, 
					sinf(g_fGameTimer) * 100.0f);

	T::D3DXVec3Normalize(&vLight, &vLight);
	vLight = vLight * -1.0f;
	m_LightConstantList.vLightDir.x = vLight.x;
	m_LightConstantList.vLightDir.y = vLight.y;
	m_LightConstantList.vLightDir.z = vLight.z;
	m_LightConstantList.vLightDir.w = 1.0f;
	return true;
}
bool Map::CreateHeightMap(const TCHAR* strHeightMapTex)
{
	HRESULT hr;	
	ID3D11ShaderResourceView* pSRV = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	size_t maxsize = 0;
	if (FAILED(hr = CreateWICTextureFromFileEx(m_pd3dDevice,
		strHeightMapTex,
		maxsize,
		D3D11_USAGE_STAGING,
		0,
		D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ,
		0,
		DirectX::WIC_LOADER_DEFAULT,
		pTexture.GetAddressOf(), nullptr)))
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
					m_fHeightList[row * desc.Width + col] = (float)uRed;	/// DWORD�̹Ƿ� pitch/4	
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
bool		Map::CreateMap(UINT width, UINT height,
	float fDistance)
{
	m_iNumCols = width;
	m_iNumRows = height;
	m_fCellDistance = fDistance;
	m_iNumVertices = m_iNumCols * m_iNumRows;
	m_iNumCellCols = m_iNumCols-1;
	m_iNumCellRows = m_iNumRows-1;
	m_iNumFaces = m_iNumCellCols* m_iNumCellRows*2;

	m_BoxCollision.vMax.x = (m_iNumCols / 2 * m_fCellDistance);
	m_BoxCollision.vMin.x = -m_BoxCollision.vMax.x;
	m_BoxCollision.vMax.z = (m_iNumRows / 2 * m_fCellDistance);
	m_BoxCollision.vMin.z = -m_BoxCollision.vMax.z;
	return true;
}
bool		Map::SetVertexData()
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
			m_VertexList[index].p.y = m_fHeightList[index]*3.0f;
			m_VertexList[index].p.z = -((iRow - hHalfRow)* m_fCellDistance);
			m_VertexList[index].n = T::TVector3(0, 1, 0);
			m_VertexList[index].c = T::TVector4(randstep(0.0f, 1.0f), 
				randstep(0.0f, 1.0f), 
				randstep(0.0f, 1.0f), 1);
			m_VertexList[index].t = 
				T::TVector2(ftxOffetU*iCol, ftxOffetV * iRow);
		}
	}
	return true;
}
bool		Map::SetIndexData()
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
	T::TVector3 vLight(100, 100, 0);
	T::D3DXVec3Normalize(&vLight, &vLight);
	vLight = vLight * 1.0f;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			// 0face
			Face face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];
			T::TVector3 vNormal;
			T::TVector3 vE0= m_VertexList[face.v1].p - m_VertexList[face.v0].p;
			T::D3DXVec3Normalize(&vE0, &vE0);
			T::TVector3 vE1= m_VertexList[face.v2].p - m_VertexList[face.v0].p;
			T::D3DXVec3Normalize(&vE1, &vE1);
			
			T::D3DXVec3Cross(&face.vNomal, &vE0, &vE1);
			T::D3DXVec3Normalize(&face.vNomal, &face.vNomal);

			m_VertexList[face.v0].n += face.vNomal;
			m_VertexList[face.v1].n += face.vNomal;
			m_VertexList[face.v2].n += face.vNomal;

			float fDot = max(0.0f, T::D3DXVec3Dot(&vLight, &face.vNomal));
			m_VertexList[face.v0].c = T::TVector4(fDot, fDot, fDot,1);
			m_VertexList[face.v1].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = T::TVector4(fDot, fDot, fDot, 1);
			m_FaceList.push_back(face);

			// 1face
			face.v0 = m_IndexList[iIndex + 3];
			face.v1 = m_IndexList[iIndex + 4];
			face.v2 = m_IndexList[iIndex + 5];
			T::D3DXVec3Subtract(&vE0, &m_VertexList[face.v1].p, &m_VertexList[face.v0].p);
			T::D3DXVec3Normalize(&vE0, &vE0);

			T::D3DXVec3Subtract(&vE1, &m_VertexList[face.v2].p, &m_VertexList[face.v0].p);
			T::D3DXVec3Normalize(&vE1, &vE1);
			T::D3DXVec3Cross(&face.vNomal, &vE0, &vE1);
			T::D3DXVec3Normalize(&face.vNomal, &face.vNomal);

			m_VertexList[face.v0].n += face.vNomal;
			m_VertexList[face.v1].n += face.vNomal;
			m_VertexList[face.v2].n += face.vNomal;

			fDot = max(0.0f, T::D3DXVec3Dot(&vLight, &face.vNomal));

			m_VertexList[face.v0].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = T::TVector4(fDot, fDot, fDot, 1);
			m_FaceList.push_back(face);

			iIndex += 6;
		}
	}
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			m_VertexList[iRow * m_iNumCols + iCol].n.Normalize();
			float fDot;
			fDot = max(0.0f, T::D3DXVec3Dot(&vLight, &m_VertexList[iRow * m_iNumCols + iCol].n));
			m_VertexList[iRow * m_iNumCols + iCol].c = T::TVector4(fDot, fDot, fDot, 1);
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