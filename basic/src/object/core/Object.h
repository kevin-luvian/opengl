#pragma once

#include "glComponent/ScreenState.h"
#include "draw/shader/core/Shader.h"
#include "draw/shader/core/ShaderType.h"
#include "draw/render/Renderable.h"
#include "mesh/core/Mesh.h"

class Object : public Renderable, public Mesh
{
private:
    typedef Renderable renderable;

public:
    glm::mat4 model;
    unit::vec3 pos;
    float scale;

    void create()
    {
        pos = unit::vec3(0.0f);
        scale = 1.0f;
        shaderType = mShaderType();
        onCreate();
        update();
        createBuffer(*this);
    };
    void update()
    {
        model = glm::translate(glm::mat4(1), pos.toGLMVec3());
        model = glm::scale(model, glm::vec3(scale, scale, scale));
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
    virtual void bindShader(Shader *shader) const { shader->setMat4(GLSLI::VMODEL, model); };

public:
    static bool ShaderTypeComparer(const Object *a, const Object *b)
    {
        return a->getShaderType() < b->getShaderType();
    }
};