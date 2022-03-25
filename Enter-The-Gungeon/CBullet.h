#pragma once

#include "CGameObject.h"

class CBullet : public CGameObject
{
private:
	bool	m_bIsShoot = true;	// 지금 쏠수있는 상황인지
	float	m_fSpeed = 300;		// 총알 속도
	fVec2	m_fvDIr;			// 총알 각도

public:
	CBullet();
	virtual ~CBullet();

	virtual CBullet* Clone();
	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetSpeed(float speed);
	void OnCollisionEnter(CCollider* pOther);
	bool Cantshoot();
};

