#pragma once

#include "object/Object.h"
#include "draw/shader/ShaderUniform.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"

class SimpleShader : public ShaderClass
{
public:
    SimpleShader() {}
    ~SimpleShader() {}
    void compile() override { compileFromFile("../res/shader/vSimple.vert", "../res/shader/fSimple.frag"); }
    void setMVP(glm::mat4 &mvp) { setMat4(ShaderUniform::VSIMPLE_MVP, mvp); }
    void attachObject(Object *object) override
    {
        BENCHMARK_PROFILE();
        auto viewProjection = Camera::ViewProjection();
        auto model = object->getModel();
        setMat4(ShaderUniform::VSIMPLE_MVP, viewProjection * model);
    }
    void setupUniforms() override {}
};