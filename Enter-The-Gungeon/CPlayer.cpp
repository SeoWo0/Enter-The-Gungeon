#include "framework.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CBullet.h"


CPlayer::CPlayer()
{
	/*m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Player", L"texture\\animation\\Player_idle");
	SetName(L"Player");
	SetScale(fPoint(50.f, 50.f));
	
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"None", m_pImg, fPoint()
	*/

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

	if (VK_LBUTTON)
	{
		// TODO:ÃÑ¾Ë ¹ß»ç ±¸Çö
	}

	if (VK_RBUTTON)
	{
		// TODO:´åÁö ·Ñ ±¸Çö
	}

	if (KEYDOWN('Q'))
	{
		// TODO:¼¶±¤Åº ±â´É ±¸Çö
	}
}

void CPlayer::render(HDC hDC)
{
	Rectangle(hDC,
		(int)GetPos().x,
		(int)GetPos().y,
		(int)GetPos().x + GetScale().x,
		(int)GetPos().y + GetScale().y
	);
}
