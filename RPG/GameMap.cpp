#include "GameMap.h"
#include "Define.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include "FightScene.h"
#include "Shop.h"
#include "Dialogue.h"
#include "AStar.h"
#include <graphics.h>
#include <conio.h>

POINT p;
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND h = GetForegroundWindow();
CONSOLE_FONT_INFO consoleCurrentFont;

CGameMap::CGameMap()
{
	//m_pCurMapDt = CDataMgr::getInstance()->getMapDtMgr()->getDataByID(1001);
	this->changeMap(1001);
	//new出玩家
	m_pPlayer = new CPlayer();
	//玩家初始位置设置。 给玩家添加设置坐标接口。
	m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
	m_pNpcMgr = new CNpcMgr();
	m_pMonsterMgr = new CMonsterMgr();
	m_pTaskMgr = new CTaskMgr();
	x = 0;
	y = 0;
}

void CGameMap::onUpdate()
{
	m_vecTask = m_pTaskMgr->getTasks();

	//鼠标点击事件
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);


	if (KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(h, &p);               //获取鼠标在窗口上的位置
		GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //获取字体信息
		x = p.x /= consoleCurrentFont.dwFontSize.X;
		y = p.y /= consoleCurrentFont.dwFontSize.Y;

		//A*算法计算最短路径
		Astar astar;
		int** arr = getCurMapDt()->pArrMap;
		int nRow = getCurMapDt()->nRowSize;
		int nCol = getCurMapDt()->nColSize;
		vector<CVec2> vec1=m_pNpcMgr->getNpcPos(getCurMapDt()->nID);
		vector<CVec2> vec2 = m_pMonsterMgr->getMonsterPosByMapId(getCurMapDt()->nID);
		vector<CVec2> vec3;
		vec3.insert(vec3.end(), vec1.begin(), vec1.end());
		vec3.insert(vec3.end(), vec2.begin(), vec2.end());
		astar.InitAstar(arr,nRow,nCol,vec3 );
		Point cur(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y);
		Point dis(y - 8, (x - 56) / 2);
		list<Point*> path = astar.GetPath(cur, dis, false);
		m_pPlayer->setPath(path);
		m_pPlayer->setIt();
		cout << x << " " << y;
	}

	if (x>=122&&x<=125&&y==7)
	{
		recharge();
	}

	if ((x > 56 && y > 8)&&(x < 126 && y < 34))
	{
		int nRow = y - 8;
		int nCol = (x - 56) / 2;
		CVec2 point = CVec2(nRow,nCol);
		m_pPlayer->autoMove(point);
	}

	if (m_pPlayer->getCurPet() && m_pPlayer->getCurPet()->getIsFollow())
	{
		m_pPlayer->getCurPet()->setPosition(m_pPlayer->getPosition().xBk, m_pPlayer->getPosition().yBk);
		if (m_pPlayer->getCurPet()->isEquals(m_pPlayer->getPosition()))
		{
			m_pPlayer->getCurPet()->onRestore();
		}
	}

	string str;
	if (KEY_DOWN(VK_RETURN))
	{
		str = "";
		while (true) {
			if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
				char ch;
				ch = _getch();//使用_getch()获取按下的键值
				if ((ch >= 65 && ch <= 90)||(ch>=97&&ch<=122))
				{
					str += ch;
				}
				if (ch == 27||ch== 13) 
				{ 
					break;
				}//当按下ESC时退出循环，ESC键的键值是27.
			}
		}
		if (str.substr(0, 8) == "addmoney")
		{
			m_pPlayer->addMoney(1000);
		}
		else if (str.substr(0,8)=="artifact")
		{
			CItemDt* pItemDt=CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByID<CItemDt>(3000);
			m_pPlayer->getBag()->addItem(pItemDt);
		}
	}
	else if (KEY_DOWN(VK_B))
	{	
		CGameMgr::getInstance()->changeWnd(m_pPlayer->getBag());
		g_bClear = true;
	}
	else if (KEY_DOWN(VK_P))
	{
		CGameMgr::getInstance()->changeWnd(m_pPlayer->getPetBag());
		g_bClear = true;
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		closegraph();
		x = 0;
		y = 0;
	}
	m_pPlayer->onUpdate();
	//判断玩家是否撞墙。
	//获取玩家坐标
	CVec2 vPos = m_pPlayer->getPosition();
	if (1 == m_pCurMapDt->pArrMap[vPos.x][vPos.y])
	{
		m_pPlayer->onRestore();
	}
	
	//vector<CMonster*> vecMonsters = m_pMonsterMgr->getMonsters();
	//for (CMonster* pMonster:vecMonsters)
	//{
	//	if (pMonster->isEquals(vPos))
	//	{
	//		m_pPlayer->onRestore();
	//	}
	//}

	//玩家移动的时候在地图数组可以拿到值得，传送门的值是大于1000而且传送门的值刚好是下一张的ID
	int nNextMapID = m_pCurMapDt->pArrMap[vPos.x][vPos.y];
	if (nNextMapID > 1000)
	{
		x = 0;
		y = 0;
		//玩家在传送门上。
		//传送到下一张图，修改地图数据
		m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(nNextMapID);
		//每一张图玩家都有个出生点
		m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
		//清屏
		g_bClear = true;
	}

	//玩家碰Npc：通过玩家行列和地图ID到Npc管理者拿Npc如果拿到意味着玩家碰到Npc
	CNpc* pNpc = m_pNpcMgr->getNpc(vPos.x, vPos.y, m_pCurMapDt->nID);
	if (pNpc)
	{
		m_pPlayer->onRestore();
		if (0 == pNpc->getType())
		{
			//进入商店。
			CShop* pShop = new CShop();
			pShop->setName("Shop");

			//切换到商店
			CGameMgr::getInstance()->changeWnd(pShop);
			//刷新物品；
			pShop->refreshItem(pNpc->getID());
			g_bClear = true;
			return;
		}
		else if(1==pNpc->getType())
		{
			CDialogue* pDialogue = new CDialogue();
			pDialogue->setName("Dialogue");
			pDialogue->setNpc(pNpc);
			CGameMgr::getInstance()->changeWnd(pDialogue);			
		}

		//玩家坐标还原


	}
	
	m_pMonsterMgr->onUpdate();
	onCollision();
}

void CGameMap::onRender()
{
	//m_pPlayer->getEquip()->showEquip();
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}

	cout << "							";
	cout << m_pCurMapDt->strName << "								  ";
	cout<<"充值" << endl;


	//m_pPlayer->getEquip()->showEquip();
	for (int i = 0; i < m_pCurMapDt->nRowSize; i++)
	{
		cout << "							";
		for (int j = 0; j < m_pCurMapDt->nColSize; j++)
		{
			//限制视野范围
			/*if (1 == m_pCurMapDt->nType&&m_pPlayer->isOutOfView(i, j)) {
				cout << "  ";
				continue;
			}*/
			//通过行列和地图ID，到Npc管理者获取Npc。
			CNpc* pNpc = m_pNpcMgr->getNpc(i, j, m_pCurMapDt->nID);
			CMonster* pMonster = m_pMonsterMgr->getMonster(i, j, m_pCurMapDt->nID);
			if (1 == m_pCurMapDt->pArrMap[i][j])
			{
				cout << "■";
			}
			else if (m_pPlayer->isEuqals(i,j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (pNpc)
			{
				//cout << pNpc->getPic();
				pNpc->onRender();
			}
			else if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->isEquals(i,j)&&m_pPlayer->getCurPet()->getIsFollow())
			{
				m_pPlayer->getCurPet()->onRender();
			}
			else if (pMonster)
			{
				pMonster->onRender();
			}
			else if (1000 < m_pCurMapDt->pArrMap[i][j])
			{
				cout << "门";
			}
			else
			{
				cout << "  ";
			}
		}
		if (0 == i)
		{
			cout << "角  色:" << m_pPlayer->getName() << "                 ";;
		}
		else if (1 == i)
		{
			cout << "等  级:" << m_pPlayer->getLevel() << "                 ";
		}
		else if (2 == i)
		{
			cout << "血  量:" << m_pPlayer->getHp() << "/" << m_pPlayer->getMaxHp() << "                 ";;
		}
		else if (3 == i)
		{
			cout << "蓝  量:" << m_pPlayer->getMp() << "/"<<m_pPlayer->getMaxMp() << "                 ";;
		}
		else if (4 == i)
		{
			cout << "攻击力:" << m_pPlayer->getAck() << "                 ";;
		}
		else if (5 == i)
		{
			cout << "防御力:" << m_pPlayer->getDef() << "                 ";;
		}
		else if (6 == i)
		{
			cout << "经  验:" << m_pPlayer->getExp() << "/" << m_pPlayer->getLevelUpExp() << "              ";
		}


		if (m_vecTask.size() != 0)
		{
			for (int k = 0; k < m_vecTask.size(); k++)
			{
				if (m_vecTask[k])
				{
					if (i == 10 + k * 5)
					{
						cout << "当前任务：";
					}
					else if (i == 11 + k * 5)
					{
						cout << "任务名称：" << m_vecTask[k]->getName() << "     ";
					}
					else if (i == 12 + k * 5)
					{
						cout << "任务描述：" << m_vecTask[k]->getDescription();
					}
					else if (i == 13 + k * 5)
					{
						cout << "任务进度：" << m_vecTask[k]->getFinishCount() << "/" << m_vecTask[k]->getCount();
					}
				}
			}
		}
		else
		{
			if (i == 10)
			{
				cout << "当前任务：";
			}
			else if (i==11)
			{
				cout << "无任务,请去Npc处接受任务";
			}
		}

		cout << endl;
	}
}



void CGameMap::onCollision() {
	CMonster* pMonster=m_pMonsterMgr->getMonster(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pCurMapDt->nID);
	if (pMonster)
	{
		//跳转战斗界面
		m_pPlayer->onRestore();
		g_bClear = true;
		CFightScene* pFight = new CFightScene();
		pFight->setTarget(m_pPlayer, pMonster);
		CGameMgr::getInstance()->changeWnd(pFight);
		return;
	}

}

void CGameMap::changeMap(int nID)
{
	m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(nID);
}


void CGameMap::recharge()
{
	initgraph(650, 650, EW_SHOWCONSOLE | EW_NOCLOSE);
	IMAGE pic1;
	loadimage(&pic1, _T("source/1.png"), 650, 650);
	putimage(0, 0, &pic1);
	system("pause");
}

void CGameMap::setNull()
{
	x = 0;
	y = 0;
}




//出Npc 武器 防具，药水，杂货，  任务， 
//玩家碰到进入商店，  不同商店显示不同物品，玩家可以购买  存储到背包
//玩家可以打开背包，使用物品（消耗品）  ，穿戴装备， 装备栏， 替换装备
//怪物
//玩家碰到怪物，进入战斗场景，回合制。

