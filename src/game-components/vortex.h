#pragma once
#include "../math-utils/vector.h"

void SpawnVortex(void);
void DestroyVortex(void);

void UpdateVortex(float const deltaSeconds);
void RenderVortex(void);

Vec2 GetVortexCenterPos(void);