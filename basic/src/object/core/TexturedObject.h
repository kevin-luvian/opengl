#pragma once

#include "draw/render/TexturedRenderable.h"
#include "Object.h"

class TexturedObject : public Object, private TexturedRenderable
{
private:
    typedef TexturedRenderable renderer;

protected:
    TexturedObject() {}
    virtual ~TexturedObject() { texture.deleteTexture(); }

    ShaderType mShaderType() override { return ShaderType::Textured; };
    void bindShader(Shader *shader) const override
    {
        shader->setMat4(GLSLI::VMODEL, model);
        texture.bindDefault();
    };
    void bindAttrib() const override { renderer::bindAttrib(); }
    void unbindAttrib() const override { renderer::unbindAttrib(); }
    void createAttrib() override { renderer::createAttrib(); }
};