#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <unordered_map>
#include "draw/shader/ShaderClass.h"
#include "draw/shader/ShaderManager.h"
#include "draw/renderer/RendererManager.h"
#include "object/Object.h"
#include "light/Lights.h"

class Scene
{
protected:
    ShaderManager mSManager;
    std::vector<Object *> rObjects;
    std::unique_ptr<DirectionalLight> globalLight;
    std::vector<PointLight *> pointLights;
    std::vector<SpotLight *> spotLights;

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
        for (const auto &obj : rObjects)
        {
            obj->create();
        }
        mSManager.createShaders();
        if (globalLight.get() != nullptr)
            mSManager.getLightShader()->attachDirectionalLight(globalLight.get());
        else
            globalLight = mSManager.getLightShader()->attachEmptyDirectionalLight();
        updateLocalLights();
        sortShapeShaders();
        onPrepare();
    }
    void play()
    {
        BENCHMARK_PROFILE();

        onPlay();
        updateLocalLights();

        Enum::ShaderType type;
        ShaderClass *shader;
        int size = static_cast<int>(Enum::ShaderType::Count);
        for (int i = 0; i < size; i++)
        {
            type = Enum::AllShaderType[i];
            shader = mSManager.getShader(type);
            shader->bind();
            shader->setupUniforms();
            drawObjects(type, shader);
            shader->unbind();
        }
    }
    void updateLocalLights()
    {
        // can be optimized
        if (pointLights.size() > 0)
        {
            sortNearestPointLight();
            mSManager.getLightShader()->attachPointLights(pointLights);
        }
        if (spotLights.size() > 0)
        {
            sortNearestSpotLight();
            mSManager.getLightShader()->attachSpotLights(spotLights);
        }
    }

    void addObject(Object *rObject)
    {
        // rObject->attachRenderer(RendererManager::CreateRendererFromShaderType(rObject->getShaderType()));
        rObjects.push_back(rObject);
    }
    void addGlobalLight(DirectionalLight *light) { globalLight = std::unique_ptr<DirectionalLight>(light); }
    void addPointLight(PointLight *light) { pointLights.push_back(light); }
    void addShapedPointLight(ShapedPointLight *light)
    {
        // auto renderer = RendererManager::CreateRendererFromShaderType(light->getShaderType());
        // light->getObject()->attachRenderer(renderer);
        addObject(light->getObject());
        addPointLight(light);
    }
    void addSpotLight(SpotLight *light) { spotLights.push_back(light); }

    void sortNearestSpotLight()
    {
        std::sort(spotLights.begin(), spotLights.end(), PointLight::DistanceComparer);
    }
    void sortNearestPointLight()
    {
        std::sort(pointLights.begin(), pointLights.end(), PointLight::DistanceComparer);
    }
    void sortShapeShaders()
    {
        BENCHMARK_PROFILE();
        std::sort(rObjects.begin(), rObjects.end(), Renderable::ShaderTypeComparer);
    }
    static void printObjectVector(std::vector<Object *> objects)
    {
        for (int i = 0; i < objects.size(); i++)
        {
            auto cType = objects[i]->getShaderType();
            std::cout << "idx: " << i << "type: " << static_cast<int>(cType) << "\n";
        }
    }
    void drawObjects(Enum::ShaderType type, ShaderClass *shader)
    {
        BENCHMARK_PROFILE();
        unsigned int obj_itr = 0;

        // find the start of shader block
        while (obj_itr < rObjects.size() && rObjects[obj_itr]->getShaderType() != type)
        {
            obj_itr++;
        }

        // iterate through shader block
        Object *curObj;
        while (obj_itr < rObjects.size() && rObjects[obj_itr]->getShaderType() == type)
        {
            curObj = rObjects[obj_itr++];
            curObj->update();
            shader->attachObject(curObj);
            curObj->render();
        }
    }
};