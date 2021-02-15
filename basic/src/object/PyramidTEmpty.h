#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidTEmpty : public TexturedObject
{
public:
    PyramidTEmpty() { std::cout << "creating PTE\n"; }
    ~PyramidTEmpty() {}
    void onCreate() override
    {
        transferMesh(MeshFactory::Pyramid());
        texture = TextureFactory::Empty();

        setPosition(unit::vec3(-14.14f, 0, -5));
        setScale(5.0f);
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};