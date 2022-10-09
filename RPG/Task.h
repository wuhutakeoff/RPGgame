#pragma once
#include "DataStruct.h"
#include "Define.h"
class CTask
{
public:
	CTask();
	void initData(CTaskDt* pTaskDt);
	void addFinishCount()
	{
		m_nFinishCount++;
	}
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(string , m_strDescription, Description);
	SYN_THE_SIZE(int, m_nCount, Count);
	SYN_THE_SIZE(int, m_nNpcID, NpcID);
	SYN_THE_SIZE(int, m_nAwadMoney, AwadMoney);
	SYN_THE_SIZE(int, m_nAwadExp, AwadExp);
	SYN_THE_SIZE(int, m_nMonsterId, MonsterId);
	SYN_THE_SIZE(int, m_nFinishCount, FinishCount);

private:
};

