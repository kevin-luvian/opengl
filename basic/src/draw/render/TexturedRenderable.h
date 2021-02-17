#pragma once

#include "Renderable.h"
#include "draw/shader/core/Shader.h"
#include "mesh/core/Texture.h"
#include "TextureInterface.h"

class TexturedRenderable : public Renderable
{
private:
    typedef Renderable instanced;

protected:
    TexturedRenderable() {}
    virtual ~TexturedRenderable() {}

    void render(Shader &shader, const Array<Texture> &textures)
    {
        unsigned int index = 0;
        unsigned int diffCount = 0;
        unsigned int specCount = 0;
        for (size_t i = 0; i < textures.size; i++)
        {
            std::string texName = GLSLI::Texture::toString(textures[i].type);
            if (GLSLI::Texture::DIFFUSE == textures[i].type)
                texName += std::to_string(diffCount++);
            if (GLSLI::Texture::SPECULAR == textures[i].type)
                texName += std::to_string(specCount++);
            textures[i].bindCallback(index, [&]() { shader.set1i(texName, index); });
            index++;
        }
        bindEmptyTexture(shader, GLSLI::Texture::DIFFUSE_MAX, diffCount, index, GLSLI::Texture::DIFFUSE_BASE);
        bindEmptyTexture(shader, GLSLI::Texture::SPECULAR_MAX, specCount, index, GLSLI::Texture::SPECULAR_BASE);
        instanced::render();
    }
    void bindEmptyTexture(Shader &shader, const unsigned int &maxCount, unsigned int &typeCount, unsigned int &index, const std::string &type)
    {
        while (typeCount < maxCount)
        {
            std::string texName = type + std::to_string(typeCount++);
            TextureFactory::Empty_Texture().bindCallback(index, [&]() { shader.set1i(texName, index); });
            index++;
        }
    }
    void bindAttrib() const override
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }
    void unbindAttrib() const override
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }
    void createAttrib() override
    {
        // define vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        // define colour attributes
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // define colour attributes
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
        glEnableVertexAttribArray(2);
    }
};