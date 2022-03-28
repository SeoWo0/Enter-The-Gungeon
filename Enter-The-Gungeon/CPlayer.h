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
	bool		m_isMove;						// 플레이어가 움직이고있는가?

	float		m_fCooltimeBullet = 0.3f;		// 총알을 쏠수있는 시간 간격
	float		m_fLastBulletTime;				// 마지막에 총알을 쏜 순간

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
	static CPlayer* GetPlayer();	// 게임 내에 하나만 있는 플레이어 객체 확인(임의로 싱글톤 선언)

};

