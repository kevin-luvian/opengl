#pragma once

#include "Object.h"
#include "draw/render/CompleteRenderable.h"

class CompleteObject : public Object, private CompleteRenderable
{
private:
    typedef CompleteRenderable renderer;

protected:
    CompleteObject() {}
    virtual ~CompleteObject() {}

    ShaderType mShaderType() override { return ShaderType::Light; };
    void bindShader(Shader *shader) const override
    {
        shader->setMat4(GLSLI::VMODEL, model);
        renderer::render(*shader, textures);
    };
    void bindAttrib() const override { renderer::bindAttrib(); }
    void unbindAttrib() const override { renderer::unbindAttrib(); }
    void createAttrib() override { renderer::createAttrib(); }
};