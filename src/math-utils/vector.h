#pragma once

typedef struct
{
    float x;
    float y;
} Vec2;

float Vec2Length(Vec2 const a);

Vec2 Vec2Sum(Vec2 const a, Vec2 const b);
Vec2 Vec2Sub(Vec2 const a, Vec2 const b);
Vec2 Vec2Scale(Vec2 const a, float const scale);
Vec2 Vec2Div(Vec2 const a, float const divider);
Vec2 Vec2Normalize(Vec2 const a);

typedef struct
{
    int x;
    int y;
} IntVec2;

Vec2 ToVec2(IntVec2 const from);