#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidTEmpty : public TexturedObject
{
public:
    PyramidTEmpty() { std::cout << "creating PTE\n"; }
    ~PyramidTEmpty() { deleteTextures(); }
    void onCreate() override
    {
        transferMesh(MeshFactory::Pyramid());
        Texture tex = TextureFactory::Empty(Colors::OCEAN);
        tex.type = GLSLI::Texture::DIFFUSE;
        // Texture tex = TextureFactory::Empty_Texture();
        textures.append(tex);
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};