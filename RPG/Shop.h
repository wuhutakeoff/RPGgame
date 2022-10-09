#pragma once
#include"DataStruct.h"
#include "WndBase.h"
class CShop:public CWndBase
{
public:
	CShop();
	void onUpdate();
	void onRender();
	void refreshItem(int nNpcID);
	SYN_THE_SIZE(bool, m_bOperatorBag, OperatorBag)

private:
	vector<CItemDt*> m_vecDatas;
	int m_nCurIndex;
	int m_nState;
	int nTime;
};

