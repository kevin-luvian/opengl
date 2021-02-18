#pragma once

#include "core/TexturedObject.h"
#include "mesh/factory/Pyramid.h"

class PyramidT : public TexturedObject
{
public:
    PyramidT() { transferMesh(MeshFactory::Pyramid()); }
    ~PyramidT() { deleteTextures(); }

    void onCreate() override
    {
        std::cout << "creating PT\n";
        Texture tex = TextureFactory::FromFile("../res/texture/GoldMetal.jpg");
        tex.type = GLSLI::Texture::DIFFUSE;
        textures.append(tex);
    }
    void onUpdate() override
    {
        // std::cout << texture << "\n";
    }
};