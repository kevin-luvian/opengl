#pragma once

struct vec3d
{
    double x, y, z;

    double dot(vec3d other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
};
