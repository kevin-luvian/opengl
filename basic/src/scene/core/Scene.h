#pragma once

#include <algorithm>
#include "model/HModel.h"
#include "object/HObject.h"
#include "light/HLight.h"
#include "light/core/LightManager.h"
#include "draw/shader/ShaderManager.h"

class Scene
{
public:
    void prepare()
    {
        sManager.compiles();
        onPrepare();
        createObjects();
        createModels();
    }
    void play()
    {
        sManager.reset();
        updateModels();

        onPlay();

        updateObjects();
        renderLights();
        renderObjects();
        renderModels();
    }

protected:
    LightManager lManager;
    ShaderManager sManager;
    std::vector<Object *> objects;
    std::vector<Model *> models;

    Scene() { std::cout << "creating Scene\n"; }
    virtual ~Scene() {}

    virtual void onPrepare() = 0;
    virtual void onPlay() = 0;

    void addModel(Model *model) { models.push_back(model); }
    void addModel(const std::unique_ptr<Model> &model) { models.push_back(model.get()); }
    void addObject(Object *obj) { objects.push_back(obj); }
    void addObject(const std::unique_ptr<Object> &obj) { objects.push_back(obj.get()); }
    void addLight(DirectionalLight *light) { lManager.insert(light); }
    void addLight(PointLight *light) { lManager.insert(light); }
    void addLight(SpotLight *light) { lManager.insert(light); }

private:
    void sortObjectsByShaderType()
    {
        std::sort(objects.begin(), objects.end(), Object::ShaderTypeComparer);
    }
    void createObjects()
    {
        sortObjectsByShaderType();
        for (Object *obj : objects)
        {
            obj->create();
        }
    }
    void createModels()
    {
        for (Model *model : models)
        {
            model->create();
        }
    }
    void updateObjects()
    {
        for (Object *obj : objects)
        {
            obj->update();
        }
    }
    void updateModels()
    {
        for (Model *model : models)
        {
            model->update();
        }
    }
    void renderObjects()
    {
        Shader *shader;
        for (Object *obj : objects)
        {
            shader = sManager.bind(obj->getShaderType());
            obj->render(shader);
        }
    }
    void renderModels()
    {
        Shader *shader;
        for (Model *model : models)
        {
            shader = sManager.bind(Model::SHADER_TYPE);
            model->render(shader);
        }
    }
    void renderLights()
    {
        Shader *shader = sManager.bind(Light::SHADER_TYPE);
        lManager.render(*shader);
    }
};