#pragma once

#include "render/InstancedMesh.h"
#include "render/Shader.h"
#include "glcomponent/Camera.h"
#include "SphereGenerator.h"
#include "render/InstanceAttr.h"

class SpherePool
{
private:
    const char *vShaderPath = "../res/shader/vInstanced.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    const int THREAD_COUNT = 3;
    const unsigned int SPHERES_RANGE = 1000;

    AttributePayload payload;
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<InstancedMesh> mMesh;
    unsigned int mSize, numX, numY;
    float sphereAngle;

    std::unique_ptr<InstanceAttr[]> generateSphereInstances() const;

public:
    SpherePool(unsigned int size, unsigned int seg) : SpherePool(size, seg, seg) {}
    SpherePool(unsigned int size, unsigned int segX, unsigned int segY);

    void create();
    void update();
    void draw();
    void recreateModels();
};