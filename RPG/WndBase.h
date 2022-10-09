#pragma once
#include "Define.h"
class CWndBase
{
public:
	CWndBase();
	~CWndBase();
	//虚函数。
	//提供接口，让派生类重写，实现多态。
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(bool, m_bDelete, Delete);
};

