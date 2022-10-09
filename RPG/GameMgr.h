#pragma once
#include "WndBase.h"
#include <vector>
using namespace std;
class CGameMgr
{
public:
	static CGameMgr* getInstance();
	void mainLoop();
	void onUpdate();
	void onRender();
	void runWithWnd(CWndBase* pWnd);
	//提供一个接口用于改变当前窗口指针指向， 指向菜单内存，菜单处理， 指向地图，地图处理。
	void changeWnd(CWndBase* pWnd);
	//回到上一个窗口
	void restoreWnd();


	template <class T>
	T* getWndByName(string strName)
	{
		if (strName.empty())
		{
			return nullptr;
		}
		if (m_pCurWnd && m_pCurWnd->getName() == strName)
		{
			return static_cast<T*>(m_pCurWnd);
		}
		for (CWndBase* pWnd : m_vecPreWnds)
		{
			if (strName == pWnd->getName())
			{
				return static_cast<T*>(pWnd);
			}
		}
		return nullptr;
	}
private:
	CGameMgr();
	static CGameMgr* m_spInstance;

	//不管理多个指针，只管理一个指针。 窗口基类指针。
	CWndBase* m_pCurWnd;

	//容器，用于存储切换过的窗口。 何时存储，切换的时候存储，调用changWnd切换。
	vector<CWndBase*> m_vecPreWnds;
};

