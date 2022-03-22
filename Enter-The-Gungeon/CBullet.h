#pragma once

#include "CGameObject.h"

class CBullet : public CGameObject
{
private:
	vector<int> m_vCountBullet;	// źâ
	bool m_isShoot;				// ���� ����ִ� ��Ȳ����
	float m_fPSpeed = 300;		// �÷��̾� �Ѿ� �ӵ�
	float m_fESpeed = 150;		// ���� �Ѿ� �ӵ�
	fVec2 m_fvDIr;				// �Ѿ� ����

public:
	CBullet();
	virtual ~CBullet();

	void ShootBullet();
	void ReloadBullet();

	virtual CBullet* Clone();
	virtual void update();
};

