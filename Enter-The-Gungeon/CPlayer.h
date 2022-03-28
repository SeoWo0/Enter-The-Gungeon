#pragma once
#include "CGameObject.h"
#include "CKeyManager.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	CD2DImage*	m_pImgIdle;
	CD2DImage*	m_pImgWalk;
	CD2DImage*	m_pImgDodge;
	float		m_fSpeed = 250;
	int			m_iHp	 = 6;
	bool		m_isMove;						// �÷��̾ �����̰��ִ°�?

	float		m_fCooltimeBullet = 0.3f;		// �Ѿ��� ����ִ� �ð� ����
	float		m_fLastBulletTime;				// �������� �Ѿ��� �� ����

public:
	CPlayer();
	~CPlayer();

	virtual CPlayer* Clone();

	virtual void update();
	void		 update_Ani();
	virtual void render();
	
	int GetHp();
	void SetHp(int hp);

	void CreateBullet(fPoint pos);

	void RegisterPlayer();
	static CPlayer* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)

};

