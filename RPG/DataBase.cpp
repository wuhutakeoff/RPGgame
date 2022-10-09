#include "DataBase.h"

CDataBaseMgr::CDataBaseMgr()
{
}

CDataBaseMgr::~CDataBaseMgr()
{
}

void CDataBaseMgr::loadFile(string strPath)
{
	fstream fromFile(strPath);
	if (fromFile)
	{
		string strInfo = "";
		getline(fromFile, strInfo);
		int nCount = 0;
		fromFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			//因为是虚函数所以到时候会执行派生对象的parse
			this->parse(fromFile);
		}
	}
}
