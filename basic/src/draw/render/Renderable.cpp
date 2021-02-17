#include "Renderable.h"

void Renderable::render() const
{
    bind();
    onRender();
    unbind();
}
void Renderable::onRender() const
{
    bool *keys = ScreenState::KeyState();
    glPointSize(1.0f);
    if (keys[GLFW_KEY_TAB])
        glDrawElements(GL_LINE_STRIP, ISize, GL_UNSIGNED_INT, 0); // draw wireframe
    else
        glDrawElements(GL_TRIANGLES, ISize, GL_UNSIGNED_INT, 0); // draw full
    // std::cout << "isize: " << ISize << "\n";
};
void Renderable::bind() const
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    bindAttrib();
}
void Renderable::unbind() const
{
    unbindAttrib();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Renderable::clear()
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
void Renderable::createBuffer(const Mesh &mesh)
{
    BENCHMARK_PROFILE();
    ISize = mesh.indices.size * 3;

    // generate vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate indices/elements buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.byte_size(), mesh.indices.get(), GL_STATIC_DRAW);

    // generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.byte_size(), mesh.vertices.get(), GL_STATIC_DRAW);

    // create attributes
    createAttrib();

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}