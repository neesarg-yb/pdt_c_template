#include "collision.h"
#include <math.h>
#include <stdbool.h>
#include "vortex.h"
#include "platform.h"
#include "projectile.h"
#include "../game-resources.h"
#include "../math-utils/vector.h"

Angle CalcRotationDegreesFromCenter(Vec2 a, Vec2 center)
{
    Vec2 const centerToA = SubVec2(a, center);
    Vec2 const centerToADir = NormalizeVec2(centerToA);

    // Remember we're in fourth quadrant
    //
    //  center
    //  _|_____________ x
    //   |\) theta           .
    //   | \                 .
    //   |  \                .
    //   |   * a             .
    // y |
    // down

    float const thetaRad = atan2f(centerToADir.y, centerToADir.x);
    float const thetaFromUpRad = thetaRad + M_PI_2;

    return MakeAngleFromRad(thetaFromUpRad);
}

void ProjectileVsPlatformCollision(float const deltaSeconds)
{
    // Get projectile location data
    Vec2  vortexCenterPos       = GetVortexCenterPos();
    Vec2  projectilePos         = GetProjectilePos();
    Angle projRotationAngle     = CalcRotationDegreesFromCenter(projectilePos, vortexCenterPos);

    // Get platform location data
    float platThickness              = GetPlatformThickness();
    Angle platCenterRotationAngle    = GetPlatformRotationAngle();
    float platWidthDegrees           = GetPlatformLengthDegrees();

    // Is the projectile at same dist from center as the platform?
    bool isOverlappingPlatformCircle = false;
    {
        float const projRadius = GetProjectileRadius();
        float const centerToProjDist = LengthVec2( SubVec2(vortexCenterPos, projectilePos) );
        float const platformRingRadius = GetPlatformRingRadius();

        if( centerToProjDist <= (platformRingRadius + projRadius) &&
            centerToProjDist >= (platformRingRadius - platThickness - projRadius) )
        {
            isOverlappingPlatformCircle = true;
        }
    }

    float deltaDeg = 0.f;
    if(isOverlappingPlatformCircle)
    {
        // Is the projectile within rotation degree range of the platform?
        bool isOverlapingRotationDegrees = false;
        {
            Angle const deltaFromPlatCenter = DeltaAngle(projRotationAngle, platCenterRotationAngle);
            deltaDeg = DegreesFromAngle(deltaFromPlatCenter);

            float const absDeltaDeg = fabsf( deltaDeg );
            
            if(absDeltaDeg < platWidthDegrees * 0.5f)
            {
                isOverlapingRotationDegrees = true;
            }
        }

        if(isOverlapingRotationDegrees)
        {
            // Collision!
            Vec2 const projToCenterDir = NormalizeVec2( SubVec2(vortexCenterPos, projectilePos) );
            Vec2 projNewDir = projToCenterDir;
            {
                Angle dummyAngle;
                dummyAngle.r = projToCenterDir.x;
                dummyAngle.i = projToCenterDir.y;

                dummyAngle = AddDegreesToAngle(dummyAngle, -deltaDeg * 5.f);
                projNewDir.x = dummyAngle.r;
                projNewDir.y = dummyAngle.i;
            }

            SetProjectileVelocityDir(projNewDir);
            DevWindowPrint("Proj collided!");
        }
    }
}
