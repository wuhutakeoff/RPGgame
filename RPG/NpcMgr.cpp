#include "NpcMgr.h"
#include "Define.h"
#include"DataMgr.h"
CNpcMgr::CNpcMgr()
{
	//游戏运行起来就要产生Npc，所以可以在这里创建出Npc
	int nCount = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getSize();
	for (int i = 0; i < nCount; i++)
	{
		CNpc* pNpc = new CNpc();
		//还要拿到npc数据，对每个npc进行属性处理
		int nID = 2001 + i;
		CNpcDt* pNpcDt = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getDataByID<CNpcDt>(nID);
		//通过这个Npc数据对npc属性进行处理。
		//pNpc->nType = pNpcDt->nType;
		//pNpc->nID = pNpcDt->nID;
		pNpc->initWithData(pNpcDt);
		//不要忘记存储
		m_vecNpc.push_back(pNpc);
	}
}

CNpc* CNpcMgr::getNpc(int nRow, int nCol, int nMapID)
{
	//遍历所有Npc，比对
	for (CNpc* pNpc : m_vecNpc)
	{
		//if (nRow == pNpc->getPos().x && nCol == pNpc->getPos().y && nMapID == pNpc->getMapID())//把比较写到Npc里面
		//{
		//	return pNpc;
		//}
		if (pNpc->isEquals(nRow, nCol, nMapID))
		{
			return pNpc;
		}
	}
	return nullptr;
}

vector<CVec2> CNpcMgr::getNpcPos(int nMapId)
{
	vector<CVec2> vecPos;
	for (int i = 0; i < m_vecNpc.size(); i++)
	{
		if (nMapId==m_vecNpc[i]->getMapID())
		{
			vecPos.push_back(m_vecNpc[i]->getPos());
		}
	}
	return vecPos;
}
