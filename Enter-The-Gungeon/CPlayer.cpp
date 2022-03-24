#include "framework.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CBullet.h"


CPlayer::CPlayer()
{
	m_pImgIdle = CResourceManager::GetInst()->LoadD2DImage(L"Player_Idle", L"texture\\Animation\\PlayerIdle.png");
	SetName(L"Player_Idle");
	SetScale(fPoint(40.f, 60.f));

	m_pImgWalk = CResourceManager::GetInst()->LoadD2DImage(L"Player_Walk", L"texture\\Animation\\PlayerWalk.png");
	SetName(L"Player_Walk");

	m_pImgDodge = CResourceManager::GetInst()->LoadD2DImage(L"Player_Dodge", L"texture\\Animation\\Dodge.png");
	SetName(L"Dodge");

	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));


	CreateAnimator();

	// 플레이어 가만히 있을 때
	GetAnimator()->CreateAnimation(L"Idle", m_pImgIdle, fPoint(0.f, 0.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightIdle", m_pImgIdle, fPoint(0.f, 60.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);
	//GetAnimator()->CreateAnimation(L"LeftIdle", m_pImgIdle, fPoint(0.f, 58.5f), fPoint(40.f, 58.5f), fPoint(40.f, 0.f), 0.25f, 4);
	GetAnimator()->CreateAnimation(L"BackIdle", m_pImgIdle, fPoint(0.f, 120.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightDiagIdle", m_pImgIdle, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);
	//GetAnimator()->CreateAnimation(L"LeftDiagIdle", m_pImgIdle, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);

	// 플레이어 걸을 때
	GetAnimator()->CreateAnimation(L"FrontWalk", m_pImgWalk, fPoint(0.f, 0.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightWalk", m_pImgWalk, fPoint(0.f, 60.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	//GetAnimator()->CreateAnimation(L"LeftWalk", m_pImgWalk, fPoint(0.f, 60.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"BackWalk", m_pImgWalk, fPoint(0.f, 120.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightDiagWalk", m_pImgWalk, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	//GetAnimator()->CreateAnimation(L"LeftDiagWalk", m_pImgWalk, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);

	// 닷지 롤
	GetAnimator()->CreateAnimation(L"FrontDodge", m_pImgDodge, fPoint(0.f, 0.f), fPoint(60.f, 54.f), fPoint(60.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"RightDodge", m_pImgDodge, fPoint(0.f, 54.f), fPoint(60.f, 54.f), fPoint(60.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"BackDodge", m_pImgDodge, fPoint(0.f, 108.f), fPoint(60.f, 54.f), fPoint(60.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"RightDiagDodge", m_pImgDodge, fPoint(0.f, 162.f), fPoint(60.f, 54.f), fPoint(60.f, 0.f), 0.1f, 9);

	GetAnimator()->Play(L"Idle");
}

CPlayer::~CPlayer()
{
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (KEY('W'))
	{
		pos.y -= m_fSpeed * fDT;
	}

	if (KEY('S'))
	{
		pos.y += m_fSpeed * fDT;
	}

	if (KEY('A'))
	{
		pos.x -= m_fSpeed * fDT;
	}

	if (KEY('D'))
	{
		pos.x += m_fSpeed * fDT;
	}

	SetPos(pos);

	if (KEY(VK_LBUTTON) || KEYDOWN(VK_LBUTTON))
	{
		
	}

	if (KEYDOWN(VK_RBUTTON))
	{
		GetAnimator()->Play(L"BackDodge");
	}
	if (KEYDOWN('Q'))
	{
		// TODO:섬광탄 기능 구현
	}

	GetAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	component_render();

}
