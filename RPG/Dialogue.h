#pragma once
#include "WndBase.h"
#include "Npc.h"
#include "DataBase.h"
#include "Task.h"
class CDialogue:public CWndBase 
{
public:
	CDialogue();
	void onUpdate();
	void onRender();
	void showMenu();
	void showDialogue();
	void showTask();
	
	SYN_THE_SIZE(CNpc*, m_pNpc, Npc);
	SYN_THE_SIZE_READONLY(vector<CTaskDt*>, m_vecTaskDt, TaskDt);

private:
	int m_nCurIndex;
	int m_nCount;
	int m_nTaskIndex;
	bool m_bShowTask;
	bool m_bShowDialogue;
	bool m_bShowSelect;
	bool m_bInSelect;
	bool m_bSubmit;
	int m_nState;
	int m_nNum;
};

