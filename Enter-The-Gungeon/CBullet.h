#pragma once

#include "CGameObject.h"

class CD2DImage;

class CBullet : public CGameObject
{
private:
	CD2DImage* m_pImgPlayerBullet;	// 플레이어 총알 이미지
	float	m_fSpeed = 350;			// 총알 속도
	fVec2	m_fvDIr;				// 총알 각도


public:
	CBullet();
	virtual ~CBullet();

	virtual CBullet* Clone();
	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetSpeed(float speed);
	void OnCollisionEnter(CCollider* pOther);
};

