#pragma once

#include "glcomponent/ScreenState.h"
#include "Mesh.h"
#include "Shader.h"
#include "InstanceAttr.h"
#include "AttributePayload.h"
#include "shape/sphere/SphereAttribute.h"

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
    void draw(SphereAttribute &attr, DetailedArray<InstanceAttr> &instances);

    // reset all value
    void resetValues();

    // clear opengl buffers state and reset all value
    void clear();

    // create buffers using default attrib pointer
    void create(SphereAttribute &attr, DetailedArray<InstanceAttr> &instances);

    // update instance buffer data
    void recreateInstance(DetailedArray<InstanceAttr> &instances);

    // print attribute values
    void printThis()
    {
        std::cout << "VAO: " << VAO << " VBO: " << VBO << " IBO: " << IBO << "\n";
    }
};