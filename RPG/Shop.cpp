#include "Shop.h"
#include "Define.h"
#include"GameMgr.h"
#include"DataMgr.h"
#include"GameMap.h"
CShop::CShop()
	:m_nCurIndex(0)
	, m_nState(E_BUY_IDLE)
	, nTime(0)
	, m_bOperatorBag(false)
{
}


void CShop::onUpdate()
{
	if (KEY_DOWN(VK_SPACE))
	{
		m_bOperatorBag = !m_bOperatorBag;
	}

	if (m_bOperatorBag)
	{
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onUpdate();
		return;
	}

	if (KEY_DOWN(VK_ESCAPE))
	{
		g_bClear = true;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->setInShop(false);
		CGameMgr::getInstance()->restoreWnd();
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
		m_nState = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->buyItem(m_vecDatas[m_nCurIndex]);
		nTime = 0;
	}

	nTime++;
	if (nTime >= 10)
	{
		m_nState = E_BUY_IDLE;
	}
}

void CShop::onRender()
{
	cout << "商店" << endl;
	cout << "  物品\t\t血量\t蓝量\t攻击力\t防御力\t价格\t描述" << endl;
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
		cout << m_vecDatas[i]->strName << "\t"
			<< m_vecDatas[i]->nHp << "\t"
			<< m_vecDatas[i]->nMp << "\t"
			<< m_vecDatas[i]->nAck << "\t"
			<< m_vecDatas[i]->nDef << "\t"
			<< m_vecDatas[i]->nPrice << "\t";
		if (i == m_nCurIndex)
		{
			cout << m_vecDatas[i]->strDescription;
		}
		else
		{
			cout << "                                                            ";
		}
		cout << endl;
	}

	if (E_BUY_IDLE == m_nState)
	{
		cout << "                                             " << endl;
	}
	else if (E_BUY_FAILED == m_nState)
	{
		cout << "你身上的钱不够，购买失败!" << endl;
	}
	else if (E_BUY_SECCUSS == m_nState)
	{
		cout << "购买成功！" << endl;
	}


	CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onRender();
}

void CShop::refreshItem(int nNpcID)
{
	m_vecDatas = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByNpcID(nNpcID);
	m_nCurIndex = 0;
	m_bOperatorBag = false;
	CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->setCurIndex(0);
	CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->setInShop(true);

}
