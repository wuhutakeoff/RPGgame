#include "Bag.h"
#include "Define.h"
#include "GameMgr.h" 
#include "Player.h"
#include "GameMap.h"
#include "Shop.h"
CBag::CBag()
{
    m_nCurIndex = 0;
	m_bInShop = false;
	m_bDelete = false;
}

CBag::~CBag()
{
}

void CBag::onUpdate()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		m_nCurIndex++;
		m_nCurIndex = m_nCurIndex >= m_vecDatas.size() ? m_vecDatas.size() - 1 : m_nCurIndex;
	}
	else if (KEY_DOWN(VK_UP))
	{
		m_nCurIndex--;
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		//
		//使用背包物品。
		if (m_vecDatas.size()<=0)
		{
			return;
		}
		this->useItem(m_vecDatas[m_nCurIndex]);
	}

	for (int i=0;i<m_vecDatas.size();i++)
	{
		if (m_vecDatas[i]->getCount()<=0)
		{
			m_vecDatas.erase(m_vecDatas.begin() + i);
		}
	}
}

void CBag::onRender()
{
	if (!m_bInShop)
	{
		cout << "装备栏" << endl;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getEquip()->bInBag = true;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getEquip()->showEquip();
	}

	cout << "背包"<<endl;
	cout << "  物品\t\t血量\t蓝量\t攻击力\t防御力\t价格\t数量\t描述" << endl;
	for (int i = 0; i < m_vecDatas.size(); i++)
	{
		if (i == m_nCurIndex)
		{
			cout << "->";
		}
		else
		{
			cout << "  ";
		}
		cout << m_vecDatas[i]->getName() << "\t\t"
			<< m_vecDatas[i]->getHp() << "\t"
			<< m_vecDatas[i]->getMp() << "\t"
			<< m_vecDatas[i]->getAck() << "\t"
			<< m_vecDatas[i]->getDef() << "\t"
			<< m_vecDatas[i]->getPrice() << "\t"
			<< m_vecDatas[i]->getCount() << "\t";
		if (i == m_nCurIndex)
		{
			cout << m_vecDatas[i]->getDescription();
		}
		else
		{
			cout << "                                                  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	g_bClear = true;
	cout <<"当前的钱："<< CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getMoney();
}

void CBag::useItem(CItem* pItem)
{
	g_bClear = true;
	CPlayer* pPlayer = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer();
	if (m_bInShop)
	{
		if (pItem->getCount() > 1) {
			pPlayer->addMoney(pItem->getPrice() / 2);
			pItem->addCount(-1);
			return;
		}
		pPlayer->addMoney(pItem->getPrice() / 2);
		m_vecDatas.erase(m_vecDatas.begin() + m_nCurIndex);
		m_nCurIndex--;
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		if (m_vecDatas.size()<=0)
		{
			CGameMgr::getInstance()->getWndByName<CShop>("Shop")->setOperatorBag(false);
		}
		SAFE_DEL(pItem);
		return;
	}

	//穿戴装备
	string strType = pItem->getType();
	if ("weapon" == strType || "armor" == strType)
	{
		CItem* pReplaceItem = pPlayer->getEquip()->addEquip(strType, pItem);

		//换下来的装备如果不为空，那么就还到背包。
		if (pReplaceItem)
		{
			m_vecDatas[m_nCurIndex] = pReplaceItem;
		}
		else
		{
			m_vecDatas.erase(m_vecDatas.begin() + m_nCurIndex);
			m_nCurIndex--;
			m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		}
	}

	if ("consumables"==strType)
	{

		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->useConsumble(pItem);
	}
}


void CBag::addItem(CItemDt* pItemDt)
{
	if (pItemDt&&0==pItemDt->nOverLying)
	{
		for (CItem* pItem : m_vecDatas)
		{
			if (pItem->getID()== pItemDt->nID)
			{
				pItem->addCount(1);
				return;
			}
		}
	}
	CItem* pItem = new CItem(pItemDt);
	m_vecDatas.push_back(pItem);
}

vector<CItem*> CBag::getItemByType(string Type)
{
	vector<CItem*> vecItems;
	for (CItem* item: m_vecDatas)
	{
		if (item->getType()==Type)
		{
			vecItems.push_back(item);
		}
	}
	return vecItems;
}
