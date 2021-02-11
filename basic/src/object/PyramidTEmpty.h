#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidTEmpty : public TexturedObject
{
public:
    PyramidTEmpty() {}
    ~PyramidTEmpty() {}
    void onCreate() override
    {
        std::cout << "creating PT\n";
        transferMesh(MeshFactory::Pyramid());
        createVerticesColorFromPos();
        auto color = Colors::OCEAN;
        color.a = 0.0f;
        addColor(color);
        // texture = TextureFactory::Mirrored("../res/texture/GoldMetal.jpg");

        // printVertices();

        pos = unit::vec3(14.14f, 0, -5);
        scale = 5.0f;
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};