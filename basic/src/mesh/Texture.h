#pragma once

#include <stb/stb_image.h>

class Texture
{
public:
    unsigned int id;
    std::string type;
    std::string path;

    void loadFromFile(std::string filepath);
};