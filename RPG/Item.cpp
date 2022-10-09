#include "Item.h"

CItem::CItem()
{
	m_nID = 0;
	m_strName = "";
	m_nHp = 0;
	m_nMp = 0;
	m_nAck = 0;
	m_nDef = 0;
	m_strPic = "";
	m_strDescription = "";
	m_nPrice = 0;
	m_nCount = 0;
}

CItem::CItem(CItemDt* pItemDt)
{
	m_nID = pItemDt->nID;
	m_strName = pItemDt->strName;
	m_nHp = pItemDt->nHp;
	m_nMp = pItemDt->nMp;
	m_nAck = pItemDt->nAck;
	m_nDef = pItemDt->nDef;
	m_strPic = pItemDt->strPic;
	m_strDescription = pItemDt->strDescription;
	m_nPrice = pItemDt->nPrice;
	m_strType = pItemDt->strType;
	m_nCount = 1;
}

CItem::CItem(string strName, int nHp, int nMp, int nAck, int nDef, int nCount)
{
	m_strName = strName;
	m_nHp = nHp;
	m_nAck = nAck;
	m_nMp = nMp;
	m_nDef = nDef;
	m_nCount = nCount;
}



CItem::~CItem()
{
}


void CItem::onRender()
{
	cout << "Çò";
}

bool CItem::isEquals(int nRow, int nCol)
{
	for (int i = 0; i < 5; i++)
	{
		if (m_arrFightPos[i].x == nRow && m_arrFightPos[i].y == nCol)
		{
			return true;
		}
	}
	return false;
}

void CItem::setFightPos(int i, int j)
{
	m_arrFightPos[0].x = i;
	m_arrFightPos[0].y = j;
	m_arrFightPos[1].x = i+1;
	m_arrFightPos[1].y = j;
	m_arrFightPos[2].x = i;
	m_arrFightPos[2].y = j+1;
	m_arrFightPos[3].x = i-1;
	m_arrFightPos[3].y = j;
	m_arrFightPos[4].x = i;
	m_arrFightPos[4].y = j-1;
}

void CItem::onFightMove(int nMove)
{
	m_arrFightPos[0].y += nMove;
	int i = m_arrFightPos[0].x;
	int j = m_arrFightPos[0].y;
	m_arrFightPos[1].x = i + 1;
	m_arrFightPos[1].y = j;
	m_arrFightPos[2].x = i;
	m_arrFightPos[2].y = j + 1;
	m_arrFightPos[3].x = i - 1;
	m_arrFightPos[3].y = j;
	m_arrFightPos[4].x = i;
	m_arrFightPos[4].y = j - 1;
}
