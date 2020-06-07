#include "collision.h"
#include <stdbool.h>
#include "vortex.h"
#include "platform.h"
#include "projectile.h"
#include "../game-resources.h"
#include "../math-utils/vector.h"

void PushProjectileAwayFromPlatform(void)
{
    // TODO: Implement
}

float CalcRotationDegreesFromCenter(Vec2 a, Vec2 center)
{
    //TODO: Implement
    return 30.f;
}

void ProjectileVsPlatformCollision(float const deltaSeconds)
{
    // Get projectile location data
    Vec2  vortexCenterPos       = GetVortexCenterPos();
    Vec2  projectilePos         = GetProjectilePos();
    float projDistFromCenter    = LengthVec2( SubVec2(projectilePos, vortexCenterPos) );
    float projRotationDegrees   = CalcRotationDegreesFromCenter(projectilePos, vortexCenterPos);
    {
        char *msgProjRot = NULL;
        g_pd->system->formatString(&msgProjRot, "ProjRotation = %.2f deg", projRotationDegrees);
        DevWindowPrint(msgProjRot);
        g_pd->system->realloc(msgProjRot, 0);
    }

    // Get platform location data
    Vec2  platformPos                = GetPlatformCenterPosition();
    float platDistFromCenter         = LengthVec2( SubVec2(platformPos, vortexCenterPos) );
    float platThickness              = GetPlatformThickness();
    float platCenterRotationDegerees = GetPlatformRotationDegrees();;
    float platWidthDegrees           = GetPlatformLengthDegrees();

    // Is the projectile at same dist from center as the platform?
    bool isOverlappingPlatformCircle = false;
    {
        
    }

    if(isOverlappingPlatformCircle)
    {
        // Is the projectile within rotation degree range of the platform?
        bool isOverlapingRotationDegrees = false;
        {
            // TODO: Calculate
        }

        if(isOverlapingRotationDegrees)
        {
            // Collision!
            PushProjectileAwayFromPlatform();
        }
    }
}
