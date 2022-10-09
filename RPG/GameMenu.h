#pragma once
#include "WndBase.h"

class CGameMenu:public CWndBase
{
public:
	CGameMenu();
	void onUpdate();
	void onRender();
private:
	int m_nMenuState;
};

