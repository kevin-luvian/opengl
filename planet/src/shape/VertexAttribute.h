#pragma once

#include "unit/vec3d.h"
#include "unit/vec4d.h"

struct VertexAttribute
{
    vec4d color;
    vec3d normal;
    
    friend std::ostream &operator<<(std::ostream &out, const VertexAttribute &v)
    {
        out << "VertexAttribute("
            << " color[x:" << v.color.x << ", y:" << v.color.y << ", z:" << v.color.z << ", w:" << v.color.w << "]"
            << " normal[x:" << v.normal.x << ", y:" << v.normal.y << ", z:" << v.normal.z << "]"
            << " )";
        return out;
    }
};