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
        Shader *shader;
        for (Object *obj : objects)
        {
            obj->update();
        }
        for (Model *model : models)
        {
            model->update();
        }

        onPlay();

        for (Object *obj : objects)
        {
            shader = sManager.bind(obj->getShaderType());
            obj->render(shader);
        }
        shader = sManager.bind(Model::getShaderType());
        for (Model *model : models)
        {
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
    void addObject(Object *obj) { objects.push_back(obj); }
    void sortObjectsByShaderType()
    {
        std::sort(objects.begin(), objects.end(), Object::ShaderTypeComparer);
    }
};