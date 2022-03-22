#pragma once

#include "CGameObject.h"

class CBullet : public CGameObject
{
private:
	vector<int> m_vCountBullet;	// 탄창
	bool m_isShoot;				// 지금 쏠수있는 상황인지
	float m_fPSpeed = 300;		// 플레이어 총알 속도
	float m_fESpeed = 150;		// 몬스터 총알 속도
	fVec2 m_fvDIr;				// 총알 각도

public:
	CBullet();
	virtual ~CBullet();

	void ShootBullet();
	void ReloadBullet();

	virtual CBullet* Clone();
	virtual void update();
};

