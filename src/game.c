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
int dx = 40;	// pxl per seconds
int dy = 40;	// pxl per seconds

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
	// Run the game
	x += dx * deltaSeconds; 
	y += dy * deltaSeconds;
	
	if ( x < 0 || x > LCD_COLUMNS - TEXT_WIDTH )
	{
		dx = -dx;
		g_pd->system->logToConsole("DEB-NB: Text Reached to side of the LDC!\n");

		if(dx > 0)
			DevWindowPrint("DEB-NB: Text turned towards RIGHT side of screen!");
		else
			DevWindowPrint("DEB-NB: Text bounced to the LEFT side!");
	}

	if ( y < 0 || y > LCD_ROWS - TEXT_HEIGHT )
	{
		dy = -dy;

		if(dy < 0)
			DevWindowPrint("DEB-NB: Text now goes UPWARDS!");
		else
			DevWindowPrint("DEB-NB: Gravity pulling DOWN the text!");
	}
}

// Called each frame, after GameUpdate
int GameRender(void)
{
	g_pd->graphics->clear(kColorWhite);
	g_pd->graphics->drawText(g_font, NULL, NULL, "Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));

	g_pd->system->drawFPS(0,0);
	
    return 1;
}