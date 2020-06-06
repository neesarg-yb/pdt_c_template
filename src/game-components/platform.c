#include "platform.h"
#include <math.h>
#include "../game-resources.h"
#include "../math-utils/vector.h"

IntVec2 m_platformPos;
int m_platformAngle = 0;  // Degrees

int const m_platformRingwidth = 230;
int const m_platformRingthickness = 1;
int const m_platformThickness = 8;
int const m_platformLengthDegrees = 30;

void SpawnPlatform(void)
{
    int const halfWidth = m_platformRingwidth * 0.5f;
    m_platformPos = ModCompIntVec2(screenCenter, -halfWidth);
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
        m_platformAngle - (m_platformLengthDegrees * 0.5f), m_platformAngle + (m_platformLengthDegrees * 0.5f), 
        kColorBlack, LCDMakeRect(0,0,0,0));
}

Vec2 GetDockPosOnPlatform(void)
{
    Vec2 dockPos = { 0.f, 0.f };
    {
        float const dockAngleDeg = m_platformAngle;
        float const platformAngleRad = dockAngleDeg * M_PI / 180.f;
        dockPos.x = (m_platformRingwidth * 0.45f) * cos(platformAngleRad - M_PI_2);
        dockPos.y = (m_platformRingwidth * 0.45f) * sin(platformAngleRad - M_PI_2);

        dockPos = SumVec2(dockPos, Vec2FromIntVec2(screenCenter));
    }   

    return dockPos;
}