#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

CMonster::CMonster()
{
	m_pAI = nullptr;

	m_pImgMonsterIdle = CResourceManager::GetInst()->LoadD2DImage(L"Monster_Idle", L"texture\\Animation\\EnemyIdle.png");
	SetScale(fPoint(35.f, 60.f));
	SetName(L"MonsterIdle");
	m_pImgMonsterWalk = CResourceManager::GetInst()->LoadD2DImage(L"Monster_Walk", L"texture\\Animation\\EnemyWalk.png");
	SetName(L"MonsterWalk");

	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

	CreateAnimator();
	// 몬스터 가만히 있을때
	GetAnimator()->CreateAnimation(L"M_Idle", m_pImgMonsterIdle, fPoint(0.f, 0.f), fPoint(35.f, 60.f), fPoint(35.f, 0.f), 0.25f, 2);
	GetAnimator()->CreateAnimation(L"M_RightIdle", m_pImgMonsterIdle, fPoint(0.f, 60.f), fPoint(35.f, 60.f), fPoint(35.f, 0.f), 0.25f, 2);
	GetAnimator()->CreateAnimation(L"M_LeftIdle", m_pImgMonsterIdle, fPoint(0.f, 60.f), fPoint(35.f, 60.f), fPoint(35.f, 0.f), 0.25f, 2, true);
	GetAnimator()->CreateAnimation(L"M_BackIdle", m_pImgMonsterIdle, fPoint(0.f, 120.f), fPoint(35.f, 60.f), fPoint(35.f, 0.f), 0.25f, 2);

	// 몬스터 걸을때
	GetAnimator()->CreateAnimation(L"M_LeftWalk", m_pImgMonsterWalk, fPoint(0.f, 0.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.125f, 6);
	GetAnimator()->CreateAnimation(L"M_RightWalk", m_pImgMonsterWalk, fPoint(0.f, 0.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.125f, 6, true);
	GetAnimator()->CreateAnimation(L"M_FrontWalk", m_pImgMonsterWalk, fPoint(0.f, 60.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.125f, 6);
	GetAnimator()->CreateAnimation(L"M_BackWalk", m_pImgMonsterWalk, fPoint(0.f, 120.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.125f, 6);

	GetAnimator()->Play(L"M_Idle");

}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
    CMonster* newMonster = new CMonster;
    if (nullptr != m_pAI)
    {
		newMonster->m_pAI = new AI;
    }
    return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
    CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 1.f;
		info.fAttRange = 200.f;
		info.fRecogRange = 600.f;
		info.fHp = 5.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::SHOTGUN:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 1.f;
		info.fAttRange = 200.f;
		info.fRecogRange = 600.f;
		info.fHp = 6.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}

		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);
	
	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
}

float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		m_tInfo.fHp -= 1;
		if (m_tInfo.fHp <= 0)
			DELETEOBJ(this);
	}
}
