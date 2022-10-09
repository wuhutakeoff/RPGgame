#pragma once
#include"Define.h"
#include"DataStruct.h"
#include "Vec2.h"

class CItem
{
public:
	CItem();
	CItem(CItemDt* pItemDt);
	CItem(string strName, int nHp, int nMp, int nAck, int nDef,int nCount);
	~CItem();
	void addCount(int nCount)
	{
		m_nCount+=nCount;
	}
	void onRender();
	bool isEquals(int i, int j);
	void setFightPos(int i, int j);
	void onFightMove(int nMove);
	CVec2 getFightPos()
	{
		return m_arrFightPos[0];
	}

	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nMp, Mp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDef, Def);
	SYN_THE_SIZE(string, m_strPic, Pic);
	SYN_THE_SIZE(string, m_strDescription, Description);
	SYN_THE_SIZE(int, m_nPrice, Price);
	SYN_THE_SIZE(string, m_strType, Type);
	SYN_THE_SIZE(int, m_nCount, Count);

private:
	CVec2 m_arrFightPos[5];
};



