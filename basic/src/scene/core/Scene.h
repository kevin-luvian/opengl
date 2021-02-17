#pragma once

#include <algorithm>
#include "model/HModel.h"
#include "object/HObject.h"
#include "draw/shader/ShaderManager.h"

class Scene
{
public:
    void prepare()
    {
        sManager.compiles();
        onPrepare();
        sortObjectsByShaderType();
        for (Object *obj : objects)
        {
            obj->create();
        }
        for (Model *model : models)
        {
            model->create();
        }
    }
    void play()
    {
        sManager.reset();
        for (Object *obj : objects)
        {
            obj->update();
        }
        for (Model *model : models)
        {
            model->update();
        }

        onPlay();

        Shader *shader;
        for (Object *obj : objects)
        {
            shader = sManager.bind(obj->getShaderType());
            obj->render(shader);
        }
        for (Model *model : models)
        {
            shader = sManager.bind(Model::getShaderType());
            model->render(shader);
        }
    }

protected:
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
    void sortObjectsByShaderType()
    {
        std::sort(objects.begin(), objects.end(), Object::ShaderTypeComparer);
    }
};