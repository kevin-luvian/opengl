#pragma once

#include "shape/ShapeClass.h"
#include "draw/shader/ShaderUniform.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"

class SimpleShader : public ShaderClass
{
public:
    SimpleShader() {}
    ~SimpleShader() {}
    void compile() { compileFromFile("../res/shader/vSimple.vert", "../res/shader/fSimple.frag"); }
    void setMVP(glm::mat4 &mvp) { setMat4(ShaderUniform::VSIMPLE_MVP, mvp); }
    void attachShape(ShapeClass *shape)
    {
        auto viewProjection = Camera::ViewProjection();
        auto model = shape->getModel();
        setMat4(ShaderUniform::VSIMPLE_MVP, viewProjection * model);
    }
};