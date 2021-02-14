#pragma once

#include "Object.h"
#include "draw/render/SimpleRenderable.h"

class SimpleObject : public Object, private SimpleRenderable
{
private:
    typedef SimpleRenderable renderer;

protected:
    SimpleObject() {}
    virtual ~SimpleObject() {}

    ShaderType mShaderType() override { return ShaderType::Simple; };
    void bindShader(Shader *shader) const override { shader->setMat4(GLSLI::VMODEL, model); }
    void bindAttrib() const override { renderer::bindAttrib(); }
    void unbindAttrib() const override { renderer::unbindAttrib(); }
    void createAttrib() override { renderer::createAttrib(); }
};