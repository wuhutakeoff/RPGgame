#include "Define.h"
#include "GameMgr.h"
#include "GameMenu.h"
#include "DataStruct.h"

bool g_bClear = false;

int main()
{
	CLoader::load();
	CGameMgr::getInstance()->runWithWnd(new CGameMenu());
	while (true)
	{
		CGameMgr::getInstance()->mainLoop();
	}
}


