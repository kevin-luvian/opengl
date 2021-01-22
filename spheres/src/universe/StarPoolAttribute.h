#pragma once

#include "render/InstancedMesh.h"
#include "shape/ShapeAttribute.h"
#include "render/InstanceAttr.h"

struct StarPoolAttribute
{
    unsigned int size, quality;
    InstancedMesh mesh;
    ShapeAttribute sphereAttr;
    DetailedArray<InstanceAttr> instances;

    void createMesh()
    {
        mesh.create(sphereAttr, instances);
        release();
    }

    void recreateMesh()
    {
        mesh.recreateInstance(instances);
        release();
    }

    void drawMesh()
    {
        mesh.draw(sphereAttr, instances);
    }

    void release()
    {
        sphereAttr.release();
        instances.release();
    }
};