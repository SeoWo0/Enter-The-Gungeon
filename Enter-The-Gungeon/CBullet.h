#pragma once

#include "CGameObject.h"

class CD2DImage;

class CBullet : public CGameObject
{
private:
	CD2DImage* m_pImgPlayerBullet;	// �÷��̾� �Ѿ� �̹���
	float	m_fSpeed = 350;			// �Ѿ� �ӵ�
	fVec2	m_fvDIr;				// �Ѿ� ����


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

