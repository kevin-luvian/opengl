#include "Texture.h"

void Texture::loadFromFile(std::string filepath)
{
    int width, height, bitDepth;
    auto *texData = stbi_load(filepath.c_str(), &width, &height, &bitDepth, 0);

    if (!texData)
    {
        stbi_image_free(texData);
        throw std::runtime_error("failed to load file: " + filepath);
    }

    // unsigned int textureID;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
}