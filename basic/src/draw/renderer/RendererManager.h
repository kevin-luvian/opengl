#pragma once

#include "draw/shader/ShaderEnum.h"
#include "impl/SimpleRenderer.h"
#include "impl/LightRenderer.h"
#include "Renderer.h"

namespace Enum
{
    enum class RendererType
    {
        Simple = 0,
        Light = 1,
        Count = 2
    };

    static const RendererType AllRendererType[] = {Enum::RendererType::Simple, Enum::RendererType::Light};
} // namespace Enum

class RendererManager
{
public:
    // returns raw pointer of new Renderer. be careful for memmory leaks
    static Renderer *CreateRendererFromType(Enum::RendererType type)
    {
        BENCHMARK_PROFILE();
        if (type == Enum::RendererType::Simple)
            return (Renderer *)new SimpleRenderer();
        if (type == Enum::RendererType::Light)
            return (Renderer *)new LightRenderer();
        return nullptr;
    }

    static Renderer *CreateRendererFromShaderType(Enum::ShaderType type)
    {
        BENCHMARK_PROFILE();
        if (type == Enum::ShaderType::Simple)
            return CreateRendererFromType(Enum::RendererType::Simple);
        if (type == Enum::ShaderType::Light)
            return CreateRendererFromType(Enum::RendererType::Light);
        return nullptr;
    }
};