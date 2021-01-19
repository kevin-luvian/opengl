#pragma once

#include "glcomponent/ScreenState.h"
#include "Mesh.h"
#include "Shader.h"

struct InstanceAttr
{
    glm::vec4 color;
    glm::vec3 position;
    glm::mat4 model;
};

struct AttributePayload
{
    std::unique_ptr<unsigned int[]> indices;
    std::unique_ptr<float[]> vertices;
    std::unique_ptr<InstanceAttr[]> instances;
    unsigned int indicesCount, verticesCount, instancesCount;

    unsigned int getIndicesSize() { return indicesCount * getIndicesTypeSize(); }
    unsigned int getIndicesTypeSize() { return sizeof(unsigned int); }
    unsigned int getVerticesSize() { return verticesCount * getVerticesTypeSize(); }
    unsigned int getVerticesTypeSize() { return sizeof(float); }
    unsigned int getInstancesSize() { return instancesCount * getInstancesTypeSize(); }
    unsigned int getInstancesTypeSize() { return sizeof(InstanceAttr); }
};

// Holds attributes and ID for vertex and vertex buffer in openGl state
class InstancedMesh
{
private:
    const int LAYOUT_COUNT = 6;
    unsigned int VAO, VBO, IBO, INSTANCE_BO;

public:
    InstancedMesh();
    ~InstancedMesh();

    // bind vertex array and vertex buffer
    void bind();

    // unbind vertex array and vertex buffer
    void unbind();

    // draw elements using glDrawElementsInstanced
    void draw(AttributePayload &payload);

    // reset all value
    void resetValues();

    // clear opengl buffers state and reset all value
    void clear();

    // create buffers using default attrib pointer
    void create(AttributePayload &payload);

    // update instance buffer data
    void recreateInstance(AttributePayload &payload);

    // print attribute values
    void printThis()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }
};