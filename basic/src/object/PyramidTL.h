#pragma once

#include "core/CompleteObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidTL : public CompleteObject
{
public:
    PyramidTL() { std::cout << "creating PTE\n"; }
    ~PyramidTL() { deleteTextures(); }
    void onCreate() override
    {
        transferMesh(MeshFactory::Pyramid());

        Texture tex = TextureFactory::FromFile("../res/texture/GoldMetal.jpg");
        // Texture tex = TextureFactory::Empty(Colors::OCEAN);
        tex.type = GLSLI::Texture::DIFFUSE;
        textures.append(tex);
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};