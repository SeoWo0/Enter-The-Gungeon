#include "framework.h"
#include "CSceneManager.h"
#include "CScene_Title.h"
#include "CScene_Stage.h"

CSceneManager::CSceneManager()
{
	// �� ��� �ʱ�ȭ
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// �� ��� ����
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::TITLE] = new CScene_Title;
	m_arrScene[(size_t)GROUP_SCENE::TITLE]->SetName(L"Title_Scene");

	m_arrScene[(size_t)GROUP_SCENE::STAGE] = new CScene_Stage;
	m_arrScene[(size_t)GROUP_SCENE::STAGE]->SetName(L"Stage_Scene");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::TITLE];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
