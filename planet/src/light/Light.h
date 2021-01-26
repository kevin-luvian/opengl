#pragma once

#include "render/Shader.h"

class Light
{
private:
    glm::vec3 colour;
    float ambientIntensity;

public:
    Light()
    {
        colour = glm::vec3(0.9f, 0.9f, 0.9f);
        ambientIntensity = 1.0f;
    };
    ~Light(){};
    void use(Shader &shader)
    {
        shader.set3f("dLight.colour", colour);
        shader.set1f("dLight.intensity", ambientIntensity);
    }
};