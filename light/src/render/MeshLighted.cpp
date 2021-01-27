#include "MeshLighted.h"

MeshLighted::MeshLighted()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indices_size = 0;
}

MeshLighted::~MeshLighted() { clear(); }

void MeshLighted::clear()
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

void MeshLighted::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void MeshLighted::unbind()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshLighted::draw()
{
    bind();
    bool *keys = ScreenState::KeyState();
    glPointSize(1.0f);
    if (keys[GLFW_KEY_TAB])
        glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0); // draw wireframe
    else
        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0); // draw full
    unbind();
}

void MeshLighted::create(ShapeAttribute &shape)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // generate vertex attribute buffer
    glGenBuffers(1, &VERTEX_ATTRIB_BO);
    glBindBuffer(GL_ARRAY_BUFFER, VERTEX_ATTRIB_BO);
    glBufferData(GL_ARRAY_BUFFER, shape.vAttributes.byte_size(), shape.vAttributes.get(), GL_STATIC_DRAW);

    // add the layout
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void *)offsetof(VertexAttribute, normal));
    glEnableVertexAttribArray(1);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}