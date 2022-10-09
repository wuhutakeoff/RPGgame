#include "TaskMgr.h"

CTaskMgr::CTaskMgr()
{
}


void CTaskMgr::addTask(CTask* pTask)
{
	for (int i = 0; i < m_vecTask.size(); i++)
	{
		if (pTask->getID() == m_vecTask[i]->getID())
		{
			return;
		}
	}
	m_vecTask.push_back(pTask);
}

void CTaskMgr::deletTask(CTask* pTask)
{
	for (int i = 0; i < m_vecTask.size(); i++)
	{
		if (pTask->getID() == m_vecTask[i]->getID())
		{
			m_vecTask.erase(m_vecTask.begin() + i);
		}
	}
}

CTask* CTaskMgr::getFinishTask()
{
	for (int i = 0; i < m_vecTask.size(); i++)
	{
		if (m_vecTask[i]->getCount() <= m_vecTask[i]->getFinishCount())
		{
			return m_vecTask[i];
		}
	}
	return nullptr;
}

bool CTaskMgr::getTaskByMonsterId(int nMonsterId)
{
	for (CTask* pTask : m_vecTask)
	{
		if (pTask->getMonsterId()==nMonsterId)
		{
			return true;
		}
	}
	return false;
}

void CTaskMgr::addFinishCount(CMonster* pMonster)
{
	for (int i = 0; i < m_vecTask.size(); i++)
	{
		if (m_vecTask[i]->getMonsterId() == pMonster->getID())
		{
			m_vecTask[i]->addFinishCount();
		}
	}
}
