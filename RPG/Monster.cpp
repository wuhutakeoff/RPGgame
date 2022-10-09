#include "Monster.h"
#include "GameMgr.h"
#include"GameMap.h"
CMonster::CMonster()
	:m_nDir(E_DIR_NONE), m_nTime(0)
{
	m_nLevel = 1;
	m_nLevelUpExp = 100;
	m_nExp = 0;
}

CMonster::CMonster(CMonster* pMonster)
{
	
	
}

CMonster::~CMonster()
{
}

void CMonster::initWithData(CMonsterDt* pMonsterDt)
{
	m_pMonsterDt = pMonsterDt;
	m_nID = pMonsterDt->nID;
	m_nHp = pMonsterDt->nHp;
	m_nMp = pMonsterDt->nMp;
	m_nAck = pMonsterDt->nAck;
	m_nDef = pMonsterDt->nDef;
	m_strPic = pMonsterDt->strPic;
	m_strName = pMonsterDt->strName;
	m_nExp = pMonsterDt->nExp;
	m_nMoney = pMonsterDt->nMoney;
	m_nMapID = pMonsterDt->nMapID;
	m_nItemID = pMonsterDt->nItemID;
	m_nMove = pMonsterDt->nMove;
	m_nMoveInterval = pMonsterDt->nMoveInterval;
	m_nLevel = 1;
	m_nLevelUpExp = 100;
	m_nMaxHp = m_nHp;
}

bool CMonster::isEquals(int nRow, int nCol, int nMapID)
{
	return m_vPos.x == nRow && m_vPos.y == nCol && m_nMapID == nMapID;
}

bool CMonster::isEquals(CVec2 pos)
{
	return m_vPos.x == pos.x && m_vPos.y == pos.y;
}


void CMonster::onMove(map<int, CVec2> mapDir)
{
	if (0 == m_nMove)
	{
		return;
	}

	int nCurMapID = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getCurMapDt()->nID;
	if (nCurMapID != m_nMapID)
	{
		return;
	}
	m_nTime++;
	if (m_nTime >= m_nMoveInterval)
	{
		m_nTime = 0;
		m_nDir = 1 + rand() % 4;
	}
	this->onBackUp();
	m_vPos.x += mapDir[m_nDir].x;
	m_vPos.y += mapDir[m_nDir].y;
}



void CMonster::changeDir()
{
	m_nDir = 1 + rand() % 4;
}

void CMonster::onRecovery()
{
	this->initWithData(m_pMonsterDt);
}
