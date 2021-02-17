#pragma once

#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"
#include "model/HModel.h"

class Scene01 : public Scene
{
public:
    std::unique_ptr<Model> trunk = std::make_unique<Model>("../res/model/wood/trunk wood.obj");
    std::unique_ptr<Model> backpack = std::make_unique<Model>("../res/model/backpack/backpack.obj", true);
    std::unique_ptr<Model> backpack1 = std::make_unique<Model>("../res/model/backpack/backpack.obj", true);

    Scene01() { std::cout << "creating scene01\n"; }
    ~Scene01() {}

    void onPrepare() override
    {
        addModel(trunk);
        addModel(backpack);
        // addModel(backpack1);

        trunk->setPosition({0, 0, -10});
        backpack1->setPosition({-5, 0, -5});
    }
    float rotation = 0.0f;
    void onPlay() override
    {
        rotation += 0.5f;
        backpack->rotateY(rotation);
        trunk->rotateZ(rotation);
    }
};