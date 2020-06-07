#include "platform.h"
#include <math.h>
#include "vortex.h"
#include "../game-resources.h"
#include "../math-utils/vector.h"

IntVec2 m_ringBoxBottomLeft;
int m_platformAngle = 0;  // Degrees

int const m_platformRingRadius = 230;
int const m_platformRingThickness = 1;
int const m_platformThickness = 8;
int const m_platformLengthDegrees = 30;

void SpawnPlatform(void)
{
    int const halfRadius = m_platformRingRadius * 0.5f;
    m_ringBoxBottomLeft = ModCompIntVec2(screenCenter, -halfRadius);
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
        m_ringBoxBottomLeft.x, m_ringBoxBottomLeft.y,
        m_platformRingRadius, m_platformRingRadius, m_platformRingThickness,
        0, 0, kColorBlack, LCDMakeRect(0,0,0,0));

    // Platform itself
    g_pd->graphics->drawEllipse(NULL, NULL,
        m_ringBoxBottomLeft.x, m_ringBoxBottomLeft.y,
        m_platformRingRadius, m_platformRingRadius, m_platformThickness,
        m_platformAngle - (m_platformLengthDegrees * 0.5f), m_platformAngle + (m_platformLengthDegrees * 0.5f), 
        kColorBlack, LCDMakeRect(0,0,0,0));
}

Vec2 GetDockPosOnPlatform(void)
{
    Vec2 const platCenterPos = GetPlatformCenterPosition();
    
    Vec2 const vortexCenterPos = GetVortexCenterPos();
    Vec2 const platToScreenCenterDir = NormalizeVec2( SubVec2(vortexCenterPos, platCenterPos) );
    
    Vec2 const posModifier = ScaleVec2(platToScreenCenterDir, 12.f);    // 12 units towards the vortex

    return SumVec2(platCenterPos, posModifier);
}

Vec2 GetPlatformCenterPosition(void)
{
    Vec2 platCenterPos = { 0.f, 0.f };
    {
        float const platformAngleRad = m_platformAngle * M_PI / 180.f;
        platCenterPos.x = (m_platformRingRadius * 0.5f) * cos(platformAngleRad - M_PI_2);
        platCenterPos.y = (m_platformRingRadius * 0.5f) * sin(platformAngleRad - M_PI_2);

        platCenterPos = SumVec2(platCenterPos, Vec2FromIntVec2(screenCenter));
    }

    return platCenterPos;
}

float GetPlatformRotationDegrees(void)
{
    return m_platformAngle;
}

float GetPlatformLengthDegrees(void)
{
    return m_platformLengthDegrees;
}

float GetPlatformThickness(void)
{
    return m_platformThickness;
}