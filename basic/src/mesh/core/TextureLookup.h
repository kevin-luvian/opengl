#pragma once

#include <unordered_map>
#include "Texture.h"

class TextureLookup
{
private:
    std::unordered_map<std::string, Texture> lookup;
    Texture *find(std::string path)
    {
        std::unordered_map<std::string, Texture>::iterator it;
        it = lookup.find(path);
        if (it != lookup.end())
            return &it->second;
        return nullptr;
    }

public:
    TextureLookup() {}
    ~TextureLookup() { clean(); }

    void clean()
    {
        std::unordered_map<std::string, Texture>::iterator it;
        for (it = lookup.begin(); it != lookup.end(); it++)
        {
            it->second.deleteTexture();
        }
    }
    void append(const Texture &texture)
    {
        lookup.insert(std::make_pair(texture.path, texture));
    }
    Texture texture(const std::string &path, const unsigned int &type = GLSLI::Texture::DIFFUSE, const bool &flipTexture = false)
    {
        Texture *it = find(path);
        if (it != nullptr)
            return *it;

        Texture tex = TextureFactory::FromFile(path, flipTexture);
        tex.type = type;
        append(tex);
        return tex;
    }
    Texture empty(const unit::color &col, const unsigned int &type)
    {
        Texture *tex = find(col.hash());
        if (tex != nullptr)
            return *tex;

        Texture emptyTex = TextureFactory::Empty(col);
        emptyTex.type = type;
        append(emptyTex);
        return emptyTex;
    }
};