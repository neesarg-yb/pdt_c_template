#include "game.h"
#include "game-resources.h"
#include "game-components/tiles.h"
#include "game-components/vortex.h"
#include "game-components/platform.h"
#include "game-components/projectile.h"

// Common resources
PlaydateAPI* g_pd = NULL;
LCDFont* g_font = NULL;

// Called when Playdate game is initalized
void GameInit(PlaydateAPI* playdate)
{
	SpawnPlatform();
	SpawnVortex();
	SpawnTiles();
	SpawnProjectile();
}

void GameTerminate(void)
{
	DestroyProjectile();
	DestroyTiles();
	DestroyVortex();
	DestroyPlatform();
}

// Called each frame, before GameRender
void GameUpdate(float const deltaSeconds)
{
	UpdatePlatform(deltaSeconds);
	UpdateProjectile(deltaSeconds);
	UpdateTiles(deltaSeconds);
	UpdateVortex(deltaSeconds);
}

// Called each frame, after GameUpdate
int GameRender(void)
{
	g_pd->graphics->clear(kColorWhite);

	RenderPlatform();
	RenderVortex();
	RenderTiles();
	RenderProjectile();

	GameRenderPrompt();
	g_pd->system->drawFPS(0,0);
	
    return 1;
}

void GameRenderPrompt(void)
{
	int const x = 25;
	int const y = (int)(LCD_ROWS * 0.83f);

	char const *promptMsg = "Press A to start..";
	g_pd->graphics->drawText(g_font, NULL, NULL, promptMsg, strlen(promptMsg), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));
}