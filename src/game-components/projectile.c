#include "projectile.h"
#include <math.h>
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
        m_projectilePos.x += m_projectileVel.x * deltaSeconds;
        m_projectilePos.y += m_projectileVel.y * deltaSeconds;
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
    Vec2 velocityDir = { 0, 0 };
    velocityDir.x = screenCenter.x - m_projectilePos.x;
    velocityDir.y = screenCenter.y - m_projectilePos.y;

    float const vecLength = sqrtf( (velocityDir.x * velocityDir.x) + (velocityDir.y * velocityDir.y) );
    velocityDir.x /= vecLength;
    velocityDir.y /= vecLength;

    m_projectileVel = velocityDir;
    m_projectileVel.x *= 80.f;
    m_projectileVel.y *= 80.f;

    m_projectileFired = true;
}

bool IsProjectileFired(void)
{
    return m_projectileFired;
}