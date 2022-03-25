#include "framework.h"
#include "CScene_MapTool.h"
#include "CTile.h"
#include "resource.h"
#include "CScene.h"
#include "CD2DImage.h"
#include "commdlg.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CTileButton.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_MapTool::CScene_MapTool()
{
	m_pMap = nullptr;

	m_hWnd = 0;
	m_iIdx = 0;
	m_gTile = GROUP_TILE::NONE;
	m_velocity = 1000;
	m_iTileX = 0;
	m_iTileY = 0;
}

CScene_MapTool::~CScene_MapTool()
{
}

void CScene_MapTool::update()
{
	CScene::update();

	if (KEYDOWN(VK_TAB))
	{
		CHANGESCN(GROUP_SCENE::TITLE);
	}

	if (KEY(VK_LEFT))
	{
		CCameraManager::GetInst()->Scroll(fVec2(-1, 0), m_velocity);
	}
	if (KEY(VK_RIGHT))
	{
		CCameraManager::GetInst()->Scroll(fVec2(1, 0), m_velocity);
	}
	if (KEY(VK_UP))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, -1), m_velocity);
	}
	if (KEY(VK_DOWN))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, 1), m_velocity);
	}

	SetTileIdx();
	SetTileGroup();
}

void CScene_MapTool::render()
{
	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->render();
	}

	PrintMap();
	PrintTileLine();
	PrintTileGroup();

	const vector<CGameObject*>& vecUI = GetGroupObject(GROUP_GAMEOBJ::UI);
	for (UINT i = 0; i < vecUI.size(); i++)
	{
		vecUI[i]->render();
	}
}

void CScene_MapTool::Enter()
{
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);
	ShowWindow(m_hWnd, SW_SHOW);

	CreateTile(20, 20);
	CreateTilePanel();

	CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CScene_MapTool::Exit()
{
	EndDialog(m_hWnd, IDOK);
	DeleteAll();
}

void CScene_MapTool::SetIdx(UINT idx)
{
	m_iIdx = idx;
}

void CScene_MapTool::SetTileIdx()
{
	if (KEY(VK_LBUTTON) || KEY(VK_RBUTTON))
	{
		fPoint fptMousePos = MOUSEPOS();
		fptMousePos = CCameraManager::GetInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// Ÿ���� ���� ��ġ ����
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (KEY(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		else if (KEY(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(0);
	}
}

void CScene_MapTool::SetGroup(GROUP_TILE group)
{
	m_gTile = group;
}

void CScene_MapTool::SetTileGroup()
{
	if (KEY(VK_LBUTTON) || KEY(VK_RBUTTON))
	{
		fPoint fptMousePos = MOUSEPOS();
		fptMousePos = CCameraManager::GetInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// Ÿ���� ���� ��ġ ����
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (KEY(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(m_gTile);
		else if (KEY(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(GROUP_TILE::NONE);
	}
}

void CScene_MapTool::CreateTile(UINT xSize, UINT ySize)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	m_iTileX = xSize;
	m_iTileY = ySize;

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

	for (UINT y = 0; y < ySize; y++)
	{
		for (UINT x = 0; x < xSize; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(fPoint((float)(x * CTile::SIZE_TILE), (float)(y * CTile::SIZE_TILE)));
			pTile->SetX(x);
			pTile->SetY(y);
			pTile->SetD2DImage(pImg);
			AddObject(pTile, GROUP_GAMEOBJ::TILE);
		}
	}
}

void CScene_MapTool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileX;
	UINT yCount = m_iTileY;
	UINT tileCount = 0;

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_MapTool::LoadTile(const wstring& strPath)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	CTile* pTile = new CTile;

	for (UINT i = 0; i < tileCount; i++)
	{
		pTile->Load(pFile);
		UINT iIdx = pTile->GetY() * xCount + pTile->GetX();
		((CTile*)vecTile[iIdx])->SetX(pTile->GetX());
		((CTile*)vecTile[iIdx])->SetY(pTile->GetY());
		((CTile*)vecTile[iIdx])->SetImgIdx(pTile->GetIdx());
		((CTile*)vecTile[iIdx])->SetGroup(pTile->GetGroup());
	}

	fclose(pFile);
}

void CScene_MapTool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd;					// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_MapTool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd; // �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CScene_MapTool::LoadMap()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd; // �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0Image\0*.png"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"map";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		m_pMap = CResourceManager::GetInst()->LoadToolD2DImage(szName);
	}
}

void ClickTileGroupButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CButtonUI
	CScene_MapTool* scene_tool = (CScene_MapTool*)param1;
	CButtonUI* button = (CButtonUI*)param2;
	scene_tool->ClickTileGroup(button);
}

void CScene_MapTool::ClickTileGroup(CButtonUI* button)
{
	if (m_gTile == GROUP_TILE::NONE)
	{
		m_gTile = GROUP_TILE::GROUND;
		button->SetText(L"GROUND");
	}
	else if (m_gTile == GROUP_TILE::GROUND)
	{
		m_gTile = GROUP_TILE::WALL;
		button->SetText(L"WALL");
	}
	else if (m_gTile == GROUP_TILE::WALL)
	{
		m_gTile = GROUP_TILE::NONE;
		button->SetText(L"NONE");
	}
}

void ClickTileButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CTileButton
	CScene_MapTool* scene_tool = (CScene_MapTool*)param1;
	CTileButton* button = (CTileButton*)param2;
	scene_tool->ClickTile(button);
}

void CScene_MapTool::ClickTile(CTileButton* button)
{
	SetIdx(button->GetIdx());
}

void CScene_MapTool::CreateTilePanel()
{
	CPanelUI* panelTile = new CPanelUI;
	panelTile->SetName(L"panelTile");
	panelTile->SetScale(fPoint(400.f, 600.f));
	panelTile->SetPos(fPoint(WINSIZEX - 450.f, 50.f));

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	for (UINT y = 0; y < 7; y++)
	{
		for (UINT x = 0; x < 6; x++)
		{
			CTileButton* btnTile = new CTileButton;
			btnTile->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
			btnTile->SetPos(fPoint((float)x * CTile::SIZE_TILE, (float)y * CTile::SIZE_TILE));
			btnTile->SetPos(btnTile->GetPos() + fPoint(8.f, 8.f));
			btnTile->SetImage(pImg);
			btnTile->SetIdx(y * 6 + x);
			btnTile->SetClickedCallBack(ClickTileButton, (DWORD_PTR)this, (DWORD_PTR)btnTile);
			panelTile->AddChild(btnTile);
		}
	}

	CButtonUI* btnTileGroup = new CButtonUI;
	btnTileGroup->SetScale(fPoint(100.f, 50.f));
	btnTileGroup->SetPos(fPoint(50.f, 500.f));
	btnTileGroup->SetText(L"NONE");
	btnTileGroup->SetClickedCallBack(ClickTileGroupButton, (DWORD_PTR)this, (DWORD_PTR)btnTileGroup);
	panelTile->AddChild(btnTileGroup);

	AddObject(panelTile, GROUP_GAMEOBJ::UI);
}

void CScene_MapTool::PrintMap()
{
	if (nullptr == m_pMap)
		return;

	fPoint pos = CCameraManager::GetInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	CRenderManager::GetInst()->RenderImage(
		m_pMap,
		0 - pos.x,
		0 - pos.y,
		2 * m_pMap->GetWidth() - pos.x,
		2 * m_pMap->GetHeight() - pos.y
	);
}

void CScene_MapTool::PrintTileLine()
{
	fPoint pos = CCameraManager::GetInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	// ������ ���
	for (UINT y = 0; y <= m_iTileY; y++)
	{
		CRenderManager::GetInst()->RenderLine(
			fPoint(0 - pos.x, y * CTile::SIZE_TILE - pos.y),
			fPoint(CTile::SIZE_TILE * m_iTileX - pos.x, y * CTile::SIZE_TILE - pos.y)
		);
	}

	// ������ ���
	for (UINT x = 0; x <= m_iTileX; x++)
	{
		CRenderManager::GetInst()->RenderLine(
			fPoint(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			fPoint(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y)
		);
	}
}

void CScene_MapTool::PrintTileGroup()
{
	fPoint pos = CCameraManager::GetInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CTile* pTile;

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		pTile = (CTile*)vecTile[i];
		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{
			CRenderManager::GetInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 0, 0),
				3.f
			);
		}
		else if (GROUP_TILE::WALL == pTile->GetGroup())
		{
			CRenderManager::GetInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 0),
				3.f
			);
		}
	}
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SAVE)
		{
			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CScene_MapTool* pToolScene = dynamic_cast<CScene_MapTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_LOAD)
		{
			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CScene_MapTool* pToolScene = dynamic_cast<CScene_MapTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_MAP)
		{
			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CScene_MapTool* pToolScene = dynamic_cast<CScene_MapTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadMap();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CScene_MapTool* pToolScene = dynamic_cast<CScene_MapTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_GAMEOBJ::TILE);
			pToolScene->CreateTile(x, y);
		}
		break;
	}
	return (INT_PTR)FALSE;
}