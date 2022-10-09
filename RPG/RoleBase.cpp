#include "RoleBase.h"

CRoleBase::CRoleBase()
{
	m_bReverse = false;
	/*m_vPos.x = 0;
	m_vPos.y = 0;
	m_vPos.xBk = 0;
	m_vPos.yBk = 0;
	m_nID = 0;
	m_nAck = 0;
	m_nDef = 0;
	m_nExp = 0;
	m_nMoney = 0;
	m_strPic = "";
	m_strName = "";
	m_nHp = m_nMaxHp = 0;
	m_nMp = m_nMaxMp = 0;
	m_nAck = 0;
	m_nDef = 0;*/
}

CRoleBase::~CRoleBase()
{
}

void CRoleBase::onBackUp()
{
	m_vPos.xBk = m_vPos.x;
	m_vPos.yBk = m_vPos.y;
}

void CRoleBase::onRestore()
{
	m_vPos.x = m_vPos.xBk;
	m_vPos.y = m_vPos.yBk;
}


void CRoleBase::onRender()
{
	cout << m_strPic;
}

bool CRoleBase::isEuqals(int nX, int nY)
{
	return m_vPos.x == nX && m_vPos.y == nY;
}

void CRoleBase::setPosition(int nX, int nY)
{
	m_vPos.x = nX;
	m_vPos.y = nY;
}

bool CRoleBase::onDamage(int nDamage)
{
	m_nHp -= nDamage;
	return m_nHp <= 0;
}


void CRoleBase::setFightPosition(int nRow, int nCol)
{
	m_arrFightPos[0].x = nRow;
	m_arrFightPos[0].y = nCol;
	//¸ü¸Ä×´Ì¬Îª¿ÕÏÐ
	this->changeState(E_FIGHT_IDLE);
}

void CRoleBase::changeState(int nState)
{
	int nRow = m_arrFightPos[0].x;
	int nCol = m_arrFightPos[0].y;
	if (m_bReverse)
	{
		if (E_FIGHT_ATTACK == nState)
		{
			nState = E_FIGHT_BACK;
		}
		else if (E_FIGHT_BACK == nState)
		{
			nState = E_FIGHT_ATTACK;
		}
	}
	switch (nState)
	{
	case E_FIGHT_IDLE:
	{
		m_arrFightPos[1].x = nRow;
		m_arrFightPos[1].y = nCol - 1;
		m_arrFightPos[2].x = nRow;
		m_arrFightPos[2].y = nCol + 1;
		m_arrFightPos[3].x = nRow - 1;
		m_arrFightPos[3].y = nCol;
		m_arrFightPos[4].x = nRow + 1;
		m_arrFightPos[4].y = nCol;
		m_arrFightPos[5].x = nRow + 2;
		m_arrFightPos[5].y = nCol;
	}
	break;
	case E_FIGHT_ATTACK:
	{
		m_arrFightPos[1].x = nRow;
		m_arrFightPos[1].y = nCol + 2;
		m_arrFightPos[2].x = nRow;
		m_arrFightPos[2].y = nCol + 1;
		m_arrFightPos[3].x = nRow - 1;
		m_arrFightPos[3].y = nCol;
		m_arrFightPos[4].x = nRow + 1;
		m_arrFightPos[4].y = nCol;
		m_arrFightPos[5].x = nRow + 2;
		m_arrFightPos[5].y = nCol;
	}
	break;
	case E_FIGHT_BACK:
	{
		m_arrFightPos[1].x = nRow;
		m_arrFightPos[1].y = nCol - 1;
		m_arrFightPos[2].x = nRow;
		m_arrFightPos[2].y = nCol - 2;
		m_arrFightPos[3].x = nRow - 1;
		m_arrFightPos[3].y = nCol;
		m_arrFightPos[4].x = nRow + 1;
		m_arrFightPos[4].y = nCol;
		m_arrFightPos[5].x = nRow + 2;
		m_arrFightPos[5].y = nCol;
	}
	break;
	}
}

bool CRoleBase::isContain(int nRow, int nCol)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_arrFightPos[i].x == nRow && m_arrFightPos[i].y == nCol)
		{
			return true;
		}
	}
	return false;
}

void CRoleBase::onFightMove(int nOffsetCol)
{
	for (int i = 0; i < 6; i++)
	{
		m_arrFightPos[i].y += nOffsetCol;
	}
}
