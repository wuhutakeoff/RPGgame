#pragma once
#include "DataStruct.h"
#include "Define.h"
#include "Vec2.h"
#include <vector>
using namespace std;
class CSkill
{
public:
	CSkill();
	void initWithData(CSkillDt* pData);
	void onRender();
	void onUpdate();
	bool isEquals(int nRow, int nCol);
	SYN_THE_SIZE_READONLY(int, m_nID, ID);
	SYN_THE_SIZE_READONLY(string, m_strName,Name);
	SYN_THE_SIZE_READONLY(int, m_nDamage, Damage);
	SYN_THE_SIZE_READONLY(int, m_nDefense, Defense);
	SYN_THE_SIZE_READONLY(int, m_nHp, Hp);
	SYN_THE_SIZE_READONLY(int, m_nMp, Mp);
	SYN_THE_SIZE_READONLY(int, m_nType, Type);
	SYN_THE_SIZE_READONLY(int, m_nRoleID, RoleID);
	SYN_THE_SIZE(CVec2, m_vPos, Position);
	SYN_THE_SIZE_READONLY(string, m_strPic, Pic);
	
private:

};

