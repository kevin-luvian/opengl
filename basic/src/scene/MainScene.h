#pragma once

#include "Scene.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/Sphere.h"

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

        auto sphere = new Sphere(20);
        sphere->setPosition(glm::vec3(3.0f, 0.0f, -5.0f));

        addShape(pyramid, Enum::ShaderType::Simple);
        addShape(sphere, Enum::ShaderType::Simple);
    }
    void play()
    {
        BENCHMARK_PROFILE();
        Enum::ShaderType type;
        ShaderClass *shader;
        for (int i = 0; i < Enum::ShaderType::Count; i++)
        {
            type = Enum::AllShaderType[i];
            shader = mSManager.getShader(type);
            shader->bind();
            drawShapes(type, shader);
            shader->unbind();
        }
    }
};