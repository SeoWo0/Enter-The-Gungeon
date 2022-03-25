#pragma once

#include "CGameObject.h"

class CBullet : public CGameObject
{
private:
	bool	m_bIsShoot = true;	// ���� ����ִ� ��Ȳ����
	float	m_fSpeed = 300;		// �Ѿ� �ӵ�
	fVec2	m_fvDIr;			// �Ѿ� ����

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

