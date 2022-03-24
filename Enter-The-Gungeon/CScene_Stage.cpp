#include "framework.h"
#include "CScene_Stage.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CD2DImage.h"
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

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"tile\\Stage.tile";
	LoadTile(path);

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200.f, 360.f));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);


	// Ä«¸Ş¶ó
	CCameraManager::GetInst()->SetLookAt(fPoint(200.f, 360.f));
	CCameraManager::GetInst()->SetTargetObj(pPlayer);
	
}

void CScene_Stage::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
