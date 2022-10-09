#include "RoleSelect.h"
#include "DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"

CRoleSelect::CRoleSelect()
{
	m_nRoleIndex = 0;
	m_vecRoleDt = CDataMgr::getInstance()->getMgr<CRoleDtMgr>("RoleDtMgr")->getDatas<CRoleDt>();
}

void CRoleSelect::onUpdate()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nRoleIndex--;
		if (m_nRoleIndex < 0)
		{
			m_nRoleIndex = m_vecRoleDt.size() - 1;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nRoleIndex++;
		if (m_nRoleIndex >= m_vecRoleDt.size())
		{
			m_nRoleIndex = 0;
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		CGameMap* pGameMap = new CGameMap();
		pGameMap->setName("GameMap");
		CGameMgr::getInstance()->changeWnd(pGameMap);
		g_bClear = true;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->initData(m_vecRoleDt[m_nRoleIndex]);
	}
}

void CRoleSelect::onRender()
{
	cout << "请选择你的角色" << endl;
	cout << "  名字\t\t攻击\t防御\t血量\t蓝量\t职业\t速度" << endl;
	for (int i = 0; i < m_vecRoleDt.size(); i++)
	{
		if (m_nRoleIndex == i)
		{
			cout << "->";
		}
		else
		{
			cout << "  ";
		}

		cout << m_vecRoleDt[i]->strName << "\t\t"
			<< m_vecRoleDt[i]->nAck << "\t"
			<< m_vecRoleDt[i]->nDef << "\t"
			<< m_vecRoleDt[i]->nHp << "\t"
			<< m_vecRoleDt[i]->nMp << "\t"
			<< m_vecRoleDt[i]->strProfession << "\t"
			<< m_vecRoleDt[i]->nSpeed << "\t";
		cout << endl;
	}
}
