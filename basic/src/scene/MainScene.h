#pragma once

#include "Scene.h"
#include "object/Colors.h"
#include "object/Objects.h"
#include "draw/shader/Shaders.h"
#include "light/Lights.h"

#include "model/Model.h"
#include "draw/renderer/impl/ModelRenderer.h"

class MainScene : public Scene
{
private:
    typedef Scene inherited;

public:
    DynamicSphere *dSphere;
    ObjectPointLight *spl;

    MainScene() {}
    ~MainScene() {}

    void setprops() override
    {
        BENCHMARK_PROFILE();
        auto globalLight = new DirectionalLight();
        globalLight->setDirection(glm::vec3(0, -1.0, -1.0));
        globalLight->setDiffuseIntensity(0.0f);
        globalLight->setAmbientIntensity(1.0f);
        addGlobalLight(globalLight);

        auto sheet = new ShadedSheet(70, 70);
        sheet->setPosition(glm::vec3(0, -3.0f, 0));
        sheet->setSize(50.0f);
        addObject(sheet);

        dSphere = new DynamicSphere(50);
        dSphere->setColour(Color::ORANGE);
        dSphere->setPosition(glm::vec3(-10, -1.0, 10));
        dSphere->changeShaderType(Enum::ShaderType::Light);
        dSphere->getMaterial().mShine = 0.0f;
        dSphere->getMaterial().mSpecularIntensity = 0.0f;
        addObject(dSphere);

        auto sp = new ShadedPyramid();
        sp->setColour(Color::SAPPHIRE);
        sp->setPosition(glm::vec3(-5.0, 0.0, -5.0));
        sp->changeShaderType(Enum::ShaderType::Light);
        addObject(sp);
    }

    void onPrepare() override {}

    float sAngle = 0.0f;

    void onPlay() override
    {
        BENCHMARK_PROFILE();
        dSphere->rotateX(sAngle);
        if (sAngle > 360.0f)
            sAngle = 0.0f;
        sAngle += 0.5f;
    }
};