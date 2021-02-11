#pragma once

#include "core/Shader.h"

class LightShader : public Shader
{
private:
    typedef Shader instanced;

public:
    LightShader() {}
    ~LightShader() {}
    ShaderType mShaderType() { return ShaderType::Light; }
    void compile() override
    {
        compileFromFile("../res/shader/vLight.vert", "../res/shader/fLight.frag");
        instanced::compile();
    }
    void attachCamera() override
    {
        setMat4(GLSLI::VVIEW, Camera::View());
        setMat4(GLSLI::VPROJECTION, Camera::Projection());
    }
};