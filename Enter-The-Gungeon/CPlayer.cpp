#include "framework.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CBullet.h"


CPlayer::CPlayer()
{
	m_pImgIdle = CResourceManager::GetInst()->LoadD2DImage(L"Player_Idle", L"texture\\Animation\\PlayerIdle.bmp");
	SetName(L"Player_Idle");
	SetScale(fPoint(40.f, 60.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle", m_pImgIdle, fPoint(0.f, 0.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightIdle", m_pImgIdle, fPoint(0.f, 60.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);
	//GetAnimator()->CreateAnimation(L"LeftIdle", m_pImgIdle, fPoint(0.f, 58.5f), fPoint(40.f, 58.5f), fPoint(40.f, 0.f), 0.25f, 4);
	GetAnimator()->CreateAnimation(L"BackIdle", m_pImgIdle, fPoint(0.f, 120.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 6);
	GetAnimator()->CreateAnimation(L"RightDiagIdle", m_pImgIdle, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);
	//GetAnimator()->CreateAnimation(L"LeftDiagIdle", m_pImgIdle, fPoint(0.f, 180.f), fPoint(40.f, 60.f), fPoint(40.f, 0.f), 0.25f, 4);
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
		// TODO:ÃÑ¾Ë ¹ß»ç ±¸Çö
	}

	if (KEYDOWN(VK_RBUTTON))
	{
		// TODO:´åÁö ·Ñ ±¸Çö
	}

	if (KEYDOWN('Q'))
	{
		// TODO:¼¶±¤Åº ±â´É ±¸Çö
	}

	GetAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	component_render();

}
