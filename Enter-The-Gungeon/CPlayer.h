#pragma once
#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;
	float m_fSpeed = 250;

public:
	CPlayer();
	~CPlayer();

	virtual CPlayer* Clone();

	void update();
	void render(HDC hDC);
};

