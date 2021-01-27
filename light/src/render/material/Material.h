#pragma once

#include "glcomponent/Camera.h"
#include "render/Shader.h"

class Material
{
public:
    Material() {}
    ~Material() {}

    void useBind(Shader &shader)
    {
        shader.bind();
        use(shader);
        shader.unbind();
    }

    void use(Shader &shader)
    {
        shader.set1f("material.shininess", mShine);
        shader.set1f("material.specularIntensity", mSpecularIntensity);
        shader.set3f("cameraPosition", Camera::GET().getPosition());
    }

    void setShine(float shine) { mShine = shine; }
    void setSpecularIntensity(float intensity) { mSpecularIntensity = intensity; }

private:
    float mSpecularIntensity = 0.3f;
    float mShine = 4.0f;
};