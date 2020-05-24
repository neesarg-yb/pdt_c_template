//
//  main.c
//  Extension
//
//  Created by Dave Hayden on 7/30/14.
//  Copyright (c) 2014 Panic, Inc. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

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
	
	return 0;
}
