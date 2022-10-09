#pragma once
#include "RoleBase.h"
#include "Monster.h"
class CPet:public CRoleBase
{
public:
	CPet();
	CPet(CMonster* pMonster);
	bool isEquals(CVec2 pos);
	bool isEquals(int nRow, int nCol);
	void addExp(int nExp);
	void onLevelUp();
	SYN_THE_SIZE(bool, m_bIsFight, IsFight);
	SYN_THE_SIZE(bool, m_bIsFollow,IsFollow)
private:
};

