#pragma once

#include <stb/stb_image.h>

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;

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
        id = 0;
        type.clear();
    }
    void deleteTexture()
    {
        if (id != 0)
        {
            glDeleteTextures(1, &id);
            std::cout << "GLTexture id:" << id << " [deleted]\n";
        }
        clear();
    }
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
        int size() const { return width * height * 4; }
    };
    static void GenerateTexture(unsigned int &id, texdata &tData)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tData.width, tData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tData.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    static Texture FromFile(const std::string &path)
    {
        Texture texture;
        texture.path = path;

        texdata tData;
        int bitDepth;
        tData.data = stbi_load(path.c_str(), &tData.width, &tData.height, &bitDepth, 0);
        // std::cout << "load file: " << path
        //           << "\n width: " << width
        //           << "\n height: " << height
        //           << std::endl;
        if (!tData.data)
            std::cout << "failed to load file: " << path << std::endl;
        GenerateTexture(texture.id, tData);
        return texture;
    }

    static Texture Empty()
    {
        Texture texture;
        texture.path = "";

        texdata tData;
        tData.height = 2;
        tData.width = 2;
        tData.data = new unsigned char[tData.size()];
        for (int i = 0; i < tData.size(); i++)
        {
            tData.data[i] = 255;
        }
        GenerateTexture(texture.id, tData);
        return texture;
    }
}; // namespace TextureFactory