#pragma once

#include "object/core/Object.h"
#include "HShader.h"

class ShaderManager
{
private:
    const unsigned int shadersSize = 3;
    Shader *shaders[3] = {new SimpleShader(), new LightShader(), new TexturedShader()};
    Shader *binding;
    void clean()
    {
        for (int i = 0; i < shadersSize; i++)
        {
            delete shaders[i];
        }
        std::cout << "all shaders deleted\n";
    }

public:
    ShaderManager() {}
    ~ShaderManager() { clean(); }

    void compiles()
    {
        for (int i = 0; i < shadersSize; i++)
        {
            shaders[i]->compile();
        }
    }
    void reset()
    {
        binding = nullptr;
        for (int i = 0; i < shadersSize; i++)
        {
            shaders[i]->bind();
            shaders[i]->attachCamera();
        }
    }
    Shader *getShader(ShaderType type)
    {
        for (int i = 0; i < shadersSize; i++)
        {
            if (type == shaders[i]->getShaderType())
                return shaders[i];
        }
        return shaders[0];
    }

    Shader *bind(const ShaderType &type)
    {
        if (binding == nullptr || binding->getShaderType() != type)
        {
            binding = getShader(type);
            binding->bind();
        }
        return binding;
    }
};