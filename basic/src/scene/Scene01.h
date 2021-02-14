#pragma once

#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"
#include "model/HModel.h"

class Scene01 : public Scene
{
public:
    Pyramid *p = new Pyramid();
    PyramidT *pt = new PyramidT();
    PyramidTEmpty *pte = new PyramidTEmpty();
    Model *car = new Model("../res/model/low_poly_car/CAR.blend");

    Scene01() { std::cout << "creating scene01\n"; }
    ~Scene01() { delete p; }

    void onPrepare() override
    {
        addObject(p);
        addObject(pt);
        addObject(pte);
        addModel(car);
        car->setPosition({0, 10, -5});
    }
    float rotation = 0.0f;
    void onPlay() override
    {
        rotation += 0.5f;
        p->rotateX(-rotation);
        pt->rotateX(rotation);
        pte->rotateX(rotation);
    }
};