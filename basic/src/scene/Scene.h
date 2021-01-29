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
#include "light/impl/PointLight.h"
#include "light/impl/ShapedPointLight.h"

class Scene
{
private:
    struct shape_pair
    {
        ShapeClass *shape;
        Enum::ShaderType type;
    };

protected:
    ShaderManager mSManager;
    std::vector<shape_pair> shapePair;
    std::unique_ptr<DirectionalLight> globalLight;
    std::vector<PointLight *> pointLights;

public:
    Scene() {}
    virtual ~Scene() {}

    virtual void setprops() = 0;
    virtual void onPrepare() = 0;
    virtual void onPlay() = 0;
    void prepare()
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
            mSManager.getLightShader()->attachDirectionalLight(globalLight.get());
        else
            globalLight = mSManager.getLightShader()->attachEmptyDirectionalLight();
        updatePointLights();
        onPrepare();
    }
    void play()
    {
        BENCHMARK_PROFILE();
        updatePointLights();

        Enum::ShaderType type;
        ShaderClass *shader;
        int size = static_cast<int>(Enum::ShaderType::Count);
        for (int i = 0; i < size; i++)
        {
            type = Enum::AllShaderType[i];
            shader = mSManager.getShader(type);
            shader->bind();
            drawShapes(type, shader);
            shader->unbind();
        }

        onPlay();
    }
    void updatePointLights()
    {
        if (pointLights.size() > 0)
        {
            sortNearestPointLight();
            mSManager.getLightShader()->attachPointLights(pointLights);
        }
    }

    void addShape(ShapeClass *shape, Enum::ShaderType sType)
    {
        shape->attachRenderer(RendererManager::CreateRendererFromShaderType(sType));
        shapePair.push_back({shape, sType});
    }
    void addGlobalLight(DirectionalLight *light) { globalLight = std::unique_ptr<DirectionalLight>(light); }
    void addPointLight(PointLight *light) { pointLights.push_back(light); }
    void addShapedPointLight(ShapedPointLight *light)
    {
        auto renderer = RendererManager::CreateRendererFromShaderType(light->getShaderType());
        light->getShape()->attachRenderer(renderer);
        shapePair.push_back({light->getShape(), light->getShaderType()});
        pointLights.push_back(light);
    }

    void sortNearestPointLight()
    {
        BENCHMARK_PROFILE();
        auto cmp = [](PointLight const *a, PointLight const *b) {
            return a->getManhattanDistanceToCamera() < b->getManhattanDistanceToCamera();
        };
        std::sort(pointLights.begin(), pointLights.end(), cmp);
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
            curShaderType = shapePair[++shape_itr].type;
        }

        // iterate through shader block
        ShapeClass *curShape;
        while (shape_itr < shapePair.size() && curShaderType == type)
        {
            curShape = shapePair[shape_itr].shape;
            curShape->update();
            shader->attachShape(curShape);
            curShape->render();
            curShaderType = shapePair[++shape_itr].type;
        }
    }
};