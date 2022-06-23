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
				SMatrix matInverseBindpose = binepose->second;
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
		S::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[iObj],&m_matBoneArray.matBoneWorld[iObj]);
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

S::SMatrix SFbxObj::Interplate(SFbxImporter* pAnimImporter, SFbxModel* pModel, float fTime)
{
	S::SMatrix matAnim; // 애니메이션 행렬 생성
	Scene tScene = pAnimImporter->m_Scene;
	int iStart = max(tScene.iStart, fTime);
	int iEnd = min(tScene.iEnd, fTime + 1);

	// 보간
	Track A = pModel->m_AnimTrack[iStart];
	Track B = pModel->m_AnimTrack[iEnd];
	float s = fTime - (float)iStart;
	S::SVector3 pos; // 위치
	S::D3DXVec3Lerp(&pos, &A.t, &B.t, s);
	S::SVector3 scale; // 크기
	S::D3DXVec3Lerp(&scale, &A.s, &B.s, s);
	S::SQuaternion rotation; // 회전
	S::D3DXQuaternionSlerp(&rotation, &A.r, &B.r, s);
	S::SMatrix matScale; // 크기행렬
	S::D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	S::SMatrix matRotation; // 회전행렬
	S::D3DXMatrixRotationQuaternion(&matRotation, &rotation);

	matAnim = matScale * matRotation; // 애니메이션 행렬 = 크기행렬 * 회전행렬
	matAnim._41 = pos.x;
	matAnim._42 = pos.y;
	matAnim._43 = pos.z;

	return matAnim;
}