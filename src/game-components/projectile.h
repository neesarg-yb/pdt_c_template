#pragma once
#include <stdbool.h>
#include "../math-utils/vector.h"

void SpawnProjectile(void);
void DestroyProjectile(void);

void UpdateProjectile(float const deltaSeconds);
void RenderProjectile(void);

void FireProjectile(void);
bool IsProjectileFired(void);

Vec2 GetProjectilePos(void);