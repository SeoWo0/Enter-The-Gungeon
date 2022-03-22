#include "framework.h"
#include "CScene_Title.h"
#include "CImageObject.h"
#include "CImageButton.h"

// AddFontResource(L"04B_03__.ttf");

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void ClickStartButton(DWORD_PTR, DWORD_PTR)
{
	CHANGESCN(GROUP_SCENE::STAGE);
}

void ClickQuitButton(DWORD_PTR, DWORD_PTR)
{
	PostQuitMessage(0);
}

void ClickMapToolButton(DWORD_PTR, DWORD_PTR)
{
	CHANGESCN(GROUP_SCENE::TOOL);
}


void CScene_Title::Enter()
{
	// 타이틀 화면 백그라운드
	CImageObject* BackgroundObject = new CImageObject;
	BackgroundObject->Load(L"BackGround", L"texture\\background\\background.png");
	BackgroundObject->SetPos(fPoint(0.f, 0.f));
	BackgroundObject->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BackgroundObject, GROUP_GAMEOBJ::BACKGROUND);
	
	// 타이틀 화면 로고
	CImageObject* TitleText = new CImageObject;
	TitleText->Load(L"TextTitle", L"texture\\background\\titletext.png");
	TitleText->SetPos(fPoint(350.f, 150.f));
	TitleText->SetScale(fPoint(580.f, 200.f));
	AddObject(TitleText, GROUP_GAMEOBJ::BACKGROUND);

	// 게임 시작 버튼
	CImageButton* StartButton = new CImageButton;
	StartButton->SetText(L"시작");
	StartButton->Load(L"StartButton", L"texture\\background\\black.png");
	StartButton->SetPos(fPoint(25.f, 510.f));
	StartButton->SetScale(fPoint(100.f, 50.f));
	StartButton->SetClickedCallBack(ClickStartButton, 0, 0);
	AddObject(StartButton, GROUP_GAMEOBJ::UI);

	// MapTool 버튼
	CImageButton* MapToolButton = new CImageButton;
	MapToolButton->SetText(L"맵 툴");
	MapToolButton->Load(L"MapToolButton", L"texture\\background\\black.png");
	MapToolButton->SetPos(fPoint(25.f, 560.f));
	MapToolButton->SetScale(fPoint(100.f, 50.f));
	MapToolButton->SetClickedCallBack(ClickMapToolButton, 0, 0);
	AddObject(MapToolButton, GROUP_GAMEOBJ::UI);
	
	// 게임 종료 버튼
	CImageButton* QuitButton = new CImageButton;
	QuitButton->SetText(L"종료");
	QuitButton->Load(L"QuitButton", L"texture\\background\\black.png");
	QuitButton->SetPos(fPoint(25.f, 610.f));
	QuitButton->SetScale(fPoint(100.f, 50.f));
	QuitButton->SetClickedCallBack(ClickQuitButton, 0, 0);
	AddObject(QuitButton, GROUP_GAMEOBJ::UI);
}

void CScene_Title::Exit()
{
}
