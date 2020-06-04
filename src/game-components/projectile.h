#pragma once
#include <stdbool.h>

void SpawnProjectile(void);
void DestroyProjectile(void);

void UpdateProjectile(float const deltaSeconds);
void RenderProjectile(void);

void FireProjectile(void);
bool IsProjectileFired(void);
