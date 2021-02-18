#pragma once

#include "light/HLight.h"
#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"
#include "model/HModel.h"

class Scene01 : public Scene
{
public:
    std::unique_ptr<PyramidT> pt = std::make_unique<PyramidT>();
    std::unique_ptr<PyramidTEmpty> pte = std::make_unique<PyramidTEmpty>();
    std::unique_ptr<Model> backpack = std::make_unique<Model>("../res/model/backpack/backpack.obj", true);
    Array<Model> backpacks;

    Scene01() { std::cout << "creating scene01\n"; }
    ~Scene01() {}

    void onPrepare() override
    {
        addObject(pt.get());
        addObject(pte.get());
        addModel(backpack);

        pt->setPosition({5, 0, 0});
        pte->setPosition({-5, 0, 0});

        backpacks.make_fill(10, Model("../res/model/backpack/backpack.obj", true));
        float zOffset = -5.0f;
        for (size_t i = 0; i < backpacks.size; i++)
        {
            backpacks[i].setPosition({0, 0, zOffset});
            zOffset -= 5.0f;
            addModel(&backpacks[i]);
        }
    }
    float rotation = 0.0f;
    void onPlay() override
    {
        rotation += 0.5f;
        pt->rotateY(rotation);
        pte->rotateY(-rotation);

        for (size_t i = 0; i < backpacks.size; i++)
        {
            if ((i + 1) % 2 == 0)
                backpacks[i].rotateY(rotation);
            else
                backpacks[i].rotateY(-rotation);
        }
    }
};