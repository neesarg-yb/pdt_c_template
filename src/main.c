#include "pd_api.h"
#include "game.h"

static int update(__attribute__ ((unused)) void* ud)
{
	GameUpdate();
	return GameRender();
}

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, __attribute__ ((unused)) uint32_t arg)
{
	if ( event == kEventInit )
	{	
		GameInit(playdate);
		
		playdate->display->setRefreshRate(20);
		playdate->system->setUpdateCallback(update, NULL);
	}
	else if( event == kEventTerminate )
	{
		GameTerminate();
	}
	
	return 0;
}
