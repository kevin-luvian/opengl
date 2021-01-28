#pragma once

#include "draw/mesh/Mesh.h"
#include "screenview/ScreenState.h"

class Renderer
{
protected:
    unsigned int VAO, VBO, IBO, IndicesSize;

public:
    Renderer()
    {
        VAO = 0;
        VBO = 0;
        IBO = 0;
        IndicesSize = 0;
    }
    virtual ~Renderer() { clear(); }

    virtual void bindLayouts() = 0;
    virtual void unbindLayouts() = 0;
    virtual void draw()
    {
        bind();
        bool *keys = ScreenState::KeyState();
        glPointSize(1.0f);
        if (keys[GLFW_KEY_TAB])
            glDrawElements(GL_LINES, IndicesSize, GL_UNSIGNED_INT, 0); // draw wireframe
        else
            glDrawElements(GL_TRIANGLES, IndicesSize, GL_UNSIGNED_INT, 0); // draw full
        unbind();
    }
    void print()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }

protected:
    void create(Mesh &mesh, std::function<void()> createOther)
    {
        IndicesSize = mesh.indices.size * Indice::count();

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

        // define vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        // create other attributes
        createOther();

        // reset
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

private:
    void bind()
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glEnableVertexAttribArray(0);
        bindLayouts();
    }
    void unbind()
    {
        unbindLayouts();
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void clear()
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
};