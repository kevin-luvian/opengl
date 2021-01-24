#pragma once

struct vec4d
{
    double x, y, z, w;

    double dot(vec4d other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
};
