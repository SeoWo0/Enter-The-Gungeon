#pragma once
#include "CButtonUI.h"

class CD2DImage;

class CImageButton : public CButtonUI
{
private:
	CD2DImage* m_pImg;
	wstring m_strText;

public:
	CImageButton();
	virtual ~CImageButton();

	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);
	void SetText(const wstring& str);
};

