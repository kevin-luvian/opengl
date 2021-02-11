#pragma once

#include "Object.h"

class SimpleObject : public Object
{
protected:
    SimpleObject() {}
    virtual ~SimpleObject() {}

    ShaderType mShaderType() override { return ShaderType::Simple; };
    void bindShader(Shader *shader) const override { shader->setMat4(GLSLI::VMODEL, model); }
    void bindAttrib() const override
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    void unbindAttrib() const override
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    void createAttrib() override
    {
        // define vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        // define colour attributes
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
    }
};