#pragma once

#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"
#include "model/HModel.h"

class Scene01 : public Scene
{
public:
    Pyramid *p = new Pyramid();
    std::unique_ptr<PyramidT> pt = std::make_unique<PyramidT>();
    std::unique_ptr<PyramidTEmpty> pte = std::make_unique<PyramidTEmpty>();
    std::unique_ptr<Model> wood = std::make_unique<Model>("../res/model/wood/trunk wood.obj");
    // std::unique_ptr<Model> alien = std::make_unique<Model>("../res/model/cottage/cottage_obj.obj");

    Scene01() { std::cout << "creating scene01\n"; }
    ~Scene01() { delete p; }

    void onPrepare() override
    {
        addObject(p);
        addObject(pt.get());
        addObject(pte.get());
        addModel(wood.get());
        // addModel(alien.get());
        // alien->setPosition({7, 10, -5});
        // alien->setScale(0.3f);
        wood->setPosition({0, 10, -5});
        wood->setScale(8.0f);
    }
    float rotation = 0.0f;
    void onPlay() override
    {
        rotation += 0.5f;
        p->rotateY(-rotation);
        pt->rotateY(rotation);
        pte->rotateY(rotation);
        wood->rotateZ(rotation);
    }
};