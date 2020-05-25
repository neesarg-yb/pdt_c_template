#include "dev-window.h"
#include "game-resources.h"

LCDBitmap* g_devBitmap = NULL;

void DevWindowInit(void)
{
    g_devBitmap = g_pd->graphics->newBitmap(LCD_COLUMNS, LCD_ROWS, kColorClear);
}

void DevWindowTerminate(void)
{
    g_pd->system->realloc(g_devBitmap, 0);
}

void DevWindowRender(void)
{
    LCDRect devWindowRect;
    {
        devWindowRect.left = 0;
        devWindowRect.right = LCD_COLUMNS;
        devWindowRect.top = 0;
        devWindowRect.bottom = LCD_ROWS;
    }

    g_pd->graphics->drawBitmap(g_devBitmap, NULL, NULL, 0, 0, kDrawModeCopy, kBitmapUnflipped, devWindowRect);
}

void DevWindowPrint(char const* msg)
{
    const  int x = 3;
    static int y = 0;
    
    y = y + 18;
	g_pd->graphics->drawText(g_font, g_devBitmap, NULL, msg, strlen(msg), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));
}

