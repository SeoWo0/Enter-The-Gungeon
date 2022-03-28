#include "framework.h"
#include "CEventManager.h"
#include "CGameObject.h"
#include "CScene.h"
#include "AI.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::Execute(const tEvent& event)
{
	switch (event.eEven)
	{
	case TYPE_EVENT::CREATE_OBJECT:
	{
		// lParam : Object �ּ�
		// wParam : Group 
		CGameObject* pObj = (CGameObject*)event.lParam;
		GROUP_GAMEOBJ group = (GROUP_GAMEOBJ)event.wParam;

		CSceneManager::GetInst()->GetCurScene()->AddObject(pObj, group);
	}
	break;
	case TYPE_EVENT::DELETE_OBJECT:
	{
		// lParam : Object �ּ�
		// Object�� ���� ���� ���·� ����
		// �������� ������Ʈ���� ��Ƶд�
		CGameObject* pObj = (CGameObject*)event.lParam;
		if (pObj->isDead())
			return;
		pObj->SetDead();
		m_vecDead.push_back(pObj);
	}
	break;
	case TYPE_EVENT::CHANGE_SCENE:
	{
		// lParam : scene �׷�
		GROUP_SCENE scene = (GROUP_SCENE)event.lParam;
		CUIManager::GetInst()->SetFocusedUI(nullptr);
		CSceneManager::GetInst()->ChangeScene(scene);
	}
	break;
	}
}

void CEventManager::update()
{
	// ��ϵ� ���� ���� ������Ʈ���� ����
	for (int i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// �̺�Ʈ ó��
	for (int i = 0; i < m_vecEvent.size(); i++)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::AddEvent(const tEvent& event)
{
	m_vecEvent.push_back(event);
}

void CEventManager::EventCreateObject(CGameObject* pObj, GROUP_GAMEOBJ group)
{
	tEvent event = {};
	event.eEven = TYPE_EVENT::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)pObj;
	event.wParam = (DWORD_PTR)group;

	AddEvent(event);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	tEvent event = {};
	event.eEven = TYPE_EVENT::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)pObj;

	AddEvent(event);
}

void CEventManager::EventChangeScene(GROUP_SCENE scene)
{
	tEvent event = {};
	event.eEven = TYPE_EVENT::CHANGE_SCENE;
	event.lParam = (DWORD_PTR)scene;

	AddEvent(event);
}

void CEventManager::EventChangeAIState(AI* ai, STATE_MON state)
{
	tEvent event = {};
	event.eEven = TYPE_EVENT::CHANGE_AI_STATE;
	event.lParam = (DWORD_PTR)ai;
	event.wParam = (DWORD_PTR)state;

	CEventManager::GetInst()->AddEvent(event);
}

