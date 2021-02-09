#pragma once

struct Vertex
{
    unit::vec3 pos;
    unit::color color = Colors::WHITE;
    unit::vec3 normal;
    unit::vec2 texCoord = unit::vec2(0.0f);

    void createColourFromPos()
    {
        color = unit::clamp(unit::color(pos.x, pos.y, pos.z, 1.0f));
    }
};