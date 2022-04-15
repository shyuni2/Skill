#define _CRT_SECURE_NO_WARNINGS
#include "SFbxObj.h"

bool SFbxObj::Init()
{
	m_fTime = 61;// ?
	return true;
}
bool SFbxObj::Frame()
{
	/*m_fTime += g_fSecPerFrame * m_pMeshImp->m_Scene.iFrameSpeed * m_fDir * m_fSpeed;
	if (m_fTime >= m_pMeshImp->m_Scene.iEnd)
	{
		m_fDir *= -1.0f;
	}
	if (m_fTime <= m_pMeshImp->m_Scene.iStart)
	{
		m_fDir *= -1.0f;
	}
	int iFrame = m_fTime;
	iFrame = max(0, min(m_pMeshImp->m_Scene.iEnd, iFrame));*/
	/*for (int iObj = 0; iObj < m_pMeshImp->m_TreeList.size(); iObj++)
	{
		TFbxModel* pObject = m_pMeshImp->m_TreeList[iObj];
		if (pObject->m_AnimTrack.size() > 0)
		{
			auto binepose = pObject->m_matBindPoseMap.find(pObject->m_iIndex);
			if (binepose != pObject->m_matBindPoseMap.end())
			{
				TMatrix matInverseBindpose = binepose->second;
				m_matBoneArray.matBoneWorld[iObj] =
					matInverseBindpose *
					pObject->m_AnimTrack[iFrame].matTrack;
			}
			else
			{
				m_matBoneArray.matBoneWorld[iObj] =
					pObject->m_AnimTrack[iFrame].matTrack;
			}
		}
		T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[iObj],&m_matBoneArray.matBoneWorld[iObj]);
	}	*/
	return true;
}
bool SFbxObj::Render()
{
	SFbxImporter* pAnimImporter = nullptr;
	if (m_pAnimImporter != nullptr)
	{
		pAnimImporter = m_pAnimImporter;
	}
	return true;
}
bool SFbxObj::Release()
{
	return true;
}

void SFbxObj::GenAABB()
{

}

T::TMatrix SFbxObj::Interplate(SFbxImporter* pAnimImporter, SFbxModel* pModel, float fTime)
{
	T::TMatrix matAnim; // 애니메이션 행렬 생성
	Scene tScene = pAnimImporter->m_Scene;
	int iStart = max(tScene.iStart, fTime);
	int iEnd = min(tScene.iEnd, fTime + 1);

	// 보간
	Track A = pModel->m_AnimTrack[iStart];
	Track B = pModel->m_AnimTrack[iEnd];
	float s = fTime - (float)iStart;
	T::TVector3 pos; // 위치
	T::D3DXVec3Lerp(&pos, &A.t, &B.t, s);
	T::TVector3 scale; // 크기
	T::D3DXVec3Lerp(&scale, &A.s, &B.s, s);
	T::TQuaternion rotation; // 회전
	T::D3DXQuaternionSlerp(&rotation, &A.r, &B.r, s);
	T::TMatrix matScale; // 크기행렬
	T::D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	T::TMatrix matRotation; // 회전행렬
	T::D3DXMatrixRotationQuaternion(&matRotation, &rotation);

	matAnim = matScale * matRotation; // 애니메이션 행렬 = 크기행렬 * 회전행렬
	matAnim._41 = pos.x;
	matAnim._42 = pos.y;
	matAnim._43 = pos.z;

	return matAnim;
}