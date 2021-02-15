#pragma once

#include "glComponent/ScreenState.h"
#include "draw/entity/Movable.h"
#include "draw/shader/core/Shader.h"
#include "draw/shader/core/ShaderType.h"
#include "draw/render/Renderable.h"
#include "mesh/core/Mesh.h"

class Object : public Renderable, public Mesh, public Movable
{
private:
    typedef Renderable renderable;
    typedef Movable movable;

public:
    void create()
    {
        shaderType = mShaderType();
        onCreate();
        update();
        createBuffer(*this);
    };
    void update()
    {
        movable::move();
        onUpdate();
    }
    ShaderType getShaderType() const { return shaderType; }
    void render(Shader *shader) const
    {
        bindShader(shader);
        renderable::render();
    }

protected:
    ShaderType shaderType;

    Object() {}
    virtual ~Object() {}

    virtual ShaderType mShaderType() = 0;
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void bindShader(Shader *shader) const = 0;

public:
    static bool ShaderTypeComparer(const Object *a, const Object *b)
    {
        return a->getShaderType() < b->getShaderType();
    }
};