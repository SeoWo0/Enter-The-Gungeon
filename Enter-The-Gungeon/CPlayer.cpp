#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (KEY('W'))
	{
		pos.y -= 150 * fDT;
	}

	if (KEY('S'))
	{
		pos.y += 150 * fDT;
	}
	
	if (KEY('A'))
	{
		pos.x -= 150 * fDT;
	}

	if (KEY('D'))
	{
		pos.x += 150 * fDT;
	}

	SetPos(pos);
}

void CPlayer::render(HDC hDC)
{
	Rectangle(hDC,
			(int)GetPos().x
				)
}
