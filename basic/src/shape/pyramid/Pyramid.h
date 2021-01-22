#pragma once

#include "glcomponent/Camera.h"
#include "render/Mesh.h"
#include "render/Shader.h"
#include "shape/ShapeAttribute.h"

class Pyramid
{
private:
    Shader mShader;
    Mesh mMesh;
    glm::mat4 model, mvp;
    float mOffset = 0.0f, mAngle = 0.0f;

public:
    glm::vec3 mPos;

    void create();
    void update();
    void draw();
};