#pragma once
#include"Define.h"
#include"DataStruct.h"
#include"Item.h"
#include "WndBase.h"
class CBag:public CWndBase
{
public:
	CBag();
	~CBag();
	void onUpdate();
	void onRender();
	void useItem(CItem* pItem);
	//添加物品函数，
	void addItem(CItemDt* pItemDt);
	vector<CItem*> getItemByType(string Type);
	SYN_THE_SIZE(int, m_nCurIndex, CurIndex);
	SYN_THE_SIZE(bool, m_bInShop, InShop);

private:
	vector<CItem*> m_vecDatas;

};



