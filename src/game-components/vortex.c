#include "vortex.h"
#include <math.h>
#include "../game-resources.h"
#include "../debug-utils/dev-window.h"

void SpawnVortex(void)
{

}

void DestroyVortex(void)
{

}

IntVec2 m_vortexPos;
int m_vortexBoxWidth = 50;
int m_vortexBoxHeight = 50;
int m_boxWidthModifier = 0;
int m_boxHeightModifier = 0;
void UpdateVortex(float const deltaSeconds)
{
    // Calculate  modifiers
    {
        // Width
        static float theta = 0;
        static float alpha = 0;
        theta += (90.f * deltaSeconds);
        alpha += (65.f * deltaSeconds);

        float const thetaRad = theta * M_PI / 180.f;
        float const alphaRad = alpha * M_PI / 180.f;
        m_boxWidthModifier = sin(thetaRad) * 4;
        m_boxHeightModifier = sin(alphaRad + M_PI_2) * 4;
    }

    int const halfWidth  = (m_vortexBoxWidth  + m_boxWidthModifier) * 0.5f;
    int const halfHeight = (m_vortexBoxHeight + m_boxHeightModifier) * 0.5f;
    m_vortexPos.x = screenCenter.x - halfWidth;
    m_vortexPos.y = screenCenter.y - halfHeight;
}

void RenderVortex(void)
{
    g_pd->graphics->fillEllipse(NULL, NULL, 
        m_vortexPos.x, m_vortexPos.y, 
        m_vortexBoxWidth + m_boxWidthModifier, m_vortexBoxHeight + m_boxHeightModifier, 
        0, 0, kColorBlack, LCDMakeRect(0,0,0,0));
}