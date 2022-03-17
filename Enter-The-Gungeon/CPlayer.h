#pragma once
#include "CGameObject.h"
class CPlayer : public CGameObject
{
private:

public:
	CPlayer();
	~CPlayer();

	void update();
	void render(HDC hDC);
};

