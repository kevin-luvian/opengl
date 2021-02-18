#pragma once

#include <functional>
#include <stb/stb_image.h>

#include "draw/shader/core/Shader.h"

struct Texture
{
    unsigned int id;
    unsigned int type;
    std::string path;
    size_t ref_counter;

    Texture() : ref_counter(1) {}
    Texture(const std::string &_path) : ref_counter(1), path(_path) {}
    void bindDefault() const { bind(0); }
    void bindCallback(const unsigned int &offset, const std::function<void()> &callback) const
    {
        glActiveTexture(GL_TEXTURE0 + offset);
        callback();
        glBindTexture(GL_TEXTURE_2D, id);
    }
    void bind(unsigned int texOffset) const
    {
        glActiveTexture(GL_TEXTURE0 + texOffset);
        glBindTexture(GL_TEXTURE_2D, id);
    }
    void deleteTexture()
    {
        if (id != 0)
        {
            glDeleteTextures(1, &id);
            printDeleted();
        }
    }
    void printCreated() { std::cout << "GLTexture [" << id << "]\tcreated | path: " << path.c_str() << "\n"; }
    void printDeleted() { std::cout << "GLTexture [" << id << "]\tdeleted | path: " << path.c_str() << "\n"; }
    friend std::ostream &operator<<(std::ostream &out, const Texture &o)
    {
        out << "id:" << o.id << ", type:" << o.type;
        return out;
    }
};

namespace TextureFactory
{
    struct texdata
    {
        unsigned char *data;
        int width, height;
        ~texdata() { free(data); }
        int size() const { return width * height * 3; }
    };
    static void GenerateTexture(unsigned int &id, texdata &tData)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tData.width, tData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tData.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    static Texture FromFile(const std::string &path)
    {
        Texture texture(path);
        texdata tData;
        int bitDepth;
        tData.data = stbi_load(path.c_str(), &tData.width, &tData.height, &bitDepth, 0);
        if (!tData.data)
            std::cout << "failed to load file: " << path << std::endl;
        GenerateTexture(texture.id, tData);
        texture.printCreated();
        return texture;
    }
    static Texture FromFile(const std::string &path, const bool &flipVertical)
    {
        stbi_set_flip_vertically_on_load(flipVertical);
        Texture tex = FromFile(path);
        if (flipVertical)
            stbi_set_flip_vertically_on_load(false);
        return tex;
    }
    static Texture Empty(unit::color color)
    {
        Texture texture(color.hash());

        texdata tData;
        tData.height = 4;
        tData.width = 4;
        tData.data = new unsigned char[tData.size()];
        color *= 255;
        for (int i = 0; i < tData.size(); i += 3)
        {
            tData.data[i] = color.r;
            tData.data[i + 1] = color.g;
            tData.data[i + 2] = color.b;
        }
        GenerateTexture(texture.id, tData);
        std::cout << "Blank texture generated\n";
        texture.printCreated();
        return texture;
    }
    static Texture Empty() { return Empty(Colors::WHITE); }
    static const Texture Empty_Texture()
    {
        static const Texture texture = Empty(Colors::WHITE);
        return texture;
    }
}; // namespace TextureFactory