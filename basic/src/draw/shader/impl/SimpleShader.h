#pragma once

#include "draw/shader/ShaderInterface.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"

class SimpleShader : public ShaderClass
{
private:
    const char *vShaderPath = "../res/shader/vSimple.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";

public:
    SimpleShader() {}
    ~SimpleShader() {}
    void compile() { compileFromFile(vShaderPath, fShaderPath); }
    void setMVP(glm::mat4 &mvp) { setMat4(ShaderInterface::VSIMPLE_MVP, mvp); }
    void attachShape(ShapeClass *shape)
    {
        auto viewProjection = Camera::GET().getViewProjection();
        auto model = shape->getModel();
        setMat4(ShaderInterface::VSIMPLE_MVP, viewProjection * model);
    }
};