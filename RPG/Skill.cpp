#include "Skill.h"

CSkill::CSkill()
{
	m_nID=0;
	m_strName="";
	m_nDamage=0;
	m_nDefense=0;
	m_nHp=0;
	m_nMp=0;
	m_nType=0;
	m_nRoleID=0;
	m_vPos.x = 0;
	m_vPos.y = 0;
	m_strPic = "";
}

void CSkill::initWithData(CSkillDt* pData)
{
	m_nID = pData->nID;
	m_strName = pData->strName;
	m_nDamage = pData->nDamage;
	m_nDefense = pData->nDefense;
	m_nHp = pData->nHp;
	m_nMp = pData->nMp;
	m_nType = pData->nType;
	m_nRoleID = pData->nRoleID;
	m_strPic = pData->strPic;
}

void CSkill::onRender()
{
	cout << m_strPic;
}

void CSkill::onUpdate()
{
	m_vPos.y++;
}

bool CSkill::isEquals(int nRow, int nCol)
{
	return m_vPos.x == nRow && m_vPos.y == nCol;
}
