#pragma once

#include "core/Shader.h"

class SimpleShader : public Shader
{
private:
    typedef Shader instanced;

public:
    SimpleShader() {}
    ~SimpleShader() {}
    ShaderType mShaderType() { return ShaderType::Simple; }
    void compile() override
    {
        instanced::compile();
        compileFromFile("../res/shader/vSimple.vert", "../res/shader/fSimple.frag");
    }
};