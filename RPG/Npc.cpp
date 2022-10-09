#include "Npc.h"
#include "Define.h"
CNpc::CNpc()
{
}

void CNpc::initWithData(CNpcDt* pNpcDt)
{
	m_nID = pNpcDt->nID;
	m_strName = pNpcDt->strName;
	m_vPos.x = pNpcDt->nRow;
	m_vPos.y = pNpcDt->nCol;
	m_nMapID = pNpcDt->nMapID;
	m_strPic = pNpcDt->strPic;
	m_nType = pNpcDt->nType;
}

bool CNpc::isEquals(int nRow, int nCol, int nMapID)
{
	return m_vPos.x==nRow&&m_vPos.y == nCol&&m_nMapID == nMapID;
}

void CNpc::onRender()
{
	cout << m_strPic;
}
