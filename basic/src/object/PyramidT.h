#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidT : public TexturedObject
{
public:
    PyramidT()
    {
        transferMesh(MeshFactory::Pyramid());
        createVerticesColorFromPos();
        auto color = Colors::OCEAN;
        color.a = 0.0f;
        addColor(color);
    }
    ~PyramidT() {}
    void onCreate() override
    {
        std::cout << "creating PT\n";
        texture = TextureFactory::FromFile("../res/texture/GoldMetal.jpg");

        setPosition(unit::vec3(14.14f, 0, -5));
        setScale(5.0f);
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};