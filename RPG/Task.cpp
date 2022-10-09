#include "Task.h"

CTask::CTask()
{
}

void CTask::initData(CTaskDt* pTaskDt)
{
	m_nID = pTaskDt->nID;
	m_strDescription = pTaskDt->strDescription;
	m_strName = pTaskDt->strName;
	m_nCount = pTaskDt->nCount;
	m_nNpcID = pTaskDt->nNpcID;
	m_nAwadExp = pTaskDt->nAwadExp;
	m_nAwadMoney = pTaskDt->nAwadMoney;
	m_nMonsterId = pTaskDt->nMonsterID;
	m_nFinishCount = 0;
}
