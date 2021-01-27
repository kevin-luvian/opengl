#pragma once

#include "glcomponent/Camera.h"
#include "render/Shader.h"
#include "shape/ShapeAttribute.h"

class Line
{
private:
    const char *vShaderPath = "../res/shader/vColored.vert";
    const char *fShaderPath = "../res/shader/fColored.frag";
    Vertex lineVertex[2] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    glm::vec4 colour = glm::vec4(1.0, 1.0, 0.1, 1.0);
    Shader shader;
    unsigned int VAO, VBO;

    void createMesh()
    {
        // generate vertex array
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // generate vertex buffer
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertex), &lineVertex, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

public:
    Line() {}
    Line(glm::vec3 start, glm::vec3 end)
    {
        create(start, end);
        // std::cout << "line created x:" << start.x << " y:" << start.y << " z:" << start.z << "\n";
    }

    void create(glm::vec3 start, glm::vec3 end)
    {
        lineVertex[0] = {start.x, start.y, start.z};
        lineVertex[1] = {end.x, end.y, end.z};

        shader.compileFromFile(vShaderPath, fShaderPath);
        createMesh();
    }

    void draw(glm::mat4 mvp)
    {
        shader.bind();
        shader.setMat4("mvp", mvp);
        shader.set4f("colour", colour);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_LINES, 0, 2);

        glDisableVertexAttribArray(0);
        glBindVertexArray(0);

        shader.unbind();
    }
};