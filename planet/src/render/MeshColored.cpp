#include "MeshColored.h"

MeshColored::MeshColored()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indices_size = 0;
}

MeshColored::~MeshColored() { clear(); }

void MeshColored::clear()
{
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (IBO != 0)
        glDeleteBuffers(1, &IBO);
    VAO = 0;
    VBO = 0;
    IBO = 0;
}

void MeshColored::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void MeshColored::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void MeshColored::drawDefault()
{
    bind();
    bool *keys = ScreenState::KeyState();
    glPointSize(1.0f);
    if (keys[GLFW_KEY_TAB])
        // glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0); // draw full
        glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    // glDrawElements(GL_POINTS, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    else
        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0); // draw full
    // glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    unbind();
}

void MeshColored::create(ShapeAttribute &shape, DetailedArray<vec4d> &colors)
{
    indices_size = shape.indices.size * Indice::count();

    // generate vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate indices/elements buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices.byte_size(), shape.indices.get(), GL_STATIC_DRAW);

    // generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.byte_size(), shape.vertices.get(), GL_STREAM_DRAW);

    // define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // color attribute
    glGenBuffers(1, &COLOR_BO);
    glBindBuffer(GL_ARRAY_BUFFER, COLOR_BO);
    glBufferData(GL_ARRAY_BUFFER, colors.byte_size(), colors.get(), GL_STREAM_DRAW);

    // color layout=1
    glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 0, 0);
    glVertexAttribDivisor(1, 0);
    glEnableVertexAttribArray(1);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MeshColored::updateVertices(ShapeAttribute &shape, DetailedArray<vec4d> &colors)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.byte_size(), shape.vertices.get(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, COLOR_BO);
    glBufferData(GL_ARRAY_BUFFER, colors.byte_size(), colors.get(), GL_STREAM_DRAW);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}