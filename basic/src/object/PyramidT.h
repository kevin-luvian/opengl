#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidT : public TexturedObject
{
public:
    PyramidT() {}
    ~PyramidT() {}
    void onCreate() override
    {
        useMesh(MeshFactory::Pyramid());
        createVerticesColorFromPos();
        auto color = Colors::OCEAN;
        color.a = 0.0f;
        addColor(color);
        texture = TextureFactory::Mirrored("../res/texture/GoldMetal.jpg");

        // printVertices();

        pos = unit::vec3(3, 0, -5);
        scale = 5.0f;
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};