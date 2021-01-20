#pragma once

#include "ScreenState.h"

class Camera
{
private:
    bool firstMoveFlag;
    float turnSpeed = 0.1f, deltaTime = 0.0f, lastFrame = 0.0f, viewRange = 3000.0f;
    glm::mat4 projection;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldUp, camFront, camRight, camUp;
    glm::vec2 viewTarget, curViewTarget;
    float yaw, pitch;

    Camera();
    void updateValues();

public:
    bool autoMoveForward = false;
    float moveSpeed = 300.0f;

    void initiate();
    void checkKeys();
    void mouseMove(float x, float y);
    void updateScreenSize();
    glm::mat4 getViewProjection();

    static Camera &GET();
    static glm::mat4 ViewProjection() { return GET().getViewProjection(); }
    static glm::vec3 CurrentPos() { return GET().pos; }
};