#pragma once

class Shader
{
public:
    virtual ~Shader() {}

protected:
    Shader()
    {
        std::cout << "creating Shader\n";
    }
};