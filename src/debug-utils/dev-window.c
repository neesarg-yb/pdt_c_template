#include "dev-window.h"
#include "stdbool.h"
#include "dev-console-msg.h"
#include "../game-resources.h"

LCDBitmap*  g_devWindowBitmap   = NULL;
bool        g_isDevWindowActive = false;

void DevWindowInit(void)
{
    g_devWindowBitmap = g_pd->graphics->newBitmap(LCD_COLUMNS, LCD_ROWS, kColorClear);
    DevWindowPrint("DevWindow Output:");
}

void DevWindowTerminate(void)
{
    DevConsoleMessagesClearAll();
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
    // Clear bitmap
    g_pd->graphics->clearBitmap(g_devWindowBitmap, kColorClear);

    // Draw DevConsole message text one by one
    static int const startX = 3;
    static int const startY = 18;
    static int const textHeight = 18;

    for(int i = 0; i < GetDevConsoleMessagesCount(); i++)
    {
        int x = startX;
        int y = startY + (i * textHeight);

        char const *consoleMsg = GetDevConsoleMessage(i);
        g_pd->graphics->drawText(g_font, g_devWindowBitmap, NULL, consoleMsg, strlen(consoleMsg), kASCIIEncoding, x, y, kDrawModeCopy, 0, LCDMakeRect(0,0,0,0));
    }
    
    // Draw bitmap to screen
    g_pd->graphics->drawBitmap(g_devWindowBitmap, NULL, NULL, 0, 0, kDrawModeCopy, kBitmapUnflipped, LCDMakeRect(0,0,0,0));
}

void DevWindowPrint(char const* msg)
{
    DevConsoleMessagesPush(msg, 10);
}

