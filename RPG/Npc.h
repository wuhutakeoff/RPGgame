#pragma once
#include "Vec2.h"
#include "DataStruct.h"
#include"Define.h"
class CNpc
{
public:
	CNpc();
	//因为属性都是私有，如果在外部对这些属性一个个set没问题，但是代码特别多，这里写个接口，通过数据对属性初始化，在本类可以直接使用私有属性
	void initWithData(CNpcDt* pNpcDt);
	bool isEquals(int nRow, int nCol, int nMapID);
	void onRender();
	SYN_THE_SIZE(int, m_nID, ID);//包含了变量定义，还有get，set接口。
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(CVec2, m_vPos, Pos);
	SYN_THE_SIZE(int, m_nMapID, MapID);
	SYN_THE_SIZE(int, m_nType, Type);
	SYN_THE_SIZE(string, m_strPic, Pic);

	/*CVec2 getPos()
	{
		return m_vPos;
	}
	int getMapID()
	{
		return m_nMapID;
	}
	string getPic()
	{
		return m_strPic;
	}

	int getType()
	{
		return m_nType;
	}


	
public:
	string getName()
	{
		return m_strName;
	}
	void setName(string strName)
	{
		m_strName = strName;
	}
private:
	string m_strName;

private:
	
	
	CVec2 m_vPos;
	int m_nMapID;
	string m_strPic;
	int m_nType;*/
};

