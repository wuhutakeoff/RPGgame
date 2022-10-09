#pragma once
#include <map>
#include "DataBase.h"
#include "DataMgr.h"
#include <unordered_map>

class CLoader
{
public:
	CLoader();
	~CLoader();
	static void load();
	template <class T>
	static void loadRes(string strPath, string strName)
	{
		T* pMgr = new T();
		pMgr->loadFile(strPath);
		CDataMgr::getInstance()->addMgr(strName, pMgr);

	}
private:

};

class CMapDt:public CDataBase
{
public:
	CMapDt()
	{
		nID = 0;
		strName = "";
		nInitRow = 0;
		nInitCol = 0;
		nRowSize = 0;
		nColSize = 0;
		pArrMap = nullptr;
	}
	string strName;
	int nInitRow;
	int nInitCol;
	int nRowSize;
	int nColSize;
	int** pArrMap;
	int nType;
};


class CMapDtMgr:public CDataBaseMgr
{
public:
	CMapDtMgr();
	virtual void parse(fstream& fromFile);
};



class CNpcDt:public CDataBase
{
public:
	CNpcDt()
	{
		nID = 0;
		strName = "";
		nRow = 0;
		nCol = 0;
		nMapID = 0;
		strPic = "";
		nType = 0;
	}
	string strName;
	int nRow;
	int nCol;
	int nMapID;
	string strPic;
	int nType;

};



class CNpcDtMgr:public CDataBaseMgr
{
public:
	CNpcDtMgr();
	virtual void parse(fstream& fromFile);

};

class CItemDt:public CDataBase
{
public:
	CItemDt()
	{
		nID = 0;
		strName = "";
		//....
	}
	string strName;
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	string strPic;
	string strDescription;
	int nPrice;
	int nNpcID;
	string strType;
	int nOverLying;

};

class CItemDtMgr:public CDataBaseMgr
{
public:
	CItemDtMgr();
	~CItemDtMgr();
	virtual void parse(fstream& fromFile);
	//有额外做了一些操作，这个类的读取操作自己写。
	virtual void loadFile(string strPath);
	vector<CItemDt*> getDataByNpcID(int nNpcID);
	unordered_map<string, string> getEquipInfo()
	{
		return m_mapEquipInfo;
	}
private:
	//存储装备栏信息： 英文key ，中文显示文字
	unordered_map<string, string> m_mapEquipInfo;
};

class CRoleDt:public CDataBase
{
public:
	CRoleDt()
	{
		nID=0;
		strName="";
		nHp=0;
		nMp=0;
		nAck=0;
		nDef=0;
		strPic="";
		strProfession="";
		nSpeed=0;
	}
	string strName;
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	string strPic;
	string strProfession;
	int nSpeed;
};

class CRoleDtMgr:public CDataBaseMgr
{
public:
	CRoleDtMgr();
	~CRoleDtMgr();
	virtual void parse(fstream& fromFile);

};

class CMonsterDt:public CDataBase
{
public:
	CMonsterDt()
	{
		nID = 0;
	}
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	string strPic;
	string strName;
	int nExp;
	int nMoney;
	int nMapID;
	int nItemID;
	int nMove;
	int nMoveInterval;
	int nCount;
};

class CMonsterDtMgr:public CDataBaseMgr
{
public:
	CMonsterDtMgr();
	~CMonsterDtMgr();
	virtual void parse(fstream& fromFile);
};

class CSkillDt:public CDataBase
{
public:
	CSkillDt()
	{
		nID = 0;
		strName = "";
		nHp = 0;
		nMp = 0;
		nDamage = 0;
		nDefense = 0;
		nType = 0;
		nRoleID = 0;
		strPic = "";
	}
	string strName;
	int nDamage;
	int nDefense;
	int nHp;
	int nMp;
	int nType;
	int nRoleID;
	string strPic;
};

class CSkillDtMgr:public CDataBaseMgr
{
public:
	CSkillDtMgr();
	~CSkillDtMgr();
	virtual void parse(fstream& fromFile);

	vector<CSkillDt*> getDatasByRoleID(int nRoleID);
};

class CTaskDt :public CDataBase
{
public:
	CTaskDt()
	{
		nID = 0;
		strDescription = "";
		strName = "";
		nCount = 0;
		nNpcID = 0;
		nAwadMoney = 0;
		nAwadExp = 0;
		nMonsterID = 0;
	}

	int nID;
	string strName;
	string strDescription;
	int nCount;
	int nNpcID;
	int nAwadMoney;
	int nAwadExp;
	int nMonsterID;
};

class CTaskDtMgr :public CDataBaseMgr
{
public:
	CTaskDtMgr();
	~CTaskDtMgr();
	virtual void parse(fstream& fromFile);

	vector<CTaskDt*> getDatasByNpcID(int nNpcId);
};