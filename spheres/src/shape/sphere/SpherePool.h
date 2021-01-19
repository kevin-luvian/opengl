#pragma once

#include "randoms/RGEN.h"
#include "render/InstancedMesh.h"
#include "render/Shader.h"
#include "glcomponent/Camera.h"
#include "SphereGenerator.h"

class SpherePool
{
private:
    const char *vShaderPath = "../res/shader/vInstanced.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    const int THREAD_COUNT = 3;
    const float SPHERES_RANGE = 1000.0f;

    AttributePayload payload;
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<InstancedMesh> mMesh;
    unsigned int mSize, numX, numY;
    float sphereAngle;

    std::unique_ptr<InstanceAttr[]> generateSphereInstances() const;
    glm::mat4 generateRandomModel(glm::vec3 pos) const;
    glm::vec3 generateRandomPosition() const;
    glm::vec4 generateRandomColor() const;

public:
    SpherePool(unsigned int size, unsigned int seg) : SpherePool(size, seg, seg) {}
    SpherePool(unsigned int size, unsigned int segX, unsigned int segY);

    void create();
    void update();
    void draw();
    void recreateModels();
};