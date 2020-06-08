#include "projectile.h"
#include "platform.h"
#include "../math-utils/vector.h"
#include "../game-resources.h"

Vec2  m_projectilePos = { 0, 0 };
Vec2  m_projectileVel = { 0, 0 };
bool  m_projectileFired = false;
float m_projectileRadius = 10.f;

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
        Vec2 const posDisp = ScaleVec2(m_projectileVel, deltaSeconds);
        m_projectilePos = SumVec2(m_projectilePos, posDisp);
    }
}

void RenderProjectile(void)
{
    float const halfRadius = m_projectileRadius * 0.5f;

    g_pd->graphics->fillEllipse(NULL, NULL,
        m_projectilePos.x - halfRadius, m_projectilePos.y - halfRadius,
        m_projectileRadius, m_projectileRadius,
        0, 0, kColorXOR, LCDMakeRect(0,0,0,0) );
}

void FireProjectile(void)
{
    Vec2 const projToScreenCenter = SubVec2( Vec2FromIntVec2(screenCenter), m_projectilePos);
    Vec2 const velocityDir = NormalizeVec2(projToScreenCenter);

    m_projectileVel = ScaleVec2(velocityDir, 80.f);
    m_projectileFired = true;

    DevWindowPrint("Projectile fired!");
}

bool IsProjectileFired(void)
{
    return m_projectileFired;
}

Vec2 GetProjectilePos(void)
{
    return m_projectilePos;
}

float GetProjectileRadius(void)
{
    return m_projectileRadius;
}

void SetProjectileVelocityDir(Vec2 const velDir)
{
    m_projectileVel = ScaleVec2(velDir, LengthVec2(m_projectileVel));
}
