#pragma once

#include <functional>
#include "shape/ShapeAttribute.h"
#include "glcomponent/ScreenState.h"
#include "Shader.h"
#include "unit/vec4d.h"

// Holds attributes and ID for vertex and vertex buffer in openGl state
class MeshColored
{
private:
    unsigned int VAO, VBO, IBO, COLOR_BO, indices_size;

public:
    MeshColored();
    ~MeshColored();

    // bind vertex array and vertex buffer
    void bind();

    // unbind vertex array and vertex buffer
    void unbind();

    // draw using default param and binding
    void drawDefault();

    // clear opengl VAO, VBO, and IBO state and reset all value
    void clear();

    // create buffers using default attrib pointer
    void create(ShapeAttribute &shape, DetailedArray<vec4d> &colors);

    void updateVertices(ShapeAttribute &shape, DetailedArray<vec4d> &colors);

    // print attribute values
    void printThis()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }
};