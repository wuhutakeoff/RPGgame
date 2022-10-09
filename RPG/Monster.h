#pragma once
#include "Vec2.h"
#include "Define.h"
#include "DataStruct.h"
#include "RoleBase.h"
class CMonster : public CRoleBase
{
public:
	CMonster();
	CMonster(CMonster* pMonster);
	~CMonster();
	void initWithData(CMonsterDt* pMonsterDt);
	//派生类再重载。
	bool isEquals(int nRow, int nCol, int nMapID);
	bool isEquals(CVec2 pos);
	void onMove(map<int, CVec2> mapDir);
	void changeDir();
	void onRecovery();

	SYN_THE_SIZE(int, m_nMapID, MapID);
	SYN_THE_SIZE(int, m_nItemID, ItemID);
	SYN_THE_SIZE(int, m_nMove, Move);
	SYN_THE_SIZE(int, m_nMoveInterval, MoveInterval);
	SYN_THE_SIZE(int, m_nDir, Dir);
	SYN_THE_SIZE(bool, m_bCatch, Catch);
private:
	int m_nTime;
	CMonsterDt* m_pMonsterDt;

};


