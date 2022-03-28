#include "framework.h"
#include "CBullet.h"
#include "CCollider.h"

CBullet::CBullet()
{
	m_pImgPlayerBullet = CResourceManager::GetInst()->LoadD2DImage(L"PlayerBullet", L"texture\\Animation\\PlayerBullet.png");
	SetName(L"PlayerBullet");
	SetScale(fPoint(20.f, 20.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale());
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
	fPoint pos = GetPos();

	pos += m_fvDIr * m_fSpeed * fDT;

	SetPos(pos);
}

void CBullet::render()
{

	fPoint RenderPos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	CRenderManager::GetInst()->RenderImage(m_pImgPlayerBullet,
		RenderPos.x,
		RenderPos.y,
		RenderPos.x + GetScale().x,
		RenderPos.y + GetScale().y
	);

	component_render();
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
	DELETEOBJ(this);
}




