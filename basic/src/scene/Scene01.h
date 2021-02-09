#pragma once

#include "core/Scene.h"
#include "object/Pyramid.h"
#include "mesh/HMesh.h"

class Scene01 : public Scene
{
public:
    Scene01()
    {
        std::cout << "creating scene01\n";
    }
    ~Scene01() {}

    void prepare() override
    {
        Pyramid p;
        p.print();
    }
    void play() override {}
};