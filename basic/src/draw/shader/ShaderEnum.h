#pragma once

namespace Enum
{
    enum class ShaderType
    {
        Simple = 0,
        Light = 1,
        Count = 2
    };

    static const ShaderType AllShaderType[] = {Enum::ShaderType::Simple, Enum::ShaderType::Light};
} // namespace Enum