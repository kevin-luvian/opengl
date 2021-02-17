#pragma once

struct Vertex
{
    unit::vec3 pos = unit::vec3(0.0f);
    unit::vec2 texCoord = unit::vec2(0.0f);
    unit::color color = Colors::WHITE;
    unit::vec3 normal = unit::vec3(0.0f);

    void createColorFromPos()
    {
        color = unit::clamp({pos.x, pos.y, pos.z, 1.0f});
    }

    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "pos(" << v.pos << "), "
            << "colour(" << v.color << "), "
            << "normal(" << v.normal << "), "
            << "texCoord(" << v.texCoord << ")";
        return out;
    }
};