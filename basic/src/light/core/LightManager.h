#pragma once

#include "draw/shader/core/Shader.h"
#include "util/MArray.h"
#include "../DirectionalLight.h"
#include "../PointLight.h"
#include "../SpotLight.h"

class LightManager
{
private:
    std::vector<PointLight *> pointlights;
    std::vector<SpotLight *> spotlights;
    DirectionalLight *directionallight;

public:
    LightManager() { directionallight = nullptr; }
    ~LightManager() {}

    void insert(DirectionalLight *light) { directionallight = light; }
    void insert(PointLight *light) { pointlights.push_back(light); }
    void insert(SpotLight *light) { spotlights.push_back(light); }
    void update()
    {
        for (PointLight *light : pointlights)
        {
            light->update();
        }
        for (SpotLight *light : spotlights)
        {
            light->update();
        }
    }
    void render(Shader &shader)
    {
        sort();
        renderDirectionalLight(shader);
        renderPointLights(shader);
        renderSpotLights(shader);
    }

private:
    void sort()
    {
        std::sort(pointlights.begin(), pointlights.end(), PointLight::DistanceComparer);
        std::sort(spotlights.begin(), spotlights.end(), PointLight::DistanceComparer);
    }
    void renderSpotLights(Shader &shader)
    {
        size_t size = std::min(GLSLI::SpotLight::MAX, spotlights.size());
        shader.set1i(GLSLI::SpotLight::COUNT, size);
        for (size_t i = 0; i < size; i++)
        {
            spotlights[i]->bind(shader, i);
        }
    }
    void renderPointLights(Shader &shader)
    {
        size_t size = std::min(GLSLI::PointLight::MAX, pointlights.size());
        shader.set1i(GLSLI::PointLight::COUNT, size);
        for (size_t i = 0; i < size; i++)
        {
            pointlights[i]->bind(shader, i);
        }
    }
    void renderDirectionalLight(Shader &shader)
    {
        if (directionallight != nullptr)
            directionallight->bind(shader);
    }
};