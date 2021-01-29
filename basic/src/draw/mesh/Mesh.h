#pragma once

#include "Indice.h"
#include "Vertex.h"

class Mesh
{
public:
    DetailedArray<Vertex> vertices;
    DetailedArray<Indice> indices;

    void release()
    {
        indices.release();
        vertices.release();
    }
    void createVerticesColourFromPos()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].createColourFromPos();
        }
    }
    void createUniformColours(glm::vec4 colour)
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].colour = colour;
        }
    }
    void calculateOriginNormals()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].normal = glm::normalize(vertices[i].pos);
        }
    }
    void calculateAverageNormals()
    {
        glm::vec3 vLeft, vRight, vTop, vSub1, vSub2;
        glm::vec3 vNormal;
        // calculate agregate cross product
        for (int i = 0; i < indices.size; i++)
        {
            Indice &curIndice = indices[i];
            vLeft = vertices[curIndice.left].pos;
            vRight = vertices[curIndice.right].pos;
            vTop = vertices[curIndice.top].pos;

            vSub1 = vLeft - vTop;
            vSub2 = vRight - vTop;

            vNormal = glm::normalize(glm::cross(vSub1, vSub2));

            vertices[curIndice.top].normal += vNormal;
            vertices[curIndice.left].normal += vNormal;
            vertices[curIndice.right].normal += vNormal;
        }
        // normalize all normal
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].normal = glm::normalize(vertices[i].normal);
        }
    }
};