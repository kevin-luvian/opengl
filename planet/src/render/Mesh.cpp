#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indices_size = 0;
}

Mesh::~Mesh() { clear(); }

void Mesh::clear()
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

void Mesh::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnableVertexAttribArray(0);
}

void Mesh::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::drawDefault()
{
    bind();
    bool *keys = ScreenState::KeyState();
    glPointSize(1.0f);
    if (keys[GLFW_KEY_TAB])
        // glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0); // draw full
        glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    else
        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0); // draw full
    // glDrawElements(GL_POINTS, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    // glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    unbind();
}

void Mesh::create(ShapeAttribute &shape)
{
    create(shape, []() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    });
}

void Mesh::create(ShapeAttribute &shape, std::function<void()> bindVertexCallback)
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
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.byte_size(), shape.vertices.get(), GL_STATIC_DRAW);

    // define vertex attributes
    bindVertexCallback();

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}