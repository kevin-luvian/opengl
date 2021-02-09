#pragma once

#include "Indice.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh
{
public:
    Array<Vertex> vertices;
    Array<Indice> indices;
    Texture texture;

    Mesh()
    {
        std::cout << "creating mesh\n";
    }
    Mesh(const Mesh &obj)
    {
        vertices = obj.vertices;
        indices = obj.indices;
        texture = obj.texture;
    }
    virtual ~Mesh() {}
    void transfer(Mesh obj)
    {
        vertices.transfer(obj.vertices);
        indices.transfer(obj.indices);
        texture = std::move(obj.texture);
    }
    void createVerticesColourFromPos()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].createColourFromPos();
        }
    }
    void createUniformColours(unit::color color)
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].color = color;
        }
    }
    void calculateOriginNormals()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].normal = unit::normalize(vertices[i].pos);
        }
    }
    void calculateAverageNormals()
    {
        unit::vec3 vLeft, vRight, vTop, vSub1, vSub2, vNormal;
        // calculate agregate normalized cross product
        for (int i = 0; i < indices.size; i++)
        {
            Indice &curIndice = indices[i];
            vLeft = vertices[curIndice.left].pos;
            vRight = vertices[curIndice.right].pos;
            vTop = vertices[curIndice.top].pos;

            vSub1 = vLeft - vTop;
            vSub2 = vRight - vTop;

            vNormal = unit::normalize(unit::cross(vSub1, vSub2));

            vertices[curIndice.top].normal += vNormal;
            vertices[curIndice.left].normal += vNormal;
            vertices[curIndice.right].normal += vNormal;
        }
        // normalize all aggregate normal
        for (int i = 0; i < vertices.size; i++)
        {
            vertices[i].normal.normalize();
        }
    }
};