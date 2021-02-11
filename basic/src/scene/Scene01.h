#pragma once

#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"

class Scene01 : public Scene
{
public:
    Pyramid *p = new Pyramid();
    PyramidT *pt = new PyramidT();

    Scene01() { std::cout << "creating scene01\n"; }
    ~Scene01() { delete p; }

    void onPrepare() override
    {
        addObject(p);
        addObject(pt);
    }
    void onPlay() override {}
};