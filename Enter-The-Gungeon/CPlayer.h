#pragma once
#include "CGameObject.h"
#include "CKeyManager.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImgIdle;
	CD2DImage* m_pImgWalk;
	CD2DImage* m_pImgDodge;
	float m_fSpeed = 250;

public:
	CPlayer();
	~CPlayer();

	virtual CPlayer* Clone();

	virtual void update();
	virtual void render(HDC hDC);
};

