#include "InstancedMesh.h"

InstancedMesh::InstancedMesh() { resetValues(); }

InstancedMesh::~InstancedMesh() { clear(); }

void InstancedMesh::clear()
{
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (IBO != 0)
        glDeleteBuffers(1, &IBO);
    if (INSTANCE_BO != 0)
        glDeleteBuffers(1, &INSTANCE_BO);
    resetValues();
}

void InstancedMesh::resetValues()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    INSTANCE_BO = 0;
}

void InstancedMesh::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    for (int i = 0; i < LAYOUT_COUNT; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void InstancedMesh::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    for (int i = 0; i < LAYOUT_COUNT; i++)
    {
        glDisableVertexAttribArray(i);
    }
}

void InstancedMesh::draw(ShapeAttribute &attr, DetailedArray<InstanceAttr> &instances)
{
    bind();
    bool *keys = ScreenState::KeyState();
    if (keys[GLFW_KEY_TAB])
        glDrawElementsInstanced(GL_LINE_STRIP, attr.indices.size, GL_UNSIGNED_INT, 0, instances.size);
    else
        glDrawElementsInstanced(GL_TRIANGLES, attr.indices.size, GL_UNSIGNED_INT, 0, instances.size);
    unbind();
}

void InstancedMesh::create(ShapeAttribute &attr, DetailedArray<InstanceAttr> &instances)
{
    // generate vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate indices/elements buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, attr.indices.byte_size(), attr.indices.get(), GL_STATIC_DRAW);

    // generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, attr.vertices.byte_size(), attr.vertices.get(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // generate instance buffer
    glGenBuffers(1, &INSTANCE_BO);
    glBindBuffer(GL_ARRAY_BUFFER, INSTANCE_BO);
    glBufferData(GL_ARRAY_BUFFER, instances.byte_size(), instances.data.get(), GL_DYNAMIC_DRAW);

    // color layout=1
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, instances.type_size(), (void *)offsetof(InstanceAttr, color));
    glVertexAttribDivisor(1, 1);

    // position layout=2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, instances.type_size(), (void *)offsetof(InstanceAttr, position));
    glVertexAttribDivisor(2, 1);

    // model layout=3, 4, 5, 6
    int layoutModelPos = 3;
    std::size_t offset = offsetof(InstanceAttr, model);
    std::size_t vec4Size = sizeof(glm::vec4);
    for (int i = 0; i < 4; i++)
    {
        glVertexAttribPointer(layoutModelPos + i, 4, GL_FLOAT, GL_FALSE, instances.type_size(), (void *)(offset + (i * vec4Size)));
        glVertexAttribDivisor(layoutModelPos + i, 1);
    }

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unbind();
}

void InstancedMesh::recreateInstance(DetailedArray<InstanceAttr> &instances)
{
    glBindBuffer(GL_ARRAY_BUFFER, INSTANCE_BO);
    glBufferData(GL_ARRAY_BUFFER, instances.byte_size(), instances.data.get(), GL_DYNAMIC_DRAW);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}