#pragma once
#include"Monster.h"
#include "WndBase.h"
#include "Pet.h"
class CPetBag:public CWndBase
{
public:
	CPetBag();
	void onUpdate();
	void onRender();
	void addPet(CPet* pPets);

	SYN_THE_SIZE_READONLY(vector< CPet*>, m_vecPets, Pets);


private:
	int m_nCurIndex;
	int m_nSelectIndex;
	int m_nCount;
	int m_nNum;
	bool m_bShowSelect;
};

