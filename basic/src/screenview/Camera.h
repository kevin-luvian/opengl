#pragma once

#include "ScreenState.h"

class Camera
{
private:
    bool firstMoveFlag;
    float moveSpeed = 10.0f, turnSpeed = 0.1f, deltaTime = 0.0f, lastFrame = 0.0f, viewRange = 100.0f;
    glm::mat4 view, projection, viewProjection;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldUp, camFront, camRight, camUp;
    glm::vec2 viewTarget, curViewTarget;
    float yaw, pitch;

    Camera();
    void updateValues();
    void updateViewProjection();

public:
    void initiate();
    void checkKeys();
    void mouseMove(float x, float y);
    void updateScreenSize();

    static Camera &GET()
    {
        static Camera instance;
        return instance;
    }
    static glm::mat4 View() { return GET().view; }
    static glm::mat4 Projection() { return GET().projection; }
    static glm::mat4 ViewProjection() { return GET().viewProjection; }
    static glm::vec3 Position() { return GET().pos; }
};