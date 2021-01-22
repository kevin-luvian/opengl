#pragma once

#include "glcomponent/Camera.h"
#include "shape/ShapeAttribute.h"
#include "render/Shader.h"
#include "render/InstancedMesh.h"
#include "render/InstanceAttr.h"
#include "IcoSH.h"

class Icosahedron
{
public:
    ShapeAttribute shape;
    ShapeAttribute moveShape() { return std::move(shape); }
    void generateShape();
};

class IcosahedronDrawer
{
private:
    const char *vShaderPath = "../res/shader/vInstanced.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    // Icosahedron ico;
    ShapeAttribute shape;
    Shader shader;
    InstancedMesh mesh;
    DetailedArray<InstanceAttr> instances;

public:
    void createInstance()
    {
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(5.0f));

        InstanceAttr attr;
        attr.position = glm::vec3(0.0f);
        attr.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        attr.model = model;

        InstanceAttr attr2;
        attr.position = glm::vec3(1.0f);
        attr.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        attr.model = model;

        instances.make_empty(2);
        instances.data[0] = attr;
        instances.data[1] = attr2;
    }

    void createShape()
    {
        int count = 0;
        int vSize = IcoSH::vertices.size();
        shape.vertices.make_empty(vSize);
        for (auto &vert : IcoSH::vertices)
        {
            shape.vertices[count++] = vert;
        }
        count = 0;
        int iSize = IcoSH::triangles.size();
        shape.indices.make_empty(iSize);
        for (auto &tri : IcoSH::triangles)
        {
            shape.indices[count++] = tri;
        }
    }

    void create()
    {
        createInstance();
        // ico.generateShape();
        createShape();
        shader.compileFromFile(vShaderPath, fShaderPath);
        mesh.create(shape, instances);
        instances[0].print();
    }

    void draw()
    {
        glm::mat4 identity(1.0f);
        identity = glm::rotate(identity, util::toRadians(60.0), glm::vec3(1.0f));
        glm::mat4 viewProjection = Camera::GET().getViewProjection();
        shader.bind();
        shader.setMat4("viewProjection", viewProjection);
        shader.setMat4("transform", identity);
        mesh.draw(shape, instances);
    }
};