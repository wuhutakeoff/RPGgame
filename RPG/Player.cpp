#include "Player.h"
#include "Define.h"
#include"DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"
#include "AStar.h"
CPlayer::CPlayer()
{
	m_vPos.x = 0;
	m_vPos.y = 0;
	m_vPos.xBk = 0;
	m_vPos.yBk = 0;
	m_pBag = new CBag();
	m_nMoney = 50000;
	m_pEquip = new CEquip();
	m_nRange = 3;
	m_strPic = "ս";
	m_strName = "սʿ";
	m_nHp = m_nMaxHp ;
	m_nMp = m_nMaxMp ;
	m_nAck = 100;
	m_nDef = 20;
	m_nLevel = 1;
	m_nExp = 0;
	m_nLevelUpExp = 100;
	m_pPetBag = new CPetBag();
}


void CPlayer::onUpdate()
{

	this->onBackUp();
	if (m_pCurPet)
	{
		m_pCurPet->onBackUp();
	}
	if (KEY_DOWN(VK_UP))
	{
		m_vPos.x--;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->setNull();
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_vPos.x++;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->setNull();
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_vPos.y--;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->setNull();
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_vPos.y++;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->setNull();
	}
	if (KEY_DOWN(VK_LCONTROL))
	{
		m_nRange--;
		m_nRange = m_nRange <= 2 ? 2 : m_nRange;
	}
	else if (KEY_DOWN(VK_RCONTROL))
	{
		m_nRange++;
		m_nRange = m_nRange >= 8 ? 8 : m_nRange;
	}
	onLevelUp();

	if (m_nHp>m_nMaxHp)
	{
		m_nHp = m_nMaxHp;
	}
	if (m_nMp>m_nMaxMp)
	{
		m_nMp = m_nMaxMp;
	}
	if (m_pCurPet &&m_pCurPet->getIsFollow())
	{
		m_pCurPet->setPosition(m_vPos.xBk, m_vPos.yBk);
		if (m_pCurPet->isEquals(m_vPos))
		{
			m_pCurPet->onRestore();
		}
	}

}

int CPlayer::buyItem(CItemDt* pItemDt)
{
	if (m_nMoney >= pItemDt->nPrice)
	{
		m_nMoney -= pItemDt->nPrice;
		m_pBag->addItem(pItemDt);
		return E_BUY_SECCUSS;
	}
	return E_BUY_FAILED;
}

void CPlayer::addMoney(int nMoney)
{
	m_nMoney += nMoney;
}

bool CPlayer::isOutOfView(int nRow, int nCol)
{
	return m_vPos.x - m_nRange > nRow || m_vPos.x + m_nRange < nRow || m_vPos.y - m_nRange > nCol || m_vPos.y + m_nRange < nCol;
}


void CPlayer::initData(CRoleDt* pRoleDt)
{
	m_strPic = pRoleDt->strPic;
	m_strName = pRoleDt->strName;
	m_nHp =  pRoleDt->nHp;
	m_nMaxHp = pRoleDt->nHp;
	m_nMp =  pRoleDt->nMp;
	m_nMaxMp = pRoleDt->nMp;
	m_nAck = pRoleDt->nAck;
	m_nDef = pRoleDt->nDef;
	m_nSpeed = pRoleDt->nSpeed;
	m_strProfession = pRoleDt->strProfession;
	m_nID = pRoleDt->nID;
	vector<CSkillDt*> vecSkillDts = CDataMgr::getInstance()->getMgr<CSkillDtMgr>("SkillDtMgr")->getDatasByRoleID(m_nID);
	for (CSkillDt* skillDt : vecSkillDts) {
		CSkill* skill = new CSkill();
		skill->setPosition(m_vPos);
		skill->initWithData(skillDt);
		m_vecSkills.push_back(skill);
	}

}

void CPlayer::useConsumble(CItem* pItem)
{
	m_nAck += pItem->getAck() > 0 ? pItem->getAck() : 0;
	m_nDef += pItem->getDef() > 0 ? pItem->getDef() : 0;
	m_nHp += pItem->getHp() > 0 ? pItem->getHp() : 0;
	m_nMp += pItem->getMp() > 0 ? pItem->getMp() : 0;

	m_nHp = m_nHp + pItem->getHp() > m_nMaxHp ? m_nMaxHp : m_nHp;
	m_nMp = m_nMp + pItem->getMp() > m_nMaxMp ? m_nMaxMp : m_nMp;

	if (pItem->getID()==3008)
	{
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->changeMap(1001);
	}
	else if (pItem->getID() == 3009)
	{
		m_nExp += 100;
	}
	pItem->setCount(pItem->getCount() - 1);
}

void CPlayer::addExp(int nExp)
{
	m_nExp += nExp;
}

void CPlayer::taskAwad(int nTaskMoney,int nTaskExp)
{
	m_nMoney += nTaskMoney;
	m_nExp += nTaskExp;
}


void CPlayer::onLevelUp()
{
	//判断经验是否大于或者等于升级经验。
	if (m_nExp >= m_nLevelUpExp)
	{
		m_nExp -= m_nLevelUpExp;
		//等级加1
		m_nLevel++;
		//玩家属性修改。
		//要先回复满血，
		m_nHp = m_nMaxHp;
		m_nHp += 50;
		m_nMaxHp = m_nHp;
		m_nMp += 10;
		m_nAck += 5;
		m_nDef += 5;
		//下一级的升级经验。
		m_nLevelUpExp += (m_nLevel * 100);
	}
}

void CPlayer::autoMove(CVec2 distanct)
{
	/*if (point.x>m_vPos.x)
	{
		m_vPos.x++;
	}
	else if (point.y>m_vPos.y)
	{
		m_vPos.y++;
	}
	else if (point.x<m_vPos.x)
	{
		m_vPos.x--;
	}
	else if (point.y<m_vPos.y)
	{
		m_vPos.y--;
	}*/

	//vector<Point*> vecPoint;
	//for (list<Point*>::iterator iter=path.begin();iter!=path.end();iter++)
	//{
	//	vecPoint.push_back(*iter);
	//}



	if (it!=path.end())
	{
		m_vPos.x = (*it)->x;
		m_vPos.y = (*it)->y;
		it++;
	}

}

void CPlayer::addAttribute(CItem* pItem)
{
	m_nAck += pItem->getAck();
	m_nDef += pItem->getDef();
	m_nHp += pItem->getHp();
	m_nMp += pItem->getMp();
}
