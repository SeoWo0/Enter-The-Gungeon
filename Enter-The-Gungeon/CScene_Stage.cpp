#include "framework.h"
#include "CScene_Stage.h"
#include "CGameObject.h"
#include "CPlayer.h"

CScene_Stage::CScene_Stage()
{
}

CScene_Stage::~CScene_Stage()
{
}

void CScene_Stage::update()
{
	CScene::update();
}

void CScene_Stage::Enter()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200.f, 360.f));
	pPlayer->SetScale(fPoint(50.f, 50.f));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
}

void CScene_Stage::Exit()
{
}
