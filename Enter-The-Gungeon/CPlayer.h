#pragma once
#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg1;
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;
	float m_fSpeed = 250;

	float m_fVelocity;
	bool isLeft;
	bool isUp;
public:
	CPlayer();
	~CPlayer();

	virtual CPlayer* Clone();

	virtual void update();
	virtual void render(HDC hDC);
};

