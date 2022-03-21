#pragma once
#include "CScene.h"

class CScene_Stage : public CScene
{
private:

public:
	CScene_Stage();
	virtual ~CScene_Stage();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

