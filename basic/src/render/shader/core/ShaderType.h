#pragma once

enum class ShaderType
{
    Simple = 0,
    Light = 1,
    Count = 2
};

static const ShaderType AllShaderType[] = {ShaderType::Simple, ShaderType::Light};