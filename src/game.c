#include "game.h"
#include "game-resources.h"

// Common resources
PlaydateAPI* g_pd = NULL;
LCDFont* g_font = NULL;

// Called when Playdate game is initalized
void GameInit(PlaydateAPI* playdate)
{

}

void GameTerminate(void)
{
	
}

// Called each frame, before GameRender
void GameUpdate(float const deltaSeconds)
{

}

// Called each frame, after GameUpdate
int GameRender(void)
{
	g_pd->graphics->clear(kColorWhite);
	g_pd->graphics->drawText(g_font, NULL, NULL, "Hello World!", strlen("Hello World!"), kASCIIEncoding, 10, 30, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));

	g_pd->system->drawFPS(0,0);
	
    return 1;
}