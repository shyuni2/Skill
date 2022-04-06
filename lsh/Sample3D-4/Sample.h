#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"
#include "Map.h"
#include "SkyObj.h"
#include "BoxObj.h"
#include "Quadtree.h" 

#define  MAX_NUM_OBJECTS 100
class Sample : public Core
{
	Camera		    m_Camera;
	Camera			m_CameraTopView;
	Map			m_MapObj;
	BoxObj			m_PlayerObj;
	std::vector<MapObj*> m_pObjList;
	SkyObj			m_SkyObj;
	Quadtree		m_Quadtree;
	BoxObj*		m_pBoxObj;
public:
	T::TVector3	m_vIntersection;
	std::vector<T::TVector3>	m_vIntersectionList;
	bool GetIntersection(T::TVector3 vStart, T::TVector3 vEnd,
		T::TVector3 v0, T::TVector3 v1, T::TVector3 v2,
		T::TVector3 vNormal);
	bool PointInPolygon(T::TVector3 vert, T::TVector3 faceNormal,
		T::TVector3 v0, T::TVector3 v1, T::TVector3 v2);
	bool IntersectTriangle(
		const TVector3& orig, const TVector3& dir,
		TVector3& v0, TVector3& v1, TVector3& v2,
		FLOAT* t, FLOAT* u, FLOAT* v);
public:
	void    CreateMapObject();
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	bool    MiniMapRender();
	virtual bool	Release()  override;	
public:
	Sample();
	virtual ~Sample();
};

