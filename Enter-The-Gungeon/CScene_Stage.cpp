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
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);


	// Ä«¸Þ¶ó
	CCameraManager::GetInst()->SetLookAt(fPoint(200.f, 360.f));
	CCameraManager::GetInst()->SetTargetObj(pPlayer);
	
}

void CScene_Stage::Exit()
{
}
