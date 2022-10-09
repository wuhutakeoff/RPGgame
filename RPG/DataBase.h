#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//数据基类
class CDataBase
{
public:
	int nID;
};


//数据操作基类
class CDataBaseMgr
{
public:
	CDataBaseMgr();
	~CDataBaseMgr();
	virtual void loadFile(string strPath);
	virtual void parse(fstream& fromFile) = 0;
	template <class T>
	T* getDataByID(int nID)
	{
		for (CDataBase* pData : m_vecDatas)
		{
			if (nID == pData->nID)
			{
				return static_cast<T*>(pData);
			}
		}
		return nullptr;
	}
	//获取个数
	int getSize()
	{
		return m_vecDatas.size();
	}
	//获取所有的数据
	template <class T>
	vector<T*> getDatas()
	{
		vector<T*> vecDatas;
		for (CDataBase* pData : m_vecDatas)
		{
			vecDatas.push_back(static_cast<T*>(pData));
		}
		return vecDatas;
	}
protected:
	vector<CDataBase*> m_vecDatas;
};

