#pragma once

#include "light/HLight.h"
#include "core/Scene.h"
#include "object/HObject.h"
#include "mesh/HMesh.h"
#include "model/HModel.h"

class Scene02 : public Scene
{
public:
    std::unique_ptr<DirectionalLight> dir = std::make_unique<DirectionalLight>();
    std::unique_ptr<PyramidTL> ptl = std::make_unique<PyramidTL>();
    std::unique_ptr<Model> backpack = std::make_unique<Model>("../res/model/backpack/backpack.obj", true);
    Array<Model> backpacks;

    Scene02() { std::cout << "creating scene02\n"; }
    ~Scene02() {}

    void onPrepare() override
    {
        addObject(ptl.get());
        addLight(dir.get());

        dir->setDiffuseIntensity(2.0f);

        backpacks.make_fill(5, *backpack.get());
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
        ptl->rotateY(rotation);

        for (size_t i = 0; i < backpacks.size; i++)
        {
            if ((i + 1) % 2 == 0)
                backpacks[i].rotateY(rotation);
            else
                backpacks[i].rotateY(-rotation);
        }
    }
};