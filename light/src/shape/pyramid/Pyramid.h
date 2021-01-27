#pragma once

#include "glcomponent/Camera.h"
#include "render/material/Material.h"
#include "render/Mesh.h"
#include "render/MeshLighted.h"
#include "render/Shader.h"
#include "shape/ShapeClass.h"

class Pyramid : ShapeClass
{
private:
    Shader mShader;
    MeshLighted mMesh;
    Material mMaterial;
    glm::mat4 model, mvp;
    float mOffset = 0.0f, mAngle = 0.0f;

public:
    glm::vec3 mPos = glm::vec3(0.0f, 0.0f, 0.0f);

    Shader &getShader() { return mShader; }
    void createShape();
    void create();
    void update();
    void draw();
};