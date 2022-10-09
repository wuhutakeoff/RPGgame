#include "DataStruct.h"
#include <fstream>

CLoader::CLoader()
{
}


CLoader::~CLoader()
{
}

void CLoader::load()
{
	CLoader::loadRes<CMapDtMgr>("data/MapDt.txt", "MapDtMgr");
	CLoader::loadRes<CNpcDtMgr>("data/NpcDt.txt", "NpcDtMgr");
	CLoader::loadRes<CItemDtMgr>("data/ItemDt.txt", "ItemDtMgr");
	CLoader::loadRes<CMonsterDtMgr>("data/MonsterDt.txt", "MonsterDtMgr");
	CLoader::loadRes<CRoleDtMgr>("data/RoleDt.txt", "RoleDtMgr");
	CLoader::loadRes<CSkillDtMgr>("data/SkillDt.txt", "SkillDtMgr");
	CLoader::loadRes<CTaskDtMgr>("data/TaskDt.txt", "TaskDtMgr");

}

CMapDtMgr::CMapDtMgr()
{
}

void CMapDtMgr::parse(fstream& fromFile)
{
	CMapDt* pData = new CMapDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nInitRow >> pData->nInitCol
		>> pData->nRowSize >> pData->nColSize
		>> pData->nType;

	pData->pArrMap = new int* [pData->nRowSize];
	for (int j = 0; j < pData->nRowSize; j++)
	{
		pData->pArrMap[j] = new int[pData->nColSize];
	}

	for (int m = 0; m < pData->nRowSize; m++)
	{
		for (int n = 0; n < pData->nColSize; n++)
		{
			fromFile >> pData->pArrMap[m][n];
		}
	}

	m_vecDatas.push_back(pData);
}



CNpcDtMgr::CNpcDtMgr()
{
}

void CNpcDtMgr::parse(fstream& fromFile)
{
	CNpcDt* pData = new CNpcDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nRow >> pData->nCol
		>> pData->nMapID >> pData->strPic
		>> pData->nType;
	m_vecDatas.push_back(pData);
}




CItemDtMgr::CItemDtMgr()
{
}

CItemDtMgr::~CItemDtMgr()
{
}

void CItemDtMgr::parse(fstream& fromFile)
{
	CItemDt* pData = new CItemDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nHp >> pData->nMp
		>> pData->nAck >> pData->nDef
		>> pData->strPic >> pData->strDescription
		>> pData->nPrice >> pData->nNpcID
		>> pData->strType >> pData->nOverLying;
	m_vecDatas.push_back(pData);
}

void CItemDtMgr::loadFile(string strPath)
{
	fstream fromFile(strPath);
	if (fromFile)
	{
		string strInfo = "";
		getline(fromFile, strInfo);
		int nCount = 0;
		vector<string> vecName;
		fromFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			string strName = "";
			fromFile >> strName;
			//存储起来。
			vecName.push_back(strName);
		}
		//遍历。读取中文显示信息
		for (int i = 0; i < vecName.size(); i++)
		{
			string strInfo = "";
			fromFile >> strInfo;
			//i ==0  vecName[i] weapon  strInfo==武器
			//i == 1  clothes	衣服
			m_mapEquipInfo[vecName[i]] = strInfo;
		}
		fromFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			this->parse(fromFile);
		}
	}
}


vector<CItemDt*> CItemDtMgr::getDataByNpcID(int nNpcID)
{
	vector<CItemDt*> vecAllDatas = this->getDatas<CItemDt>();
	//创建一个空的容器
	vector<CItemDt*> vecDatas;
	//遍历所有的物品数据，每个物品数据的npcid跟传递进来的比较
	for (CItemDt* pItemDt : vecAllDatas)
	{
		if (pItemDt->nNpcID == nNpcID)
		{
			//如果有找到，那么存储起来。
			vecDatas.push_back(pItemDt);
		}
	}
	return vecDatas;
}


CRoleDtMgr::CRoleDtMgr()
{
}

CRoleDtMgr::~CRoleDtMgr()
{
}

void CRoleDtMgr::parse(fstream& fromFile)
{
	CRoleDt* pData = new CRoleDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nHp >> pData->nMp
		>> pData->nAck >> pData->nDef
		>> pData->strPic >> pData->strProfession
		>> pData->nSpeed;
	m_vecDatas.push_back(pData);
}


CMonsterDtMgr::CMonsterDtMgr()
{
}

CMonsterDtMgr::~CMonsterDtMgr()
{
}

void CMonsterDtMgr::parse(fstream& fromFile)
{
	CMonsterDt* pData = new CMonsterDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nHp >> pData->nMp
		>> pData->nAck >> pData->nDef
		>> pData->strPic >> pData->nExp
		>> pData->nMoney >> pData->nItemID
		>> pData->nMapID >> pData->nMove
		>> pData->nMoveInterval >> pData->nCount;
	m_vecDatas.push_back(pData);
}


CSkillDtMgr::CSkillDtMgr()
{
}


CSkillDtMgr::~CSkillDtMgr()
{
}

void CSkillDtMgr::parse(fstream& fromFile)
{
	CSkillDt* pData = new CSkillDt();
	fromFile >> pData->nID >> pData->strName >> pData->nDamage
		>> pData->nDefense >> pData->nHp >> pData->nType
		>> pData->nMp >> pData->nRoleID>>pData->strPic;
	m_vecDatas.push_back(pData);
}


vector<CSkillDt*> CSkillDtMgr::getDatasByRoleID(int nRoleID)
{
	vector<CSkillDt*> vecAllDatas = this->getDatas<CSkillDt>();
	//创建一个空的容器
	vector<CSkillDt*> vecDatas;
	//遍历所有的物品数据，每个物品数据的npcid跟传递进来的比较
	for (CSkillDt* pSkillDt : vecAllDatas)
	{
		if (pSkillDt->nRoleID == nRoleID)
		{
			//如果有找到，那么存储起来。
			vecDatas.push_back(pSkillDt);
		}
	}
	return vecDatas;
}


CTaskDtMgr::CTaskDtMgr()
{
}

CTaskDtMgr::~CTaskDtMgr()
{
}

void CTaskDtMgr::parse(fstream& fromFile)
{
	CTaskDt* pData = new CTaskDt();
	fromFile >> pData->nID >>pData->strName>>pData->strDescription >> pData->nCount
		>> pData->nNpcID >> pData->nAwadMoney >> pData->nAwadExp >> pData->nMonsterID;
	m_vecDatas.push_back(pData);
}

vector<CTaskDt*> CTaskDtMgr::getDatasByNpcID(int nNpcId)
{
	vector<CTaskDt*> vecAllDatas = this->getDatas<CTaskDt>();
	vector<CTaskDt*> vecDatas;
	//遍历所有的物品数据，每个物品数据的npcid跟传递进来的比较
	for (CTaskDt* pTaskDt : vecAllDatas)
	{
		if (pTaskDt->nNpcID == nNpcId)
		{
			//如果有找到，那么存储起来。
			vecDatas.push_back(pTaskDt);
		}
	}
	return vecDatas;
}
