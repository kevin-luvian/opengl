#pragma once

struct Vertex
{
    glm::vec3 pos;
    glm::vec4 colour;

    static unsigned long posCount() { return 3; }
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "x:" << v.pos.x << ", y:" << v.pos.y << ", z:" << v.pos.z;
        return out;
    }
};