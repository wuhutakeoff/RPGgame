#pragma once
#include <vector>
#include <string>
#include "WndBase.h"
#include "DataStruct.h"
using namespace std;

class CRoleSelect:public CWndBase
{
public:
	CRoleSelect();
	void onUpdate();
	void onRender();
private:
	vector<CRoleDt*> m_vecRoleDt;
	int m_nRoleIndex;
};

