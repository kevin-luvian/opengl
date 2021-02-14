#pragma once

#include "glComponent/ScreenState.h"
#include "mesh/core/Mesh.h"
#include "draw/shader/core/ShaderType.h"

class Renderable
{
public:
    void render() const;
    void createBuffer(const Mesh &mesh);

protected:
    unsigned int VAO, VBO, IBO, ISize;
    ShaderType shaderType;

    virtual ~Renderable() {}
    Renderable() : VAO(0), VBO(0), IBO(0), ISize(0) {}
    virtual void bindAttrib() const = 0;
    virtual void unbindAttrib() const = 0;
    virtual void createAttrib() = 0;

    virtual void onRender() const;

private:
    void bind() const;
    void unbind() const;
    void clear();
};