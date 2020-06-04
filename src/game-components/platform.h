#pragma once
#include "../math-utils/vector.h"

void SpawnPlatform(void);
void DestroyPlatform(void);

void UpdatePlatform(float const deltaSeconds);
void RenderPlatform(void);

Vec2 GetDockPosOnPlatform(void);