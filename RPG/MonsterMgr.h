#pragma once
#include "Monster.h"
class CMonsterMgr
{
public:
	CMonsterMgr();
	~CMonsterMgr();
	void createMonster();
	//通过行列和地图ID获取某个怪物
	CMonster* getMonster(int nRow, int nCol, int nMapID);
	vector<CMonster*> getMonsters()
	{
		return m_vecMonster;
	}
	void addDeathMonster(CMonster* pMonster);
	//刷新怪物。
	void refreshMonster();
	void onUpdate();
	vector<CVec2> getMonsterPosByMapId(int nMapId);

	vector<CMonster*> m_vecDeathMonster;
	int m_nTime;
	//SYN_THE_SIZE(int, m_nDeathMonsterNum, DeathMonsterNum);
private:
	vector<CMonster*> m_vecMonster;
	//不管哪只怪物，都是一样map， 没必要定义成怪物的成员变量（多少只怪，多少个） 只要有一个就够了 ，定义到怪物管理者。
	map<int, CVec2> m_mapDir;

};

