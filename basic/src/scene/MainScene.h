#pragma once

#include "Scene.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/Sphere.h"
#include "draw/shader/impl/LightShader.h"
#include "light/impl/DirectionalLight.h"

class MainScene : public Scene
{
private:
    typedef Scene inherited;

public:
    MainScene() {}
    ~MainScene() {}

    void setprops()
    {
        BENCHMARK_PROFILE();
        std::cout << "creating scene\n";
        auto pyramid = new Pyramid();
        pyramid->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
        addShape(pyramid, Enum::ShaderType::Light);
        for (int i = 0; i < 10; i++)
        {
            auto sphere = new Sphere(70);
            sphere->setPosition(glm::vec3(3.0f + i * 2.0f, 0.0f, -5.0f + i * -2.0f));
            if (i == 0)
            {
                sphere->getMaterial().mSpecularIntensity = 8.0f;
                sphere->getMaterial().mShine = 32.0f;
            }
            if (i < 5)
                addShape(sphere, Enum::ShaderType::Light);
            else
                addShape(sphere, Enum::ShaderType::Simple);
        }

        DirectionalLight *dirLight = new DirectionalLight();
        addGlobalLight(*dirLight);
    }
    void play()
    {
        BENCHMARK_PROFILE();
        Enum::ShaderType type;
        int size = static_cast<int>(Enum::ShaderType::Count);
        for (int i = 0; i < size; i++)
        {
            type = Enum::AllShaderType[i];
            ShaderClass *shader = mSManager.getShader(type);
            shader->bind();
            drawShapes(type, shader);
            shader->unbind();
        }
    }
};