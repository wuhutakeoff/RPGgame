#include "Pet.h"

CPet::CPet()
{
	m_nLevel = 1;
	m_nLevelUpExp = 100;
}

CPet::CPet(CMonster* pMonster)
{
	m_nID = pMonster->getID();
	m_nHp = pMonster->getHp();
	m_nMp = pMonster->getMp();
	m_nAck = pMonster->getAck();
	m_nDef = pMonster->getDef();
	m_strPic = pMonster->getPic();
	m_strName = pMonster->getName();
	m_nExp = 0;
	m_nMoney = pMonster->getMoney();
	m_nLevel = 1;
	m_bIsFight = false;
	m_bIsFollow = false;
	m_nLevelUpExp = pMonster->getLevelUpExp();
	m_nMaxHp = m_nHp;
	m_nMaxMp = m_nHp;
}

bool CPet::isEquals(CVec2 pos)
{
	return m_vPos.x == pos.x && m_vPos.y == pos.y;
}

bool CPet::isEquals(int nRow, int nCol)
{
	return m_vPos.x == nRow && m_vPos.y == nCol;
}

void CPet::addExp(int nExp)
{
	m_nExp += nExp;
}

void CPet::onLevelUp()
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
