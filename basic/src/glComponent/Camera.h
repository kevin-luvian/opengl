#pragma once

#include "ScreenState.h"

class Camera
{
private:
    float yaw = -90.0f;
    float pitch = 0.0f;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float turnSpeed = 0.1f;
    float moveSpeed = 10.0f;
    float viewRange = 200.0f;
    glm::mat4 view, projection, viewProjection;
    glm::vec3 camFront, camRight, camUp;
    glm::vec2 viewTarget, curViewTarget;
    bool firstMoveFlag = true;

    glm::vec3 pos = glm::vec3(0);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    void updateCameraNormals();
    void updateViewProjection();
    void keyUpdate();
    void screenUpdate();
    void mouseUpdate(float x, float y);

    Camera() {}
    ~Camera() {}
    static Camera &GET()
    {
        static Camera instance;
        return instance;
    }

public:
    static void MouseMove(float x, float y) { GET().mouseUpdate(x, y); }
    static void KeyUpdate() { GET().keyUpdate(); }
    static void UpdateSize() { GET().screenUpdate(); };
    static glm::vec3 Front()
    {
        glm::vec3 f = GET().camFront;
        return f;
    }
    static glm::mat4 View() { return GET().view; }
    static glm::mat4 Projection() { return GET().projection; }
    static glm::mat4 ViewProjection() { return GET().viewProjection; }
    static glm::vec3 Position() { return GET().pos; }
    static unit::vec3 UnitPosition() { return unit::vec3(GET().pos); }
};