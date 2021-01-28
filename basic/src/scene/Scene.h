#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <unordered_map>
#include "draw/shader/ShaderClass.h"
#include "draw/shader/ShaderManager.h"
#include "draw/renderer/RendererManager.h"
#include "shape/ShapeClass.h"
#include "light/Light.h"
#include "light/impl/DirectionalLight.h"

class Scene
{
private:
    // TODO
    // Global light
    // point lights
    struct shape_pair
    {
        ShapeClass *shape;
        Enum::ShaderType type;
    };

public:
    ShaderManager mSManager;
    std::vector<shape_pair> shapePair;
    std::unique_ptr<DirectionalLight> globalLight;
    // std::vector<Light *> pointLights; TODO

    Scene() {}
    virtual ~Scene() {}

    virtual void setprops() = 0;
    virtual void play() = 0;
    virtual void prepare()
    {
        BENCHMARK_PROFILE();
        setprops();
        sortShapeShaders();
        for (const auto &pair : shapePair)
        {
            pair.shape->create();
        }
        mSManager.createShaders();
        if (globalLight.get() != nullptr)
            mSManager.getLightShader()->setDirectionalLightUniforms(globalLight.get());
    }
    void addShape(ShapeClass *shape, Enum::ShaderType sType)
    {
        shape->attachRenderer(RendererManager::CreateRendererFromShaderType(sType));
        shapePair.push_back({shape, sType});
    }
    void addGlobalLight(DirectionalLight &light)
    {
        globalLight = std::make_unique<DirectionalLight>(light);
    }
    void sortShapeShaders()
    {
        BENCHMARK_PROFILE();
        auto cmp = [](shape_pair const &a, shape_pair const &b) {
            return a.type < b.type;
        };
        std::sort(shapePair.begin(), shapePair.end(), cmp);
    }
    void drawShapes(Enum::ShaderType type, ShaderClass *shader)
    {
        BENCHMARK_PROFILE();
        unsigned int shape_itr = 0;

        // find the start of shader block
        Enum::ShaderType curShaderType = shapePair[shape_itr].type;
        while (shape_itr < shapePair.size() && curShaderType != type)
        {
            shape_itr++;
            curShaderType = shapePair[shape_itr].type;
        }

        // iterate through shader block
        ShapeClass *curShape;
        while (shape_itr < shapePair.size() && curShaderType == type)
        {
            curShape = shapePair[shape_itr].shape;
            curShape->update();
            shader->attachShape(curShape);
            curShape->render();
            shape_itr++;
            curShaderType = shapePair[shape_itr].type;
        }
    }
};