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

IntVec2 m_pos;
int m_width = 50;
int m_modifier = 0;
void UpdateVortex(float const deltaSeconds)
{
    {    
        static float theta = 0;
        theta += (90.f * deltaSeconds);
        if(theta > 360.f)
            theta -= 360.f;

        m_modifier = sin(theta * 3.14 / 360) * 7;
    }

    int const halfWidth = (m_width + m_modifier) * 0.5f;
    m_pos.x = screenCenter.x - halfWidth;
    m_pos.y = screenCenter.y - halfWidth;
}

void RenderVortex(void)
{
    g_pd->graphics->fillEllipse(NULL, NULL, 
        m_pos.x, m_pos.y, 
        m_width + m_modifier, m_width + m_modifier, 
        0, 0, kColorBlack, LCDMakeRect(0,0,0,0));
}