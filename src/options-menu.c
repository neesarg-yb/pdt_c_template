#include "options-menu.h"
#include "stdbool.h"
#include "pd_api.h"
#include "game-resources.h"

LCDBitmap*  g_optionsMenuBitmap = NULL;
bool        g_isOptionsMenuOpen = false;

int const optionMenuWidth    = LCD_COLUMNS * 0.5f;
int const optionMenuHeight   = LCD_ROWS * 0.5f;

#define NUM_OPTIONS 3
const char *menuOptionsStr[ NUM_OPTIONS ] = { "toggle console", "toggle steps (d-pad)", "close menu" };
int selectionIdx = 0;

// Called when A button is pressed in OptionsMenu
void MenuOptionSelected(int const optionIdx)
{
    if(optionIdx == 0)
        g_isDevWindowActive = !g_isDevWindowActive;     // toggle console
    else if(optionIdx == 1)
    {
        g_isStepThroughOn = !g_isStepThroughOn;         // Step through
        g_isOptionsMenuOpen = false;
    }
    else if(optionIdx == 2)
        g_isOptionsMenuOpen = false;                    // close menu
}

// Called when "options" is selected from Playdate Menu
int PlaydateOptionsMenu_CallBack(void* userdata)
{
    g_isOptionsMenuOpen = !g_isOptionsMenuOpen;
    return 1;
}

void OptionsMenuInit(void)
{
    g_optionsMenuBitmap = g_pd->graphics->newBitmap(optionMenuWidth, optionMenuHeight, kColorBlack);
    g_pd->system->setOptionsCallback(PlaydateOptionsMenu_CallBack, NULL);
}

void OptionsMenuTerminate(void)
{
    g_pd->system->realloc(g_optionsMenuBitmap, 0);
}

void OptionsMenuUpdate(float const deltaSeconds)
{
    if(!g_isOptionsMenuOpen)
        return;

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
        MenuOptionSelected(selectionIdx);

    // Hit B button
    if((pushedButton & kButtonB) != 0)
        selectionIdx = 2;       // select "close menu"
}

void OptionsMenuRender(void)
{
    // Clear old bitmap
    g_pd->graphics->clearBitmap(g_optionsMenuBitmap, kColorBlack);

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
            int const boxWidth  = optionMenuWidth - (x*2);
            int const boxHeight = 18;
            g_pd->graphics->fillRect(g_optionsMenuBitmap, NULL, x, y + 1, boxWidth, boxHeight, kColorWhite, clipRect);

            // Draw text in black color
            g_pd->graphics->drawText(g_font, g_optionsMenuBitmap, NULL, menuOptionsStr[i], strlen(menuOptionsStr[i]), kASCIIEncoding, x, y, kDrawModeFillBlack, 0, clipRect);
        }
        else
        {
            // Draw menu text in white color
            g_pd->graphics->drawText(g_font, g_optionsMenuBitmap, NULL, menuOptionsStr[i], strlen(menuOptionsStr[i]), kASCIIEncoding, x, y, kDrawModeFillWhite, 0, clipRect);
        }
        
    }

    // Render the bitmap
    g_pd->graphics->drawBitmap(g_optionsMenuBitmap, NULL, NULL, LCD_COLUMNS * 0.25f, LCD_ROWS * 0.25f, kDrawModeCopy, kBitmapUnflipped, clipRect);
}