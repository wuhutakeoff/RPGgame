#pragma once
#include"Item.h"
#include<map>
#include<unordered_map>
using namespace std;
class CEquip
{
public:
	CEquip();
	~CEquip();
	void init();
	CItem* addEquip(string strName, CItem* pItem);
	void showEquip();
	bool bInBag;

private:
	map<string, CItem*> m_mapEquip;
	unordered_map<string, string> m_mapShowInfo;
	int m_nCount;
};



 