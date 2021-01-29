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
    PointLight *pp;
    ShapedPointLight *spl;

    MainScene() {}
    ~MainScene() {}

    Sphere *sphere;

    void setprops()
    {
        BENCHMARK_PROFILE();
        std::cout << "creating scene\n";

        sphere = new Sphere(70);
        sphere->setPosition(glm::vec3(3.0f, 0.0f, -5.0f));
        addShape(sphere, Enum::ShaderType::Light);

        auto sphere2 = new Sphere(70);
        sphere2->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
        addShape(sphere2, Enum::ShaderType::Light);

        // auto globalLight = new DirectionalLight();
        // globalLight->mDiffuseIntensity = 0.05f;
        // addGlobalLight(globalLight);

        pp = new PointLight();
        pp->setPosition(glm::vec3(-24.0, 0.0, 0.0));
        pp->mDiffuseIntensity = 1.3f;
        // addPointLight(pp);

        auto splShape = new Pyramid();
        splShape->setSize(0.2f);
        splShape->setColour(glm::vec4(1.0));
        spl = new ShapedPointLight(splShape, Enum::ShaderType::Simple);
        spl->setPosition(glm::vec3(-7.0, 0, 0));
        addShapedPointLight(spl);

        auto splShape1 = new Sphere(25);
        splShape1->setSize(0.2f);
        splShape1->setColour(glm::vec4(1));
        auto spl1 = new ShapedPointLight(splShape1, Enum::ShaderType::Simple);
        spl1->setPosition(glm::vec3(0, 7.0, 0.5));
        addShapedPointLight(spl1);
    }

    void onPrepare() {}

    float offset = 0.01f;
    float sAngle = 0.0f;

    void onPlay()
    {
        BENCHMARK_PROFILE();
        if (spl->getPosition().x > 10.0f || spl->getPosition().x < -10.0f)
            offset *= -1;
        spl->addVelocity(glm::vec3(offset, 0.0f, 0.0f));
        spl->update();

        sAngle += 0.03f;
        sphere->rotateY(sAngle);
    }
};