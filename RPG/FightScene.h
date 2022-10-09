#pragma once
#include "DataStruct.h"
#include "Player.h"
#include "Monster.h"
#include "Define.h"
#include <string>
#include "WndBase.h"
class CFightScene:public CWndBase
{
public:
	CFightScene();
	~CFightScene();
	void onUpdate();
	void onRender();
	//设置目标
	void setTarget(CPlayer* pPlayer, CMonster* pMonster);
	void showTarget();
	void showSelectMenu();
	void showSkill();
	void showConsumble();
	void setAllFalse();
	void useConsumble(CItem* pItem);

	SYN_THE_SIZE(int, m_nCurIndex, CurIndex);
private:
	CMapDt* m_pCurMapDt;
	//用于处理战斗场景里面的逻辑，到时候玩家碰到怪物，把玩家和怪物设置进来
	CPlayer* m_pPlayer;
	CMonster* m_pMonster;

	//布尔值表示玩家回合，默认玩家先手
	bool m_bPlayerRound;
	bool m_bPetRound;

	bool m_bDefense;

	bool m_bShowSkill;
	bool m_bInSkill;

	//显示
	bool m_bShowConsumble;
	bool m_bInComsuble;

	bool m_bIsFlee;
	bool m_bUseSkill;
	bool m_bUseBall;
	//当前玩家或者怪物的状态。
	string m_strState;

	int m_nCurSkillIndex;
	int m_nCurConsumbleIndex;
	int m_nSkillIndex;
	int m_nCount;

	vector<CItem*> m_vecItems;
	vector<CSkill*> m_vecSkills;
};


