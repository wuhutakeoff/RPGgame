#include "Equip.h"
#include"DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"
CEquip::CEquip()
{
	this->init();
}

CEquip::~CEquip()
{
}

void CEquip::init()
{
	m_nCount = 0;
	bInBag = false;
	m_mapShowInfo = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getEquipInfo();
	//遍历这个容器，给装备置空。
	for (auto iter: m_mapShowInfo)
	{
		m_mapEquip[iter.first] = nullptr;
	}
}


//穿装备接口。
//返回换下来的装备。
CItem* CEquip::addEquip(string strName, CItem* pItem)
{
	int nCount = m_mapEquip.count(strName);
	if (nCount <= 0)
	{
		return nullptr;
	}
	//如果这种类型到装备栏获取到是空指针。没有装备。
	if (!m_mapEquip[strName])
	{
		m_mapEquip[strName] = pItem;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->addAttribute(pItem);
		//穿装备。
		return nullptr;
	}
	
	//已经有一件这种类型的装备。
	CItem* pTempItem = m_mapEquip[strName];
	m_mapEquip[strName] = pItem;
	return pTempItem;

}

void CEquip::showEquip()
{
	for (auto iter : m_mapShowInfo)
	{
		if (!bInBag)
		{
			cout << "							";
		}
		cout << iter.second << ":";
		string strName = m_mapEquip[iter.first] ? m_mapEquip[iter.first]->getName() : "无";
		cout << strName << endl;
	}
	cout << endl;

}
