#pragma once

#include "render/Renderable.h"
#include "mesh/core/Mesh.h"

class Object : public Mesh, Renderable
{
public:
    virtual ~Object() {}
    void useMesh(Mesh mesh) { transfer(mesh); }

protected:
    Object()
    {
        std::cout << "creating object\n";
    }
};