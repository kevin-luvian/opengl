#pragma once

#include <functional>

#include "shape/ShapeAttribute.h"
#include "glcomponent/ScreenState.h"
#include "Shader.h"

// Holds attributes and ID for vertex and vertex buffer in openGl state
class Mesh
{
private:
    unsigned int VAO, VBO, IBO, indices_size;

public:
    Mesh();
    ~Mesh();

    // bind vertex array and vertex buffer
    void bind();

    // unbind vertex array and vertex buffer
    void unbind();

    // draw elements using glDrawElements
    void draw();

    // draw using default param and binding
    void drawDefault();

    // clear opengl VAO, VBO, and IBO state and reset all value
    void clear();

    // create buffers using default attrib pointer
    void create(ShapeAttribute &attr);

    // create buffers with callback to set custom attrib pointer
    void create(ShapeAttribute &attr, std::function<void()> bindVertexCallback);

    // print attribute values
    void printThis()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }
};