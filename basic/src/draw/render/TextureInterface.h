#pragma once

#include "mesh/core/Texture.h"
#include "draw/shader/core/Shader.h"

class TextureInterface
{
private:
    Array<Texture> diffuses;
    Array<Texture> speculars;
    size_t diffCounter;
    size_t specCounter;

    void appendDiffuse(const Texture &tex)
    {
        diffuses[diffCounter++] = tex;
    }

    void appendSpecular(const Texture &tex)
    {
        speculars[specCounter++] = tex;
    }

    size_t texSize() const { return diffuses.size + speculars.size; }

public:
    TextureInterface()
    {
        diffuses.make_fill(GLSLI::Texture::DIFFUSE_MAX, TextureFactory::Empty_Texture());
        speculars.make_fill(GLSLI::Texture::SPECULAR_MAX, TextureFactory::Empty_Texture());
        diffCounter = 0;
        specCounter = 0;
    }
    ~TextureInterface() {}

    void append(const Texture &tex)
    {
        if (GLSLI::Texture::DIFFUSE == tex.type)
            appendDiffuse(tex);
        else if (GLSLI::Texture::SPECULAR == tex.type)
            appendSpecular(tex);
    }
    void render(Shader &shader) const
    {
        unsigned int texCounter = 0;
        for (size_t i = 0; i < diffuses.size; i++)
        {
            std::string texName = GLSLI::Texture::DIFFUSE_INDEX(i);
            diffuses[i].bindCallback(texCounter, [&]() { shader.set1i(texName, texCounter); });
            texCounter++;
        }
        for (size_t i = 0; i < speculars.size; i++)
        {
            std::string texName = GLSLI::Texture::SPECULAR_INDEX(i);
            speculars[i].bindCallback(texCounter, [&]() { shader.set1i(texName, texCounter); });
            texCounter++;
        }
    }
};