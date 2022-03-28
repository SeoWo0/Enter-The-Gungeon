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


	// ī�޶�
	CCameraManager::GetInst()->SetTargetObj(pPlayer);

	// �浹 �׷� ����
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);			// �÷��̾�� Ÿ��(������)
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);		// �÷��̾�� ����
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BULLET_MONSTER);	// �÷��̾�� ������ �Ѿ�
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_PLAYER, GROUP_GAMEOBJ::TILE);	// �÷��̾��� �Ѿ˰� Ÿ��(������Ʈ)
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_PLAYER, GROUP_GAMEOBJ::MONSTER); // �÷��̾��� �Ѿ˰� ����
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::BULLET_MONSTER, GROUP_GAMEOBJ::TILE);	// ������ �Ѿ˰� Ÿ��(������Ʈ)


	// ���� ��ġ
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
