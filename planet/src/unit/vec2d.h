#pragma once

struct vec2d
{
    double x, y;

    double dot(vec2d other) const
    {
        return x * other.x + y * other.y;
    }
};
