#pragma once

#include <stb/stb_image.h>

struct Texture
{
    unsigned int id;
    std::string type;

    ~Texture() { clear(); }
    void bindDefault() const
    {
        bind(0);
    }
    void bind(unsigned int texOffset) const
    {
        glActiveTexture(GL_TEXTURE0 + texOffset);
        glBindTexture(GL_TEXTURE_2D, id);
    }
    void clear()
    {
        glDeleteTextures(1, &id);
        id = 0;
        type.clear();
    }
    friend std::ostream &operator<<(std::ostream &out, const Texture &o)
    {
        out << "id:" << o.id << ", type:" << o.type;
        return out;
    }
};

namespace TextureFactory
{
    static Texture Mirrored(const std::string &path)
    {
        Texture texture;
        int width, height, bitDepth;
        auto *texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
        std::cout << "load file: " << path << std::endl;
        if (!texData)
            std::cout << "failed to load file: " << path << std::endl;

        std::cout << texData << "\n";

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(texData);
        std::cout << "texId:: " << texture.id << "\n";
        return texture;
    }
}; // namespace TextureFactory