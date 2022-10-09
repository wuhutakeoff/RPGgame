#pragma once
#include "Npc.h"
class CNpcMgr
{
public:
	CNpcMgr();
	//通过行列和地图ID获取Npc
	CNpc* getNpc(int nRow, int nCol, int nMapID);
	vector<CVec2> getNpcPos(int nMapID);

private:
	vector<CNpc*> m_vecNpc;
};

