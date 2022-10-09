#pragma once
#include "Task.h"
#include "Monster.h"
class CTaskMgr
{
public:
	CTaskMgr();
	void addTask(CTask* pTask);
	void deletTask(CTask* pTask);
	CTask* getFinishTask();
	bool getTaskByMonsterId(int nMonsterId);
	void addFinishCount(CMonster* pMonster);
	int getVecTaskSize()
	{
		return m_vecTask.size();
	}
	SYN_THE_SIZE(vector<CTask*>,m_vecTask,Tasks)
private:
};

