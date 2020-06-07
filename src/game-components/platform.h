#pragma once
#include "../math-utils/angle.h"
#include "../math-utils/vector.h"

void SpawnPlatform(void);
void DestroyPlatform(void);

void UpdatePlatform(float const deltaSeconds);
void RenderPlatform(void);

Vec2 GetDockPosOnPlatform(void);

Vec2  GetPlatformCenterPosition(void);
float GetPlatformRotationDegrees(void);
float GetPlatformLengthDegrees(void);
float GetPlatformThickness(void);
