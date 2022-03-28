#include "framework.h"
#include "CScene_Stage.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
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


	// 카메라
	CCameraManager::GetInst()->SetTargetObj(pPlayer);

	// 충돌 그룹 지정
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);			// 플레이어와 타일(구조물)
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);		// 플레이어와 몬스터
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BULLET_MONSTER);	// 플레이어와 몬스터의 총알
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_PLAYER, GROUP_GAMEOBJ::TILE);	// 플레이어의 총알과 타일(오브젝트)
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_PLAYER, GROUP_GAMEOBJ::MONSTER); // 플레이어의 총알과 몬스터
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_MONSTER, GROUP_GAMEOBJ::TILE);	// 몬스터의 총알과 타일(오브젝트)


	// 몬스터 배치
	CMonster* pMon = CMonster::Create(MON_TYPE::NORMAL, fPoint(500.f, 500.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMonClone = pMon->Clone();
	pMonClone = CMonster::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(pMonClone, GROUP_GAMEOBJ::MONSTER);
	
}

void CScene_Stage::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
