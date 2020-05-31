#include "dev-window.h"
#include "stdbool.h"
#include "game-resources.h"

LCDBitmap*  g_devWindowBitmap         = NULL;
bool        g_isDevWindowActive = false;

void DevWindowInit(void)
{
    g_devWindowBitmap = g_pd->graphics->newBitmap(LCD_COLUMNS, LCD_ROWS, kColorClear);
    DevWindowPrint("DevWindow Output:");
}

void DevWindowTerminate(void)
{
    g_pd->system->realloc(g_devWindowBitmap, 0);
}

void DevWindowUpdate(float const deltaseconds)
{
    if(!g_isDevWindowActive)
        return;

    // Nothing for now
}

void DevWindowRender(void)
{
    g_pd->graphics->drawBitmap(g_devWindowBitmap, NULL, NULL, 0, 0, kDrawModeCopy, kBitmapUnflipped, LCDMakeRect(0,0,0,0));
}

void DevWindowPrint(char const* msg)
{
    const  int x = 3;
    static int y = 0;
    
    y = y + 18;
    g_pd->graphics->drawText(g_font, g_devWindowBitmap, NULL, msg, strlen(msg), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));
}

