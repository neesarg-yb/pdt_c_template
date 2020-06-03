#include "platform.h"
#include "../game-resources.h"

IntVec2 m_platformPos;
int m_platformAngle = 100;  // Degrees

int const m_platformRingwidth = 230;
int const m_platformRingthickness = 1;
int const m_platformThickness = 8;
int const m_platformLengthDegrees = 30;

void SpawnPlatform(void)
{
    int const halfWidth = m_platformRingwidth * 0.5f;
    m_platformPos.x = screenCenter.x - halfWidth;
    m_platformPos.y = screenCenter.y - halfWidth;
}

void DestroyPlatform(void)
{

}

void UpdatePlatform(float const deltaSeconds)
{
    if(!g_pd->system->isCrankDocked())
    {
        float deltaAngle = g_pd->system->getCrankChange();
        m_platformAngle += (deltaAngle * 0.8f);
    }
}

void RenderPlatform(void)
{
    // Platform ring
    g_pd->graphics->drawEllipse(NULL, NULL,
        m_platformPos.x, m_platformPos.y,
        m_platformRingwidth, m_platformRingwidth, m_platformRingthickness,
        0, 0, kColorBlack, LCDMakeRect(0,0,0,0));

    // Platform itself
    g_pd->graphics->drawEllipse(NULL, NULL,
        m_platformPos.x, m_platformPos.y,
        m_platformRingwidth, m_platformRingwidth, m_platformThickness,
        m_platformAngle, m_platformAngle + m_platformLengthDegrees, 
        kColorBlack, LCDMakeRect(0,0,0,0));
}