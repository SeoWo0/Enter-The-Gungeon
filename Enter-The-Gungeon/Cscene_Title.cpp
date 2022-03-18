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
	// CHANGESCN(GROUP_SCENE::STAGE);
}



void CScene_Title::Enter()
{
	// 타이틀 화면 백그라운드
	CImageObject* backgroundObject = new CImageObject;
	backgroundObject->Load(L"BackGround", L"texture\\background\\background.png");
	backgroundObject->SetPos(fPoint(0.f, 0.f));
	backgroundObject->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(backgroundObject, GROUP_GAMEOBJ::BACKGROUND);
	
	// 타이틀 화면 로고
	CImageObject* titleText = new CImageObject;
	titleText->Load(L"TextTitle", L"texture\\background\\titletext.png");
	titleText->SetPos(fPoint(350.f, 150.f));
	titleText->SetScale(fPoint(580.f, 200.f));
	AddObject(titleText, GROUP_GAMEOBJ::BACKGROUND);

	// 게임 시작 버튼
	CImageButton* startbutton = new CImageButton;
	startbutton->SetName(L"시작");
	startbutton->SetPos(fPoint(100.f, 500.f));
	startbutton->SetScale(fPoint(100.f, 50.f));
	startbutton->SetClickedCallBack(ClickStartButton, 0, 0);
	AddObject(startbutton, GROUP_GAMEOBJ::UI);

}

void CScene_Title::Exit()
{
}
