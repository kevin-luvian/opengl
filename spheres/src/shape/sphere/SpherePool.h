#pragma once

#include "render/Mesh.h"
#include "render/Shader.h"
#include "glcomponent/Camera.h"
#include "SphereGenerator.h"

static const float DEFAULT_SPHERE_RADIUS = 1.0f;

class Sphere
{
private:
    float angle;

public:
    float radius;
    glm::vec3 pos;
    glm::mat4 model, mvp;

    Sphere() : Sphere(DEFAULT_SPHERE_RADIUS, glm::vec3(0.0f, 0.0f, -1.0f)){};
    Sphere(float r, glm::vec3 p)
    {
        radius = r;
        pos = p;
        update();
    }
    void update()
    {
        angle = fmodf32(angle + 0.3f, 360.0f);
        // sSize += 0.001f;

        // currentSize[0] = util::mapBetweenFloat(sSize, 0, vpSize[2], 0.0f, 1.0f);
        // currentSize[1] = util::mapBetweenFloat(sSize, 0, vpSize[3], 0.0f, 1.0f);

        // reset to identity matrix
        model = glm::mat4(1.0f);

        // do transformation in reverse order
        model = glm::translate(model, pos);
        model = glm::rotate(model, util::toRadians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::rotate(model, util::toRadians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(radius));

        mvp = Camera::GET().getViewProjection() * model;
    }
    void updateQuick() { mvp = Camera::GET().getViewProjection() * model; }
};

class SpherePool
{
private:
    const char *vShaderPath = "../res/shader/vSeparate.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    const int THREAD_COUNT = 3;

    // Create two threads
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<Mesh> mMesh;
    // std::unique_ptr<Texture> mTexture;
    std::unique_ptr<Sphere[]> mSpheres;
    unsigned int mSize, numX, numY;

    void generateSpheres();
    void updateBatch(int startPos, int endPos);
    void drawBatch(int startPos, int endPos);

public:
    glm::vec3 mPos;

    SpherePool(unsigned int size, unsigned int seg) : SpherePool(size, seg, seg) {}
    SpherePool(unsigned int size, unsigned int segX, unsigned int segY);

    void create();
    void update();
    void draw();
};