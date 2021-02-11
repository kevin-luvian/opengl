#pragma once

#include <algorithm>
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
    }
    void play()
    {
        sManager.reset();
        Shader *shader;
        for (Object *obj : objects)
        {
            obj->update();
        }
        onPlay();
        for (Object *obj : objects)
        {
            shader = sManager.bind(obj->getShaderType());
            obj->render(shader);
        }
    }

protected:
    ShaderManager sManager;
    std::vector<Object *> objects; // vector handles heap. is safe.

    Scene() { std::cout << "creating Scene\n"; }
    virtual ~Scene() {}

    virtual void onPrepare() = 0;
    virtual void onPlay() = 0;

    void addObject(Object *obj) { objects.push_back(obj); }
    void sortObjectsByShaderType()
    {
        std::sort(objects.begin(), objects.end(), Object::ShaderTypeComparer);
    }
};