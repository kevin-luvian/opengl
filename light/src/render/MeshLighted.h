#pragma once

#include <functional>
#include "shape/ShapeAttribute.h"
#include "glcomponent/ScreenState.h"
#include "Shader.h"

// Holds attributes and ID for vertex and vertex buffer in openGl state
class MeshLighted
{
private:
    unsigned int VAO, VBO, IBO, VERTEX_ATTRIB_BO, indices_size;

public:
    MeshLighted();
    ~MeshLighted();

    // bind vertex array and vertex buffer
    void bind();

    // unbind vertex array and vertex buffer
    void unbind();

    // draw using default param and binding
    void draw();

    // clear opengl VAO, VBO, and IBO state and reset all value
    void clear();

    // create buffers using default attrib pointer
    void create(ShapeAttribute &shape);

    // print attribute values
    void printThis()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }
};