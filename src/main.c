#include "pd_api.h"
#include "app.h"

static int update(__attribute__ ((unused)) void* ud)
{
	AppUpdate();
	return AppRender();
}

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, __attribute__ ((unused)) uint32_t arg)
{
	if ( event == kEventInit )
	{	
		AppInit(playdate);
		
		playdate->display->setRefreshRate(20);
		playdate->system->setUpdateCallback(update, NULL);
	}
	else if( event == kEventTerminate )
	{
		AppTerminate();
	}
	
	return 0;
}
