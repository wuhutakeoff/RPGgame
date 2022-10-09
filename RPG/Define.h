#pragma once
//很多源文件需要用到的内容写在这里，到时候那边直接include就可以。
#include <windows.h>
#include <iostream>
using namespace std;

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code)&0x8000?1:0)
#define VK_B 0x42
#define VK_P 0x50
#define SAFE_DEL(p) if(p){delete p; p = nullptr;}



extern bool g_bClear;

enum
{
	E_MENU_START,
	E_MENU_SET,
	E_MENU_EXIT
};


enum
{
	E_GAME_MENU,
	E_GAME_MAP,
	E_GAME_SHOP,
	E_GAME_BAG,
	E_GAME_FIGHT,
	E_GAME_ROLESELECT
};
enum 
{
	E_BUY_IDLE,
	E_BUY_SECCUSS,
	E_BUY_FAILED
	
};

enum
{
	E_DIR_NONE,
	E_DIR_UP,
	E_DIR_DOWN,
	E_DIR_LEFT,
	E_DIR_RIGHT
};

enum
{
	E_FIGHT_IDLE,
	E_FIGHT_ATTACK,
	E_FIGHT_BACK
};

#define SYN_THE_SIZE(valueType,valueName,funcName)\
public:\
	valueType get##funcName()\
	{\
		return valueName;\
	}\
	void set##funcName(valueType value)\
	{\
		valueName = value;\
	}\
protected:\
	valueType valueName;


#define SYN_THE_SIZE_READONLY(valueType,valueName,funcName)\
public:\
	valueType get##funcName()\
	{\
		return valueName;\
	}\
protected:\
	valueType valueName;