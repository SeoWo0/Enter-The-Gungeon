#include "framework.h"
#include "CImageButton.h"

CImageButton::CImageButton()
{
    m_pImg = nullptr;
    m_strText = L"";
}

CImageButton::~CImageButton()
{
}

void CImageButton::render()
{
    if (nullptr == m_pImg)
        return;

    CRenderManager::GetInst()->RenderImage(
        m_pImg,
        GetPos().x,
        GetPos().y,
        GetPos().x + GetScale().x,
        GetPos().y + GetScale().y
    );

    CRenderManager::GetInst()->RenderText(
        m_strText,
        GetPos().x,
        GetPos().y,
        GetPos().x + GetScale().x,
        GetPos().y + GetScale().y,
        30.f,
        RGB(255, 255, 255)
    );
}

void CImageButton::Load(const wstring& strKey, const wstring& strPath)
{
    m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strPath);
}

void CImageButton::SetText(const wstring& str)
{
    m_strText = str;
}
