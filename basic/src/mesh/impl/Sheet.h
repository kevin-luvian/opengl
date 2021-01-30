#pragma once

#include "mesh/Mesh.h"

class Sheet : public Mesh
{
private:
    unsigned int width, height;

public:
    Sheet() : Sheet(30, 30) {}
    Sheet(unsigned int width_, unsigned int height_)
    {
        width = width_;
        height = height_;
    }
    ~Sheet() {}
    void createMesh() override
    {
        vertices.make_empty(width * height);
        indices.make_empty((width - 1) * (height - 1) * 2);
        unsigned int vOffset = 0, iOffset = 0;
        float xVal, zVal;
        unsigned int vIndex;
        for (size_t z = 0; z < height; z++)
        {
            for (size_t x = 0; x < width; x++)
            {
                // vertices
                float xVal = util::mapBetweenFloat(x, 0, width - 1, -1, 1);
                float zVal = util::mapBetweenFloat(z, 0, height - 1, 1, -1);
                vertices[vOffset++].pos = glm::vec3(xVal, 0, zVal);
                if (x < width - 1 && z < height - 1)
                {
                    vIndex = x + z * width;
                    indices[iOffset++] = {vIndex, vIndex + 1, vIndex + width};
                    indices[iOffset++] = {vIndex + width, vIndex + 1, vIndex + width + 1};
                }
            }
        }
    }
};