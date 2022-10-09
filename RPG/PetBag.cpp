#include "PetBag.h"
#include "Define.h"
#include "GameMgr.h"
#include "GameMap.h"

CPetBag::CPetBag()
{
	m_bDelete = false;
	m_nCount = 0;
}

void CPetBag::onUpdate()
{
	if (KEY_DOWN(VK_UP)&&!m_bShowSelect)
	{
		m_nCurIndex--;
		m_nCurIndex < 0 ? m_nCurIndex = m_vecPets.size()-1 : m_nCurIndex;
	}
	else if (KEY_DOWN(VK_DOWN) && !m_bShowSelect)
	{
		m_nCurIndex++;
		m_nCurIndex >=m_vecPets.size() ? m_nCurIndex = 0 : m_nCurIndex;
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_nSelectIndex--;
		m_nSelectIndex < 0 ? m_nSelectIndex = 1 : m_nSelectIndex;
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_nSelectIndex++;
		m_nSelectIndex >= 2 ? m_nSelectIndex = 0 : m_nSelectIndex;
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		m_nCount++;

		if(m_nCount==1&&m_bShowSelect)
		{
			m_bShowSelect = false;
			m_nSelectIndex = 0;
			m_nCount = 0;
			m_nNum = 0;
		}
		else if (m_nCount >= 2)
		{
			m_nCount = 0;
			g_bClear = true;
			m_bShowSelect = false;
			m_nNum = 0;
			CGameMgr::getInstance()->restoreWnd();
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		m_nNum++;
		if (m_nNum==1)
		{
			m_bShowSelect = true;
		}
		else if (m_vecPets[m_nCurIndex]->getIsFollow()&& m_nSelectIndex==1)
		{
			m_vecPets[m_nCurIndex]->setIsFollow(false);
		}
		else if (m_vecPets[m_nCurIndex]->getIsFight()&& m_nSelectIndex==0)
		{
			m_vecPets[m_nCurIndex]->setIsFight(false);
		}
		else if (m_nSelectIndex==0&&m_nNum>=2)
		{
			//出战
			CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->setCurPet(m_vecPets[m_nCurIndex]);
			//CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->setPetFight(true);
			m_vecPets[m_nCurIndex]->setIsFight(true);
		}
		else if (m_nSelectIndex == 1&&m_nNum>=2)
		{
			//跟随
			CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->setCurPet(m_vecPets[m_nCurIndex]);
			//CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->setPetFight(false);
			m_vecPets[m_nCurIndex]->setIsFollow(true);

		}

		if (m_bShowSelect&&m_nNum>=2)
		{
			m_nNum = 0;
		}
	}
	for (int  i = 0; i < m_vecPets.size(); i++)
	{
		m_vecPets[i]->onLevelUp();
	}
}

void CPetBag::onRender()
{
	cout << "宠物背包"<<endl;
	cout << "  名字    等级    血量    蓝量    攻击    防御    经验"<<endl;

	for (int i=0;i<m_vecPets.size();i++)
	{
		if (m_nCurIndex == i)
		{
			cout << "->";
		}
		else
		{
			cout << "  ";
		}
		cout << m_vecPets[i]->getName() << "\t" << m_vecPets[i]->getLevel() << "\t" << m_vecPets[i]->getHp() << "\t" 
			<< m_vecPets[i]->getMp() << "\t" << m_vecPets[i]->getAck() << "\t" << m_vecPets[i]->getDef()<<"\t" << m_vecPets[i]->getExp()<<"/"<<m_vecPets[i]->getLevelUpExp();
		
		if (m_nSelectIndex==0&&m_bShowSelect&& m_nCurIndex == i)
		{
			g_bClear = true;

			cout << "  ->";
			if (m_vecPets[m_nCurIndex]->getIsFight())
			{
				cout << "取消";
			}
			cout << "出战    ";
			if (m_vecPets[m_nCurIndex]->getIsFollow())
			{
				cout << "取消";
			}
			cout << "跟随";

		}
		else if(m_nSelectIndex==1&& m_bShowSelect && m_nCurIndex == i)
		{
			g_bClear = true;
			cout << "    ";
			if (m_vecPets[m_nCurIndex]->getIsFight())
			{
				cout << "取消";
			}
			cout << "出战  ->";
			if (m_vecPets[m_nCurIndex]->getIsFollow())
			{
				cout << "取消";
			}
			cout<< "跟随";
		}
		
		cout << endl;
	}
	//cout << "            ■■             ";
	//cout << "          ■■■■           ";
	//cout << "        ■■■■■■         ";
	//cout << "          ■■■■           ";
	//cout << "            ■■             ";

}

void CPetBag::addPet(CPet* pPet)
{
	m_vecPets.push_back(pPet);
}


