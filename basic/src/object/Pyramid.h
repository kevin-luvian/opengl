#pragma once

#include "Object.h"
#include "mesh/factory/Pyramid.h"

class Pyramid : public Object
{
public:
    Pyramid()
    {
        useMesh(MeshFactory::Pyramid());
        std::cout << "creating pyramid\n";
    }
    ~Pyramid() {}

    void print()
    {
        std::cout << "wassup\n";
    }

    void create() override {}
    void update() override {}
    void draw() override {}
};