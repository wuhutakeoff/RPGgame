#pragma once
#include "Define.h"
#include "Vec2.h"
class CRoleBase
{
public:
	CRoleBase();
	~CRoleBase();
	void onBackUp();
	void onRestore();
	void onRender();
	bool isEuqals(int nX, int nY);
	void setPosition(int nX, int nY);
	bool onDamage(int nDamage);

	SYN_THE_SIZE(CVec2, m_vPos, Position);
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nMp, Mp);
	SYN_THE_SIZE(int, m_nMaxHp, MaxHp);
	SYN_THE_SIZE(int, m_nMaxMp, MaxMp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDef, Def);
	SYN_THE_SIZE(string, m_strPic, Pic);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(int, m_nExp, Exp);
	SYN_THE_SIZE(int, m_nLevelUpExp, LevelUpExp);
	SYN_THE_SIZE(int, m_nMoney, Money);
	SYN_THE_SIZE(int, m_nSpeed, Speed);
	SYN_THE_SIZE(int, m_nLevel, Level);

private:

//处理战斗的公共函数
public:
	void setFightPosition(int nRow, int nCol);
	void changeState(int nState);
	bool isContain(int nRow, int nCol);
	//战斗图片移动
	void onFightMove(int nOffsetCol);
	CVec2 getCenterPos()
	{
		return m_arrFightPos[0];
	}
	SYN_THE_SIZE(bool, m_bReverse, Reverse);
private:

	CVec2 m_arrFightPos[6];
};
