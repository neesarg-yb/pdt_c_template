#include "app.h"
#include "game.h"
#include "game-resources.h"
#include "dev-window.h"
#include "options-menu.h"

unsigned int g_currentTimeMs = 0U;
bool g_isStepThroughOn = false;

void AppInit(PlaydateAPI* playdate)
{
    // Common resources
    g_pd = playdate;
	g_font = g_pd->graphics->loadFont("/System/Fonts/Asheville-Sans-14-Bold.pft", NULL);
    g_currentTimeMs = g_pd->system->getCurrentTimeMilliseconds();

    // Init systems
    GameInit(playdate);
    DevWindowInit();
    OptionsMenuInit();
}

void AppTerminate(void)
{
    OptionsMenuTerminate();
    DevWindowTerminate();
    GameTerminate();
}

void AppUpdate(void)
{
    // Calc delta seconds for this frame
    float deltaSeconds = 0.f;
    {
        unsigned int lastFrameTimeMs = g_currentTimeMs;
        g_currentTimeMs = g_pd->system->getCurrentTimeMilliseconds();

        deltaSeconds = ((float)(g_currentTimeMs - lastFrameTimeMs)) * 0.001f;
    }

    // Update the debug stuffs
    DevWindowUpdate(deltaSeconds);
    OptionsMenuUpdate(deltaSeconds);

    bool updateGameFrame = true;
    {
        // Pause game if:
        // in options menu OR stepping-through
        if(g_isOptionsMenuOpen || g_isStepThroughOn)
            updateGameFrame = false;
        
        bool rightLeftJustPressed = false;
        bool upDownCurrentlyPressed = false;
        {   
            PDButtons pushedButton = 0;
            PDButtons currentButton = 0;
            g_pd->system->getButtonState(&currentButton, &pushedButton, NULL);

            // Move forward
            if((pushedButton & kButtonRight) != 0)
                rightLeftJustPressed = true;
            else if((currentButton & kButtonUp) != 0)
                upDownCurrentlyPressed = true;
            
            // Move backwords
            if((pushedButton & kButtonLeft) != 0)
            {
                deltaSeconds *= -1.f;
                rightLeftJustPressed = true;
            }            
            else if((currentButton & kButtonDown) != 0)
            {
                deltaSeconds *= -1.f;
                upDownCurrentlyPressed = true;
            }
        }
        
        if(g_isStepThroughOn && (rightLeftJustPressed || upDownCurrentlyPressed))
            updateGameFrame = true;
    }

    if(updateGameFrame)
        GameUpdate(deltaSeconds);
}

int AppRender(void)
{
    GameRender();
    
    if(g_isDevWindowActive)
        DevWindowRender();

    if(g_isOptionsMenuOpen)
        OptionsMenuRender();
        
    return 1;
}