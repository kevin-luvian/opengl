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
    for (int i = 0; i < LAYOUT_COUNT; i++)
    {
        glDisableVertexAttribArray(i);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void InstancedMesh::draw(AttributePayload &payload)
{
    bind();
    bool *keys = ScreenState::KeyState();
    if (keys[GLFW_KEY_TAB])
        glDrawElementsInstanced(GL_LINE_STRIP, payload.indicesCount, GL_UNSIGNED_INT, 0, payload.instancesCount);
    else
        glDrawElementsInstanced(GL_TRIANGLES, payload.indicesCount, GL_UNSIGNED_INT, 0, payload.instancesCount);
    unbind();
}

void InstancedMesh::create(AttributePayload &payload)
{
    // generate vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate indices/elements buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, payload.getIndicesSize(), payload.indices.get(), GL_STATIC_DRAW);

    // generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, payload.getVerticesSize(), payload.vertices.get(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // generate instance buffer
    glGenBuffers(1, &INSTANCE_BO);
    glBindBuffer(GL_ARRAY_BUFFER, INSTANCE_BO);
    glBufferData(GL_ARRAY_BUFFER, payload.getInstancesSize(), payload.instances.get(), GL_DYNAMIC_DRAW);

    // color layout=1
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, payload.getInstancesTypeSize(), (void *)offsetof(InstanceAttr, color));
    glVertexAttribDivisor(1, 1);

    // position layout=2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, payload.getInstancesTypeSize(), (void *)offsetof(InstanceAttr, position));
    glVertexAttribDivisor(2, 1);

    // model layout=3, 4, 5, 6
    int layoutModelPos = 3;
    std::size_t offset = offsetof(InstanceAttr, model);
    std::size_t vec4Size = sizeof(glm::vec4);
    for (int i = 0; i < 4; i++)
    {
        glVertexAttribPointer(layoutModelPos + i, 4, GL_FLOAT, GL_FALSE, payload.getInstancesTypeSize(), (void *)(offset + (i * vec4Size)));
        glVertexAttribDivisor(layoutModelPos + i, 1);
    }

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void InstancedMesh::recreateInstance(AttributePayload &payload)
{
    glBindBuffer(GL_ARRAY_BUFFER, INSTANCE_BO);
    glBufferData(GL_ARRAY_BUFFER, payload.getInstancesSize(), payload.instances.get(), GL_DYNAMIC_DRAW);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}