#include "game.h"
#include "game-resources.h"

// Common resources
PlaydateAPI* g_pd = NULL;
LCDFont* g_font = NULL;

// Game variables
#define TEXT_WIDTH 86
#define TEXT_HEIGHT 16

int x = (400-TEXT_WIDTH)/2;
int y = (240-TEXT_HEIGHT)/2;
int dx = 1;
int dy = 2;

// Called when Playdate game is initalized
void GameInit(PlaydateAPI* playdate)
{
	g_pd = playdate;
	g_font = g_pd->graphics->loadFont("/System/Fonts/Asheville-Sans-14-Bold.pft", NULL);
}

// Called each frame, before GameRender
void GameUpdate(void)
{
	x += dx; y += dy;
	
	if ( x < 0 || x > LCD_COLUMNS - TEXT_WIDTH )
	{
		dx = -dx;
		g_pd->system->logToConsole("DEB-NB: Text Reached to side of the LDC!\n");
	}

	if ( y < 0 || y > LCD_ROWS - TEXT_HEIGHT )
		dy = -dy;
}

// Called each frame, after GameUpdate
int GameRender(void)
{
	g_pd->graphics->clear(kColorWhite);
	g_pd->graphics->drawText(g_font, NULL, NULL, "Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));

	g_pd->system->drawFPS(0,0);

    return 1;
}