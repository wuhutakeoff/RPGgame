#include "GameMgr.h"
#include "Define.h"

CGameMgr* CGameMgr::m_spInstance = nullptr;
CGameMgr::CGameMgr()
{
	m_pCurWnd = nullptr;
}

void CGameMgr::onUpdate()
{
	m_pCurWnd->onUpdate();
}

void CGameMgr::onRender()
{
	if (g_bClear)
	{
		system("cls");
		g_bClear = false;
	}

	m_pCurWnd->onRender();

}

void CGameMgr::runWithWnd(CWndBase* pWnd)
{
	m_pCurWnd = pWnd;
}

void CGameMgr::changeWnd(CWndBase* pWnd)
{
	//切换前：m_pCurWnd前面的窗口。
	/*if (m_pCurWnd)
	{*/
	m_vecPreWnds.push_back(m_pCurWnd);
	//}
	//切换窗口。
	m_pCurWnd = pWnd;
}

void CGameMgr::restoreWnd()
{
	if (m_vecPreWnds.size() <= 0)
	{
		return;
	}
	//要释放掉当前内存。
	if (m_pCurWnd->getDelete())
	{
		SAFE_DEL(m_pCurWnd);//从商店退回到地图， 商店要释放掉。  m_pCurWnd商店。
	}
	//拿到容器的最后一个元素赋值给当前窗口指针。
	m_pCurWnd = m_vecPreWnds.back();
	//最后一个元素要从前置窗口容器去掉
	m_vecPreWnds.pop_back();
}

CGameMgr* CGameMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CGameMgr();
	}
	return m_spInstance;
}

void CGameMgr::mainLoop()
{
	//HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //获得控制台句柄
	//COORD NewSize = GetLargestConsoleWindowSize(HOUT);//获得控制台最大坐标，坐标以字符数为单位
	//NewSize.X -= 1;
	//NewSize.Y -= 1;    //可以不加，不加时显示滚动条
	//SetConsoleScreenBufferSize(HOUT, NewSize); //设置控制台缓冲区大小

	//SMALL_RECT DisplayArea = { 0,0,0,0 };
	//DisplayArea.Right = NewSize.X;
	//DisplayArea.Bottom = NewSize.Y;
	//SetConsoleWindowInfo(HOUT, TRUE, &DisplayArea);
	/*HWND Hwnd = GetForegroundWindow();
	ShowWindow(Hwnd, SW_MAXIMIZE);*/

	SetConsoleTitleA("RPG");
	Sleep(100);
	CONSOLE_CURSOR_INFO cursor; //定义结构体 控制台光标信息
	cursor.bVisible = 0; //设置不显示
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); //设置光标信息
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	this->onUpdate();
	this->onRender();
}
