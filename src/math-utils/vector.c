#include "vector.h"
#include <math.h>

float Vec2Length(Vec2 const a)
{
    float const vecLength = sqrtf( (a.x * a.x) + (a.y * a.y) );
    return vecLength;
}

Vec2 Vec2Sum(Vec2 const a, Vec2 const b)
{
    Vec2 sum = 
    {
        a.x + b.x,
        a.y + b.y
    };

    return sum;
}

Vec2 Vec2Sub(Vec2 const a, Vec2 const b)
{
    Vec2 sub =
    {
        a.x - b.x,
        a.y - b.y
    };

    return sub;
}

Vec2 Vec2Scale(Vec2 const a, float const scale)
{
    Vec2 scaledVec2 =
    {
        a.x * scale,
        a.y * scale
    };

    return scaledVec2;
}

Vec2 Vec2Div(Vec2 const a, float const divider)
{
    Vec2 divAns =
    {
        a.x / divider,
        a.y / divider
    };

    return divAns;
}

Vec2 Vec2Normalize(Vec2 const a)
{
    float const length = Vec2Length(a);
    return Vec2Div(a, length);
}

Vec2 ToVec2(IntVec2 from)
{
    Vec2 vecToRet =
    {
        from.x,
        from.y
    };

    return vecToRet;
}
