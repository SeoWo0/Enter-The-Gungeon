#include "framework.h"
#include "CPanelUI.h"

CPanelUI::CPanelUI()
	: CUI(false)
{
	m_fptDragStart = {};
}

CPanelUI::~CPanelUI()
{
}

CPanelUI* CPanelUI::Clone()
{
	return new CPanelUI(*this);
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		fPoint fptDiff = MOUSEPOS() - m_fptDragStart;

		fPoint fptCurPos = GetPos();
		fptCurPos += fptDiff;
		SetPos(fptCurPos);

		m_fptDragStart = MOUSEPOS();
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_fptDragStart = MOUSEPOS();
}

void CPanelUI::MouseLbtnUp()
{
}
