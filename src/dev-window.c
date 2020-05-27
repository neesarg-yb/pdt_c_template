#include "dev-window.h"
#include "stdbool.h"
#include "game-resources.h"

LCDBitmap*      g_devBitmap         = NULL;
LCDBitmap*      g_devMenuBitmap     = NULL;
DevWindowState  g_devWindowState    = kDevWindowClosed;

int DevWindowOptions_callback(void* userdata)
{
    switch(g_devWindowState)
    {
        case kDevWindowClosed:
        case kDevWindowConsole:
            g_devWindowState = kDevWindowOptionsMenu;
            break;
        
        case kDevWindowOptionsMenu:
            g_devWindowState = kDevWindowClosed;
    }

    return 1;
}

int const devOptionMenuWidth    = LCD_COLUMNS * 0.5f;
int const devOptionMenuHeight   = LCD_ROWS * 0.5f;

void DevWindowInit(void)
{
    g_pd->system->setOptionsCallback(DevWindowOptions_callback, NULL);

    g_devBitmap     = g_pd->graphics->newBitmap(LCD_COLUMNS, LCD_ROWS, kColorClear);
    g_devMenuBitmap = g_pd->graphics->newBitmap(devOptionMenuWidth, devOptionMenuHeight, kColorBlack);
}

void DevWindowTerminate(void)
{
    g_pd->system->realloc(g_devMenuBitmap, 0);
    g_pd->system->realloc(g_devBitmap, 0);
}

void DevWindowUpdate()
{
    switch (g_devWindowState)
    {
    case kDevWindowOptionsMenu:
        DevWindowUpdate_OptionsMenu();
        break;
    
    case kDevWindowConsole:
        DevWindowUpdate_Console();
        break;

    default:
        break;
    }
}

#define NUM_OPTIONS 3
const char *menuOptionsStr[ NUM_OPTIONS ] = { "open console", "close console", "step through" };
int selectionIdx = 0;

void DevMenuOptionSelected(int idx)
{
    switch (idx)
    {
    case 0:
        g_devWindowState = kDevWindowConsole;
        break;
    
    case 1:
        g_devWindowState = kDevWindowClosed;
        break;
        
    case 2:
        break;
    
    default:
        break;
    }
}

void DevWindowUpdate_OptionsMenu(void)
{
    PDButtons pushedButton = 0;
    g_pd->system->getButtonState(NULL, &pushedButton, NULL);

    // Down Button pushed
    if((pushedButton & kButtonDown) != 0)
        selectionIdx++;

    // Up Button pushed
    if((pushedButton & kButtonUp) != 0)
        selectionIdx--;

    // Selection wraps top-to-bottom kinda deal..
    if(selectionIdx < 0)
        selectionIdx = NUM_OPTIONS - 1;
    else if(selectionIdx >= NUM_OPTIONS)
        selectionIdx = 0;

    // Hit A button
    if((pushedButton & kButtonA) != 0)
        DevMenuOptionSelected(selectionIdx);
}

void DevWindowUpdate_Console(void)
{
    // Nothing for now
}

void DevWindowRender(void)
{
    switch (g_devWindowState)
    {
    case kDevWindowOptionsMenu:
        DevWindowRender_Console();
        DevWindowRender_OptionsMenu();
        break;
    
    case kDevWindowConsole:
        DevWindowRender_Console();
        break;

    default:
        break;
    }
}

void DevWindowRender_OptionsMenu(void)
{
    // Clear old bitmap
    g_pd->graphics->clearBitmap(g_devMenuBitmap, kColorBlack);

    LCDRect clipRect;
    {
        clipRect.left = 0;
        clipRect.right = 0;
        clipRect.top = 0;
        clipRect.bottom = 0;
    }

    // Draw new stuffs to the bitmap
    for(int i = 0; i < NUM_OPTIONS; i++)
    {
        int const x = 3;
        int const y = 20 * i;

        if(i == selectionIdx)
        {
            // Draw selection box
            int const boxWidth  = devOptionMenuWidth - (x*2);
            int const boxHeight = 18;
            g_pd->graphics->fillRect(g_devMenuBitmap, NULL, x, y + 1, boxWidth, boxHeight, kColorWhite, clipRect);

            // Draw text in black color
            g_pd->graphics->drawText(g_font, g_devMenuBitmap, NULL, menuOptionsStr[i], strlen(menuOptionsStr[i]), kASCIIEncoding, x, y, kDrawModeFillBlack, 0, clipRect);
        }
        else
        {
            // Draw menu text in white color
            g_pd->graphics->drawText(g_font, g_devMenuBitmap, NULL, menuOptionsStr[i], strlen(menuOptionsStr[i]), kASCIIEncoding, x, y, kDrawModeFillWhite, 0, clipRect);
        }
        
    }

    // Render the bitmap
    g_pd->graphics->drawBitmap(g_devMenuBitmap, NULL, NULL, LCD_COLUMNS * 0.25f, LCD_ROWS * 0.25f, kDrawModeCopy, kBitmapUnflipped, clipRect);
}

void DevWindowRender_Console(void)
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

