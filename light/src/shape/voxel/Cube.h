#pragma once

#include "render/Shader.h"
#include "render/Mesh.h"
#include "shape/ShapeClass.h"

class Cube : ShapeClass
{
private:
    Shader mShader;
    Mesh mMesh;
    glm::mat4 model, mvp;
    float mOffset = 0.0f, mAngle = 0.0f;

public:
    glm::vec3 mPos = glm::vec3(0.0f, 0.0f, 0.0f);
    float mSize = 0.3f;

    Shader &getShader() { return mShader; }
    void createShape();
    void create();
    void update();
    void draw();
};