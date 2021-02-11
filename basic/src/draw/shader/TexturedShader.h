#pragma once

#include "core/Shader.h"

class TexturedShader : public Shader
{
private:
    typedef Shader instanced;

public:
    TexturedShader() {}
    ~TexturedShader() {}
    ShaderType mShaderType() { return ShaderType::Textured; }
    void compile() override
    {
        instanced::compile();
        compileFromFile("../res/shader/vTextured.vert", "../res/shader/fTextured.frag");
    }
};