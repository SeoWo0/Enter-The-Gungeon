#include "framework.h"
#include "CBullet.h"

CBullet::CBullet()
{
	m_bIsShoot = true;
}

CBullet::~CBullet()
{
}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}

void CBullet::update()
{
}

void CBullet::render()
{
}

void CBullet::SetDir(fVec2 vec)
{
	m_fvDIr = vec;
}

void CBullet::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

void CBullet::OnCollisionEnter(CCollider* pOther)
{

}

bool CBullet::Cantshoot()
{
	return !m_bIsShoot;
}


