#include "projectile.h"
#include "platform.h"
#include "../math-utils/vector.h"
#include "../game-resources.h"

Vec2 m_projectilePos = { 0, 0 };
Vec2 m_projectileVel = { 0, 0 };
bool m_projectileFired = false;

void SpawnProjectile(void)
{
    m_projectileFired = false;
    m_projectilePos = GetDockPosOnPlatform();
}

void DestroyProjectile(void)
{

}

void UpdateProjectile(float const deltaSeconds)
{
    bool aButtonJustPressed = false;
    {
        PDButtons pushedButtons = 0;
        g_pd->system->getButtonState(NULL, &pushedButtons, NULL);

        aButtonJustPressed = (pushedButtons & kButtonA) == kButtonA;
    }

    if(!m_projectileFired && aButtonJustPressed)
        FireProjectile();
    
    if(!m_projectileFired)
        m_projectilePos = GetDockPosOnPlatform();

    if(m_projectileFired)
    {
        // Update Velocity

        // Update Position
        Vec2 const posDisp = Vec2Scale(m_projectileVel, deltaSeconds);
        m_projectilePos = Vec2Sum(m_projectilePos, posDisp);
    }
}

void RenderProjectile(void)
{
    g_pd->graphics->fillEllipse(NULL, NULL,
        m_projectilePos.x - 5, m_projectilePos.y - 5,
        10, 10,
        0, 0, kColorXOR, LCDMakeRect(0,0,0,0) );
}

void FireProjectile(void)
{
    Vec2 const projToScreenCenter = Vec2Sub( ToVec2(screenCenter), m_projectilePos);
    Vec2 const velocityDir = Vec2Normalize(projToScreenCenter);

    m_projectileVel = Vec2Scale(velocityDir, 80.f);
    m_projectileFired = true;
}

bool IsProjectileFired(void)
{
    return m_projectileFired;
}