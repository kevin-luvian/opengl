#pragma once

struct Vertex
{
    glm::vec3 pos;
    glm::vec4 colour = glm::vec4(1.0, 0.0, 0.0, 1.0);
    glm::vec3 normal;

    void createColourFromPos() { colour = glm::vec4(clampPos(0.0, 1.0), 1.0) + glm::vec4(0.0, 0.4, 0.7, 0.2); }
    static unsigned long posCount() { return 3; }
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "pos(x:" << v.pos.x << ", y:" << v.pos.y << ", z:" << v.pos.z << "), "
            << "colour(r:" << v.colour.x << ", g:" << v.colour.y << ", b:" << v.colour.z << ", a:" << v.colour.w << "), "
            << "normal(x:" << v.normal.x << ", y:" << v.normal.y << ", z:" << v.normal.z << ")";
        return out;
    }
    glm::vec3 clampPos(float min, float max) const
    {
        return glm::vec3(clamp(pos.x, min, max), clamp(pos.y, min, max), clamp(pos.z, min, max));
    }
    static float clamp(float a, float &min, float &max)
    {
        if (a < min)
            return min;
        else if (a > max)
            return max;
        else
            return a;
    }
};